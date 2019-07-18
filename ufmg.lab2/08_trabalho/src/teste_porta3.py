import RPi.GPIO as GPIO
import log

porta = 6
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(porta, GPIO.OUT)
GPIO.output(porta, GPIO.LOW)
log.logar("Porta " + str(porta) + ": " + str(GPIO.LOW))
#GPIO.cleanup()

