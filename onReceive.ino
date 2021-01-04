bool onReceive()
{
  String incoming = "";
 
  uint8_t len = sizeof(buf);
  uint8_t from;
  if (manager->recvfromAck(buf, &len, &from))
  {
    digitalWrite(LORA_RECV, HIGH);
    #ifdef debug
    Serial.print("got request from : 0x");
    Serial.print(from, HEX);
    Serial.print(": ");
    Serial.println((char*)buf);
    #endif

    incoming = buf;
    processInboundPacket(incoming,from);
  }
 
  digitalWrite(LORA_RECV, LOW);
  return true;
}
