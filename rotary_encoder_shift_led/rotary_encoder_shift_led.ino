 
const int dataPin = 0;
const int latchPin = 1;
const int clockPin = 4;
const int buttonPin = 5;

#define encoderPin1  2
#define encoderPin2  3

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

boolean toggle = false;
int previousButtonState = LOW;


byte randX = 0;
int randY = 0;

void setup() {

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);


  for(byte i=6; i<14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  
  pinMode(encoderPin1, INPUT);
  digitalWrite(encoderPin1, HIGH);
  pinMode(encoderPin2, INPUT);
  digitalWrite(encoderPin2, HIGH);
  
 //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
  
  randomSeed(256);
  
}

void readButton() {
  
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState && buttonState != previousButtonState ) {
    toggle = !toggle;
  } 
  previousButtonState = buttonState;
}



void loop() {
  
  
  
  // count from 0 to 255 and display the number 
  // on the LEDs
  if (toggle) {
    
    for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
      
      drawLeds(encoderValue);
      // take the latchPin low so 
      // the LEDs don't change while you're sending in bits:

      digitalWrite(latchPin, LOW);
      // shift out the bits:
      shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);  
  
      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
      
      readButton();
      
      if (!toggle) {
        break;
      }
  
      // pause before next value:
      delay(100);
      readButton();
      delay(100);
      readButton();
      delay(100);
      readButton();
      delay(100);
      readButton();
    }
  } else {
    
    randX = random(256);
    randY = random(256);

   setLeds(randX);
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, randY);  
   digitalWrite(latchPin, HIGH);
   readButton();
   delay(100);
   readButton();
   delay(100);
   readButton();
   delay(100);
   readButton();

  }
  
}

void setLeds(int value) {

  byte temp = value;
  
  for(int i=0; i<8; i++) {
    digitalWrite(i+6, temp & 1);      
    temp = temp >> 1;     
  }
 
}



void drawLeds(int position) {

 int led;
   
  
  led = (position>>2) & 0x07;
  
  for(int i=0; i<8; i++) {
    
    if(i==led) {
      digitalWrite(i+6, LOW) ;
    } else {
      digitalWrite(i+6, HIGH);
    }
  }
 
}




void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
