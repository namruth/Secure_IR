#include <IRremote.h>
#define PIN_RECV 2
#define LED_PIN 10
#define LED_PIN2 12

int encr_key = 0;
int counter_initial = 0;
int next_counter = 0;

void setup()  
{  
   Serial.begin(9600); //initialize serial connection to print on the Serial Monitor of the Arduino IDE
   IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object
   pinMode(LED_PIN, OUTPUT);
   pinMode(LED_PIN2, OUTPUT);
   Serial.println("Ready to recieve: ");
}
                           
void loop()  
{    
   if (IrReceiver.decode()) {
    unsigned long Time1 = millis();

     //delay(11000);

    int data = IrReceiver.decodedIRData.command;

    if(data == 0xFF)
    {
      int device_addr_key = IrReceiver.decodedIRData.address ;
      int device_addr = device_addr_key >> 8;
      encr_key = device_addr_key & 0xFF;
      Serial.print("\nDevice address: ");
      Serial.print(device_addr, HEX);
      //encr_key = IrReceiver.decodedIRData.address ;
      Serial.print("\nEncryption Key recieved: ");
      Serial.println(encr_key, HEX);
      digitalWrite(LED_PIN2, HIGH);
      delay(300);
      digitalWrite(LED_PIN2, LOW);   
      counter_initial = 0;
      //Serial.print(encr_key, HEX);
      IrReceiver.resume(); // Important, enables to receive the next IR signal

    }
    else
    {
      int counter_extracted = IrReceiver.decodedIRData.address;
      if (counter_initial == 0)
      {
        counter_initial = counter_extracted;
        Serial.println("Initial random counter set as: ");
        Serial.print(counter_initial);
      }
      else
      {
        if(counter_extracted != next_counter)
        {
          digitalWrite(LED_PIN, HIGH);
          delay(300);
          Serial.println("=========REPLAY ATTACK==========");
          Serial.print("\nCounter extracted: ");
          Serial.print(counter_extracted, HEX);
          Serial.println("\nNext counter expected: ");
          Serial.println(next_counter, HEX);
          digitalWrite(LED_PIN, LOW);
          goto next;          
        }
      }
      
      digitalWrite(LED_PIN2, HIGH);
      delay(300);
      digitalWrite(LED_PIN2, LOW);          
      
      
      Serial.print("\nData recieved: ");
      Serial.print(data, HEX);
      Serial.print("\nCounter extracted: ");
      Serial.print(counter_extracted, HEX);      
      next_counter = counter_extracted+0x1;
      if((counter_extracted + encr_key) == 0xFF)
      {
        next_counter = 0x1;
      }
      Serial.println("\nNext counter expected: ");
      Serial.print(next_counter, HEX);
      if(encr_key == 0)
      {
         Serial.println("\nEncryption key not found");
      }
      else
      {
         int key_decr = encr_key+counter_extracted;  //256
         int data_decr = key_decr^data;    // 100
         Serial.print("\nDecrypted data: ");
         Serial.print(data_decr, HEX);
         Serial.println("\n\n");
         //delay(3000);
         //if(data_decr != 0x10)
         //{
          // Serial.println("==============Wrong data============");
          // exit(0);
         //}
      }
      
    next: 
     IrReceiver.resume(); // Important, enables to receive the next IR signal
    unsigned long Time2 = millis();
    Serial.print("\nTime taken on reciever: ");
    Serial.println(Time2-Time1);
    }
   }  
}  