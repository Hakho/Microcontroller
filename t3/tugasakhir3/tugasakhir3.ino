int pbuttonPin = 13;// connect output to push button
int relayPin = 3;// Connected to relay (LED)
int val = 13; // push value from pin 13
int lightON = 0;//light status
int pushed = 0;//push status


void setup() {
  Serial.begin(9600);
  pinMode(pbuttonPin, INPUT_PULLUP); 
  pinMode(relayPin, OUTPUT);
 digitalWrite(relayPin, HIGH);
}

void loop() {
  val = digitalRead(pbuttonPin);
  if(val == HIGH && lightON == LOW){
    pushed = 1-pushed;
    delay(100);
  }    
  lightON = val;

      if(pushed == HIGH){
        Serial.println("Light ON");
        digitalWrite(relayPin, LOW); 
        delay(200);
        digitalWrite(relayPin, HIGH); 
        delay(200);
        digitalWrite(relayPin, LOW); 
       
      }else{
        Serial.println("Light OFF");
        digitalWrite(relayPin, HIGH);
   
      }     
  delay(100);
}
