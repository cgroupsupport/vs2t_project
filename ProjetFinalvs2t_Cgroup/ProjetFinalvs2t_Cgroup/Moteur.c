/*---------------------------------------------------------------------------*/
/**
 * \file Moteur.c
 * \date 25/09/2015
 * \authors : C group, équipe surveillance
 * \copyright 	C group : Secuity Department
 * 
 * Composant : CY8C29466-24PXI
 * Réglage Pixymon : Arduini ICSP SPI
 *
 * Balayage et asservissement du moteur
 */
/*----------------------------------------------------------------------------*/

#include "Moteur.h"
#include "capteur.h"

int asservissement(void ){
	
	static int posx = 0, posy = 0, posximage = 0, posximageprec = 0, posximageprecprec = 1, posyimage = 2, posyimageprec = 0, i =  1, posnextgd = 166, posnexthb = 166, count = 0;
	
	if (BlockCam.signature== 1){
		//Asservissement sur l'axe x et y		
		if (i>=1) {
			i=0;
			posx=LED2_PWM_wReadPulseWidth();
			posximageprec = posximage;
			posximage = BlockCam.x;
			posy=LED1_PWM_wReadPulseWidth();
			posyimageprec = posyimage;
			posyimage = BlockCam.y;
		
			if (count >= 1 && posximageprecprec == posximage){
				count++;
				if (count >= 500){
					LED_1_Invert();
					return 1;
				}
			}
			else if (posximage == posximageprec){
				posximageprecprec = posximageprec;
				count = 1;
			}
			else {
				count = 0;
			}
		
			if (posximage == 0){
				posnextgd = LED2_PWM_wReadPulseWidth();
			}
			if(posximage>0x118 && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()+6;
			}
			if(posximage>0xFA && posximage<=0x118 && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()+5;
			}
			if(posximage>0xDC && posximage<=0xFA && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()+3;
			}
			if(posximage>0xBE && posximage<=0xDC && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()+2;
			}
			if(posximage>0xAA && posximage<=0xBE && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()+1;
			}
			if(posximage<0x96 && posximage>=0x82 && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()-1;			
			}
			if(posximage<0x82 && posximage>=0x64 && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()-2;			
			}
			if(posximage<0x64 && posximage>=0x46 && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()-3;			
			}
			if(posximage<0x46 && posximage>=0x28 && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()-5;			
			}
			if(posximage<0x28 && posximageprec != posximage){
				posnextgd = LED2_PWM_wReadPulseWidth()-6;			
			}
			if (posyimage == 0){
				posnexthb = LED1_PWM_wReadPulseWidth();
			}
			if(posyimage>0x7D && posyimageprec != posyimage){
				posnexthb = LED1_PWM_wReadPulseWidth()+3;
			}
			if(posyimage<0x4B && posyimageprec != posyimage){
				posnexthb = LED1_PWM_wReadPulseWidth()-3;
			}
		}	
		if (i<1 && count == 0){
			//On fixe la position à la position haute			
			LED2_PWM_WritePulseWidth(posnextgd);
			LED1_PWM_WritePulseWidth(posnexthb);
			i++;
		}
		else if (i<1 && count > 0) {
			i++;
			return 0;
		}
	}	
	return 0;
}

void balayage(void ){
	
	static int j=0, h=0;
	
	//Balayage aller de l'axe des x à la position basse
	if (h<400 && j==0){
		if (h>0){
			LED2_PWM_WritePulseWidth(144);
		}
		if (h>100){
			LED2_PWM_WritePulseWidth(207);
		}
		if (h>200){
			LED2_PWM_WritePulseWidth(270);
		}
		if (h>300){
			LED1_PWM_WritePulseWidth(270);
		}
		h=h+1;
	}
	else if (h==40 && j==0) {
		j=1;
	}
	//Balayage retour de l'axe des x à la position haute
	if (h>1 && j == 1){
		if (h<400){
			LED2_PWM_WritePulseWidth(223);
		}
		if (h<300){
			LED2_PWM_WritePulseWidth(176);
		}
		if (h<200){
			LED2_PWM_WritePulseWidth(129);
		}
		if (h<100){
			LED2_PWM_WritePulseWidth(82);
		}
		if (h<50){
			LED1_PWM_WritePulseWidth(82);
		}
		h=h-1;
	}
	//Condition nécessaire pour lancer un nouveau balayage
	else if (h== 1 && j==1){
		j=0;
	}
}
