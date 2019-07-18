import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(13, GPIO.OUT)

f = False
while True:    
    if GPIO.input(26) == GPIO.HIGH:
        print("pressed")
        f = not f
        GPIO.output(13, f)
    time.sleep(1)
    
            
