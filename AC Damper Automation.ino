
All of the functions used in this program are labeled and 
placed above the MAIN loop. There is one block of code below
MAIN that is done through interrupts and
so I placed it below MAIN






                             HEADERS

#include rotary.h
#include SimpleTimer.h
#include Servo.h 
#include OneWire.h used for DS18B20 1-wire digital temperature sensors
#include DallasTemperature.h Library for handling the input of the temperature
#include Wire.h
#include Adafruit_LEDBackpack.h
#include Adafruit_GFX.h




                        #DEFINE THINGS

1-wire I2C in this pin
#define ONE_WIRE_BUS 12 
#define NumberOfDevices 50         
Matrixes
#define LEFT 0
#define MID 1
#define RIGHT 2
Servo Positions
#define CLOSED_POS 0
#define OPEN_POS 90
Servo Locations
#define R_ONE_LOC 7 
#define R_TWO_LOC 9
#define R_THREE_LOC 11
#define I_ONE_LOC 8
#define I_TWO_LOC 10
#define I_THREE_LOC 12

#define encoder0PinA  2
#define encoder0PinB  3





                 1-WIRE TEMPERATURE CREATION

 Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
 Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);




                            GLOBALS


           SERVOS          
Servo rOne;
Servo rTwo;
Servo rThree;
Servo iOne;
Servo iTwo;
Servo iThree;

        Rotary Encoder       
Rotary r = Rotary(encoder0PinA,encoder0PinB);
volatile int encoderSwitchPin = 4; push button switch

         Temp Var's          
byte roomArray[NumberOfDevices][8];
float lastTemp = 0.0;
float diffTemp = 0.0;
int tempRoomOne = 75;
int tempRoomTwo;
int tempRoomThree;
boolean tempTwoFlag = FALSE;
boolean tempThreeFlag = FALSE;
This is a timing var to decide whether to check the temp
int tempPol = 0;  

            MENU            
boolean menuFlag = FALSE;
boolean resetScrolled = FALSE;
int menuType = 0;
int menuPick = 1;
int starttime = 0;
int floorSel = 1;
int resetVal = 1;

        LED MATRIXES       
Adafruit_8x8matrix matrix[3] = (Adafruit_8x8matrix(),Adafruit_8x8matrix(),Adafruit_8x8matrix()) ;
int tens=7;
int ones=5;
int tensFloor;
int onesFloor;
int mLeft = 1;
int mMid = 2;
int mRight = 3;
int flash = 0;
         LED Display        
 defines 8x8 ASCII characters needed (i.e. 0-9 and °C)

static const uint8_t PROGMEM

zero[] = { 0x3c, 0x66, 0x76, 0x7e, 0x6e, 0x66, 0x3c, 0x00 },    0 
one[] = { 0x18, 0x78, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00 },     1 
two[] = { 0x3c, 0x66, 0x06, 0x1c, 0x30, 0x66, 0x7e, 0x00 },     2 
three[] = { 0x3c, 0x66, 0x06, 0x1c, 0x06, 0x66, 0x3c, 0x00 },   3 
four[] = { 0x0c, 0x1c, 0x34, 0x64, 0x66, 0x7e, 0x04, 0x00 },    4 
five[] = { 0x7e, 0x60, 0x3e, 0x06, 0x06, 0x66, 0x3c, 0x00 },    5
six[] = { 0x1c, 0x30, 0x60, 0x7c, 0x66, 0x66, 0x3c, 0x00 },     6
seven[] = { 0x7e, 0x66, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x00 },   7 
eight[] = { 0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x3c, 0x00 },   8 
nine[] = { 0x3c, 0x66, 0x66, 0x3e, 0x06, 0x0c, 0x38, 0x00 },    9

Off[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  OFF
celsius[] = { 0xe0, 0xa0, 0xe0, 0x0f, 0x08, 0x08, 0x08, 0x0f },  °C
farhen[] = { 0xe0, 0xa0, 0xe0, 0x0f, 0x08, 0x0e, 0x08, 0x08 };   °F






                            SETUP

void setup() {
  Serial.begin(9600);
  get the temp sensors addresses
  discoverOneWireDevices();
  sensors.begin();
  tempRoomTwo = tempRoomOne;
  tempRoomThree = tempRoomOne;
  attach servos to pin locations
  rOne.attach(R_ONE_LOC);
  iOne.attach(I_ONE_LOC);
  rTwo.attach(R_TWO_LOC);
  iTwo.attach(I_TWO_LOC);  
  rThree.attach(R_THREE_LOC);
  iThree.attach(I_THREE_LOC);
 Initiallize the Matrixes
  for(uint8_t i=0; i3; i++) {
    matrix[i].begin(0x70 + i);
    matrix[i].setTextSize(1);
    matrix[i].setTextWrap(false);  Allow text to run off edges
    matrix[i].setBrightness(0);
    matrix[i].setTextColor(LED_ON);
  }
  for(int i = 0; i = (sizeof(roomArray)8); i++){
    sensors.setResolution(roomArray[i], 10);
  }
  pinMode(encoderSwitchPin, INPUT);
  digitalWrite(encoderSwitchPin, HIGH); turn pullup resistor on
  attachInterrupt(0, Encoder, CHANGE);   encoder pin on interrupt 0 - pin 2
  attachInterrupt(1, Encoder, CHANGE);   encoder pin on interrupt 0 - pin 2

}



                 GRAB TEMPERPATURE SENSORS
This function should only be done once at the beginning of
the program.  During Setup it will look for all temp sensors
and collect their addresses into an array.  This is done
so that more sensors can be added and would require only
a powercycle of the thermostat.  We could also (later), set
it as a function in the menu to manually search without 
a powercycle.               

void discoverOneWireDevices(void) {
  byte j, i, numDevices = 0;
  byte addr[8];
  
  while(oneWire.search(addr)) {
    for(j=0; jNumberOfDevices;j++){
      for(i = 0; i  8; i++) {
        roomArray[j][i] = addr[i];
      }
      if (OneWirecrc8( addr, 7) != addr[7]) {
          Serial.print(CRC is not valid!n);
          return;
      }
    }
  }
  return;
}




                    CHECKING THE TEMPERATURE

void checkTemperature(){
  for( int i =0; i (sizeof(roomArray)8); i++ ){
    float tempC = sensors.getTempC(roomArray[i]);
    float tempF;
    if(tempC == -127.00){
      Serial.print(Err);
    }
    else{
      tempF = tempC1.8 + 32;
      diffTemp = lastTemp - tempF;
      if(diffTemp = -2){
        Save servo
      }
      else if(diffTemp = 2){
        save servo
      } 
    }    
  }
}




          WHAT TO DO WITH A BUTTON PRESS

void button(){   
   delay(150);
   switch (menuPick){
     case 1
        menuFlag = TRUE;
        menuType = 1;
        break;
     case 2
        menuType = 2;
        break;
     case 3
        menuType = 3;
        break;
     case 4
       menuType = 4;
       break;
     default
       menuType = 0;
       break;
   }  
}



                 CHANGE MATRIX TEMP

void ChangeMatrixTemp(){
  matrix[LEFT].clear();
  matrix[MID].clear();
  matrix[RIGHT].clear();
  matrix[LEFT].setCursor(2,0);
  matrix[LEFT].print(tens);
  matrix[MID].setCursor(0,0);
  matrix[MID].print(ones);
  matrix[RIGHT].setCursor(1,0);
  matrix[RIGHT].drawBitmap(0,0,farhen,8,8,LED_ON);
  matrix[LEFT].writeDisplay();
  matrix[MID].writeDisplay();
  matrix[RIGHT].writeDisplay();
  delay(90);
}



                 CHANGE MATRIX FLOOR

void ChangeMatrixFloors(){
  if ((flash % 2) == 0){
    matrix[LEFT].clear();
    matrix[MID].clear();
    matrix[RIGHT].clear();
    matrix[LEFT].setCursor(1,0);
    matrix[LEFT].print(mLeft);
    matrix[MID].setCursor(1,0);
    matrix[MID].print(mMid);
    matrix[RIGHT].setCursor(1,0);
    matrix[RIGHT].print(mRight);
    matrix[LEFT].writeDisplay();
    matrix[MID].writeDisplay();
    matrix[RIGHT].writeDisplay();
    delay(90);
  }
}



                 CHANGE MATRIX FLOOR TEMP

void ChangeMatrixFloorTemp(){
  if ((floorSel-1) == LEFT){
    tensFloor = tempRoomOne  10;
    onesFloor = tempRoomOne % 10;
  }
  else if ((floorSel-1) == MID){
    tensFloor = tempRoomTwo  10;
    onesFloor = tempRoomTwo % 10;
    Serial.println(Menu True);
    tempTwoFlag = TRUE;
  }
  else if ((floorSel-1) == RIGHT){
    tensFloor = tempRoomThree  10;
    onesFloor = tempRoomThree % 10;
        Serial.println(Menu True);
    tempThreeFlag = TRUE;
  }
  matrix[LEFT].clear();
  matrix[MID].clear();
  matrix[RIGHT].clear();
  matrix[LEFT].setCursor(2,0);
  matrix[LEFT].print(tensFloor);
  matrix[MID].setCursor(0,0);
  matrix[MID].print(onesFloor);
  matrix[RIGHT].setCursor(1,0);
  matrix[RIGHT].drawBitmap(0,0,farhen,8,8,LED_ON);
  matrix[LEFT].writeDisplay();
  matrix[MID].writeDisplay();
  matrix[RIGHT].writeDisplay();
  delay(90);
}



               DECIDE TO RESET FLOOR TEMPS


void ResetFloorValDecide(){
    if(!resetScrolled){
      matrix[LEFT].clear();
      matrix[MID].clear();
      matrix[RIGHT].clear();
      matrix[LEFT].writeDisplay();
      matrix[MID].writeDisplay();
      matrix[RIGHT].writeDisplay();

      int8_t y=7, z=7;
      for (int8_t x=8; x=-45; x--) {
        matrix[RIGHT].clear();
        matrix[RIGHT].setCursor(x,0);
        matrix[RIGHT].print(RESET);
        matrix[RIGHT].writeDisplay();
        if (x = -1){
          matrix[MID].clear();
          matrix[MID].setCursor(y,0);
          matrix[MID].print(RESET);
          matrix[MID].writeDisplay();
          y--;  
        }  
        if (x = -9){
          matrix[LEFT].clear();
          matrix[LEFT].setCursor(z,0);
          matrix[LEFT].print(RESET);
          matrix[LEFT].writeDisplay();
          z--;
        }
        delay(45);
        if(x == -45){
          resetScrolled = TRUE;
        }
      }     
    }
    else if(resetScrolled){
      if ((flash % 2) == 0){
        Serial.println(ShouldFlash);
        matrix[LEFT].setCursor(2,0);
        matrix[LEFT].print(Y);
        matrix[LEFT].writeDisplay();
        matrix[RIGHT].setCursor(2,0);
        matrix[RIGHT].print(N);
        matrix[RIGHT].writeDisplay();
      }
    }
  }



                   RESET MENU VAR


void ResetMenu(){
    starttime = 0;
    menuType = 0;
    menuFlag = FALSE;
    menuPick = 0;
    resetScrolled = FALSE;
  } 



                   MAIN LOOP


void loop() {
  boolean buttonBreak = FALSE;
  if(digitalRead(encoderSwitchPin) == HIGH){
  }
  else{
    if(menuType == 0){
      menuPick = 1;
    }
    button();
  }   
  if(menuType == 0){
    ChangeMatrixTemp();
  }
  else if(menuType == 1){
    ChangeMatrixFloors();
    while(starttime  800){
      Serial.println(starttime);
      if ((starttime % 100) == 0){
        matrix[floorSel-1].clear();
        matrix[floorSel-1].drawBitmap(0,0,Off,8,8,LED_ON);
        matrix[floorSel-1].writeDisplay();
        flash++;
        ChangeMatrixFloors();
      }
      if (!(digitalRead(encoderSwitchPin) == HIGH)){
        Serial.println(BUTTON);
        buttonBreak = TRUE;
        menuPick = 2;
        starttime = 0; 
        goto Button;        
      }  
      starttime++;
    }  do this loop for up to 4 seconds
    ResetMenu();
  } 
  else if(menuType == 2){
    ChangeMatrixFloorTemp();
    while(starttime  45) {
      Serial.println(starttime);
      ChangeMatrixFloorTemp();
      if (!(digitalRead(encoderSwitchPin) == HIGH)){
        Serial.println(BUTTON);
        buttonBreak = TRUE;
        menuPick = 3;
        starttime = 0; 
        goto Button;        
      }  
      starttime++;
    }  do this loop for up to 4 seconds
    ResetMenu();
  } 
  else if(menuType == 3){
    ResetFloorValDecide();
    while(starttime  800){
      Serial.println(starttime);
      if ((starttime % 100) == 0){
        matrix[resetVal].clear();
        matrix[resetVal].drawBitmap(0,0,Off,8,8,LED_ON);
        matrix[resetVal].writeDisplay();
        flash++;
        ResetFloorValDecide();
      }
      if (!(digitalRead(encoderSwitchPin) == HIGH)){
        Serial.println(BUTTON);
        menuPick = 4;
        starttime = 0; 
        goto ResetFloorVal; 
      }  
      starttime++;
    }  do this loop for up to 4 seconds
    ResetMenu();
  }
  else{
    ResetMenu();
  }
  if(tempPol == 10000){
    sensors.requestTemperatures();
    checkTemperature();
    tempPol = 0;
  }
  else{
    tempPol++;
  }
Button if(buttonBreak){
            buttonBreak = FALSE;
            button();
        }
ResetFloorVal if(resetVal == 0){
                 resetVal = 1;
                 tempRoomTwo = tempRoomOne;
                 tempRoomThree = tempRoomOne;
                 Serial.println(Menu RESET False);
                 tempTwoFlag = FALSE;
                 tempThreeFlag = FALSE;
                 button();
               }
}



          WHAT TO DO WITH TURNING THE ENCODER

     
       This section is for changing the degrees
       when you have not entered the menu
     
void Encoder(){
  unsigned char result = r.process();
  if (!menuFlag){
    if (result) {
      if (tempRoomOne == 59 && result == DIR_CCW){
        Serial.println(tempRoomOne);
      }
     else if (tempRoomOne == 85 && result == DIR_CW){
        Serial.println(tempRoomOne);
      }  
      else{
        Serial.println(result == DIR_CW  ++tempRoomOne  --tempRoomOne);
      }  
      tens = tempRoomOne  10;
      ones = tempRoomOne % 10;
      
      if (tempTwoFlag == FALSE){
        Serial.println(Menu Found False);
        tempRoomTwo = tempRoomOne;
      }
      if (tempThreeFlag == FALSE){
        Serial.println(Menu Found False);
        tempRoomThree = tempRoomOne;
      }
    }
  }
  
     
           This section is for picking floors
     
     
  else{
    if(menuType == 1){
      if(result){process the floor changes  
        starttime = 0;   
        delay(100);
        if (floorSel == 1 && result == DIR_CCW){
          Serial.println(floorSel);
        }
        else if (floorSel == 3 && result == DIR_CW){
          Serial.println(floorSel);
        }  
        else{
          Serial.println(result == DIR_CW  ++floorSel  --floorSel);
        }  
      }
    }  
        
        
               This section if to show the temp
               from the floor selected above.
        
        
   else if (menuType == 2){
     starttime = 0;   
     switch (floorSel){
       case 1
          if (result) {
            if (tempRoomOne == 59 && result == DIR_CCW){
              Serial.println(tempRoomOne);
            }
            else if (tempRoomOne == 85 && result == DIR_CW){
              Serial.println(tempRoomOne);
            }  
            else{
              Serial.println(result == DIR_CW  ++tempRoomOne  --tempRoomOne);
            }  
         } 
         break;
       case 2
         if (result) {
           if (tempRoomTwo == 59 && result == DIR_CCW){
             Serial.println(tempRoomTwo);
           }
           else if (tempRoomTwo == 85 && result == DIR_CW){
             Serial.println(tempRoomTwo);
           }  
           else{
             Serial.println(result == DIR_CW  ++tempRoomTwo  --tempRoomTwo);
           } 
         }
         break;
       case 3
         if (result) {
           if (tempRoomThree == 59 && result == DIR_CCW){
             Serial.println(tempRoomThree);
           }
           else if (tempRoomThree == 85 && result == DIR_CW){
             Serial.println(tempRoomThree);
           }  
           else{
             Serial.println(result == DIR_CW  ++tempRoomThree  --tempRoomThree);
           } 
         }
       break;      
       }  
     }
        
               Change the Temp setting for the 
               individual floor that was selected
            
        
   else if (menuType == 3){
     if(result){process the floor changes  
       starttime = 0;   
       delay(100);
       if (result == DIR_CCW){
         resetVal = LEFT;
         Serial.println(floorSel);
       }
       else if (result == DIR_CW){
         resetVal = RIGHT;
         Serial.println(floorSel);
       }     
     }     
   } 
}
}

