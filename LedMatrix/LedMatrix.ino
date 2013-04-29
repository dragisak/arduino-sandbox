#include "LedControl.h"

/* 
 * Now we create a new LedControl. 
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221 	
 * There will only be a single MAX7221 attached to the arduino 
 */
// LedControl lc1=LedControl(10,12,11,1);


//LedControl lc=LedControl(10,12,11,3);

int devices = 3;

byte a[4] = {0x18, 0x3C, 0x7E, 0xFF};
LedControl lc=LedControl(10,12,11,devices);

int cnt[3] = {0,1,2};
int b=0;

void setup() {

  //LedControl lc1 = LedControl(10,12,11,3);
  
  for(int index=0;index<lc.getDeviceCount();index++) {
      lc.shutdown(index,false);
      lc.setIntensity(index,4);
      lc.clearDisplay(index);
  }
 
}

void square(int addr, int n) {
  
  lc.clearDisplay(addr);
  if(n != 0) {
    byte val = a[n-1];
    
    lc.setRow(addr, 4-n, val);
    lc.setRow(addr, 3+n, val);
    lc.setColumn(addr, 4-n, val);
    lc.setColumn(addr, 3+n, val);
  }
}

void loop() {
    for(int i=0; i<devices; i++) {
      square(i, cnt[0]);
    }
    
   delay(500);
    
    cnt[0] = (cnt[0] + 1) % 5;
  
}

