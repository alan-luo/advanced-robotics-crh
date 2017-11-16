# Testing Parts

Our parts finally arrived! Before putting them all together, my first task was to test all of these parts and make sure that I had working code for each one individually.

**Bluetooth Shield**

First, I installed the bluetooth shield directly onto the Arduino, and ran the `cmd_bleuart` example from Adafruit's bluefruit library. 

- Working screencast: `/final_project/img/bluetooth.mov`
- Working code: `/final_project/code/test_bluetooth/`

**DHT-22 Humidity Sensor**

For the Humidity sensor, I tried breathing on it to increase the temperature and humidity. This would show that it works. It worked quite well.

![working dht](../../final_project/img/humidity_test.jpg)

- Video of me breathing on a sensor: `/final_project/img/humidity_breathing.mp4`
- Working code: `/final_project/code/test_temp/`

**Light Sensor**

I tested the light sensor by placing my finger on it. It worked well.

- Working video `/final_project/img/lux_test.mp4`
- Working code: `/final_project/code/test_light/`

**Pump**

The pump drew too much power from the Arduino and didn't work. However, it worked fine when wired to an old VEX battery.

- Working video `/final_project/img/pump_test.mp4`