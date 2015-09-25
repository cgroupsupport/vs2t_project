
/*---------------------------------------------------------------------------*/
/**
 * \file Capteur.c
 * \date 25/09/2015
 * \authors : Cgroup & ENSI Corp
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

#include "capteur.h"

enum BlockType blockT;


int getBlocks(int maxBlocks, int master)
{
  int i;
  int w, checksum, sum, blockCount;
  static int skipStart;
  
  if (!skipStart)
  {
    if (getStart(master)==0)
      return 0;
  }
  else{
	}
	
  for(blockCount=0; blockCount<maxBlocks && blockCount<PIXY_MAXIMUM_ARRAYSIZE;)
  {
    checksum = getWord(master);
    if (checksum==PIXY_START_WORD) // we've reached the beginning of the next frame
    {
      skipStart = 1;
	  blockT = NORMAL_BLOCK;
	  //Serial.println("skip");
      return blockCount;
    }
	else if (checksum==PIXY_START_WORD_CC)
	{
	  skipStart = 1;
	  blockT = CC_BLOCK;
	  return blockCount;
	}
    else if (checksum==0){
    	return blockCount;
	}
	
    for (i=0, sum=0; i<sizeof(struct Block)/sizeof(int); i++)
    {
	  if (blockT==NORMAL_BLOCK && i>=5) // skip 
	  {
		BlockCam.angle = 0;
		break;
	 }
      w = getWord(master);
	 if (i==0){
	   BlockCam.signature = w;
	 }
 	 else if(i==1){
	   BlockCam.x = w;
	}
	else if(i==2){
	   BlockCam.y = w;
	}
	else if(i==3){
	   BlockCam.width = w;
	}
	else if(i==4){
	   BlockCam.height = w;
	}
	
      sum += w;
    }

    if (checksum==sum)
      blockCount++;
	
	w = getWord(master);
	if (w==PIXY_START_WORD){
	  blockT = NORMAL_BLOCK;
	}
	else if (w==PIXY_START_WORD_CC)
	  blockT = CC_BLOCK;
	else
      return blockCount;
  }
}


int getWord(int master)
 {
      // ordering is different because Pixy is sending 16 bits through SPI 
      // instead of 2 bytes in a 16-bit word as with I2C
      int w;
	  static int outIndex =0, outLen = 0, outBuf[PIXY_OUTBUF_SIZE];
      BYTE c, cout = 0;


      if (outLen)
      {
		if (master == 1){
			while (!(SPIM_1_bReadStatus()&SPIM_1_SPIM_TX_BUFFER_EMPTY));
			SPIM_1_SendTxData(PIXY_SYNC_BYTE_DATA);
		
			while (!(	SPIM_1_bReadStatus()&SPIM_1_SPIM_RX_BUFFER_FULL));
			w = SPIM_1_bReadRxData();
		}
		else if(master == 2){
			while (!(SPIM_2_bReadStatus()&SPIM_2_SPIM_TX_BUFFER_EMPTY));
			SPIM_2_SendTxData(PIXY_SYNC_BYTE_DATA);
		
			while (!(	SPIM_2_bReadStatus()&SPIM_2_SPIM_RX_BUFFER_FULL));
			w = SPIM_2_bReadRxData();
		}
       	cout = outBuf[outIndex++];
        if (outIndex==outLen)
         	outLen = 0; 
      }
      else{
		if (master == 1){
			while (!(SPIM_1_bReadStatus()&SPIM_1_SPIM_TX_BUFFER_EMPTY));
			SPIM_1_SendTxData(PIXY_SYNC_BYTE);
			while (!(	SPIM_1_bReadStatus()&SPIM_1_SPIM_RX_BUFFER_FULL));
			w = SPIM_1_bReadRxData();
		}
		else if(master == 2){
			while (!(SPIM_2_bReadStatus()&SPIM_2_SPIM_TX_BUFFER_EMPTY));
			SPIM_2_SendTxData(PIXY_SYNC_BYTE);
			while (!(	SPIM_2_bReadStatus()&SPIM_2_SPIM_RX_BUFFER_FULL));
			w = SPIM_2_bReadRxData();
		}	
      	w <<= 8;
		if (master == 1){
     		while (!(SPIM_1_bReadStatus()&SPIM_1_SPIM_TX_BUFFER_EMPTY));
			SPIM_1_SendTxData(cout);
		
			while (!(	SPIM_1_bReadStatus()&SPIM_1_SPIM_RX_BUFFER_FULL));
			c = SPIM_1_bReadRxData();
		}
		else if(master == 2){
			while (!(SPIM_2_bReadStatus()&SPIM_2_SPIM_TX_BUFFER_EMPTY));
			SPIM_2_SendTxData(cout);
		
			while (!(	SPIM_2_bReadStatus()&SPIM_2_SPIM_RX_BUFFER_FULL));
			c = SPIM_2_bReadRxData();
		}
     	 w |= c;	
	   }
        return w;
  }

 int getByte(int master)
 {
	if (master == 1){
		while (!(SPIM_1_bReadStatus()&SPIM_1_SPIM_TX_BUFFER_EMPTY));
		SPIM_1_SendTxData(0x00);
		
		while (!(	SPIM_1_bReadStatus()&SPIM_1_SPIM_RX_BUFFER_FULL));
    	return SPIM_1_bReadRxData();
	}
	else if(master == 2){
		while (!(SPIM_2_bReadStatus()&SPIM_2_SPIM_TX_BUFFER_EMPTY));
		SPIM_2_SendTxData(0x00);
		
		while (!(	SPIM_2_bReadStatus()&SPIM_2_SPIM_RX_BUFFER_FULL));
    	return SPIM_2_bReadRxData();
	}
 }

int getStart(int master)
{
  int w, lastw, i;
 
  lastw = 0xffff;
  
  while(1)
  {
    w = getWord(master);
    if (w==0 && lastw==0)
	{
	  	return 0;
	}		
    else if (w==PIXY_START_WORD && lastw==PIXY_START_WORD){
		return 1;}
	else if (w==PIXY_START_WORDX)
	{
	  getByte(master); // resync
	}
	lastw = w; 
	
  }
}
