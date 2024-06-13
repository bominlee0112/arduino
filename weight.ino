#include "HX711.h"

#define DOUT 3        // 데이터 출력 핀
#define CLK 4         // 클럭 핀
#define BUZZER_PIN 5  // 부저 핀
#define RAW_THRESHOLD 1000  // 원시 데이터 임계값

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);
  pinMode(BUZZER_PIN, OUTPUT);  // 부저 핀을 출력 모드로 설정

  Serial.println("Calibrating... Please wait.");
  delay(2000);  // 초기 안정화 시간을 줌
  scale.tare(); // 초기 기준점 설정

  long baseReading = scale.get_units(10);  // 초기 기준값 설정 (10번 평균 측정)
  Serial.print("Base reading: ");
  Serial.println(baseReading);  // 초기값을 SERIAL MONITOR에 출력
}

void loop() {
  long currentReading = scale.get_units(5);  // 현재 값을 5번 평균 측정

  if (currentReading > RAW_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);  // 데이터가 임계값을 초과하면 부저를 울림
    tone(BUZZER_PIN, 252, 1000);
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // 그렇지 않으면 부저를 끔
  }

  delay(1000);  // 1초 간격으로 상태 확인
}