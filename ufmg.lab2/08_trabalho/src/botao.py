import log
import RPi.GPIO as GPIO
import time

BOTAO_INTERNO = 26
BOTAO_EXTERNO = 27

def aguardarBotao(porta):
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(porta, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    c = 0
    while True:    
        if GPIO.input(26) == GPIO.HIGH:
            c = c + 1
            print("Button was pushed! " + str(c))
        time.sleep(1)    

def aguardarBotaoInterno():
    log.logar("Aguardar botao interno")
    aguardarBotao(BOTAO_INTERNO)

def aguardarBotaoExterno():
    log.logar("Aguardar botao externo")
    aguardarBotao(BOTAO_EXTERNO)