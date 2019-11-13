#define INPUT_START 4
#define INPUT_END 20
#define BAUD 57600

bool lastStates [INPUT_END-INPUT_START+1]  ;
bool states [INPUT_END-INPUT_START+1] ;
int inputCount=INPUT_END-INPUT_START;
int statesPrintedCount;
int printHeaderAfter=12;
int delayAfterChange=1;  // add some delay to avoid flickering noise
bool lastBlinkState;

void printHeader()
{
  Serial.print("\r\n");
  for (int i=0;i<inputCount;i++)
  {
   Serial.print(" ");
   if (i+INPUT_START<10) 
    Serial.print(" ");
   Serial.print(i+INPUT_START);
   Serial.print(" ");
  }
  
}


void printState()
{
  Serial.print("\r\n");
  for (int i=0;i<inputCount;i++)
  {
   Serial.print("[");
   if (states[i]) 
    Serial.print("HI"); 
   else 
    Serial.print("--");
   Serial.print("]");
  }
}
  
void setup() 
{
   pinMode(LED_BUILTIN, OUTPUT);
  for (int i=0;i<=inputCount;i++)
  {
    pinMode(i, INPUT_PULLUP);
    states[i]=digitalRead(i);
    lastStates[i]=states[i];
  }
  Serial.begin(BAUD);
  Serial.print("\r\n\r\n");
  Serial.println("InputStateAnalyzer by zambari");
  printHeader();
}


void loop() {
  for (int i=0;i<=inputCount;i++)
  {
    states[i]=digitalRead(i+INPUT_START);
  }
  bool hasChanged=false;
  for (int i=0;i<inputCount;i++)
  {
    if (lastStates[i]!=states[i])
    {
      lastBlinkState=!lastBlinkState;
       digitalWrite(LED_BUILTIN, lastBlinkState);
      hasChanged=true;
      lastStates[i]=states[i];
    }
    
  }
  if (hasChanged)
  {

    statesPrintedCount++;
    if (statesPrintedCount>printHeaderAfter)
    {
      statesPrintedCount=0;
      printHeader();
    }
    printState();
    if(delayAfterChange>0)
      delay(delayAfterChange);
    hasChanged=false;
  }

 }
  
