/*---------------------------------------------------------------------------*/
/**
 * \file LCDetUART.h
 * \date 25/09/2015
 * \authors : C group, équipe surveillance
 * \copyright 	C group : Secuity Department
 * 
 * Composant : CY8C29466-24PXI
 * Réglage Pixymon : Arduini ICSP SPI
 *
 * Affichage et envoi des infomartions de Pixy
 */
/*----------------------------------------------------------------------------*/


/* \fn printCoor
* \param	void
* \return	void
* \brief	affiche les informations d'un bloc à l'écran
*/
void printCoor(void);

/* \fn printRS232
* \param	void
* \return	void
* \brief	Envoie les informations de la caméra via la liaison RS232
*/
void printRS232(void);
