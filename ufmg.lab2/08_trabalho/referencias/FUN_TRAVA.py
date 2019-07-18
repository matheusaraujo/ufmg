import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(13, GPIO.OUT)

while True:    
    if GPIO.input(26) == GPIO.HIGH:
        print("pressed")        
        GPIO.output(13, 1)
        time.sleep(5)
        GPIO.output(13, 0)
    time.sleep(1)
    
            
