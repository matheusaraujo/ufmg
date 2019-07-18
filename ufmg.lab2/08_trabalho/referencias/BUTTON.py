import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

c = 0
while True:    
    if GPIO.input(26) == GPIO.HIGH:
        c = c + 1
        print("Button was pushed! " + str(c))
    time.sleep(1)    
            
