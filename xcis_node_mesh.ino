
// Beta Version 14/12/2020 
#include <SPI.h>              // include libraries
#include <SoftwareSerial.h>

#include <RHRouter.h>
#include <RHMesh.h>
#include <RH_RF95.h>


uint8_t nodeId;

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

#define XCIS_RH_MESH_MAX_MESSAGE_LEN 32

// Singleton instance of the radio driver
//RH_RF95 rf95;
RH_RF95 rf95(RFM95_CS, RFM95_INT);
// Class to manage message delivery and receipt, using the driver declared above
RHMesh *manager;
// message buffer
uint8_t buf[RH_MESH_MAX_MESSAGE_LEN];

#define debug1 // Turn serial output OFF when not connected to a IDE via USB

uint8_t localAddress = 2;
String localAddress_string = "02";

String sensorName = "Azabu2";

#define LORA_SEND 22
#define LORA_RECV 23

//SoftwareSerial usonic (20,21); //RX, TX)
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish
unsigned long DELAY_TIME = 5000; // 5 sec

unsigned char data[4]={};
float distance;
String distance_string;

void setup()
{
   pinMode(RFM95_RST, OUTPUT);
   digitalWrite(RFM95_RST, HIGH);
   pinMode(LORA_SEND, OUTPUT);
   pinMode(LORA_RECV, OUTPUT);
    
  digitalWrite(LED_BUILTIN, LOW);
  
  #ifdef debug1
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Lora Mesh Sensor1");
  #endif
  nodeId = localAddress;
  Serial.print("initializing node ");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  manager = new RHMesh(rf95, nodeId);

  if (!manager->init()) {
    Serial.println(F("init failed"));
  } else {
    Serial.println("done");
  }
  rf95.setTxPower(23, false);
  rf95.setFrequency(915.0);
  rf95.setCADTimeout(500);

  Serial2.begin(9600);
  while (!Serial2);
  Serial.println("Usonic init done");
  delayStart = millis();   // start delay
  delayRunning = true;    // not finished yet
  Serial.println("Lora Mesh Sensor1 Ready");
}

void loop()
{
    // check if delay has timed out after 10sec == DELAY_TIME
  if (delayRunning && ((millis() - delayStart) >= DELAY_TIME))
  {
    delayStart += DELAY_TIME; 
    delayRunning = true; // // if false, prevent this code being run more then once   
    readDataStream();
  }

  // parse for a packet, and call onReceive with the result:
  if (onReceive())
  {
    //String message = "Got Message!";   // send a message
  }
}
