import time
import RPi.GPIO as GPIO

print('time: {}'.format(time.time()))

GPIO.setmode(GPIO.BCM)

# GPIO 23 & 17 set up as interrupts
GPIO.setup(17,GPIO.IN,pull_up_down=GPIO.PUD_UP)


t17 = time.time()


def callback_gpio17(channel):
    global t17
    print('interrupt on GPIO 17 time diff: {} mS'.format( (time.time()-t17)*1000))
    t17 = time.time()

GPIO.add_event_detect(17,GPIO.BOTH,callback=callback_gpio17,bouncetime=1)

try:
    while(True):
        pass
        #print('...')
        #time.sleep(0.5)
except KeyboardInterrupt:
    GPIO.cleanup()
GPIO.cleanup()
