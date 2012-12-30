const int ledPin1 = 13;
const int ledPin2 = 11;
const int buttonPin = 12;

const int pins = 8;
const int steps = 28;

int buttonState = LOW;
int previousButtonState = LOW;

int ledState = 0;

int ledDirection = 1;

void setup() {



  for(int i=0; i<pins; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(buttonPin, INPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

}

void setAll(int state) {

  digitalWrite(0, state);
  digitalWrite(1, state);
  digitalWrite(2, state);
  digitalWrite(3, state);
  digitalWrite(4, state);
  digitalWrite(5, state);
  digitalWrite(6, state);
  digitalWrite(7, state);

}




void loop(){  

  if (ledDirection > 0) {
    if (ledState < steps) {
      setAll(LOW);
      delay(steps-ledState);
      setAll(HIGH);
      delay(ledState);
      ledState++; 
    } 
    else {
      ledDirection = -ledDirection;
    }


  } 
  else {
    if (ledState > 0) {
      setAll(HIGH);
      delay(ledState);
      setAll(LOW);
      delay(steps-ledState);
      ledState--; 
    } 
    else {
      ledDirection = -ledDirection;
    }
  }

}

