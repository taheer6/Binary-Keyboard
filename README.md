# Binary Keyboard

## Intro
The Binary Keyboard is exactly what it sounds like: an 8-bit ASCII keyboard that converts binary input into letters, numbers, and a few special characters like backspace, space, and return. It uses two switches to enter `0` and `1`, builds a full byte, shows the active 8-bit input on an LCD, and then sends the finished character to a computer as a USB keyboard. It is part experiment, part joke, and part immersive typing experience for anyone who has ever wanted to feel like they are typing in raw machine language. Next up is a keyboard-to-binary converter that uses a mechanical solenoid to convert normal keyboard input back into binary for those who are binarily challenged.

## Schematic
The schematic is built around the Seeed XIAO SAMD21, which handles both the binary input logic and USB HID keyboard output. Two switch inputs are wired to the XIAO to represent binary `0` and `1`, and the display is a standard HD44780-style character LCD running in 4-bit mode to keep the wiring simple. A contrast potentiometer is broken out through a 3-pin connector, and the LCD backlight is current-limited with a resistor. On the input side, the PCB was designed to support mechanical keyboard switches through Kailh hot-swap sockets, so the two binary keys can be swapped or changed without soldering the switches directly.

<img width="974" height="672" alt="image" src="https://github.com/user-attachments/assets/39efd87b-11a6-4084-9a85-fa7b016da672" />

## PCB Design
The PCB takes the breadboard prototype and turns it into a cleaner dedicated input board with mounts for the XIAO SAMD21, the LCD header, the two switch positions, and the contrast adjustment header. The routing is intentionally simple since the board only needs to handle two button inputs, LCD signaling, and power distribution, but it still gave me a solid introduction to laying out a compact custom board around a microcontroller, display, and keyboard hardware.

<img width="695" height="543" alt="image" src="https://github.com/user-attachments/assets/4065232a-cfc8-4a2e-a9ba-6dc6174d20d9" />
<img width="455" height="309" alt="image" src="https://github.com/user-attachments/assets/4f112bbd-9902-4a5f-b6e1-2b7388f4c14a" />

## What I Learned, Mistakes Made, and Version 2
This project taught me a lot about the difference between getting something working on a breadboard and designing it properly into a PCB. On the firmware side, I learned how to debounce switches, assemble binary input into full bytes, convert those bytes into ASCII, and send them over USB HID so a Mac recognizes the board as a keyboard. On the hardware side, I got more comfortable with LCD interfacing, microcontroller pin mapping, KiCad schematic capture, PCB routing, and working with mechanical keyboard parts like Kailh hot-swap sockets. Most of the mistakes in Version 1 came from footprint edits and part placement rather than the circuit idea itself: when converting the XIAO SAMD21 footprint from surface mount to through-hole, I left the holes a bit too wide, which still works but requires bending the pins outward slightly, and I also misplaced the hot-swap socket footprint when it should have been inverted onto the second layer so the switches could sit flush with the PCB. If I were building Version 2, I would spend more time validating dimensions, checking part orientation, and researching any footprint I had not used before, especially when adapting pre-existing parts instead of treating them as ready to drop in.
