#include <IRremote.h> // >v3.0.0
#include <TimeLib.h>

#define PIN_SEND 10
#define KEY_BUTTON_PIN 2
#define DATA_BUTTON_PIN 3
#define LED_PIN 12



IRsend irsend;
int device_addr = 0x69;
int data = 0x10;

void setup()  
{  
  Serial.begin(9600);
  pinMode(KEY_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DATA_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  IrSender.begin(PIN_SEND); // Initializes IR sender
}


void Send_data_with_time()
{
  time_t t = now();
  Serial.println("Current time on sender in seconds: ");
  //Serial.println(t);
  int ts = second(t);
  //Serial.println(second(t));
  Serial.println(ts, HEX);
  int device_addr_time = (device_addr << 8)+ts;
  Serial.println("Device Address + Time in seconds: ");
  Serial.print(device_addr_time, HEX);
  Serial.println();
  Serial.println("\n\n"); 
  IrSender.sendNEC(device_addr_time, 0x10,0);
}
                               
void loop()  
{
  byte key_button_state = digitalRead(KEY_BUTTON_PIN);
  if (key_button_state == LOW)
  {
    Serial.println("Button pressed");
    //unsigned long ttl1 = millis();
    //Serial.println(ttl1);
    unsigned long Time1 = millis();
    
    //send_key();
    Send_data_with_time();
    unsigned long Time2 = millis();
    Serial.print("\nTime taken on Sender: ");
    Serial.println(Time2-Time1);

    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
  }
  //delay(1000)

}  
 