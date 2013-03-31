/*
 * Copyright (c) 2012 by Xavier HINAULT - support@mon-club-elec.fr
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 3
 * or the GNU Lesser General Public License version 3, both as
 * published by the Free Software Foundation.
 */

#include "Arduino.h"
#include "Servo.h"
#include "Utils.h"
#include "SimpleCDbot.h"



  SimpleCDbot::SimpleCDbot(){ // constructeur par défaut 
 
  } // fin constructeur par défaut 

  SimpleCDbot::SimpleCDbot(int brocheServoDroitIn, int maxARDroit, int maxAVDroit, int brocheServoGaucheIn, int maxARGauche, int maxAVGauche, int neutreDroitIn,int neutreGaucheIn ){ // constructeur avec initialisation des broches 

  //-- utiliser this pour passer les paramètres aux variables de la classe...

	this->_debug=true; 

 	this->_Droit=0; // servo Droit a l'indice 0
	this->_Gauche=1; // servo Droit a l'indice 1
	
	this->_neutre[_Droit]=neutreDroitIn; // largeur impulsion arret 
	this->_neutre[_Gauche]=neutreGaucheIn; // largeur impulsion arret 
	
	//-- tableau de valeur à utiliser -- 
	//this->_maxAV={maxAVDroit,maxAVGauche}; // largeur impulsion vitesse max en avant
	//this->_maxAR={maxARDroit,maxARGauche}; // largeur impulsion vitesse max en arriere

	//this->_brocheServo={brocheServoDroitIn,brocheServoGaucheIn}; // broches des servomoteurs 

	//-- correction bug 1.0.1
	this->_maxAV[_Droit]=maxAVDroit;
	this->_maxAV[_Gauche]=maxAVGauche; 
		
	this->_maxAR[_Droit]=maxARDroit;
	this->_maxAR[_Gauche]=maxARGauche; 

	this->_brocheServo[_Droit]=brocheServoDroitIn;
	this->_brocheServo[_Gauche]=brocheServoGaucheIn;
	

	// initialisation des variables internes 
	_debug=false; // drapeau de messages de debug - false par défaut

	_AVANT=1; // constante sens moteur
	_ARRIERE=0; // constante sens moteur
	_STOP=0; // constante vitesse moteur


/*
	// initialisation des variables internes de broches des moteurs 
 	_sensMoteurDroit=sensMoteurDroitIn;
 	_vitesseMoteurDroit=vitesseMoteurDroitIn;  
	_sensMoteurGauche=sensMoteurGaucheIn;
	_vitesseMoteurGauche=vitesseMoteurGaucheIn;

	//--- met en sortie les 4 broches de commande des moteurs --- 
	 pinMode (_sensMoteurGauche,OUTPUT); // Broche sensMoteur1 configurée en sortie
	 pinMode (_vitesseMoteurGauche,OUTPUT); // Broche vitesseMoteur1 configurée en sortie
	 pinMode (_vitesseMoteurDroit,OUTPUT); // Broche vitesseMoteur2 configurée en sortie
	 pinMode (_sensMoteurDroit,OUTPUT); // Broche sensMoteur2 configurée en sortie
   
*/

  } // fin constructeur avec initialisation 


//------ fonctions de la classe

//----- fonction activation / désactivation debug
void SimpleCDbot::setDebug(boolean flagIn) {
	
	_debug=flagIn; // modifie variable interne 

}


//--------- fonctions d'étalonnage des servomoteurs ---------- 
void SimpleCDbot::impulsServo(int indiceServo,int largeurImpulsIn){

     this->_servo[indiceServo].attach(_brocheServo[indiceServo]); // attache le servomoteur à la broche

	this->_servo[indiceServo].writeMicroseconds(largeurImpulsIn); 
}

void SimpleCDbot::impulsDroit(int largeurImpulsIn){

	impulsServo(_Droit, largeurImpulsIn); 
	//this->_servo[_Droit].writeMicroseconds(largeurImpulsIn); 
}

void SimpleCDbot::impulsGauche(int largeurImpulsIn){
	impulsServo(_Gauche, largeurImpulsIn); 
	//this->_servo[_Gauche].writeMicroseconds(largeurImpulsIn); 
}


//-------- fonctions des mouvements de base des servomoteurs ------

//----- fonction de controle de la vitesse avant d'un servomoteur
void SimpleCDbot::servoAvant(int indiceServo, int vitesseIn) {
// -- vitesse entre 10 et 100% --  
 
     int impulsServo; // variable locale 
     
      this->_servo[indiceServo].attach(_brocheServo[indiceServo]); // attache le servomoteur à la broche
     
     impulsServo=map(vitesseIn, 0, 100, _neutre[indiceServo], _maxAV[indiceServo]); // calcul largeur impulsion AV correspondante
      this->_servo[indiceServo].writeMicroseconds(impulsServo); 
     delay(10); // pause 

	if (_debug) Serial.print(F("indice =")), Serial.println(indiceServo); 
	if (_debug) Serial.print(F("broche =")), Serial.println(_brocheServo[indiceServo]); 
	if (_debug) Serial.print(F("impulsion =")), Serial.println(impulsServo); 

  
} // fin servoAvant 

void SimpleCDbot::avantDroit(int vitesseIn) {
// -- vitesse entre 10 et 100% --  
	
	servoAvant(_Droit, vitesseIn); 

} // fin 

void SimpleCDbot::avantGauche(int vitesseIn) {
// -- vitesse entre 10 et 100% --  
	
	servoAvant(_Gauche, vitesseIn); 

} // fin 

//----- fonction de controle de la vitesse arriere d'un servomoteur
void SimpleCDbot::servoArriere(int indiceServo, int vitesseIn) {
// -- vitesse entre 10 et 100% --  
 
     int impulsServo; // variable locale 
     
     this->_servo[indiceServo].attach(_brocheServo[indiceServo]); // attache le servomoteur à la broche
     
     impulsServo=map(vitesseIn, 0, 100, _neutre[indiceServo], _maxAR[indiceServo]); // calcul largeur impulsion AV correspondante
      this->_servo[indiceServo].writeMicroseconds(impulsServo); 

	if (_debug) Serial.print(F("indice =")), Serial.println(indiceServo); 
	if (_debug) Serial.print(F("broche =")), Serial.println(_brocheServo[indiceServo]); 
	if (_debug) Serial.print(F("impulsion =")), Serial.println(impulsServo); 

     delay(10); // pause 

  
} // fin servoArriere

void SimpleCDbot::arriereDroit(int vitesseIn) {
// -- vitesse entre 10 et 100% --  
	
	servoArriere(_Droit, vitesseIn); 

} // fin 

void SimpleCDbot::arriereGauche(int vitesseIn) {
// -- vitesse entre 10 et 100% --  
	
	servoArriere(_Gauche, vitesseIn); 

} // fin 

//---------------------- mouvements synchrones des 2 servomoteurs --------------- 

//--- fonction stop = arret complet
void SimpleCDbot::arret() {

   this->_servo[this->_Droit].detach(); // met le servomoteur à l'arret
   this->_servo[this->_Gauche].detach(); // met le servomoteur à l'arret 
  
} //--- fin fonction stop = arret complet

//--- fonction stop = arret complet avec delay
void SimpleCDbot::arret(int dureeIn) {

	arret(); 
	delay(dureeIn); 
  
} //--- fin fonction stop = arret complet avec delay

void SimpleCDbot::enAvant(int vitesseIn) { // met les 2 moteurs en avant
// vitesse entre 10 et 100%
  
  servoAvant(_Droit, vitesseIn); // moteur Droit
  servoAvant(_Gauche, vitesseIn); // moteur Gauche
  
} // fin en avant 

void SimpleCDbot::enAvant(int vitesseIn, int dureeIn) { // met les 2 moteurs en avant avec durée
// vitesse entre 10 et 100% - durée en ms

	dureeIn=min(10000, dureeIn); // pour eviter duree sup 10 secondes

	enAvant(vitesseIn); 
	delay(dureeIn); 
	arret(); 

} // fin  

void SimpleCDbot::enArriere(int vitesseIn) { // met les 2 moteurs en arriere
// vitesse entre 10 et 100%
  
  servoArriere(_Droit, vitesseIn); // moteur Droit
  servoArriere(_Gauche, vitesseIn); // moteur Gauche
  
} // fin en arriere

void SimpleCDbot::enArriere(int vitesseIn, int dureeIn) { // met les 2 moteurs en arrière avec durée
// vitesse entre 10 et 100% - durée en ms

	dureeIn=min(10000, dureeIn); // pour eviter duree sup 10 secondes

	enArriere(vitesseIn); 
	delay(dureeIn); 
	arret(); 

} // fin  


void SimpleCDbot::tourneDroite(int vitesseIn) { // tourne à droite
// vitesse entre 10 et 100%
  
  servoArriere(_Droit, vitesseIn); // moteur Droit
  servoAvant(_Gauche, vitesseIn); // moteur Gauche
  
} // fin tourne droite

void SimpleCDbot::tourneDroite(int vitesseIn, int dureeIn) { // tourne à droite avec durée
// vitesse entre 10 et 100% - durée en ms

	dureeIn=min(10000, dureeIn); // pour eviter duree sup 10 secondes

	tourneDroite(vitesseIn); 
	delay(dureeIn); 
	arret(); 

} // fin  tourne à droite


void SimpleCDbot::tourneGauche(int vitesseIn) { // tourne à gauche
// vitesse entre 10 et 100%
  
  servoAvant(_Droit, vitesseIn); // moteur Droit
  servoArriere(_Gauche, vitesseIn); // moteur Gauche
  
} // fin tourne gauche

void SimpleCDbot::tourneGauche(int vitesseIn, int dureeIn) { // tourne à gauche avec durée
// vitesse entre 10 et 100% - durée en ms

	dureeIn=min(10000, dureeIn); // pour eviter duree sup 10 secondes

	tourneGauche(vitesseIn); 
	delay(dureeIn); 
	arret(); 

} // fin  tourne à gauche





//------------ SimpleCDbot :: infoAnalyseChaine() --------- 

void SimpleCDbot::infosAnalyseChaine() {

	Serial.println(F("***** Servomoteurs Rotation Continue x 2 *****")); // debug
	Serial.println(F("")); // debug
	Serial.println(F("arret() : stoppe les servomoteurs ")); // debug
	Serial.println(F("stop() : stoppe les servomoteurs ")); // debug
	Serial.println(F("")); // debug
	Serial.println(F("debug(true/false)")); // debug
	Serial.println(F("")); // debug
	Serial.println(F("avantDroit(vitesse)")); // debug
	Serial.println(F("avantGauche(vitesse)")); // debug
	Serial.println(F("arriereDroit(vitesse)")); // debug
	Serial.println(F("arriereGauche(vitesse)")); // debug
	Serial.println(F("")); // debug
	Serial.println(F("enAvant(vitesse) | enAvant(vitesse, duree ms): marche avant - vitesse entre 0 et 100%")); // debug
	Serial.println(F("enArriere(vitesse) | enArriere(vitesse, duree ms): marche arriere- vitesse entre 0 et 100%")); // debug
	Serial.println(F("")); // debug
	Serial.println(F("tourneDroite(vitesse) | tourneDroite(vitesse, duree ms) : tourne vers la droite - vitesse entre 0 et 100%")); // debug
	Serial.println(F("tourneGauche(vitesse) | tourneGauche(vitesse, duree ms) : tourne vers la gauche - vitesse entre 0 et 100%")); // debug
	Serial.println(F("")); // debug
	Serial.println(F("impulsDroit(impulsionMicrosecondes)")); // debug
	Serial.println(F("impulsGauche(impulsionMicrosecondes)")); // debug
	Serial.println(F("")); // debug

} // fin infosAnalyseChaine

//------------ SimpleCDbot : analyseChaine ---------------
void SimpleCDbot::analyseChaine(String chaineReceptionIn) { // fonction d'analyse de la chaine recue


 String paramString; // chaine locale 
 long params[6]; // tableau de paramètres pour instructions à paramètres multiples - taille du tableau fixée par le nombre max de paramètres utilisés 

  // ---- analyse de la chaine recue sur le port Série ---- 
  //chaineReception=chaineReception.trim(); // enlève les espaces
  //chaineReception=chaineReception.trim(); // enlève les espaces
  chaineReceptionIn.trim(); // enlève les espaces - version 1.0

  
  //xxxxxxxxxxxxxxxxxxx instructions sans paramètres xxxxxxxxxxxx
  
  if (chaineReceptionIn=="arret()") { // si instruction sans paramètre reçue 
    arret(); // exécute instruction si valide
  } 

  if (chaineReceptionIn=="stop()") { // si instruction sans paramètre reçue 
    arret(); // exécute instruction si valide
  } 

  
  //xxxxxxxxxxxxxxxxxxxxx instructions avec parametres chaines xxxxxxxxxxxxxxxxxxx
  
    paramString=_utils.testInstructionString("debug(", chaineReceptionIn); // récupère la chaine  paramètre ou null 
    if (paramString) { // si instruction avec chaine reçue !=0 équivaut !=null   (ne pas utiliser ==true)

      if (_debug) Serial.print(F("Chaine recue : ")); 
      if (_debug) Serial.println(paramString); // affiche la chaine extraite
 
      if (paramString=="true"){
        
        _debug=true; // active debug

         
      } // fin if true 

      if (paramString=="false"){
        _debug=false; // désactive debug
        
        
      } // fin if false 
      
  } // if paramString==true 


/*
    //if (chaineReception=="servoPanUp()") { // si instruction reçue
    paramString=utils.testInstructionString("servoPanUp(", chaineReception); // récupère la chaine  paramètre ou null 
    if (paramString) { // si instruction avec chaine reçue !=0 équivaut !=null   (ne pas utiliser ==true)

      if (debug) Serial.print(F("Chaine recue : ")); 
      if (debug) Serial.println(paramString); // affiche la chaine extraite
 
      if (paramString=="true"){
        
        servoPanUp=true; // active rotation Pan continue

        //-- RAZ angle avant de commencer -- non : utiliser l'angle courant
        //servoPan.writeMicroseconds(angle(angleServoPanFace)); // crée impulsion à partir valeur angle - plus précis que write()    
        //angleServoPan0=angleServoPanFace; // mémorise angle actuel 
        //angleServoPan=angleServoPanFace; // RAZ aussi angleServoPan

        
      } // fin if true 

      if (paramString=="false"){
        servoPanUp=false; // active rotation Pan continue
        
        //-- RAZ angle --
        //servoPan.writeMicroseconds(angle(angleServoPanFace)); // crée impulsion à partir valeur angle - plus précis que write()    
        //angleServoPan0=angleServoPanFace; // mémorise angle actuel 

        
      } // fin if false 
      
  } // if paramString==true 

*/

/*
  //---------- instruction serial : renvoie chaine idem sur le port serie ------------
    paramString=utils.testInstructionString("serial(", chaineReception); // récupère la chaine  paramètre ou null 
    if (paramString) { // si instruction avec chaine reçue !=0 équivaut !=null   (ne pas utiliser ==true)
    
      if (debug) Serial.print(F("Chaine recue : ")); 
      if (debug) Serial.println(paramString); // affiche la chaine extraite
      
      String transString=paramString; 
      
      //if (utils.testInstructionString("joueSon(", transString)) { // test si la chaine extraite est elle-meme une instruction valide 
      paramString=utils.testInstructionString("joueSon(", transString); // récupère la chaine  paramètre ou null 
      if (paramString) { // si instruction avec chaine reçue !=0 équivaut !=null   (ne pas utiliser ==true)
 
           if (debug) Serial.print(F("Chaine recue : ")); 
           if (debug) Serial.println(paramString); // affiche la chaine extraite
           
           joueSon(paramString,true); // appelle la fonction pour execution 
 
      } // fin if 
  
  } // fin si serial
 
*/
 
/*
  //---------- instruction joueSon(***)
   // if (utils.testInstructionString("joueSon(", chaineReception)==true) { // si instruction avec chaine reçue
       paramString=utils.testInstructionString("joueSon(", chaineReception); // récupère la chaine  paramètre ou null 
    if (paramString) { // si instruction avec chaine reçue !=0 équivaut !=null   (ne pas utiliser ==true)

    
      if (debug) Serial.print(F("Chaine recue : ")); 
      if (debug) Serial.println(paramString); // affiche la chaine extraite
      
      joueSon(paramString,true); // appelle la fonction pour execution      
  
  } // fin si joueSon

*/

/*
  //---------- instruction direTexte(***)
 //   if (utils.testInstructionString("direTexte(", chaineReception)==true) { // si instruction avec chaine reçue
     paramString=utils.testInstructionString("direTexte(", chaineReception); // récupère la chaine  paramètre ou null 
    if (paramString) { // si instruction avec chaine reçue !=0 équivaut !=null   (ne pas utiliser ==true)

    
      if (debug) Serial.print(F("Chaine recue : ")); 
      if (debug) Serial.println(paramString); // affiche la chaine extraite
      
      direTexte(paramString,true); // appelle la fonction pour execution      
  
  } // fin si joueSon

*/


  //xxxxxxxxxxxxxxxxxxxx instructions avec paramètres numeriques entiers xxxxxxxxxxxxxxx

     // info : la valeur numérique extraite par testInstruction() est stockée dans variable globale param
     
  //================= instructions paramètres généraux =============
 


//------------------ instructions servomoteurs moteurs --------------- 

//------- mouvements unitaires ------- 
if (_utils.testInstruction2(chaineReceptionIn,"avantDroit(",1,params)==true) { //si instruction avec 1 paramètre reçue valide
    avantDroit(params[0]); // exécute instruction 
  } // fin 

if (_utils.testInstruction2(chaineReceptionIn,"avantGauche(",1,params)==true) { //si instruction avec 1 paramètre reçue valide
    avantGauche(params[0]); // exécute instruction 
  } // fin 

if (_utils.testInstruction2(chaineReceptionIn,"arriereDroit(",1,params)==true) { //si instruction avec 1 paramètre reçue valide
    arriereDroit(params[0]); // exécute instruction 
  } // fin 

if (_utils.testInstruction2(chaineReceptionIn,"arriereGauche(",1,params)==true) { //si instruction avec 1 paramètre reçue valide
    arriereGauche(params[0]); // exécute instruction 
  } // fin 

  //-------------- test instruction enAvant avec vitesse ----------- 
    // mettre les formes avec le plus de paramètres d'abord...
  
  //---- enAvant avec vitesse et duree 
  //if (testInstruction2("enAvant(",2)==true) { // si instruction avec 2 paramètres reçue valide
  if (_utils.testInstruction2(chaineReceptionIn,"enAvant(",2,params)==true) { //si instruction avec 2 paramètre reçue valide
  
    //--- recupere et renomme les parametres recus
    long vitesseIn=params[0]; 
    long dureeIn=params[1];
   
    
    if (_debug) Serial.print(F("enAvant(")), Serial.print(vitesseIn),Serial.print(","), Serial.print(dureeIn), Serial.println(")");  
    
    enAvant(vitesseIn, dureeIn); // enAvant avec durée
        
  } // fin enAvant avec vitesse et duree

   else if (_utils.testInstruction2(chaineReceptionIn,"enAvant(",1,params)==true) { //si instruction avec 1 paramètre reçue valide

    enAvant(params[0]); // exécute instruction 

  } // fin test enAvant(xxx) 


  //-------------- test instruction enArriere ----------- 
  // mettre les formes avec le plus de paramètres d'abord...
  
  //---- enArriere avec vitesse et duree 

  //if (testInstruction2("enArriere(",2)==true) { // si instruction avec 2 paramètres reçue valide
  if (_utils.testInstruction2(chaineReceptionIn,"enArriere(",2,params)==true) { //si instruction avec 2 paramètre reçue valide
  
    //--- recupere et renomme les parametres recus
    long vitesseIn=params[0]; 
    long dureeIn=params[1];
   
    
    if (_debug) Serial.print(F("enArriere(")), Serial.print(vitesseIn),Serial.print(","), Serial.print(dureeIn), Serial.println(")");  
    
    enArriere(vitesseIn, dureeIn); // enAvant
       
  } // fin enArriere avec vitesse et duree

  else if (_utils.testInstruction2(chaineReceptionIn,"enArriere(",1,params)==true) { //si instruction avec 1 paramètre reçue valide
    enArriere(params[0]); // exécute instruction 
  } // fin test enArriere(xxx) 




  //-------------- test instruction tourne Droite -----------
  // mettre les formes avec le plus de paramètres d'abord...  
  
  //---- tourneDroite avec vitesse et duree 
  if (_utils.testInstruction2(chaineReceptionIn,"tourneDroite(",2,params)==true) { //si instruction avec 1 paramètre reçue valide    
    //--- recupere et renomme les parametres recus
    long vitesseIn=params[0]; 
    long dureeIn=params[1];
   
    
    if (_debug) Serial.print(F("tourneDroite(")), Serial.print(vitesseIn),Serial.print(","), Serial.print(dureeIn), Serial.println(")");  
    
    tourneDroite(vitesseIn, dureeIn); // enAvant
        
  } // fin tourneDroite avec vitesse et duree
 
  //-- tourneDroite avec vitesse seule 
    else if (_utils.testInstruction2(chaineReceptionIn,"tourneDroite(",1,params)==true) { //si instruction avec 1 paramètre reçue valide
    tourneDroite(params[0]); // exécute instruction 
  } // fin test tourneDroite(xxx) 



  //-------------- test instruction tourne Gauche ----------- 
   // mettre les formes avec le plus de paramètres d'abord...  
   
  //---- tourneGauche avec vitesse et duree 
  //if (testInstruction2("tourneGauche(",2)==true) { // si instruction avec 2 paramètres reçue valide

/*
  //-- test avec n paramètres -- 
   if (utils.testInstruction2(chaineReception,"tourneGauche(",6,params)==true) { //si instruction avec 3 paramètres reçue valide    

    //--- test 3 paramètres 
    
  } // fin tourneGauche avec vitesse et duree
  */

   if (_utils.testInstruction2(chaineReceptionIn,"tourneGauche(",2,params)==true) { //si instruction avec 2 paramètres reçue valide    
    //--- recupere et renomme les parametres recus
    long vitesseIn=params[0]; 
    long dureeIn=params[1];
   
    
    if (_debug) Serial.print(F("tourneGauche(")), Serial.print(vitesseIn),Serial.print(","), Serial.print(dureeIn), Serial.println(")");  
    
    tourneGauche(vitesseIn, dureeIn); // tourne gauche
    
    
  } // fin tourneGauche avec vitesse et duree

  //else if (testInstruction2("tourneGauche(",1)==true) { // si instruction avec 1 paramètre reçue valide
  else if (_utils.testInstruction2(chaineReceptionIn,"tourneGauche(",1,params)==true) { //si instruction avec 1 paramètre reçue valide    
    tourneGauche(params[0]); // exécute instruction 
  } // fin test tourneGauche(xxx) 

//------------- instructions étalonnage ---------- 
if (_utils.testInstruction2(chaineReceptionIn,"impulsGauche(",1,params)==true) { //si instruction avec 1 paramètre reçue valide    
    impulsGauche(params[0]); // exécute instruction 
  } // fin test tourneGauche(xxx) 

if (_utils.testInstruction2(chaineReceptionIn,"impulsDroit(",1,params)==true) { //si instruction avec 1 paramètre reçue valide    
    impulsDroit(params[0]); // exécute instruction 
  } // fin test tourneGauche(xxx) 

} ///////////////////////////////////// fin fonction analyse chaine /////////////////////////////////

