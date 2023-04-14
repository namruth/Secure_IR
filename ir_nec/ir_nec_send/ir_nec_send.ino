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
                               
void loop()  
{
  byte key_button_state = digitalRead(KEY_BUTTON_PIN);
  if (key_button_state == LOW)
  {
    Serial.println("Button pressed");
    //Serial.println(device_addr, HEX);
    //Serial.println(data, HEX);
    unsigned long Time1 = millis();
    IrSender.sendNEC(device_addr, data,0);
    unsigned long Time2 = millis();
    Serial.print("\nTime taken on Sender: ");
    Serial.println(Time2-Time1);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
  }
}  
 