void readDataStream()
{
  #ifdef debug1
  Serial.println("readDataStream");
  #endif
  unsigned char data[4]={};
  unsigned char incomingByte = 0;
  String inData = "";
  int byteCount = 0;
  bool foundPacket = false;
  while (Serial2.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial2.read();
    if (incomingByte == 0xFF)
    {
      //Serial.println("Found start");
      data[0] = incomingByte;
      byteCount++;
      while (Serial2.available() > 0) {
        data[byteCount] = Serial2.read();
        byteCount++;
        if (byteCount > 3)
        {
          foundPacket = true;
          break;
        }
      }
    }
    if (foundPacket)
        break;
  }
  Serial2.flush();
  /*
  for(int i=0;i<4;i++)
  {
      Serial.print(data[i],HEX);
  }
  */
  if(data[0]==0xff)
  {
    int sum;
    sum=(data[0]+data[1]+data[2])&0x00FF;
    if(sum==data[3])
    {
        distance=(data[1]<<8)+data[2];

       #ifdef debug
        if(distance>30)
        {
          Serial.print("distance=");
          Serial.print(distance/10);
          Serial.println("cm");
        }
        else 
        {
          Serial.println("Below the lower limit");
        }
       #endif
        
    }
    else 
    {
      #ifdef debug
      Serial.println("ERROR");
      #endif
    }
  }
 
}
