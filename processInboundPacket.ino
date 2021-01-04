bool processInboundPacket(String inboundData, uint8_t from)
{
  #ifdef debug1
  Serial.print("Processing inbound packet");
  Serial.println(inboundData);
  #endif
  //Packet structure is
  //ID:COMMAND:DET:EOM
  //ID:REQUEST:ALL:EOM

  // Respond to command
  String command = inboundData.substring(3,10);
  #ifdef debug1
  Serial.print("COMMAND:");
  Serial.println(command);
  #endif
  String det = inboundData.substring(11,14);
  #ifdef debug1
  Serial.print("DET:");
  Serial.println(det);
  #endif
  String eom = inboundData.substring(15,18);
  #ifdef debug1
  Serial.print("EOM:");
  Serial.println(eom);
  #endif
  if (eom != "EOM")
  {
    #ifdef debug1
    Serial.println("INVALID PACKET:EOM ERROR");
    #endif
    return false;
  }
  processCommand(command,det, from);
  return true;
}
