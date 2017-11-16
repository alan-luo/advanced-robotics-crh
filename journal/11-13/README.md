# Soldering

I soldered all the components onto the Bluetooth shield, using the exact same circuit from before.

![all soldered](../../final_project/img/assembly_final.jpg)

After soldering, I still had to test each component to make sure my joints were good. I had a problem with the DHT sensor:

![all soldered](../../final_project/img/humidity_fail.jpg)

I tried to test each joint with a multimeter, but the some of the connections were too small. Instead, I set up a basic LED circuit with two jumpers, and essentially used that circuit as a multimeter. When connected to the DHT joints, the LED didn't light up, indicating a soldering issue. After reheating the joints and resoldering, it worked fine.

With everything in place and each component working, I could then test interfacing it with the Bluetooth sensor. This worked. The following photo shows temperature, humidity, and lux being sent to the computer wirelessly from the circuit.

![working bt](../../final_project/img/assembly_bluetooth.jpg)

- Working code: `/final_project/code/test_all/`