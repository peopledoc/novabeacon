# -*- coding: utf-8 -*-

from redis import StrictRedis
import serial
import time
import sys
import signal

from redis_settings import HOST, PORT, DB, PUBSUB_CHANNELS

redis = StrictRedis(host=HOST, port=PORT, db=DB)

def send_event(ser, led, total, on, off):
    """Write the data to the API.
    StartByte LedNumber TotalTime (seconds) OnTime(hundredth of second) OffTime(hundredth of second)
    """
    # Start byte
    ser.write('~')
    # Led id
    ser.write(chr(led))
    # Total time
    ser.write(chr(total))
    # On Time
    ser.write(chr(on))
    # Off Time
    ser.write(chr(off))    


def main():
    ser = serial.Serial('/dev/ttyACM0', 9600)
    pubsub = redis.pubsub()
    pubsub.subscribe(PUBSUB_CHANNELS)
    time.sleep(3)  # Time to let the arduino start.

    print "Run"
    try:
        ser.open()
    except:
        print "Serial already open."

    if ser.isOpen():
        print("Listening on: ", ser.portstr)
    else:
        sys.stderr.write('Failed to open serial on : %s\n' % ser.portstr)
        sys.exit(1)

    def handler(signum, frame):
        print 'Goodbye'
        ser.close()
        sys.exit(0)

    signal.signal(signal.SIGTERM, handler)
    signal.signal(signal.SIGINT, handler)

    for item in pubsub.listen():
        if item['type'] == 'message':
            led = PUBSUB_CHANNELS.index(item['channel'])
            send_event(ser, led, 11, 11, 0)
            # time.sleep(2.7)

if __name__ == '__main__':
    main()
