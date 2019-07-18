import RPi.GPIO as GPIO
import log
import time

PORTA_EXTERNA = 6
PORTA_INTERNA = 6

def abrirPorta(porta):
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(porta, GPIO.OUT)
    GPIO.output(porta, GPIO.HIGH)
    log.logar("Porta " + str(porta) + ": " + str(GPIO.HIGH))
    time.sleep(5)
    GPIO.output(porta, GPIO.LOW)
    log.logar("Porta " + str(porta) + ": " + str(GPIO.LOW))
    GPIO.cleanup()

def abrirPortaExterna():
    log.logar("Abrir porta externa")
    abrirPorta(PORTA_EXTERNA)

def abrirPortaInterna():
    log.logar("Abrir porta interna")
    abrirPorta(PORTA_INTERNA)