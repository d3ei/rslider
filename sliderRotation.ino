
/*
 * Tête rotative pour caméra
 * 01-2020
 * J
 */

/*
 * Biblio moteur pas à pas
 */
#include <Stepper.h>

/*
 * Nombre de pas du moteur pour 1 tour
 * A adapter en fonction de votre moteur
 */
const int stepsPerRevolution = 2048;

/*
 * degrés de rotation entre le début et la fin du mouvement
 */
const int rotationAngle = 30;

/*
 * Durée de rotation en minutes entre le début et la fin du mouvement
 */
const int rotationDuration = 10;

/*
 * Sens horaire : 1 - Sens anti-horaire -1
 */
const int rotationDirection = 1;

/*
 * Initialisation du moteur
 * Attention à l'ordre des pins
 * Sur mon arduino Nano la liaison avec le driver UKN2003 est la suivante : 
 *  IN1 => Arduino D8
 *  IN2 => Arduino D9
 *  IN3 => Arduino D10
 *  IN4 => Arduino D11
 * Et l'initialisation du moteur comme ci-dessous :
 * Stepper myStepper(stepsPerRevolution, IN2, IN4, IN3, IN1);
 */
Stepper myStepper(stepsPerRevolution, 9, 11, 10, 8);

void setup() {
  /*
   * Vitesse 1 tour par minute soit 2048 pas / 60 secondes
   * Vous pouvez modifier mais pour des timelapses j'ai pris la plus basse vitesse
   */
  myStepper.setSpeed(1);
  
  /*
   * Délai de 10s avant de commencer
   */
  delay(10000);
  Serial.begin(9600);
}

/*
 * Calcul nombre de pas pour la rotation demandée
 * Facteur 3 pour rapport courroie GT2 20 dents à GT2 60 dents.
 */
int nbStepsForRotation = (stepsPerRevolution / 360) * rotationAngle * 3;

/*
 * Délai en millisecondes entre deux pas pour la durée de rotation
 */
int delayMilliSecond = (rotationDuration  * 60000) / nbStepsForRotation;

void loop() {
  Serial.println("Delai millisecondes : ");
  Serial.print(delayMilliSecond);
  int nbSteps = 0;
  do {
    /*
     * Un pas dans le sens de rotation défini plus haut
     */
    myStepper.step(rotationDirection);
    /*
     * Attente entre deux pas pour adapter à la durée totale de rotation
     */
    delay(delayMilliSecond);
    nbSteps++;
  } while (nbSteps <= nbStepsForRotation);
  /*
   * Attends 120 secondes à la fin
   * Attention : au-delà le loop() recommence ;)
   */
  delay(120000);
}
