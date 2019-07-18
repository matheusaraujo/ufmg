import log
import teclado2
    
def lerSenha(senhaValida):
    while(True):
        log.logar("Ler Senha - " + str(senhaValida))
        senha_acesso = teclado2.ler()
        log.logar(senha_acesso)
        if senha_acesso.isdigit() and int(senha_acesso) == senhaValida:
            break  