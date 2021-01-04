bool processCommand(String command, String detail, uint8_t from)
{

  #ifdef debug1
  Serial.println("Processing command");
  Serial.print("COMMAND:");
  Serial.println(command);
  Serial.print("DETAIL:");
  Serial.println(detail);
  #endif
  // Generate response data based on command and request
  
  // Send response

  String response = "Value=" + String(distance) + ",";

   #ifdef debug1
  Serial.println(response);
  #endif
  sendMessage("ID=" + localAddress_string + ",Name=" + sensorName + "," + response, from);

}
