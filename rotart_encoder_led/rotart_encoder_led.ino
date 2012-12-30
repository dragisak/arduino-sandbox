 

#define ledPin1 14
#define ledPin2 12
#define buttonPin  13



int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {



  for(byte i=4; i<12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  pinMode(buttonPin, INPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  pinMode(encoderPin1, INPUT);
  digitalWrite(encoderPin1, HIGH);
  pinMode(encoderPin2, INPUT);
  digitalWrite(encoderPin2, HIGH);
  
 //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}



void loop(){  

   
   drawLeds(encoderValue);
   
 
}

void drawLeds(int position) {

 int led;
   
  
  led = (position>>2) & 0x07;
  
  for(int i=0; i<8; i++) {
    
    if(i==led) {
      digitalWrite(i+4, LOW);
    } else {
      digitalWrite(i+4, HIGH);
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
