///les different states : 
//analogiques
int state = 0;
//numeriques
int newState = 0;
int oldState = 0;
//commencement 
int caACommence = 0;

//tableau des bits
int curseurTab = 0;
int curseurTime = 0;
int curseurTabMontant = 0;
int tabInt[64]; //tableau de 8 octets
int matriceInt[8][8];
char tabChar[8]; //tableau de 8 caractères
int tabTemps[65];

//message final 
String message = "";

//start and stop chrono
unsigned long startMillis;
unsigned long stopMillis;

void setup() {
  // put your setup code here, to run once:
  pinMode(A5, INPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);

}

int tabToInt(int tab[], int somme, int numberPuissance)
{
  somme = somme + tab[numberPuissance] * pow(2,numberPuissance);
  numberPuissance++;
  if(8 == numberPuissance){return somme;}
  else{return tabToInt(tab,somme,numberPuissance);}
}

void loop() {  

  
  state = analogRead(A5);
  //Serial.println(state);
  //Serial.println(newState);
  if(state < 100)
  {
    newState = 0;
  }
  else
  {
    newState = 1;
  }


  if(newState != oldState && newState == 1)
  {
    //FRONT MONTANT
    startMillis = micros();
    oldState = newState;
    curseurTabMontant++;
    //Serial.println(curseurTabMontant);
    
  }
   else if(newState != oldState && newState == 0)
  {
    //FRONT DESCENDANT
    stopMillis = micros();
    oldState = newState;

    
    //Serial.println(curseurTab);

    unsigned long myTime = stopMillis - startMillis;
    /*Serial.print("startMillis: ");
    Serial.println(startMillis); //prints time since program started
    Serial.print("stopMillis: ");
    Serial.println(stopMillis); //prints time since program started
    Serial.print("Time: ");*/
    
    //Serial.println(myTime); //prints time since program started
    tabTemps[curseurTime] = myTime;
    
    
    if(myTime< 3100 && myTime > 2700 && caACommence == 0)//bit de start
    {
      caACommence = 1;
      //Serial.println("Ca commence !");
    }
    if(myTime > 750 && myTime < 1400 && caACommence == 1)//bit 1
    {
      //on push 1 dans le tableau
      tabInt[curseurTab] = 1;
      curseurTab++;
    }
    if(myTime> 1650 && myTime < 2050 && caACommence == 1)//bit 0
    {
      //on push dans le tableau
      tabInt[curseurTab] = 0;
      curseurTab++;
    }
    
    curseurTime++;
    /*
    for(int i=0; i<curseurTab; i++)
    {
      Serial.print(tabInt[i]);
    }*/
    
    
  }
  else
  {
    //pas de changement d'état
  }

  
  //A FAIRE : 
  //Faire la condition de next octet et de stop
  //maintenant mon tableau devrait etre rempli de 0 et de 1 -> il faudrait les afficher
  //ensuite il faudrait les convertir en caractère
  //ensuite il faudrait les stocker dans une chaine de caractère
  //ensuite il faut l'afficher

  if(micros() > 3000000 && micros() < 4000000)
  {
    Serial.println(curseurTab);
    Serial.println(curseurTabMontant);
    Serial.println(curseurTime);
    for(int i=0; i<curseurTime; i++)
    {
      Serial.println(tabTemps[i]+1);
      //Serial.println(tabInt[i]);
    }
    for(int i=0; i<curseurTab; i++)
    {
      //Serial.println(tabTemps[i]+1);
      Serial.println(tabInt[i]);
    }

    for(int i = 0; i<8; i++)
    {
      for(int j = 0; j<8; j++)
      {
        matriceInt[i][j] = tabInt[i*8+j];
        Serial.print(matriceInt[i][j]);
      }
      Serial.println();
    }
    Serial.println("SALUTSALUTSALUTSALUTSALUTSALUTSALUTSALUT");
    
  }
}





  
