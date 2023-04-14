#include <IRremote.h>
#include <TimeLib.h>

#define PIN_RECV 2
#define LED_PIN 12
#define LED_PIN2 10

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

    //Serial.println("Current time in seconds: ");
    //Serial.println(t);  
   if (IrReceiver.decode()) {
    unsigned long Time1 = millis();

    time_t t = now();
     
    int tr = second(t);
    Serial.print("\nCurrent time on reciever: ");
    Serial.println(tr, HEX); 
    
    int data = IrReceiver.decodedIRData.command;

    int device_addr_time = IrReceiver.decodedIRData.address ;
    int device_addr = device_addr_time >> 8;
    int ts = device_addr_time & 0xFF;

    //Serial.print("\nDevice address: ");
    //Serial.print(device_addr, HEX);
    //Serial.print("\nSender Time recieved: ");
    //Serial.println(ts, HEX);

    //Serial.print("\nTime difference: ");
    //Serial.println(tr-ts);

    if((tr - ts) >= 2)
    {
      Serial.println("=======REPLAY ATTACK======");
      digitalWrite(LED_PIN2, HIGH);
      delay(300);
      digitalWrite(LED_PIN2, LOW); 
    }
    else
    {
      Serial.println("Data recieved sucessfully");
      digitalWrite(LED_PIN, HIGH);
      delay(300);
      digitalWrite(LED_PIN, LOW);
    }
    //digitalWrite(LED_PIN2, HIGH);
    //delay(1000);
    //digitalWrite(LED_PIN2, LOW);   
     IrReceiver.resume(); // Important, enables to receive the next IR signal
     unsigned long Time2 = millis();
    Serial.print("\nTime taken on reciever: ");
    Serial.println(Time2-Time1);
   }
   //delay(1000);  
}  