///les different states : 
//analogiques
int state = 0;
//numeriques
int newState = 0;
int oldState = 0;
//commencement 
int caACommence = 0;
//affichage
int cestAffiche = 0;

//tableau 
int curseurTab = 0;
int tabInt[64]; //tableau de 8 octets
int matriceInt[8][8];
int tabDecimal[8];
char tabChar[8]; //tableau de 8 caractères

//start and stop chrono
unsigned long startMillis;
unsigned long stopMillis;

void setup() {
  // put your setup code here, to run once:
  pinMode(A5, INPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);

}

//fonction qui sert à transformer un octect en décimal
int tabToInt(int tab[], int somme, int numberPuissance)
{
  if(tab[7-numberPuissance] == 1)
  {
    somme = somme + (tab[7-numberPuissance] * pow(2,numberPuissance));
    if(numberPuissance > 4) {somme = somme + 1;}
  }
  if(numberPuissance == 0){return somme;}
  else
  {
    numberPuissance--;
    return tabToInt(tab,somme,numberPuissance);
  }
}

//fonction principale : affiche sous forme de string un signal recu sous forme de lumière
void loop() {  

  
  state = analogRead(A5);
  
  if(state < 100){newState = 0;}
  else{newState = 1;}


  if(newState != oldState && newState == 1)//FRONT MONTANT
  {
    startMillis = micros(); //On lance le chrono
    oldState = newState; //On change l'ancien state  
  }
   else if(newState != oldState && newState == 0)//FRONT DESCENDANT
  {
    stopMillis = micros(); //On arrete le chrono
    oldState = newState; //On change l'ancien state
    unsigned long myTime = stopMillis - startMillis; //On calcule le chrono entre front montant et front descendant 
    
    if(myTime< 3100 && myTime > 2700 && caACommence == 0){caACommence = 1;}//bit de start
    else if(myTime > 750 && myTime < 1400 && caACommence == 1)//bit 1
    {
      //on push 1 dans le tableau
      tabInt[curseurTab] = 1;
      curseurTab++;
    }
    else if(myTime> 1650 && myTime < 2050 && caACommence == 1)//bit 0
    {
      //on push 0 dans le tableau
      tabInt[curseurTab] = 0;
      curseurTab++;
    }  
  }

  //Quand il n'y a pas eu de changement d'état depuis 200000 microsecondes et que le resultat n'a pas encore été affiché
  if(stopMillis != 0 && (micros() > (stopMillis + 200000)) && cestAffiche == 0)
  {
    for(int i = 0; i<8; i++)
    {
      for(int j = 0; j<8; j++)
      {
        matriceInt[i][j] = tabInt[i*8+j]; //on transforme le tableau de 64 bits en une matrice de 8*8 bits
      }
      tabDecimal[i] = tabToInt(matriceInt[i],0,7); //on transforme chaque sous tableau en un décimal qu'on ajoute au tableau de décimal
    }
    for(int i = 0; i<8; i++)
    {
      tabChar[i] = (char)tabDecimal[i]; //on affiche l'ensemble des décimales sous forme de caractère en utilisant la table ASCII
      Serial.print(tabChar[i]);
    }
    Serial.println();
    cestAffiche = 1;  // on remplace la variable c'est affiché pour ne plus rentrer dans le if (on affiche qu'une seule fois)
  }
}





  
