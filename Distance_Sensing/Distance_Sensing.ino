int trig = 5;
int echo = A0;
int distance;
int warn = 0;

int ledPin = 11;
int ledVal = 0;
int way = 0;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trig, HIGH);
  delay(100);
  digitalWrite(trig, LOW);  
  distance = pulseIn(echo, HIGH);
  if(distance < 1000 && distance > 0){
    warn = 1;
  }else{
    warn = 0;
  }
//  delay(50);

  if(ledVal == 240){
    way = 1;//down
  }else if(ledVal == 0){
    way = 0;//up
  }

  if(way == 0){
    ledVal += 8;//up
  }else if(way == 1){
    ledVal -= 8;//down
  }

  if(warn == 1){
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }else{
    analogWrite(ledPin, ledVal);
  }
  
//  Serial.print(warn);
  Serial.print(distance);
  Serial.print("\n");
  delay(100);
}
