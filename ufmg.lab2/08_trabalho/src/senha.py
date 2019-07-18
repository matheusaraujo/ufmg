import log
import random

def obterSenhaExterna():
    senha = 1234
    log.logar("Obter senha externa - " + str(senha))
    return senha

def gerarSenhaInterna():
    senha = random.randint(1000, 9999) 
    log.logar("Gerar senha interna - " + str(senha))
    return senha
