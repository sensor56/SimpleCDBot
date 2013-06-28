//--- exemple librairie SimpleCDbot
//--- contrle du CD-Bot par la lumière
// par X. HINAULT - Tous droits réservés - licence GPL v3 - www.mon-club-elec.fr
// Septembre 2012

//--- entete déclarative = variables et constantes globales 

//---- inclusion de librairie
#include <Servo.h> // inclut la librairie Servo

#include <Utils.h> // librairie personnelle avec plusieurs fonctions utiles

#include <SimpleCDbot.h> // librairie personnelle avec fonctions de controle d'une robot à 2 servos RC

// --- constantes des broches ---

const int RVarD=2; //declaration constante de broche analogique
const int RVarG=3; //declaration constante de broche analogique

//--- variables pour réception chaine sur port Série
//int octetReception=0; // variable de réception octet
//char caractereReception=0; // variable de réception caractère
String chaineReception=""; // déclare un objet String vide

//--- variables et constantes pour les servomoteurs
const int Droit=0; // servo Droit a l'indice 0
const int Gauche=1; // servo Droit a l'indice 1

const int neutre[2]={1410, 1400}; // largeur impulsion arret 
const int maxAV[2]={1220,1620}; // largeur impulsion vitesse max en avant
const int maxAR[2]={1620,1220}; // largeur impulsion vitesse max en arriere

const int brocheServo[2]={14,15}; // broches des servomoteur 

//int impulsServo=0; // largeur impulsion servomteur en µsecondes

// --- Déclaration des variables globales ---
int mesureBruteD=0;// Variable pour acquisition résultat brut de conversion analogique numérique
int mesureBruteG=0;// Variable pour acquisition résultat brut de conversion analogique numérique

int seuilD=200; // Variable fixant le seuil de détection de l'obscurité - à adapter
int seuilG=200; // Variable fixant le seuil de détection de l'obscurité - à adapter


//--- objets utiles --- 
Servo servo[2]; // déclaration d'un objet servomoteur

Utils utils; 

SimpleCDbot robot(brocheServo[Droit], maxAR[Droit], maxAV[Droit],brocheServo[Gauche], maxAR[Gauche], maxAV[Gauche], neutre[Droit], neutre[Gauche]); 

//--- la fonction setup() : exécutée au début et 1 seule fois
void setup() {

   Serial.begin(115200); // initialise la vitesse de la connexion série
   //-- utilise la meme vitesse dans le Terminal Série
  
   
   
} // fin de la fonction setup()


//--- la fonction loop() : exécutée en boucle sans fin 
void loop() {

  // acquisition conversion analogique-numerique (CAN) sur la voie analogique
  mesureBruteD=analogRead(RVarD); 
  mesureBruteG=analogRead(RVarG); 

  // affiche valeur numerique entière ou à virgule au format décimal
  Serial.print("Gauche="); Serial.print(mesureBruteG); 
  Serial.print("Droit="); Serial.print(mesureBruteD); 
  Serial.println(); 
  
  if (mesureBruteD<seuilD) Serial.println("Obscurite detectee a droite"); // message si obscurité détectée
  if (mesureBruteG<seuilG) Serial.println("Obscurite detectee a gauche"); // message si obscurité détectée
  
  mesureBruteD=mesureBruteD+130; // correction
  
  //-- code à exécuter en fonction des mesures -- 
  if (abs(mesureBruteD-mesureBruteG)<150)robot.arret();
  
  //--- si la photoR droite est plus éclairée que la gauche
  else if (mesureBruteD>mesureBruteG) robot.tourneDroite(30);

  //--- si la photoR gauche est plus éclairée que la droite
  else if (mesureBruteG>mesureBruteD) robot.tourneGauche(20); 
  
    delay(20); // entre 2 mesures
    
} // fin de la fonction loop()

