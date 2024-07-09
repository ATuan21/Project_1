#include <Arduino.h>
#include <rdm6300.h>

#define RDM6300_RX_PIN 3
#define READ_LED_PIN 13

//#define En138 2

#define R1_PIN 4
#define R2_PIN 5
#define R3_PIN 6

/*#define C1_PIN 10
#define C2_PIN 9
#define C3_PIN 8*/


Rdm6300 rdm6300;

void setup() {
  Serial.begin(9600);

  pinMode(READ_LED_PIN, OUTPUT);
  
  pinMode(R1_PIN, OUTPUT);
  pinMode(R2_PIN, OUTPUT);
  pinMode(R3_PIN, OUTPUT);

  /*pinMode(C1_PIN, OUTPUT);
  pinMode(C2_PIN, OUTPUT);
  pinMode(C3_PIN, OUTPUT);*/

  digitalWrite(R1_PIN, 0);
  digitalWrite(R2_PIN, 0);
  digitalWrite(R3_PIN, 0);

  /*digitalWrite(C1_PIN, 0);
  digitalWrite(C2_PIN, 0);
  digitalWrite(C3_PIN, 0);*/

  digitalWrite(READ_LED_PIN, LOW);

  rdm6300.begin(RDM6300_RX_PIN);

  Serial.println("\nPlace RFID tag near the rdm6300...");
}

void loop() {
  for (int i = 0; i < 8; i++) {
    int a = i & 0x01;
    int b = (i & 0x02) >> 1;
    int c = (i & 0x04) >> 2;
//Serial.print("Chuyển trạng thái: ");
    Serial.print(c);
    Serial.print(' ');
    Serial.print(b);
    Serial.print(' ');
    Serial.print(a);
    Serial.println(' ');
    digitalWrite(R1_PIN, a);
    digitalWrite(R2_PIN, b);
    digitalWrite(R3_PIN, c);
    delay(1);
    unsigned long startTime = millis();
    while (millis() - startTime < 60) { 
      uint32_t new_tag_id = rdm6300.get_new_tag_id();
      if (new_tag_id) {
        Serial.println(new_tag_id, DEC);
        digitalWrite(READ_LED_PIN, HIGH);
        delay(10);
        digitalWrite(READ_LED_PIN, LOW);
        break; // Thoát khỏi vòng while nếu tìm thấy thẻ
      }
    }
  }
}  
