import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(26,GPIO.OUT)

while True:
    print "LED on"
    GPIO.output(26,GPIO.HIGH)
    time.sleep(5)
    print "LED off"
    GPIO.output(26,GPIO.LOW)
    time.sleep(5)
