void sendMessage(String outgoing, uint8_t from)
{
  //flashResponseLed();
  digitalWrite(LORA_SEND, HIGH);
  uint8_t data[XCIS_RH_MESH_MAX_MESSAGE_LEN];
  outgoing.toCharArray(data,sizeof(data));
  if (manager->sendtoWait(data, sizeof(data), from) != RH_ROUTER_ERROR_NONE)
  {
      #ifdef debug
      Serial.println("sendtoWait failed");
      #endif debug
  }
  digitalWrite(LORA_SEND, LOW);
}
