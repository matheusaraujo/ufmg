import RPi.GPIO as GPIO
import log

porta = 6
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(porta, GPIO.OUT)
GPIO.output(porta, GPIO.HIGH)
log.logar("Porta " + str(porta) + ": " + str(GPIO.HIGH))
#GPIO.cleanup()
