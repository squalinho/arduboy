

// See: https://mlxxxp.github.io/documents/Arduino/libraries/Arduboy2/Doxygen/html/
#include <Arduboy2.h>

 
Arduboy2 arduboy;

int menu = 0;


int highscore = 0;
int tab1 = 1;
int tab2 = 1;
int tab1Old = 0;
int tab2Old = 0;
int valeur = 0;
int win = 0;
int lose = 0;
boolean winner = false;
boolean looser = false;
boolean fin = false;
int soluOld = 0;
int temps = 0;
int timing = 60;
int fini = 0;
int oldTemps = 0;
String message = "";
int nbPartie = 0;
boolean blocTemps = false;
int tempsJeu = 0;
int menuY = 8;
boolean modeTime = true;
String mesTime = "Temps ON";
String sep3 = "REUSSI:";
String sep4 = " RATE:";
boolean multiTrou = false;
int ordreTrou = 0;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();

  // initialize things here
  tab1 = random(1,10);
  tab2 = random(1,10);
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();


  // game goes here


if(menu == 0){
    //8 -> Multiplications
    //18 - > Multi-Trous
    //28 - > Options

    
          arduboy.setCursor(10,5);
          arduboy.print("Multiplications");
          arduboy.setCursor(10,15);
          arduboy.print("Multi-trous");
          arduboy.setCursor(10,25);
          arduboy.print("Options");
          arduboy.drawCircle(4, menuY, 2, WHITE);
          //arduboy.setCursor(10,50);
          //arduboy.print(ordreTrou);

          if(arduboy.justPressed(DOWN_BUTTON)){
            menuY += 10;
            if(menuY > 28){
              menuY = 8;
            }
          }
  
          if(arduboy.justPressed(UP_BUTTON)){
            menuY -= 10;
            if(menuY < 8){
              menuY = 28;
            }
          }
          if(arduboy.justPressed(A_BUTTON)){

            if(menuY == 8){
              menu = 1;
              multiTrou = false;
              oldTemps = (millis()/1000);
             
            }
            else if(menuY == 18){
              menu = 1;
              multiTrou = true;
              ordreTrou = random(0,100);
              oldTemps = (millis()/1000);
              valeur = 0;
              
              
            }
            else if(menuY == 28){
              menu = 10;
              menuY = 8;
            }
          }
}



else if(menu == 10){

          arduboy.drawCircle(4, menuY, 2, WHITE);

          String opt1 = "Timing : ";
          arduboy.setCursor(10,5);
          arduboy.print(opt1 + timing);
          arduboy.setCursor(10,15);
          arduboy.print(mesTime);


          if(arduboy.pressed(RIGHT_BUTTON)){
           timing += 1;
          }
  
          if(arduboy.pressed(LEFT_BUTTON) && timing > 0){
            timing -= 1;
          }


          if(arduboy.justPressed(A_BUTTON)){
           if(menuY == 18){

            
            if(modeTime){
              modeTime = false;
              mesTime = "Temps OFF";
            }
            else 
            { 
              modeTime = true;
              mesTime = "Temps ON";
             }
           }
          }
          if(arduboy.justPressed(B_BUTTON)){
           menu = 0;
          }
          if(arduboy.justPressed(DOWN_BUTTON)){
            menuY += 10;
            if(menuY > 18){
              menuY = 8;
            }
          }
  
          if(arduboy.justPressed(UP_BUTTON)){
            menuY -= 10;
            if(menuY < 8){
              menuY = 18;
            }
          }
        
}

else if(menu == 1){
  
          if(!fin)
          {

            if(arduboy.pressed(DOWN_BUTTON) && arduboy.pressed(UP_BUTTON)){
              menu = 0;
            }

            
            int solu = tab1 * tab2;
            arduboy.drawLine(0, 12, 127, 12, WHITE);
            arduboy.drawLine(0, 42, 127, 42, WHITE);
            arduboy.drawLine(0, 0, 127, 0, WHITE);
            arduboy.drawLine(0, 63, 127, 63, WHITE);
            arduboy.drawLine(0, 0, 0, 63, WHITE);
            arduboy.drawLine(127, 0, 127, 63, WHITE);
            
            arduboy.setCursor(6,20);
            arduboy.setTextSize(2);
            String sep1 = " x ";
            String sep2 = " = ";


            if(multiTrou == false){
              arduboy.print(tab1 + sep1 + tab2 + sep2 + valeur);
            }
            else if(multiTrou == true){
              if(ordreTrou > 50){
                arduboy.print(tab1 + sep1 + valeur + sep2 + solu);
              }
              else if(ordreTrou <= 50){
                arduboy.print(valeur + sep1 + tab1 + sep2 + solu);
              }
            }
            



            
            String sep = "|";
            arduboy.setCursor(4,3);
            arduboy.setTextSize(1);
            arduboy.print("CLOE AIME MULTIPLIER");
            
            
            
            
            if(arduboy.justPressed(UP_BUTTON)){
              valeur += 1;
              winner = false;
              looser = false;
              if(multiTrou && valeur > 10){
                valeur = 10;
              }
            }
            
            if(arduboy.justPressed(DOWN_BUTTON) && valeur > 0){
              valeur -= 1;
              winner = false;
              looser = false;
            }
            if(arduboy.justPressed(LEFT_BUTTON)){
          
              if(valeur >10){
                valeur -= 10;
              }
              else if(valeur <= 10){
                valeur = 0;
              }
              winner = false;
              looser = false;
            }
            
            if(arduboy.justPressed(RIGHT_BUTTON)){
              valeur += 10;
              winner = false;
              looser = false;
            }
            
            if( arduboy.justPressed(B_BUTTON)){
              valeur = 0;
              winner = false;
              looser = false;
            }
          
          if( arduboy.justPressed(A_BUTTON)){
                    winner = false;
                    looser = false;
                
                    soluOld = solu;
                    tab1Old = tab1;
                    tab2Old = tab2;
                    

                  if(!multiTrou){
                    
                 
                            if( valeur == solu){
                              
                              winner = true;
                          
                              tab1 = random(1,10);
                              tab2 = random(1,10);
                              valeur = 0;
                              win += 1;
                              
                             
                            }
                            else {
                              
                              looser = true;
                              tab1 = random(1,10);
                              tab2 = random(1,10);
                              valeur = 0;
                              lose += 1;
                              
                            }
                  }
                  else {
                  //multitrou
                  ordreTrou = random(0,100);
                              if( valeur == tab2){
                              
                              winner = true;
                          
                              tab1 = random(1,10);
                              tab2 = random(1,10);
                              valeur = 0;
                              win += 1;
                              
                             
                            }
                            else {
                              
                              looser = true;
                              tab1 = random(1,10);
                              tab2 = random(1,10);
                              valeur = 0;
                              lose += 1;
                              
                            }
                    
                  }
          }
          
            if (winner) {
              arduboy.setCursor(50,45);
              arduboy.print("GAGNE");
            }
            if (looser) {
              arduboy.setCursor(6,45);
              String message = "PERDU -> ";
              if(ordreTrou >50){
                arduboy.print(message + +tab1Old +sep1 + tab2Old + sep2 + soluOld);
              }
              else{
                arduboy.print(message + +tab2Old +sep1 + tab1Old + sep2 + soluOld);
              }
            }
            temps = (millis()/1000)- oldTemps;
           
            if(modeTime){
                    fini = timing - temps;
                    
                  
                  //arduboy.setCursor(60,45);
                  //arduboy.print(temps + sep + fini);
                  
                  
                    
                    arduboy.drawRect(2, 58, fini*(128/timing), 4, WHITE);
            }
            else{
                  fini = 128;
                  arduboy.setCursor(4,55);
                  arduboy.print(sep3 + win + sep + sep4 + lose);
              }
            arduboy.setCursor(2,44);
          
          
          
            
            if(fini <= 0){
              
              fin = true;
              
            }
          
          }
          else if( fin == true){
          
            blocTemps = true;
            if( arduboy.justPressed(B_BUTTON)){
          
                blocTemps = false;
                nbPartie += 1;
                valeur = 0;
                fini = 60;
                win = 0;
                lose = 0;
                winner = false;
                looser = false;
                tab1 = random(1,10);
                tab2 = random(1,10);
                oldTemps = (millis()/1000);
                fin = false; 
                
            }
            arduboy.setCursor(50,10);
            arduboy.setTextSize(2);
            arduboy.print("FIN");
            arduboy.setTextSize(1);
            arduboy.setCursor(12,48);
          
            
            String hs = "Meilleur score : ";
            
            arduboy.print(sep3+ win + sep4 + lose);
            if (win > highscore) {
              if(nbPartie > 0){
                 message = "Record battu";
              }
             
              highscore = win;
            }
            else if(win < highscore){
              message = "Revise encore...";
            }
             arduboy.setCursor(12,55);
              arduboy.print(message);
            arduboy.setCursor(12,32);
            arduboy.print(hs + highscore);
            arduboy.setCursor(2,2);
            arduboy.print(nbPartie);
          
          if(blocTemps){
           tempsJeu = (millis()/1000)/60;
          }
          
            arduboy.setCursor(30,2);
            arduboy.print(tempsJeu);
          }
}


  arduboy.display();
}
 
