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

/* 
    -- VERIFY THIS: -- 
    D4 - D8  =>  ROWS [INPUT_PULLUP]
    D9 - D13 =>  COLS [OUTPUT]
    A0 - A5  =>  POTS [INPUT]
*/

void setup() 
{
  Serial.begin(9600);
  for(int i=9; i>=4; i--)
  {
    pinMode(i, OUTPUT); //ROWS = OUTPUT
    digitalWrite(i, LOW);
  }
  
  for(int i=13; i>=8; i--)
  {
    pinMode(i, INPUT); //COLS = INPUT_PULLUP
  }
}

void loop() 
{
  //delay(3); //process delay
  for(int i=4; i<9; i++) //for each row: if key pressed, output x value
  {
      rowScan(i); 
      for(int j=9; j<14; j++) //for each column: if key pressed, read y value
      {
        colRead(j); 
        //Serial.println(digitalRead(j));
        if(foundCol)
        {
           Serial.println(keys[i-4][j-9]); //print played key number
           //Serial.println(keyNames[i-4][j-9]); //print played key name
        } 
      } 
  }
}

void rowScan(int x)
{
  for(int j=4; j<9; j++)
  {
    digitalWrite(j, HIGH);
  }
  digitalWrite(x, LOW); //one row at a time!
}

//void rowScan(int x) 
//{
//  digitalWrite(x, HIGH);
//  digitalWrite(x-1, LOW); //one row at a time!
//}

void colRead(int x)
{
  pinMode(x, INPUT_PULLUP);
  colVal = digitalRead(x);
  pinMode(x, INPUT);
  
  if(colVal == 1)
  {
     foundCol = true;
  }
  else
  {
     foundCol = false;
  }
}
