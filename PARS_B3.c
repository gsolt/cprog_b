/**+**************************************************************************
* NAME           :  PARS_B.c                                                 *
* DESCRIPTION    :  This example demonstrates a way of self learning the     *
*                   site ID and the link ID. By pushing PB1, the RTU sends a *
*                   broadcast message to inform the other RTU about its      *
*                   own site ID and link ID. After this stage, each RTU may  *
*                   send a message to the other RTU and expects to get an    *
*                   echo which will be logged in the error logger.           *
*                   By pushing PB2, the RTU sends the string "THE QUICK.." to*
*                   the designated RTU. The designated RTU echoes the same   *
*                   string as an answer. The source RTU logs the message in  *
*                   the error logger.                                        *
* PROCESS        :  The example includes three functions -                   *
*                                                                            *
*                   tx_new_site:- The function sets the first line in the    *
*                   static site table with site id 0 (using                  *
*                   MOSCAD_set_sitetable), and sends its own site/link as a  *
*                   a broadcast.                                             *
*                                                                            *
*                   tx:- The function sends the string "THE QUICK.." to      *
*                   designated RTU.                                          *
*                                                                            *
*                   rx- should be called all the time.  rx may receive three *
                    types of messages:                                       *
*                       1) TxFrm message- This means that PB1 was pushed and *
*                          the receiving buffer contains the site ID and     *
*                          the link ID of the sender.                        *
*                       2) SndFrm message-This means that PB2 was pushed and *
*                          the receiving buffer contains the string. It      *
*                          echoes it as an answer.                           *
*                       3) AnsFrm Message-The receiving buffer contains echo.*
*                          It logs it in the error logger.                   *
*                                                                            *
* [C] Copyright Zsolt Gergely,  2003.  All Rights Reserved                 *
*                                                                            *
* REV    DATE     PROGRAMMER         REVISION HISTORY                        *
* V2.1.23	2013.10.29	Gergely Zsolt		51-42				*

*****************************************************************************/

#include "CAPPLIC.H"
#include <stdio.h>
/* Parameterek strukturaja */
#include "strPar.H"




/*--------------------------------------------------------------------------*/
/* Prototypes and defines                                                   */
/*--------------------------------------------------------------------------*/

extern void setdat(unsigned char *input);

/**********************************************/
/* Globals                                     */
/**********************************************/


/*--------------------------------------------------------------------------*/
/* The list of the function included in this block                          */
/*--------------------------------------------------------------------------*/
/*const CB_JUMPTBL user_jumptable[]=
{
   {"setdat"   , setdat},  	
   {0      , 0 }
};*/
/*--------------------------------------------------------------------------*/
/* 'C' Block Initialization and Completion                                  */
/*--------------------------------------------------------------------------*/
/*void user_control_function(int control)
{
unsigned long		lTotal;
unsigned long		lLargest;
unsigned long		lBlockSize;
unsigned char		*byP;	
int					nI;
	
	
   switch(control)
      {
         case CB_INIT :
         	
            break;

         case CB_EXIT :
         	
         break;
      }
}*/


/****************************************************************************/
/* Parameter strukturak feltoltese     										*/
/****************************************************************************/
void setdat(unsigned char *input)
{
	int					nI;
	TOTAL_PAR			*sT;
	
	sT = (TOTAL_PAR *)input;
	
/* TMOK jelszámok inicializálása ciklusban */	
for (nI = 0;nI<	MAX_RTU;nI++)
{
	sT[0].sMOT[nI].nIEC_SP_NUM = 14;
	sT[0].sMOT[nI].nIEC_DP_NUM  = 1;
	sT[0].sMOT[nI].nNMNum      = 3;
}

/* Single command inicializálása ciklusban */	
for (nI = 0;nI<	MAX_RTU;nI++)
{
sT[0].sCP[0].sCPR[nI].nSCNum  = 1;
}

sT[0].sCP[0].sCPR[0].nDCStart  = 0;    sT[0].sCP[0].sCPR[0].nDCNum  = 0;    sT[0].sCP[0].sCPR[0].nSCStart  = 1;    sT[0].sCP[0].sCPR[0].nAckStart  =0;    sT[0].sCP[0].sCPR[0].nAckNum  =0;   sT[0].sCP[0].sCPR[0].nSPOffsetCS  = 6;   sT[0].sCP[0].sCPR[0].nSPOffsetLek  = 7; 	
sT[0].sCP[0].sCPR[1].nDCStart  = 2;    sT[0].sCP[0].sCPR[1].nDCNum  = 4;    sT[0].sCP[0].sCPR[1].nSCStart  = 7;    sT[0].sCP[0].sCPR[1].nAckStart  =6;    sT[0].sCP[0].sCPR[1].nAckNum  =1;   sT[0].sCP[0].sCPR[1].nSPOffsetCS  = 43;  sT[0].sCP[0].sCPR[1].nSPOffsetLek  = 44;
sT[0].sCP[0].sCPR[2].nDCStart  = 0;    sT[0].sCP[0].sCPR[2].nDCNum  = 0;    sT[0].sCP[0].sCPR[2].nSCStart  = 8;    sT[0].sCP[0].sCPR[2].nAckStart  =0;    sT[0].sCP[0].sCPR[2].nAckNum  =0;   sT[0].sCP[0].sCPR[2].nSPOffsetCS  = 1248;sT[0].sCP[0].sCPR[2].nSPOffsetLek  = 1249;
sT[0].sCP[0].sCPR[3].nDCStart  = 0;    sT[0].sCP[0].sCPR[3].nDCNum  = 0;    sT[0].sCP[0].sCPR[3].nSCStart  = 9;    sT[0].sCP[0].sCPR[3].nAckStart  =0;    sT[0].sCP[0].sCPR[3].nAckNum  =0;   sT[0].sCP[0].sCPR[3].nSPOffsetCS  = 58;  sT[0].sCP[0].sCPR[3].nSPOffsetLek  = 59;
sT[0].sCP[0].sCPR[4].nDCStart  = 0;    sT[0].sCP[0].sCPR[4].nDCNum  = 0;    sT[0].sCP[0].sCPR[4].nSCStart  = 10;   sT[0].sCP[0].sCPR[4].nAckStart  =0;    sT[0].sCP[0].sCPR[4].nAckNum  =0;   sT[0].sCP[0].sCPR[4].nSPOffsetCS  = 71;  sT[0].sCP[0].sCPR[4].nSPOffsetLek  = 72;
sT[0].sCP[0].sCPR[5].nDCStart  = 11;   sT[0].sCP[0].sCPR[5].nDCNum  = 3;    sT[0].sCP[0].sCPR[5].nSCStart  = 14;   sT[0].sCP[0].sCPR[5].nAckStart  =0;    sT[0].sCP[0].sCPR[5].nAckNum  =0;   sT[0].sCP[0].sCPR[5].nSPOffsetCS  = 86;  sT[0].sCP[0].sCPR[5].nSPOffsetLek  = 87;
sT[0].sCP[0].sCPR[6].nDCStart  = 760;  sT[0].sCP[0].sCPR[6].nDCNum  = 4;    sT[0].sCP[0].sCPR[6].nSCStart  = 15;   sT[0].sCP[0].sCPR[6].nAckStart  =0;    sT[0].sCP[0].sCPR[6].nAckNum  =0;   sT[0].sCP[0].sCPR[6].nSPOffsetCS  = 123; sT[0].sCP[0].sCPR[6].nSPOffsetLek  = 124;
sT[0].sCP[0].sCPR[7].nDCStart  = 279;  sT[0].sCP[0].sCPR[7].nDCNum  = 1;    sT[0].sCP[0].sCPR[7].nSCStart  = 16;   sT[0].sCP[0].sCPR[7].nAckStart  =0;    sT[0].sCP[0].sCPR[7].nAckNum  =0;   sT[0].sCP[0].sCPR[7].nSPOffsetCS  = 1222;sT[0].sCP[0].sCPR[7].nSPOffsetLek  = 1223;
sT[0].sCP[0].sCPR[8].nDCStart  = 17;   sT[0].sCP[0].sCPR[8].nDCNum  = 3;    sT[0].sCP[0].sCPR[8].nSCStart  = 20;   sT[0].sCP[0].sCPR[8].nAckStart  =0;    sT[0].sCP[0].sCPR[8].nAckNum  =0;   sT[0].sCP[0].sCPR[8].nSPOffsetCS  = 146; sT[0].sCP[0].sCPR[8].nSPOffsetLek  = 147;
sT[0].sCP[0].sCPR[9].nDCStart  = 21;   sT[0].sCP[0].sCPR[9].nDCNum  = 1;    sT[0].sCP[0].sCPR[9].nSCStart  = 22;   sT[0].sCP[0].sCPR[9].nAckStart  =392;  sT[0].sCP[0].sCPR[9].nAckNum  =1;   sT[0].sCP[0].sCPR[9].nSPOffsetCS  = 163; sT[0].sCP[0].sCPR[9].nSPOffsetLek  = 164;
sT[0].sCP[0].sCPR[10].nDCStart = 0;    sT[0].sCP[0].sCPR[10].nDCNum = 0;    sT[0].sCP[0].sCPR[10].nSCStart = 23;   sT[0].sCP[0].sCPR[10].nAckStart =0;    sT[0].sCP[0].sCPR[10].nAckNum =0;   sT[0].sCP[0].sCPR[10].nSPOffsetCS = 170; sT[0].sCP[0].sCPR[10].nSPOffsetLek = 171;
sT[0].sCP[0].sCPR[11].nDCStart = 24;   sT[0].sCP[0].sCPR[11].nDCNum = 1;    sT[0].sCP[0].sCPR[11].nSCStart = 25;   sT[0].sCP[0].sCPR[11].nAckStart =0;    sT[0].sCP[0].sCPR[11].nAckNum =0;   sT[0].sCP[0].sCPR[11].nSPOffsetCS = 186; sT[0].sCP[0].sCPR[11].nSPOffsetLek = 187;
sT[0].sCP[0].sCPR[12].nDCStart = 26;   sT[0].sCP[0].sCPR[12].nDCNum = 1;    sT[0].sCP[0].sCPR[12].nSCStart = 27;   sT[0].sCP[0].sCPR[12].nAckStart =0;    sT[0].sCP[0].sCPR[12].nAckNum =0;   sT[0].sCP[0].sCPR[12].nSPOffsetCS = 202; sT[0].sCP[0].sCPR[12].nSPOffsetLek = 203;
sT[0].sCP[0].sCPR[13].nDCStart = 28;   sT[0].sCP[0].sCPR[13].nDCNum = 1;    sT[0].sCP[0].sCPR[13].nSCStart = 29;   sT[0].sCP[0].sCPR[13].nAckStart =395;  sT[0].sCP[0].sCPR[13].nAckNum =1;   sT[0].sCP[0].sCPR[13].nSPOffsetCS = 218; sT[0].sCP[0].sCPR[13].nSPOffsetLek = 219;
sT[0].sCP[0].sCPR[14].nDCStart = 30;   sT[0].sCP[0].sCPR[14].nDCNum = 1;    sT[0].sCP[0].sCPR[14].nSCStart = 31;   sT[0].sCP[0].sCPR[14].nAckStart =391;  sT[0].sCP[0].sCPR[14].nAckNum =1;   sT[0].sCP[0].sCPR[14].nSPOffsetCS = 234; sT[0].sCP[0].sCPR[14].nSPOffsetLek = 235;
sT[0].sCP[0].sCPR[15].nDCStart = 0;    sT[0].sCP[0].sCPR[15].nDCNum = 0;    sT[0].sCP[0].sCPR[15].nSCStart = 32;   sT[0].sCP[0].sCPR[15].nAckStart =0;    sT[0].sCP[0].sCPR[15].nAckNum =0;   sT[0].sCP[0].sCPR[15].nSPOffsetCS = 241; sT[0].sCP[0].sCPR[15].nSPOffsetLek = 242;
sT[0].sCP[0].sCPR[16].nDCStart = 33;   sT[0].sCP[0].sCPR[16].nDCNum = 1;    sT[0].sCP[0].sCPR[16].nSCStart = 34;   sT[0].sCP[0].sCPR[16].nAckStart =752;  sT[0].sCP[0].sCPR[16].nAckNum =1;   sT[0].sCP[0].sCPR[16].nSPOffsetCS = 264; sT[0].sCP[0].sCPR[16].nSPOffsetLek = 265;
sT[0].sCP[0].sCPR[17].nDCStart = 0;    sT[0].sCP[0].sCPR[17].nDCNum = 0;    sT[0].sCP[0].sCPR[17].nSCStart = 35;   sT[0].sCP[0].sCPR[17].nAckStart =0;    sT[0].sCP[0].sCPR[17].nAckNum =0;   sT[0].sCP[0].sCPR[17].nSPOffsetCS = 271; sT[0].sCP[0].sCPR[17].nSPOffsetLek = 272;
sT[0].sCP[0].sCPR[18].nDCStart = 36;   sT[0].sCP[0].sCPR[18].nDCNum = 1;    sT[0].sCP[0].sCPR[18].nSCStart = 37;   sT[0].sCP[0].sCPR[18].nAckStart =0;    sT[0].sCP[0].sCPR[18].nAckNum =0;   sT[0].sCP[0].sCPR[18].nSPOffsetCS = 287; sT[0].sCP[0].sCPR[18].nSPOffsetLek = 288;
sT[0].sCP[0].sCPR[19].nDCStart = 38;   sT[0].sCP[0].sCPR[19].nDCNum = 1;    sT[0].sCP[0].sCPR[19].nSCStart = 39;   sT[0].sCP[0].sCPR[19].nAckStart =397;  sT[0].sCP[0].sCPR[19].nAckNum =1;   sT[0].sCP[0].sCPR[19].nSPOffsetCS = 303; sT[0].sCP[0].sCPR[19].nSPOffsetLek = 304;
sT[0].sCP[0].sCPR[20].nDCStart = 48;   sT[0].sCP[0].sCPR[20].nDCNum = 1;    sT[0].sCP[0].sCPR[20].nSCStart = 49;   sT[0].sCP[0].sCPR[20].nAckStart =0;    sT[0].sCP[0].sCPR[20].nAckNum =0;   sT[0].sCP[0].sCPR[20].nSPOffsetCS = 383; sT[0].sCP[0].sCPR[20].nSPOffsetLek = 384;
sT[0].sCP[0].sCPR[21].nDCStart = 58;   sT[0].sCP[0].sCPR[21].nDCNum = 1;    sT[0].sCP[0].sCPR[21].nSCStart = 59;   sT[0].sCP[0].sCPR[21].nAckStart =426;  sT[0].sCP[0].sCPR[21].nAckNum =1;   sT[0].sCP[0].sCPR[21].nSPOffsetCS = 463; sT[0].sCP[0].sCPR[21].nSPOffsetLek = 464;
sT[0].sCP[0].sCPR[22].nDCStart = 50;   sT[0].sCP[0].sCPR[22].nDCNum = 1;    sT[0].sCP[0].sCPR[22].nSCStart = 51;   sT[0].sCP[0].sCPR[22].nAckStart =427;  sT[0].sCP[0].sCPR[22].nAckNum =1;   sT[0].sCP[0].sCPR[22].nSPOffsetCS = 399; sT[0].sCP[0].sCPR[22].nSPOffsetLek = 400;
sT[0].sCP[0].sCPR[23].nDCStart = 52;   sT[0].sCP[0].sCPR[23].nDCNum = 1;    sT[0].sCP[0].sCPR[23].nSCStart = 53;   sT[0].sCP[0].sCPR[23].nAckStart =422;  sT[0].sCP[0].sCPR[23].nAckNum =1;   sT[0].sCP[0].sCPR[23].nSPOffsetCS = 415; sT[0].sCP[0].sCPR[23].nSPOffsetLek = 416;
sT[0].sCP[0].sCPR[24].nDCStart = 54;   sT[0].sCP[0].sCPR[24].nDCNum = 1;    sT[0].sCP[0].sCPR[24].nSCStart = 55;   sT[0].sCP[0].sCPR[24].nAckStart =423;  sT[0].sCP[0].sCPR[24].nAckNum =1;   sT[0].sCP[0].sCPR[24].nSPOffsetCS = 431; sT[0].sCP[0].sCPR[24].nSPOffsetLek = 432;
sT[0].sCP[0].sCPR[25].nDCStart = 56;   sT[0].sCP[0].sCPR[25].nDCNum = 1;    sT[0].sCP[0].sCPR[25].nSCStart = 57;   sT[0].sCP[0].sCPR[25].nAckStart =428;  sT[0].sCP[0].sCPR[25].nAckNum =1;   sT[0].sCP[0].sCPR[25].nSPOffsetCS = 447; sT[0].sCP[0].sCPR[25].nSPOffsetLek = 448;
sT[0].sCP[0].sCPR[26].nDCStart = 40;   sT[0].sCP[0].sCPR[26].nDCNum = 1;    sT[0].sCP[0].sCPR[26].nSCStart = 41;   sT[0].sCP[0].sCPR[26].nAckStart =0;    sT[0].sCP[0].sCPR[26].nAckNum =0;   sT[0].sCP[0].sCPR[26].nSPOffsetCS = 319; sT[0].sCP[0].sCPR[26].nSPOffsetLek = 320;
sT[0].sCP[0].sCPR[27].nDCStart = 42;   sT[0].sCP[0].sCPR[27].nDCNum = 1;    sT[0].sCP[0].sCPR[27].nSCStart = 43;   sT[0].sCP[0].sCPR[27].nAckStart =396;  sT[0].sCP[0].sCPR[27].nAckNum =1;   sT[0].sCP[0].sCPR[27].nSPOffsetCS = 335; sT[0].sCP[0].sCPR[27].nSPOffsetLek = 336;
sT[0].sCP[0].sCPR[28].nDCStart = 44;   sT[0].sCP[0].sCPR[28].nDCNum = 1;    sT[0].sCP[0].sCPR[28].nSCStart = 45;   sT[0].sCP[0].sCPR[28].nAckStart =0;    sT[0].sCP[0].sCPR[28].nAckNum =0;   sT[0].sCP[0].sCPR[28].nSPOffsetCS = 351; sT[0].sCP[0].sCPR[28].nSPOffsetLek = 352;
sT[0].sCP[0].sCPR[29].nDCStart = 46;   sT[0].sCP[0].sCPR[29].nDCNum = 1;    sT[0].sCP[0].sCPR[29].nSCStart = 47;   sT[0].sCP[0].sCPR[29].nAckStart =370;  sT[0].sCP[0].sCPR[29].nAckNum =1;   sT[0].sCP[0].sCPR[29].nSPOffsetCS = 367; sT[0].sCP[0].sCPR[29].nSPOffsetLek = 368;
sT[0].sCP[0].sCPR[30].nDCStart = 60;   sT[0].sCP[0].sCPR[30].nDCNum = 1;    sT[0].sCP[0].sCPR[30].nSCStart = 61;   sT[0].sCP[0].sCPR[30].nAckStart =372;  sT[0].sCP[0].sCPR[30].nAckNum =1;   sT[0].sCP[0].sCPR[30].nSPOffsetCS = 479; sT[0].sCP[0].sCPR[30].nSPOffsetLek = 480;
sT[0].sCP[0].sCPR[31].nDCStart = 62;   sT[0].sCP[0].sCPR[31].nDCNum = 1;    sT[0].sCP[0].sCPR[31].nSCStart = 63;   sT[0].sCP[0].sCPR[31].nAckStart =373;  sT[0].sCP[0].sCPR[31].nAckNum =1;   sT[0].sCP[0].sCPR[31].nSPOffsetCS = 495; sT[0].sCP[0].sCPR[31].nSPOffsetLek = 496;

sT[0].sCP[0].sCPR[32].nDCStart = 64;   sT[0].sCP[0].sCPR[32].nDCNum = 1;    sT[0].sCP[0].sCPR[32].nSCStart = 65;   sT[0].sCP[0].sCPR[32].nAckStart =0;    sT[0].sCP[0].sCPR[32].nAckNum =0;   sT[0].sCP[0].sCPR[32].nSPOffsetCS = 514; sT[0].sCP[0].sCPR[32].nSPOffsetLek = 515;
sT[0].sCP[0].sCPR[33].nDCStart = 66;   sT[0].sCP[0].sCPR[33].nDCNum = 1;    sT[0].sCP[0].sCPR[33].nSCStart = 67;   sT[0].sCP[0].sCPR[33].nAckStart =0;    sT[0].sCP[0].sCPR[33].nAckNum =0;   sT[0].sCP[0].sCPR[33].nSPOffsetCS = 530; sT[0].sCP[0].sCPR[33].nSPOffsetLek = 531;
sT[0].sCP[0].sCPR[34].nDCStart = 68;   sT[0].sCP[0].sCPR[34].nDCNum = 1;    sT[0].sCP[0].sCPR[34].nSCStart = 69;   sT[0].sCP[0].sCPR[34].nAckStart =362;  sT[0].sCP[0].sCPR[34].nAckNum =1;   sT[0].sCP[0].sCPR[34].nSPOffsetCS = 546; sT[0].sCP[0].sCPR[34].nSPOffsetLek = 547;
sT[0].sCP[0].sCPR[35].nDCStart = 70;   sT[0].sCP[0].sCPR[35].nDCNum = 1;    sT[0].sCP[0].sCPR[35].nSCStart = 71;   sT[0].sCP[0].sCPR[35].nAckStart =0;    sT[0].sCP[0].sCPR[35].nAckNum =0;   sT[0].sCP[0].sCPR[35].nSPOffsetCS = 562; sT[0].sCP[0].sCPR[35].nSPOffsetLek = 563;
sT[0].sCP[0].sCPR[36].nDCStart = 148;  sT[0].sCP[0].sCPR[36].nDCNum = 1;    sT[0].sCP[0].sCPR[36].nSCStart = 149;  sT[0].sCP[0].sCPR[36].nAckStart =0;    sT[0].sCP[0].sCPR[36].nAckNum =0;   sT[0].sCP[0].sCPR[36].nSPOffsetCS = 1206;sT[0].sCP[0].sCPR[36].nSPOffsetLek = 1207;
sT[0].sCP[0].sCPR[37].nDCStart = 72;   sT[0].sCP[0].sCPR[37].nDCNum = 1;    sT[0].sCP[0].sCPR[37].nSCStart = 73;   sT[0].sCP[0].sCPR[37].nAckStart =0;    sT[0].sCP[0].sCPR[37].nAckNum =0;   sT[0].sCP[0].sCPR[37].nSPOffsetCS = 578; sT[0].sCP[0].sCPR[37].nSPOffsetLek = 579;

sT[0].sCP[0].sCPR[38].nDCStart = 74;   sT[0].sCP[0].sCPR[38].nDCNum = 1;    sT[0].sCP[0].sCPR[38].nSCStart = 75;   sT[0].sCP[0].sCPR[38].nAckStart =371;  sT[0].sCP[0].sCPR[38].nAckNum =1;   sT[0].sCP[0].sCPR[38].nSPOffsetCS = 594; sT[0].sCP[0].sCPR[38].nSPOffsetLek = 595;
sT[0].sCP[0].sCPR[39].nDCStart = 76;   sT[0].sCP[0].sCPR[39].nDCNum = 1;    sT[0].sCP[0].sCPR[39].nSCStart = 77;   sT[0].sCP[0].sCPR[39].nAckStart =0;    sT[0].sCP[0].sCPR[39].nAckNum =0;   sT[0].sCP[0].sCPR[39].nSPOffsetCS = 610; sT[0].sCP[0].sCPR[39].nSPOffsetLek = 611;
sT[0].sCP[0].sCPR[40].nDCStart = 78;   sT[0].sCP[0].sCPR[40].nDCNum = 1;    sT[0].sCP[0].sCPR[40].nSCStart = 79;   sT[0].sCP[0].sCPR[40].nAckStart =0;    sT[0].sCP[0].sCPR[40].nAckNum =0;   sT[0].sCP[0].sCPR[40].nSPOffsetCS = 626; sT[0].sCP[0].sCPR[40].nSPOffsetLek = 627;
sT[0].sCP[0].sCPR[41].nDCStart = 80;   sT[0].sCP[0].sCPR[41].nDCNum = 1;    sT[0].sCP[0].sCPR[41].nSCStart = 81;   sT[0].sCP[0].sCPR[41].nAckStart =376;  sT[0].sCP[0].sCPR[41].nAckNum =1;   sT[0].sCP[0].sCPR[41].nSPOffsetCS = 642; sT[0].sCP[0].sCPR[41].nSPOffsetLek = 643;
sT[0].sCP[0].sCPR[42].nDCStart = 82;   sT[0].sCP[0].sCPR[42].nDCNum = 1;    sT[0].sCP[0].sCPR[42].nSCStart = 83;   sT[0].sCP[0].sCPR[42].nAckStart =375;  sT[0].sCP[0].sCPR[42].nAckNum =1;   sT[0].sCP[0].sCPR[42].nSPOffsetCS = 658; sT[0].sCP[0].sCPR[42].nSPOffsetLek = 659;

sT[0].sCP[0].sCPR[43].nDCStart = 84;   sT[0].sCP[0].sCPR[43].nDCNum = 1;    sT[0].sCP[0].sCPR[43].nSCStart = 85;   sT[0].sCP[0].sCPR[43].nAckStart =378;  sT[0].sCP[0].sCPR[43].nAckNum =1;   sT[0].sCP[0].sCPR[43].nSPOffsetCS = 674; sT[0].sCP[0].sCPR[43].nSPOffsetLek = 675;
sT[0].sCP[0].sCPR[44].nDCStart = 86;   sT[0].sCP[0].sCPR[44].nDCNum = 1;    sT[0].sCP[0].sCPR[44].nSCStart = 87;   sT[0].sCP[0].sCPR[44].nAckStart =0;    sT[0].sCP[0].sCPR[44].nAckNum =0;   sT[0].sCP[0].sCPR[44].nSPOffsetCS = 690; sT[0].sCP[0].sCPR[44].nSPOffsetLek = 691;
sT[0].sCP[0].sCPR[45].nDCStart = 88;   sT[0].sCP[0].sCPR[45].nDCNum = 1;    sT[0].sCP[0].sCPR[45].nSCStart = 89;   sT[0].sCP[0].sCPR[45].nAckStart =0;    sT[0].sCP[0].sCPR[45].nAckNum =0;   sT[0].sCP[0].sCPR[45].nSPOffsetCS = 706; sT[0].sCP[0].sCPR[45].nSPOffsetLek = 707;
sT[0].sCP[0].sCPR[46].nDCStart = 90;   sT[0].sCP[0].sCPR[46].nDCNum = 1;    sT[0].sCP[0].sCPR[46].nSCStart = 91;   sT[0].sCP[0].sCPR[46].nAckStart =429;  sT[0].sCP[0].sCPR[46].nAckNum =1;   sT[0].sCP[0].sCPR[46].nSPOffsetCS = 722; sT[0].sCP[0].sCPR[46].nSPOffsetLek = 723;
sT[0].sCP[0].sCPR[47].nDCStart = 92;   sT[0].sCP[0].sCPR[47].nDCNum = 1;    sT[0].sCP[0].sCPR[47].nSCStart = 93;   sT[0].sCP[0].sCPR[47].nAckStart =394;  sT[0].sCP[0].sCPR[47].nAckNum =1;   sT[0].sCP[0].sCPR[47].nSPOffsetCS = 738; sT[0].sCP[0].sCPR[47].nSPOffsetLek = 739;
sT[0].sCP[0].sCPR[48].nDCStart = 94;   sT[0].sCP[0].sCPR[48].nDCNum = 1;    sT[0].sCP[0].sCPR[48].nSCStart = 95;   sT[0].sCP[0].sCPR[48].nAckStart =363;  sT[0].sCP[0].sCPR[48].nAckNum =1;   sT[0].sCP[0].sCPR[48].nSPOffsetCS = 764; sT[0].sCP[0].sCPR[48].nSPOffsetLek = 765;
sT[0].sCP[0].sCPR[49].nDCStart = 96;   sT[0].sCP[0].sCPR[49].nDCNum = 1;    sT[0].sCP[0].sCPR[49].nSCStart = 97;   sT[0].sCP[0].sCPR[49].nAckStart =0;    sT[0].sCP[0].sCPR[49].nAckNum =0;   sT[0].sCP[0].sCPR[49].nSPOffsetCS = 780; sT[0].sCP[0].sCPR[49].nSPOffsetLek = 781;
sT[0].sCP[0].sCPR[50].nDCStart = 98;   sT[0].sCP[0].sCPR[50].nDCNum = 1;    sT[0].sCP[0].sCPR[50].nSCStart = 99;   sT[0].sCP[0].sCPR[50].nAckStart =364;  sT[0].sCP[0].sCPR[50].nAckNum =1;   sT[0].sCP[0].sCPR[50].nSPOffsetCS = 796; sT[0].sCP[0].sCPR[50].nSPOffsetLek = 797;
sT[0].sCP[0].sCPR[51].nDCStart = 100;  sT[0].sCP[0].sCPR[51].nDCNum = 1;    sT[0].sCP[0].sCPR[51].nSCStart = 101;  sT[0].sCP[0].sCPR[51].nAckStart =0;    sT[0].sCP[0].sCPR[51].nAckNum =0;   sT[0].sCP[0].sCPR[51].nSPOffsetCS = 812; sT[0].sCP[0].sCPR[51].nSPOffsetLek = 813;
sT[0].sCP[0].sCPR[52].nDCStart = 102;  sT[0].sCP[0].sCPR[52].nDCNum = 1;    sT[0].sCP[0].sCPR[52].nSCStart = 103;  sT[0].sCP[0].sCPR[52].nAckStart =0;    sT[0].sCP[0].sCPR[52].nAckNum =0;   sT[0].sCP[0].sCPR[52].nSPOffsetCS = 828; sT[0].sCP[0].sCPR[52].nSPOffsetLek = 829;

sT[0].sCP[0].sCPR[53].nDCStart = 104;  sT[0].sCP[0].sCPR[53].nDCNum = 1;    sT[0].sCP[0].sCPR[53].nSCStart = 105;  sT[0].sCP[0].sCPR[53].nAckStart =379;  sT[0].sCP[0].sCPR[53].nAckNum =1;   sT[0].sCP[0].sCPR[53].nSPOffsetCS = 844; sT[0].sCP[0].sCPR[53].nSPOffsetLek = 845;
sT[0].sCP[0].sCPR[54].nDCStart = 106;  sT[0].sCP[0].sCPR[54].nDCNum = 1;    sT[0].sCP[0].sCPR[54].nSCStart = 107;  sT[0].sCP[0].sCPR[54].nAckStart =0;    sT[0].sCP[0].sCPR[54].nAckNum =0;   sT[0].sCP[0].sCPR[54].nSPOffsetCS = 860; sT[0].sCP[0].sCPR[54].nSPOffsetLek = 861;
sT[0].sCP[0].sCPR[55].nDCStart = 108;  sT[0].sCP[0].sCPR[55].nDCNum = 1;    sT[0].sCP[0].sCPR[55].nSCStart = 109;  sT[0].sCP[0].sCPR[55].nAckStart =383;  sT[0].sCP[0].sCPR[55].nAckNum =1;   sT[0].sCP[0].sCPR[55].nSPOffsetCS = 876; sT[0].sCP[0].sCPR[55].nSPOffsetLek = 877;
sT[0].sCP[0].sCPR[56].nDCStart = 110;  sT[0].sCP[0].sCPR[56].nDCNum = 1;    sT[0].sCP[0].sCPR[56].nSCStart = 111;  sT[0].sCP[0].sCPR[56].nAckStart =387;  sT[0].sCP[0].sCPR[56].nAckNum =1;   sT[0].sCP[0].sCPR[56].nSPOffsetCS = 892; sT[0].sCP[0].sCPR[56].nSPOffsetLek = 893;
sT[0].sCP[0].sCPR[57].nDCStart = 112;  sT[0].sCP[0].sCPR[57].nDCNum = 1;    sT[0].sCP[0].sCPR[57].nSCStart = 113;  sT[0].sCP[0].sCPR[57].nAckStart =382;  sT[0].sCP[0].sCPR[57].nAckNum =1;   sT[0].sCP[0].sCPR[57].nSPOffsetCS = 908; sT[0].sCP[0].sCPR[57].nSPOffsetLek = 909;
sT[0].sCP[0].sCPR[58].nDCStart = 114;  sT[0].sCP[0].sCPR[58].nDCNum = 1;    sT[0].sCP[0].sCPR[58].nSCStart = 115;  sT[0].sCP[0].sCPR[58].nAckStart =377;  sT[0].sCP[0].sCPR[58].nAckNum =1;   sT[0].sCP[0].sCPR[58].nSPOffsetCS = 924; sT[0].sCP[0].sCPR[58].nSPOffsetLek = 925;
sT[0].sCP[0].sCPR[59].nDCStart = 116;  sT[0].sCP[0].sCPR[59].nDCNum = 1;    sT[0].sCP[0].sCPR[59].nSCStart = 117;  sT[0].sCP[0].sCPR[59].nAckStart =374;  sT[0].sCP[0].sCPR[59].nAckNum =1;   sT[0].sCP[0].sCPR[59].nSPOffsetCS = 940; sT[0].sCP[0].sCPR[59].nSPOffsetLek = 941;

sT[0].sCP[0].sCPR[60].nDCStart = 118;  sT[0].sCP[0].sCPR[60].nDCNum = 1;    sT[0].sCP[0].sCPR[60].nSCStart = 119;  sT[0].sCP[0].sCPR[60].nAckStart =0;    sT[0].sCP[0].sCPR[60].nAckNum =0;   sT[0].sCP[0].sCPR[60].nSPOffsetCS = 956;  sT[0].sCP[0].sCPR[60].nSPOffsetLek = 957;
sT[0].sCP[0].sCPR[61].nDCStart = 120;  sT[0].sCP[0].sCPR[61].nDCNum = 1;    sT[0].sCP[0].sCPR[61].nSCStart = 121;  sT[0].sCP[0].sCPR[61].nAckStart =0;    sT[0].sCP[0].sCPR[61].nAckNum =0;   sT[0].sCP[0].sCPR[61].nSPOffsetCS = 972;  sT[0].sCP[0].sCPR[61].nSPOffsetLek = 973;
sT[0].sCP[0].sCPR[62].nDCStart = 122;  sT[0].sCP[0].sCPR[62].nDCNum = 1;    sT[0].sCP[0].sCPR[62].nSCStart = 123;  sT[0].sCP[0].sCPR[62].nAckStart =367;  sT[0].sCP[0].sCPR[62].nAckNum =1;   sT[0].sCP[0].sCPR[62].nSPOffsetCS = 988;  sT[0].sCP[0].sCPR[62].nSPOffsetLek = 989;
sT[0].sCP[0].sCPR[63].nDCStart = 124;  sT[0].sCP[0].sCPR[63].nDCNum = 1;    sT[0].sCP[0].sCPR[63].nSCStart = 125;  sT[0].sCP[0].sCPR[63].nAckStart =0;    sT[0].sCP[0].sCPR[63].nAckNum =0;   sT[0].sCP[0].sCPR[63].nSPOffsetCS = 1014; sT[0].sCP[0].sCPR[63].nSPOffsetLek = 1015;
sT[0].sCP[0].sCPR[64].nDCStart = 126;  sT[0].sCP[0].sCPR[64].nDCNum = 1;    sT[0].sCP[0].sCPR[64].nSCStart = 127;  sT[0].sCP[0].sCPR[64].nAckStart =388;  sT[0].sCP[0].sCPR[64].nAckNum =1;   sT[0].sCP[0].sCPR[64].nSPOffsetCS = 1030; sT[0].sCP[0].sCPR[64].nSPOffsetLek = 1031;
sT[0].sCP[0].sCPR[65].nDCStart = 128;  sT[0].sCP[0].sCPR[65].nDCNum = 1;    sT[0].sCP[0].sCPR[65].nSCStart = 129;  sT[0].sCP[0].sCPR[65].nAckStart =421;  sT[0].sCP[0].sCPR[65].nAckNum =1;   sT[0].sCP[0].sCPR[65].nSPOffsetCS = 1046; sT[0].sCP[0].sCPR[65].nSPOffsetLek = 1047;
sT[0].sCP[0].sCPR[66].nDCStart = 130;  sT[0].sCP[0].sCPR[66].nDCNum = 1;    sT[0].sCP[0].sCPR[66].nSCStart = 131;  sT[0].sCP[0].sCPR[66].nAckStart =365;  sT[0].sCP[0].sCPR[66].nAckNum =1;   sT[0].sCP[0].sCPR[66].nSPOffsetCS = 1062; sT[0].sCP[0].sCPR[66].nSPOffsetLek = 1063;
sT[0].sCP[0].sCPR[67].nDCStart = 132;  sT[0].sCP[0].sCPR[67].nDCNum = 1;    sT[0].sCP[0].sCPR[67].nSCStart = 133;  sT[0].sCP[0].sCPR[67].nAckStart =393;  sT[0].sCP[0].sCPR[67].nAckNum =1;   sT[0].sCP[0].sCPR[67].nSPOffsetCS = 1078; sT[0].sCP[0].sCPR[67].nSPOffsetLek = 1079;
sT[0].sCP[0].sCPR[68].nDCStart = 134;  sT[0].sCP[0].sCPR[68].nDCNum = 1;    sT[0].sCP[0].sCPR[68].nSCStart = 135;  sT[0].sCP[0].sCPR[68].nAckStart =0;    sT[0].sCP[0].sCPR[68].nAckNum =0;   sT[0].sCP[0].sCPR[68].nSPOffsetCS = 1094; sT[0].sCP[0].sCPR[68].nSPOffsetLek = 1095;
sT[0].sCP[0].sCPR[69].nDCStart = 136;  sT[0].sCP[0].sCPR[69].nDCNum = 1;    sT[0].sCP[0].sCPR[69].nSCStart = 137;  sT[0].sCP[0].sCPR[69].nAckStart =0;    sT[0].sCP[0].sCPR[69].nAckNum =0;   sT[0].sCP[0].sCPR[69].nSPOffsetCS = 1110; sT[0].sCP[0].sCPR[69].nSPOffsetLek = 1111;

sT[0].sCP[0].sCPR[70].nDCStart = 138;  sT[0].sCP[0].sCPR[70].nDCNum = 1;    sT[0].sCP[0].sCPR[70].nSCStart = 139;  sT[0].sCP[0].sCPR[70].nAckStart =366;  sT[0].sCP[0].sCPR[70].nAckNum =1;   sT[0].sCP[0].sCPR[70].nSPOffsetCS = 1126; sT[0].sCP[0].sCPR[70].nSPOffsetLek = 1127;
sT[0].sCP[0].sCPR[71].nDCStart = 140;  sT[0].sCP[0].sCPR[71].nDCNum = 1;    sT[0].sCP[0].sCPR[71].nSCStart = 141;  sT[0].sCP[0].sCPR[71].nAckStart =424;  sT[0].sCP[0].sCPR[71].nAckNum =1;   sT[0].sCP[0].sCPR[71].nSPOffsetCS = 1142; sT[0].sCP[0].sCPR[71].nSPOffsetLek = 1143;
sT[0].sCP[0].sCPR[72].nDCStart = 142;  sT[0].sCP[0].sCPR[72].nDCNum = 1;    sT[0].sCP[0].sCPR[72].nSCStart = 143;  sT[0].sCP[0].sCPR[72].nAckStart =0;    sT[0].sCP[0].sCPR[72].nAckNum =0;   sT[0].sCP[0].sCPR[72].nSPOffsetCS = 1158; sT[0].sCP[0].sCPR[72].nSPOffsetLek = 1159;
sT[0].sCP[0].sCPR[73].nDCStart = 144;  sT[0].sCP[0].sCPR[73].nDCNum = 1;    sT[0].sCP[0].sCPR[73].nSCStart = 145;  sT[0].sCP[0].sCPR[73].nAckStart =369;  sT[0].sCP[0].sCPR[73].nAckNum =1;   sT[0].sCP[0].sCPR[73].nSPOffsetCS = 1174; sT[0].sCP[0].sCPR[73].nSPOffsetLek = 1175;
sT[0].sCP[0].sCPR[74].nDCStart = 146;  sT[0].sCP[0].sCPR[74].nDCNum = 1;    sT[0].sCP[0].sCPR[74].nSCStart = 147;  sT[0].sCP[0].sCPR[74].nAckStart =368;  sT[0].sCP[0].sCPR[74].nAckNum =1;   sT[0].sCP[0].sCPR[74].nSPOffsetCS = 1190; sT[0].sCP[0].sCPR[74].nSPOffsetLek = 1191;

sT[0].sCP[0].sCPR[75].nDCStart = 0;    sT[0].sCP[0].sCPR[75].nDCNum = 0;    sT[0].sCP[0].sCPR[75].nSCStart = 185;  sT[0].sCP[0].sCPR[75].nAckStart =0;    sT[0].sCP[0].sCPR[75].nAckNum =0;   sT[0].sCP[0].sCPR[75].nSPOffsetCS = 248;  sT[0].sCP[0].sCPR[75].nSPOffsetLek = 249;
sT[0].sCP[0].sCPR[76].nDCStart = 152;  sT[0].sCP[0].sCPR[76].nDCNum = 1;    sT[0].sCP[0].sCPR[76].nSCStart = 153;  sT[0].sCP[0].sCPR[76].nAckStart =0;    sT[0].sCP[0].sCPR[76].nAckNum =0;   sT[0].sCP[0].sCPR[76].nSPOffsetCS = 1238; sT[0].sCP[0].sCPR[76].nSPOffsetLek = 1239;
sT[0].sCP[0].sCPR[77].nDCStart = 154;  sT[0].sCP[0].sCPR[77].nDCNum = 1;    sT[0].sCP[0].sCPR[77].nSCStart = 155;  sT[0].sCP[0].sCPR[77].nAckStart =756;  sT[0].sCP[0].sCPR[77].nAckNum =1;   sT[0].sCP[0].sCPR[77].nSPOffsetCS = 1264; sT[0].sCP[0].sCPR[77].nSPOffsetLek = 1265;
sT[0].sCP[0].sCPR[78].nDCStart = 148;  sT[0].sCP[0].sCPR[78].nDCNum = 1;    sT[0].sCP[0].sCPR[78].nSCStart = 149;  sT[0].sCP[0].sCPR[78].nAckStart =0;    sT[0].sCP[0].sCPR[78].nAckNum =0;   sT[0].sCP[0].sCPR[78].nSPOffsetCS = 1206; sT[0].sCP[0].sCPR[78].nSPOffsetLek = 1207;
sT[0].sCP[0].sCPR[79].nDCStart = 156;  sT[0].sCP[0].sCPR[79].nDCNum = 1;    sT[0].sCP[0].sCPR[79].nSCStart = 157;  sT[0].sCP[0].sCPR[79].nAckStart =513;  sT[0].sCP[0].sCPR[79].nAckNum =1;   sT[0].sCP[0].sCPR[79].nSPOffsetCS = 1280; sT[0].sCP[0].sCPR[79].nSPOffsetLek = 1281;
sT[0].sCP[0].sCPR[80].nDCStart = 158;  sT[0].sCP[0].sCPR[80].nDCNum = 1;    sT[0].sCP[0].sCPR[80].nSCStart = 159;  sT[0].sCP[0].sCPR[80].nAckStart =0;    sT[0].sCP[0].sCPR[80].nAckNum =0;   sT[0].sCP[0].sCPR[80].nSPOffsetCS = 1296; sT[0].sCP[0].sCPR[80].nSPOffsetLek = 1297;

sT[0].sCP[0].sCPR[81].nDCStart = 160;  sT[0].sCP[0].sCPR[81].nDCNum = 1;    sT[0].sCP[0].sCPR[81].nSCStart = 161;  sT[0].sCP[0].sCPR[81].nAckStart =0;    sT[0].sCP[0].sCPR[81].nAckNum =0;   sT[0].sCP[0].sCPR[81].nSPOffsetCS = 1312; sT[0].sCP[0].sCPR[81].nSPOffsetLek = 1313;
sT[0].sCP[0].sCPR[82].nDCStart = 162;  sT[0].sCP[0].sCPR[82].nDCNum = 1;    sT[0].sCP[0].sCPR[82].nSCStart = 163;  sT[0].sCP[0].sCPR[82].nAckStart =0;    sT[0].sCP[0].sCPR[82].nAckNum =0;   sT[0].sCP[0].sCPR[82].nSPOffsetCS = 1328; sT[0].sCP[0].sCPR[82].nSPOffsetLek = 1329;
sT[0].sCP[0].sCPR[83].nDCStart = 164;  sT[0].sCP[0].sCPR[83].nDCNum = 1;    sT[0].sCP[0].sCPR[83].nSCStart = 165;  sT[0].sCP[0].sCPR[83].nAckStart =389;  sT[0].sCP[0].sCPR[83].nAckNum =1;   sT[0].sCP[0].sCPR[83].nSPOffsetCS = 1344; sT[0].sCP[0].sCPR[83].nSPOffsetLek = 1345;
sT[0].sCP[0].sCPR[84].nDCStart = 166;  sT[0].sCP[0].sCPR[84].nDCNum = 1;    sT[0].sCP[0].sCPR[84].nSCStart = 167;  sT[0].sCP[0].sCPR[84].nAckStart =390;  sT[0].sCP[0].sCPR[84].nAckNum =1;   sT[0].sCP[0].sCPR[84].nSPOffsetCS = 1360; sT[0].sCP[0].sCPR[84].nSPOffsetLek = 1361;
sT[0].sCP[0].sCPR[85].nDCStart = 168;  sT[0].sCP[0].sCPR[85].nDCNum = 1;    sT[0].sCP[0].sCPR[85].nSCStart = 169;  sT[0].sCP[0].sCPR[85].nAckStart =0;    sT[0].sCP[0].sCPR[85].nAckNum =0;   sT[0].sCP[0].sCPR[85].nSPOffsetCS = 1376; sT[0].sCP[0].sCPR[85].nSPOffsetLek = 1377;
sT[0].sCP[0].sCPR[86].nDCStart = 170;  sT[0].sCP[0].sCPR[86].nDCNum = 1;    sT[0].sCP[0].sCPR[86].nSCStart = 171;  sT[0].sCP[0].sCPR[86].nAckStart =515;  sT[0].sCP[0].sCPR[86].nAckNum =1;   sT[0].sCP[0].sCPR[86].nSPOffsetCS = 1392; sT[0].sCP[0].sCPR[86].nSPOffsetLek = 1393;

sT[0].sCP[0].sCPR[87].nDCStart = 172;  sT[0].sCP[0].sCPR[87].nDCNum = 1;    sT[0].sCP[0].sCPR[87].nSCStart = 173;  sT[0].sCP[0].sCPR[87].nAckStart =0;    sT[0].sCP[0].sCPR[87].nAckNum =0;   sT[0].sCP[0].sCPR[87].nSPOffsetCS = 1408; sT[0].sCP[0].sCPR[87].nSPOffsetLek = 1409;
sT[0].sCP[0].sCPR[88].nDCStart = 174;  sT[0].sCP[0].sCPR[88].nDCNum = 1;    sT[0].sCP[0].sCPR[88].nSCStart = 175;  sT[0].sCP[0].sCPR[88].nAckStart =0;    sT[0].sCP[0].sCPR[88].nAckNum =0;   sT[0].sCP[0].sCPR[88].nSPOffsetCS = 1424; sT[0].sCP[0].sCPR[88].nSPOffsetLek = 1425;
sT[0].sCP[0].sCPR[89].nDCStart = 176;  sT[0].sCP[0].sCPR[89].nDCNum = 1;    sT[0].sCP[0].sCPR[89].nSCStart = 177;  sT[0].sCP[0].sCPR[89].nAckStart =514;  sT[0].sCP[0].sCPR[89].nAckNum =1;   sT[0].sCP[0].sCPR[89].nSPOffsetCS = 1440; sT[0].sCP[0].sCPR[89].nSPOffsetLek = 1441;
sT[0].sCP[0].sCPR[90].nDCStart = 178;  sT[0].sCP[0].sCPR[90].nDCNum = 1;    sT[0].sCP[0].sCPR[90].nSCStart = 179;  sT[0].sCP[0].sCPR[90].nAckStart =508;  sT[0].sCP[0].sCPR[90].nAckNum =1;   sT[0].sCP[0].sCPR[90].nSPOffsetCS = 1456; sT[0].sCP[0].sCPR[90].nSPOffsetLek = 1457;
sT[0].sCP[0].sCPR[91].nDCStart = 180;  sT[0].sCP[0].sCPR[91].nDCNum = 1;    sT[0].sCP[0].sCPR[91].nSCStart = 181;  sT[0].sCP[0].sCPR[91].nAckStart =749;  sT[0].sCP[0].sCPR[91].nAckNum =1;   sT[0].sCP[0].sCPR[91].nSPOffsetCS = 1472; sT[0].sCP[0].sCPR[91].nSPOffsetLek = 1473;
sT[0].sCP[0].sCPR[92].nDCStart = 182;  sT[0].sCP[0].sCPR[92].nDCNum = 1;    sT[0].sCP[0].sCPR[92].nSCStart = 183;  sT[0].sCP[0].sCPR[92].nAckStart =0;    sT[0].sCP[0].sCPR[92].nAckNum =0;   sT[0].sCP[0].sCPR[92].nSPOffsetCS = 1488; sT[0].sCP[0].sCPR[92].nSPOffsetLek = 1489;
sT[0].sCP[0].sCPR[93].nDCStart = 0;    sT[0].sCP[0].sCPR[93].nDCNum = 0;    sT[0].sCP[0].sCPR[93].nSCStart = 184;  sT[0].sCP[0].sCPR[93].nAckStart =0;    sT[0].sCP[0].sCPR[93].nAckNum =0;   sT[0].sCP[0].sCPR[93].nSPOffsetCS = 745;  sT[0].sCP[0].sCPR[93].nSPOffsetLek = 746;

sT[0].sCP[0].sCPR[94].nDCStart = 186;  sT[0].sCP[0].sCPR[94].nDCNum = 1;    sT[0].sCP[0].sCPR[94].nSCStart = 187;  sT[0].sCP[0].sCPR[94].nAckStart =506;  sT[0].sCP[0].sCPR[94].nAckNum =1;   sT[0].sCP[0].sCPR[94].nSPOffsetCS = 1514; sT[0].sCP[0].sCPR[94].nSPOffsetLek = 1515;
sT[0].sCP[0].sCPR[95].nDCStart = 188;  sT[0].sCP[0].sCPR[95].nDCNum = 1;    sT[0].sCP[0].sCPR[95].nSCStart = 189;  sT[0].sCP[0].sCPR[95].nAckStart =0;    sT[0].sCP[0].sCPR[95].nAckNum =0;   sT[0].sCP[0].sCPR[95].nSPOffsetCS = 1530; sT[0].sCP[0].sCPR[95].nSPOffsetLek = 1531;
sT[0].sCP[0].sCPR[96].nDCStart = 190;  sT[0].sCP[0].sCPR[96].nDCNum = 1;    sT[0].sCP[0].sCPR[96].nSCStart = 191;  sT[0].sCP[0].sCPR[96].nAckStart =748;  sT[0].sCP[0].sCPR[96].nAckNum =1;   sT[0].sCP[0].sCPR[96].nSPOffsetCS = 1546; sT[0].sCP[0].sCPR[96].nSPOffsetLek = 1547;
sT[0].sCP[0].sCPR[97].nDCStart = 192;  sT[0].sCP[0].sCPR[97].nDCNum = 1;    sT[0].sCP[0].sCPR[97].nSCStart = 193;  sT[0].sCP[0].sCPR[97].nAckStart =0;    sT[0].sCP[0].sCPR[97].nAckNum =0;   sT[0].sCP[0].sCPR[97].nSPOffsetCS = 1562; sT[0].sCP[0].sCPR[97].nSPOffsetLek = 1563;

sT[0].sCP[0].sCPR[98].nDCStart = 194;  sT[0].sCP[0].sCPR[98].nDCNum = 1;    sT[0].sCP[0].sCPR[98].nSCStart = 195;  sT[0].sCP[0].sCPR[98].nAckStart =507;  sT[0].sCP[0].sCPR[98].nAckNum =1;   sT[0].sCP[0].sCPR[98].nSPOffsetCS = 1578; sT[0].sCP[0].sCPR[98].nSPOffsetLek = 1579;
sT[0].sCP[0].sCPR[99].nDCStart = 196;  sT[0].sCP[0].sCPR[99].nDCNum = 1;    sT[0].sCP[0].sCPR[99].nSCStart = 197;  sT[0].sCP[0].sCPR[99].nAckStart =0;    sT[0].sCP[0].sCPR[99].nAckNum =0;   sT[0].sCP[0].sCPR[99].nSPOffsetCS = 1594; sT[0].sCP[0].sCPR[99].nSPOffsetLek = 1595;
sT[0].sCP[0].sCPR[100].nDCStart= 198; sT[0].sCP[0].sCPR[100].nDCNum = 1;   sT[0].sCP[0].sCPR[100].nSCStart = 199;  sT[0].sCP[0].sCPR[100].nAckStart =751; sT[0].sCP[0].sCPR[100].nAckNum =1;  sT[0].sCP[0].sCPR[100].nSPOffsetCS = 1610; sT[0].sCP[0].sCPR[100].nSPOffsetLek = 1611;
sT[0].sCP[0].sCPR[101].nDCStart= 200; sT[0].sCP[0].sCPR[101].nDCNum = 1;   sT[0].sCP[0].sCPR[101].nSCStart = 201;  sT[0].sCP[0].sCPR[101].nAckStart =753; sT[0].sCP[0].sCPR[101].nAckNum =1;  sT[0].sCP[0].sCPR[101].nSPOffsetCS = 1626; sT[0].sCP[0].sCPR[101].nSPOffsetLek = 1627;

sT[0].sCP[0].sCPR[102].nDCStart= 202; sT[0].sCP[0].sCPR[102].nDCNum = 1;   sT[0].sCP[0].sCPR[102].nSCStart = 203;  sT[0].sCP[0].sCPR[102].nAckStart =516; sT[0].sCP[0].sCPR[102].nAckNum =1;  sT[0].sCP[0].sCPR[102].nSPOffsetCS = 1642; sT[0].sCP[0].sCPR[102].nSPOffsetLek = 1643;
sT[0].sCP[0].sCPR[103].nDCStart= 204; sT[0].sCP[0].sCPR[103].nDCNum = 1;   sT[0].sCP[0].sCPR[103].nSCStart = 205;  sT[0].sCP[0].sCPR[103].nAckStart =510; sT[0].sCP[0].sCPR[103].nAckNum =1;  sT[0].sCP[0].sCPR[103].nSPOffsetCS = 1658; sT[0].sCP[0].sCPR[103].nSPOffsetLek = 1659;
sT[0].sCP[0].sCPR[104].nDCStart= 206; sT[0].sCP[0].sCPR[104].nDCNum = 1;   sT[0].sCP[0].sCPR[104].nSCStart = 207;  sT[0].sCP[0].sCPR[104].nAckStart =755; sT[0].sCP[0].sCPR[104].nAckNum =1;  sT[0].sCP[0].sCPR[104].nSPOffsetCS = 1674; sT[0].sCP[0].sCPR[104].nSPOffsetLek = 1675;
sT[0].sCP[0].sCPR[105].nDCStart= 208; sT[0].sCP[0].sCPR[105].nDCNum = 1;   sT[0].sCP[0].sCPR[105].nSCStart = 209;  sT[0].sCP[0].sCPR[105].nAckStart =0;   sT[0].sCP[0].sCPR[105].nAckNum =0;  sT[0].sCP[0].sCPR[105].nSPOffsetCS = 1690; sT[0].sCP[0].sCPR[105].nSPOffsetLek = 1691;

sT[0].sCP[0].sCPR[106].nDCStart= 236; sT[0].sCP[0].sCPR[106].nDCNum = 1;   sT[0].sCP[0].sCPR[106].nSCStart = 237;  sT[0].sCP[0].sCPR[106].nAckStart =758; sT[0].sCP[0].sCPR[106].nAckNum =1;  sT[0].sCP[0].sCPR[106].nSPOffsetCS = 1924; sT[0].sCP[0].sCPR[106].nSPOffsetLek = 1925;
sT[0].sCP[0].sCPR[107].nDCStart= 238; sT[0].sCP[0].sCPR[107].nDCNum = 1;   sT[0].sCP[0].sCPR[107].nSCStart = 239;  sT[0].sCP[0].sCPR[107].nAckStart =0;   sT[0].sCP[0].sCPR[107].nAckNum =0;  sT[0].sCP[0].sCPR[107].nSPOffsetCS = 1940; sT[0].sCP[0].sCPR[107].nSPOffsetLek = 1941;

sT[0].sCP[0].sCPR[108].nDCStart= 240; sT[0].sCP[0].sCPR[108].nDCNum = 1;   sT[0].sCP[0].sCPR[108].nSCStart = 241;  sT[0].sCP[0].sCPR[108].nAckStart =754; sT[0].sCP[0].sCPR[108].nAckNum =1;  sT[0].sCP[0].sCPR[108].nSPOffsetCS = 1956; sT[0].sCP[0].sCPR[108].nSPOffsetLek = 1957;
sT[0].sCP[0].sCPR[109].nDCStart= 242; sT[0].sCP[0].sCPR[109].nDCNum = 1;   sT[0].sCP[0].sCPR[109].nSCStart = 243;  sT[0].sCP[0].sCPR[109].nAckStart =757; sT[0].sCP[0].sCPR[109].nAckNum =1;  sT[0].sCP[0].sCPR[109].nSPOffsetCS = 1972; sT[0].sCP[0].sCPR[109].nSPOffsetLek = 1973;
sT[0].sCP[0].sCPR[110].nDCStart= 244; sT[0].sCP[0].sCPR[110].nDCNum = 1;   sT[0].sCP[0].sCPR[110].nSCStart = 245;  sT[0].sCP[0].sCPR[110].nAckStart =750; sT[0].sCP[0].sCPR[110].nAckNum =1;  sT[0].sCP[0].sCPR[110].nSPOffsetCS = 1988; sT[0].sCP[0].sCPR[110].nSPOffsetLek = 1989;
sT[0].sCP[0].sCPR[111].nDCStart= 246; sT[0].sCP[0].sCPR[111].nDCNum = 1;   sT[0].sCP[0].sCPR[111].nSCStart = 247;  sT[0].sCP[0].sCPR[111].nAckStart =0;   sT[0].sCP[0].sCPR[111].nAckNum =0;  sT[0].sCP[0].sCPR[111].nSPOffsetCS = 2014; sT[0].sCP[0].sCPR[111].nSPOffsetLek = 2015;

sT[0].sCP[0].sCPR[112].nDCStart= 210; sT[0].sCP[0].sCPR[112].nDCNum = 1;   sT[0].sCP[0].sCPR[112].nSCStart = 211;  sT[0].sCP[0].sCPR[112].nAckStart =0;   sT[0].sCP[0].sCPR[112].nAckNum =0;  sT[0].sCP[0].sCPR[112].nSPOffsetCS = 1706; sT[0].sCP[0].sCPR[112].nSPOffsetLek = 1707;
sT[0].sCP[0].sCPR[113].nDCStart= 212; sT[0].sCP[0].sCPR[113].nDCNum = 1;   sT[0].sCP[0].sCPR[113].nSCStart = 213;  sT[0].sCP[0].sCPR[113].nAckStart =0;   sT[0].sCP[0].sCPR[113].nAckNum =0;  sT[0].sCP[0].sCPR[113].nSPOffsetCS = 1722; sT[0].sCP[0].sCPR[113].nSPOffsetLek = 1723;
sT[0].sCP[0].sCPR[114].nDCStart= 248; sT[0].sCP[0].sCPR[114].nDCNum = 1;   sT[0].sCP[0].sCPR[114].nSCStart = 249;  sT[0].sCP[0].sCPR[114].nAckStart =0;   sT[0].sCP[0].sCPR[114].nAckNum =0;  sT[0].sCP[0].sCPR[114].nSPOffsetCS = 2030; sT[0].sCP[0].sCPR[114].nSPOffsetLek = 2031;
sT[0].sCP[0].sCPR[115].nDCStart= 220; sT[0].sCP[0].sCPR[115].nDCNum = 1;   sT[0].sCP[0].sCPR[115].nSCStart = 221;  sT[0].sCP[0].sCPR[115].nAckStart =509; sT[0].sCP[0].sCPR[115].nAckNum =1;  sT[0].sCP[0].sCPR[115].nSPOffsetCS = 1796; sT[0].sCP[0].sCPR[115].nSPOffsetLek = 1797;

sT[0].sCP[0].sCPR[116].nDCStart= 214; sT[0].sCP[0].sCPR[116].nDCNum = 1;   sT[0].sCP[0].sCPR[116].nSCStart = 215;  sT[0].sCP[0].sCPR[116].nAckStart =0;   sT[0].sCP[0].sCPR[116].nAckNum =0;  sT[0].sCP[0].sCPR[116].nSPOffsetCS = 1738; sT[0].sCP[0].sCPR[116].nSPOffsetLek = 1739;
sT[0].sCP[0].sCPR[117].nDCStart= 216; sT[0].sCP[0].sCPR[117].nDCNum = 1;   sT[0].sCP[0].sCPR[117].nSCStart = 217;  sT[0].sCP[0].sCPR[117].nAckStart =511; sT[0].sCP[0].sCPR[117].nAckNum =1;  sT[0].sCP[0].sCPR[117].nSPOffsetCS = 1764; sT[0].sCP[0].sCPR[117].nSPOffsetLek = 1765;
sT[0].sCP[0].sCPR[118].nDCStart= 0  ; sT[0].sCP[0].sCPR[118].nDCNum = 0;   sT[0].sCP[0].sCPR[118].nSCStart = 497;  sT[0].sCP[0].sCPR[118].nAckStart =0;   sT[0].sCP[0].sCPR[118].nAckNum =0;  sT[0].sCP[0].sCPR[118].nSPOffsetCS = 2730; sT[0].sCP[0].sCPR[118].nSPOffsetLek = 2731;
sT[0].sCP[0].sCPR[119].nDCStart= 230; sT[0].sCP[0].sCPR[119].nDCNum = 1;   sT[0].sCP[0].sCPR[119].nSCStart = 231;  sT[0].sCP[0].sCPR[119].nAckStart =0;   sT[0].sCP[0].sCPR[119].nAckNum =0;  sT[0].sCP[0].sCPR[119].nSPOffsetCS = 1876; sT[0].sCP[0].sCPR[119].nSPOffsetLek = 1877;
sT[0].sCP[0].sCPR[120].nDCStart= 232; sT[0].sCP[0].sCPR[120].nDCNum = 1;   sT[0].sCP[0].sCPR[120].nSCStart = 233;  sT[0].sCP[0].sCPR[120].nAckStart =0;   sT[0].sCP[0].sCPR[120].nAckNum =0;  sT[0].sCP[0].sCPR[120].nSPOffsetCS = 1892; sT[0].sCP[0].sCPR[120].nSPOffsetLek = 1893;

sT[0].sCP[0].sCPR[121].nDCStart= 234; sT[0].sCP[0].sCPR[121].nDCNum = 1;   sT[0].sCP[0].sCPR[121].nSCStart = 235;  sT[0].sCP[0].sCPR[121].nAckStart =0;   sT[0].sCP[0].sCPR[121].nAckNum =0;  sT[0].sCP[0].sCPR[121].nSPOffsetCS = 1908; sT[0].sCP[0].sCPR[121].nSPOffsetLek = 1909;
sT[0].sCP[0].sCPR[122].nDCStart= 250; sT[0].sCP[0].sCPR[122].nDCNum = 1;   sT[0].sCP[0].sCPR[122].nSCStart = 251;  sT[0].sCP[0].sCPR[122].nAckStart =0;   sT[0].sCP[0].sCPR[122].nAckNum =0;  sT[0].sCP[0].sCPR[122].nSPOffsetCS = 2046; sT[0].sCP[0].sCPR[122].nSPOffsetLek = 2047;

sT[0].sCP[0].sCPR[123].nDCStart= 264; sT[0].sCP[0].sCPR[123].nDCNum = 1;   sT[0].sCP[0].sCPR[123].nSCStart = 265;  sT[0].sCP[0].sCPR[123].nAckStart =517; sT[0].sCP[0].sCPR[123].nAckNum =1;  sT[0].sCP[0].sCPR[123].nSPOffsetCS = 2158; sT[0].sCP[0].sCPR[123].nSPOffsetLek = 2159;
sT[0].sCP[0].sCPR[124].nDCStart= 266; sT[0].sCP[0].sCPR[124].nDCNum = 1;   sT[0].sCP[0].sCPR[124].nSCStart = 267;  sT[0].sCP[0].sCPR[124].nAckStart =0;   sT[0].sCP[0].sCPR[124].nAckNum =0;  sT[0].sCP[0].sCPR[124].nSPOffsetCS = 2174; sT[0].sCP[0].sCPR[124].nSPOffsetLek = 2175;
sT[0].sCP[0].sCPR[125].nDCStart= 268; sT[0].sCP[0].sCPR[125].nDCNum = 1;   sT[0].sCP[0].sCPR[125].nSCStart = 269;  sT[0].sCP[0].sCPR[125].nAckStart =0;   sT[0].sCP[0].sCPR[125].nAckNum =0;  sT[0].sCP[0].sCPR[125].nSPOffsetCS = 2190; sT[0].sCP[0].sCPR[125].nSPOffsetLek = 2191;
sT[0].sCP[0].sCPR[126].nDCStart= 270; sT[0].sCP[0].sCPR[126].nDCNum = 1;   sT[0].sCP[0].sCPR[126].nSCStart = 271;  sT[0].sCP[0].sCPR[126].nAckStart =425; sT[0].sCP[0].sCPR[126].nAckNum =1;  sT[0].sCP[0].sCPR[126].nSPOffsetCS = 2206; sT[0].sCP[0].sCPR[126].nSPOffsetLek = 2207;
sT[0].sCP[0].sCPR[127].nDCStart= 272; sT[0].sCP[0].sCPR[127].nDCNum = 1;   sT[0].sCP[0].sCPR[127].nSCStart = 273;  sT[0].sCP[0].sCPR[127].nAckStart =0;   sT[0].sCP[0].sCPR[127].nAckNum =0;  sT[0].sCP[0].sCPR[127].nSPOffsetCS = 2222; sT[0].sCP[0].sCPR[127].nSPOffsetLek = 2223;
sT[0].sCP[0].sCPR[128].nDCStart= 274; sT[0].sCP[0].sCPR[128].nDCNum = 4;   sT[0].sCP[0].sCPR[128].nSCStart = 278;  sT[0].sCP[0].sCPR[128].nAckStart =0;   sT[0].sCP[0].sCPR[128].nAckNum =0;  sT[0].sCP[0].sCPR[128].nSPOffsetCS = 2248; sT[0].sCP[0].sCPR[128].nSPOffsetLek = 2249;
sT[0].sCP[0].sCPR[129].nDCStart= 563; sT[0].sCP[0].sCPR[129].nDCNum = 4;   sT[0].sCP[0].sCPR[129].nSCStart = 567;  sT[0].sCP[0].sCPR[129].nAckStart =0;   sT[0].sCP[0].sCPR[129].nAckNum =0;  sT[0].sCP[0].sCPR[129].nSPOffsetCS = 3693; sT[0].sCP[0].sCPR[129].nSPOffsetLek = 3694;

sT[0].sCP[0].sCPR[130].nDCStart= 252; sT[0].sCP[0].sCPR[130].nDCNum = 1;   sT[0].sCP[0].sCPR[130].nSCStart = 253;  sT[0].sCP[0].sCPR[130].nAckStart =0;   sT[0].sCP[0].sCPR[130].nAckNum =0;  sT[0].sCP[0].sCPR[130].nSPOffsetCS = 2062; sT[0].sCP[0].sCPR[130].nSPOffsetLek = 2063;
sT[0].sCP[0].sCPR[131].nDCStart= 254; sT[0].sCP[0].sCPR[131].nDCNum = 1;   sT[0].sCP[0].sCPR[131].nSCStart = 255;  sT[0].sCP[0].sCPR[131].nAckStart =512; sT[0].sCP[0].sCPR[131].nAckNum =1;  sT[0].sCP[0].sCPR[131].nSPOffsetCS = 2078; sT[0].sCP[0].sCPR[131].nSPOffsetLek = 2079;
sT[0].sCP[0].sCPR[132].nDCStart= 222; sT[0].sCP[0].sCPR[132].nDCNum = 1;   sT[0].sCP[0].sCPR[132].nSCStart = 223;  sT[0].sCP[0].sCPR[132].nAckStart =0;   sT[0].sCP[0].sCPR[132].nAckNum =0;  sT[0].sCP[0].sCPR[132].nSPOffsetCS = 1812; sT[0].sCP[0].sCPR[132].nSPOffsetLek = 1813;
sT[0].sCP[0].sCPR[133].nDCStart= 224; sT[0].sCP[0].sCPR[133].nDCNum = 1;   sT[0].sCP[0].sCPR[133].nSCStart = 225;  sT[0].sCP[0].sCPR[133].nAckStart =0;   sT[0].sCP[0].sCPR[133].nAckNum =0;  sT[0].sCP[0].sCPR[133].nSPOffsetCS = 1828; sT[0].sCP[0].sCPR[133].nSPOffsetLek = 1829;
sT[0].sCP[0].sCPR[134].nDCStart= 226; sT[0].sCP[0].sCPR[134].nDCNum = 1;   sT[0].sCP[0].sCPR[134].nSCStart = 227;  sT[0].sCP[0].sCPR[134].nAckStart =0;   sT[0].sCP[0].sCPR[134].nAckNum =0;  sT[0].sCP[0].sCPR[134].nSPOffsetCS = 1844; sT[0].sCP[0].sCPR[134].nSPOffsetLek = 1845;
sT[0].sCP[0].sCPR[135].nDCStart= 228; sT[0].sCP[0].sCPR[135].nDCNum = 1;   sT[0].sCP[0].sCPR[135].nSCStart = 229;  sT[0].sCP[0].sCPR[135].nAckStart =0;   sT[0].sCP[0].sCPR[135].nAckNum =0;  sT[0].sCP[0].sCPR[135].nSPOffsetCS = 1860; sT[0].sCP[0].sCPR[135].nSPOffsetLek = 1861;

sT[0].sCP[0].sCPR[136].nDCStart= 256; sT[0].sCP[0].sCPR[136].nDCNum = 1;   sT[0].sCP[0].sCPR[136].nSCStart = 257;  sT[0].sCP[0].sCPR[136].nAckStart =0;   sT[0].sCP[0].sCPR[136].nAckNum =0;  sT[0].sCP[0].sCPR[136].nSPOffsetCS = 2094; sT[0].sCP[0].sCPR[136].nSPOffsetLek = 2095;
sT[0].sCP[0].sCPR[137].nDCStart= 258; sT[0].sCP[0].sCPR[137].nDCNum = 1;   sT[0].sCP[0].sCPR[137].nSCStart = 259;  sT[0].sCP[0].sCPR[137].nAckStart =0;   sT[0].sCP[0].sCPR[137].nAckNum =0;  sT[0].sCP[0].sCPR[137].nSPOffsetCS = 2110; sT[0].sCP[0].sCPR[137].nSPOffsetLek = 2111;
sT[0].sCP[0].sCPR[138].nDCStart= 260; sT[0].sCP[0].sCPR[138].nDCNum = 1;   sT[0].sCP[0].sCPR[138].nSCStart = 261;  sT[0].sCP[0].sCPR[138].nAckStart =0;   sT[0].sCP[0].sCPR[138].nAckNum =0;  sT[0].sCP[0].sCPR[138].nSPOffsetCS = 2126; sT[0].sCP[0].sCPR[138].nSPOffsetLek = 2127;
sT[0].sCP[0].sCPR[139].nDCStart= 262; sT[0].sCP[0].sCPR[139].nDCNum = 1;   sT[0].sCP[0].sCPR[139].nSCStart = 263;  sT[0].sCP[0].sCPR[139].nAckStart =759; sT[0].sCP[0].sCPR[139].nAckNum =1;  sT[0].sCP[0].sCPR[139].nSPOffsetCS = 2142; sT[0].sCP[0].sCPR[139].nSPOffsetLek = 2143;

sT[0].sCP[0].sCPR[140].nDCStart= 280; sT[0].sCP[0].sCPR[140].nDCNum = 4;   sT[0].sCP[0].sCPR[140].nSCStart = 285;  sT[0].sCP[0].sCPR[140].nAckStart =284; sT[0].sCP[0].sCPR[140].nAckNum =1;  sT[0].sCP[0].sCPR[140].nSPOffsetCS = 2287; sT[0].sCP[0].sCPR[140].nSPOffsetLek = 2288;
sT[0].sCP[0].sCPR[141].nDCStart= 286; sT[0].sCP[0].sCPR[141].nDCNum = 4;   sT[0].sCP[0].sCPR[141].nSCStart = 291;  sT[0].sCP[0].sCPR[141].nAckStart =290; sT[0].sCP[0].sCPR[141].nAckNum =1;  sT[0].sCP[0].sCPR[141].nSPOffsetCS = 2326; sT[0].sCP[0].sCPR[141].nSPOffsetLek = 2327;
sT[0].sCP[0].sCPR[142].nDCStart= 292; sT[0].sCP[0].sCPR[142].nDCNum = 4;   sT[0].sCP[0].sCPR[142].nSCStart = 297;  sT[0].sCP[0].sCPR[142].nAckStart =296; sT[0].sCP[0].sCPR[142].nAckNum =1;  sT[0].sCP[0].sCPR[142].nSPOffsetCS = 2365; sT[0].sCP[0].sCPR[142].nSPOffsetLek = 2366;
sT[0].sCP[0].sCPR[143].nDCStart= 298; sT[0].sCP[0].sCPR[143].nDCNum = 4;   sT[0].sCP[0].sCPR[143].nSCStart = 303;  sT[0].sCP[0].sCPR[143].nAckStart =302; sT[0].sCP[0].sCPR[143].nAckNum =1;  sT[0].sCP[0].sCPR[143].nSPOffsetCS = 2404; sT[0].sCP[0].sCPR[143].nSPOffsetLek = 2405;
sT[0].sCP[0].sCPR[144].nDCStart= 304; sT[0].sCP[0].sCPR[144].nDCNum = 4;   sT[0].sCP[0].sCPR[144].nSCStart = 309;  sT[0].sCP[0].sCPR[144].nAckStart =308; sT[0].sCP[0].sCPR[144].nAckNum =1;  sT[0].sCP[0].sCPR[144].nSPOffsetCS = 2443; sT[0].sCP[0].sCPR[144].nSPOffsetLek = 2444;
sT[0].sCP[0].sCPR[145].nDCStart= 310; sT[0].sCP[0].sCPR[145].nDCNum = 4;   sT[0].sCP[0].sCPR[145].nSCStart = 315;  sT[0].sCP[0].sCPR[145].nAckStart =314; sT[0].sCP[0].sCPR[145].nAckNum =1;  sT[0].sCP[0].sCPR[145].nSPOffsetCS = 2482; sT[0].sCP[0].sCPR[145].nSPOffsetLek = 2483;
sT[0].sCP[0].sCPR[146].nDCStart= 316; sT[0].sCP[0].sCPR[146].nDCNum = 4;   sT[0].sCP[0].sCPR[146].nSCStart = 321;  sT[0].sCP[0].sCPR[146].nAckStart =320; sT[0].sCP[0].sCPR[146].nAckNum =1;  sT[0].sCP[0].sCPR[146].nSPOffsetCS = 2537; sT[0].sCP[0].sCPR[146].nSPOffsetLek = 2538;
sT[0].sCP[0].sCPR[147].nDCStart= 322; sT[0].sCP[0].sCPR[147].nDCNum = 4;   sT[0].sCP[0].sCPR[147].nSCStart = 326;  sT[0].sCP[0].sCPR[147].nAckStart =0;   sT[0].sCP[0].sCPR[147].nAckNum =0;  sT[0].sCP[0].sCPR[147].nSPOffsetCS = 2553; sT[0].sCP[0].sCPR[147].nSPOffsetLek = 2554;
sT[0].sCP[0].sCPR[148].nDCStart= 327; sT[0].sCP[0].sCPR[148].nDCNum = 4;   sT[0].sCP[0].sCPR[148].nSCStart = 331;  sT[0].sCP[0].sCPR[148].nAckStart =0;   sT[0].sCP[0].sCPR[148].nAckNum =0;  sT[0].sCP[0].sCPR[148].nSPOffsetCS = 2569; sT[0].sCP[0].sCPR[148].nSPOffsetLek = 2570;
sT[0].sCP[0].sCPR[149].nDCStart= 332; sT[0].sCP[0].sCPR[149].nDCNum = 1;   sT[0].sCP[0].sCPR[149].nSCStart = 333;  sT[0].sCP[0].sCPR[149].nAckStart =0;   sT[0].sCP[0].sCPR[149].nAckNum =0;  sT[0].sCP[0].sCPR[149].nSPOffsetCS = 2585; sT[0].sCP[0].sCPR[149].nSPOffsetLek = 2586;

sT[0].sCP[0].sCPR[150].nDCStart= 334; sT[0].sCP[0].sCPR[150].nDCNum = 1;   sT[0].sCP[0].sCPR[150].nSCStart = 335;  sT[0].sCP[0].sCPR[150].nAckStart =0;   sT[0].sCP[0].sCPR[150].nAckNum =0;  sT[0].sCP[0].sCPR[150].nSPOffsetCS = 2601; sT[0].sCP[0].sCPR[150].nSPOffsetLek = 2602;
sT[0].sCP[0].sCPR[151].nDCStart= 336; sT[0].sCP[0].sCPR[151].nDCNum = 1;   sT[0].sCP[0].sCPR[151].nSCStart = 337;  sT[0].sCP[0].sCPR[151].nAckStart =747; sT[0].sCP[0].sCPR[151].nAckNum =1;  sT[0].sCP[0].sCPR[151].nSPOffsetCS = 2617; sT[0].sCP[0].sCPR[151].nSPOffsetLek = 2618;
sT[0].sCP[0].sCPR[152].nDCStart= 338; sT[0].sCP[0].sCPR[152].nDCNum = 1;   sT[0].sCP[0].sCPR[152].nSCStart = 339;  sT[0].sCP[0].sCPR[152].nAckStart =0;   sT[0].sCP[0].sCPR[152].nAckNum =0;  sT[0].sCP[0].sCPR[152].nSPOffsetCS = 2633; sT[0].sCP[0].sCPR[152].nSPOffsetLek = 2634;

sT[0].sCP[0].sCPR[153].nDCStart= 340; sT[0].sCP[0].sCPR[153].nDCNum = 1;   sT[0].sCP[0].sCPR[153].nSCStart = 341;  sT[0].sCP[0].sCPR[153].nAckStart =0;   sT[0].sCP[0].sCPR[153].nAckNum =0;  sT[0].sCP[0].sCPR[153].nSPOffsetCS = 2640; sT[0].sCP[0].sCPR[153].nSPOffsetLek = 2641;
sT[0].sCP[0].sCPR[154].nDCStart= 342; sT[0].sCP[0].sCPR[154].nDCNum = 4;   sT[0].sCP[0].sCPR[154].nSCStart = 347;  sT[0].sCP[0].sCPR[154].nAckStart =346; sT[0].sCP[0].sCPR[154].nAckNum =1;  sT[0].sCP[0].sCPR[154].nSPOffsetCS = 2677; sT[0].sCP[0].sCPR[154].nSPOffsetLek = 2678;
sT[0].sCP[0].sCPR[155].nDCStart= 150; sT[0].sCP[0].sCPR[155].nDCNum = 1;   sT[0].sCP[0].sCPR[155].nSCStart = 151;  sT[0].sCP[0].sCPR[155].nAckStart =0;   sT[0].sCP[0].sCPR[155].nAckNum =0;  sT[0].sCP[0].sCPR[155].nSPOffsetCS = 2693; sT[0].sCP[0].sCPR[155].nSPOffsetLek = 2694;
sT[0].sCP[0].sCPR[156].nDCStart= 348; sT[0].sCP[0].sCPR[156].nDCNum = 1;   sT[0].sCP[0].sCPR[156].nSCStart = 349;  sT[0].sCP[0].sCPR[156].nAckStart =0;   sT[0].sCP[0].sCPR[156].nAckNum =0;  sT[0].sCP[0].sCPR[156].nSPOffsetCS = 2707; sT[0].sCP[0].sCPR[156].nSPOffsetLek = 2708;
sT[0].sCP[0].sCPR[157].nDCStart= 350; sT[0].sCP[0].sCPR[157].nDCNum = 1;   sT[0].sCP[0].sCPR[157].nSCStart = 351;  sT[0].sCP[0].sCPR[157].nAckStart =0;    sT[0].sCP[0].sCPR[157].nAckNum=0;  sT[0].sCP[0].sCPR[157].nSPOffsetCS = 2498; sT[0].sCP[0].sCPR[157].nSPOffsetLek = 2499;

sT[0].sCP[0].sCPR[158].nDCStart= 352; sT[0].sCP[0].sCPR[158].nDCNum = 1;   sT[0].sCP[0].sCPR[158].nSCStart = 353;  sT[0].sCP[0].sCPR[158].nAckStart =384;  sT[0].sCP[0].sCPR[158].nAckNum=1;  sT[0].sCP[0].sCPR[158].nSPOffsetCS = 2723; sT[0].sCP[0].sCPR[158].nSPOffsetLek = 2724;
sT[0].sCP[0].sCPR[159].nDCStart= 568; sT[0].sCP[0].sCPR[159].nDCNum = 4;   sT[0].sCP[0].sCPR[159].nSCStart = 572;  sT[0].sCP[0].sCPR[159].nAckStart =0;    sT[0].sCP[0].sCPR[159].nAckNum=0;  sT[0].sCP[0].sCPR[159].nSPOffsetCS = 3707; sT[0].sCP[0].sCPR[159].nSPOffsetLek = 3708;
sT[0].sCP[0].sCPR[160].nDCStart= 356; sT[0].sCP[0].sCPR[160].nDCNum = 1;   sT[0].sCP[0].sCPR[160].nSCStart = 357;  sT[0].sCP[0].sCPR[160].nAckStart =0;    sT[0].sCP[0].sCPR[160].nAckNum=0;  sT[0].sCP[0].sCPR[160].nSPOffsetCS = 2764; sT[0].sCP[0].sCPR[160].nSPOffsetLek = 2765;
sT[0].sCP[0].sCPR[161].nDCStart= 358; sT[0].sCP[0].sCPR[161].nDCNum = 1;   sT[0].sCP[0].sCPR[161].nSCStart = 359;  sT[0].sCP[0].sCPR[161].nAckStart =380;  sT[0].sCP[0].sCPR[161].nAckNum=1;  sT[0].sCP[0].sCPR[161].nSPOffsetCS = 2780; sT[0].sCP[0].sCPR[161].nSPOffsetLek = 2781;
sT[0].sCP[0].sCPR[162].nDCStart= 360; sT[0].sCP[0].sCPR[162].nDCNum = 1;   sT[0].sCP[0].sCPR[162].nSCStart = 361;  sT[0].sCP[0].sCPR[162].nAckStart =381;  sT[0].sCP[0].sCPR[162].nAckNum=1;  sT[0].sCP[0].sCPR[162].nSPOffsetCS = 2796; sT[0].sCP[0].sCPR[162].nSPOffsetLek = 2797;	

sT[0].sCP[0].sCPR[163].nDCStart= 0  ; sT[0].sCP[0].sCPR[163].nDCNum = 0;   sT[0].sCP[0].sCPR[163].nSCStart = 385;  sT[0].sCP[0].sCPR[163].nAckStart =0;    sT[0].sCP[0].sCPR[163].nAckNum=0;  sT[0].sCP[0].sCPR[163].nSPOffsetCS = 2746; sT[0].sCP[0].sCPR[163].nSPOffsetLek = 2747;	
sT[0].sCP[0].sCPR[164].nDCStart= 0  ; sT[0].sCP[0].sCPR[164].nDCNum = 0;   sT[0].sCP[0].sCPR[164].nSCStart = 386;  sT[0].sCP[0].sCPR[164].nAckStart =0;    sT[0].sCP[0].sCPR[164].nAckNum=0;  sT[0].sCP[0].sCPR[164].nSPOffsetCS = 1995; sT[0].sCP[0].sCPR[164].nSPOffsetLek = 1996;	

sT[0].sCP[0].sCPR[165].nDCStart= 398; sT[0].sCP[0].sCPR[165].nDCNum = 1;   sT[0].sCP[0].sCPR[165].nSCStart = 399;  sT[0].sCP[0].sCPR[165].nAckStart =0;    sT[0].sCP[0].sCPR[165].nAckNum=0;  sT[0].sCP[0].sCPR[165].nSPOffsetCS = 2812; sT[0].sCP[0].sCPR[165].nSPOffsetLek = 2813;	
sT[0].sCP[0].sCPR[166].nDCStart= 400; sT[0].sCP[0].sCPR[166].nDCNum = 1;   sT[0].sCP[0].sCPR[166].nSCStart = 401;  sT[0].sCP[0].sCPR[166].nAckStart =0;    sT[0].sCP[0].sCPR[166].nAckNum=0;  sT[0].sCP[0].sCPR[166].nSPOffsetCS = 2828; sT[0].sCP[0].sCPR[166].nSPOffsetLek = 2829;	

sT[0].sCP[0].sCPR[167].nDCStart= 402; sT[0].sCP[0].sCPR[167].nDCNum = 1;   sT[0].sCP[0].sCPR[167].nSCStart = 403;  sT[0].sCP[0].sCPR[167].nAckStart =0;    sT[0].sCP[0].sCPR[167].nAckNum=0;  sT[0].sCP[0].sCPR[167].nSPOffsetCS = 2844; sT[0].sCP[0].sCPR[167].nSPOffsetLek = 2845;	
sT[0].sCP[0].sCPR[168].nDCStart= 404; sT[0].sCP[0].sCPR[168].nDCNum = 1;   sT[0].sCP[0].sCPR[168].nSCStart = 405;  sT[0].sCP[0].sCPR[168].nAckStart =406;  sT[0].sCP[0].sCPR[168].nAckNum=1;  sT[0].sCP[0].sCPR[168].nSPOffsetCS = 2860; sT[0].sCP[0].sCPR[168].nSPOffsetLek = 2861;	
sT[0].sCP[0].sCPR[169].nDCStart= 407; sT[0].sCP[0].sCPR[169].nDCNum = 1;   sT[0].sCP[0].sCPR[169].nSCStart = 408;  sT[0].sCP[0].sCPR[169].nAckStart =0;    sT[0].sCP[0].sCPR[169].nAckNum=0;  sT[0].sCP[0].sCPR[169].nSPOffsetCS = 2876; sT[0].sCP[0].sCPR[169].nSPOffsetLek = 2877;	
sT[0].sCP[0].sCPR[170].nDCStart= 409; sT[0].sCP[0].sCPR[170].nDCNum = 1;   sT[0].sCP[0].sCPR[170].nSCStart = 410;  sT[0].sCP[0].sCPR[170].nAckStart =411;  sT[0].sCP[0].sCPR[170].nAckNum=1;  sT[0].sCP[0].sCPR[170].nSPOffsetCS = 2892; sT[0].sCP[0].sCPR[170].nSPOffsetLek = 2893;	
sT[0].sCP[0].sCPR[171].nDCStart= 412; sT[0].sCP[0].sCPR[171].nDCNum = 1;   sT[0].sCP[0].sCPR[171].nSCStart = 413;  sT[0].sCP[0].sCPR[171].nAckStart =414;  sT[0].sCP[0].sCPR[171].nAckNum=1;  sT[0].sCP[0].sCPR[171].nSPOffsetCS = 2908; sT[0].sCP[0].sCPR[171].nSPOffsetLek = 2909;	
sT[0].sCP[0].sCPR[172].nDCStart= 415; sT[0].sCP[0].sCPR[172].nDCNum = 1;   sT[0].sCP[0].sCPR[172].nSCStart = 416;  sT[0].sCP[0].sCPR[172].nAckStart =0;    sT[0].sCP[0].sCPR[172].nAckNum=0;  sT[0].sCP[0].sCPR[172].nSPOffsetCS = 2924; sT[0].sCP[0].sCPR[172].nSPOffsetLek = 2925;	
sT[0].sCP[0].sCPR[173].nDCStart= 417; sT[0].sCP[0].sCPR[173].nDCNum = 1;   sT[0].sCP[0].sCPR[173].nSCStart = 418;  sT[0].sCP[0].sCPR[173].nAckStart =0;    sT[0].sCP[0].sCPR[173].nAckNum=0;  sT[0].sCP[0].sCPR[173].nSPOffsetCS = 2940; sT[0].sCP[0].sCPR[173].nSPOffsetLek = 2941;	
sT[0].sCP[0].sCPR[174].nDCStart= 419; sT[0].sCP[0].sCPR[174].nDCNum = 1;   sT[0].sCP[0].sCPR[174].nSCStart = 420;  sT[0].sCP[0].sCPR[174].nAckStart =0;    sT[0].sCP[0].sCPR[174].nAckNum=0;  sT[0].sCP[0].sCPR[174].nSPOffsetCS = 2956; sT[0].sCP[0].sCPR[174].nSPOffsetLek = 2957;	
sT[0].sCP[0].sCPR[175].nDCStart= 430; sT[0].sCP[0].sCPR[175].nDCNum = 1;   sT[0].sCP[0].sCPR[175].nSCStart = 431;  sT[0].sCP[0].sCPR[175].nAckStart =0;    sT[0].sCP[0].sCPR[175].nAckNum=0;  sT[0].sCP[0].sCPR[175].nSPOffsetCS = 2972; sT[0].sCP[0].sCPR[175].nSPOffsetLek = 2973;	

sT[0].sCP[0].sCPR[176].nDCStart= 432; sT[0].sCP[0].sCPR[176].nDCNum = 1;   sT[0].sCP[0].sCPR[176].nSCStart = 433;  sT[0].sCP[0].sCPR[176].nAckStart =452;  sT[0].sCP[0].sCPR[176].nAckNum=1;  sT[0].sCP[0].sCPR[176].nSPOffsetCS = 2988; sT[0].sCP[0].sCPR[176].nSPOffsetLek = 2989;	
sT[0].sCP[0].sCPR[177].nDCStart= 434; sT[0].sCP[0].sCPR[177].nDCNum = 1;   sT[0].sCP[0].sCPR[177].nSCStart = 435;  sT[0].sCP[0].sCPR[177].nAckStart =453;  sT[0].sCP[0].sCPR[177].nAckNum=1;  sT[0].sCP[0].sCPR[177].nSPOffsetCS = 3004; sT[0].sCP[0].sCPR[177].nSPOffsetLek = 3005;	
sT[0].sCP[0].sCPR[178].nDCStart= 436; sT[0].sCP[0].sCPR[178].nDCNum = 1;   sT[0].sCP[0].sCPR[178].nSCStart = 437;  sT[0].sCP[0].sCPR[178].nAckStart =454;  sT[0].sCP[0].sCPR[178].nAckNum=1;  sT[0].sCP[0].sCPR[178].nSPOffsetCS = 3020; sT[0].sCP[0].sCPR[178].nSPOffsetLek = 3021;	
sT[0].sCP[0].sCPR[179].nDCStart= 438; sT[0].sCP[0].sCPR[179].nDCNum = 1;   sT[0].sCP[0].sCPR[179].nSCStart = 439;  sT[0].sCP[0].sCPR[179].nAckStart =0;    sT[0].sCP[0].sCPR[179].nAckNum=0;  sT[0].sCP[0].sCPR[179].nSPOffsetCS = 3036; sT[0].sCP[0].sCPR[179].nSPOffsetLek = 3037;	
sT[0].sCP[0].sCPR[180].nDCStart= 440; sT[0].sCP[0].sCPR[180].nDCNum = 1;   sT[0].sCP[0].sCPR[180].nSCStart = 441;  sT[0].sCP[0].sCPR[180].nAckStart =0;    sT[0].sCP[0].sCPR[180].nAckNum=0;  sT[0].sCP[0].sCPR[180].nSPOffsetCS = 3052; sT[0].sCP[0].sCPR[180].nSPOffsetLek = 3053;	
sT[0].sCP[0].sCPR[181].nDCStart= 442; sT[0].sCP[0].sCPR[181].nDCNum = 1;   sT[0].sCP[0].sCPR[181].nSCStart = 443;  sT[0].sCP[0].sCPR[181].nAckStart =455;  sT[0].sCP[0].sCPR[181].nAckNum=1;  sT[0].sCP[0].sCPR[181].nSPOffsetCS = 3068; sT[0].sCP[0].sCPR[181].nSPOffsetLek = 3069;	
sT[0].sCP[0].sCPR[182].nDCStart= 444; sT[0].sCP[0].sCPR[182].nDCNum = 1;   sT[0].sCP[0].sCPR[182].nSCStart = 445;  sT[0].sCP[0].sCPR[182].nAckStart =456;  sT[0].sCP[0].sCPR[182].nAckNum=1;  sT[0].sCP[0].sCPR[182].nSPOffsetCS = 3084; sT[0].sCP[0].sCPR[182].nSPOffsetLek = 3085;	
sT[0].sCP[0].sCPR[183].nDCStart= 446; sT[0].sCP[0].sCPR[183].nDCNum = 1;   sT[0].sCP[0].sCPR[183].nSCStart = 447;  sT[0].sCP[0].sCPR[183].nAckStart =457;  sT[0].sCP[0].sCPR[183].nAckNum=1;  sT[0].sCP[0].sCPR[183].nSPOffsetCS = 3100; sT[0].sCP[0].sCPR[183].nSPOffsetLek = 3101;	
sT[0].sCP[0].sCPR[184].nDCStart= 448; sT[0].sCP[0].sCPR[184].nDCNum = 1;   sT[0].sCP[0].sCPR[184].nSCStart = 449;  sT[0].sCP[0].sCPR[184].nAckStart =0;    sT[0].sCP[0].sCPR[184].nAckNum=0;  sT[0].sCP[0].sCPR[184].nSPOffsetCS = 3116; sT[0].sCP[0].sCPR[184].nSPOffsetLek = 3117;	
sT[0].sCP[0].sCPR[185].nDCStart= 450; sT[0].sCP[0].sCPR[185].nDCNum = 1;   sT[0].sCP[0].sCPR[185].nSCStart = 451;  sT[0].sCP[0].sCPR[185].nAckStart =458;  sT[0].sCP[0].sCPR[185].nAckNum=1;  sT[0].sCP[0].sCPR[185].nSPOffsetCS = 3132; sT[0].sCP[0].sCPR[185].nSPOffsetLek = 3133;	

sT[0].sCP[0].sCPR[186].nDCStart= 459; sT[0].sCP[0].sCPR[186].nDCNum = 1;   sT[0].sCP[0].sCPR[186].nSCStart = 460;  sT[0].sCP[0].sCPR[186].nAckStart =463;  sT[0].sCP[0].sCPR[186].nAckNum=1;  sT[0].sCP[0].sCPR[186].nSPOffsetCS = 3148; sT[0].sCP[0].sCPR[186].nSPOffsetLek = 3149;	
sT[0].sCP[0].sCPR[187].nDCStart= 461; sT[0].sCP[0].sCPR[187].nDCNum = 1;   sT[0].sCP[0].sCPR[187].nSCStart = 462;  sT[0].sCP[0].sCPR[187].nAckStart =0;    sT[0].sCP[0].sCPR[187].nAckNum=0;  sT[0].sCP[0].sCPR[187].nSPOffsetCS = 3164; sT[0].sCP[0].sCPR[187].nSPOffsetLek = 3165;	

sT[0].sCP[0].sCPR[188].nDCStart= 464; sT[0].sCP[0].sCPR[188].nDCNum = 1;   sT[0].sCP[0].sCPR[188].nSCStart = 465;  sT[0].sCP[0].sCPR[188].nAckStart =480;  sT[0].sCP[0].sCPR[188].nAckNum=1;  sT[0].sCP[0].sCPR[188].nSPOffsetCS = 3180; sT[0].sCP[0].sCPR[188].nSPOffsetLek = 3181;	
sT[0].sCP[0].sCPR[189].nDCStart= 573; sT[0].sCP[0].sCPR[189].nDCNum = 4;   sT[0].sCP[0].sCPR[189].nSCStart = 577;  sT[0].sCP[0].sCPR[189].nAckStart =0;    sT[0].sCP[0].sCPR[189].nAckNum=0;  sT[0].sCP[0].sCPR[189].nSPOffsetCS = 4796; sT[0].sCP[0].sCPR[189].nSPOffsetLek = 4797;
sT[0].sCP[0].sCPR[190].nDCStart= 735; sT[0].sCP[0].sCPR[190].nDCNum = 4;   sT[0].sCP[0].sCPR[190].nSCStart = 740;  sT[0].sCP[0].sCPR[190].nAckStart =739;  sT[0].sCP[0].sCPR[190].nAckNum=1;  sT[0].sCP[0].sCPR[190].nSPOffsetCS = 4756; sT[0].sCP[0].sCPR[190].nSPOffsetLek = 4757;	
sT[0].sCP[0].sCPR[191].nDCStart= 466; sT[0].sCP[0].sCPR[191].nDCNum = 1;   sT[0].sCP[0].sCPR[191].nSCStart = 467;  sT[0].sCP[0].sCPR[191].nAckStart =741;  sT[0].sCP[0].sCPR[191].nAckNum=1;  sT[0].sCP[0].sCPR[191].nSPOffsetCS = 3196; sT[0].sCP[0].sCPR[191].nSPOffsetLek = 3197;	
sT[0].sCP[0].sCPR[192].nDCStart= 472; sT[0].sCP[0].sCPR[192].nDCNum = 1;   sT[0].sCP[0].sCPR[192].nSCStart = 473;  sT[0].sCP[0].sCPR[192].nAckStart =481;  sT[0].sCP[0].sCPR[192].nAckNum=1;  sT[0].sCP[0].sCPR[192].nSPOffsetCS = 3244; sT[0].sCP[0].sCPR[192].nSPOffsetLek = 3245;	
sT[0].sCP[0].sCPR[193].nDCStart= 474; sT[0].sCP[0].sCPR[193].nDCNum = 1;   sT[0].sCP[0].sCPR[193].nSCStart = 475;  sT[0].sCP[0].sCPR[193].nAckStart =0;    sT[0].sCP[0].sCPR[193].nAckNum=0;  sT[0].sCP[0].sCPR[193].nSPOffsetCS = 3260; sT[0].sCP[0].sCPR[193].nSPOffsetLek = 3261;	
sT[0].sCP[0].sCPR[194].nDCStart= 476; sT[0].sCP[0].sCPR[194].nDCNum = 1;   sT[0].sCP[0].sCPR[194].nSCStart = 477;  sT[0].sCP[0].sCPR[194].nAckStart =482;  sT[0].sCP[0].sCPR[194].nAckNum=1;  sT[0].sCP[0].sCPR[194].nSPOffsetCS = 3276; sT[0].sCP[0].sCPR[194].nSPOffsetLek = 3277;	
sT[0].sCP[0].sCPR[195].nDCStart= 468; sT[0].sCP[0].sCPR[195].nDCNum = 1;   sT[0].sCP[0].sCPR[195].nSCStart = 469;  sT[0].sCP[0].sCPR[195].nAckStart =0;    sT[0].sCP[0].sCPR[195].nAckNum=0;  sT[0].sCP[0].sCPR[195].nSPOffsetCS = 3212; sT[0].sCP[0].sCPR[195].nSPOffsetLek = 3213;	

sT[0].sCP[0].sCPR[196].nDCStart= 484; sT[0].sCP[0].sCPR[196].nDCNum = 1;   sT[0].sCP[0].sCPR[196].nSCStart = 485;  sT[0].sCP[0].sCPR[196].nAckStart =0;    sT[0].sCP[0].sCPR[196].nAckNum=0;  sT[0].sCP[0].sCPR[196].nSPOffsetCS = 3308; sT[0].sCP[0].sCPR[196].nSPOffsetLek = 3309;	

sT[0].sCP[0].sCPR[197].nDCStart= 486; sT[0].sCP[0].sCPR[197].nDCNum = 2;   sT[0].sCP[0].sCPR[197].nSCStart = 488;  sT[0].sCP[0].sCPR[197].nAckStart =0;    sT[0].sCP[0].sCPR[197].nAckNum=0;  sT[0].sCP[0].sCPR[197].nSPOffsetCS = 3340; sT[0].sCP[0].sCPR[197].nSPOffsetLek = 3341; sT[0].sCP[0].sCPR[197].nSPOffsetCS2 = 3342;   sT[0].sCP[0].sCPR[197].nSPOffsetLek2 = 3343; sT[0].sCP[0].sCPR[197].nSCNum  = 2;

sT[0].sCP[0].sCPR[198].nDCStart= 490; sT[0].sCP[0].sCPR[198].nDCNum = 1;   sT[0].sCP[0].sCPR[198].nSCStart = 491;  sT[0].sCP[0].sCPR[198].nAckStart =0;    sT[0].sCP[0].sCPR[198].nAckNum=0;  sT[0].sCP[0].sCPR[198].nSPOffsetCS = 3358; sT[0].sCP[0].sCPR[198].nSPOffsetLek = 3359;	
sT[0].sCP[0].sCPR[199].nDCStart= 492; sT[0].sCP[0].sCPR[199].nDCNum = 4;   sT[0].sCP[0].sCPR[199].nSCStart = 496;  sT[0].sCP[0].sCPR[199].nAckStart =0;    sT[0].sCP[0].sCPR[199].nAckNum=0;  sT[0].sCP[0].sCPR[199].nSPOffsetCS = 3374; sT[0].sCP[0].sCPR[199].nSPOffsetLek = 3375;	

sT[0].sCP[0].sCPR[200].nDCStart= 500; sT[0].sCP[0].sCPR[200].nDCNum = 1;   sT[0].sCP[0].sCPR[200].nSCStart = 501;  sT[0].sCP[0].sCPR[200].nAckStart=0;     sT[0].sCP[0].sCPR[200].nAckNum=0;  sT[0].sCP[0].sCPR[200].nSPOffsetCS = 3390; sT[0].sCP[0].sCPR[200].nSPOffsetLek = 3391;

sT[0].sCP[0].sCPR[201].nDCStart= 518; sT[0].sCP[0].sCPR[201].nDCNum = 1;   sT[0].sCP[0].sCPR[201].nSCStart = 519;  sT[0].sCP[0].sCPR[201].nAckStart =0;    sT[0].sCP[0].sCPR[201].nAckNum=0;  sT[0].sCP[0].sCPR[201].nSPOffsetCS = 3424; sT[0].sCP[0].sCPR[201].nSPOffsetLek = 3425;	
	
sT[0].sCP[0].sCPR[202].nDCStart= 520; sT[0].sCP[0].sCPR[202].nDCNum = 2;   sT[0].sCP[0].sCPR[202].nSCStart = 524;  sT[0].sCP[0].sCPR[202].nAckStart=0;     sT[0].sCP[0].sCPR[202].nAckNum=0;  sT[0].sCP[0].sCPR[202].nSPOffsetCS = 3456; sT[0].sCP[0].sCPR[202].nSPOffsetLek = 3457; sT[0].sCP[0].sCPR[202].nSPOffsetCS2 = 3458;   sT[0].sCP[0].sCPR[202].nSPOffsetLek2 = 3459; sT[0].sCP[0].sCPR[202].nSCNum  = 2;
sT[0].sCP[0].sCPR[203].nDCStart= 526; sT[0].sCP[0].sCPR[203].nDCNum = 4;   sT[0].sCP[0].sCPR[203].nSCStart = 531;  sT[0].sCP[0].sCPR[203].nAckStart =530;  sT[0].sCP[0].sCPR[203].nAckNum =1; sT[0].sCP[0].sCPR[203].nSPOffsetCS = 3497; sT[0].sCP[0].sCPR[203].nSPOffsetLek = 3498;
sT[0].sCP[0].sCPR[204].nDCStart= 532; sT[0].sCP[0].sCPR[204].nDCNum = 4;   sT[0].sCP[0].sCPR[204].nSCStart = 537;  sT[0].sCP[0].sCPR[204].nAckStart =536;  sT[0].sCP[0].sCPR[204].nAckNum =1; sT[0].sCP[0].sCPR[204].nSPOffsetCS = 3534; sT[0].sCP[0].sCPR[204].nSPOffsetLek = 3535;

sT[0].sCP[0].sCPR[205].nDCStart= 538; sT[0].sCP[0].sCPR[205].nDCNum = 4;   sT[0].sCP[0].sCPR[205].nSCStart = 543;  sT[0].sCP[0].sCPR[205].nAckStart =542;  sT[0].sCP[0].sCPR[205].nAckNum =1; sT[0].sCP[0].sCPR[205].nSPOffsetCS = 3571; sT[0].sCP[0].sCPR[205].nSPOffsetLek = 3572;
sT[0].sCP[0].sCPR[206].nDCStart= 544; sT[0].sCP[0].sCPR[206].nDCNum = 4;   sT[0].sCP[0].sCPR[206].nSCStart = 549;  sT[0].sCP[0].sCPR[206].nAckStart =548;  sT[0].sCP[0].sCPR[206].nAckNum =1; sT[0].sCP[0].sCPR[206].nSPOffsetCS = 3608; sT[0].sCP[0].sCPR[206].nSPOffsetLek = 3609;
sT[0].sCP[0].sCPR[207].nDCStart= 550; sT[0].sCP[0].sCPR[207].nDCNum = 4;   sT[0].sCP[0].sCPR[207].nSCStart = 555;  sT[0].sCP[0].sCPR[207].nAckStart =554;  sT[0].sCP[0].sCPR[207].nAckNum =1; sT[0].sCP[0].sCPR[207].nSPOffsetCS = 3645; sT[0].sCP[0].sCPR[207].nSPOffsetLek = 3646;
sT[0].sCP[0].sCPR[208].nDCStart= 556; sT[0].sCP[0].sCPR[208].nDCNum = 4;   sT[0].sCP[0].sCPR[208].nSCStart = 560;  sT[0].sCP[0].sCPR[208].nAckStart =0;    sT[0].sCP[0].sCPR[208].nAckNum =0; sT[0].sCP[0].sCPR[208].nSPOffsetCS = 3663; sT[0].sCP[0].sCPR[208].nSPOffsetLek = 3664;	

sT[0].sCP[0].sCPR[209].nDCStart =561; sT[0].sCP[0].sCPR[209].nDCNum = 1;   sT[0].sCP[0].sCPR[209].nSCStart = 562;  sT[0].sCP[0].sCPR[209].nAckStart =0;    sT[0].sCP[0].sCPR[209].nAckNum =0; sT[0].sCP[0].sCPR[209].nSPOffsetCS = 3679; sT[0].sCP[0].sCPR[209].nSPOffsetLek = 3680;
sT[0].sCP[0].sCPR[210].nDCStart =578; sT[0].sCP[0].sCPR[210].nDCNum = 2;   sT[0].sCP[0].sCPR[210].nSCStart = 582;  sT[0].sCP[0].sCPR[210].nAckStart =0  ;  sT[0].sCP[0].sCPR[210].nAckNum =0; sT[0].sCP[0].sCPR[210].nSPOffsetCS = 3753; sT[0].sCP[0].sCPR[210].nSPOffsetLek = 3754; sT[0].sCP[0].sCPR[210].nSPOffsetCS2 = 3755;   sT[0].sCP[0].sCPR[210].nSPOffsetLek2 = 3756;sT[0].sCP[0].sCPR[210].nSCNum  = 2;

sT[0].sCP[0].sCPR[211].nDCStart =354; sT[0].sCP[0].sCPR[211].nDCNum = 1;   sT[0].sCP[0].sCPR[211].nSCStart = 355;  sT[0].sCP[0].sCPR[211].nAckStart =0;    sT[0].sCP[0].sCPR[211].nAckNum =0; sT[0].sCP[0].sCPR[211].nSPOffsetCS = 3771; sT[0].sCP[0].sCPR[211].nSPOffsetLek = 3772;
sT[0].sCP[0].sCPR[212].nDCStart =498; sT[0].sCP[0].sCPR[212].nDCNum = 1;   sT[0].sCP[0].sCPR[212].nSCStart = 499;  sT[0].sCP[0].sCPR[212].nAckStart =0;    sT[0].sCP[0].sCPR[212].nAckNum =0; sT[0].sCP[0].sCPR[212].nSPOffsetCS = 3787; sT[0].sCP[0].sCPR[212].nSPOffsetLek = 3788;
sT[0].sCP[0].sCPR[213].nDCStart =585; sT[0].sCP[0].sCPR[213].nDCNum = 1;   sT[0].sCP[0].sCPR[213].nSCStart = 586;  sT[0].sCP[0].sCPR[213].nAckStart =0;    sT[0].sCP[0].sCPR[213].nAckNum =0; sT[0].sCP[0].sCPR[213].nSPOffsetCS = 3803; sT[0].sCP[0].sCPR[213].nSPOffsetLek = 3804;
sT[0].sCP[0].sCPR[214].nDCStart =587; sT[0].sCP[0].sCPR[214].nDCNum = 1;   sT[0].sCP[0].sCPR[214].nSCStart = 588;  sT[0].sCP[0].sCPR[214].nAckStart =589;  sT[0].sCP[0].sCPR[214].nAckNum =1; sT[0].sCP[0].sCPR[214].nSPOffsetCS = 3819; sT[0].sCP[0].sCPR[214].nSPOffsetLek = 3820;
sT[0].sCP[0].sCPR[215].nDCStart =590; sT[0].sCP[0].sCPR[215].nDCNum = 1;   sT[0].sCP[0].sCPR[215].nSCStart = 591;  sT[0].sCP[0].sCPR[215].nAckStart =592;  sT[0].sCP[0].sCPR[215].nAckNum =1; sT[0].sCP[0].sCPR[215].nSPOffsetCS = 3835; sT[0].sCP[0].sCPR[215].nSPOffsetLek = 3836;
sT[0].sCP[0].sCPR[216].nDCStart =593; sT[0].sCP[0].sCPR[216].nDCNum = 1;   sT[0].sCP[0].sCPR[216].nSCStart = 594;  sT[0].sCP[0].sCPR[216].nAckStart =595;  sT[0].sCP[0].sCPR[216].nAckNum =1; sT[0].sCP[0].sCPR[216].nSPOffsetCS = 3851; sT[0].sCP[0].sCPR[216].nSPOffsetLek = 3852;
sT[0].sCP[0].sCPR[217].nDCStart =596; sT[0].sCP[0].sCPR[217].nDCNum = 1;   sT[0].sCP[0].sCPR[217].nSCStart = 597;  sT[0].sCP[0].sCPR[217].nAckStart =0;    sT[0].sCP[0].sCPR[217].nAckNum =0; sT[0].sCP[0].sCPR[217].nSPOffsetCS = 3867; sT[0].sCP[0].sCPR[217].nSPOffsetLek = 3868;
sT[0].sCP[0].sCPR[218].nDCStart =598; sT[0].sCP[0].sCPR[218].nDCNum = 1;   sT[0].sCP[0].sCPR[218].nSCStart = 599;  sT[0].sCP[0].sCPR[218].nAckStart =0;    sT[0].sCP[0].sCPR[218].nAckNum =0; sT[0].sCP[0].sCPR[218].nSPOffsetCS = 3883; sT[0].sCP[0].sCPR[218].nSPOffsetLek = 3884;

sT[0].sCP[0].sCPR[219].nDCStart =600; sT[0].sCP[0].sCPR[219].nDCNum = 1;   sT[0].sCP[0].sCPR[219].nSCStart = 601;  sT[0].sCP[0].sCPR[219].nAckStart =0;    sT[0].sCP[0].sCPR[219].nAckNum =0; sT[0].sCP[0].sCPR[219].nSPOffsetCS = 3899; sT[0].sCP[0].sCPR[219].nSPOffsetLek = 3900;
sT[0].sCP[0].sCPR[220].nDCStart =602; sT[0].sCP[0].sCPR[220].nDCNum = 1;   sT[0].sCP[0].sCPR[220].nSCStart = 603;  sT[0].sCP[0].sCPR[220].nAckStart =0;    sT[0].sCP[0].sCPR[220].nAckNum =0; sT[0].sCP[0].sCPR[220].nSPOffsetCS = 3915; sT[0].sCP[0].sCPR[220].nSPOffsetLek = 3916;

sT[0].sCP[0].sCPR[221].nDCStart= 628; sT[0].sCP[0].sCPR[221].nDCNum = 1;   sT[0].sCP[0].sCPR[221].nSCStart = 629;  sT[0].sCP[0].sCPR[221].nAckStart=0;     sT[0].sCP[0].sCPR[221].nAckNum=0;  sT[0].sCP[0].sCPR[221].nSPOffsetCS = 4075; sT[0].sCP[0].sCPR[221].nSPOffsetLek = 4076;

sT[0].sCP[0].sCPR[222].nDCStart= 634; sT[0].sCP[0].sCPR[222].nDCNum = 1;   sT[0].sCP[0].sCPR[222].nSCStart = 635;  sT[0].sCP[0].sCPR[222].nAckStart=636;   sT[0].sCP[0].sCPR[222].nAckNum=1;  sT[0].sCP[0].sCPR[222].nSPOffsetCS = 4109; sT[0].sCP[0].sCPR[222].nSPOffsetLek = 4110;

sT[0].sCP[0].sCPR[223].nDCStart =612; sT[0].sCP[0].sCPR[223].nDCNum = 1;   sT[0].sCP[0].sCPR[223].nSCStart = 613;  sT[0].sCP[0].sCPR[223].nAckStart =0;    sT[0].sCP[0].sCPR[223].nAckNum =0; sT[0].sCP[0].sCPR[223].nSPOffsetCS = 3995; sT[0].sCP[0].sCPR[223].nSPOffsetLek = 3996;
sT[0].sCP[0].sCPR[224].nDCStart =614; sT[0].sCP[0].sCPR[224].nDCNum = 1;   sT[0].sCP[0].sCPR[224].nSCStart = 615;  sT[0].sCP[0].sCPR[224].nAckStart =616;  sT[0].sCP[0].sCPR[224].nAckNum =1; sT[0].sCP[0].sCPR[224].nSPOffsetCS = 4011; sT[0].sCP[0].sCPR[224].nSPOffsetLek = 4012;
sT[0].sCP[0].sCPR[225].nDCStart =617; sT[0].sCP[0].sCPR[225].nDCNum = 1;   sT[0].sCP[0].sCPR[225].nSCStart = 618;  sT[0].sCP[0].sCPR[225].nAckStart =0;    sT[0].sCP[0].sCPR[225].nAckNum =0; sT[0].sCP[0].sCPR[225].nSPOffsetCS = 4027; sT[0].sCP[0].sCPR[225].nSPOffsetLek = 4028;

sT[0].sCP[0].sCPR[226].nDCStart =619; sT[0].sCP[0].sCPR[226].nDCNum = 1;   sT[0].sCP[0].sCPR[226].nSCStart = 620;  sT[0].sCP[0].sCPR[226].nAckStart =621;  sT[0].sCP[0].sCPR[226].nAckNum =1; sT[0].sCP[0].sCPR[226].nSPOffsetCS = 4043; sT[0].sCP[0].sCPR[226].nSPOffsetLek = 4044;
sT[0].sCP[0].sCPR[227].nDCStart =622; sT[0].sCP[0].sCPR[227].nDCNum = 1;   sT[0].sCP[0].sCPR[227].nSCStart = 623;  sT[0].sCP[0].sCPR[227].nAckStart =624;  sT[0].sCP[0].sCPR[227].nAckNum =1; sT[0].sCP[0].sCPR[227].nSPOffsetCS = 4059; sT[0].sCP[0].sCPR[227].nSPOffsetLek = 4060;
sT[0].sCP[0].sCPR[228].nDCStart =625; sT[0].sCP[0].sCPR[228].nDCNum = 1;   sT[0].sCP[0].sCPR[228].nSCStart = 626;  sT[0].sCP[0].sCPR[228].nAckStart =627;  sT[0].sCP[0].sCPR[228].nAckNum =1; sT[0].sCP[0].sCPR[228].nSPOffsetCS = 1780; sT[0].sCP[0].sCPR[228].nSPOffsetLek = 1781;
sT[0].sCP[0].sCPR[229].nDCStart = 0;  sT[0].sCP[0].sCPR[229].nDCNum = 0;   sT[0].sCP[0].sCPR[229].nSCStart = 584;  sT[0].sCP[0].sCPR[229].nAckStart =0;    sT[0].sCP[0].sCPR[229].nAckNum =0; sT[0].sCP[0].sCPR[229].nSPOffsetCS = 995;  sT[0].sCP[0].sCPR[229].nSPOffsetLek = 996;
sT[0].sCP[0].sCPR[230].nDCStart =604; sT[0].sCP[0].sCPR[230].nDCNum = 1;   sT[0].sCP[0].sCPR[230].nSCStart = 605;  sT[0].sCP[0].sCPR[230].nAckStart =606;  sT[0].sCP[0].sCPR[230].nAckNum =1; sT[0].sCP[0].sCPR[230].nSPOffsetCS = 3931; sT[0].sCP[0].sCPR[230].nSPOffsetLek = 3932;
sT[0].sCP[0].sCPR[231].nDCStart =607; sT[0].sCP[0].sCPR[231].nDCNum = 1;   sT[0].sCP[0].sCPR[231].nSCStart = 608;  sT[0].sCP[0].sCPR[231].nAckStart =609;  sT[0].sCP[0].sCPR[231].nAckNum =1; sT[0].sCP[0].sCPR[231].nSPOffsetCS = 3947; sT[0].sCP[0].sCPR[231].nSPOffsetLek = 3948;
sT[0].sCP[0].sCPR[232].nDCStart =640; sT[0].sCP[0].sCPR[232].nDCNum = 1;   sT[0].sCP[0].sCPR[232].nSCStart = 641;  sT[0].sCP[0].sCPR[232].nAckStart =642;  sT[0].sCP[0].sCPR[232].nAckNum =1; sT[0].sCP[0].sCPR[232].nSPOffsetCS = 3963; sT[0].sCP[0].sCPR[232].nSPOffsetLek = 3964;
sT[0].sCP[0].sCPR[233].nDCStart =610; sT[0].sCP[0].sCPR[233].nDCNum = 1;   sT[0].sCP[0].sCPR[233].nSCStart = 611;  sT[0].sCP[0].sCPR[233].nAckStart =0;    sT[0].sCP[0].sCPR[233].nAckNum =0; sT[0].sCP[0].sCPR[233].nSPOffsetCS = 4143; sT[0].sCP[0].sCPR[233].nSPOffsetLek = 4144;
sT[0].sCP[0].sCPR[234].nDCStart =643; sT[0].sCP[0].sCPR[234].nDCNum = 1;   sT[0].sCP[0].sCPR[234].nSCStart = 644;  sT[0].sCP[0].sCPR[234].nAckStart =645;  sT[0].sCP[0].sCPR[234].nAckNum =1; sT[0].sCP[0].sCPR[234].nSPOffsetCS = 4159; sT[0].sCP[0].sCPR[234].nSPOffsetLek = 4160;
sT[0].sCP[0].sCPR[235].nDCStart =646; sT[0].sCP[0].sCPR[235].nDCNum = 1;   sT[0].sCP[0].sCPR[235].nSCStart = 647;  sT[0].sCP[0].sCPR[235].nAckStart =648;  sT[0].sCP[0].sCPR[235].nAckNum =1; sT[0].sCP[0].sCPR[235].nSPOffsetCS = 4175; sT[0].sCP[0].sCPR[235].nSPOffsetLek = 4176;
sT[0].sCP[0].sCPR[236].nDCStart =649; sT[0].sCP[0].sCPR[236].nDCNum = 1;   sT[0].sCP[0].sCPR[236].nSCStart = 650;  sT[0].sCP[0].sCPR[236].nAckStart =651;  sT[0].sCP[0].sCPR[236].nAckNum =1; sT[0].sCP[0].sCPR[236].nSPOffsetCS = 4191; sT[0].sCP[0].sCPR[236].nSPOffsetLek = 4192;
sT[0].sCP[0].sCPR[237].nDCStart =652; sT[0].sCP[0].sCPR[237].nDCNum = 1;   sT[0].sCP[0].sCPR[237].nSCStart = 653;  sT[0].sCP[0].sCPR[237].nAckStart =0;    sT[0].sCP[0].sCPR[237].nAckNum =0; sT[0].sCP[0].sCPR[237].nSPOffsetCS = 4207; sT[0].sCP[0].sCPR[237].nSPOffsetLek = 4208;
sT[0].sCP[0].sCPR[238].nDCStart =654; sT[0].sCP[0].sCPR[238].nDCNum = 1;   sT[0].sCP[0].sCPR[238].nSCStart = 655;  sT[0].sCP[0].sCPR[238].nAckStart =656;  sT[0].sCP[0].sCPR[238].nAckNum =1; sT[0].sCP[0].sCPR[238].nSPOffsetCS = 4223; sT[0].sCP[0].sCPR[238].nSPOffsetLek = 4224;
sT[0].sCP[0].sCPR[239].nDCStart =657; sT[0].sCP[0].sCPR[239].nDCNum = 1;   sT[0].sCP[0].sCPR[239].nSCStart = 658;  sT[0].sCP[0].sCPR[239].nAckStart =0;    sT[0].sCP[0].sCPR[239].nAckNum =0; sT[0].sCP[0].sCPR[239].nSPOffsetCS = 4239; sT[0].sCP[0].sCPR[239].nSPOffsetLek = 4240;
sT[0].sCP[0].sCPR[240].nDCStart =659; sT[0].sCP[0].sCPR[240].nDCNum = 1;   sT[0].sCP[0].sCPR[240].nSCStart = 660;  sT[0].sCP[0].sCPR[240].nAckStart =661;  sT[0].sCP[0].sCPR[240].nAckNum =1; sT[0].sCP[0].sCPR[240].nSPOffsetCS = 4255; sT[0].sCP[0].sCPR[240].nSPOffsetLek = 4256;
sT[0].sCP[0].sCPR[241].nDCStart =662; sT[0].sCP[0].sCPR[241].nDCNum = 1;   sT[0].sCP[0].sCPR[241].nSCStart = 663;  sT[0].sCP[0].sCPR[241].nAckStart =664;  sT[0].sCP[0].sCPR[241].nAckNum =1; sT[0].sCP[0].sCPR[241].nSPOffsetCS = 4271; sT[0].sCP[0].sCPR[241].nSPOffsetLek = 4272;
sT[0].sCP[0].sCPR[242].nDCStart =665; sT[0].sCP[0].sCPR[242].nDCNum = 1;   sT[0].sCP[0].sCPR[242].nSCStart = 666;  sT[0].sCP[0].sCPR[242].nAckStart =0;    sT[0].sCP[0].sCPR[242].nAckNum =0; sT[0].sCP[0].sCPR[242].nSPOffsetCS = 4287; sT[0].sCP[0].sCPR[242].nSPOffsetLek = 4288;
sT[0].sCP[0].sCPR[243].nDCStart =667; sT[0].sCP[0].sCPR[243].nDCNum = 1;   sT[0].sCP[0].sCPR[243].nSCStart = 668;  sT[0].sCP[0].sCPR[243].nAckStart =669;  sT[0].sCP[0].sCPR[243].nAckNum =1; sT[0].sCP[0].sCPR[243].nSPOffsetCS = 4303; sT[0].sCP[0].sCPR[243].nSPOffsetLek = 4304;
sT[0].sCP[0].sCPR[244].nDCStart =670; sT[0].sCP[0].sCPR[244].nDCNum = 1;   sT[0].sCP[0].sCPR[244].nSCStart = 671;  sT[0].sCP[0].sCPR[244].nAckStart =0;    sT[0].sCP[0].sCPR[244].nAckNum =0; sT[0].sCP[0].sCPR[244].nSPOffsetCS = 4319; sT[0].sCP[0].sCPR[244].nSPOffsetLek = 4320;
sT[0].sCP[0].sCPR[245].nDCStart =672; sT[0].sCP[0].sCPR[245].nDCNum = 1;   sT[0].sCP[0].sCPR[245].nSCStart = 673;  sT[0].sCP[0].sCPR[245].nAckStart =0;    sT[0].sCP[0].sCPR[245].nAckNum =0; sT[0].sCP[0].sCPR[245].nSPOffsetCS = 4335; sT[0].sCP[0].sCPR[245].nSPOffsetLek = 4336;

sT[0].sCP[0].sCPR[246].nDCStart =674; sT[0].sCP[0].sCPR[246].nDCNum = 1;   sT[0].sCP[0].sCPR[246].nSCStart = 675;  sT[0].sCP[0].sCPR[246].nAckStart =0;    sT[0].sCP[0].sCPR[246].nAckNum =0; sT[0].sCP[0].sCPR[246].nSPOffsetCS = 4351; sT[0].sCP[0].sCPR[246].nSPOffsetLek = 4352;
sT[0].sCP[0].sCPR[247].nDCStart =676; sT[0].sCP[0].sCPR[247].nDCNum = 1;   sT[0].sCP[0].sCPR[247].nSCStart = 677;  sT[0].sCP[0].sCPR[247].nAckStart =747;  sT[0].sCP[0].sCPR[247].nAckNum =1; sT[0].sCP[0].sCPR[247].nSPOffsetCS = 4367; sT[0].sCP[0].sCPR[247].nSPOffsetLek = 4368;
sT[0].sCP[0].sCPR[248].nDCStart =678; sT[0].sCP[0].sCPR[248].nDCNum = 1;   sT[0].sCP[0].sCPR[248].nSCStart = 679;  sT[0].sCP[0].sCPR[248].nAckStart =717;  sT[0].sCP[0].sCPR[248].nAckNum =1; sT[0].sCP[0].sCPR[248].nSPOffsetCS = 4383; sT[0].sCP[0].sCPR[248].nSPOffsetLek = 4384;
sT[0].sCP[0].sCPR[249].nDCStart =684; sT[0].sCP[0].sCPR[249].nDCNum = 1;   sT[0].sCP[0].sCPR[249].nSCStart = 685;  sT[0].sCP[0].sCPR[249].nAckStart =0;    sT[0].sCP[0].sCPR[249].nAckNum =0; sT[0].sCP[0].sCPR[249].nSPOffsetCS = 4431; sT[0].sCP[0].sCPR[249].nSPOffsetLek = 4432;
sT[0].sCP[0].sCPR[250].nDCStart =680; sT[0].sCP[0].sCPR[250].nDCNum = 1;   sT[0].sCP[0].sCPR[250].nSCStart = 681;  sT[0].sCP[0].sCPR[250].nAckStart =0;    sT[0].sCP[0].sCPR[250].nAckNum =0; sT[0].sCP[0].sCPR[250].nSPOffsetCS = 4399; sT[0].sCP[0].sCPR[250].nSPOffsetLek = 4400;
sT[0].sCP[0].sCPR[251].nDCStart =682; sT[0].sCP[0].sCPR[251].nDCNum = 1;   sT[0].sCP[0].sCPR[251].nSCStart = 683;  sT[0].sCP[0].sCPR[251].nAckStart =0;    sT[0].sCP[0].sCPR[251].nAckNum =0; sT[0].sCP[0].sCPR[251].nSPOffsetCS = 4415; sT[0].sCP[0].sCPR[251].nSPOffsetLek = 4416;
sT[0].sCP[0].sCPR[252].nDCStart =686; sT[0].sCP[0].sCPR[252].nDCNum = 1;   sT[0].sCP[0].sCPR[252].nSCStart = 687;  sT[0].sCP[0].sCPR[252].nAckStart =0;    sT[0].sCP[0].sCPR[252].nAckNum =0; sT[0].sCP[0].sCPR[252].nSPOffsetCS = 4447; sT[0].sCP[0].sCPR[252].nSPOffsetLek = 4448;
sT[0].sCP[0].sCPR[253].nDCStart =688; sT[0].sCP[0].sCPR[253].nDCNum = 1;   sT[0].sCP[0].sCPR[253].nSCStart = 689;  sT[0].sCP[0].sCPR[253].nAckStart =0;    sT[0].sCP[0].sCPR[253].nAckNum =0; sT[0].sCP[0].sCPR[253].nSPOffsetCS = 4463; sT[0].sCP[0].sCPR[253].nSPOffsetLek = 4464;

sT[0].sCP[0].sCPR[254].nDCStart =690; sT[0].sCP[0].sCPR[254].nDCNum = 1;   sT[0].sCP[0].sCPR[254].nSCStart = 691;  sT[0].sCP[0].sCPR[254].nAckStart =692;  sT[0].sCP[0].sCPR[254].nAckNum =1; sT[0].sCP[0].sCPR[254].nSPOffsetCS = 4479; sT[0].sCP[0].sCPR[254].nSPOffsetLek = 4480;
sT[0].sCP[0].sCPR[255].nDCStart =693; sT[0].sCP[0].sCPR[255].nDCNum = 1;   sT[0].sCP[0].sCPR[255].nSCStart = 694;  sT[0].sCP[0].sCPR[255].nAckStart =695;  sT[0].sCP[0].sCPR[255].nAckNum =1; sT[0].sCP[0].sCPR[255].nSPOffsetCS = 4495; sT[0].sCP[0].sCPR[255].nSPOffsetLek = 4496;
sT[0].sCP[0].sCPR[256].nDCStart =696; sT[0].sCP[0].sCPR[256].nDCNum = 1;   sT[0].sCP[0].sCPR[256].nSCStart = 697;  sT[0].sCP[0].sCPR[256].nAckStart =698;  sT[0].sCP[0].sCPR[256].nAckNum =1; sT[0].sCP[0].sCPR[256].nSPOffsetCS = 4511; sT[0].sCP[0].sCPR[256].nSPOffsetLek = 4512;
sT[0].sCP[0].sCPR[257].nDCStart =699; sT[0].sCP[0].sCPR[257].nDCNum = 1;   sT[0].sCP[0].sCPR[257].nSCStart = 700;  sT[0].sCP[0].sCPR[257].nAckStart =701;  sT[0].sCP[0].sCPR[257].nAckNum =1; sT[0].sCP[0].sCPR[257].nSPOffsetCS = 4527; sT[0].sCP[0].sCPR[257].nSPOffsetLek = 4528;
sT[0].sCP[0].sCPR[258].nDCStart =702; sT[0].sCP[0].sCPR[258].nDCNum = 1;   sT[0].sCP[0].sCPR[258].nSCStart = 703;  sT[0].sCP[0].sCPR[258].nAckStart =704;  sT[0].sCP[0].sCPR[258].nAckNum =1; sT[0].sCP[0].sCPR[258].nSPOffsetCS = 4543; sT[0].sCP[0].sCPR[258].nSPOffsetLek = 4544;
sT[0].sCP[0].sCPR[259].nDCStart =705; sT[0].sCP[0].sCPR[259].nDCNum = 1;   sT[0].sCP[0].sCPR[259].nSCStart = 706;  sT[0].sCP[0].sCPR[259].nAckStart =707;  sT[0].sCP[0].sCPR[259].nAckNum =1; sT[0].sCP[0].sCPR[259].nSPOffsetCS = 4559; sT[0].sCP[0].sCPR[259].nSPOffsetLek = 4560;
sT[0].sCP[0].sCPR[260].nDCStart =708; sT[0].sCP[0].sCPR[260].nDCNum = 1;   sT[0].sCP[0].sCPR[260].nSCStart = 709;  sT[0].sCP[0].sCPR[260].nAckStart =710;  sT[0].sCP[0].sCPR[260].nAckNum =1; sT[0].sCP[0].sCPR[260].nSPOffsetCS = 4575; sT[0].sCP[0].sCPR[260].nSPOffsetLek = 4576;
sT[0].sCP[0].sCPR[261].nDCStart =711; sT[0].sCP[0].sCPR[261].nDCNum = 1;   sT[0].sCP[0].sCPR[261].nSCStart = 712;  sT[0].sCP[0].sCPR[261].nAckStart =713;  sT[0].sCP[0].sCPR[261].nAckNum =1; sT[0].sCP[0].sCPR[261].nSPOffsetCS = 4591; sT[0].sCP[0].sCPR[261].nSPOffsetLek = 4592;
sT[0].sCP[0].sCPR[262].nDCStart =714; sT[0].sCP[0].sCPR[262].nDCNum = 1;   sT[0].sCP[0].sCPR[262].nSCStart = 715;  sT[0].sCP[0].sCPR[262].nAckStart =716;  sT[0].sCP[0].sCPR[262].nAckNum =1; sT[0].sCP[0].sCPR[262].nSPOffsetCS = 4607; sT[0].sCP[0].sCPR[262].nSPOffsetLek = 4608;
sT[0].sCP[0].sCPR[263].nDCStart =718; sT[0].sCP[0].sCPR[263].nDCNum = 1;   sT[0].sCP[0].sCPR[263].nSCStart = 719;  sT[0].sCP[0].sCPR[263].nAckStart =720;  sT[0].sCP[0].sCPR[263].nAckNum =1; sT[0].sCP[0].sCPR[263].nSPOffsetCS = 4623; sT[0].sCP[0].sCPR[263].nSPOffsetLek = 4624;
sT[0].sCP[0].sCPR[264].nDCStart =721; sT[0].sCP[0].sCPR[264].nDCNum = 1;   sT[0].sCP[0].sCPR[264].nSCStart = 722;  sT[0].sCP[0].sCPR[264].nAckStart =0;	   sT[0].sCP[0].sCPR[264].nAckNum =0; sT[0].sCP[0].sCPR[264].nSPOffsetCS = 4639; sT[0].sCP[0].sCPR[264].nSPOffsetLek = 4640;
sT[0].sCP[0].sCPR[265].nDCStart =723; sT[0].sCP[0].sCPR[265].nDCNum = 1;   sT[0].sCP[0].sCPR[265].nSCStart = 724;  sT[0].sCP[0].sCPR[265].nAckStart =0;	   sT[0].sCP[0].sCPR[265].nAckNum =0; sT[0].sCP[0].sCPR[265].nSPOffsetCS = 4655; sT[0].sCP[0].sCPR[265].nSPOffsetLek = 4656;
sT[0].sCP[0].sCPR[266].nDCStart =725; sT[0].sCP[0].sCPR[266].nDCNum = 1;   sT[0].sCP[0].sCPR[266].nSCStart = 726;  sT[0].sCP[0].sCPR[266].nAckStart =0;	   sT[0].sCP[0].sCPR[266].nAckNum =0; sT[0].sCP[0].sCPR[266].nSPOffsetCS = 4671; sT[0].sCP[0].sCPR[266].nSPOffsetLek = 4672;
sT[0].sCP[0].sCPR[267].nDCStart =727; sT[0].sCP[0].sCPR[267].nDCNum = 1;   sT[0].sCP[0].sCPR[267].nSCStart = 728;  sT[0].sCP[0].sCPR[267].nAckStart =729;  sT[0].sCP[0].sCPR[267].nAckNum =1; sT[0].sCP[0].sCPR[267].nSPOffsetCS = 4687; sT[0].sCP[0].sCPR[267].nSPOffsetLek = 4688;
sT[0].sCP[0].sCPR[268].nDCStart =730; sT[0].sCP[0].sCPR[268].nDCNum = 1;   sT[0].sCP[0].sCPR[268].nSCStart = 731;  sT[0].sCP[0].sCPR[268].nAckStart =732;  sT[0].sCP[0].sCPR[268].nAckNum =1; sT[0].sCP[0].sCPR[268].nSPOffsetCS = 4703; sT[0].sCP[0].sCPR[268].nSPOffsetLek = 4704;

sT[0].sCP[0].sCPR[269].nDCStart =733; sT[0].sCP[0].sCPR[269].nDCNum = 1;   sT[0].sCP[0].sCPR[269].nSCStart = 734;  sT[0].sCP[0].sCPR[269].nAckStart =0;    sT[0].sCP[0].sCPR[269].nAckNum =0; sT[0].sCP[0].sCPR[269].nSPOffsetCS = 4719; sT[0].sCP[0].sCPR[269].nSPOffsetLek = 4720;
sT[0].sCP[0].sCPR[270].nDCStart =502; sT[0].sCP[0].sCPR[270].nDCNum = 1;   sT[0].sCP[0].sCPR[270].nSCStart = 503;  sT[0].sCP[0].sCPR[270].nAckStart =0;    sT[0].sCP[0].sCPR[270].nAckNum =0; sT[0].sCP[0].sCPR[270].nSPOffsetCS = 3406; sT[0].sCP[0].sCPR[270].nSPOffsetLek = 3407;
sT[0].sCP[0].sCPR[271].nDCStart =742; sT[0].sCP[0].sCPR[271].nDCNum = 4;   sT[0].sCP[0].sCPR[271].nSCStart = 746;  sT[0].sCP[0].sCPR[271].nAckStart =0;    sT[0].sCP[0].sCPR[271].nAckNum =0; sT[0].sCP[0].sCPR[271].nSPOffsetCS = 4778; sT[0].sCP[0].sCPR[271].nSPOffsetLek = 4779;
sT[0].sCP[0].sCPR[272].nDCStart =764; sT[0].sCP[0].sCPR[272].nDCNum = 1;   sT[0].sCP[0].sCPR[272].nSCStart = 765;  sT[0].sCP[0].sCPR[272].nAckStart =766;  sT[0].sCP[0].sCPR[272].nAckNum =1; sT[0].sCP[0].sCPR[272].nSPOffsetCS = 4127; sT[0].sCP[0].sCPR[272].nSPOffsetLek = 4128;
sT[0].sCP[0].sCPR[273].nDCStart =767; sT[0].sCP[0].sCPR[273].nDCNum = 1;   sT[0].sCP[0].sCPR[273].nSCStart = 768;  sT[0].sCP[0].sCPR[273].nAckStart =0;    sT[0].sCP[0].sCPR[273].nAckNum =0; sT[0].sCP[0].sCPR[273].nSPOffsetCS = 4093; sT[0].sCP[0].sCPR[273].nSPOffsetLek = 4094;

	
/* Veszprém átjátszó -----------------------------------------------------------*/	
sT[0].sTI[0].nType = TYP_MOT;	

	/*sT[0].sMOT[0].nTableNumPar			= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[0].nIEC_SP				= 1;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[0].nIEC_SP_NUM			= 8;		/* Egybites értékek száma*/	
	sT[0].sMOT[0].nIEC_DP_NUM			= 0;
	sT[0].sMOT[0].nNMNum      			= 0;



/* Veszprém, NATO -------------------------------------------------------------*/
sT[0].sTI[1].nType = TYP_TAL;	

		/*sT[0].sTAL[1].nTableNumPar		= 2;*/
		sT[0].sTAL[1].nIEC_SP       		= 9;
		/*sT[0].sTAL[1].nIEC_ElsoZarlatCim	= 9;*/
		sT[0].sTAL[1].nIEC_OsszevontHiba	= 41;
		sT[0].sTAL[1].nIEC_MT_KommHiba	= 42;
		sT[0].sTAL[1].nIEC_DP       		= 1;
		sT[0].sTAL[1].nIEC_DP_FSZ1  		= 5;
		sT[0].sTAL[1].nIEC_NM				= 1;
		sT[0].sTAL[1].nNMNum		  		= 4;
		sT[0].sTAL[1].nIEC_DP_2BIT1 		= 35;
		sT[0].sTAL[1].nIEC_DP_2BIT2 		= 36;
		sT[0].sTAL[1].nIEC_DP_2BIT3 		= 0;
		sT[0].sTAL[1].nIEC_DP_2BIT_KINT1	= 912;
		sT[0].sTAL[1].nIEC_DP_2BIT_BENT1	= 913;
		sT[0].sTAL[1].nIEC_DP_2BIT_KINT2	= 920;
		sT[0].sTAL[1].nIEC_DP_2BIT_BENT2	= 925;
		sT[0].sTAL[1].nIEC_DP_2BIT_KINT3	= 0;
		sT[0].sTAL[1].nIEC_DP_2BIT_BENT3	= 0;

/* Kapuvar átjátszó -----------------------------------------------------------*/	
sT[0].sTI[2].nType = TYP_MOT;	

	/*sT[0].sMOT[2].nTableNumPar		= 2;		Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[2].nIEC_SP				= 1240;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[2].nIEC_SP_NUM			= 8;		/* Egybites értékek száma*/	
	sT[0].sMOT[2].nIEC_DP_NUM			= 0;
	sT[0].sMOT[2].nNMNum      			= 0;
	
/* Nyul domb átjátszó -----------------------------------------------------------*/	
sT[0].sTI[3].nType = TYP_MOT;	

	/*sT[0].sMOT[3].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[3].nIEC_SP				= 53;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[3].nIEC_SP_NUM			= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[3].nIEC_DP_NUM			= 0;
	sT[0].sMOT[3].nNMNum      			= 0;


/* Tapolca átjátszó -----------------------------------------------------------*/	
sT[0].sTI[4].nType = TYP_MOT;	

	/*sT[0].sMOT[4].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[4].nIEC_SP				= 63;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[4].nIEC_SP_NUM			= 1;		/* Egybites értékek száma*/	
	sT[0].sMOT[4].nIEC_SP_FLAG		= 64;		/* Egybites FLAG értékek IEC kezdõcíme*/
	sT[0].sMOT[4].nIEC_SP_FLAG_NUM	= 4;		/* Egybites FLAG értékek száma*/
	sT[0].sMOT[4].nIEC_DP_NUM			= 0;
	sT[0].sMOT[4].nNMNum      			= 0;

/* Tapolca, Kazinczy II. fûtõmû -----------------------------------------------------------*/	
sT[0].sTI[5].nType = TYP_MOT;	

	/*sT[0].sMOT[5].nTableNumPar		= 2;		Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[5].nIEC_SP				= 74;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[5].nIEC_SP_NUM			= 12;		/* Egybites értékek száma*/	
	sT[0].sMOT[5].nIEC_SP_FLAG			= 0;		/* Egybites FLAG értékek IEC kezdõcíme*/
	sT[0].sMOT[5].nIEC_SP_FLAG_NUM		= 0;		/* Egybites FLAG értékek száma*/
	sT[0].sMOT[5].nIEC_DP				= 9;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[5].nIEC_DP_NUM			= 8;   		/* Két bites értékek száma*/	
	sT[0].sMOT[5].nIEC_DP_FSZ1			= 0;		/* 1. földelõ szakaszoló IEC címe*/
	sT[0].sMOT[5].nIEC_DP_FSZ_NUM		= 0;		/* Földelõ szakaszolók száma*/
	sT[0].sMOT[5].nIEC_NM				= 5;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[5].nNMNum				= 9;		/* Analóg mérések száma*/


/* Gyor, G1 futomu -------------------------------------------------------------*/
sT[0].sTI[6].nType = TYP_TAL;	

	/*sT[0].sTAL[6].nTableNumPar		= 2;*/
	sT[0].sTAL[6].nIEC_SP       		= 89;
	/*sT[0].sTAL[6].nIEC_ElsoZarlatCim	= 0;*/
	sT[0].sTAL[6].nIEC_OsszevontHiba	= 0;
	sT[0].sTAL[6].nIEC_MT_KommHiba	= 0;
	sT[0].sTAL[6].nIEC_DP       		= 19;
	
		sT[0].sTAL[6].nIEC_DP_2BIT1 		= 482;
		sT[0].sTAL[6].nIEC_DP_2BIT2 		= 483;
		sT[0].sTAL[6].nIEC_DP_2BIT3 		= 0;
		sT[0].sTAL[6].nIEC_DP_2BIT_KINT1	= 912;
		sT[0].sTAL[6].nIEC_DP_2BIT_BENT1	= 913;
		sT[0].sTAL[6].nIEC_DP_2BIT_KINT2	= 920;
		sT[0].sTAL[6].nIEC_DP_2BIT_BENT2	= 925;
		sT[0].sTAL[6].nIEC_DP_2BIT_KINT3	= 0;
		sT[0].sTAL[6].nIEC_DP_2BIT_BENT3	= 0;
		
	

/* Esztergom átjátszó -----------------------------------------------------------*/	
sT[0].sTI[7].nType = TYP_MOT;	

	/*sT[0].sMOT[7].nTableNumPar			= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[7].nIEC_SP				= 1208;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[7].nIEC_SP_NUM			= 1;		/* Egybites értékek száma*/	
	sT[0].sMOT[7].nIEC_SP_FLAG			= 1209;		/* Egybites FLAG értékek IEC kezdõcíme*/
	sT[0].sMOT[7].nIEC_SP_FLAG_NUM		= 13;		/* Egybites FLAG értékek száma*/
	sT[0].sMOT[7].nIEC_DP				= 311;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[7].nIEC_DP_NUM			= 1;
	sT[0].sMOT[7].nNMNum      			= 0;

/* Esztergom, Vasary Kolos -----------------------------------------------------------*/	
sT[0].sTI[8].nType = TYP_MOT;	

	/*sT[0].sMOT[8].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[8].nIEC_SP				= 136;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[8].nIEC_SP_NUM			= 6;		/* Egybites értékek száma*/	
	sT[0].sMOT[8].nIEC_SP_FLAG		= 142;		/* Egybites FLAG értékek IEC kezdõcíme*/
	sT[0].sMOT[8].nIEC_SP_FLAG_NUM	= 4;		/* Egybites FLAG értékek száma*/
	sT[0].sMOT[8].nIEC_DP				= 26;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[8].nIEC_DP_NUM			= 4;   		/* Két bites értékek száma*/	
	sT[0].sMOT[8].nIEC_DP_FSZ1		= 30;		/* 1. földelõ szakaszoló IEC címe*/
	sT[0].sMOT[8].nIEC_DP_FSZ_NUM		= 3;		/* Földelõ szakaszolók száma*/
	sT[0].sMOT[8].nIEC_NM				= 34;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[8].nNMNum				= 9;		/* Analóg mérések száma*/

/* TMOK, 62-77 -----------------------------------------------------------*/	
sT[0].sTI[9].nType = TYP_TMOK;	

	sT[0].sMOT[9].nIEC_SP				= 149;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[9].nIEC_DP				= 34;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[9].nIEC_NM				= 43;		/* Mérések IEC kezdõcíme */		
	
/* Sopronkovesd átjátszó -----------------------------------------------------------*/	
sT[0].sTI[10].nType = TYP_MOT;	

	/*sT[0].sMOT[10].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[10].nIEC_SP			= 165;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[10].nIEC_SP_NUM		= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[10].nIEC_DP_NUM			= 0;
	sT[0].sMOT[10].nNMNum      			= 0;

/*  TMOK, 64-67  -----------------------------------------------------------*/	
sT[0].sTI[11].nType = TYP_TMOK;	

	sT[0].sMOT[11].nIEC_SP			= 172;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[11].nIEC_DP			= 37;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[11].nIEC_NM			= 46;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-71  -----------------------------------------------------------*/	
sT[0].sTI[12].nType = TYP_TMOK;	

	sT[0].sMOT[12].nIEC_SP			= 188;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[12].nIEC_DP			= 38;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[12].nIEC_NM			= 49;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-76  -----------------------------------------------------------*/	
sT[0].sTI[13].nType = TYP_TMOK;	

	sT[0].sMOT[13].nIEC_SP			= 204;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[13].nIEC_DP			= 39;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[13].nIEC_NM			= 52;		/* Mérések IEC kezdõcíme */		
	

/*  TMOK, 61-60  -----------------------------------------------------------*/	
sT[0].sTI[14].nType = TYP_TMOK;	

	sT[0].sMOT[14].nIEC_SP			= 220;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[14].nIEC_DP			= 40;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[14].nIEC_NM			= 55;		/* Mérések IEC kezdõcíme */		
	
/*  Pápa atjatszo  -----------------------------------------------------------*/	
sT[0].sTI[15].nType = TYP_MOT;	

	/*sT[0].sMOT[15].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[15].nIEC_SP			= 236;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[15].nIEC_SP_NUM		= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[15].nIEC_DP_NUM			= 0;
	sT[0].sMOT[15].nNMNum      			= 0;

/*  TMOK, 51_48  -----------------------------------------------------------*/	
sT[0].sTI[16].nType = TYP_TMOK;	

	sT[0].sMOT[16].nIEC_SP			= 250;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[16].nIEC_DP			= 41;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[16].nIEC_NM			= 58;		/* Mérések IEC kezdõcíme */		
	

/*  Korishegy atjatszo  -----------------------------------------------------------*/	
sT[0].sTI[17].nType = TYP_MOT;	

	/*sT[0].sMOT[17].nTableNumPar		= 2;		Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[17].nIEC_SP			= 266;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[17].nIEC_SP_NUM		= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[17].nIEC_DP_NUM			= 0;
	sT[0].sMOT[17].nNMNum      			= 0;

/*  TMOK, 65-13  -----------------------------------------------------------*/	
sT[0].sTI[18].nType = TYP_TMOK;	

	sT[0].sMOT[18].nIEC_SP			= 273;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[18].nIEC_DP			= 42;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[18].nIEC_NM			= 61;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 65-14  -----------------------------------------------------------*/	
sT[0].sTI[19].nType = TYP_TMOK;	

	sT[0].sMOT[19].nIEC_SP			= 289;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[19].nIEC_DP			= 43;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[19].nIEC_NM			= 64;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 11-02  -----------------------------------------------------------*/	
sT[0].sTI[20].nType = TYP_TMOK;	

	sT[0].sMOT[20].nIEC_SP			= 369;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[20].nIEC_DP			= 48;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[20].nIEC_NM			= 79;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 11-54  -----------------------------------------------------------*/	
sT[0].sTI[21].nType = TYP_TMOK;	

	sT[0].sMOT[21].nIEC_SP			= 449;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[21].nIEC_DP			= 53;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[21].nIEC_NM			= 94;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 11-78  -----------------------------------------------------------*/	
sT[0].sTI[22].nType = TYP_TMOK;	

	sT[0].sMOT[22].nIEC_SP			= 385;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[22].nIEC_DP			= 49;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[22].nIEC_NM			= 82;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 10-77  -----------------------------------------------------------*/	
sT[0].sTI[23].nType = TYP_TMOK;	

	sT[0].sMOT[23].nIEC_SP			= 401;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[23].nIEC_DP			= 50;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[23].nIEC_NM			= 85;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 11-08  -----------------------------------------------------------*/	
sT[0].sTI[24].nType = TYP_TMOK;	

	sT[0].sMOT[24].nIEC_SP			= 417;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[24].nIEC_DP			= 51;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[24].nIEC_NM			= 88;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 11-87  -----------------------------------------------------------*/	
sT[0].sTI[25].nType = TYP_TMOK;	

	sT[0].sMOT[25].nIEC_SP			= 433;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[25].nIEC_DP			= 52;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[25].nIEC_NM			= 91;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 62-20  -----------------------------------------------------------*/	
sT[0].sTI[26].nType = TYP_TMOK;	

	sT[0].sMOT[26].nIEC_SP			= 305;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[26].nIEC_DP			= 44;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[26].nIEC_NM			= 67;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 64-30  -----------------------------------------------------------*/	
sT[0].sTI[27].nType = TYP_TMOK;	

	sT[0].sMOT[27].nIEC_SP			= 321;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[27].nIEC_DP			= 45;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[27].nIEC_NM			= 70;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-62  -----------------------------------------------------------*/	
sT[0].sTI[28].nType = TYP_TMOK;	

	sT[0].sMOT[28].nIEC_SP			= 337;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[28].nIEC_DP			= 46;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[28].nIEC_NM			= 73;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-65  -----------------------------------------------------------*/	
sT[0].sTI[29].nType = TYP_TMOK;	

	sT[0].sMOT[29].nIEC_SP			= 353;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[29].nIEC_DP			= 47;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[29].nIEC_NM			= 76;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-81  -----------------------------------------------------------*/	
sT[0].sTI[30].nType = TYP_TMOK;	

	sT[0].sMOT[30].nIEC_SP			= 465;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[30].nIEC_DP			= 54;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[30].nIEC_NM			= 97;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-83  -----------------------------------------------------------*/	
sT[0].sTI[31].nType = TYP_TMOK;	

	sT[0].sMOT[31].nIEC_SP			= 481;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[31].nIEC_DP			= 55;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[31].nIEC_NM			= 100;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 64-17  -----------------------------------------------------------*/	
sT[0].sTI[32].nType = TYP_TMOK;	

	sT[0].sMOT[32].nIEC_SP			= 500;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[32].nIEC_DP			= 56;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[32].nIEC_NM			= 103;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 41-99  -----------------------------------------------------------*/	
sT[0].sTI[33].nType = TYP_TMOK;	

	sT[0].sMOT[33].nIEC_SP			= 516;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[33].nIEC_DP			= 57;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[33].nIEC_NM			= 106;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-17  -----------------------------------------------------------*/	
sT[0].sTI[34].nType = TYP_TMOK;	

	sT[0].sMOT[34].nIEC_SP			= 532;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[34].nIEC_DP			= 58;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[34].nIEC_NM			= 109;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-20  -----------------------------------------------------------*/	
sT[0].sTI[35].nType = TYP_TMOK;	

	sT[0].sMOT[35].nIEC_SP			= 548;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[35].nIEC_DP			= 59;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[35].nIEC_NM			= 112;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-45  -----------------------------------------------------------*/	
sT[0].sTI[36].nType = TYP_TMOK;	

	sT[0].sMOT[36].nIEC_SP			= 1192;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[36].nIEC_DP			= 98;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[36].nIEC_NM			= 229;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 11-49  -----------------------------------------------------------*/	
sT[0].sTI[37].nType = TYP_TMOK;	

	sT[0].sMOT[37].nIEC_SP			= 564;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[37].nIEC_DP			= 60;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[37].nIEC_NM			= 115;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-75  -----------------------------------------------------------*/	
sT[0].sTI[38].nType = TYP_TMOK;	

	sT[0].sMOT[38].nIEC_SP			= 580;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[38].nIEC_DP			= 61;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[38].nIEC_NM			= 118;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 64-72  -----------------------------------------------------------*/	
sT[0].sTI[39].nType = TYP_TMOK;	

	sT[0].sMOT[39].nIEC_SP			= 596;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[39].nIEC_DP			= 62;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[39].nIEC_NM			= 121;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-39  -----------------------------------------------------------*/	
sT[0].sTI[40].nType = TYP_TMOK;	

	sT[0].sMOT[40].nIEC_SP			= 612;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[40].nIEC_DP			= 63;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[40].nIEC_NM			= 124;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-11  -----------------------------------------------------------*/	
sT[0].sTI[41].nType = TYP_TMOK;	

	sT[0].sMOT[41].nIEC_SP			= 628;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[41].nIEC_DP			= 64;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[41].nIEC_NM			= 127;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-08  -----------------------------------------------------------*/	
sT[0].sTI[42].nType = TYP_TMOK;	

	sT[0].sMOT[42].nIEC_SP			= 644;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[42].nIEC_DP			= 65;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[42].nIEC_NM			= 130;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-36  -----------------------------------------------------------*/	
sT[0].sTI[43].nType = TYP_TMOK;	

	sT[0].sMOT[43].nIEC_SP			= 660;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[43].nIEC_DP			= 66;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[43].nIEC_NM			= 133;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-37  -----------------------------------------------------------*/	
sT[0].sTI[44].nType = TYP_TMOK;	

	sT[0].sMOT[44].nIEC_SP			= 676;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[44].nIEC_DP			= 67;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[44].nIEC_NM			= 136;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 13-01  -----------------------------------------------------------*/	
sT[0].sTI[45].nType = TYP_TMOK;	

	sT[0].sMOT[45].nIEC_SP			= 692;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[45].nIEC_DP			= 68;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[45].nIEC_NM			= 139;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 13-96  -----------------------------------------------------------*/	
sT[0].sTI[46].nType = TYP_TMOK;	

	sT[0].sMOT[46].nIEC_SP			= 708;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[46].nIEC_DP			= 69;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[46].nIEC_NM			= 142;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 65-08  -----------------------------------------------------------*/	
sT[0].sTI[47].nType = TYP_TMOK;	

	sT[0].sMOT[47].nIEC_SP			= 724;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[47].nIEC_DP			= 70;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[47].nIEC_NM			= 145;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-07  -----------------------------------------------------------*/	
sT[0].sTI[48].nType = TYP_TMOK;	

	sT[0].sMOT[48].nIEC_SP			= 750;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[48].nIEC_DP			= 71;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[48].nIEC_NM			= 148;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-05  -----------------------------------------------------------*/	
sT[0].sTI[49].nType = TYP_TMOK;	

	sT[0].sMOT[49].nIEC_SP			= 766;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[49].nIEC_DP			= 72;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[49].nIEC_NM			= 151;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-03  -----------------------------------------------------------*/	
sT[0].sTI[50].nType = TYP_TMOK;	

	sT[0].sMOT[50].nIEC_SP			= 782;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[50].nIEC_DP			= 73;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[50].nIEC_NM			= 154;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 66-92  -----------------------------------------------------------*/	
sT[0].sTI[51].nType = TYP_TMOK;	

	sT[0].sMOT[51].nIEC_SP			= 798;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[51].nIEC_DP			= 74;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[51].nIEC_NM			= 157;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-97  -----------------------------------------------------------*/	
sT[0].sTI[52].nType = TYP_TMOK;	

	sT[0].sMOT[52].nIEC_SP			= 814;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[52].nIEC_DP			= 75;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[52].nIEC_NM			= 160;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-38  -----------------------------------------------------------*/	
sT[0].sTI[53].nType = TYP_TMOK;	

	sT[0].sMOT[53].nIEC_SP			= 830;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[53].nIEC_DP			= 76;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[53].nIEC_NM			= 163;		/* Mérések IEC kezdõcíme */		
	

/*  TMOK, 64-31  -----------------------------------------------------------*/	
sT[0].sTI[54].nType = TYP_TMOK;	

	sT[0].sMOT[54].nIEC_SP			= 846;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[54].nIEC_DP			= 77;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[54].nIEC_NM			= 166;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 10-23  -----------------------------------------------------------*/	
sT[0].sTI[55].nType = TYP_TMOK;	

	sT[0].sMOT[55].nIEC_SP			= 862;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[55].nIEC_DP			= 78;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[55].nIEC_NM			= 169;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 10-26  -----------------------------------------------------------*/	
sT[0].sTI[56].nType = TYP_TMOK;	

	sT[0].sMOT[56].nIEC_SP			= 878;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[56].nIEC_DP			= 79;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[56].nIEC_NM			= 172;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-02  -----------------------------------------------------------*/	
sT[0].sTI[57].nType = TYP_TMOK;	

	sT[0].sMOT[57].nIEC_SP			= 894;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[57].nIEC_DP			= 80;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[57].nIEC_NM			= 175;		/* Mérések IEC kezdõcíme */		
	

/*  TMOK, 61-19  -----------------------------------------------------------*/	
sT[0].sTI[58].nType = TYP_TMOK;	

	sT[0].sMOT[58].nIEC_SP			= 910;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[58].nIEC_DP			= 81;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[58].nIEC_NM			= 178;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 61-05  -----------------------------------------------------------*/	
sT[0].sTI[59].nType = TYP_TMOK;	

	sT[0].sMOT[59].nIEC_SP			= 926;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[59].nIEC_DP			= 82;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[59].nIEC_NM			= 181;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 64-68  -----------------------------------------------------------*/	
sT[0].sTI[60].nType = TYP_TMOK;	

	sT[0].sMOT[60].nIEC_SP			= 942;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[60].nIEC_DP			= 83;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[60].nIEC_NM			= 184;		/* Mérések IEC kezdõcíme */		
	

/*  TMOK, 62-81  -----------------------------------------------------------*/	
sT[0].sTI[61].nType = TYP_TMOK;	

	sT[0].sMOT[61].nIEC_SP			= 958;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[61].nIEC_DP			= 84;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[61].nIEC_NM			= 187;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-31  -----------------------------------------------------------*/	
sT[0].sTI[62].nType = TYP_TMOK;	

	sT[0].sMOT[62].nIEC_SP			= 974;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[62].nIEC_DP			= 85;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[62].nIEC_NM			= 190;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-30  -----------------------------------------------------------*/	
sT[0].sTI[63].nType = TYP_TMOK;	

	sT[0].sMOT[63].nIEC_SP			= 1000;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[63].nIEC_DP			= 86;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[63].nIEC_NM			= 193;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 10-43  -----------------------------------------------------------*/	
sT[0].sTI[64].nType = TYP_TMOK;	

	sT[0].sMOT[64].nIEC_SP			= 1016;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[64].nIEC_DP			= 87;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[64].nIEC_NM			= 196;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 10-72  -----------------------------------------------------------*/	
sT[0].sTI[65].nType = TYP_TMOK;	

	sT[0].sMOT[65].nIEC_SP			= 1032;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[65].nIEC_DP			= 88;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[65].nIEC_NM			= 199;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-14  -----------------------------------------------------------*/	
sT[0].sTI[66].nType = TYP_TMOK;	

	sT[0].sMOT[66].nIEC_SP			= 1048;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[66].nIEC_DP			= 89;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[66].nIEC_NM			= 202;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 62-24  -----------------------------------------------------------*/	
sT[0].sTI[67].nType = TYP_TMOK;	

	sT[0].sMOT[67].nIEC_SP			= 1064;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[67].nIEC_DP			= 90;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[67].nIEC_NM			= 205;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 70-94  -----------------------------------------------------------*/	
sT[0].sTI[68].nType = TYP_TMOK;	

	sT[0].sMOT[68].nIEC_SP			= 1080;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[68].nIEC_DP			= 91;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[68].nIEC_NM			= 208;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 70-97  -----------------------------------------------------------*/	
sT[0].sTI[69].nType = TYP_TMOK;	

	sT[0].sMOT[69].nIEC_SP			= 1096;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[69].nIEC_DP			= 92;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[69].nIEC_NM			= 211;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 60-28  -----------------------------------------------------------*/	
sT[0].sTI[70].nType = TYP_TMOK;	

	sT[0].sMOT[70].nIEC_SP			= 1112;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[70].nIEC_DP			= 93;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[70].nIEC_NM			= 214;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 11-15  -----------------------------------------------------------*/	
sT[0].sTI[71].nType = TYP_TMOK;	

	sT[0].sMOT[71].nIEC_SP			= 1128;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[71].nIEC_DP			= 94;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[71].nIEC_NM			= 217;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 13-10  -----------------------------------------------------------*/	
sT[0].sTI[72].nType = TYP_TMOK;	

	sT[0].sMOT[72].nIEC_SP			= 1144;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[72].nIEC_DP			= 95;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[72].nIEC_NM			= 220;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 60-43  -----------------------------------------------------------*/	
sT[0].sTI[73].nType = TYP_TMOK;	

	sT[0].sMOT[73].nIEC_SP			= 1160;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[73].nIEC_DP			= 96;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[73].nIEC_NM			= 223;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 60-41  -----------------------------------------------------------*/	
sT[0].sTI[74].nType = TYP_TMOK;	

	sT[0].sMOT[74].nIEC_SP			= 1176;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[74].nIEC_DP			= 97;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[74].nIEC_NM			= 226;		/* Mérések IEC kezdõcíme */		

/*   Kormend atjatszo -----------------------------------------------------------*/	
sT[0].sTI[75].nType = TYP_MOT;	

	/*sT[0].sMOT[75].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[75].nIEC_SP			= 243;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[75].nIEC_SP_NUM		= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[75].nIEC_DP_NUM			= 0;
	sT[0].sMOT[75].nNMNum      			= 0;

/*  TMOK, 53-31  -----------------------------------------------------------*/	
sT[0].sTI[76].nType = TYP_TMOK;	

	sT[0].sMOT[76].nIEC_SP			= 1224;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[76].nIEC_DP			= 100;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[76].nIEC_NM			= 235;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 53-39  -----------------------------------------------------------*/	
sT[0].sTI[77].nType = TYP_TMOK;	

	sT[0].sMOT[77].nIEC_SP			= 1250;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[77].nIEC_DP			= 101;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[77].nIEC_NM			= 240;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 60-45  -----------------------------------------------------------*/	
sT[0].sTI[78].nType = TYP_TMOK;	

	sT[0].sMOT[78].nIEC_SP			= 1192;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[78].nIEC_DP			= 98;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[78].nIEC_NM			= 229;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 86-55  -----------------------------------------------------------*/	
sT[0].sTI[79].nType = TYP_TMOK;	

	sT[0].sMOT[79].nIEC_SP			= 1266;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[79].nIEC_DP			= 102;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[79].nIEC_NM			= 243;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-65  -----------------------------------------------------------*/	
sT[0].sTI[80].nType = TYP_TMOK;	

	sT[0].sMOT[80].nIEC_SP			= 1282;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[80].nIEC_DP			= 103;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[80].nIEC_NM			= 246;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-04  -----------------------------------------------------------*/	
sT[0].sTI[81].nType = TYP_TMOK;	

	sT[0].sMOT[81].nIEC_SP			= 1298;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[81].nIEC_DP			= 104;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[81].nIEC_NM			= 249;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-11  -----------------------------------------------------------*/	
sT[0].sTI[82].nType = TYP_TMOK;	

	sT[0].sMOT[82].nIEC_SP			= 1314;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[82].nIEC_DP			= 105;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[82].nIEC_NM			= 252;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 61-79  -----------------------------------------------------------*/	
sT[0].sTI[83].nType = TYP_TMOK;	

	sT[0].sMOT[83].nIEC_SP			= 1330;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[83].nIEC_DP			= 106;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[83].nIEC_NM			= 255;		/* Mérések IEC kezdõcíme */		


/*  TMOK, 61-81  -----------------------------------------------------------*/	
sT[0].sTI[84].nType = TYP_TMOK;	

	sT[0].sMOT[84].nIEC_SP			= 1346;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[84].nIEC_DP			= 107;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[84].nIEC_NM			= 258;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 70-65  -----------------------------------------------------------*/	
sT[0].sTI[85].nType = TYP_TMOK;	

	sT[0].sMOT[85].nIEC_SP			= 1362;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[85].nIEC_DP			= 108;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[85].nIEC_NM			= 261;		/* Mérések IEC kezdõcíme */		


/*  TMOK, 70-67  -----------------------------------------------------------*/	
sT[0].sTI[86].nType = TYP_TMOK;	

	sT[0].sMOT[86].nIEC_SP			= 1378;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[86].nIEC_DP			= 109;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[86].nIEC_NM			= 264;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-06  -----------------------------------------------------------*/	
sT[0].sTI[87].nType = TYP_TMOK;	

	sT[0].sMOT[87].nIEC_SP			= 1394;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[87].nIEC_DP			= 110;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[87].nIEC_NM			= 267;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-91  -----------------------------------------------------------*/	
sT[0].sTI[88].nType = TYP_TMOK;	

	sT[0].sMOT[88].nIEC_SP			= 1410;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[88].nIEC_DP			= 111;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[88].nIEC_NM			= 270;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-53  -----------------------------------------------------------*/	
sT[0].sTI[89].nType = TYP_TMOK;	

	sT[0].sMOT[89].nIEC_SP			= 1426;			/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[89].nIEC_DP			= 112;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[89].nIEC_NM			= 273;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-75  -----------------------------------------------------------*/	
sT[0].sTI[90].nType = TYP_TMOK;	

	sT[0].sMOT[90].nIEC_SP			= 1442;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[90].nIEC_DP			= 113;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[90].nIEC_NM			= 276;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 50-93  -----------------------------------------------------------*/	
sT[0].sTI[91].nType = TYP_TMOK;	

	sT[0].sMOT[91].nIEC_SP			= 1458;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[91].nIEC_DP			= 114;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[91].nIEC_NM			= 279;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 50-97  -----------------------------------------------------------*/	
sT[0].sTI[92].nType = TYP_TMOK;	

	sT[0].sMOT[92].nIEC_SP			= 1474;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[92].nIEC_DP			= 115;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[92].nIEC_NM			= 282;		/* Mérések IEC kezdõcíme */		

/*  Kabhegy atjatszo  -----------------------------------------------------------*/	
sT[0].sTI[93].nType = TYP_MOT;	

	/*sT[0].sMOT[93].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[93].nIEC_SP			= 740;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[93].nIEC_SP_NUM		= 4;		/* Egybites értékek száma*/	
	sT[0].sMOT[93].nIEC_DP_NUM			= 0;
	sT[0].sMOT[93].nNMNum      			= 0;


/*  TMOK, 72-27  -----------------------------------------------------------*/	
sT[0].sTI[94].nType = TYP_TMOK;	

	sT[0].sMOT[94].nIEC_SP			= 1500;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[94].nIEC_DP			= 116;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[94].nIEC_NM			= 285;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-93  -----------------------------------------------------------*/	
sT[0].sTI[95].nType = TYP_TMOK;	

	sT[0].sMOT[95].nIEC_SP			= 1516;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[95].nIEC_DP			= 117;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[95].nIEC_NM			= 288;		/* Mérések IEC kezdõcíme */		


/*  TMOK, 50-64  -----------------------------------------------------------*/	
sT[0].sTI[96].nType = TYP_TMOK;	

	sT[0].sMOT[96].nIEC_SP			= 1532;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[96].nIEC_DP			= 118;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[96].nIEC_NM			= 291;		/* Mérések IEC kezdõcíme */		


/*  TMOK, 50-69  -----------------------------------------------------------*/	
sT[0].sTI[97].nType = TYP_TMOK;	

	sT[0].sMOT[97].nIEC_SP			= 1548;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[97].nIEC_DP			= 119;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[97].nIEC_NM			= 294;		/* Mérések IEC kezdõcíme */		


/*  TMOK, 72-93  -----------------------------------------------------------*/	
sT[0].sTI[98].nType = TYP_TMOK;	

	sT[0].sMOT[98].nIEC_SP			= 1564;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[98].nIEC_DP			= 120;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[98].nIEC_NM			= 297;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-98  -----------------------------------------------------------*/	
sT[0].sTI[99].nType = TYP_TMOK;	

	sT[0].sMOT[99].nIEC_SP			= 1580;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[99].nIEC_DP			= 121;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[99].nIEC_NM			= 300;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 51-43  -----------------------------------------------------------*/	
sT[0].sTI[100].nType = TYP_TMOK;	

	sT[0].sMOT[100].nIEC_SP			= 1596;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[100].nIEC_DP			= 122;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[100].nIEC_NM			= 303;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 51-69  -----------------------------------------------------------*/	
sT[0].sTI[101].nType = TYP_TMOK;	
	
	sT[0].sMOT[101].nIEC_SP			= 1612;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[101].nIEC_DP			= 123;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[101].nIEC_NM			= 306;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 70-82  -----------------------------------------------------------*/	
sT[0].sTI[102].nType = TYP_TMOK;	

	sT[0].sMOT[102].nIEC_SP			= 1628;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[102].nIEC_DP			= 124;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[102].nIEC_NM			= 309;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 70-81  -----------------------------------------------------------*/	
sT[0].sTI[103].nType = TYP_TMOK;	

	sT[0].sMOT[103].nIEC_SP			= 1644;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[103].nIEC_DP			= 125;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[103].nIEC_NM			= 312;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 52-48  -----------------------------------------------------------*/	
sT[0].sTI[104].nType = TYP_TMOK;	

	sT[0].sMOT[104].nIEC_SP			= 1660;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[104].nIEC_DP			= 126;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[104].nIEC_NM			= 315;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 52-62  -----------------------------------------------------------*/	
sT[0].sTI[105].nType = TYP_TMOK;	

	sT[0].sMOT[105].nIEC_SP			= 1676;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[105].nIEC_DP			= 127;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[105].nIEC_NM			= 318;		/* Mérések IEC kezdõcíme */		


/*  TMOK, 50-82  -----------------------------------------------------------*/	
sT[0].sTI[106].nType = TYP_TMOK;	

	sT[0].sMOT[106].nIEC_SP			= 1910;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[106].nIEC_DP			= 141;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[106].nIEC_NM			= 360;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 52-57  -----------------------------------------------------------*/	
sT[0].sTI[107].nType = TYP_TMOK;	

	sT[0].sMOT[107].nIEC_SP			= 1926;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[107].nIEC_DP			= 142;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[107].nIEC_NM			= 363;		/* Mérések IEC kezdõcíme */		


/*  TMOK, 52-42  -----------------------------------------------------------*/	
sT[0].sTI[108].nType = TYP_TMOK;	

	sT[0].sMOT[108].nIEC_SP			= 1942;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[108].nIEC_DP			= 143;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[108].nIEC_NM			= 366;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 54-11  -----------------------------------------------------------*/	
sT[0].sTI[109].nType = TYP_TMOK;	

	sT[0].sMOT[109].nIEC_SP			= 1958;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[109].nIEC_DP			= 144;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[109].nIEC_NM			= 369;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 51-22  -----------------------------------------------------------*/	
sT[0].sTI[110].nType = TYP_TMOK;	

	sT[0].sMOT[110].nIEC_SP			= 1974;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[110].nIEC_DP			= 145;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[110].nIEC_NM			= 372;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 51-28  -----------------------------------------------------------*/	
sT[0].sTI[111].nType = TYP_TMOK;	

	sT[0].sMOT[111].nIEC_SP			= 2000;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[111].nIEC_DP			= 146;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[111].nIEC_NM			= 375;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 70-75  -----------------------------------------------------------*/	
sT[0].sTI[112].nType = TYP_TMOK;	

	sT[0].sMOT[112].nIEC_SP			= 1692;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[112].nIEC_DP			= 128;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[112].nIEC_NM			= 321;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 74-01  -----------------------------------------------------------*/	
sT[0].sTI[113].nType = TYP_TMOK;	

	sT[0].sMOT[113].nIEC_SP			= 1708;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[113].nIEC_DP			= 129;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[113].nIEC_NM			= 324;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 51-20  -----------------------------------------------------------*/	
sT[0].sTI[114].nType = TYP_TMOK;	

	sT[0].sMOT[114].nIEC_SP			= 2016;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[114].nIEC_DP			= 147;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[114].nIEC_NM			= 378;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 70-88  -----------------------------------------------------------*/	
sT[0].sTI[115].nType = TYP_TMOK;	

	sT[0].sMOT[115].nIEC_SP			= 1782;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[115].nIEC_DP			= 133;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[115].nIEC_NM			= 336;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 74-02  -----------------------------------------------------------*/	
sT[0].sTI[116].nType = TYP_TMOK;	

	sT[0].sMOT[116].nIEC_SP			= 1724;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[116].nIEC_DP			= 130;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[116].nIEC_NM			= 327;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-65  -----------------------------------------------------------*/	
sT[0].sTI[117].nType = TYP_TMOK;	

	sT[0].sMOT[117].nIEC_SP			= 1750;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[117].nIEC_DP			= 131;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[117].nIEC_NM			= 330;		/* Mérések IEC kezdõcíme */		

/*  Dorog atjatszo  -----------------------------------------------------------*/	
sT[0].sTI[118].nType = TYP_MOT;	

	/*sT[0].sMOT[3].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[118].nIEC_SP				= 2725;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[118].nIEC_SP_NUM			= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[118].nIEC_DP_NUM			= 0;
	sT[0].sMOT[118].nNMNum     			= 0;

/*  TMOK, 71-91  -----------------------------------------------------------*/	
sT[0].sTI[119].nType = TYP_TMOK;	

	sT[0].sMOT[119].nIEC_SP			= 1862;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[119].nIEC_DP			= 138;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[119].nIEC_NM			= 351;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-37  -----------------------------------------------------------*/	
sT[0].sTI[120].nType = TYP_TMOK;	

	sT[0].sMOT[120].nIEC_SP			= 1878;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[120].nIEC_DP			= 139;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[120].nIEC_NM			= 354;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-44  -----------------------------------------------------------*/	
sT[0].sTI[121].nType = TYP_TMOK;	

	sT[0].sMOT[121].nIEC_SP			= 1894;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[121].nIEC_DP			= 140;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[121].nIEC_NM			= 357;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 72-77  -----------------------------------------------------------*/	
sT[0].sTI[122].nType = TYP_TMOK;	

	sT[0].sMOT[122].nIEC_SP			= 2032;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[122].nIEC_DP			= 148;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[122].nIEC_NM			= 381;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 70-14  -----------------------------------------------------------*/	
sT[0].sTI[123].nType = TYP_TMOK;	

	sT[0].sMOT[123].nIEC_SP			= 2144;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[123].nIEC_DP			= 155;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[123].nIEC_NM			= 402;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 40-63  -----------------------------------------------------------*/	
sT[0].sTI[124].nType = TYP_TMOK;	

	sT[0].sMOT[124].nIEC_SP			= 2160;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[124].nIEC_DP			= 156;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[124].nIEC_NM			= 405;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 40-61  -----------------------------------------------------------*/	
sT[0].sTI[125].nType = TYP_TMOK;	

	sT[0].sMOT[125].nIEC_SP			= 2176;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[125].nIEC_DP			= 157;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[125].nIEC_NM			= 408;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 11-38  -----------------------------------------------------------*/	
sT[0].sTI[126].nType = TYP_TMOK;	

	sT[0].sMOT[126].nIEC_SP			= 2192;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[126].nIEC_DP			= 158;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[126].nIEC_NM			= 411;		/* Mérések IEC kezdõcíme */		
	
/*  TMOK, 15-50  -----------------------------------------------------------*/	
sT[0].sTI[127].nType = TYP_TMOK;	

	sT[0].sMOT[127].nIEC_SP			= 2208;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[127].nIEC_DP			= 159;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[127].nIEC_NM			= 414;		/* Mérések IEC kezdõcíme */		

/*  LINDE, Repcelak  -----------------------------------------------------------*/	
sT[0].sTI[128].nType = TYP_MOT2;	

	/*sT[0].sMOT[128].nTableNumPar		= 2;		Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[128].nIEC_SP			= 2224;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[128].nIEC_SP_NUM		= 24;		/* Egybites értékek száma*/	
	sT[0].sMOT[128].nIEC_DP			= 160;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[128].nIEC_DP_NUM		= 18;  		/* Két bites értékek száma*/	
	sT[0].sMOT[128].nIEC_NM			= 417;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[128].nNMNum			= 24;		/* Analóg mérések száma*/
	
/* Vasvar, regioho  ----------------------------------------------------------------*/
sT[0].sTI[129].nType = TYP_MOT;

	/*sT[0].sMOT[129].nTableNumPar		= 2;	 Egesz paraméterek tábla sorszáma */
	sT[0].sMOT[129].nIEC_SP				= 3681;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[129].nIEC_SP_NUM			= 12;		/* Egybites értékek száma*/
	sT[0].sMOT[129].nIEC_DP				= 378;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[129].nIEC_DP_NUM			= 6;   		/* Két bites értékek száma*/
	sT[0].sMOT[129].nIEC_NM				= 674;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[129].nNMNum				= 7;		/* Analóg mérések száma*/

/*  TMOK, 72-16  -----------------------------------------------------------*/	
sT[0].sTI[130].nType = TYP_TMOK;	

	sT[0].sMOT[130].nIEC_SP			= 2048;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[130].nIEC_DP			= 149;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[130].nIEC_NM			= 384;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-31  -----------------------------------------------------------*/	
sT[0].sTI[131].nType = TYP_TMOK;	

	sT[0].sMOT[131].nIEC_SP			= 2064;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[131].nIEC_DP			= 150;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[131].nIEC_NM			= 387;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 42-11  -----------------------------------------------------------*/	
sT[0].sTI[132].nType = TYP_TMOK;	

	sT[0].sMOT[132].nIEC_SP			= 1798;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[132].nIEC_DP			= 134;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[132].nIEC_NM			= 339;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 42-34  -----------------------------------------------------------*/	
sT[0].sTI[133].nType = TYP_TMOK;	

	sT[0].sMOT[133].nIEC_SP			= 1814;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[133].nIEC_DP			= 135;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[133].nIEC_NM			= 342;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 42-12  -----------------------------------------------------------*/	
sT[0].sTI[134].nType = TYP_TMOK;	

	sT[0].sMOT[134].nIEC_SP			= 1830;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[134].nIEC_DP			= 136;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[134].nIEC_NM			= 345;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 48-938  -----------------------------------------------------------*/	
sT[0].sTI[135].nType = TYP_TMOK;	

	sT[0].sMOT[135].nIEC_SP			= 1846;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[135].nIEC_DP			= 137;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[135].nIEC_NM			= 348;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-02  -----------------------------------------------------------*/	
sT[0].sTI[136].nType = TYP_TMOK;	

	sT[0].sMOT[136].nIEC_SP			= 2080;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[136].nIEC_DP			= 151;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[136].nIEC_NM			= 390;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-58  -----------------------------------------------------------*/	
sT[0].sTI[137].nType = TYP_TMOK;	

	sT[0].sMOT[137].nIEC_SP			= 2096;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[137].nIEC_DP			= 152;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[137].nIEC_NM			= 393;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 71-28  -----------------------------------------------------------*/	
sT[0].sTI[138].nType = TYP_TMOK;	

	sT[0].sMOT[138].nIEC_SP			= 2112;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[138].nIEC_DP			= 153;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[138].nIEC_NM			= 396;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 70-24  -----------------------------------------------------------*/	
sT[0].sTI[139].nType = TYP_TMOK;	

	sT[0].sMOT[139].nIEC_SP			= 2128;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[139].nIEC_DP			= 154;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[139].nIEC_NM			= 399;		/* Mérések IEC kezdõcíme */		

/* Esztergom, Suzuki 2. -------------------------------------------------------------*/
sT[0].sTI[140].nType = TYP_TAL;	

		/*sT[0].sTAL[140].nTableNumPar			= 2;*/
		sT[0].sTAL[140].nIEC_SP       		= 2250;
		/*sT[0].sTAL[140].nIEC_ElsoZarlatCim	= 2250;*/
		sT[0].sTAL[140].nIEC_OsszevontHiba	= 2282;
		sT[0].sTAL[140].nIEC_MT_KommHiba		= 2283;
		sT[0].sTAL[140].nKommStatusNum		= 2;		
		sT[0].sTAL[140].nIEC_DP       		= 178;
		sT[0].sTAL[140].nIEC_DP_FSZ1  		= 182;
		sT[0].sTAL[140].nIEC_NM				= 441;
		sT[0].sTAL[140].nNMNum		  		= 2;
		
/* Esztergom, TYCO -------------------------------------------------------------*/
sT[0].sTI[141].nType = TYP_TAL;	

		/*sT[0].sTAL[141].nTableNumPar			= 2;*/
		sT[0].sTAL[141].nIEC_SP       		= 2289;
		/*sT[0].sTAL[141].nIEC_ElsoZarlatCim	= 2289;*/
		sT[0].sTAL[141].nIEC_OsszevontHiba	= 2321;
		sT[0].sTAL[141].nIEC_MT_KommHiba		= 2322;
		sT[0].sTAL[141].nKommStatusNum		= 2;		
		sT[0].sTAL[141].nIEC_DP       		= 186;
		sT[0].sTAL[141].nIEC_DP_FSZ1  		= 190;
		sT[0].sTAL[141].nIEC_NM				= 443;
		sT[0].sTAL[141].nNMNum		  		= 2;

/* Esztergom, Lotus Foods -------------------------------------------------------------*/
sT[0].sTI[142].nType = TYP_TAL;	

		/*sT[0].sTAL[142].nTableNumPar			= 2;*/
		sT[0].sTAL[142].nIEC_SP       		= 2328;
		/*sT[0].sTAL[142].nIEC_ElsoZarlatCim	= 2328;*/
		sT[0].sTAL[142].nIEC_OsszevontHiba	= 2360;
		sT[0].sTAL[142].nIEC_MT_KommHiba		= 2361;
		sT[0].sTAL[142].nKommStatusNum		= 2;		
		sT[0].sTAL[142].nIEC_DP       		= 194;
		sT[0].sTAL[142].nIEC_DP_FSZ1  		= 198;
		sT[0].sTAL[142].nIEC_NM				= 445;
		sT[0].sTAL[142].nNMNum		  		= 2;

/* Esztergom, TESCO -------------------------------------------------------------*/
sT[0].sTI[143].nType = TYP_TAL;	

		/*sT[0].sTAL[143].nTableNumPar			= 2;*/
		sT[0].sTAL[143].nIEC_SP       		= 2367;
		/*sT[0].sTAL[143].nIEC_ElsoZarlatCim	= 2367;*/
		sT[0].sTAL[143].nIEC_OsszevontHiba	= 2399;
		sT[0].sTAL[143].nIEC_MT_KommHiba		= 2400;
		sT[0].sTAL[143].nKommStatusNum		= 2;		
		sT[0].sTAL[143].nIEC_DP       		= 202;
		sT[0].sTAL[143].nIEC_DP_FSZ1  		= 206;
		sT[0].sTAL[143].nIEC_NM				= 447;
		sT[0].sTAL[143].nNMNum		  		= 2;


/* Esztergom, Ipari Park1. -------------------------------------------------------------*/
sT[0].sTI[144].nType = TYP_TAL;	

		/*sT[0].sTAL[144].nTableNumPar			= 2;*/
		sT[0].sTAL[144].nIEC_SP       		= 2406;
		/*sT[0].sTAL[144].nIEC_ElsoZarlatCim	= 2406;*/
		sT[0].sTAL[144].nIEC_OsszevontHiba	= 2438;
		sT[0].sTAL[144].nIEC_MT_KommHiba		= 2439;
		sT[0].sTAL[144].nKommStatusNum		= 2;		
		sT[0].sTAL[144].nIEC_DP       		= 210;
		sT[0].sTAL[144].nIEC_DP_FSZ1  		= 214;
		sT[0].sTAL[144].nIEC_NM				= 449;
		sT[0].sTAL[144].nNMNum		  		= 2;

/* Esztergom, Ipari Park2. -------------------------------------------------------------*/
sT[0].sTI[145].nType = TYP_TAL;	

		/*sT[0].sTAL[145].nTableNumPar			= 2;*/
		sT[0].sTAL[145].nIEC_SP       		= 2445;
		/*sT[0].sTAL[145].nIEC_ElsoZarlatCim	= 2445;*/
		sT[0].sTAL[145].nIEC_OsszevontHiba	= 2477;
		sT[0].sTAL[145].nIEC_MT_KommHiba		= 2478;
		sT[0].sTAL[145].nKommStatusNum		= 2;		
		sT[0].sTAL[145].nIEC_DP       		= 218;
		sT[0].sTAL[145].nIEC_DP_FSZ1  		= 222;
		sT[0].sTAL[145].nIEC_NM				= 451;
		sT[0].sTAL[145].nNMNum		  		= 4;

/* Esztergom, Ipari Park3. -------------------------------------------------------------*/
sT[0].sTI[146].nType = TYP_TAL;	

		/*sT[0].sTAL[146].nTableNumPar		= 2;*/
		sT[0].sTAL[146].nIEC_SP       		= 2500;
		/*sT[0].sTAL[146].nIEC_ElsoZarlatCim	= 2500;*/
		sT[0].sTAL[146].nIEC_OsszevontHiba	= 2532;
		sT[0].sTAL[146].nIEC_MT_KommHiba	= 2533;
		sT[0].sTAL[146].nKommStatusNum		= 2;		
		sT[0].sTAL[146].nIEC_DP       		= 226;
		sT[0].sTAL[146].nIEC_DP_FSZ1  		= 230; 
		sT[0].sTAL[146].nIEC_NM				= 455;
		sT[0].sTAL[146].nNMNum		  		= 2;

/* Balatonfured, Furedho -----------------------------------------------------------*/	
sT[0].sTI[147].nType = TYP_MOT;	

	/*sT[0].sMOT[147].nTableNumPar			= 2;		Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[147].nIEC_SP				= 2539;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[147].nIEC_SP_NUM			= 14;		/* Egybites értékek száma*/	
	sT[0].sMOT[147].nIEC_SP_FLAG			= 0;		/* Egybites FLAG értékek IEC kezdõcíme*/
	sT[0].sMOT[147].nIEC_SP_FLAG_NUM		= 0;		/* Egybites FLAG értékek száma*/
	sT[0].sMOT[147].nIEC_DP				= 234;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[147].nIEC_DP_NUM			= 4;   		/* Két bites értékek száma*/	
	sT[0].sMOT[147].nIEC_DP_FSZ1			= 238;		/* 1. földelõ szakaszoló IEC címe*/
	sT[0].sMOT[147].nIEC_DP_FSZ_NUM		= 4;		/* Földelõ szakaszolók száma*/
	sT[0].sMOT[147].nIEC_NM				= 457;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[147].nNMNum				= 7;		/* Analóg mérések száma*/

/* Kormend, Kormendho -----------------------------------------------------------*/	
sT[0].sTI[148].nType = TYP_MOT;	

	/*sT[0].sMOT[148].nTableNumPar			= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[148].nIEC_SP				= 2555;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[148].nIEC_SP_NUM			= 14;		/* Egybites értékek száma*/	
	sT[0].sMOT[148].nIEC_SP_FLAG			= 0;		/* Egybites FLAG értékek IEC kezdõcíme*/
	sT[0].sMOT[148].nIEC_SP_FLAG_NUM		= 0;		/* Egybites FLAG értékek száma*/
	sT[0].sMOT[148].nIEC_DP				= 242;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[148].nIEC_DP_NUM			= 4;   		/* Két bites értékek száma*/	
	sT[0].sMOT[148].nIEC_DP_FSZ1			= 246;		/* 1. földelõ szakaszoló IEC címe*/
	sT[0].sMOT[148].nIEC_DP_FSZ_NUM		= 4;		/* Földelõ szakaszolók száma*/
	sT[0].sMOT[148].nIEC_NM				= 464;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[148].nNMNum				= 7;		/* Analóg mérések száma*/

/*  TMOK, 12-90  -----------------------------------------------------------*/	
sT[0].sTI[149].nType = TYP_TMOK;	

	sT[0].sMOT[149].nIEC_SP			= 2571;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[149].nIEC_DP			= 99;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[149].nIEC_NM			= 471;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 61-24  -----------------------------------------------------------*/	
sT[0].sTI[150].nType = TYP_TMOK;	

	sT[0].sMOT[150].nIEC_SP			= 2587;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[150].nIEC_DP			= 250;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[150].nIEC_NM			= 474;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 50-22  -----------------------------------------------------------*/	
sT[0].sTI[151].nType = TYP_TMOK;	

	sT[0].sMOT[151].nIEC_SP			= 2603;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[151].nIEC_DP			= 251;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[151].nIEC_NM			= 477;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 50-23  -----------------------------------------------------------*/	
sT[0].sTI[152].nType = TYP_TMOK;	

	sT[0].sMOT[152].nIEC_SP			= 2619;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[152].nIEC_DP			= 252;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[152].nIEC_NM			= 480;		/* Mérések IEC kezdõcíme */		

/*  Gyor, Raba repter  -----------------------------------------------------------*/	
sT[0].sTI[153].nType = TYP_MOT;	

	/*sT[0].sMOT[153].nTableNumPar		= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[153].nIEC_SP			= 2635;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[153].nIEC_SP_NUM		= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[153].nIEC_DP			= 253;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[153].nIEC_DP_NUM		= 3;   		/* Két bites értékek száma*/	
	sT[0].sMOT[153].nIEC_NM			= 483;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[153].nNMNum			= 5;		/* Analóg mérések száma*/

/* Gyor, EETEK -------------------------------------------------------------*/
sT[0].sTI[154].nType = TYP_TAL;	

		/*sT[0].sTAL[154].nTableNumPar			= 2;*/
		sT[0].sTAL[154].nIEC_SP       		= 2642;
		/*sT[0].sTAL[154].nIEC_ElsoZarlatCim	= 2642;*/
		sT[0].sTAL[154].nIEC_OsszevontHiba	= 2674;
		sT[0].sTAL[154].nIEC_MT_KommHiba		= 2675;
		sT[0].sTAL[154].nIEC_DP       		= 256;
		sT[0].sTAL[154].nIEC_DP_FSZ1  		= 260;
		sT[0].sTAL[154].nIEC_NM				= 488;
		sT[0].sTAL[154].nNMNum		  		= 9;
		sT[0].sTAL[154].nIEC_DP_2BIT1 		= 264;
		sT[0].sTAL[154].nIEC_DP_2BIT2 		= 265;
		sT[0].sTAL[154].nIEC_DP_2BIT3 		= 0;
		sT[0].sTAL[154].nIEC_DP_2BIT_KINT1	= 912;
		sT[0].sTAL[154].nIEC_DP_2BIT_BENT1	= 913;
		sT[0].sTAL[154].nIEC_DP_2BIT_KINT2	= 920;
		sT[0].sTAL[154].nIEC_DP_2BIT_BENT2	= 925;
		sT[0].sTAL[154].nIEC_DP_2BIT_KINT3	= 0;
		sT[0].sTAL[154].nIEC_DP_2BIT_BENT3	= 0;

/*  TMOK, 61-80  -----------------------------------------------------------*/	
sT[0].sTI[155].nType = TYP_TMOK;	

	sT[0].sMOT[155].nIEC_SP			= 2679;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[155].nIEC_DP			= 266;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[155].nIEC_NM			= 232;		/* Mérések IEC kezdõcíme */		


/*  Balf, gazmotor  -----------------------------------------------------------*/	
sT[0].sTI[156].nType = TYP_MOT;	

	/*sT[0].sMOT[156].nTableNumPar	= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[156].nIEC_SP			= 2695;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[156].nIEC_SP_NUM		= 12;		/* Egybites értékek száma*/	
	sT[0].sMOT[156].nIEC_DP			= 267;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[156].nIEC_DP_NUM		= 3;   		/* Két bites értékek száma*/	
	sT[0].sMOT[156].nIEC_NM			= 497;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[156].nNMNum			= 5;		/* Analóg mérések száma*/


/*  TMOK, 40-70  -----------------------------------------------------------*/	
sT[0].sTI[157].nType = TYP_TMOK;	

	sT[0].sMOT[157].nIEC_SP			= 2484;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[157].nIEC_DP			= 270;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[157].nIEC_NM			= 502;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 31-67  -----------------------------------------------------------*/	
sT[0].sTI[158].nType = TYP_TMOK;	

	sT[0].sMOT[158].nIEC_SP			= 2709;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[158].nIEC_DP			= 271;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[158].nIEC_NM			= 505;		/* Mérések IEC kezdõcíme */		

/* Balatonalmadi, gazmotor  ----------------------------------------------------------------*/
sT[0].sTI[159].nType = TYP_MOT;

	/*sT[0].sMOT[159].nTableNumPar		= 2;	 Egesz paraméterek tábla sorszáma */
	sT[0].sMOT[159].nIEC_SP				= 3695;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[159].nIEC_SP_NUM			= 12;		/* Egybites értékek száma*/
	sT[0].sMOT[159].nIEC_DP				= 397;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[159].nIEC_DP_NUM			= 7;   		/* Két bites értékek száma*/
	sT[0].sMOT[159].nIEC_NM				= 681;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[159].nNMNum				= 7;		/* Analóg mérések száma*/

/*  TMOK, 90-05  -----------------------------------------------------------*/	
sT[0].sTI[160].nType = TYP_TMOK;	

	sT[0].sMOT[160].nIEC_SP			= 2750;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[160].nIEC_DP			= 273;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[160].nIEC_NM			= 511;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 37-21  -----------------------------------------------------------*/	
sT[0].sTI[161].nType = TYP_TMOK;	

	sT[0].sMOT[161].nIEC_SP			= 2766;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[161].nIEC_DP			= 274;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[161].nIEC_NM			= 514;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 37-33  -----------------------------------------------------------*/	
sT[0].sTI[162].nType = TYP_TMOK;	

	sT[0].sMOT[162].nIEC_SP			= 2782;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[162].nIEC_DP			= 275;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[162].nIEC_NM			= 517;		/* Mérések IEC kezdõcíme */		

/*  Bicske átjátszó -----------------------------------------------------------*/	
sT[0].sTI[163].nType = TYP_MOT;	

	/*sT[0].sMOT[163].nTableNumPar	= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[163].nIEC_SP			= 2741;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[163].nIEC_SP_NUM		= 5;		/* Egybites értékek száma*/	

/*  Sümeg átjátszó -----------------------------------------------------------*/	
sT[0].sTI[164].nType = TYP_MOT;	

	/*sT[0].sMOT[164].nTableNumPar	= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[164].nIEC_SP			= 1990;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[164].nIEC_SP_NUM		= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[164].nIEC_DP_NUM			= 0;
	sT[0].sMOT[164].nNMNum      			= 0;

/*  TMOK, 90-32  -----------------------------------------------------------*/	
sT[0].sTI[165].nType = TYP_TMOK;	

	sT[0].sMOT[165].nIEC_SP			= 2798;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[165].nIEC_DP			= 276;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[165].nIEC_NM			= 520;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-40  -----------------------------------------------------------*/	
sT[0].sTI[166].nType = TYP_TMOK;	

	sT[0].sMOT[166].nIEC_SP			= 2814;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[166].nIEC_DP			= 277;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[166].nIEC_NM			= 523;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-10  -----------------------------------------------------------*/	
sT[0].sTI[167].nType = TYP_TMOK;	

	sT[0].sMOT[167].nIEC_SP			= 2830;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[167].nIEC_DP			= 278;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[167].nIEC_NM			= 526;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-11  -----------------------------------------------------------*/	
sT[0].sTI[168].nType = TYP_TMOK;	

	sT[0].sMOT[168].nIEC_SP			= 2846;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[168].nIEC_DP			= 279;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[168].nIEC_NM			= 529;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-18  -----------------------------------------------------------*/	
sT[0].sTI[169].nType = TYP_TMOK;	

	sT[0].sMOT[169].nIEC_SP			= 2862;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[169].nIEC_DP			= 280;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[169].nIEC_NM			= 532;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-23  -----------------------------------------------------------*/	
sT[0].sTI[170].nType = TYP_TMOK;	

	sT[0].sMOT[170].nIEC_SP			= 2878;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[170].nIEC_DP			= 281;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[170].nIEC_NM			= 535;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-55  -----------------------------------------------------------*/	
sT[0].sTI[171].nType = TYP_TMOK;	

	sT[0].sMOT[171].nIEC_SP			= 2894;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[171].nIEC_DP			= 282;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[171].nIEC_NM			= 538;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-63  -----------------------------------------------------------*/	
sT[0].sTI[172].nType = TYP_TMOK;	

	sT[0].sMOT[172].nIEC_SP			= 2910;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[172].nIEC_DP			= 283;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[172].nIEC_NM			= 541;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-79  -----------------------------------------------------------*/	
sT[0].sTI[173].nType = TYP_TMOK;	

	sT[0].sMOT[173].nIEC_SP			= 2926;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[173].nIEC_DP			= 284;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[173].nIEC_NM			= 544;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-86  -----------------------------------------------------------*/	
sT[0].sTI[174].nType = TYP_TMOK;	

	sT[0].sMOT[174].nIEC_SP			= 2942;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[174].nIEC_DP			= 285;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[174].nIEC_NM			= 547;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 11-48  -----------------------------------------------------------*/	
sT[0].sTI[175].nType = TYP_TMOK;	

	sT[0].sMOT[175].nIEC_SP			= 2958;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[175].nIEC_DP			= 286;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[175].nIEC_NM			= 550;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-28  -----------------------------------------------------------*/	
sT[0].sTI[176].nType = TYP_TMOK;	

	sT[0].sMOT[176].nIEC_SP			= 2974;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[176].nIEC_DP			= 287;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[176].nIEC_NM			= 553;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-33  -----------------------------------------------------------*/	
sT[0].sTI[177].nType = TYP_TMOK;	

	sT[0].sMOT[177].nIEC_SP			= 2990;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[177].nIEC_DP			= 288;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[177].nIEC_NM			= 556;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-34  -----------------------------------------------------------*/	
sT[0].sTI[178].nType = TYP_TMOK;	

	sT[0].sMOT[178].nIEC_SP			= 3006;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[178].nIEC_DP			= 289;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[178].nIEC_NM			= 559;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-35  -----------------------------------------------------------*/	
sT[0].sTI[179].nType = TYP_TMOK;	

	sT[0].sMOT[179].nIEC_SP			= 3022;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[179].nIEC_DP			= 290;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[179].nIEC_NM			= 562;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-40  -----------------------------------------------------------*/	
sT[0].sTI[180].nType = TYP_TMOK;	

	sT[0].sMOT[180].nIEC_SP			= 3038;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[180].nIEC_DP			= 291;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[180].nIEC_NM			= 565;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-43  -----------------------------------------------------------*/	
sT[0].sTI[181].nType = TYP_TMOK;	

	sT[0].sMOT[181].nIEC_SP			= 3054;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[181].nIEC_DP			= 292;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[181].nIEC_NM			= 568;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-62  -----------------------------------------------------------*/	
sT[0].sTI[182].nType = TYP_TMOK;	

	sT[0].sMOT[182].nIEC_SP			= 3070;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[182].nIEC_DP			= 293;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[182].nIEC_NM			= 571;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-71  -----------------------------------------------------------*/	
sT[0].sTI[183].nType = TYP_TMOK;	

	sT[0].sMOT[183].nIEC_SP			= 3086;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[183].nIEC_DP			= 294;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[183].nIEC_NM			= 574;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-72  -----------------------------------------------------------*/	
sT[0].sTI[184].nType = TYP_TMOK;	

	sT[0].sMOT[184].nIEC_SP			= 3102;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[184].nIEC_DP			= 295;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[184].nIEC_NM			= 577;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 87-90  -----------------------------------------------------------*/	
sT[0].sTI[185].nType = TYP_TMOK;	

	sT[0].sMOT[185].nIEC_SP			= 3118;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[185].nIEC_DP			= 296;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[185].nIEC_NM			= 580;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 86-88  -----------------------------------------------------------*/	
sT[0].sTI[186].nType = TYP_TMOK;	

	sT[0].sMOT[186].nIEC_SP			= 3134;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[186].nIEC_DP			= 297;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[186].nIEC_NM			= 583;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 86-95  -----------------------------------------------------------*/	
sT[0].sTI[187].nType = TYP_TMOK;	

	sT[0].sMOT[187].nIEC_SP			= 3150;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[187].nIEC_DP			= 298;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[187].nIEC_NM			= 586;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 62-23  -----------------------------------------------------------*/	
sT[0].sTI[188].nType = TYP_TMOK;	

	sT[0].sMOT[188].nIEC_SP			= 3166;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[188].nIEC_DP			= 299;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[188].nIEC_NM			= 589;		/* Mérések IEC kezdõcíme */		

/* Esztergom, elmenyfurdo  ----------------------------------------------------------------*/
sT[0].sTI[189].nType = TYP_MOT;

	/*sT[0].sMOT[189].nTableNumPar		= 2;	 Egesz paraméterek tábla sorszáma */
	sT[0].sMOT[189].nIEC_SP				= 4780;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[189].nIEC_SP_NUM			= 16;		/* Egybites értékek száma*/
	sT[0].sMOT[189].nIEC_DP				= 390;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[189].nIEC_DP_NUM			= 7;   		/* Két bites értékek száma*/
	sT[0].sMOT[189].nIEC_NM				= 688;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[189].nNMNum				= 7;		/* Analóg mérések száma*/

	
/* Nyergesújfalu, Etertech -------------------------------------------------------------*/
sT[0].sTI[190].nType = TYP_TAL;	

		sT[0].sTAL[190].nIEC_SP       		= 4721;
		sT[0].sTAL[190].nIEC_OsszevontHiba	= 4753;
		sT[0].sTAL[190].nIEC_MT_KommHiba	= 4754;
		sT[0].sTAL[190].nIEC_DP       		= 459;
		sT[0].sTAL[190].nIEC_DP_FSZ1  		= 463;
		sT[0].sTAL[190].nIEC_NM				= 872;
		sT[0].sTAL[190].nNMNum		  		= 13;
		sT[0].sTAL[190].nIEC_DP_2BIT1 		= 467;
		sT[0].sTAL[190].nIEC_DP_2BIT2 		= 468;
		sT[0].sTAL[190].nIEC_DP_2BIT_KINT1	= 912;
		sT[0].sTAL[190].nIEC_DP_2BIT_BENT1	= 913;
		sT[0].sTAL[190].nIEC_DP_2BIT_KINT2	= 920;
		sT[0].sTAL[190].nIEC_DP_2BIT_BENT2	= 925;
		sT[0].sTAL[190].nDP_EXTRA_OFFSET    = 469;
		sT[0].sTAL[190].nDP_EXTRA_NUM       = 5;

/*  TMOK, 90-82  -----------------------------------------------------------*/	
sT[0].sTI[191].nType = TYP_TMOK;	

	sT[0].sMOT[191].nIEC_SP			= 3182;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[191].nIEC_DP			= 300;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[191].nIEC_NM			= 592;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 21-66  -----------------------------------------------------------*/	
sT[0].sTI[192].nType = TYP_TMOK;	

	sT[0].sMOT[192].nIEC_SP			= 3230;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[192].nIEC_DP			= 303;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[192].nIEC_NM			= 601;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 21-81  -----------------------------------------------------------*/	
sT[0].sTI[193].nType = TYP_TMOK;	

	sT[0].sMOT[193].nIEC_SP			= 3246;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[193].nIEC_DP			= 304;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[193].nIEC_NM			= 604;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 21-84  -----------------------------------------------------------*/	
sT[0].sTI[194].nType = TYP_TMOK;	

	sT[0].sMOT[194].nIEC_SP			= 3262;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[194].nIEC_DP			= 305;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[194].nIEC_NM			= 607;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 90-90  -----------------------------------------------------------*/	
sT[0].sTI[195].nType = TYP_TMOK;	

	sT[0].sMOT[195].nIEC_SP			= 3198;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[195].nIEC_DP			= 301;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[195].nIEC_NM			= 595;		/* Mérések IEC kezdõcíme */		

/*  TMOK, 11-81  -----------------------------------------------------------*/	
sT[0].sTI[196].nType = TYP_TMOK;	

	sT[0].sMOT[196].nIEC_SP			= 3294;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[196].nIEC_DP			= 307;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[196].nIEC_NM			= 613;		/* Mérések IEC kezdõcíme */		

/* 10-01, 10-20 -----------------------------------------------------------*/

sT[0].sTI[197].nType = TYP_TMOK;

	sT[0].sMOT[197].nIEC_SP				= 3310;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[197].nIEC_SP_NUM			= 30;		/* Egybites értékek száma*/
	sT[0].sMOT[197].nIEC_DP				= 308;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[197].nIEC_DP_NUM			= 2;   		/* Két bites értékek száma*/
	sT[0].sMOT[197].nIEC_NM				= 616;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[197].nNMNum				= 4;		/* Analóg mérések száma*/

/*  TMOK, 40-62  -----------------------------------------------------------*/	
sT[0].sTI[198].nType = TYP_TMOK;	

	sT[0].sMOT[198].nIEC_SP			= 3344;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[198].nIEC_DP			= 310;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[198].nIEC_NM			= 620;		/* Mérések IEC kezdõcíme */		


/* Fertoszentmiklos, kabelkori kapcsolo  ----------------------------------------------------------------*/
sT[0].sTI[199].nType = TYP_MOT;

	/*sT[0].sMOT[199].nTableNumPar		= 2;	 Egesz paraméterek tábla sorszáma */
	sT[0].sMOT[199].nIEC_SP				= 3360;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[199].nIEC_SP_NUM			= 14;		/* Egybites értékek száma*/
	sT[0].sMOT[199].nIEC_DP				= 312;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[199].nIEC_DP_NUM			= 10;   		/* Két bites értékek száma*/
	sT[0].sMOT[199].nIEC_NM				= 623;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[199].nNMNum				= 2;		/* Analóg mérések száma*/

/* 71-44 -----------------------------------------------------------*/
sT[0].sTI[200].nType = TYP_TMOK;

	sT[0].sMOT[200].nIEC_SP				= 3376;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[200].nIEC_DP				= 322;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[200].nIEC_NM				= 892;		/* Mérések IEC kezdõcíme */

/*  TMOK, 13-85  -----------------------------------------------------------*/	
sT[0].sTI[201].nType = TYP_TMOK;	

	sT[0].sMOT[201].nIEC_SP			= 3410;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[201].nIEC_DP			= 324;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[201].nIEC_NM			= 948;		/* Mérések IEC kezdõcíme */		
	sT[0].sMOT[201].nNMNum     		= 4;		/* Mérések száma */


/* 21-21, 21-22 -----------------------------------------------------------*/
sT[0].sTI[202].nType = TYP_TMOK;

	sT[0].sMOT[202].nIEC_SP				= 3426;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[202].nIEC_SP_NUM			= 30;		/* Egybites értékek száma*/
	sT[0].sMOT[202].nIEC_DP				= 325;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[202].nIEC_DP_NUM			= 2;   		/* Két bites értékek száma*/
	sT[0].sMOT[202].nIEC_NM				= 632;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[202].nNMNum				= 4;		/* Analóg mérések száma*/

/* Sopron, Ipari Park -------------------------------------------------------------*/
sT[0].sTI[203].nType = TYP_TAL;	

		/*sT[0].sTAL[203].nTableNumPar		= 2;*/
		sT[0].sTAL[203].nIEC_SP       		= 3460;
		/*sT[0].sTAL[203].nIEC_ElsoZarlatCim	= 3460;*/
		sT[0].sTAL[203].nIEC_OsszevontHiba	= 3492;
		sT[0].sTAL[203].nIEC_MT_KommHiba	= 3493;
		sT[0].sTAL[203].nIEC_DP       		= 327;
		sT[0].sTAL[203].nIEC_DP_FSZ1  		= 331;
		sT[0].sTAL[203].nIEC_NM				= 636;
		sT[0].sTAL[203].nNMNum		  		= 9;
		sT[0].sTAL[203].nIEC_DP_2BIT1 		= 335;
		sT[0].sTAL[203].nIEC_DP_2BIT_KINT1	= 912;
		sT[0].sTAL[203].nIEC_DP_2BIT_BENT1	= 913;


/* Veszprem, Balaton Plaza TALUS -------------------------------------------------------------*/
sT[0].sTI[204].nType = TYP_TAL;	

		/*sT[0].sTAL[204].nTableNumPar		= 2;*/
		sT[0].sTAL[204].nIEC_SP       		= 3499;
		/*sT[0].sTAL[204].nIEC_ElsoZarlatCim	= 3499;*/
		sT[0].sTAL[204].nIEC_OsszevontHiba	= 3531;
		sT[0].sTAL[204].nIEC_MT_KommHiba	= 3532;
		sT[0].sTAL[204].nIEC_DP       		= 336;
		sT[0].sTAL[204].nIEC_DP_FSZ1  		= 340;
		sT[0].sTAL[204].nIEC_NM				= 645;
		sT[0].sTAL[204].nNMNum		  		= 4;

/* Sopron, szemettelep TALUS -------------------------------------------------------------*/
sT[0].sTI[205].nType = TYP_TAL;	

		/*sT[0].sTAL[205].nTableNumPar		= 2;*/
		sT[0].sTAL[205].nIEC_SP       		= 3536;
		/*sT[0].sTAL[205].nIEC_ElsoZarlatCim	= 3536;*/
		sT[0].sTAL[205].nIEC_OsszevontHiba	= 3568;
		sT[0].sTAL[205].nIEC_MT_KommHiba	= 3569;
		sT[0].sTAL[205].nIEC_DP       		= 344;
		sT[0].sTAL[205].nIEC_DP_FSZ1  		= 348;
		sT[0].sTAL[205].nIEC_NM				= 649;
		sT[0].sTAL[205].nNMNum		  		= 9;
		
/* Veszprem, Csolnoky kórház TALUS -------------------------------------------------------------*/
sT[0].sTI[206].nType = TYP_TAL;	

		/*sT[0].sTAL[206].nTableNumPar		= 2;*/
		sT[0].sTAL[206].nIEC_SP       		= 3573;
		/*sT[0].sTAL[206].nIEC_ElsoZarlatCim	= 3573;*/
		sT[0].sTAL[206].nIEC_OsszevontHiba	= 3605;
		sT[0].sTAL[206].nIEC_MT_KommHiba	= 3606;
		sT[0].sTAL[206].nIEC_DP       		= 352;
		sT[0].sTAL[206].nIEC_DP_FSZ1  		= 356;
		sT[0].sTAL[206].nIEC_NM				= 658;
		sT[0].sTAL[206].nNMNum		  		= 9;
		
/* Taploca, TESCO -------------------------------------------------------------*/
sT[0].sTI[207].nType = TYP_TAL;	

		/*sT[0].sTAL[207].nTableNumPar		= 2;*/
		sT[0].sTAL[207].nIEC_SP       		= 3610;
		/*sT[0].sTAL[207].nIEC_ElsoZarlatCim	= 3573;*/
		sT[0].sTAL[207].nIEC_OsszevontHiba	= 3642;
		sT[0].sTAL[207].nIEC_MT_KommHiba	= 3643;
		sT[0].sTAL[207].nIEC_DP       		= 360;
		sT[0].sTAL[207].nIEC_DP_FSZ1  		= 364;
		sT[0].sTAL[207].nIEC_NM				= 667;
		sT[0].sTAL[207].nNMNum		  		= 4;
		sT[0].sTAL[207].nIEC_DP_2BIT1 		= 368;
		sT[0].sTAL[207].nIEC_DP_2BIT_KINT1	= 913;
		sT[0].sTAL[207].nIEC_DP_2BIT_BENT1	= 912;

/* Kekkut, kabelkori kapcsolo  ----------------------------------------------------------------*/
sT[0].sTI[208].nType = TYP_MOT;

	/*sT[0].sMOT[208].nTableNumPar		= 2;	 Egesz paraméterek tábla sorszáma */
	sT[0].sMOT[208].nIEC_SP				= 3647;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[208].nIEC_SP_NUM			= 16;		/* Egybites értékek száma*/
	sT[0].sMOT[208].nIEC_DP				= 369;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[208].nIEC_DP_NUM			= 8;   		/* Két bites értékek száma*/
	sT[0].sMOT[208].nIEC_NM				= 623;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[208].nNMNum				= 0;		/* Analóg mérések száma*/

/*  TMOK, 11-10  -----------------------------------------------------------*/	
sT[0].sTI[209].nType = TYP_TMOK;	

	sT[0].sMOT[209].nIEC_SP			= 3665;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[209].nIEC_DP			= 377;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[209].nIEC_NM			= 671;		/* Mérések IEC kezdõcíme */	
	
/* 21-15, 21-73 NPS-RTU-NPS TMOK ----------------------------------------------------*/
sT[0].sTI[210].nType = TYP_TMOK;

	sT[0].sMOT[210].nIEC_SP				= 3723;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[210].nIEC_SP_NUM			= 30;		/* Egybites értékek száma*/
	sT[0].sMOT[210].nIEC_DP				= 404;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[210].nIEC_DP_NUM			= 2;   		/* Két bites értékek száma*/
	sT[0].sMOT[210].nIEC_NM				= 695;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[210].nNMNum				= 4;		/* Analóg mérések száma*/

/*  TMOK, 10-74  -----------------------------------------------------------*/	
sT[0].sTI[211].nType = TYP_TMOK;	

	sT[0].sMOT[211].nIEC_SP			= 3757;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[211].nIEC_DP			= 272;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[211].nIEC_NM			= 699;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 11-22  -----------------------------------------------------------*/	
sT[0].sTI[212].nType = TYP_TMOK;	

	sT[0].sMOT[212].nIEC_SP			= 3773;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[212].nIEC_DP			= 384;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[212].nIEC_NM			= 702;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 11-35  -----------------------------------------------------------*/	
sT[0].sTI[213].nType = TYP_TMOK;	

	sT[0].sMOT[213].nIEC_SP			= 3789;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[213].nIEC_DP			= 385;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[213].nIEC_NM			= 705;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 10-19  -----------------------------------------------------------*/	
sT[0].sTI[214].nType = TYP_TMOK;	

	sT[0].sMOT[214].nIEC_SP			= 3805;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[214].nIEC_DP			= 386;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[214].nIEC_NM			= 708;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 11-80  -----------------------------------------------------------*/	
sT[0].sTI[215].nType = TYP_TMOK;	

	sT[0].sMOT[215].nIEC_SP			= 3821;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[215].nIEC_DP			= 387;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[215].nIEC_NM			= 711;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 11-99  -----------------------------------------------------------*/	
sT[0].sTI[216].nType = TYP_TMOK;	

	sT[0].sMOT[216].nIEC_SP			= 3837;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[216].nIEC_DP			= 388;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[216].nIEC_NM			= 714;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 52-50  -----------------------------------------------------------*/	
sT[0].sTI[217].nType = TYP_TMOK;	

	sT[0].sMOT[217].nIEC_SP			= 3853;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[217].nIEC_DP			= 389;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[217].nIEC_NM			= 717;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 54-02  -----------------------------------------------------------*/	
sT[0].sTI[218].nType = TYP_TMOK;	

	sT[0].sMOT[218].nIEC_SP			= 3869;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[218].nIEC_DP			= 406;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[218].nIEC_NM			= 720;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 51-12  -----------------------------------------------------------*/	
sT[0].sTI[219].nType = TYP_TMOK;	

	sT[0].sMOT[219].nIEC_SP			= 3885;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[219].nIEC_DP			= 407;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[219].nIEC_NM			= 723;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 50-49  -----------------------------------------------------------*/	
sT[0].sTI[220].nType = TYP_TMOK;	

	sT[0].sMOT[220].nIEC_SP			= 3901;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[220].nIEC_DP			= 408;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[220].nIEC_NM			= 726;		/* Mérések IEC kezdõcíme */	

/* 51-39, 51-41 -----------------------------------------------------------*/
sT[0].sTI[221].nType = TYP_TMOK;

	sT[0].sMOT[221].nIEC_SP				= 4061;		/* Egybites értékek IEC kezdõcíme*/
	/*sT[0].sMOT[221].nIEC_SP_NUM			= 14; */		/* Egybites értékek száma*/
	sT[0].sMOT[221].nIEC_DP				= 409;		/* Kétbites értékek IEC kezdõcíme*/
	/*sT[0].sMOT[221].nIEC_DP_NUM			= 2; */  		/* Két bites értékek száma*/
	sT[0].sMOT[221].nIEC_NM				= 756;		/* Mérések IEC kezdõcíme */
	/*sT[0].sMOT[221].nNMNum				= 4;	*/	/* Analóg mérések száma*/

/* 51-40 -----------------------------------------------------------*/
sT[0].sTI[222].nType = TYP_TMOK;

	sT[0].sMOT[222].nIEC_SP				= 4095;		/* Egybites értékek IEC kezdõcíme*/
	/*sT[0].sMOT[222].nIEC_SP_NUM			= 30;*/		/* Egybites értékek száma*/
	sT[0].sMOT[222].nIEC_DP				= 411;		/* Kétbites értékek IEC kezdõcíme*/
	/*sT[0].sMOT[222].nIEC_DP_NUM			= 2;*6   		/* Két bites értékek száma*/
	sT[0].sMOT[222].nIEC_NM				= 760;		/* Mérések IEC kezdõcíme */
	/*sT[0].sMOT[222].nNMNum				= 4;*/		/* Analóg mérések száma*/

/*  TMOK, 61-15  -----------------------------------------------------------*/	
sT[0].sTI[223].nType = TYP_TMOK;	

	sT[0].sMOT[223].nIEC_SP			= 3981;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[223].nIEC_DP			= 413;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[223].nIEC_NM			= 741;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 64-84  -----------------------------------------------------------*/	
sT[0].sTI[224].nType = TYP_TMOK;	

	sT[0].sMOT[224].nIEC_SP			= 3997;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[224].nIEC_DP			= 414;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[224].nIEC_NM			= 744;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 74-24  -----------------------------------------------------------*/	
sT[0].sTI[225].nType = TYP_TMOK;	

	sT[0].sMOT[225].nIEC_SP			= 4013;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[225].nIEC_DP			= 415;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[225].nIEC_NM			= 904;		/* Mérések IEC kezdõcíme */	
	sT[0].sMOT[225].nNMNum     		= 4;		/* Mérések száma */


/*  TMOK, 51-74  -----------------------------------------------------------*/	
sT[0].sTI[226].nType = TYP_TMOK;	

	sT[0].sMOT[226].nIEC_SP			= 4029;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[226].nIEC_DP			= 416;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[226].nIEC_NM			= 750;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 37-29  -----------------------------------------------------------*/	
sT[0].sTI[227].nType = TYP_TMOK;	

	sT[0].sMOT[227].nIEC_SP			= 4045;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[227].nIEC_DP			= 417;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[227].nIEC_NM			= 753;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 73-06  -----------------------------------------------------------*/	
sT[0].sTI[228].nType = TYP_TMOK;	

	sT[0].sMOT[228].nIEC_SP			= 1766;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[228].nIEC_DP			= 418;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[228].nIEC_NM			= 508;		/* Mérések IEC kezdõcíme */	

/* Dorog DAC -----------------------------------------------------------*/	
sT[0].sTI[229].nType = TYP_MOT;	

	/*sT[0].sMOT[229].nTableNumPar			= 2;		 Egesz paraméterek tábla sorszáma */	
	sT[0].sMOT[229].nIEC_SP				= 990;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[229].nIEC_SP_NUM			= 5;		/* Egybites értékek száma*/	
	sT[0].sMOT[229].nIEC_DP_NUM			= 0;
	sT[0].sMOT[229].nNMNum      		= 0;
	sT[0].sMOT[229].nIEC_DP			= 0;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[229].nIEC_NM			= 0;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 51-01  -----------------------------------------------------------*/	
sT[0].sTI[230].nType = TYP_TMOK;	

	sT[0].sMOT[230].nIEC_SP			= 3917;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[230].nIEC_DP			= 419;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[230].nIEC_NM			= 729;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 11-66  -----------------------------------------------------------*/	
sT[0].sTI[231].nType = TYP_TMOK;	

	sT[0].sMOT[231].nIEC_SP			= 3933;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[231].nIEC_DP			= 420;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[231].nIEC_NM			= 732;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 70-60  -----------------------------------------------------------*/	
sT[0].sTI[232].nType = TYP_TMOK;	

	sT[0].sMOT[232].nIEC_SP			= 3949;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[232].nIEC_DP			= 421;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[232].nIEC_NM			= 735;		/* Mérések IEC kezdõcíme */	


/*  TMOK, 10-24  -----------------------------------------------------------*/	
sT[0].sTI[233].nType = TYP_TMOK;	

	sT[0].sMOT[233].nIEC_SP			= 4129;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[233].nIEC_DP			= 422;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[233].nIEC_NM			= 738;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 11-28  -----------------------------------------------------------*/	
sT[0].sTI[234].nType = TYP_TMOK;	

	sT[0].sMOT[234].nIEC_SP			= 4145;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[234].nIEC_DP			= 423;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[234].nIEC_NM			= 764;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 50-96  -----------------------------------------------------------*/	
sT[0].sTI[235].nType = TYP_TMOK;	

	sT[0].sMOT[235].nIEC_SP			= 4161;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[235].nIEC_DP			= 424;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[235].nIEC_NM			= 767;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 51-53  -----------------------------------------------------------*/	
sT[0].sTI[236].nType = TYP_TMOK;	

	sT[0].sMOT[236].nIEC_SP			= 4177;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[236].nIEC_DP			= 425;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[236].nIEC_NM			= 770;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 51-53  -----------------------------------------------------------*/	
sT[0].sTI[237].nType = TYP_TMOK;	

	sT[0].sMOT[237].nIEC_SP			= 4193;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[237].nIEC_DP			= 426;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[237].nIEC_NM			= 773;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 37-03  -----------------------------------------------------------*/	
sT[0].sTI[238].nType = TYP_TMOK;	

	sT[0].sMOT[238].nIEC_SP			= 4209;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[238].nIEC_DP			= 427;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[238].nIEC_NM			= 776;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 60-08  -----------------------------------------------------------*/	
sT[0].sTI[239].nType = TYP_TMOK;	

	sT[0].sMOT[239].nIEC_SP			= 4225;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[239].nIEC_DP			= 428;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[239].nIEC_NM			= 779;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 15-55  -----------------------------------------------------------*/	
sT[0].sTI[240].nType = TYP_TMOK;	

	sT[0].sMOT[240].nIEC_SP			= 4241;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[240].nIEC_DP			= 429;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[240].nIEC_NM			= 782;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 51-13  -----------------------------------------------------------*/	
sT[0].sTI[241].nType = TYP_TMOK;	

	sT[0].sMOT[241].nIEC_SP			= 4257;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[241].nIEC_DP			= 430;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[241].nIEC_NM			= 785;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 60-71  -----------------------------------------------------------*/	
sT[0].sTI[242].nType = TYP_TMOK;	

	sT[0].sMOT[242].nIEC_SP			= 4273;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[242].nIEC_DP			= 431;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[242].nIEC_NM			= 788;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 34-04  -----------------------------------------------------------*/	
sT[0].sTI[243].nType = TYP_TMOK;	

	sT[0].sMOT[243].nIEC_SP			= 4289;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[243].nIEC_DP			= 432;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[243].nIEC_NM			= 791;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 60-90  -----------------------------------------------------------*/	
sT[0].sTI[244].nType = TYP_TMOK;	

	sT[0].sMOT[244].nIEC_SP			= 4305;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[244].nIEC_DP			= 433;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[244].nIEC_NM			= 794;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 61-59  -----------------------------------------------------------*/	
sT[0].sTI[245].nType = TYP_TMOK;	

	sT[0].sMOT[245].nIEC_SP			= 4321;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[245].nIEC_DP			= 434;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[245].nIEC_NM			= 797;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 20-14  -----------------------------------------------------------*/	
sT[0].sTI[246].nType = TYP_TMOK;	

	sT[0].sMOT[246].nIEC_SP			= 4337;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[246].nIEC_DP			= 435;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[246].nIEC_NM			= 800;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 51-09  -----------------------------------------------------------*/	
sT[0].sTI[247].nType = TYP_TMOK;	

	sT[0].sMOT[247].nIEC_SP			= 4353;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[247].nIEC_DP			= 436;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[247].nIEC_NM			= 803;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 52-60  -----------------------------------------------------------*/	
sT[0].sTI[248].nType = TYP_TMOK;	

	sT[0].sMOT[248].nIEC_SP			= 4369;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[248].nIEC_DP			= 437;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[248].nIEC_NM			= 806;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 71-16  -----------------------------------------------------------*/	
sT[0].sTI[249].nType = TYP_TMOK;	

	sT[0].sMOT[249].nIEC_SP			= 4417;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[249].nIEC_DP			= 440;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[249].nIEC_NM			= 815;		/* Mérések IEC kezdõcíme */	


/*  TMOK, 61-40  -----------------------------------------------------------*/	
sT[0].sTI[250].nType = TYP_TMOK;	

	sT[0].sMOT[250].nIEC_SP			= 4385;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[250].nIEC_DP			= 438;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[250].nIEC_NM			= 809;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 65-07  -----------------------------------------------------------*/	
sT[0].sTI[251].nType = TYP_TMOK;	

	sT[0].sMOT[251].nIEC_SP			= 4401;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[251].nIEC_DP			= 439;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[251].nIEC_NM			= 812;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 80-87  -----------------------------------------------------------*/	
sT[0].sTI[252].nType = TYP_TMOK;	

	sT[0].sMOT[252].nIEC_SP			= 4433;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[252].nIEC_DP			= 441;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[252].nIEC_NM			= 818;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 87-66  -----------------------------------------------------------*/	
sT[0].sTI[253].nType = TYP_TMOK;	

	sT[0].sMOT[253].nIEC_SP			= 4449;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[253].nIEC_DP			= 442;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[253].nIEC_NM			= 821;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 50-68  -----------------------------------------------------------*/	
sT[0].sTI[254].nType = TYP_TMOK;	

	sT[0].sMOT[254].nIEC_SP			= 4465;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[254].nIEC_DP			= 443;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[254].nIEC_NM			= 824;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 51-78  -----------------------------------------------------------*/	
sT[0].sTI[255].nType = TYP_TMOK;	

	sT[0].sMOT[255].nIEC_SP			= 4481;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[255].nIEC_DP			= 444;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[255].nIEC_NM			= 827;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 52-70  -----------------------------------------------------------*/	
sT[0].sTI[256].nType = TYP_TMOK;	

	sT[0].sMOT[256].nIEC_SP			= 4497;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[256].nIEC_DP			= 445;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[256].nIEC_NM			= 830;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 54-19  -----------------------------------------------------------*/	
sT[0].sTI[257].nType = TYP_TMOK;	

	sT[0].sMOT[257].nIEC_SP			= 4513;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[257].nIEC_DP			= 446;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[257].nIEC_NM			= 833;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 64-89  -----------------------------------------------------------*/	
sT[0].sTI[258].nType = TYP_TMOK;	

	sT[0].sMOT[258].nIEC_SP			= 4529;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[258].nIEC_DP			= 447;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[258].nIEC_NM			= 836;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 65-25  -----------------------------------------------------------*/	
sT[0].sTI[259].nType = TYP_TMOK;	

	sT[0].sMOT[259].nIEC_SP			= 4545;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[259].nIEC_DP			= 448;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[259].nIEC_NM			= 839;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 71-61  -----------------------------------------------------------*/	
sT[0].sTI[260].nType = TYP_TMOK;	

	sT[0].sMOT[260].nIEC_SP			= 4561;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[260].nIEC_DP			= 449;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[260].nIEC_NM			= 842;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 72-89  -----------------------------------------------------------*/	
sT[0].sTI[261].nType = TYP_TMOK;	

	sT[0].sMOT[261].nIEC_SP			= 4577;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[261].nIEC_DP			= 450;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[261].nIEC_NM			= 845;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 90-83  -----------------------------------------------------------*/	
sT[0].sTI[262].nType = TYP_TMOK;	

	sT[0].sMOT[262].nIEC_SP			= 4593;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[262].nIEC_DP			= 451;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[262].nIEC_NM			= 848;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 50-86  -----------------------------------------------------------*/	
sT[0].sTI[263].nType = TYP_TMOK;	

	sT[0].sMOT[263].nIEC_SP			= 4609;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[263].nIEC_DP			= 452;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[263].nIEC_NM			= 851;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 62-29  -----------------------------------------------------------*/	
sT[0].sTI[264].nType = TYP_TMOK;	

	sT[0].sMOT[264].nIEC_SP			= 4625;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[264].nIEC_DP			= 453;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[264].nIEC_NM			= 854;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 20-02  -----------------------------------------------------------*/	
sT[0].sTI[265].nType = TYP_TMOK;	

	sT[0].sMOT[265].nIEC_SP			= 4641;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[265].nIEC_DP			= 454;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[265].nIEC_NM			= 857;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 21-05  -----------------------------------------------------------*/	
sT[0].sTI[266].nType = TYP_TMOK;	

	sT[0].sMOT[266].nIEC_SP			= 4657;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[266].nIEC_DP			= 455;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[266].nIEC_NM			= 860;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 72-90  -----------------------------------------------------------*/	
sT[0].sTI[267].nType = TYP_TMOK;	

	sT[0].sMOT[267].nIEC_SP			= 4673;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[267].nIEC_DP			= 456;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[267].nIEC_NM			= 863;		/* Mérések IEC kezdõcíme */	

/*  TMOK, 21-07  -----------------------------------------------------------*/	
sT[0].sTI[268].nType = TYP_TMOK;	

	sT[0].sMOT[268].nIEC_SP			= 4689;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[268].nIEC_DP			= 457;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[268].nIEC_NM			= 964;		/* Mérések IEC kezdõcíme */	

	sT[0].sMOT[268].nNMNum     		= 4;		/* Mérések száma */

/*  TMOK, 37-199  -----------------------------------------------------------*/	
sT[0].sTI[269].nType = TYP_TMOK;	

	sT[0].sMOT[269].nIEC_SP			= 4705;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[269].nIEC_DP			= 458;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[269].nIEC_NM			= 869;		/* Mérések IEC kezdõcíme */	

/* 71-43 -----------------------------------------------------------*/
sT[0].sTI[270].nType = TYP_TMOK;

	sT[0].sMOT[270].nIEC_SP				= 3392;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[270].nIEC_DP				= 323;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[270].nIEC_NM				= 895;		/* Mérések IEC kezdõcíme */


/* Balatonfured, Anna Grand Hotel  ----------------------------------------------------------------*/
sT[0].sTI[271].nType = TYP_MOT;

	sT[0].sMOT[271].nIEC_SP				= 4758;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[271].nIEC_SP_NUM			= 16;		/* Egybites értékek száma*/
	sT[0].sMOT[271].nIEC_SP_FLAG		= 4774;		/* Egybites FLAG értékek IEC kezdõcíme*/
	sT[0].sMOT[271].nIEC_SP_FLAG_NUM	= 4;		/* Egybites FLAG értékek száma*/	
	sT[0].sMOT[271].nIEC_DP				= 474;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[271].nIEC_DP_NUM			= 8;   		/* Két bites értékek száma*/
	sT[0].sMOT[271].nIEC_NM				= 885;		/* Mérések IEC kezdõcíme */
	sT[0].sMOT[271].nNMNum				= 7;		/* Analóg mérések száma*/

/* 51-42 -----------------------------------------------------------*/
sT[0].sTI[272].nType = TYP_TMOK;

	sT[0].sMOT[272].nIEC_SP				= 4113;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[272].nIEC_DP				= 412;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[272].nIEC_NM				= 898;		/* Mérések IEC kezdõcíme */

/* 51-41 -----------------------------------------------------------*/
sT[0].sTI[273].nType = TYP_TMOK;

	sT[0].sMOT[273].nIEC_SP				= 4079;		/* Egybites értékek IEC kezdõcíme*/
	sT[0].sMOT[273].nIEC_DP				= 410;		/* Kétbites értékek IEC kezdõcíme*/
	sT[0].sMOT[273].nIEC_NM				= 901;		/* Mérések IEC kezdõcíme */


} /* end fnSetDataPar()*/

