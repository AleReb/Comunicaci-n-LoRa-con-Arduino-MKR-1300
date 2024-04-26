#include <MKRWAN_v2.h>
  

LoRaModem modem;

String appEui = "3000000000000060";
String appKey = "7466CCC6064E3B6EA0FB9BFF654E9585";
void setup() {
 Serial.begin(115200);
 while (!Serial);

 if (!modem.begin(AU915)) {
 Serial.println("Failed to start module");
 while (1);
  };
Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
 int connected = modem.joinOTAA(appEui, appKey);
 while(!connected){
 Serial.println("Retry...");
 if(!modem.joinOTAA(appEui, appKey)){
 Serial.println("Fail");
    }
 else{
 break;
    }
  };
  
  // Set poll interval to 60 secs.
  modem.minPollInterval(60);
  // NOTE: independently by this setting the modem will
  // not allow to send more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void loop() {
 Serial.println();
 Serial.println("Send something in the serial console to send the payload");

 
while (!Serial.available());
  //This line is clearing the serial buffer
  String msg = Serial.readStringUntil('\r');


 Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
 Serial.println();
 int err;
 modem.setPort(1);
 modem.beginPacket();
 modem.print(msg);
 err = modem.endPacket(true);
 Serial.print("Message state: ");
 Serial.println(err);

 switch (err) {
     case -1:
         Serial.println("Timeout");
         break;

     case 1:
         Serial.println("Message sent !");
         break;
     default:
         Serial.print("Error while sending message with code: ");
         Serial.println(err);
         break;
}

 Serial.println();

} 
