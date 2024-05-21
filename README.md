# 2D-pong project

This project uses an Arduino Uno, some RGB LEDs and a couple of shift registers to construct a single-player 2D-pong game box. The game features a live counter, LEDs acting as ping pong balls, push buttons to play the game, and a 9v battery and power switch to increase portability. This repo features the code used to program the Arduino and a simulation of a prototype Using Wokwi and PlatformIO in Vscode. There is also a circuit diagram for those wanting to construct it themselves.
This project is inspired by <a href="https://hackaday.com/?p=651220">1D led pong, Arduino style</a> by Kristina Panos.

## How it works

The game uses push buttons to bounce LEDs back and forth. While the player is doing this, the LEDs will go faster and change color with the starting color being green, then blue, and finally red when the game is being played at its fastest speed. A 7-segment display acts as a counter from 9 to 0. When a player fails, the counter is reduced by one. When the counter reaches zero a chime is played by the buzzer and the counter is reset back to 9 and loops over again. A link to a demo video can be found below

- https://drive.google.com/file/d/1gppf-Sq-f_mhw7JxwpiT1e1hT7sdtg1i/view?usp=sharing - Demo video

If you would like to support the work that I do, please follow me on GitHub and <a href = " https://www.linkedin.com/in/marvin-ochei-913a73278?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app ">LinkedIn</a>.
