#define trigpin1 13 
#define echopin1 12
#define BUZZER_PIN 9
#define ledpin1 10
#define MQ2pin 0

float sensorValue = 0; 
float duration1;
float distance1;
float prevsensorValue = 0;
int count = 0;

void setup()
{
  pinMode(ledpin1, OUTPUT);
  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 test");
  Serial.println("with Arduino Uno R3");
  Serial.println("Gas sensor warming up!");
  delay(5000); // allow the MQ-2 to warm up
  
}

void loop()
{
  
  digitalWrite(trigpin1, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1, LOW);

  duration1 = pulseIn(echopin1, HIGH);
  distance1 = duration1 /58;

  prevsensorValue = sensorValue;
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  delay(1000);

  if(distance1<=16){
      buzz();
  }
  if(count>0){
    if((sensorValue - prevsensorValue) >= 30){
      buzz();
    }
  }
  else{
    count++;
  }
  
}

void buzz(){
  int i = 2;
  while(i>0){
  tone(BUZZER_PIN,2000,500);
  digitalWrite(ledpin1, HIGH);
  delay(500);
  tone(BUZZER_PIN,2000,500);
  digitalWrite(ledpin1, LOW);
  delay(500);
  tone(BUZZER_PIN,2000,500);
  digitalWrite(ledpin1, HIGH);
  delay(500);
  tone(BUZZER_PIN,2000,500);
  digitalWrite(ledpin1, LOW);
  delay(500);
  i--;
  Serial.print("Cycles left in Alarm: ");
  Serial.println(i);
  count++;
  }
}
