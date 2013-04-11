============
Redis Beacon
============

The Consumer
============

The consumer will listen to redis beacon channels and send a event on
the Arduino serial.


The Arduino
===========

The arduino will read the serial and process event's that arrive.
You can plug the led on O0, O1, O2, O3, O4, O5 (PIN 11, 10, 9, 6, 5, 3)

Then you use the beacon library in your software to publish on the channel.
