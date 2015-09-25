/**
 * \file moteur.h
 * \date 25/09/2015
 * \authors : C group, équipe surveillance
 * \copyright 	C group : Secuity Department
 * 
 * Composant : CY8C29466-24PXI
 * Réglage Pixymon : Arduini ICSP SPI
 *
 * Balayage et asservissement du moteur
 */


/** 
 * \fn asservissement
 * \param 	void
 * \return	void int renvoie 0 si une cible est détectée, 1 si aucune cible n'est détectée pendant  * un certain temps
 * \brief	Fonction permettant l'asservissement des moteurs en fonction de la position des caméras
*/
int asservissement(void );

/**
 * \fn balayage
 * \param 	void
 * \return	void
 * \brief	Fonction permettant le balayage des caméras
 */
void balayage(void );