#include <LiquidCrystal.h>

const int startPress = 4;
const int boostPress = 5;
const int track = 3; 
const int trigPin = 6; // connects to the trigger pin on the distance sensor
const int echoPin = 7; // connects to the echo pin on the distance sensor

// Initializing LCD
const int rs = 8, en = 2, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//contrast variable for LCD
const int contrast = 50;
const int contrastPin = 9;

int startState;
int startStateSet;
int boostState;
int boostStateSet; 
int boostsLeft;
int boostActive;
float duration;
float distance;
int raceOver;
long startTime;
long elapsedTime;

// Setup
void setup()
{
    pinMode(startPress, INPUT);
    pinMode(boostPress, INPUT);
    pinMode(contrastPin, OUTPUT);

  
    pinMode(trigPin, OUTPUT); //the trigger pin will output pulses of electricity
    pinMode(echoPin, INPUT); //the echo pin will measure the duration of pulses coming back from the distance sensor
  	

  	lcd.begin(16, 2); //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  	lcd.clear(); //clear the display
  
    analogWrite(contrastPin, contrast);

  	boostsLeft = 1;
}

// Main Function
void loop()
{
  	waitForStart(); // Checks for start button press then shows starting signal
}

// Waits for start button press
void waitForStart() // Checks for start button press then calls startSignal()
{
  	// Resets Neccessary Variables for all functions
	startState = LOW;
	startStateSet = 0;
	boostState = LOW;
	boostStateSet = 0; 
	boostsLeft = 1;
	boostActive = 0;
	raceOver = 0;
	distance = 0; 
  	// waits for start button
  	while (startStateSet == 0)
  	{ 
  		startStateSet = startButton(); // sets startStateSet to startButton()
    	delay(100);
  	}
  	delay(500); // delay before start signal goes off
  	startSignal(); // Shows start signal 
  	RaceOngoing(); // Race Starts
}

// Checks for start button press
int startButton() // checks if startState is HIGH and returns 1 if so, 0 otherwise
{
  	startState = digitalRead(startPress);
    	if(startState == HIGH)
    	{
        	return 1;
    	}
  	return 0;
}

// Shows start signal
void startSignal() // Shows start signal
{
  	// turns on LCD timer
  	lcdON();
  	delay(3000);
  	lcdTime(); // Updates race timer
}

// Starts Race
void RaceOngoing()
{
  	// Race starts, track power on
  	digitalWrite(track,HIGH);//analogWrite(track, 200);  
  	// MAKE SURE RACE ALWAYS LASTS LONGER THAN TIME FOR START SIGNAL TO TURN OFF
  	// REWORK TO MAKE BOOST WORK DURING FIRST COUPLE SECONDS OR SHOW SIGNAL FOR WHEN BOOST CAN BE USED
  
  	// checks for boost press or end of race after start light turns off        
  	while (raceOver == 0)
  	{ 
      if (boostsLeft > 0)
      {
  		  boostButton(); // sets boostStateSet to 0, increases voltage
      }
    	if (boostActive == 1) // turns on boost if boost button is pressed
    	{
  	  	for (int i=0; i<=10; i++) // boosts for 1 second or until race ends
    		{
        	lcdTime(); // Updates race timer
        	raceEnded(); // checks if race has ended
        	if(raceOver == 1) // breaks boost if race is over
        	{
          	i = 11;
        	}
        	delay2(100);
        }
        //digitalWrite(track,HIGH);//analogWrite(track, 200);  
        boostActive = 0; // sets boost active to 0
      }
      digitalWrite(track,HIGH);//analogWrite(track, 200); 
      lcdTime(); // Updates race timer
    	raceEnded(); // checks if race has ended
    	delay2(100);
    }
  // ADD SOUND EFFECT LATER
}

// Uses Speed Boost
void boostButton() // checks if startState is HIGH and returns 1 if so, 0 otherwise
{

  	boostState = digitalRead(boostPress);
  		if(boostState == HIGH)
  		{
      		boostsLeft--; // set boostsLeft to 0
        	boostActive = 1;
        	analogWrite(track, 255); // turn on boost
    	}

}

// Checks if race is over
void raceEnded()
{
	distance = getDistance(); // variable to store the distance measured by the sensor
  	if (distance <= 5) // change to working value
    {
      raceOver = 1;
	  analogWrite(track, 0);
    }
}

int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  return distance;
}

void lcdON()
{
  lcd.clear();
  lcd.print("Time: 00:00");
  startTime = millis() + 3000;
}

void lcdOFF()
{
  analogWrite(9, 0);
}

void lcdTime()
{
   	elapsedTime = millis() - startTime;
  	unsigned long minutes = (elapsedTime / 60000) % 60;
  	unsigned long seconds = (elapsedTime / 1000) % 60;
  	unsigned long milliseconds = (elapsedTime % 100);

  	// Format the time
  	String raceTimer = "Time: " + String(minutes, 10) + ":" + String(seconds, 10) + ":" + String(milliseconds, 10);

  	// Update the LCD display
    lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print(raceTimer);
}            

// Use for delays so timer updates properly, min time 100 ms
void delay2(int time)
{
  for(int i = 0; i <= (time/100); i++)
  {
      lcdTime();
      boostButton();
      delay(100);
  }
}