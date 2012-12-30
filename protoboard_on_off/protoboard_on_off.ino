const int ser = 11;
const int srclk = 12;
const int srclr = 10;
const int ledPin = 13;

void setup() {
  pinMode(ser, OUTPUT);
  pinMode(srclk, OUTPUT);
  pinMode(srclr, OUTPUT);

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);


  for(int i = 0; i<8; i++) {
    digitalWrite(0, HIGH);
  }
       
}

int counter = 7;

void loop(){

  if (counter == 0) {
     digitalWrite(srclr, HIGH);
     digitalWrite(srclr, LOW);
     digitalWrite(ser, HIGH);
  }
    
  
  
  digitalWrite(srclk, HIGH);
  digitalWrite(srclk, LOW);
  
  digitalWrite(ser, LOW);
  
  
    
  
  
  
  
  
}
