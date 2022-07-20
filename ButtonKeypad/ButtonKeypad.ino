#include <Keypad.h>

const byte numRows=5; //number of rows on the keypad
const byte numCols=5; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
int keymap[numRows][numCols]=
{
{ 1, 2, 3, 4, 5},
{ 6, 7, 8, 9,10},
{11,12,13,14,15},
{16,17,18,19,20},
{21,22,23,24,25},
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {1,2,3,4,5}; //Rows 0 to 4
byte colPins[numCols]= {6,7,8,9,10}; //Columns 0 to 4

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
char keypressed = myKeypad.getKey();
if (keypressed != NO_KEY)
{
Serial.println(keypressed);
}
}
