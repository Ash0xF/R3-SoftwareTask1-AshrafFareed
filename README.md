
<img align="left" src="https://i.imgur.com/fUMdZvH.png">

# 2 7-Segment Displays

The circuit was made using TinkerCad. The purpose of this circuit was to implement a way that a potentiometer controls which number from 0 to 99 is displayed to the 2 7-segment displays. This was accomplish by connecting 2 CD4511 decoders (Binary-coded decimal) to the 7-segment displays, where they take 4 inputs from the Arduino and output 7 signal to the 7-segment display. 

## Demo
---

![Alt Text](https://i.imgur.com/hnJxPyK.gif "2 7-Segment displays controlled by 2 CD4511")

## TinkerCad link
---

You can check out the circuit with all the C++ code by clicking [here](https://www.tinkercad.com/things/fjrNXZbFBFk).




## Known Issues with TinkerCad
---

**These issues have to do with the simulation of the circuit and not the wiring or code. This is because the analog input of the potentiometer prints the correct number in the serial console.**

- When attempting to make the displays "00" the display gets stuck to the previously held number (e.g. 02, 03, etc). Unless before the circuit simulation the potentiometer is initialized at 00 the display will show "00", but it will still not give "00" if you have turned it to a different number and back.

- Near the end tickers of the potentiometer, instead of smoothly rotating to 99 it will instead jump to 99 instantaneously.

- The potentiometer will jump 2 ticks instead of 1 even though it is mapped from 0 to 99. **The analog input still prints out the correct 2 jump tick output although it is mapped correctly in the code**