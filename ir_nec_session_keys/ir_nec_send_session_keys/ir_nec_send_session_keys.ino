#include <IRremote.h> // >v3.0.0

#define PIN_SEND 10
#define KEY_BUTTON_PIN 2
#define DATA_BUTTON_PIN 3
#define LED_PIN 12



IRsend irsend;
int encr_key = 0;
int counter = 0;
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

void send_key()
{  
  //Serial.println("\n\n");
  randomSeed(analogRead(A0));   
  encr_key = random(1,253);
  //encr_key = 0x27;
  Serial.print("Sending key: ");
  Serial.println(encr_key, HEX);
  int device_addr_key = (device_addr << 8)+encr_key;
  Serial.println("Device Address + Key: ");
  Serial.print(device_addr_key, HEX);
  Serial.println();
  Serial.println("\n\n"); 
  IrSender.sendNEC(device_addr_key, 0xFF,0);
  //IrSender.sendNEC(encr_key, 0xFF,0);
}


void send_data()
{
  //Serial.println("\n\n\n");
  Serial.println("Counter for this iteration: ");
  Serial.print(counter, HEX); //146
  Serial.println();
  int key_up = encr_key + counter; //256 

  int data_enc = data ^ key_up;   //356
  Serial.print("Sending encrypted data: ");
  Serial.print(data_enc, HEX);
  Serial.println();
  Serial.println("\n\n"); 

  IrSender.sendNEC(counter, data_enc,0);
  if ((encr_key+counter) == 0xFF)
  {
    counter = 0x1;
  }
  else
  {
  counter += 0x1;
  }
}
                               
void loop()  
{
  byte key_button_state = digitalRead(KEY_BUTTON_PIN);
  if (encr_key == 0)
  {
  if (key_button_state == LOW)
  {
    Serial.println("Key button pressed");
    send_key();
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
  }
  counter = random(1,255-encr_key);
  //delay(500);
  }
 
  
  byte data_button_state = digitalRead(DATA_BUTTON_PIN);
  if (data_button_state == LOW)
  {
    Serial.println("Data button pressed and sending data");
    unsigned long Time1 = millis();
    send_data();
    unsigned long Time2 = millis();
    Serial.print("\nTime taken on Sender: ");
    Serial.println(Time2-Time1);

    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);      
  }
  //delay(100);
}  
 