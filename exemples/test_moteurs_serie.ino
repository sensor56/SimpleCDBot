//--- exemple librairie SimpleCDbot
// Programme pour le controle de 2 servomoteurs à rotation continue
// par le Terminal Serie
// par X. HINAULT - Tous droits réservés - licence GPL v3 - www.mon-club-elec.fr
// Septembre 2012

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

const int neutre[2]={1420,1420}; // largeur impulsion arret 
const int maxAV[2]={1220,1620}; // largeur impulsion vitesse max en avant
const int maxAR[2]={1620,1220}; // largeur impulsion vitesse max en arriere

const int brocheServo[2]={14,15}; // broches des servomoteur 

//int impulsServo=0; // largeur impulsion servomteur en µsecondes

//Servo servo[2]; // déclaration d'un objet servomoteur

Utils utils; 

// SimpleCDbot(int brocheServoDroitIn, int maxARDroit, int maxAVDroit, int brocheServoGaucheIn, int maxARGauche, int maxAVGauche, int neutreDroit, int neutreGauche); // constructeur avec initialisation 
SimpleCDbot robot(brocheServo[Droit], maxAR[Droit], maxAV[Droit],brocheServo[Gauche], maxAR[Gauche], maxAV[Gauche], neutre[Droit], neutre[Gauche]); 

//--- la fonction setup() : exécutée au début et 1 seule fois
void setup() {

   Serial.begin(115200); // initialise la vitesse de la connexion série
   //-- utilise la meme vitesse dans le Terminal Série
  
   robot.infosAnalyseChaine(); // infos sur les chaines reconnues par la fonction analyse chaine 
   
} // fin de la fonction setup()


//--- la fonction loop() : exécutée en boucle sans fin 
void loop() {

      //--- réception de chaine sur le port série et analyse de la chaine -- 
      chaineReception=utils.waitingString(true); // appelle la fonction de réception sur le port série 

      if (chaineReception!="") robot.analyseChaine( chaineReception); // appelle la fonction d'analyse de la chaine en réception


  
} // fin de la fonction loop()
