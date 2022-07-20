bool foundCol = false;

int colVal=0;
byte buttons[10] = {4,5,6,7,8,9,10,11,12,13}; //9 will be used for Mozzi speakers later on - it is fine for now
byte keys[5][5] = {
                        {1,2,3,4,5},
                       {6,7,8,9,10},
                   {11,12,13,14,15},
                   {16,17,18,19,20},
                   {21,22,23,24,25},
                 };

String keyNames[5][5] = {
                   {"C","C#","D","D#","E"},
                   {"F","F#","G","G#","A"},
                   {"A#","B","C","C#","D"},
                   {"D#","E","F","F#","G"},
                   {"G#","A","A#","B","C"},
                 };

float f[5][5] = {
                  {262, 277, 294, 311, 330},
                  {349, 370, 392, 415, 440},
                  {466, 494, 523, 554, 587},
                  {622, 659, 698, 740, 784},
                  {831, 880, 932, 988, 1050},
                }; // 3sf

/* 
      -- DEFINITIONS -- 
    
    D4 - D8  =>  ROWS [OUTPUT]
    D9 - D13 =>  COLS [INPUT]
    A0 - A5  =>  POTS [INPUT]
*/

void setup() 
{
  Serial.begin(9600);
  for(int i=4; i<9; i++)
  {
    pinMode(i, OUTPUT); //ROWS = OUTPUT
    digitalWrite(i, HIGH);
  }
  
  for(int i=9; i<14; i++)
  {
    pinMode(i, INPUT_PULLUP); //COLS = INPUT_PULLUP
  }
}

void loop() 
{
  rowWrite();
  //delay(3); //process delay
//  for(int i=4; i<9; i++) //for each row: if key pressed, output x value //or possibly for each key?
//  {
//      rowWrite(i); 
//      for(int j=9; j<14; j++) //for each column: if key pressed, read y value
//      {
//        colRead(j); 
//        Serial.print("Scanning column ");
//        Serial.println(j-4);
//        //Serial.println(digitalRead(j));
//        if(foundCol)
//        {
//           //Serial.println(keys[i-4][j-9]); //print played key number
//           //Serial.println(keyNames[i-4][j-9]); //print played key name
//           tone(2, f[i-4][j-9]);
//           //tone(3, f[i-4][j-9]);
//           delay(5);
//        } 
//      }
}

void colRead()
{
  for(int j=9; j<14; j++)
  {
  //pinMode(x, INPUT_PULLUP);
    colVal = digitalRead(j);
//    Serial.print("Scanning column ");
//    Serial.println(j-9);
  //pinMode(x, INPUT);
  }
  if(colVal == 0)
  {
     foundCol = true;
     //Serial.println(" -- KEY FOUND -- ");
  }
  else
  {
     foundCol = false;
  }
}

void rowWrite()
{
  for(int j=4; j<9; j++)
  {
    digitalWrite(j, LOW); //write LOW, not HIGH
    Serial.print("Setting row ");
    Serial.println(j-4);
    colRead();
    digitalWrite(j, HIGH); //reset row count
  }
}
