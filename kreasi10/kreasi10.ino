#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
const int led=10;
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  switch(customKey){
    case '1':
      kedip(1);
      break;
    case '2':
      kedip(2);
      break;
    case '3':
      kedip(3);
      break;
    case '4':
      kedip(4);
      break;
    case '5':
      kedip(5);
      break;
    case '6':
      kedip(6);
      break;
    case '7':
      kedip(7);
      break;
    case '8':
      kedip(8);
      break;
    case '9':
      kedip(9);
      break;
    default:
      break;
  }
}

void kedip(int jumlah){
  for(int i=1; i<=jumlah; i++){
    digitalWrite(led,HIGH);
    delay(400);
    digitalWrite(led,LOW);
    delay(200);
  }
}

