// demo: CAN-BUS Shield, send data

#include "mcp_can.h"
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);// Set CS pin

void setup(){
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(CAN_500KBPS)){ // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(1000);
    }
    Serial.println("CAN BUS Shield init ok!");
}

unsigned char stmp[8] = {7, 6, 5, 4, 3, 2, 1, 0};

void loop(){
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    Serial.print("\nMessage send N="); 
    for( byte i=0; i<=7; i++){ Serial.print((++stmp[i]),HEX); Serial.print(" "); }
    
    CAN.sendMsgBuf(0x00, 0, 8, stmp);
    delay(1000); // send data per 1000ms
}
