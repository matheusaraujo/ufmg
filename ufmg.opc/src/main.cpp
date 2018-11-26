/*=========================================================================

Servidor OPC para uso com Arduino

=========================================================================*/

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include <time.h>
// le arquivo de configuracao
#include <iostream>
#include <fstream>
#include <math.h>

/*
  Includes do OPC Wintech
*/
#include <opcda.h>
#include "opc_ae.h"
#include "opcerror.h"
#include "wtopcsvrapi.h"
#include "WtOPCsvrEXTapi.h"
#include "SerialPort.h"
#define IDT_TIMER1  200

#define IDT_TEMPO_ARD  600
#define IBUF_TAMANHO  100
#define ID_WATCHDOG_TIMER_COM 5

#define NUM_ITEMS  12
#define NUM_COLUMNS     7
#define MAX_ITEMLEN     64

#define C_COLUMNS       4

#define TIMER_INIT      5

/*
OPC callback de escrita
*/
//void CALLBACK EXPORT WriteNotifyCallback(HANDLE Handle, VARIANT *pNewValue, DWORD *pDeviceError);


//void CALLBACK EXPORT WriteNotifyCallback(HANDLE Handle, VARIANT *pNewValue, DWORD *pDeviceError);
//LRESULT CALLBACK WriteNotifyCallback(HANDLE Handle, VARIANT *pNewValue, DWORD *pDeviceError);
void CALLBACK WriteNotifyCallback(HANDLE Handle, VARIANT *pNewValue, DWORD *pDeviceError);

// criacao de itens
void Criar_Itens();


// atualização periodica dos itens
void Atualiza_VQT_Itens();

char c_sinais[ NUM_ITEMS ][ 16]
{
    "ED1",
    "ED2",
    "ED3",
    "ED4",
    "SD1",
    "SD2",
    "SD3",
    "EA1",
    "EA2",
    "EA3",
    "SA1",
    "SA2",
};

char c_canais[ NUM_ITEMS ][ 16]
{
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "A0",
    "A1",
    "A2",
    "10",
    "11",
};

using namespace std;

/*
   GUID do servidor
*/
//const GUID CLSID_WtSvrTst2 =
//{ 0xc6c83062, 0x6c69, 0x11d4, { 0x80, 0xff, 0x0, 0xc0, 0x4f, 0x79, 0xf, 0x3b } };

// {59DD39E3-D4F1-4A43-9823-BAC02CE3A134}
//IMPLEMENT_OLECREATE(<<class>>, <<external_name>>,
//0x59dd39e3, 0xd4f1, 0x4a43, 0x98, 0x23, 0xba, 0xc0, 0x2c, 0xe3, 0xa1, 0x34);

// {59DD39E3-D4F1-4A43-9823-BAC02CE3A134}
//DEFINE_GUID(<<name>>,
//0x59dd39e3, 0xd4f1, 0x4a43, 0x98, 0x23, 0xba, 0xc0, 0x2c, 0xe3, 0xa1, 0x34);

// {59DD39E3-D4F1-4A43-9823-BAC02CE3A134}
static const GUID CLSID_UFMGWT =
{ 0x6325f8c9, 0xca52, 0x43a4, { 0xa3, 0x97, 0x6d, 0x49, 0xbe, 0xf9, 0xc3, 0x29 } };


// {F51DA47D-5BBC-4E95-A781-5A877C3DAE18}

//{59DD39E3-D4F1-4A43-9823-BAC02CE3A134}

//[Guid("59DD39E3-D4F1-4A43-9823-BAC02CE3A134")]

//<Guid("59DD39E3-D4F1-4A43-9823-BAC02CE3A134")>

/*
Notificacao de escrita
*/

HINSTANCE hInst;

/*
Comandos e mensagens na tela
*/
HWND TextBox, hwnd_but_registrar, hwnd_but_desregistrar;
HWND hList = NULL; // List View identifier
CRITICAL_SECTION m_CriticalSection;


/*
Conexão com o arduino
*/
// Nome da porta serial à qual o arduino está conectado
char portName[32];
void Atualiza_Valores(int itamanho);
DWORD n_lidos = 0;
bool b_escreveu = false;
bool b_solicitou = false;
int i_wdgt = 0;
char buf[MAX_DATA_LENGTH];
char carimbo_tempo[MAX_DATA_LENGTH];
char c_mensagem[MAX_DATA_LENGTH];
const unsigned int BLINKING_DELAY = 1000;
int valores[NUM_ITEMS];
//Arduino SerialPort object
SerialPort *arduino;


// vaores das entrada discretas
bool ent_disc[4];

// vaores das saidaa discretas
bool sai_disc[4];

// vaores das entrada analogicas
int ent_analog[3];


// vaores das saidas analogicas
int sai_analog[2];

#define MAX_DATA_LENGTH 255

char incomingData[MAX_DATA_LENGTH];


//Control signals for turning on and turning off the led
//Check arduino code
char c_ler_ard[] = "?\n";
char c_esc_do01_0[] = "SD6 0\n";
char c_esc_do01_1[] = "SD6 1\n";
char c_esc_do02_0[] = "SD6 0\n";
char c_esc_do02_1[] = "SD6 1\n";
char c_esc_do03_0[] = "SD6 0\n";
char c_esc_do03_1[] = "SD6 1\n";

//=============================================================================
// Funções de escrita e Leitura no arduino
//=============================================================================

void exampleReceiveData(DWORD *lidos)
{
    int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
    *lidos = readResult;
    printf("%s", incomingData);
//    Sleep(60000);
}

void exampleWriteData(unsigned int delayTime)
{
    b_escreveu = arduino->writeSerialPort(c_mensagem, MAX_DATA_LENGTH);
    Sleep(IDT_TEMPO_ARD);
//    arduino->writeSerialPort(ledOFF, MAX_DATA_LENGTH);
//    Sleep(delayTime);
}
//=============================================================================

/*
Classe dos itens OPC
*/
class   CTag //: public CObject
{
public:

    HANDLE  Handle = NULL;
//  CString Name;
    char Name[20];
    VARIANT Value;
    FILETIME tempo_item;
    bool b_novo_valor = false;
    bool b_eh_escrita = false;
    int i_val_novo_val = 0;

};
CTag ItensOPC[20];

char titulo_col[ NUM_COLUMNS ][ 16]
{
    "ITEM",
    "VALOR",
    "QUALIDADE",
    "TEMPO",
    "TIPO",
    "ESCRITA",
    "CANAL"
};
//void CALLBACK EXPORT WriteNotifyCallback(HANDLE Handle, VARIANT *pNewValue, DWORD *pDeviceError)
void CALLBACK WriteNotifyCallback(HANDLE Handle, VARIANT *pNewValue, DWORD *pDeviceError)
{
//  CWtSvrTst2App   *pApp;

//  pApp = (CWtSvrTst2App *)AfxGetApp();
//  if (pApp->pView != NULL)
//      pApp->pView->WriteNotificationHandler(Handle, pNewValue, pDeviceError);

    int i;
    /*
    // usado para verificar em operação
        char buf[128];

        MessageBox(NULL, "Atualizacao", "Recebi valor",
                MB_ICONEXCLAMATION | MB_OK);
    */

    for (i = 0; i < NUM_ITEMS; i++)
    {
        if ((ItensOPC[i].Handle == Handle) & ItensOPC[i].b_eh_escrita)
        {
            VariantCopy (&(ItensOPC[i].Value), pNewValue);
            *pDeviceError = S_OK;
            ItensOPC[i].b_novo_valor = true;
            ItensOPC[i].i_val_novo_val = 0;
            /*
            // usado para verificar em operação
                        sprintf(buf, "Achei item %s : %d", ItensOPC[i].Name, i);
                        MessageBox(NULL, "Atualizar", buf,
                                            MB_ICONEXCLAMATION | MB_OK);
            */

            return;
        }
    }
    *pDeviceError = OPC_E_INVALIDHANDLE;



}


/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++
                 criacao de itens
++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void Criar_Itens()
{
    int i = 0;
    int len, j;
    VARIANT var;
    char    buf[100];
    WCHAR   wide_str[100];


    for (i = 0; i < NUM_ITEMS; i++)
    {
        switch (ItensOPC[i].Value.vt)
        {
        case VT_BOOL:
            var.vt = VT_BOOL;
            var.boolVal = 0;
            VariantCopy (&(ItensOPC[i].Value), &var);
            ItensOPC[i].Handle = CreateTag(ItensOPC[i].Name, var, OPC_QUALITY_NOT_CONNECTED, ItensOPC[i].b_eh_escrita );
            break;
        case VT_R4:
            var.vt = VT_R4;
            var.fltVal = 0.0;
            VariantCopy (&(ItensOPC[i].Value), &var);
            ItensOPC[i].Handle = CreateTag(ItensOPC[i].Name, var, OPC_QUALITY_NOT_CONNECTED, ItensOPC[i].b_eh_escrita );
            break;
        case VT_R8:
            var.vt = VT_R8;
            var.dblVal = 0.0;
            VariantCopy (&(ItensOPC[i].Value), &var);
            ItensOPC[i].Handle = CreateTag(ItensOPC[i].Name, var, OPC_QUALITY_NOT_CONNECTED, ItensOPC[i].b_eh_escrita );
            break;
        case VT_I4:
            var.vt = VT_I4;
            var.lVal = (long) 0;
            VariantCopy (&(ItensOPC[i].Value), &var);
            ItensOPC[i].Handle = CreateTag(ItensOPC[i].Name, var, OPC_QUALITY_NOT_CONNECTED, ItensOPC[i].b_eh_escrita );
            break;
        case VT_BSTR:
            var.vt = VT_BSTR;
            sprintf (buf, "Texto=%d", VT_BSTR);
            len = strlen (buf);
            for (j = 0; j < len + 1; j++)
                wide_str[j] = buf[j];
            var.bstrVal = SysAllocString (wide_str);
            VariantCopy (&(ItensOPC[i].Value), &var);
            ItensOPC[i].Handle = CreateTag(ItensOPC[i].Name, var, OPC_QUALITY_NOT_CONNECTED, ItensOPC[i].b_eh_escrita );
            break;
        } //switch(ItensOPC[i].Value.vt)
        VariantClear(&var);
    } //for(i=0;i<8;i++)
// pTag->Handle = CreateTag(pTag->Name, var, OPC_QUALITY_GOOD, TRUE );

} //void Criar_Itens()
/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++
 atualização periodica dos itens
++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void Atualiza_Valores(int itamanho)
{
    int i, len, j, k, m;
    //int idx = 0;
    int ival;
    char buf[IBUF_TAMANHO];
    //WCHAR   wide_str[100];
    SYSTEMTIME st;
    FILETIME t_agora;
    int canal = -1;

    GetSystemTime(&st);
    SystemTimeToFileTime( &st, &t_agora );

    len = itamanho;
    i = 0;
    while ((i < len) && incomingData[i] != 'I')
    {
        i++;
    }
    j = i + 2;

//Recuperacao dos itens
    /*
       Resposta do arduino:
       I;2,0;3,1;4,0;5,0;6,0;7,0;8,0;A0,527;A1,0;A2,0;S0,0;S1,0;F
    */
// primeira (0) entrada discreta
    m = 0;
    memset(buf, '\0', sizeof(buf));
    k = j;
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    canal = atoi(buf);
    k++;
    j = k;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    valores[m] = ival;
    if (ival == 0)
        ent_disc[canal - 2] = false;
    else
        ent_disc[canal - 2] = true;
    //sprintf(buf,"%d",ent_disc[canal-2]);
    //ListView_SetItemText( hList,0,2,buf);

// segundaa (1)aa entrada discreta
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    canal = atoi(buf);
    k++;
    j = k;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
        buf[k - j] = '\0';
    }
    k++;
    j = k;
    ival = atoi(buf);
    valores[m] = ival;
    if (ival == 0)
        ent_disc[canal - 2] = false;
    else
        ent_disc[canal - 2] = true;
//        sprintf(buf,"%d",ent_disc[canal-2]);
//          ListView_SetItemText( hList,1,2,buf);

// terceira entrada discreta
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    canal = atoi(buf);
    k++;
    j = k;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    valores[m] = ival;
    if (ival == 0)
        ent_disc[canal - 2] = false;
    else
        ent_disc[canal - 2] = true;
//        sprintf(buf,"%d",ent_disc[canal-2]);
//          ListView_SetItemText( hList,2,2,buf);

// quarta entrada discreta
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    canal = atoi(buf);
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    valores[m] = ival;
    if (ival == 0)
        ent_disc[canal - 2] = false;
    else
        ent_disc[canal - 2] = true;
//        sprintf(buf,"%d",ent_disc[canal-2]);
//          ListView_SetItemText( hList,3,2,buf);

    /*
       Resposta do arduino:
       I;2,0;3,1;4,0;5,0;6,0;7,0;8,0;A0,527;A1,0;A2,0;S0,0;S1,0;F
    */


// primeira saida discreta
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    canal = atoi(buf);
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    valores[m] = ival;
    if (ival == 0)
        sai_disc[canal - 6] = false;
    else
        sai_disc[canal - 6] = true;
//        sprintf(buf,"%d",sai_disc[canal-6]);
//          ListView_SetItemText( hList,4,2,buf);


// segunda saida discreta
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    canal = atoi(buf);
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    valores[m] = ival;
    if (ival == 0)
        sai_disc[canal - 6] = false;
    else
        sai_disc[canal - 6] = true;
//        sprintf(buf,"%d",sai_disc[canal-6]);
//          ListView_SetItemText( hList,5,2,buf);

//++++++++

// terceira saida discreta
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    canal = atoi(buf);
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    valores[m] = ival;
    if (ival == 0)
        sai_disc[canal - 6] = false;
    else
        sai_disc[canal - 6] = true;
//        sprintf(buf,"%d",sai_disc[canal-6]);
//          ListView_SetItemText( hList,6,2,buf);


    /*
       Resposta do arduino:
       I;2,0;3,1;4,0;5,0;6,0;7,0;8,0;A0,527;A1,0;A2,0;S0,0;S1,0;F
    */
// primeira entrada analogica
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    canal = buf[1] - 48;
    k++;
    j = k;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    ent_analog[canal] = ival;
    valores[m] = ival;
//        sprintf(buf,"%d",ent_analog[canal]);
//          ListView_SetItemText( hList,7,2,buf);

// segunda entrada analogica
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    canal = buf[1] - 48;
    k++;
    j = k;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    ent_analog[canal] = ival;
    valores[m] = ival;
//        sprintf(buf,"%d",ent_analog[canal]);
//          ListView_SetItemText( hList,8,2,buf);


// terceira entrada analogica
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    canal = buf[1] - 48;
    k++;
    j = k;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    ent_analog[canal] = ival;
    valores[m] = ival;
//        sprintf(buf,"%d",ent_analog[canal]);
//          ListView_SetItemText( hList,9,2,buf);

    /*
       Resposta do arduino:
    Rev 0:
       I;2,0;3,1;4,0;5,0;6,0;7,0;8,0;A0,527;A1,0;A2,0;S0,0;S1,0;F
    Rev 1:
       I;2,1;3,0;4,0;5,0;6,0;7,0;8,0;A0,0;A1,0;A2,669;S0,0;S1,0;F

    */
// primeira saida analogica
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    canal = buf[1] - 48;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    sai_analog[canal] = ival;
    valores[m] = ival;
//        sprintf(buf,"%d",sai_analog[canal]);
//          ListView_SetItemText( hList,10,2,buf);

// segunda saida analogica
    m++;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ',')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    canal = buf[1] - 48;
    memset(buf, '\0', sizeof(buf));
    while ((k < len) && incomingData[k] != ';')
    {
        buf[k - j] = incomingData[k];
        k++;
    }
    k++;
    j = k;
    ival = atoi(buf);
    sai_analog[canal] = ival;
    valores[m] = ival;
//        sprintf(buf,"%d",sai_analog[canal]);
//          ListView_SetItemText( hList,11,2,buf);


    sprintf(buf, "A hora do sistema  : %02d:%02d:%02d.%03d\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    sprintf(carimbo_tempo, "%02d/%02d/%04d:%02d:%02d:%02d.%03d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
//      printf("\n\nHora de processamento : %s\n", carimbo_tempo);


//        for(i=0;i<NUM_ITEMS;i++)
//        {
//             ListView_SetItemText( hList,i,3,"OK");
//             ListView_SetItemText( hList,i,4,carimbo_tempo);
//        }

    /*

            ListView_SetItemText( hList,0,3,"OK");
            ListView_SetItemText( hList,1,3,"OK");
            ListView_SetItemText( hList,2,3,"OK");
            ListView_SetItemText( hList,3,3,"OK");
            ListView_SetItemText( hList,4,3,"OK");
            ListView_SetItemText( hList,5,3,"OK");
            ListView_SetItemText( hList,6,3,"OK");
            ListView_SetItemText( hList,7,3,"OK");
            ListView_SetItemText( hList,8,3,"OK");
            ListView_SetItemText( hList,9,3,"OK");
            ListView_SetItemText( hList,10,3,"OK");
            ListView_SetItemText( hList,11,3,"OK");

            ListView_SetItemText( hList,0,4,carimbo_tempo);
            ListView_SetItemText( hList,1,4,carimbo_tempo);
            ListView_SetItemText( hList,2,4,carimbo_tempo);
            ListView_SetItemText( hList,3,4,carimbo_tempo);
            ListView_SetItemText( hList,4,4,carimbo_tempo);
            ListView_SetItemText( hList,5,4,carimbo_tempo);
            ListView_SetItemText( hList,6,4,carimbo_tempo);
            ListView_SetItemText( hList,7,4,carimbo_tempo);
            ListView_SetItemText( hList,8,4,carimbo_tempo);
            ListView_SetItemText( hList,9,4,carimbo_tempo);
            ListView_SetItemText( hList,10,4,carimbo_tempo);
            ListView_SetItemText( hList,11,4,carimbo_tempo);
    */

}

/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++
 atualização periodica dos itens
++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void Atualiza_VQT_Itens()
{
    int i, len, j, aux;
    int tamanho;
    //int random;
    char buf[100];
    char cvalor[32];
    WCHAR   wide_str[100];
    VARIANT var;
    SYSTEMTIME st;
    FILETIME t_agora;
    //SYSTEMTIME stl;

    GetSystemTime(&st);
    SystemTimeToFileTime( &st, &t_agora );
    VariantInit(&var);

    sprintf(buf, "%02d/%02d/%04d:%02d:%02d:%02d.%03d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    StartUpdateTags();
    for (i = 0; i < NUM_ITEMS; i++)
    {
        ItensOPC[i].i_val_novo_val++;
        switch (ItensOPC[i].Value.vt)
        {
        case VT_BOOL:
            var.vt = VT_BOOL;
            if (ItensOPC[i].b_novo_valor)
            {
                Sleep(1000);
                memset(c_mensagem, '\0', sizeof(c_mensagem));
                strcpy(c_mensagem, "SD");
                memset(buf, '\0', sizeof(buf));
                strcpy(buf, c_canais[i]);
                strcat(c_mensagem, buf);
                strcat(c_mensagem, " ");

                if (ItensOPC[i].Value.boolVal) {
                    strcat(c_mensagem, "1\n");
                } else {
                    strcat(c_mensagem, "0\n");
                }

                b_escreveu = false;
                exampleWriteData(BLINKING_DELAY);
                if (b_escreveu) {
                    memset(incomingData, sizeof(incomingData), '\0');
                    n_lidos = 0;
                    exampleReceiveData(&n_lidos);
                    tamanho = n_lidos;
                    if (tamanho > 0)
                        Atualiza_Valores(tamanho);
                }

                var.boolVal = ItensOPC[i].Value.boolVal;
                UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                ItensOPC[i].b_novo_valor = false;
                if (ItensOPC[i].Value.boolVal)
                {

                    ListView_SetItemText( hList, i, 1, "true");
                }
                else
                {
                    ListView_SetItemText( hList, i, 1, "false");
                }
                ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                ListView_SetItemText( hList, i, 3, buf);
            }
            else
            {
                if (ItensOPC[i].i_val_novo_val > TIMER_INIT)
                {
                    var.boolVal = valores[i];
                    ItensOPC[i].i_val_novo_val = TIMER_INIT;
                    VariantCopy (&(ItensOPC[i].Value), &var);
                    UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                    if (ItensOPC[i].Value.boolVal)
                    {

                        ListView_SetItemText( hList, i, 1, "true");
                    }
                    else
                    {
                        ListView_SetItemText( hList, i, 1, "false");
                    }
                    ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                    ListView_SetItemText( hList, i, 3, buf);
                }
            }
            break;
        case VT_R4:
            var.vt = VT_R4;
            if (ItensOPC[i].b_novo_valor)
            {
                Sleep(5000);
                memset(c_mensagem, '\0', sizeof(c_mensagem));
                strcpy(c_mensagem, "SA");
                memset(buf, '\0', sizeof(buf));
                strcpy(buf, c_canais[i]);
                strcat(c_mensagem, buf);
                strcat(c_mensagem, " ");

                //if ((ItensOPC[i].Value.intVal >= 0) && (ItensOPC[i].Value.intVal <= 255)) {
                if ((ItensOPC[i].Value.fltVal >= 0.0) && (ItensOPC[i].Value.fltVal <= 255.0)) {
                    aux = (int) floor(ItensOPC[i].Value.fltVal);
                    //itoa(ItensOPC[i].Value.intVal, buf, 10);
                    itoa(aux, buf, 10);
                    strcat(c_mensagem, buf);
                    strcat(c_mensagem, "\n");

                    b_escreveu = false;
                    exampleWriteData(BLINKING_DELAY);
                    if (b_escreveu)
                    {
                        memset(incomingData, sizeof(incomingData), '\0');
                        n_lidos = 0;
                        exampleReceiveData(&n_lidos);
                        tamanho = n_lidos;
                        if (tamanho > 0)
                            Atualiza_Valores(tamanho);
                    }
                }

                var.fltVal = ItensOPC[i].Value.fltVal;
                UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                ItensOPC[i].b_novo_valor = false;
                sprintf(cvalor, "%f", ItensOPC[i].Value.fltVal);
                ListView_SetItemText( hList, i, 1, cvalor);
                ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                ListView_SetItemText( hList, i, 3, buf);
            }
            else
            {
                if (ItensOPC[i].i_val_novo_val > TIMER_INIT)
                {
                    var.fltVal = (float)valores[i] / 100.0f;
                    ItensOPC[i].i_val_novo_val = TIMER_INIT;
                    VariantCopy (&(ItensOPC[i].Value), &var);
                    UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                    sprintf(cvalor, "%f", ItensOPC[i].Value.fltVal);
                    ListView_SetItemText( hList, i, 1, cvalor);
                    ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                    ListView_SetItemText( hList, i, 3, buf);
                }
            }
            break;
        case VT_R8:
            var.vt = VT_R8;
            if (ItensOPC[i].b_novo_valor)
            {
                memset(c_mensagem, '\0', sizeof(c_mensagem));
                strcpy(c_mensagem, "SA");
                memset(buf, '\0', sizeof(buf));
                strcpy(buf, c_canais[i]);
                strcat(c_mensagem, buf);
                strcat(c_mensagem, " ");

                if ((ItensOPC[i].Value.intVal >= 0) && (ItensOPC[i].Value.intVal <= 255)) {
                    itoa(ItensOPC[i].Value.intVal, buf, 10);
                    strcat(c_mensagem, buf);
                    strcat(c_mensagem, "\n");

                    b_escreveu = false;
                    exampleWriteData(BLINKING_DELAY);
                    if (b_escreveu)
                    {
                        memset(incomingData, sizeof(incomingData), '\0');
                        n_lidos = 0;
                        exampleReceiveData(&n_lidos);
                        tamanho = n_lidos;
                        if (tamanho > 0)
                            Atualiza_Valores(tamanho);
                    }
                }

                var.dblVal = ItensOPC[i].Value.dblVal;
                UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                ItensOPC[i].b_novo_valor = false;
                sprintf(cvalor, "%f", ItensOPC[i].Value.dblVal);
                ListView_SetItemText( hList, i, 1, cvalor);
                ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                ListView_SetItemText( hList, i, 3, buf);
            }
            else
            {
                if (ItensOPC[i].i_val_novo_val > TIMER_INIT)
                {
                    var.dblVal = (double)valores[i] / 100.0f;
                    ItensOPC[i].i_val_novo_val = TIMER_INIT;
                    VariantCopy (&(ItensOPC[i].Value), &var);
                    UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                    sprintf(cvalor, "%f", ItensOPC[i].Value.dblVal);
                    ListView_SetItemText( hList, i, 1, cvalor);
                    ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                    ListView_SetItemText( hList, i, 3, buf);
                }
            }
            break;
        case VT_I4:
            var.vt = VT_I4;
            if (ItensOPC[i].b_novo_valor)
            {
                memset(c_mensagem, '\0', sizeof(c_mensagem));
                strcpy(c_mensagem, "SA");
                memset(buf, '\0', sizeof(buf));
                strcpy(buf, c_canais[i]);
                strcat(c_mensagem, buf);
                strcat(c_mensagem, " ");

                if ((ItensOPC[i].Value.intVal >= 0) && (ItensOPC[i].Value.intVal <= 255)) {
                    itoa(ItensOPC[i].Value.intVal, buf, 10);
                    strcat(c_mensagem, buf);
                    strcat(c_mensagem, "\n");

                    b_escreveu = false;
                    exampleWriteData(BLINKING_DELAY);
                    if (b_escreveu)
                    {
                        memset(incomingData, sizeof(incomingData), '\0');
                        n_lidos = 0;
                        exampleReceiveData(&n_lidos);
                        tamanho = n_lidos;
                        if (tamanho > 0)
                            Atualiza_Valores(tamanho);
                    }
                }

                var.lVal = ItensOPC[i].Value.lVal;
                UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                ItensOPC[i].b_novo_valor = false;
                sprintf(cvalor, "%ld", ItensOPC[i].Value.lVal);
                ListView_SetItemText( hList, i, 1, cvalor);
                ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                ListView_SetItemText( hList, i, 3, buf);
            }
            else
            {
                if (ItensOPC[i].i_val_novo_val > TIMER_INIT)
                {
                    var.lVal = (long) valores[i];
                    ItensOPC[i].i_val_novo_val = TIMER_INIT;
                    VariantCopy (&(ItensOPC[i].Value), &var);
                    UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                    sprintf(cvalor, "%ld", ItensOPC[i].Value.lVal);
                    ListView_SetItemText( hList, i, 1, cvalor);
                    ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                    ListView_SetItemText( hList, i, 3, buf);
                }
            }
            break;
        case VT_BSTR:

            var.vt = VT_BSTR;
            if (ItensOPC[i].b_novo_valor)
            {
                var.bstrVal = ItensOPC[i].Value.bstrVal;
                UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
                ItensOPC[i].b_novo_valor = false;
//                        sprintf(cvalor,"%s",ItensOPC[i].Value.bstrVal);
//                        ListView_SetItemText( hList,i,1,cvalor);
                ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                ListView_SetItemText( hList, i, 3, buf);
            }
            else
            {
                if (ItensOPC[i].i_val_novo_val > TIMER_INIT)
                {
                    sprintf (buf, "Texto=%d", valores[i]);
                    len = strlen (buf);
                    for (j = 0; j < len + 1; j++)
                        wide_str[j] = buf[j];
                    var.bstrVal = SysAllocString (wide_str);
                    ItensOPC[i].i_val_novo_val = TIMER_INIT;
                    VariantCopy (&(ItensOPC[i].Value), &var);
                    UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD, t_agora);
//                            sprintf(cvalor,"%s",ItensOPC[i].Value.bstrVal);
//                            ListView_SetItemText( hList,i,1,cvalor);
                    ListView_SetItemText( hList, i, 2, "OPC_QUALITY_GOOD");
                    ListView_SetItemText( hList, i, 3, buf);
                }
            }
            /*
            //@@@@@@@@@@@@@@@@@@@@@@@@@?????????????????????????
                                var.vt = VT_BSTR;
                                sprintf (buf, "Texto=%d", rand());
                                len = strlen (buf);
                                for (j=0; j<len+1; j++)
                                    wide_str[j] = buf[j];
                                var.bstrVal = SysAllocString (wide_str);
                                VariantCopy (&(ItensOPC[i].Value), &var);
            //                    ItensOPC[i].Handle = CreateTag(ItensOPC[i].Name, var, OPC_QUALITY_NOT_CONNECTED, TRUE );
                                UpdateTagWithTimeStamp (ItensOPC[i].Handle, var, OPC_QUALITY_GOOD,t_agora);
            //@@@@@@@@@@@@@@@@@@@@@@@@@?????????????????????????
            */
            break;
        } //switch(ItensOPC[i].Value.vt)
        VariantClear(&var);


    }//for (i=0; i<8; i++)

    EndUpdateTags ();

    sprintf(buf, "A hora do sistema é : %02d:%02d\n", st.wHour, st.wMinute);



}


// InitListViewColumns: Adds columns to a list-view control.
// hWndListView:        Handle to the list-view control.
// Returns TRUE if successful, and FALSE otherwise.
BOOL InitListViewColumns(HWND hWndListView)
{
    //WCHAR szText[256];     // Temporary buffer.
    LVCOLUMN lvc;
    int iCol;

    // Initialize the LVCOLUMN structure.
    // The mask specifies that the format, width, text,
    // and subitem members of the structure are valid.
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    // Add the columns.
    for (iCol = 0; iCol < C_COLUMNS; iCol++)
    {
        memset(buf, '\0', sizeof(buf));
        sprintf(buf, "Coluna %d", iCol);
        lvc.iSubItem = iCol;
        lvc.pszText = buf;
        lvc.cx = 100;               // Width of column in pixels.

        if ( iCol < 2 )
            lvc.fmt = LVCFMT_LEFT;  // Left-aligned column.
        else
            lvc.fmt = LVCFMT_RIGHT; // Right-aligned column.

        // Load the names of the column headings from the string resources.
        LoadString(hInst,
//                  IDS_FIRSTCOLUMN + iCol,
                   1 + iCol,
                   buf,
                   sizeof(buf) / sizeof(buf[0]));

        // Insert the columns into the list view.
        if (ListView_InsertColumn(hWndListView, iCol, &lvc) == -1)
            return FALSE;
    }

    return TRUE;
}
// InsertListViewItems: Inserts items into a list view.
// hWndListView:        Handle to the list-view control.
// cItems:              Number of items to insert.
// Returns TRUE if successful, and FALSE otherwise.
BOOL InsertListViewItems(HWND hWndListView, int cItems)
{
    LVITEM lvI;

    // Initialize LVITEM members that are common to all items.
    lvI.pszText   = LPSTR_TEXTCALLBACK; // Sends an LVN_GETDISPINFO message.
    lvI.mask      = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvI.stateMask = 0;
    lvI.iSubItem  = 0;
    lvI.state     = 0;

    // Initialize LVITEM members that are different for each item.
    for (int index = 0; index < cItems; index++)
    {
        lvI.iItem  = index;
        lvI.iImage = index;

        // Insert items into the list.
        if (ListView_InsertItem(hWndListView, &lvI) == -1)
            return FALSE;
    }

    return TRUE;
}



/****************************************************************************
*
*    FUNCTION: CreateListView(HWND)
*
*    PURPOSE:  Creates the list view window and initializes it
*
****************************************************************************/
HWND CreateListView (HWND hWndParent)
{
    HWND hWndList;      // Handle to the list view window
    RECT rcl;           // Rectangle for setting the size of the window
    //HICON hIcon;        // Handle to an icon
    int index;          // Index used in for loops
    //HIMAGELIST hSmall, hLarge; // Handles to image lists for large and small icons
    LV_COLUMN lvC;      // List View Column structure
    char szText[MAX_PATH];    // Place to store some text
    LV_ITEM lvI;        // List view item structure
    int iSubItem;       // Index for inserting sub items

    // Ensure that the common control DLL is loaded.
    InitCommonControls();

    // Get the size and position of the parent window
    GetClientRect(hWndParent, &rcl);

    /* vou crriar no resource


        // Create the list view window that starts out in report view
        // and allows label editing.
        hWndList = CreateWindowEx( 0L,
            WC_LISTVIEW,                // list view class
            "",                         // no default text
            WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT |
                LVS_EDITLABELS | WS_EX_CLIENTEDGE,
            7, 25,
            410, 250,
            hWndParent,
            (HMENU) ID_LISTVIEW,
            hInst,
            NULL );
    */

// criada no arquivo resource
    hWndList = hList;

    if (hWndList == NULL )
        return NULL;


    // initialize the list view window
    // First, initialize the image lists we will need
    // create an image list for the small and large icons
    // FALSE specifies large icons - TRUE specifies small

    /*  hSmall = ImageList_Create( BITMAP_WIDTH, BITMAP_HEIGHT,
            FALSE, 3, 0 );

        hLarge = ImageList_Create( LG_BITMAP_WIDTH, LG_BITMAP_HEIGHT,FALSE, 3, 0 );

        // load the icons and add them to the image lists
        for (index = REDMOND; index <= SEATTLE ; index++)
        {
            hIcon = LoadIcon ( hInst, MAKEINTRESOURCE(index));
            // there are 3 of each type of icon here, so add 3 at a time.
            for (iSubItem = 0; iSubItem < 3; iSubItem++)
            {
                if ((ImageList_AddIcon(hSmall, hIcon) == -1) ||
                    (ImageList_AddIcon(hLarge, hIcon) == -1))
                    return NULL;
            }
        }

        // Make sure that all of the icons were added
        if (ImageList_GetImageCount(hSmall) < 3)
            return FALSE;

        // Make sure that all of the icons were added
        if (ImageList_GetImageCount(hLarge) < 3)
            return FALSE;

        // Associate the image list with the list view
        ListView_SetImageList(hWndList, hSmall, LVSIL_SMALL);

        ListView_SetImageList(hWndList, hLarge, LVSIL_NORMAL);
    */
    // Now initialize the columns we will need
    // Initialize the LV_COLUMN structure
    // the mask specifies that the .fmt, .ex, width, and .subitem members
    // of the structure are valid,
    lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvC.fmt = LVCFMT_LEFT;  // left align the column
    lvC.cx = 75;            // width of the column, in pixels


    // Add the columns.
    for (index = 0; index <= NUM_COLUMNS; index++)
    {
        lvC.iSubItem = index;
        lvC.pszText = szText;
        LoadString( hInst,
//                  IDS_ADDRESS + index,
                    index,
                    szText,
                    sizeof(szText));
        if (ListView_InsertColumn(hWndList, index, &lvC) == -1)
            return NULL;
// Titulo do cabecalho da coluna
        memset(szText, '\0', sizeof(szText));
//      sprintf(szText,"Item %d", index);
        sprintf(szText, "%s", titulo_col[index]);
        lvC.mask = LVCF_TEXT;
        lvC.pszText = szText;
//Cria a coluna
        if (ListView_SetColumn(hWndList, index, &lvC) == -1)
            return NULL;;
        lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvC.fmt = LVCFMT_LEFT;  // left align the column
        lvC.cx = 75;            // width of the column, in pixels
    }

    // Finally, let's add the actual items to the control
    // Fill in the LV_ITEM structure for each of the items to add
    // to the list.
    // The mask specifies the the .pszText, .iImage, .lParam and .state
    // members of the LV_ITEM structure are valid.
    lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
    lvI.state = 0;      //
    lvI.stateMask = 0;  //

    for (index = 0; index < NUM_ITEMS; index++)
    {
        lvI.iItem = index;
//Define que eh primeira coluna
        lvI.iSubItem = 0;
        // The parent window is responsible for storing the text. The List view
        // window will send a LVN_GETDISPINFO when it needs the text to display/
//      lvI.pszText = LPSTR_TEXTCALLBACK;
// conteudo da primeira coluna, todas as linhas irao receber
        memset(szText, '\0', sizeof(szText));
        sprintf(szText, "SubItem A %d", index);
        lvI.pszText = szText;
        lvI.cchTextMax = MAX_ITEMLEN;
//      lvI.iImage = index;
//      lvI.lParam = (LPARAM)&rgHouseInfo[index];

        if (ListView_InsertItem(hWndList, &lvI) == -1)
            return NULL;

//      lvI.iImage = index;


        for (iSubItem = 1; iSubItem <= NUM_COLUMNS; iSubItem++)
        {
//Conteudo das demais colunas
            memset(szText, '\0', sizeof(szText));
            sprintf(szText, "SubItem %d , %d", index, iSubItem);
            ListView_SetItemText( hWndList,
                                  index,
                                  iSubItem,
//              LPSTR_TEXTCALLBACK);
                                  szText);
        }
    }
    return (hWndList);
}






BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LPCSTR  SvrName, SvrDescr, HelpPath;
    int i = 0;
    //char lpBuffer1[128];
    DWORD n_lidos;
    //char   lpBuffer[32] ;              // lpBuffer should be  char or byte array, otherwise write wil fail
    //DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port    DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port
    //DWORD  dNoOfBytesWritten;
    int pos;
    HWND hwndrasc;
    //int lbCanal;
    //int lbValor;
    int tamanho;
    ifstream arq_cfg;

    switch (uMsg)
    {
    case WM_INITDIALOG:
    {

        /*
          Inicia o servidor OPC
        */
        MessageBox(NULL, "Comecar", "Inicio",
                   MB_ICONEXCLAMATION | MB_OK);

        if (InitWTOPCsvr( (BYTE *)&CLSID_UFMGWT, 250 ))
        {
            MessageBox(NULL, "Iniciado OPC", "Iniciar DCOM",
                       MB_ICONEXCLAMATION | MB_OK);
        }
        else
        {
            MessageBox(NULL, "Não Iniciado OPC", "Iniciar DCOM",
                       MB_ICONEXCLAMATION | MB_OK);
        }

//=============================================================================================
// Conecta ao arduino
//=============================================================================================
        memset(portName, '\0', sizeof(portName));
        strcpy(portName, "\\\\.\\COM");
        char c_temporario[32];
        memset(c_temporario, '\0', sizeof(c_temporario));
        arq_cfg.open ("porta.cfg");
        arq_cfg >> c_temporario;
        arq_cfg.close();
        strcat(portName, c_temporario);
        arduino = new SerialPort(portName);

        //Checking if arduino is connected or not
        if (arduino->isConnected()) {
            printf("Connection established at port %s \n", portName);
        }

        /*
        inclui as opcoes de canais discretos de escrita

        */
        // Add items to list.
        hwndrasc = GetDlgItem(hwndDlg, IDC_LST_SD);

        pos = (int)SendMessage(hwndrasc, LB_ADDSTRING, 0,
                               (LPARAM) TEXT("6"));
        SendMessage(hwndrasc, LB_SETITEMDATA, pos, (LPARAM) 0);
        pos = (int)SendMessage(hwndrasc, LB_ADDSTRING, 0,
                               (LPARAM) TEXT("7"));
        SendMessage(hwndrasc, LB_SETITEMDATA, pos, (LPARAM) 1);
        pos = (int)SendMessage(hwndrasc, LB_ADDSTRING, 0,
                               (LPARAM) TEXT("8"));
        SendMessage(hwndrasc, LB_SETITEMDATA, pos, (LPARAM) 2);


        /*
        inclui as opcoes de canais analogicos de escrita

        */
        // Add items to list.
        hwndrasc = GetDlgItem(hwndDlg, IDC_LST_SA);

        pos = (int)SendMessage(hwndrasc, LB_ADDSTRING, 0,
                               (LPARAM) TEXT("10"));
        SendMessage(hwndrasc, LB_SETITEMDATA, pos, (LPARAM) 0);
        pos = (int)SendMessage(hwndrasc, LB_ADDSTRING, 0,
                               (LPARAM) TEXT("11"));
        SendMessage(hwndrasc, LB_SETITEMDATA, pos, (LPARAM) 1);
        /*
        Cria os botoes no dialogo
        */
        /*
        Mudei a criacao para o ResEdit
        */
        /*
                    TextBox = CreateWindow("EDIT",
                                           "",
                                           WS_BORDER | WS_CHILD | WS_VISIBLE,
                                           10, 10, 390, 150,
                                           hwndDlg, (HMENU) 1, NULL, NULL);
                    SendButton = CreateWindow("BUTTON",
                                 "Registrar",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 20, 160, 80, 20,
                                 hwndDlg, (HMENU) 2, NULL, NULL);

                    SendButton = CreateWindow("BUTTON",
                                 "Des-registrar",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 110, 160, 90, 20,
                                 hwndDlg, (HMENU) 3, NULL, NULL);

                    SendButton = CreateWindow("BUTTON",
                                 "Rodar+Item",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 210, 160, 90, 20,
                                 hwndDlg, (HMENU) 4, NULL, NULL);

        */

        /*
        botoes para registrar e desregistrar
        */

        hwnd_but_registrar =  GetDlgItem(hwndDlg, IDC_BUT_REGISTRAR);
        hwnd_but_desregistrar =  GetDlgItem(hwndDlg, IDC_BUT_DESREGISTRAR);


        /*
        Definição dos itens OPC
        */


// Pseudo entradas
        strcpy(ItensOPC[0].Name, c_sinais[0]);
        ItensOPC[0].Value.vt = VT_BOOL;
        ItensOPC[0].b_eh_escrita = false;
        strcpy(ItensOPC[1].Name, c_sinais[1]);
        ItensOPC[1].b_eh_escrita = false;
        ItensOPC[1].Value.vt = VT_BOOL;
        strcpy(ItensOPC[2].Name, c_sinais[2]);
        ItensOPC[2].b_eh_escrita = false;
        ItensOPC[2].Value.vt = VT_BOOL;
        strcpy(ItensOPC[3].Name, c_sinais[3]);
        ItensOPC[3].b_eh_escrita = false;
        ItensOPC[3].Value.vt = VT_BOOL;
// Pseudo saidas
        strcpy(ItensOPC[4].Name, c_sinais[4]);
        ItensOPC[4].b_eh_escrita = true;
        ItensOPC[4].Value.vt = VT_BOOL;
        strcpy(ItensOPC[5].Name, c_sinais[5]);
        ItensOPC[5].b_eh_escrita = true;
        ItensOPC[5].Value.vt = VT_BOOL;
        strcpy(ItensOPC[6].Name, c_sinais[6]);
        ItensOPC[6].b_eh_escrita = true;
        ItensOPC[6].Value.vt = VT_BOOL;
// Entarda analogica
        strcpy(ItensOPC[7].Name, c_sinais[7]);
        ItensOPC[7].b_eh_escrita = false;
        ItensOPC[7].Value.vt = VT_I4;
        strcpy(ItensOPC[8].Name, c_sinais[8]);
        ItensOPC[8].b_eh_escrita = false;
        ItensOPC[8].Value.vt =  VT_R8;
        strcpy(ItensOPC[9].Name, c_sinais[9]);
        ItensOPC[9].b_eh_escrita = false;
        ItensOPC[9].Value.vt =  VT_R8;
// Saida analogica
        strcpy(ItensOPC[10].Name, c_sinais[10]);
        ItensOPC[10].b_eh_escrita = true;
        ItensOPC[10].Value.vt =  VT_R4;
        strcpy(ItensOPC[11].Name, c_sinais[11]);
        ItensOPC[11].b_eh_escrita = true;
        ItensOPC[11].Value.vt =  VT_R4;
        Criar_Itens();
        /*
        Controle para mostrar itens na tela
        */
        hList = GetDlgItem(hwndDlg, IDC_LST_ITENS);

// Sao elementos de uma matriz indexados a partir de zero, na forma linha, coluna
        hList = CreateListView( hwndDlg );

        for (i = 0; i < NUM_ITEMS; i++)
        {
            ListView_SetItemText( hList, i, 0, ItensOPC[i].Name);
            ListView_SetItemText( hList, i, 6, c_canais[i]);
            switch (ItensOPC[i].Value.vt)
            {
            case VT_BOOL:
                ListView_SetItemText( hList, i, 4, "VT_BOOL");
                break;
            case VT_R4:
                ListView_SetItemText( hList, i, 4, "VT_R4");
                break;
            case VT_R8:
                ListView_SetItemText( hList, i, 4, "VT_R8");
                break;
            case VT_I4:
                ListView_SetItemText( hList, i, 4, "VT_I4");
                break;
            case VT_BSTR:
                ListView_SetItemText( hList, i, 4, "VT_BSTR");
                break;
            } //switch(ItensOPC[i].Value.vt)
            if (ItensOPC[i].b_eh_escrita)
            {
                ListView_SetItemText( hList, i, 5, "Esc/Leit");
            }
            else
            {
                ListView_SetItemText( hList, i, 5, "Leitura");
            }
        } //for(i=0;i<NUM_ITEMS;i++)


//
// controle das tarefas de tempo quase-real
//
        InitializeCriticalSection(&m_CriticalSection);

        /*
              cria timer para atualizacoes
        */

        SetTimer(hwndDlg, IDT_TIMER1, 3000, NULL );
        /*
                    Habilita o tratamento de escrita pelo usuario
        */
        EnableWriteNotification (WriteNotifyCallback, TRUE);

        /*            TextField = CreateWindow("EDIT",
                                             "",
                                             WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
                                             10, 190, 380, 290,
                                             hwndDlg, (HMENU) 3, NULL, NULL); */

        break;


    }
    return TRUE;

    case WM_CLOSE:
    {
        KillTimer(hwndDlg, IDT_TIMER1);
        RequestDisconnect();
        Sleep(2000);
        DeleteCriticalSection(&m_CriticalSection);

        EndDialog(hwndDlg, 0);
    }
    return TRUE;


    case WM_TIMER:

        switch (wParam)
        {
        case IDT_TIMER1:
//Entrando na tarefa que nao deve ser interrompida

            EnterCriticalSection( &m_CriticalSection );
            b_escreveu = false;
            memset(c_mensagem, '\0', sizeof(c_mensagem));
            strcpy(c_mensagem, c_ler_ard);
            exampleWriteData(BLINKING_DELAY);
            b_solicitou = true;
            if (b_solicitou)
                i_wdgt++;

            if (b_escreveu)
            {
                memset(incomingData, sizeof(incomingData), '\0');
                n_lidos = 0;
                exampleReceiveData(&n_lidos);
                tamanho = n_lidos;
                if (tamanho > 0)
                {
                    Atualiza_Valores(tamanho);
                    Atualiza_VQT_Itens();
                    i_wdgt = 0;
                    b_solicitou = false;
                }
                /*
                // soh usar para desenvolvimento
                                      for(tamanho=0;tamanho<4;tamanho++)
                                      {
                                          printf("Entrada discreta %d : %d\n", tamanho, ent_disc[tamanho]);
                                      }
                                      for(tamanho=0;tamanho<3;tamanho++)
                                      {
                                          printf("Saida discreta %d : %d\n", tamanho, sai_disc[tamanho]);
                                      }
                                      for(tamanho=0;tamanho<1;tamanho++)
                                      {
                                          printf("Entrada analogica %d : %d\n", tamanho, ent_analog[tamanho]);
                                      }
                                      for(tamanho=0;tamanho<1;tamanho++)
                                      {
                                          printf("Saida analogica %d : %d\n", tamanho, sai_analog[tamanho]);
                                      }

                */
            } //if(b_escreveu)
            if (i_wdgt > ID_WATCHDOG_TIMER_COM)
            {
                ListView_SetItemText( hList, 0, 3, "Nao OK");
                ListView_SetItemText( hList, 1, 3, "Nao OK");
                ListView_SetItemText( hList, 2, 3, "Nao OK");
                ListView_SetItemText( hList, 3, 3, "Nao OK");
                ListView_SetItemText( hList, 4, 3, "Nao OK");
                ListView_SetItemText( hList, 5, 3, "Nao OK");
                ListView_SetItemText( hList, 6, 3, "Nao OK");
                ListView_SetItemText( hList, 7, 3, "Nao OK");
                ListView_SetItemText( hList, 8, 3, "Nao OK");
                ListView_SetItemText( hList, 9, 3, "Nao OK");
                ListView_SetItemText( hList, 10, 3, "Nao OK");
                ListView_SetItemText( hList, 11, 3, "Nao OK");


            } //if(b_escreveu) else
            /*
            Saindo da secao critica
            */
            LeaveCriticalSection( &m_CriticalSection );
            strcpy(buf, "Teste de escrita na tela");
//                  SetWindowTextA(TextBox, &buf[0]);
            HWND htexto_tempo;
            htexto_tempo = GetDlgItem( hwndDlg, IDC_ULTIMARODADA);
            //int len = GetWindowTextLengthA(htexto_tempo);
            SetWindowTextA(htexto_tempo, &carimbo_tempo[0]);
            /*                 if(len > 0)
                             {
                                   int i;
                                   //buf = (char*)GlobalAlloc(GPTR, len + 1);
                                   // GlobalFree((HANDLE)buf);
                                   GetWindowText(TextBox, &buf[0], sizeof(buf));
                                   strcat(buf," li e escrevi");
                                   SetWindowTextA(TextBox, &buf[0]);
            //                        GetDlgItemText(hwnd, IDC_TEXT, buf, len + 1);
                                   //... do stuff with text ...
                             }*/
            break;
        }
        return TRUE;



    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_BUT_REGISTRAR:
            MessageBox(NULL, "Registrar", "Registro do servidor",
                       MB_ICONEXCLAMATION | MB_OK);


            //int   i;
            // get path to executable by parsing the help path
            char dir[255];
            GetCurrentDirectory(254, dir);
            strcat(dir, "\\ServOPCUFMGAluno2.exe");
            HelpPath = dir;
            // get path to executable by parsing the help path
            // contained in CWinApp
            //HelpPath = AfxGetApp()->m_pszHelpFilePath;
            //i = HelpPath.ReverseFind('\\');
            //HelpPath = HelpPath.Left(i+1);
            //HelpPath += "WtSvrTst2.exe";

            SvrName = "ServOPCUFMGAluno2";
            SvrDescr = "Servidor OPC da UFMG para teste com Arduino";

            if (UpdateRegistry ((BYTE *)&CLSID_UFMGWT, SvrName, SvrDescr, HelpPath))
            {
                MessageBox(NULL, "Registro OPC", "Registrado",
                           MB_ICONEXCLAMATION | MB_OK);
            }
            else
            {
                MessageBox(NULL, "Registro OPC", "Não Registrado",
                           MB_ICONEXCLAMATION | MB_OK);
            }



            break;

        case IDC_BUT_DESREGISTRAR:
            MessageBox(NULL, "Des-Registrar", "Remover servidor do registro",
                       MB_ICONEXCLAMATION | MB_OK);

            SvrName = "ServOPCUFMGAluno2";
            if (UnregisterServer ((BYTE *)&CLSID_UFMGWT, SvrName))
            {
                MessageBox(NULL, "Des-Registro servidor OPC", "Desregistrado",
                           MB_ICONEXCLAMATION | MB_OK);
            }
            else
            {
                MessageBox(NULL, "Des-Registro servidor OPC", "Não desregistrado",
                           MB_ICONEXCLAMATION | MB_OK);
            }
            break;



        case 4:
            MessageBox(NULL, "Criar itens", "Criar itens do servidor",
                       MB_ICONEXCLAMATION | MB_OK);
            Criar_Itens();


            break;



        }
    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
