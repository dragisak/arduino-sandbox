#include <Wifly.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

WiflyClass Wifly(2,3);  

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 

  Serial.begin(9600);//use the hardware serial to communicate with the PC
  Serial.print("Start");
  Wifly.init();//Initialize the wifishield
  Wifly.setConfig("AsymetricAnimals","laurie1dragisa");//here to set the ssid and password of the Router
  Wifly.join("AsymetricAnimals");
  Wifly.checkAssociated();
}
void loop()
{
  char content;
  
  // http://api.wunderground.com/api/d5d0fdedafa46e57/conditions/q/94110.json
  //while(!Wifly.connect("38.102.136.138","80"));
  while(!Wifly.connect("192.168.16.131","9000"));
  Serial.print("Connected");
  lcd.backlight();
  
  Wifly.writeToSocket("GET /temp/94110 HTTP/1.0\n\n");
  
  while(!Wifly.canReadFromSocket()){}
  
  while(Wifly.canReadFromSocket()) {
    
     content = Wifly.readFromSocket();
     Serial.print(content);
     while(!Wifly.canReadFromSocket()){}
  }


  delay(10000); 
  Serial.print("Repeating"); 
  
}
