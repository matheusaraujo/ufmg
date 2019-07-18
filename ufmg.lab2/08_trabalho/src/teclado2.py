import RPi.GPIO as GPIO
import time

MATRIX = [[1,2,3,"A"],
    [4,5,6,"B"],
    [7,8,9,"C"],
    ["*",0,"#","D"]
]
    
ROW = [4,17,27,22]
COL = [18,23,24,25]

def ler():

    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    
    for j in range(4):
        GPIO.setup(COL[j], GPIO.OUT)
        GPIO.output(COL[j], 1)
        GPIO.setup(ROW[j], GPIO.IN, pull_up_down=GPIO.PUD_UP)
        
    kod="";
    try:
        while(True):
            for j in range(4):
                GPIO.output(COL[j],0)
                for i in range(4):
                    if GPIO.input(ROW[i]) == 0:
                        time.sleep(0.3)
                        print "Digitou: " + str(MATRIX[i][j])
                        kod+=str(MATRIX[i][j])
                        while(GPIO.input(ROW[i]) == 0):
                            pass

                GPIO.output(COL[j],1)
            if(len(kod)==4):
                print kod
                return kod
                
    except KeyboardInterrupt:
        GPIO.cleanup()