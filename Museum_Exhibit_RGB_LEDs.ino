const int red1 = 2;
const int red2 = 6;
const int red3 = 8;
const int blue1 = 3;
const int blue2 = 5;
const int blue3 = 9;
const int green1 = 4;
const int green2 = 7;
const int green3 = 10;
const int startPress = 11;

int startState;
int startStateSet;

// Setup
void setup()
{
	  pinMode(red1, OUTPUT);
    pinMode(red2, OUTPUT);
    pinMode(red3, OUTPUT);
  	pinMode(blue1, OUTPUT);
    pinMode(blue2, OUTPUT);
    pinMode(blue3, OUTPUT);
    pinMode(green1, OUTPUT);
    pinMode(green2, OUTPUT);
    pinMode(green3, OUTPUT);
    pinMode(startPress, INPUT);

  	digitalWrite(blue1, LOW);
    digitalWrite(blue2, LOW);
    digitalWrite(blue3, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(green2, LOW);
    digitalWrite(green3, LOW);
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
}

// Main Function
void loop()
{
  startSignal();
  
  waitForStart(); // Checks for start button press then shows starting signal
}

// Waits for start button press
void waitForStart() // Checks for start button press then calls startSignal()
{
  	// Resets Neccessary Variables for all functions
	startState = LOW;
	startStateSet = 0;
  // waits for start button
	while (startStateSet == 0)
  { 
		startStateSet = startButton(); // sets startStateSet to startButton()
  	delay(100);
  }
  delay(500); // delay before start signal goes off
  startSignal(); // Shows start signal 
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
  // RBG1 Red
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(green3, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, LOW);
	digitalWrite(red3, LOW);
	delay(1000);
  // RGB2 Red
  digitalWrite(red2, HIGH);
	delay(1000);
  // RGB3 Red
  digitalWrite(red3, HIGH);
	delay(1000);
  // All green
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
	digitalWrite(red3, LOW);
	digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  digitalWrite(green3, HIGH);
  delay(8000); // time for start signal to turn off
  	// Start signal off
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(green3, LOW);
}