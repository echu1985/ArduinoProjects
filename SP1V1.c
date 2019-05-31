//#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <LCDBitmap.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
LCDBitmap bitmap(&lcd, 0, 0);  // Set the bitmap to the &lcd display at character position 0,0.
//RANDOM INT randomNumber;
int valves[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 34, 36}; //Enter the number of the pins being used
int RNum = 0;

//Botones set de pines
byte buttons[] = {48,50,52}; 
const byte nrButtons = 3;

//Set menu Funciones
int menusize = 16;
bool state_1 = LOW; 
bool state_2 = HIGH; 
String menu[] = {
  "Menu",                               //0
  "Menu>Prueba",                          //1
  "Menu>Prueba>Encender todo",             //2
  "Menu>Prueba>Apagar Todo",               //3
  "Menu>Show1",                           //4
  "Menu>Show1>On",                       //5
  "Menu>Show1>Off",                       //6
  "Menu>Show2",                          //7
  "Menu>Show2>On",                       //8
  "Menu>Show2>Off",                      //9
  "Menu>Random",                         //10
  "Menu>Random>On",                      //11
  "Menu>Random>Off",                     //12
  "Menu>Corrida",                            //13
  "Menu>Corrida>On",                        //14
  "Menu>Corrida>Off",                      //15
  "Menu>Apagar",                       //16
};

int t;
byte pressedButton, currentPos,currentPosParent, possiblePos[20], possiblePosCount, possiblePosScroll = 0;
String parent = "";

unsigned long timer = (millis() / 30);
int mode = 0;

//Delays Ciclos
int modeDelay = 20000;  //Tiempo de shows(encendido y apagado valvulas)
unsigned int delayloop = 30000;   //Tiempo de Corrida (encendido y apagado valvulas secuenciador)
unsigned int delaycen = 60000;   //Tiempo de Centrales (Tiempo encendido picos centrales SHOW2)

int actualdelay = delayloop;  //Define el tiempo de duracion del paso actual dentro de un show. Por defecto
                              //hay que setearlo a delayloop
unsigned int showloopcount = 0;  //Contador de los ciclos de un show. Resetea al llegar a delayloop
int showstep = 0;       //Paso actual dentro de un show


void updateMenu () {
  possiblePosCount = 0;
  while (possiblePosCount == 0) {
    
    for (t = 1; t < menusize;t++) {
      if (mid(menu[t],1,inStrRev(menu[t],">")-1).equals(menu[currentPos])) {
        possiblePos[possiblePosCount]  =  t;
        possiblePosCount = possiblePosCount + 1;
      }
    }
    
    //find the current parent for the current menu
    parent = mid(menu[currentPos],1,inStrRev(menu[currentPos],">")-1);
    currentPosParent = 0;
    for (t = 0; t < menusize; t++) {
       if (parent == menu[t]) {currentPosParent = t;}
    }

    // reached the end of the Menu line
    if (possiblePosCount == 0) {
    //Menu Option Items
      switch (currentPos) {
        
        case 2: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";
       
        break;
        case 3: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";
          
        break;
          case 5: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";

          break;
          case 6: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";

          break;
          case 8: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";

          break;
          case 9: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";
        
          break;
          case 11: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";

          break;
          case 12: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";

          break;
          case 14: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";

          break;
          case 15: //Choose between 
          for (t = 2; t<16; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";
      }


      //Set Variables  // Case 0-1 Test ONOFF
      switch (currentPos) {
        case 2:               //PRENDETODO
          mode = 1;
          cleanshow();
          break;
        case 3:               //APAGATODO
          mode = 0;
          cleanshow();
          break;
        case 5:                 //SHOW1 ON
          mode = 2;
          cleanshow();
          break;
        case 6:                 //SHOW1 OFF
          mode = 0;
          cleanshow();
          break;
        case 8:                  //SHOW2 ON
          mode = 3;
          cleanshow();
          break;
        case 9:                  //SHOW2 OFF
          mode = 0;
          cleanshow();
          break;
        case 11:                //RANDOM ON
          mode = 4;
          cleanshow();
          break;
        case 12:                //RANDOM OFF
          mode = 0;
          cleanshow();
          break;
        case 14:                //Corrida ON
          mode = 5;
          cleanshow();
          break;
        case 15:                //Corrida OFF
          mode = 0;
          cleanshow();
          break;
        case 16:               //APAGATODO
          mode = 0;
          cleanshow();
          break;
      }

      // go to the parent
      currentPos = currentPosParent;
    }
  }
    lcd.clear();
    lcd.setCursor(0,0); lcd.print(mid(menu[currentPos],inStrRev(menu[currentPos],">")+1,len(menu[currentPos])-inStrRev(menu[currentPos],">")));
    lcd.setCursor(0,1); lcd.print(mid(menu[possiblePos[possiblePosScroll]],inStrRev(menu[possiblePos[possiblePosScroll]],">")+1,len(menu[possiblePos[possiblePosScroll]])-inStrRev(menu[possiblePos[possiblePosScroll]],">")));

}

void cleanshow(){
  showstep = 0;
  showloopcount = 0;
}

// Look for a button press
byte checkButtonPress() {
  byte bP = 0;
  byte rBp = 0;
  for (t = 0; t<nrButtons;t++) {
    if (digitalRead(buttons[t]) == 0) {bP = (t + 1);}
  }
  rBp = bP;
  while (bP != 0) { // wait while the button is still down
    bP = 0;
    for (t = 0; t<nrButtons;t++) {
      if (digitalRead(buttons[t]) == 0) {bP = (t + 1);}
    }
  }
  return rBp;

}



void setup() {
  //Serial.begin(9600);
  //Secuenciador Random
  randomSeed(analogRead(0));
  //LCD LOGO
  lcd.begin(16,2);
  bitmap.begin();
  //BITMAP LOGO
  bitmap.rectFill(0, 0, 19, 15, ON, NO_UPDATE);
  bitmap.rectFill(2, 2, 17, 13, OFF, NO_UPDATE);
  bitmap.rectFill(4, 4, 15, 11, ON, NO_UPDATE);    
  bitmap.rect(6, 6, 13, 9, OFF, UPDATE);
  //BOOT LCD
  lcd.setCursor(6, 0);
  lcd.print("ARQAGUA");
  delay(5000);
  lcd.clear();
  lcd.setCursor(2, 5);
  lcd.print("  SP1 V1.0  ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(" --BOTONES-- ");
  lcd.setCursor(2, 2);
  lcd.print("BACK/SELE/OK");
  delay(6000);
  
  for (t=0;t<nrButtons;t++) {
    pinMode(buttons[t],INPUT_PULLUP); 
  }

  //PINMODE (ENTRADA,SALIDA)
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(34,OUTPUT); //Valvula 20
  pinMode(36,OUTPUT); //Valvula 21
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);

  //Escritura LOW or HIGH - Encendido o Apagado
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(34, LOW); //Valvula 20 OFF
  digitalWrite(36, LOW); //Valvula 21 OFF
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);

  updateMenu();

}

void loop()
{

  if (showloopcount == 0){
    switch (mode) {
        case 1: // Prueba encender 
          digitalWrite(1, HIGH);
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          digitalWrite(9, HIGH);
          digitalWrite(10, HIGH);
          digitalWrite(11, HIGH);
          digitalWrite(12, HIGH);
          digitalWrite(13, HIGH);
          digitalWrite(14, HIGH);
          digitalWrite(15, HIGH);
          digitalWrite(16, HIGH);
          digitalWrite(17, HIGH);
          digitalWrite(18, HIGH);
          digitalWrite(19, HIGH);
          digitalWrite(34, HIGH); //Valvula 20 ON
          digitalWrite(36, HIGH); //Valvula 21 ON
          digitalWrite(22, HIGH);
          digitalWrite(23, HIGH);
          digitalWrite(24, HIGH);
          digitalWrite(25, HIGH);
          digitalWrite(26, HIGH);
          digitalWrite(27, HIGH);
          digitalWrite(28, HIGH);
          digitalWrite(29, HIGH);
          digitalWrite(30, HIGH);
          digitalWrite(31, HIGH);
          digitalWrite(32, HIGH);
          break;
        case 0: // Prueba Apagar
          digitalWrite(1, LOW);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          digitalWrite(12, LOW);
          digitalWrite(13, LOW);
          digitalWrite(14, LOW);
          digitalWrite(15, LOW);
          digitalWrite(16, LOW);
          digitalWrite(17, LOW);
          digitalWrite(18, LOW);
          digitalWrite(19, LOW);
          digitalWrite(34, LOW); //Valvula 20 OFF
          digitalWrite(36, LOW); //Valvula 21 OFF
          digitalWrite(22, LOW);
          digitalWrite(23, LOW);
          digitalWrite(24, LOW);
          digitalWrite(25, LOW);
          digitalWrite(26, LOW);
          digitalWrite(27, LOW);
          digitalWrite(28, LOW);
          digitalWrite(29, LOW);
          digitalWrite(30, LOW);
          digitalWrite(31, LOW);
          digitalWrite(32, LOW);
          break;
    
      
        case 2: //Show 1 ON          
          switch (showstep) {
            case 1:
              toggleValve(1);toggleValve(32);
              break;
            case 2:
              toggleValve(2);toggleValve(31);
              break;
            case 3:
              toggleValve(3);toggleValve(30);
              break;
            case 4:
              toggleValve(1);toggleValve(32);
              break;
            case 5:
              toggleValve(4);toggleValve(29);
              break;
            case 6:
              toggleValve(2);toggleValve(31);
              break;
            case 7:
              toggleValve(5);toggleValve(28);
              break;
            case 8:
              toggleValve(3);toggleValve(30);
              break;
            case 9:
              toggleValve(6);toggleValve(27);
              break;
            case 10:
              toggleValve(4);toggleValve(29);
              break;
            case 11:
              toggleValve(7);toggleValve(26);
              break;
            case 12:
              toggleValve(5);toggleValve(28);
              break;
            case 13:
              toggleValve(8);toggleValve(25);
              break;
            case 14:
              toggleValve(6);toggleValve(27);
              break;
            case 15:
              toggleValve(16);toggleValve(17);
              break;
            case 16:
              toggleValve(7);toggleValve(26);
              break;
            case 17:
              toggleValve(15);toggleValve(18);
              break;
            case 18:
              toggleValve(8);toggleValve(25);
              break;
            case 19:
              toggleValve(14);toggleValve(19);
              break;
            case 20:
              toggleValve(16);toggleValve(17);
              break;
            case 21:
              toggleValve(13);toggleValve(34);
              break;
            case 22:
              toggleValve(15);toggleValve(18);
              break;
            case 23:
              toggleValve(12);toggleValve(36);
              break;
            case 24:
              toggleValve(14);toggleValve(19);
              break;
            case 25:
              toggleValve(12);toggleValve(13);
              break;
            case 26:
              toggleValve(34);toggleValve(36);
              break;
            default:
              cleanshow();
              break;

          }
          break;

          
      
      case 3: //Show 2 ON 
      switch (showstep) {
        case 1:
        toggleValve(1); toggleValve(2); toggleValve(3); toggleValve(4); toggleValve(5); toggleValve(6); toggleValve(7); toggleValve(8);
        toggleValve(25); toggleValve(26); toggleValve(27); toggleValve(28); toggleValve(29); toggleValve(30); toggleValve(31); toggleValve(32);
        actualdelay = delaycen;
        break;
        case 2:          
        toggleValve(1); toggleValve(2); toggleValve(3); toggleValve(4); toggleValve(5); toggleValve(6); toggleValve(7); toggleValve(8);
        toggleValve(25); toggleValve(26); toggleValve(27); toggleValve(28); toggleValve(29); toggleValve(30); toggleValve(31); toggleValve(32);
        actualdelay = delaycen;
        break; 
        case 3:
          actualdelay = delayloop;
          toggleValve(1);
        break; 
        case 4:
          toggleValve(2); 
        break; 
        case 5:
          toggleValve(3); 
        break; 
        case 6:
          toggleValve(4);       
        break; 
        case 7:
          toggleValve(5);
        break; 
        case 8:
          toggleValve(6);
        break; 
        case 9:
          toggleValve(7);
        break; 
        case 10:
          toggleValve(8);
        break; 
        case 11:
          toggleValve(16);
        break; 
        case 12:
          toggleValve(24);
        break; 
        case 13:
          toggleValve(32);
        break; 
        case 14:
          toggleValve(31);
        break; 
        case 15:
          toggleValve(30);
        break; 
        case 16:
          toggleValve(29);
        break; 
        case 17:
          toggleValve(28);
        break; 
        case 18:
          toggleValve(27);
        break; 
        case 19:
          toggleValve(26);
        break; 
        case 20:
          toggleValve(25);
        break; 
        case 21:
          toggleValve(17);
        break; 
        case 22:
          toggleValve(9);  
        break; 
        case 23:
          toggleValve(12); toggleValve(13); toggleValve(34); toggleValve(36);
        break; 
        case 24:
          toggleValve(1);
        break; 
        case 25:
          toggleValve(2); 
        break; 
        case 26:
          toggleValve(3); 
        break; 
        case 27:
          toggleValve(4);       
        break; 
        case 28:
          toggleValve(5);
        break; 
        case 29:
          toggleValve(6);
        break; 
        case 30:
          toggleValve(7);
        break; 
        case 31:
          toggleValve(8);
        break; 
        case 32:
          toggleValve(16);
        break; 
        case 33:
          toggleValve(24);
        break; 
        case 34:
          toggleValve(32);
        break; 
        case 35:
          toggleValve(31);
        break; 
        case 36:
          toggleValve(30);
        break; 
        case 37:
          toggleValve(29);
        break; 
        case 38:
          toggleValve(28);
        break; 
        case 39:
          toggleValve(27);
        break; 
        case 40:
          toggleValve(26);
        break; 
        case 41:
          toggleValve(25);
        break; 
        case 42:
          toggleValve(17);
        break; 
        case 43:
          toggleValve(9);
        break; 
        case 44:
          toggleValve(12); toggleValve(13); toggleValve(34); toggleValve(36); 
          actualdelay = delaycen; 
          case 45:
          actualdelay = delayloop;
            break;
            default:
              cleanshow();
              break;

          }
          break;
        
     case 4: //Random
      switch (showstep) {
        case 1:
        actualdelay = delaycen;
         digitalWrite (valves[RNum],LOW);
         // Random numero de valvulas conectadas
        RNum = random(1,32);  
        //the above generates a random number
        digitalWrite (valves[RNum],HIGH);
        actualdelay = delayloop;
             break;
            default:
              cleanshow();
              break;

          }
          break;
       
        case 5: //Corrida ON
        switch (showstep) {
        case 1:
        toggleValve(1);
        break; 
        case 2:
        toggleValve(2);
        break; 
        case 3:
        toggleValve(3);
        break; 
        case 4:
        toggleValve(4); 
        break; 
        case 5:
        toggleValve(5); 
        break; 
        case 6:
        toggleValve(6); 
        break; 
        case 7:
        toggleValve(7); 
        break; 
        case 8:
        toggleValve(8); 
        break; 
        case 9:
        toggleValve(9); 
        break; 
        case 10:
        toggleValve(10); 
        break; 
        case 11:
        toggleValve(11); 
        break; 
        case 12:
        toggleValve(12); 
        break; 
        case 13:
        toggleValve(13); 
        break; 
        case 14:
        toggleValve(14); 
        break; 
        case 15:
        toggleValve(15); 
        break; 
        case 16:
        toggleValve(16); 
        break; 
        case 17:
        toggleValve(17); 
        break; 
        case 18:
        toggleValve(18); 
        break; 
        case 19:
        toggleValve(19); 
        break; 
        case 20:
        toggleValve(34); 
        break; 
        case 21:
        toggleValve(36); 
        break; 
        case 22:
        toggleValve(22); 
        break; 
        case 23:
        toggleValve(23); 
        break; 
        case 24:
        toggleValve(24); 
        break; 
        case 25:
        toggleValve(25); 
        break; 
        case 26:
        toggleValve(26); 
        break; 
        case 27:
        toggleValve(27); 
        break; 
        case 28:
        toggleValve(28); 
        break; 
        case 29:
        toggleValve(29); 
        break; 
        case 30:
        toggleValve(30); 
        break; 
        case 31:
        toggleValve(31); 
        break; 
        case 32:
        toggleValve(32); 
        break;
            default:
              cleanshow();
              break;
        }
        }   
  }

  pressedButton = checkButtonPress();
  if (pressedButton !=0) {
    switch (pressedButton) {
      case 1:
          possiblePosScroll = (possiblePosScroll + 1) % possiblePosCount; // Scroll
      break;
      case 2:
        currentPos = possiblePos[possiblePosScroll]; //Okay
      break;
      case 3:
        currentPos = currentPosParent; //Back
        possiblePosScroll = 0;
      break;
    }
    updateMenu();
  }

  showloopcount++;
  if (showloopcount >= actualdelay){
    //Serial.print("\ntermina un step\n");
    showloopcount = 0;
    showstep++;
  }

}


String mid(String str, int start, int len) {
   int t = 0;
   String u = ""; 
   for (t = 0; t < len;t++) {
    u = u + str.charAt(t+start-1);
   }
   return u;
}

int inStrRev(String str,String chr) {
  int t = str.length()-1;
  int u = 0;
   while (t>-1) {
    if (str.charAt(t)==chr.charAt(0)) {
      u = t+1;t = -1;
    }
    t = t - 1;
   }
  return u;
}

int len(String str) {
  return str.length();
}

void toggleValve(int valveId){
  if (digitalRead(valveId) == 0) { digitalWrite(valveId,HIGH); }
  else { digitalWrite(valveId,LOW); }
}
