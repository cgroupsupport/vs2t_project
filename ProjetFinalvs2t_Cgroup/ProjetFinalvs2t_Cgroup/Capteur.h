/*---------------------------------------------------------------------------*/
/**
 * \file capteur.h
 * \date 25/09/2015
 * \authors C group, équipe surveillance
 * \copyright 	C group : Secuity Department
 * 
 * Composant : CY8C29466-24PXI
 * Réglage Pixymon : Arduini ICSP SPI
 *
 * Liaison SPI avec une caméra pixy CMUCAM et Timer au vu d'une communication avec une seconde
 * caméra
 * La caméra envoie les informations (signature s, abscisse x, ordonnée y, hautur de l'objet h, 
 * largeur de l'objet w et l'angle = 0) d'un objet qu'elle détecte
 * Si elle ne reçoit pas d'information, les informations du dernier objet reste affichées sur 
 * l'écran
 */
/*----------------------------------------------------------------------------*/


#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

#define PIXY_SYNC_BYTE              0x5a
#define PIXY_SYNC_BYTE_DATA         0x5b
#define PIXY_OUTBUF_SIZE            6

#define PIXY_INITIAL_ARRAYSIZE      30
#define PIXY_MAXIMUM_ARRAYSIZE      130
#define PIXY_START_WORD             0xaa55
#define PIXY_START_WORD_CC          0xaa56
#define PIXY_START_WORDX            0x55aa
#define PIXY_MAX_SIGNATURE          7
#define PIXY_DEFAULT_ARGVAL         0xffff

// deux types de detection d'objet : couleur, bloc
enum BlockType
{
	NORMAL_BLOCK,
	CC_BLOCK
};

// Information d'un objet
struct Block 
{
  // print block structure!
  int signature;
  int x;
  int y;
  int width;
  int height;
  int angle;
};

// Bloc contenant les informations de l'objet envoyé à l'écran
extern struct Block BlockCam;

/** 
 * \fn getBlocks
 * \param 	int maxBlocks nombre de bloc à lire
 * \return	int renvoie le nombre de bloc lu
 * \brief	lis les données issues des caméras
*/
int getBlocks(int maxBlocks, int master);


/* \fn getWord
* \param 	int maxBlocks : nombre de bloc à lire
* \return	int : renvoie le mot de 16 bits
* \brief	Renvoie un bloc de 16 bits 
*/
int getWord(int master);

/* \fn getByte
* \param 	int maxBlocks : nombre de bloc à lire
* \return	int mot de 8 bits
* \brief	Renvoie un bloc de 8 bits, permet de réaligner les séquences entre le PSOC et Pixy
 */
int getByte(int master);

/* \fn getStart(void)
* \param 	void
* \return	int renvoie 0 si la communication ne démarre pas, 1 si elle peut démarrer
* \brief	Fonction permet d'introduire la communication avec Pixy
 */
int getStart(int master);
