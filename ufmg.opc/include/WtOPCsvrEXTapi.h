#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/////////////////////////////////////////////////////////////////
//
//		Security api
//
//
///////////////////////////////////////////////////////////////////

#define ACCESSLEVELNONE	0x00000000
#define	ACCESSLEVEL1	0x00010000
#define	ACCESSLEVEL2	0x00020000
#define	ACCESSLEVEL3	0x00040000
#define	ACCESSLEVEL4	0x00080000
#define	ACCESSLEVEL5	0x00100000
#define	ACCESSLEVEL6	0x00200000
#define	ACCESSLEVEL7	0x00400000
#define	ACCESSLEVEL8	0x00800000
#define	ACCESSLEVEL9	0x01000000
#define	ACCESSLEVEL10	0x02000000
#define	ACCESSLEVEL11	0x04000000
#define	ACCESSLEVEL12	0x08000000
#define	ACCESSLEVEL13	0x10000000
#define	ACCESSLEVEL14	0x20000000
#define	ACCESSLEVEL15	0x40000000
#define	ACCESSLEVEL16	0x80000000



/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Extended Callback Definitions
//
//					EnableWriteNotification2 (WRITENOTIFYPROC2 lpCallback);
//		
//
//	WRITENOTIFYPROC2
//		Signals the Application that an OPC Client has requested a write to a 
//		tag.  Identical to WRITENOTIFYPROC with extra parameter to identify
//		the name of the user requesting the write.
//
#ifdef STRICT
typedef VOID (CALLBACK* WRITENOTIFYPROC2)(HANDLE, VARIANT*, DWORD*, CHAR*);
typedef HRESULT (CALLBACK *AEACKCONDITIONPROC)(DWORD, WORD*, WORD*, WORD**, WORD**, FILETIME*, DWORD*, HRESULT**);
#else /* !STRICT */
typedef FARPROC WRITENOTIFYPROC2;
typedef FARPROC AEACKCONDITIONPROC;
#endif

_declspec(dllexport) BOOL WINAPI EnableWriteNotification2 (WRITENOTIFYPROC2 lpCallback, BOOL ConvertToNativeType);

_declspec(dllexport) BOOL WINAPI EnableAEAckConditionCallback (AEACKCONDITIONPROC lpCallback);

_declspec(dllexport) BOOL WINAPI WTUpdateRegistry (BYTE *pCLSID_Svr, LPCSTR Name, LPCSTR Descr, LPCSTR ExePath);

_declspec(dllexport) BOOL WINAPI EnableNTSecurity (BOOL EnableSecurity, DWORD MinImpersonationLevel);

_declspec(dllexport) HRESULT WINAPI DefineNTUser (LPCSTR GroupName, LPCSTR UserName, DWORD AccessLevel);

_declspec(dllexport) HANDLE WINAPI CreateSecureTag (LPCSTR Name, VARIANT Value, WORD InitialQuality, DWORD ReadAccessLevel, DWORD WriteAccessLevel);

#ifdef __cplusplus
}
#endif
