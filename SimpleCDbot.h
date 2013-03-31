/*
 * Librairie RobotCCx2
 *
 * Cette librairie implémente les fonctions types utiles 
 * sur un robot utilisant 2 moteurs CC contrôlés chacun 
 * par une broche de sens et de vitesse.
 *
 * Copyright (c) 2012 by Xavier HINAULT - support@mon-club-elec.fr
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 3
 * or the GNU Lesser General Public License version 3, both as
 * published by the Free Software Foundation.
 * 
 */

#ifndef SimpleCDbot_h
#define SimpleCDbot_h

#include "Arduino.h"
#include "Servo.h"
#include "Utils.h"


class SimpleCDbot {

  private : // déclaration (et seulement déclaration !) des variables _internes de la classe 

  //------ variables et constantes internes de broches de moteurs
	// -- ne pas utiliser constantes si on veut initialiser valeur avec le constructeur - constante = initilisation obligatoire à la déclaration
 	int _Droit; // servo Droit a l'indice 0
	int _Gauche; // servo Droit a l'indice 1

	int _neutre[2]; // largeur impulsion arret - 1 par moteur

	int _maxAV[2]; // largeur impulsion vitesse max en avant
	int _maxAR[2]; // largeur impulsion vitesse max en arriere

	int _brocheServo[2]; // broches des servomoteur 

	boolean _debug; // drapeau de messages de debug - false par défaut

	int _AVANT; // constante sens moteur
	int _ARRIERE; // constante sens moteur
	int _STOP; // constante vitesse moteur

	Utils _utils; // objet utils donnant accès aux fonctions de la lib
  
  public :

	Servo _servo[2]; // déclaration d'un tableau de 2 objets servomoteurs

	//------ déclaration des constructeurs de la librairie --- 
 	SimpleCDbot(); // constructeur par défaut 
	SimpleCDbot(int brocheServoDroitIn, int maxARDroit, int maxAVDroit, int brocheServoGaucheIn, int maxARGauche, int maxAVGauche, int neutreDroit, int neutreGauche); // constructeur avec initialisation 

	//--- déclaration des fonctions publiques de la librairie 

	//------ fonctions d'étalonnage des servomoteurs ---------- 
 	void impulsServo(int indiceServo,int largeurImpulsIn);
	void impulsDroit(int largeurImpulsIn);
	void impulsGauche(int largeurImpulsIn);

	//------ mouvements individuels des servomoteurs -----
	void servoAvant(int indiceServo, int vitesseIn);  // fonction principale 
	void avantDroit(int vitesseIn); 
	void avantGauche(int vitesseIn); 
 
	void servoArriere(int indiceServo, int vitesseIn); // fonction principale
	void arriereDroit(int vitesseIn); 
	void arriereGauche(int vitesseIn); 

	void arret(); 
	void arret(int dureeIn); 

	//------ mouvements synchrone des servomoteurs ---- 

	void enAvant(int vitesseIn);
	void enAvant(int vitesseIn, int dureeIn);

	void enArriere(int vitesseIn);
	void enArriere(int vitesseIn, int dureeIn);

	void tourneDroite(int vitesseIn);
	void tourneDroite(int vitesseIn, int dureeIn);

	void tourneGauche(int vitesseIn);
	void tourneGauche(int vitesseIn, int dureeIn);

	//------ analyse chaine ---------- 
	void infosAnalyseChaine();
	void analyseChaine(String chaineRecue); 

	//------ fonctions de paramétrages internes --- 
	void setDebug(boolean flagIn);
	
  
  private : // fonctions internes


};


#endif
