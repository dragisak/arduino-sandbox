#include "Wifly.h"
#include <SoftwareSerial.h>
WiflyClass Wifly(2,3);
void setup()
{
  Serial.begin(9600);//use the hardware serial to communicate with the PC
  Wifly.init();//Initialize the wifishield
  Wifly.setConfig("AsymetricAnimals","laurie1dragisa");//here to set the ssid and password of the Router
  Wifly.join("AsymetricAnimals");
  Wifly.checkAssociated();
  while(!Wifly.connect("192.168.16.131","5007"));//connect the remote service
  Wifly.writeToSocket("Arduino!");
}
void loop()
{
  if(Wifly.canReadFromSocket())
  {
    Serial.print(Wifly.readFromSocket());
  }
  if(Serial.available())
  {
    Wifly.print((char)Serial.read());
  }
}
