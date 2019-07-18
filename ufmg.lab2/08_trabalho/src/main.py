import botao
import cofre
import email2
import log
import porta
import senha
import teclado

senhaGerada = senha.gerarSenhaInterna()

def main():
    estado = 1
    while(True):
        log.logar("--- Estado: "  + str(estado))
        if estado == 1:
            estado1()
            estado = 2        
        elif estado == 2:
            estado2()        
            estado = 3  
        elif estado == 3:
            estado3()        
            estado = 4
        elif estado == 4:
            estado4()        
            estado = 1
        else:
            print("Estado Invalido")
            estado = 1


def estado1():
    teclado.lerSenha(senha.obterSenhaExterna())
    porta.abrirPortaExterna()
    senhaGerada = senha.gerarSenhaInterna()
    email2.enviarEmail(senhaGerada)

def estado2():
    teclado.lerSenha(senhaGerada)
    porta.abrirPortaInterna()
    cofre.acionarIluminacao()
    cofre.acionarVentilacao()

def estado3():
    botao.aguardarBotaoInterno()
    porta.abrirPortaInterna()
    cofre.desligarIluminacao()
    cofre.desligarVentilacao()

def estado4():
    botao.aguardarBotaoExterno()
    porta.abrirPortaExterna()

main()