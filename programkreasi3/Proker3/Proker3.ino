int lampu=2;

void setup () {
  Serial.begin(9600);
  pinMode(lampu,OUTPUT);
}

void loop (){
  digitalWrite(lampu,HIGH);
  delay(5000);
  digitalWrite(lampu,LOW);
  delay(1000);
}