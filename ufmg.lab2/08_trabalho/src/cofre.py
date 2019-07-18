import log
import RPi.GPIO as GPIO
import time

ILUMINACAO = 26
VENTILACAO = 27

def escreverSaida(porta, sinal):
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(porta, sinal)

def acionarIluminacao():
    log.logar("Acionar iluminacao")
    escreverSaida(ILUMINACAO, GPIO.HIGH)

def acionarVentilacao():
    log.logar("Acionar ventilacao")
    escreverSaida(VENTILACAO, GPIO.HIGH)

def desligarIluminacao():
    log.logar("Desligar iluminacao")
    escreverSaida(ILUMINACAO, GPIO.LOW)

def desligarVentilacao():
    log.logar("Desligar ventilacao")
    escreverSaida(VENTILACAO, GPIO.LOW)