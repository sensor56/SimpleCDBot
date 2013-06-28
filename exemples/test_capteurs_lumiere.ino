// --- constantes des broches ---

const int RVarD=2; //declaration constante de broche analogique
const int RVarG=3; //declaration constante de broche analogique

// --- Déclaration des variables globales ---
int mesureBruteD=0;// Variable pour acquisition résultat brut de conversion analogique numérique
int mesureBruteG=0;// Variable pour acquisition résultat brut de conversion analogique numérique

int seuilD=600; // Variable fixant le seuil de détection de l'obscurité - à adapter
int seuilG=600; // Variable fixant le seuil de détection de l'obscurité - à adapter

//**************** FONCTION SETUP = Code d'initialisation *****

void setup()   { // debut de la fonction setup()

Serial.begin(115200); // initialise connexion série à 115200 bauds
// IMPORTANT : régler le terminal côté PC avec la même valeur de transmission 


} // fin de la fonction setup()

//***** FONCTION LOOP = Boucle sans fin *****


void loop(){ // debut de la fonction loop()

// acquisition conversion analogique-numerique (CAN) sur la voie analogique
mesureBruteD=analogRead(RVarD); 
mesureBruteG=analogRead(RVarG); 

// affiche valeur numerique entière ou à virgule au format décimal
Serial.print("Gauche="); Serial.print(mesureBruteG); 
Serial.print("Droit="); Serial.print(mesureBruteD); 
Serial.println(); 

if (mesureBruteD<seuilD) Serial.println("Obscurite detectee a droite"); // message si obscurité détectée
if (mesureBruteG<seuilG) Serial.println("Obscurite detectee a gauche"); // message si obscurité détectée

delay(500);

} // fin de la fonction loop() - le programme recommence au début de la fonction loop sans fin
