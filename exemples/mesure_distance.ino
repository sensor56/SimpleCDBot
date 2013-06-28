//--- Programme pour le controle de 2 servomoteurs à rotation continue
// par le Terminal Serie
// par X. HINAULT - Tous droits réservés - licence GPL v3 - www.mon-club-elec.fr

//--- entete déclarative = variables et constantes globales 

//---- inclusion de librairie
#include <Servo.h> // inclut la librairie Servo

#include <Utils.h> // librairie personnelle avec plusieurs fonctions utiles

#include <SimpleCDbot.h> // librairie personnelle avec fonctions de controle d'une robot à 2 servos RC


//--- variables pour réception chaine sur port Série
//int octetReception=0; // variable de réception octet
//char caractereReception=0; // variable de réception caractère
String chaineReception=""; // déclare un objet String vide

//--- variables et constantes pour les servomoteurs
const int Droit=0; // servo Droit a l'indice 0
const int Gauche=1; // servo Droit a l'indice 1

const int neutre[2]={1410,1400}; // largeur impulsion arret 
const int maxAV[2]={1230,1730}; // largeur impulsion vitesse max en avant
const int maxAR[2]={1730,1230}; // largeur impulsion vitesse max en arriere

const int brocheServo[2]={14,15}; // broches des servomoteur 

//--- pour le GP2D12 --- 
const int GP2D12=A2; //declaration constante de broche analogique

// --- Déclaration des variables globales ---
int mesure_brute=0;// Variable pour acquisition résultat brut de conversion analogique numérique
float mesuref=0.0;// Variable pour calcul résultat décimal de conversion analogique numérique

int distance; // distance référence

//--- tableau de valeurs en millivolts pour distance de 5 en 5cm de 10 à 80 cm pour le capteur GP2D12
// 1ère valeur a l'index 0 
int calibrage[]={ // valeurs en mV
2370, // 10 cm - index 0
1700, // 15 cm - index 1
1300, // 20 cm - index 2
1100, // 25 cm - index 3 
950, // 30 cm - index 4
830, // 35 cm - index 5
720, // 40 cm - index 6
650, // 45 cm - index 7
580, // 50 cm - index 8
540, // 55 cm - index 9 
500, // 60 cm - index 10 
480, // 65 cm - index 11
450, // 70 cm - index 12
430, // 75 cm - index 13
410, // 80 cm - index 14 
400, // au delà 80cm - index 15
}; // fin du tableau 

//int impulsServo=0; // largeur impulsion servomteur en µsecondes

Servo servo[2]; // déclaration d'un objet servomoteur

Utils utils; 

SimpleCDbot robot(brocheServo[Droit], maxAR[Droit], maxAV[Droit],brocheServo[Gauche], maxAR[Gauche], maxAV[Gauche], neutre[Droit], neutre[Gauche]); 

boolean debug=true; 
boolean etatMoteurs=false; // temoin etat moteur
boolean detectObstacle=false; // témoin détection obstacle

//--- la fonction setup() : exécutée au début et 1 seule fois
void setup() {

   Serial.begin(115200); // initialise la vitesse de la connexion série
   //-- utilise la meme vitesse dans le Terminal Série


  robot.infosAnalyseChaine(); // info sur les chaines reconnues par analyseChaine()

  
} // fin de la fonction setup()


//--- la fonction loop() : exécutée en boucle sans fin 
void loop() {

      //--- réception de chaine sur le port série et analyse de la chaine -- 
      chaineReception=utils.waitingString(true); // appelle la fonction de réception sur le port série 
      //if (chaineReception!="") analyseChaine( chaineReception); // appelle la fonction d'analyse de la chaine en réception
      
      //if (chaineReception!="") robot.analyseChaine( chaineReception); // appelle la fonction d'analyse de la chaine en réception
      // la fonction analyse chaine "décode" la chaine et appelle la fonction de la lib RobotCCx2 voulue si la chaine est valide

      if (chaineReception!="") robot.analyseChaine( chaineReception); // appelle la fonction d'analyse de la chaine en réception


    mesuref=moyenneMesure(30, GP2D12); // réalise moyenne de 30 mesures analogiques sur voie GP2D12
    
    distance=distanceGP2D12(mesuref); // renvoie la valeur de la distance correspondante à la valeur tension
    
    //----- affichage du résultat -------- 
    
    if (distance==0) {// si valeur ne correspond pas au calibrage
      if (debug) Serial.println("Distance hors plage de mesure"); 
      
      if ( (etatMoteurs==false) || (detectObstacle==true) ) { // allume moteur
        robot.enAvant(100); 
        etatMoteurs=true;
        detectObstacle==false; 
      }
      
    }
    else { // si valeur distance calculée
      if (debug) Serial.print("Distance comprise entre"), Serial.print(distance), Serial.print(" cm et "); 
      if (debug) Serial.print(distance+5),Serial.println(" cm."); 
      
      if (distance<20) {
        
             if (etatMoteurs==true) { // si moteur allumé
              robot.arret(1000); 
              robot.enArriere(50,1000); // recule 1 seconde
              //etatMoteurs=false; // on laisse à true jusqu'à distance sup 30 suivante.. 
              detectObstacle=true; 
              
            } // fin if moteur==true
             
      } // fin if <30
       else if (distance>=20) {
             
            if (detectObstacle==true) { // si moteur allumé = si gestion distance <30 toujours en cours
             robot.tourneDroite(50,1000);
             etatMoteurs=false; 
            detectObstacle=false; // plus d'obstacle
            } // fin if
            
                 if (etatMoteurs==false) { // allume moteur
                robot.enAvant(100); 
                etatMoteurs=true;
                  } // fin if moteurs false

            
             
       } // fin else if distance


    }// fin else
    
    delay (250); // entre 2 mesures 
  
} // fin de la fonction loop()


//======== autres fonctions ==========

// --- fonction réalisant une moyenne de n mesures analogiques sur voie analogique

float moyenneMesure(int nombreMesure, int voie) { // --- fonction réalisant une moyenne de n mesures analogiques

  //---- variables locales ---
  int mesure_can=0;
  long cumul_can=0;
  int moyenne_can=0;
  float mesure_canf=0; 
  
  //----- calcul d'une moyenne de plusieurs mesures ------- 
  for (int i=0; i<nombreMesure; i++) // répète la mesure n fois
  {
    mesure_can=analogRead(voie); 
    cumul_can=cumul_can+mesure_can; 
  }

  if (debug) Serial.print("cumul="), Serial.println(cumul_can); 

  // calcul moyenne 
  moyenne_can=cumul_can/nombreMesure; 
  cumul_can=0; //RAZ cumul...
    if (debug) Serial.print("moyenne="), Serial.println(moyenne_can); 

  // mesure tension correspondante en mV
  mesure_canf=float(moyenne_can); 
  mesure_canf=mesure_canf*5000.0;
  mesure_canf=mesure_canf/1023.0;

    if (debug) Serial.print("tension="), Serial.println(mesure_canf); 

  return (mesure_canf); // valeur renvoyée par la fonction  

} // --- fin fonction moyenneMesure

//------------- fonction renvoyant la distance en fonction de la mesure analogique GP2D12 ----
// cette fonction est nécessaire car la sortie analogique du GP2D12 n'est pas linéaire

int distanceGP2D12(float mesure_float) {

   int dist=0; // RAZ variable locale distance 

  // ------- détermination de la distance à partir du tableau de reference

  for (int j=0; j<=14; j++) { // teste les valeurs de calibrage

    if ((int(mesure_float)<=calibrage[j]) && (int(mesure_float)>calibrage[j+1])) { // si la mesure comprise entre 2 valeurs
      dist=10+(j*5); // calcule de la distance en cm à partir de l'index courant
    }
  
  } // fin boucle test calibrage

  return (dist); // valeur renvoyée par la fonction
  
} // ----------- fin fonction analyse distanceGP2D12 ----
