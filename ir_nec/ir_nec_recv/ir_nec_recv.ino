#include <IRremote.h>
#include <TimeLib.h>

#define PIN_RECV 2
#define LED_PIN 12


void setup()  
{  
   Serial.begin(9600); //initialize serial connection to print on the Serial Monitor of the Arduino IDE
   IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object
   pinMode(LED_PIN, OUTPUT);
   Serial.println("Ready to recieve: ");
}
                           
void loop()  
{  
   if (IrReceiver.decode()) {
    unsigned long Time1 = millis();
    
    int data = IrReceiver.decodedIRData.command;

    int device_addr = IrReceiver.decodedIRData.address ;

    //Serial.print("\nDevice address: ");
    //Serial.print(device_addr, HEX);
    //Serial.print("\nData recieved: ");
    //Serial.println(data, HEX);

    //Serial.println("Data recieved sucessfully");
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    IrReceiver.resume(); // Important, enables to receive the next IR signal
    unsigned long Time2 = millis();
    Serial.print("\nTime taken on reciever: ");
    Serial.println(Time2-Time1);
   }
}  