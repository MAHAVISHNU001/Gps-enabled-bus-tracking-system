#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//connect to the row pinouts of the keypad
byte rowPins[ROWS] = {2, 3, 4, 5}; //R1,R2,R3,R4
//connect to the column pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9};//C1,C2,C3,C4

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Serial.print("Destination:");
}
 
void loop()
{
  char key_1 = keypad.getKey();
  if (key_1)
   {
    Serial.print(key_1);
    Serial.println("No.of Passengers");
    char key_2 = keypad.getKey();
     if (key_2)
     {
      Serial.print(key_2);
     }
   }
  break;
}
