int x = A0;
int y = A1;
int speed_up_x_down = 0;
int speed_up_x_up = 0;

int max_steady_x = 800;
int min_steady_x = 700;

int button = 10;
int current_DP_state = 0;
int DP = 0;

bool x_steady = true;

int currentNum = 0;
const int digitNums = 10;
const int segmentStates = 7;
const int digits[digitNums][segmentStates] = {
  {0, 1, 1, 1, 1, 1, 1}, //0
  {0, 0, 0, 1, 0, 0, 1}, //1
  {1, 0, 1, 1, 1, 1, 0}, //2
  {1, 0, 1, 1, 0, 1, 1}, //3
  {1, 1, 0, 1, 0, 0, 1}, //4
  {1, 1, 1, 0, 0, 1, 1}, //5
  {1, 1, 1, 0, 1, 1, 1}, //6
  {0, 1, 1, 1, 0, 0, 1}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}, //9
};


void setup() {
  Serial.begin(9600);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(button, INPUT_PULLUP);

  for(int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
  }

  for(int currentSegment = 0; currentSegment < segmentStates; currentSegment++) // Initializes the segment display to 0
  {
    digitalWrite(currentSegment + 2, digits[0][currentSegment]);
  }
  delay(1000);
  
}

void button_push() {
  if(digitalRead(button) != 1 && current_DP_state == DP) // Turns on/off the Decimal Point whenever the button is first pressed
  {
    DP = !DP;
    digitalWrite(9, DP);
  }
  if(digitalRead(button) == 1) // Ensurses when the button is released the current Decimal Point status is recorded
  {
    current_DP_state = DP;
  }
}

void loop() {
  x_steady = (max_steady_x > analogRead(x)) && (analogRead(x) > min_steady_x); 
  // Determines whether the joystick is steady based on its x cords

  // Serial.print("Steady?: "); 
  // Serial.println(x_steady);
  // Serial.print("X Cord: ");
  // Serial.println(analogRead(x));
  // Serial.println();
  //Debug info

  while(!(x_steady))
  {

    button_push();

    if(max_steady_x < analogRead(x)) // Joystick is pushed downward
    {
      speed_up_x_up = 0;
      speed_up_x_down++;

      currentNum--;
      if(currentNum <= -1) // Ensures the segment display loops from 0 back to 9
      {
        currentNum = 9;
      }

      for(int currentSegment = 0; currentSegment < segmentStates; currentSegment++) // Changes the segment display to the next number in the sequence
      {
        digitalWrite(currentSegment + 2, digits[currentNum][currentSegment]);
      }

      speed_up_x_down >= 4 ? delay(250) : delay(500); // If the jostick is pushed downward long enough, speed up the decrease
    }
    if(analogRead(x) < min_steady_x) // Joystick is pushed upward
    {
      speed_up_x_down = 0;
      speed_up_x_up++;

      currentNum++;
      if(currentNum >= 10) // Ensures the segment display loops from 9 back to 0
      {
        currentNum = 0;
      }

      for(int currentSegment = 0; currentSegment < segmentStates; currentSegment++) // Changes the segment display to the next number in the sequence
      {
        digitalWrite(currentSegment + 2, digits[currentNum][currentSegment]);
      }

      speed_up_x_up >= 4 ? delay(250) : delay(500); // If the jostick is pushed upward long enough, speed up the increase
    }

    x_steady = (800 > analogRead(x)) && (analogRead(x) > 700); 

  }

  speed_up_x_up = 0;
  speed_up_x_down = 0;
  // Resets the speed up when the joystick returns to its steady state

  button_push();

}
