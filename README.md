# 7-Segment-Display-Modification-using-a-Joystick
### Using a Joystick Module to change the numbers displayed on a 5161AS 7-Segment Display
+ Pushing the joystick upward increments the number displayed while pushing the joystick downward decrements the number displayed
+ Pushing the joystick in one direction long enough speeds up the change in the number displayed (default change is every 1/2 second, but after 4 increments/decrements change is every 1/4 second)
+ Pushing the button of the joystick turns on and off the decimal point
### Issues
+ Random increments of the display despite no movement of the joystick
  + This might be due to my joystick drifting and having a X-Cord value of 700-800 when steady while the typical value should be ~520
+ Pushing the button of the joystick while the display is incrementing/decrementing will sometimes cause the decimal point to change
  + This is because in order for a visual change of the display a delay is needed, meaning during that period if the button is pressed the decimal point wont change
### Wiring Diagram
![Screenshot of the wiring diagram used when writing the program](images/Wiring_Diagram-Joystick_Segment_Display.png)
