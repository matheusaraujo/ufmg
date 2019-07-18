import RPi.GPIO as GPIO
import time
import smtplib

def send_mail():
    server = smtplib.SMTP("smtps.bol.com.br", 587)
    server.starttls()
    server.login("dtirhcoding@bol.com.br", "Dti@1406")

    message = "lab2"
    server.sendmail("dtirhcoding@bol.com.br", "matheus.saraujo@gmail.com", message)
    print("mail sent")

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(13, GPIO.OUT)

f = False
while True:    
    if GPIO.input(26) == GPIO.HIGH:
        if not f:
            print("pressed")
        send_mail()
        f = not f
        GPIO.output(13, f)
    time.sleep(1)
    
            
