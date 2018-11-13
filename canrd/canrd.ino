// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// 22


#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN); // Set CS pin

void setup(){
    Serial.begin(9600);
    while (CAN_OK != CAN.begin(CAN_500KBPS)){ // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}


void loop(){
    byte len = 0;
    byte buf[8];
    if(CAN_MSGAVAIL == CAN.checkReceive()){ // check if data coming
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        unsigned long canId = CAN.getCanId();    
        Serial.print("\nID=0x"); Serial.print(canId, HEX);
        Serial.print(" data= ");
        for(int i = 0; i<len; i++){ Serial.print(buf[i], HEX); Serial.print(" "); }
    }
}

