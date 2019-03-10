/*
  Arjav Patel - KAMSC Research Team 2019 Reaction Wheel Control System 
  March 7, 2019
  Tasks:
   - Take user input
   - Spin motor at specified duty cycle 
   - Control LEDs to reflect Task
     - Blinking Red: Indicates start 
     - Yellow: Motor is speeding up
     - Green: Motor is running at indicated duty cycle
     - Red: Motor is stopping
   - Output what command is running to the Serial Monitor
   - Make program robust
     - Inform user of invalid input (without breaking)
     - Make adjustments easy to do
 */

//Create pin numbers for each compenents
int motor = 11;
int red = 10;
int yellow = 9;
int green = 8;

//Create varibles to help build a number from user input
int input = 0;
int byteVal = 0;
int junk = 0;
char nextByte = ' ';

//Create varibles for the various timing elements (in millieconds)
long preStart = 10000; //Even number
long speedTime = preStart + 7000;
long constTime = speedTime + 10000;
long currTime = 0;
long startTime = 0;

//Create varibles to facilitate flow of control
int state = 0;
bool check = 0;


//Function that takes in user input and builds a number
int getVal() {

  //Prompt user for input and reset variables
  Serial.println("\nEnter a duty cycle from 0 to 255: ");
  input = 0;
  check = 0;

  //Wait until user provides input
  while(Serial.available() <= 0) {
     delay(10);
  }

  //Run as long as there is input
  while(Serial.available() > 0) {

    //Input each digit as a character and get ASCII value
    nextByte = Serial.read();
    byteVal = (int) nextByte;

    //If not a numerican digit, inform user
    if (byteVal < 48 || byteVal > 57) {
      Serial.print("Character '");
      Serial.print(nextByte);
      Serial.println("' is invalid. Please try again...");

      //If bad input, take the rest of the values as junk input
      if (Serial.available() > 0) {
        while (Serial.available() > 0) {
          junk = Serial.read();
        }
        check = 1;
      }
    }

    //Add next digit to end of number
    input *= 10;
    input += byteVal - 48;
  }

  //If bad input, prompt user for input again
  if (check == 1) {
    getVal();
  }

  //If value exceeds 255, inform user and call getVal() for new input
  if(input < 0 || input > 255) {
    Serial.print("Value '");
    Serial.print(input);
    Serial.println("' is out of range. Please try again...");
    getVal();
  }

  //Exit function
  return 0;
}


//Setup function that runs once each time the program begins
void setup() {

  //Declare the pins to recieve output
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT); 
  pinMode(green, OUTPUT); 
  analogWrite(motor, 0); // By changing values from 0 to 255 you can control motor speed

  //Inform user of what the LEDs mean
  Serial.println("LED INDICATORS");
  Serial.println("Blinking Red: Indicates start");
  Serial.println("Yellow: Motor is speeding up");
  Serial.println("Green: Motor is running at indicated duty cycle");
  Serial.println("Red: Motor is stopping");

  //Get user input, and if value is good, print that
  getVal();
  Serial.print("Setting duty cycle to: ");
  Serial.println(input);
  Serial.println("*Please remove cable before countdown reaches 0*");

  //Set the time variable, and reset the others
  startTime = millis();
  state = 0;
  check = 0;
}


//Looping function that runs every couple of milliseconds
//Avoid for/while loops and delays
void loop()
{
  //Continuously calculate the time elapsed since program began
  currTime = millis() - startTime;

  //Switch case to eliminate loops
  switch (state) {

    /*          GENERAL FORMAT
     * case #
     *   Output to specific components
     *   Print what is happening to serial monitor
     *   Check to see if it is time to move to the next stage
     *   Reset check and increment state
     * break  
     */

    //Turn red LED on
    //Output countdown until motor starts
    case 0:
        digitalWrite(red, HIGH);
        if (check == 0) {
          Serial.print((preStart/2000) - (currTime / 2000));
          Serial.println("...");
        }
        check = 1;
        
        if (currTime < preStart && (currTime / 1000 % 2 != 0)) {
          state = 1;
        }
    break;

    //Turn red LED off to create a blinking effect
    //If enough time has elapsed, start to turn motor
    case 1:
        digitalWrite(red, LOW);

        if (currTime > preStart) {
          state = 2;
          check = 0;
        }
    
        if (currTime < preStart && (currTime / 1000 % 2 == 0)) {
          state = 0;
          check = 0;
        }
    break;

    //Start to send power to the motor
    //Print to serial monitor that motor is running
    //Turn yellow LED on and red LED off
    case 2:
        analogWrite(motor, input);
        digitalWrite(red, LOW);
        digitalWrite(yellow, HIGH);

        if (check == 0) {
          Serial.println("Speeding motor");
        }
        check = 1;

        if (currTime > speedTime) {
          state = 3;
          //check = 0;
        }
    break;

    //Continue to send power to the motor
    //Print to serial monitor that motor has reached specified speed
    //Turn green LED on and yellow LED off
    case 3:
        analogWrite(motor, input);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);

        /*if (check == 0) {
          Serial.println("Speed reached");
        }
        check = 1;*/

        if (currTime > constTime) {
          state = 4;
          //check = 0;
        }
    break;

    //Stop the motor
    //Print to serial monitor that the motor is being stopped
    //Turn red LED on and green LED off
    case 4:
        analogWrite(motor, 0);
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);

        /*if (check == 0) {
          Serial.println("Stopping motor");
        }
        check = 1;*/
    break;
  }
}
