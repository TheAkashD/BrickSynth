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
    D9 - D13 =>  COLS [INPUT_PULLUP]
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

void rowWrite()
{
  for(int i=4; i<9; i++)
  {
    digitalWrite(i, LOW); //write LOW, not HIGH
    //Serial.print("Setting row ");
    //Serial.println(i-4);
    
    for(int j=9; j<14; j++)
      {
        colVal = digitalRead(j);
        //Serial.print("Scanning column ");
        //Serial.println(j-9);

        if(colVal == 0)
        {
         foundCol = true;
        }
        else
        {
         foundCol = false;
        }
        
        if(foundCol)
        {
           Serial.println(keys[i-4][j-9]); //print played key number
           //Serial.println(keyNames[i-4][j-9]); //print played key name
           tone(2, f[i-4][j-9]);
           tone(3, f[i-4][j-9]);
        } 
      }
    digitalWrite(i, HIGH); //reset row count
  }
}

void loop() 
{
  rowWrite();
  delay(100);
}
