/*---------------------------------------------------------------------------*/
/**
 * \file main.c
 * \date 25/09/2015
 * \authors : C group, équipe surveillance
 * \copyright 	C group : Secuity Department
 * 
 * Composant : CY8C29466-24PXI
 * Réglage Pixymon : Arduini ICSP SPI
 *
 * Liaison SPI avec une caméra pixy CMUCAM et Timer au vu d'une communication avec une seconde
 * caméra
 *
 * La caméra envoie les informations (signature s, abscisse x, ordonnée y, hautur de l'objet
 * h, largeur de l'objet w et l'angle = 0) d'un objet qu'elle détecte
 *
 * Si elle ne reçoit pas d'information, les informations du dernier objet reste affichées sur
 * l'écran
 */
/*----------------------------------------------------------------------------*/

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "stdio.h" 
#include "stdlib.h" 
#include "math.h" 
#include "string.h" 
#include "capteur.h"
#include "LCDetUART.h"
#include "Moteur.h"

#pragma interrupt_handler Timer32_1_ISR

// Bloc contenant les informations de l'objet envoyé à l'écran
struct Block BlockCam;

void Timer32_1_ISR(void);

void main(void)
{
	char LCDBuffer[15];
	
	LCD_1_Start();
	
	// Initialise le buffer d'envoi et de réception
    UART_1_CmdReset(); 
	
	// Autorisation des interruptions globales
	M8C_EnableGInt;
    
    //Autorise les interruptions sur RX
    UART_1_IntCntl(UART_1_ENABLE_RX_INT);       
   
	// Paramétrage pour aucun bit de parité
    UART_1_Start(UART_1_PARITY_NONE);
	
	// Démarrage du Timer au vu d'ajouter une deuxième caméra
	Timer32_1_Start();
	
	// Autorisation des interruptions pour le timer
	Timer32_1_EnableInt();
	
	LED1_PWM_Start();
	LED2_PWM_Start();
	
	SPIM_1_Start(SPIM_1_SPIM_MODE_0 | SPIM_1_SPIM_MSB_FIRST);  
	SPIM_2_Start(SPIM_2_SPIM_MODE_0 | SPIM_2_SPIM_MSB_FIRST); 
	
	
	while (1){
		}
}

 /* \fn Timer32_1_ISR
* \param 	void
* \return	void
* \brief	Fonction d'interruption activé par le timer à chaque front montant, permet par la
* suite d'utiliser les deux caméras successivement.
*/
void Timer32_1_ISR(void)
{
	int maxBlocks=1, k, j=0;
	static int masterCam = 1, h=0;
	
	// Lis les informations de l'objet
	if (masterCam == 1){
		k = getBlocks(maxBlocks, masterCam);
		masterCam=2;
	}
	else if (masterCam == 2){
		k = getBlocks(maxBlocks, masterCam);
		masterCam=1;
	}
	
	j = asservissement();
	
	if (j==1){
		balayage();
	}

	// Affiche ces informations sur l'écran
	printCoor();
	
	if(h==25){
		printRS232();
		h=0;
	}
	h++;
}
