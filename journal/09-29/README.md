# Sept 29: In-class Assessment

In class on Sept 28, I was given an assignment to complete within the class block that acted as a form of assessment. The assignment:

- Use 8 LEDs
- Have them turn on in sequence, 5 seconds apart
- As the last one turns on, activate a buzzer for 5 seconds
- Disable the buzzer and turn everything off, then repeat

To complete this assignment, I chose to use the shift register because it makes programming a large number of LEDs very easy.

## Program Design

Since every action of the program runs on regular intervals, I decided to run the code off of an animation loop. In an animation loop, every state change is determined by the position in the loop rather than be strict timing. For instance, if we weren't to use an animation loop, we might do something like:

```
void loop() {
	for(int i=0; i<8; i++) {
		// turn on an LED
		delay(5000);
	}
}
```

With an animation loop, we'd do:

```
int framecount = 0;
void loop() {
	turnOnLeds(framecount % 8);

	delay(5000);
	framecount++;
}
```

Here, we keep a running count of how many frames have passed. The advantage here is that each run of `loop` on the Arduino only requires a single `delay` call. Once we add the buzzer, this will make changing the duration as simple as changing a single number, whereas without an animation loop, we might have to change the `delay` amount in multiple places. 

Using an animation also makes it easier to add complex behaviors. In this case, we can simply use the mod (`%`) operator to track where we are in the loop. As an example, if I wanted every other buzzer sound to be higher pitch, I could add a `% 16` condition.

Here's my loop code:

```
int frameCount = 0;
void loop(){
  noTone(buzzer); // reset

  leds = 0; // set [framecount] bits on
  for(int i=0; i<=frameCount; i++) {
    bitSet(leds, i);
  }
  updateShiftRegister();

  // if it's the 8th bit, set the buzzer to 1kHz
  if(frameCount == 7) {
    tone(buzzer, 1000);
  }
 
  frameCount++;
  frameCount = frameCount % 8;
  delay(5000);
}
```

In my case, to prevent overflow, I reset the value of the animation loop at the end of each cycle. (Technically, this is not an issue, since it would take impractically long to overflow, but it also makes `if(frameCount == 7)` cleaner.) 

The structure of my loop is simple. First, I reset everything by setting `leds` (the shift register byte) to 0 and disabling the buzzer. Then, I update the shift with the current cycle in the frame. Finally, I add an conditional to enable the buzzer on the final frame.

## Troubleshooting

I didn't really have any issue getting the circuit to work. I already had the shift register set up, so all I needed to do was use the buzzer. I had no trouble getting the buzzer to work. I followed [this](http://www.ardumotive.com/how-to-use-a-buzzer-en.html) tutorial.

One issue I ran into was that two of my LEDs would turn off when all eight were supposed to be turned on. Initially, I had my LEDs set up as two groups of red, green, yellow, and blue. The blue LEDs would turn off once power was applied to all eight. I think this probably happened because blue is a higher frequency and thus higher energy color, so it requires more power to run. Thus, when there is insufficient power to run all eight LEDs, the most demanding components do not work, i.e. the blue LEDs. I was able to resolve this issue by replacing the blue LEDs with other red LEDs.

## Adding Other Stuff

I completed the assignment a bit early, so I used the extra time to add extra features to my code. I turned the assignment into a visualization of C major scale. I changed the loop code to turn on only the bit corresponding to the current frame. I also had the buzzer play the current note of the scale. I looked up a [table](https://pages.mtu.edu/~suits/notefreqs.html) of note frequencies and copied them into an array to do this.

```
int notes[8] = {262, 294, 330, 349, 392, 440, 494, 523};
...
void loop(){
  noTone(buzzer);
  leds = 0;
  bitSet(leds, frameCount);
  updateShiftRegister();

  tone(buzzer, notes[frameCount]*2);
 
  frameCount++;
  frameCount = frameCount % 8;
  delay(1000);
}
```


## Working code

- `code/test`: working code for finished assignment
- `code/test2`: working code after adding other stuff