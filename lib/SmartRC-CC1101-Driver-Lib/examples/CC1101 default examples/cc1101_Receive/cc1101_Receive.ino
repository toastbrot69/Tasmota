// These examples are from the Electronics Cookbook by Simon Monk
//https://github.com/LSatan/SmartRC-CC1101-Driver-Lib
// mod by Little_S@tan

#include <ELECHOUSE_CC1101_SRC_DRV.h>

int gdo0;

const int n = 61;

void setup(){

#ifdef ESP32
gdo0 = 2;  // for esp32! GDO0 on GPIO pin 2.
#elif ESP8266
gdo0 = 5;  // for esp8266! GDO0 on pin 5 = D1.
#else
gdo0 = 6;  // for Arduino! GDO0 on pin 6.
#endif 
  
    Serial.begin(9600);
    Serial.println("Rx");
    ELECHOUSE_cc1101.Init();              // must be set to initialize the cc1101!
    ELECHOUSE_cc1101.setGDO(gdo0,0);     // set lib internal gdo pins (gdo0,gdo2). Gdo2 not use for this example.
    ELECHOUSE_cc1101.setCCMode(1);      // set config for internal transmission mode.
    ELECHOUSE_cc1101.setModulation(0); // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
    ELECHOUSE_cc1101.setMHZ(433.92);  // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
 // ELECHOUSE_cc1101.setPA(10);      // set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12)   Default is max!
    ELECHOUSE_cc1101.SetRx();       // set Receive on.
}
byte buffer[61] = {0};

void loop(){
  
  if (ELECHOUSE_cc1101.CheckReceiveFlag())
  {
    Serial.print("Rssi: ");
    Serial.println(ELECHOUSE_cc1101.getRssi());
    Serial.print("LQI: ");
    Serial.println(ELECHOUSE_cc1101.getLqi());
    
    int len = ELECHOUSE_cc1101.ReceiveData(buffer);
    buffer[len] = '\0';
    Serial.println((char *) buffer);
    ELECHOUSE_cc1101.SetRx();
  }
}
