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
  lcd.backlight();
  Wifly.init();//Initialize the wifishield
  Wifly.setConfig("AsymetricAnimals","laurie1dragisa");//here to set the ssid and password of the Router
  Wifly.join("AsymetricAnimals");
  Wifly.checkAssociated();
  while(!Wifly.connect("192.168.16.131","5007"));//connect the remote service
  Serial.print("Connected");
  Wifly.writeToSocket("Arduino!");
}
void loop()
{
  if(Wifly.canReadFromSocket())
  {
    //Serial.print(Wifly.readFromSocket());
    lcd.print(Wifly.readFromSocket());
  }
  if(Serial.available())
  {
    Wifly.print((char)Serial.read());
  }
}
