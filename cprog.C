/**+**************************************************************************
* NAME           :  command.c                                                *
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
v2.0     2014.04.16 Gergely Zsolt	Vételi számláló nullázása nap végén
*****************************************************************************/

#include "CAPPLIC.H"
#include <stdio.h>
/* Parameterek strukturaja */
#include "strPar.H"

#define  BYTE					unsigned char
#define  RSlink1  				51
#define  AllLinks 				0
#define  SetCall  				0
#define  VALID  				1
#define  LEKERDEZES_TIMEOUT		100
#define  COMMAND_LENGTH			6


/*--------------------------------------------------------------------------*/
/* Prototypes and defines                                                   */
/*--------------------------------------------------------------------------*/
void fnReadPar(void);
void fnSetStatus(int nI, int nValue);
extern void fnSetStatSiteTable(void);
extern void fnSetComPar(void);
extern void fnSetDataPar(void);
extern void fnWriteSPData(int nIEC_Offset, int nData, int nMS1, int nMS2, int nMin, int nCTAct);
extern int  fnReadSPData(int nIEC_Offset);
extern void fnDPTblIndx(int nIECOffset, int *nDPTblIndx, int *nIndx);
extern void fnWriteSPStatus(int nIEC_Offset, int nData);
extern void fnWriteDPStatus(int nIEC_Offset, int nData);
extern void fnWriteNMStatus(int nIEC_Offset, int nData);
void MOT_DATA(STATION_DESC_MOT	*pMOT, unsigned char *buf);
void MOT_DATA2(STATION_DESC_MOT	*pMOT, unsigned char *buf);
void TALUS_EVENT(STATION_DESC_TALUS *pTAL, unsigned char *rx_buf);
void TALUS_DAT(STATION_DESC_TALUS *pTAL, unsigned char *rx_buf);
void TMOK_DATA(STATION_DESC_MOT	*pMOT, unsigned char *buf);
void TMOK_DATA2(STATION_DESC_MOT	*pMOT, unsigned char *rx_buf);
void tx_command(void);
void rx(void);
void com_check(void);
extern void fnWriteNM( int nIECOffset,unsigned int nData);
extern void fnDCTblIndx(int nIECOffset, int *nDCTblIndx, int *nOffset, short **p_col_DCAct);
extern void fnSCTblIndx(int nIECOffset, int *nSCTblIndx, int *nOffset, short **p_col_SCAct);


extern void com_check();
extern void rx();
extern void tx_command();
extern void fnLekR(void);
void G1_DAT(unsigned char *rx_buf);
int value_BX(int );
int value_CErrX(int nI);
int value_CComX(int nI);
int value_CRcvdX(int nI);
int value_CLekX(int nI);
void setvalue_LiX(int, int );
void setvalue_CErrX(int nI, int nValue);
void setvalue_CStatusX(int nI, int nValue);
void setvalue_CComX(int nI, int nValue);
void setvalue_CRcvdX(int nI, int nValue);
void setvalue_CLekX(int nI, int nValue);
extern void fnSetDinamicSiteTable(void);

extern void setdat2(unsigned char *input);
extern void setdat(unsigned char *input);

/* 2017.09*/
extern void fnWriteDPData(int nIEC_Offset, int nData, int nMS1, int nMS2, int nMin, int nCTAct);
extern int fnReadDPData(int nIEC_Offset, int nMS1, int nMS2, int nMin, int nCTAct);


/**********************************************/
/* Globals                                     */
/**********************************************/

unsigned short	nTableNum1 = 1;
unsigned short	nTableNum2 = 2;


/*CB_TABLE_INFO   table_DC2;*/
short          *p_col_DC2;

CB_TABLE_INFO   table_CStat1;
short          *p_col_CRcvd1;
short          *p_col_Status1;
short          *p_col_CLek1;
short          *p_col_CCom1;
short          *p_col_CErr1;

CB_TABLE_INFO   table_CStat2;
short          *p_col_CRcvd2;
short          *p_col_Status2;
short          *p_col_CLek2;
short          *p_col_CCom2;
short          *p_col_CErr2;


/*CB_TABLE_INFO   table_SC2;*/
short          *p_col_SC2;

CB_TABLE_INFO   table_Controls;
short          *p_col_Controls;

CB_TABLE_INFO   table_CBuf;
CB_TABLE_INFO   table_parBool;
CB_TABLE_INFO   table_parInt;
CB_TABLE_INFO   table_RxMon;
CB_TABLE_INFO   table_Stat;
/*CB_TABLE_INFO   table_SP;
CB_TABLE_INFO   table_SP1;
CB_TABLE_INFO   table_SP2;
CB_TABLE_INFO   table_SP3;
CB_TABLE_INFO   table_SP4;
CB_TABLE_INFO   table_SP5;

CB_TABLE_INFO   table_NM;
CB_TABLE_INFO   table_DC;*/
CB_TABLE_INFO   table_EVT;
CB_TABLE_INFO   table_SC;
CB_TABLE_INFO	table_ComBuf;
CB_TABLE_INFO	table_Timers;

CB_TABLE_INFO   table_DP;

/* MOSCAD tablak oszlopai */
short          *p_col_parBool;	
short          *p_col_parInt;
short          *p_col_RxMon;
short          *p_col_TxMon;
short          *p_col_Stat;

short          *p_col_SP1;
short          *p_col_SP1_MS1;
short          *p_col_SP1_MS2;
short          *p_col_SP1_MIN;
short          *p_col_SP1_CT;
short          *p_col_SP1_XOR;
short          *p_col_SP2;
short          *p_col_SP2_MS1;
short          *p_col_SP2_MS2;
short          *p_col_SP2_MIN;
short          *p_col_SP2_CT;
short          *p_col_SP2_XOR;
short          *p_col_SP3;
short          *p_col_SP3_MS1;
short          *p_col_SP3_MS2;
short          *p_col_SP3_MIN;
short          *p_col_SP3_CT;
short          *p_col_SP3_XOR;
short          *p_col_SP4;
short          *p_col_SP4_MS1;
short          *p_col_SP4_MS2;
short          *p_col_SP4_MIN;
short          *p_col_SP4_CT;
short          *p_col_SP4_XOR;
short          *p_col_SP5;
short          *p_col_SP5_MS1;
short          *p_col_SP5_MS2;
short          *p_col_SP5_MIN;
short          *p_col_SP5_CT;
short          *p_col_SP5_XOR;

short          *p_col_DPL;
short          *p_col_DPH;
short          *p_col_DP_MS1;
short          *p_col_DP_MS2;
short          *p_col_DP_MIN;
short          *p_col_DP_CT;
short          *p_col_NM;
short          *p_col_NM_LZ;
short          *p_col_NM_Tx;
short          *p_col_DC;
short          *p_col_EVT;
short          *p_col_SC;
unsigned short          *p_col_RxBuf;

short          *p_col_T1;
short          *p_col_T2;
short          *p_col_Li1;
short          *p_col_Li2;
short          *p_col_B1;
short          *p_col_B2;


int					nRxMonTblIndx;
int					nUPort;
int					nStatTblIndx;
int					nLinkTimeOut;
int					nMaxRptNum;
int					nLenCAOA;
int					nLenIOA;
int					nCAOA;
int					nSPTblIndx;
int					nSPTblIndx1;
int					nSPTblIndx2;
int					nSPTblIndx3;
int					nSPTblIndx4;
int					nSPTblIndx5;
int					nSPNum;
unsigned long		lSPStart;				
unsigned long		lSP2Start;				
unsigned long		lSP3Start;	
unsigned long		lSP4Start;	
unsigned long		lSP5Start;	
			
int					nDPTblIndx;
int					nDPNum;
unsigned long		lDPStart;	
int					nNMTblIndx;
int					nNMNum;
unsigned long		lNMStart;	
int					nDCTblIndx;
int					nDCTblIndx2;
int					nDCNum;
unsigned long		lDCStart;	
int					nSCTblIndx;
int					nSCTblIndx2;
int					nSCNum;
unsigned long		lSCStart;	
int					nLinkTestCycle;
int					nDelta;
int					nDCTimeOut;
int					nTimerTblIndx;
int					nStart;
int					nAfterInit;

unsigned short current_site;
unsigned char  current_link;
unsigned short dest_site;
unsigned short dest_inx;
unsigned char  dest_link;
int				nActIndx;
int				nActIndx2;
int				nRxLen;
int				nTxLen;


unsigned short		nNumOfSites;
unsigned short		nSiteList[MAX_RTU];
unsigned short		nLinkList[MAX_RTU];
unsigned char		byComStat[MAX_RTU];
char 				message[100];

unsigned char		*p_flash;
unsigned long		lSize;
STR_TALUS_EVENT		strTE[4];

COM_PAR				sCP;
STATION_TYPE_INDEX 	sTI[MAX_RTU];
/*STATION_DESC_MOT	sMOT[250];*/
STATION_DESC_TALUS	sTAL[MAX_RTU];
STATION_COMM_DATA	sCD[MAX_RTU];

/*RTU_RAD				sRAD;*/
RTU_LIN				sLIN;

RTU_RAD_NEW			sRAD_K1;
RTU_RAD_NEW			sRAD_K2;
RTU_RAD_NEW			sRAD_K3;

/*	unsigned short				nTableNumPar;			
	int							nIEC_SP;			
	int							nIEC_SP_NUM;			
	int							nIEC_SP_FLAG;		
	int							nIEC_SP_FLAG_NUM;	
	int							nIEC_DP;			
	int							nIEC_DP_NUM;   			
	int							nIEC_DP_FSZ1;		
	int							nIEC_DP_FSZ_NUM;	
	int							nIEC_NM;					
	int							nNMNum;				*/

STATION_DESC_MOT	sMOT[MAX_RTU];

TOTAL_PAR			sT;
int					nTotalRTU;

BYTE			nMoscadHours;
/*--------------------------------------------------------------------------*/
/* The list of the function included in this block                          */
/*--------------------------------------------------------------------------*/
const CB_JUMPTBL user_jumptable[]=
{
   {"com_ch", com_check},
   {"txcom"   , tx_command},
   {"Rx"   , rx},
   {"LekR"   , fnLekR},
   {0      , 0 }
};
/*-------------------------------------*/
/* For the use of MOSCAD_find_func     */
/*-------------------------------------*/
/*static CB_FUNC setdat;
static CB_FUNC setdat2;*/
/*--------------------------------------------------------------------------*/
/* 'C' Block Initialization and Completion                                  */
/*--------------------------------------------------------------------------*/
void user_control_function(int control)
{

unsigned long		lLargest;


int					nI;	
int 			nOffset;

short			*p_col_SCAct;
unsigned long	lSRAMLength;	
	
	
   switch(control)
      {
         case CB_INIT :
         	
         	 /*setdat.func_adr = 0L;*/
         	 
         	 /* sT struktura feltoltese*/
         	 sT.sCP  = &sCP;
         	 sT.sMOT = sMOT;
         	 sT.sTAL = sTAL;
         	 sT.sTI  = sTI;
         	 sT.sRAD_K1 = &sRAD_K1;
         	 sT.sRAD_K2 = &sRAD_K2;
         	 sT.sRAD_K3 = &sRAD_K3;
         	 sT.sLIN = &sLIN;
         	 sT.nNumOfSites =&nNumOfSites;	
			 sT.nSiteList   =nSiteList;	
			 sT.nLinkList	=nLinkList;	

         	 
             nActIndx  = 0;
         	 nActIndx2 = 0;

			setdat2( (unsigned char *)&sT );
			setdat( (unsigned char *)&sT);
         	          	
        	 MOSCAD_largest_available_free_mem(&lLargest);
	   		 sprintf(message,"Version 1.2.1 Largest available free memory: %ld,   sCPR[16].nDCStart: %d",lLargest,sCP.sCPR[16].nDCStart);
   			 MOSCAD_message(message );         	          	
         	
         	
			lSRAMLength=MOSCAD_bspSRamLength();   
	   		 sprintf(message,"SRAM length: %ld",lSRAMLength);
   			 MOSCAD_message(message );         	          	

         	
        	 /*MOSCAD_available_mem(&lTotal,&lLargest);
	   		 MOSCAD_sprintf(message,"Total: %d, Largest: %d",lTotal,lLargest);
   			 MOSCAD_error(message );*/

             fnReadPar();  
             
             /*if (MOSCAD_find_func("setd2", &setdat2) == 0)
		     {
         		MOSCAD_ucall_1(&setdat2, (unsigned char *)(&sT));
         		MOSCAD_error("cbSetData2 found");
      		 }
      		 else
		     {
         		MOSCAD_error("cbSetData NOT found");
      		 }

             
             if (MOSCAD_find_func("setdat", &setdat) == 0)
		     {
         		MOSCAD_ucall_1(&setdat, (unsigned char *)(&sT));
         		MOSCAD_error("cbSetData found");
      		 }
      		 else
		     {
         		MOSCAD_error("cbSetData NOT found");
      		 }*/
      		 
       		 
      		 
         MOSCAD_set_sitetable(250,nSiteList,nLinkList,byComStat);
		 
      		/* Statikus site tabla feltoltese */
			/*fnSetStatSiteTable();*/
			
			/* Dinamikus site tabla feltoltese */
			/*fnSetDinamicSiteTable();*/

			
			/* Parancs kuldes parameterei */
			/*fnSetComPar();*/

			
     /*Nyugta inicializalas*/

/* 2014.12.10 */
for (nI=0;nI<nTotalRTU && nI<MAX_RTU;nI++)
{
	if (sCP.sCPR[nI].nAckNum>0)
		{
 		fnSCTblIndx(sCP.sCPR[nI].nAckStart, &nSCTblIndx, &nOffset, &p_col_SCAct);

		p_col_SCAct[sCP.sCPR[nI].nAckStart-nOffset] = 1;
		}
}
     
/* Statusok inicializalasa */
for (nI=0;nI<sCP.nRtuNum && nI<MAX_RTU;nI++)
{
	fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetCS, VALID);
	fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetLek, VALID);
}


     
                    
            /*if(MOSCAD_get_user_flash_block(&p_flash, &lSize) == 0)
   			{
   				MOSCAD_sprintf(message,"Parameter file found, size: %ld",lSize);
   			 	MOSCAD_error(message );
   			 	
   				sT = (TOTAL_PAR*) p_flash;
				
    			MOSCAD_sprintf(message,"nRtuNum: %d",sT->nRtuNum);
   			 	MOSCAD_error(message );
  				
   			}
   			else
   			{
   				MOSCAD_sprintf(message,"Parameter file NOT found");
   			 	MOSCAD_error(message );

   			}*/                    
            break;

         case CB_EXIT :
         	


         break;
      }
}
/*--------------------------------------------------------------------------*/
/* functions.                                                               */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Kommunikacio ellenorzes                                                  */
/*--------------------------------------------------------------------------*/
void com_check(void)
{
int			nI;

int			nTemp;

  		for (nI=0;nI<sCP.nRtuNum;nI++)
  		{
  			if (value_BX(nI)== 1)
  			/*if (p_col_B1[nI]== 1)*/
  			{

				/* Visszatörli a timer indito bitet */
				setvalue_LiX(nI,0);	
  				 		
  				 					
  				/* Ha nem volt elõtte lekérdezés */
  				if ( fnReadSPData(sCP.sCPR[nI].nSPOffsetLek) == 0)
  				{

  					 /* Hiba szamlalo novelese */
  					if (sCD[nI].nError < 100)
  					{
  						sCD[nI].nError = sCD[nI].nError + 1;
  						
  						nTemp = value_CErrX(nI);
  						setvalue_CErrX(nI,nTemp+1);	
  						
						/*if (nI < 250)
						{
 							p_col_CErr1[nI] = p_col_CErr1[nI] + 1;   		
						}*/
  					}
  					
   					if (sCD[nI].nError > 2)
  					{
  						fnWriteSPData(sCP.sCPR[nI].nSPOffsetCS,1,0,0,0,0) ; /* Komm. hiba 1-be allitasa */
  						
  						
  						/*Az IEC drivernek jelzi, hogy erventelenek az adatok*/
  						fnSetStatus(nI, NOT_TOPICAL);
  						
  						if (sCP.sCPR[nI].nSCNum == 2)
						{
							fnWriteSPData(sCP.sCPR[nI].nSPOffsetCS2, 1,  0,0,0,0);			
							fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetCS2, TOPICAL);
						}
						fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetCS, TOPICAL);
	  					fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetLek, TOPICAL);
						
						setvalue_CStatusX(nI,1);
  					} /* end if (sCD[nI].nError > 3) */
  				 					
  				}/* end if ( fnReadSPData(sCP.sCPR[nI].nSPOffsetLek) == 0) */
  				
  				
  				/* Ha volt elõtte IEC-s lekérdezés parancs*/
  				if ( fnReadSPData(sCP.sCPR[nI].nSPOffsetLek) == 1 && sCP.sCPR[nI].nSPOffsetLek > 0)
  				{

  					 MOSCAD_sprintf(message,"Komm hiba = 1: %d",nI);
   					 MOSCAD_error(message );
  					
  					fnWriteSPData(sCP.sCPR[nI].nSPOffsetLek,0,0,0,0,0); /* Lekérdezés visszatörlése */
  					fnWriteSPData(sCP.sCPR[nI].nSPOffsetCS,1,0,0,0,0) ; /* Komm. hiba 1-be allitasa */
 					
  					/*Az IEC drivernek jelzi, hogy erventelenek az adatok*/
  					fnSetStatus(nI, NOT_TOPICAL);
  					
  					if (sCP.sCPR[nI].nSPOffsetCS2 > 0)
  					{
						fnWriteSPData(sCP.sCPR[nI].nSPOffsetCS2,1,0,0,0,0) ; /* Komm. hiba 1-be allitasa */
	  					fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetCS2, TOPICAL);
 
  					}
  					
   					fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetCS, TOPICAL);
  					fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetLek, TOPICAL);
 
  					
  				}

  				/* Ha volt elõtte IEC-s lekérdezés parancs*/
  				if ( fnReadSPData(sCP.sCPR[nI].nSPOffsetLek2) == 1 && sCP.sCPR[nI].nSPOffsetLek2 > 0)
  				{

  					 MOSCAD_sprintf(message,"Komm hiba = 1: %d",nI);
   					 MOSCAD_error(message );
   					 
  					/*Az IEC drivernek jelzi, hogy erventelenek az adatok*/
  					fnSetStatus(nI, NOT_TOPICAL);
  					
	    			fnWriteSPData(sCP.sCPR[nI].nSPOffsetLek2,0,0,0,0,0); /* Lekérdezés visszatörlése */
  					fnWriteSPData(sCP.sCPR[nI].nSPOffsetCS2,1,0,0,0,0) ; /* Komm. hiba 1-be allitasa */
					
					fnWriteSPData(sCP.sCPR[nI].nSPOffsetCS,1,0,0,0,0) ; /* Komm. hiba 1-be allitasa */
					
	   				fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetCS, TOPICAL);
	   				fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetCS2, TOPICAL);
  					fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetLek, TOPICAL);
 				
					
  				} 					  				
  			}
  		}



} /* end com_check */




/*--------------------------------------------------------------------------*/
/* Táviratok fogadása és adatfeldolgozás                                    */
/*--------------------------------------------------------------------------*/
void rx(void)
{
MOSCAD_DATE_TM	mdt;


   unsigned short site_inx;

   unsigned char  rx_buffer[CB_MAX_MDLC_BUF_SIZE];

   unsigned short buff_len;
   unsigned	char  type;
   int			  nType;

   unsigned short *nRxBuf;
   int			  nTemp;


/* Ha napváltás volt  2014.04.16 GZS*/
MOSCAD_get_datetime(&mdt);
if ( mdt.hours < nMoscadHours)
	{
   				MOSCAD_sprintf(message,"Napvaltas");
   			 	MOSCAD_error(message ); 				

		for (nTemp=0;nTemp<500;nTemp++)
		{
			setvalue_CRcvdX(nTemp,0);
		}
	}
nMoscadHours = mdt.hours;
	


   buff_len=sizeof(rx_buffer);
   
   nRxBuf = (unsigned short *)rx_buffer;
 

   /*---------------------*/
   /* Receive the frame.  */
   /*---------------------*/
   if( (MOSCAD_RcvFrm(&site_inx, rx_buffer, &buff_len, &type) == 0) )
   {
   				/* MOSCAD_sprintf(message,"Frame rec., index: %d",site_inx);
   			 	MOSCAD_error(message ); */				

   	
   	if (site_inx<MAX_RTU)
   	{
   	   	
/*		MOSCAD_sprintf(message,"RxBuf[0]: %d, RxBuf[1]: %d",p_col_Rx[0],p_col_Rx[1]);
	 	MOSCAD_error(message ); 				
   	
		MOSCAD_sprintf(message,"TxBuf[0]: %d, TxBuf[1]: %d",p_col_Tx[0],p_col_Tx[1]);
	 	MOSCAD_error(message ); 				*/

      switch (type)
      {
      			


        case CB_GROUPCALL_TYPE:
            break;

        case CB_ORIGINATE_TYPE:
           break;

        case CB_ANSWER_TYPE:
			
			
        case CB_MSG_TYPE:
        	
        		nTemp = value_CRcvdX(site_inx);
				setvalue_CRcvdX(site_inx,nTemp+1);
				
				setvalue_CStatusX(site_inx,0);
				
				/* Visszatörli a timer indito bitet */
				setvalue_LiX(site_inx,0);

        	
				/*MOSCAD_sprintf(message,"Frame received, index: %d",site_inx);				
   			 	MOSCAD_error(message ); 				*/


			/*  Növeli a kommunikáció számlálót */
			/*sCD[site_inx].nCtrComm = sCD[site_inx].nCtrComm + 1;*/
 		
 			/* Nullázza a hiba számlálót */
 			sCD[site_inx].nError = 0;
 		
 			/* Nullázza a komm. hibát */
 			/*sCD[site_inx].nState = 0; 		*/
 			
 			/* Nullázza a komm. hibát az IEC táblában */
			fnWriteSPData(sCP.sCPR[site_inx].nSPOffsetCS, 0,  0,0,0,0);
			
			/*Az IEC drivernek jelzi, hogy ervenyesek az adatok*/
  			fnSetStatus(site_inx, VALID);

			fnWriteSPStatus(sCP.sCPR[site_inx].nSPOffsetCS, TOPICAL);

			if (sCP.sCPR[site_inx].nSCNum == 2)
			{
				fnWriteSPData(sCP.sCPR[site_inx].nSPOffsetCS2, 0,  0,0,0,0);
				fnWriteSPStatus(sCP.sCPR[site_inx].nSPOffsetCS2, TOPICAL);
			
			}
 		
 			/* Nullázza a lekerdezes folyamatban szot az IEC táblában */
			fnWriteSPData(sCP.sCPR[site_inx].nSPOffsetLek, 0,   0,0,0,0);
			fnWriteSPStatus(sCP.sCPR[site_inx].nSPOffsetLek, TOPICAL);

			
			if (sCP.sCPR[site_inx].nSCNum == 2)
			{
				fnWriteSPData(sCP.sCPR[site_inx].nSPOffsetLek2, 0,  0,0,0,0);			
				fnWriteSPStatus(sCP.sCPR[site_inx].nSPOffsetLek2, TOPICAL);

			}
 			

			/* Elvégzi az adatfeldolgozást */
 			nType = sTI[site_inx].nType;
 			
 				MOSCAD_sprintf(message,"Frame received, index: %d, type: %d, rx_buffer[0]: %d, rx_buffer[1]: %d, rx_buffer[2]: %d",site_inx,nType,nRxBuf[0], nRxBuf[1],nRxBuf[2]);
   			 	MOSCAD_error(message ); 				
 
			/*Szinkronizalasi igeny erkezett*/
			
			if (buff_len==4*2 &&  nRxBuf[0] == 17 && nRxBuf[1] == 7)
			{
				MOSCAD_sync(site_inx);
				MOSCAD_sprintf(message,"Szinkronizalas tortent, index: %d",site_inx);
   			 	MOSCAD_error(message ); 				

			}
				 			
 			if (nType == TYP_TAL && nRxBuf[0] == 2048 && nRxBuf[2] == 2048 && buff_len < 42 * 2)
 			{
 				TALUS_EVENT(&sTAL[site_inx],rx_buffer);
 			}
 			else if (nType == TYP_TAL && nRxBuf[0] != 2048 && buff_len == 42 * 2 )
 			{
 				TALUS_DAT(&sTAL[site_inx],rx_buffer);
 				if (site_inx == 6)
 				{
 					G1_DAT(rx_buffer);
 				}
 			}

 			
			else if (nType == TYP_MOT &&  buff_len == 42 * 2)
 			{

 				MOT_DATA(&sMOT[site_inx],rx_buffer);
 				 				
 			} 			
			else if (nType == TYP_TMOK && nRxBuf[0] == 15 && buff_len == 12 * 2)
 			{
 				TMOK_DATA(&sMOT[site_inx],rx_buffer);
 			} 	
 			else if (nType == TYP_MOT2 && nRxBuf[0] == 31 )
 			{
 				MOT_DATA2(&sMOT[site_inx],rx_buffer);
 			} 		
			else if (nType == TYP_TMOK && nRxBuf[0] == 89 )
 			{
 				TMOK_DATA2(&sMOT[site_inx],rx_buffer);
 			} 	
			else if (nType == TYP_FRONTEND && nRxBuf[0] == 100 )
 			{
 				FRONTEND_DATA(rx_buffer);
 			} 	
	
		
 			else
 			{
				MOSCAD_sprintf(message,"Type parameter error: index: %d, type: %d",site_inx,nType);
   			 	MOSCAD_error(message ); 				
 			} 			

           break;
		
       } /*end switch */
      }/*end if site_inx<MAX_RTU */
   } /*end if == 0*/
   fnRetesz();
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*Elkuld egy parancsot a DC vagy SC tabla alapjan																								  */
/*--------------------------------------------------------------------------------------------------------------------*/
void tx_command(void)
{
   unsigned char  tx_buffer[CB_MAX_MDLC_BUF_SIZE];




   int				nI;  
   int				nJ;  

   unsigned short *nTxBuf;
   int nOffset;
   short	*p_col_DCAct;
   short	*p_col_SCAct;
   int		nTemp;


   
   nTxBuf = (unsigned short *)tx_buffer;

	fnReadPar();
   
   /* Ha talal nem nullat a DC tablaban, elkuldi a parancsot a megfelelo RTU-nak, majd vissza nullaz */
   for (nI=0;nI<sCP.nRtuNum;nI++)
   {
   	for (nJ=sCP.sCPR[nI].nDCStart;nJ<sCP.sCPR[nI].nDCStart+sCP.sCPR[nI].nDCNum;nJ++)
   	{
   		fnDCTblIndx(nJ, &nDCTblIndx, &nOffset, &p_col_DCAct);
   		
   		if (p_col_DCAct[nJ-nOffset]>0)
   		{
   			
   				/*MOSCAD_sprintf(message,"nI:%d, nJ:%d ,nOffset: %d",nI, nJ,nOffset);
   			 	MOSCAD_error(message ); 				*/

   		   	/*tx_buffer[0] = 8;							
   		   	tx_buffer[1] = nJ - sCP.sCPR[nI].nDCStart;	
   		   	tx_buffer[2] = p_col_DC[nJ];				*/
   		   	
   		   	nTxBuf[0] = 0;
   		   	nTxBuf[1] = 0;
   		   	nTxBuf[2] = 0;
   		   	nTxBuf[3] = 0;
   		   	nTxBuf[4] = 0;
   		   	
   	   		nTxBuf[5] = value_CComX(nI)+1;
	   	
   		   	
   		   	nTxBuf[nJ - sCP.sCPR[nI].nDCStart] = p_col_DCAct[nJ-nOffset];
   		   	
		   		/* Mindenkeppen visszanullaz */
   				p_col_DCAct[nJ-nOffset] = 0;

 		   	
			/* Tavirat elkuldese */
 		  	if (MOSCAD_TxFrm(nI, tx_buffer, COMMAND_LENGTH*2) !=0 )
 		  	{
				MOSCAD_sprintf(message,"Could not send parancs ,nI: %d",nI);
   			 	MOSCAD_error(message ); 				
   			}
		   	else
		   	{

   				
			} 
			
			nTemp = value_CComX(nI);
			setvalue_CComX(nI,nTemp+1);

  			   	
   		} /* end if   */
   	} /* end for nJ */   	
   } /* end for nI */
   
   /* Lekerdezes parancs: ha talal nem nullat az SC tablaban, elkuldi a parancsot a megfelelo RTU-nak, majd vissza nullaz */
   for (nI=0;nI<sCP.nRtuNum;nI++)
   {
   	
   	
   	for (nJ=sCP.sCPR[nI].nSCStart;nJ<sCP.sCPR[nI].nSCStart+sCP.sCPR[nI].nSCNum;nJ++)
   	{
   		fnSCTblIndx(nJ, &nSCTblIndx, &nOffset, &p_col_SCAct);
   		
   		if (p_col_SCAct[nJ-nOffset]>0)
   		{
   			

   			
   		   	nTxBuf[0] = 8;							/* SC parancs */  
   		   	
		   		/* Mindenkeppen visszanullaz */
   				p_col_SCAct[nJ-nOffset] = 0;
 		   	   		
 
			/* Tavirat elkuldese */
 		  	if (MOSCAD_SndFrm(nI, tx_buffer, 2) !=0 )
 		  	{
				/*MOSCAD_sprintf(message,"Could not send lekerdezes ,nI: %d",nI);
   			 	MOSCAD_error(message );*/ 				
    			}
		   	else
		   	{
   				
   					
   				/* Jelzi, hogy lekérdezés folyamatban van */   				
   				if (nJ == sCP.sCPR[nI].nSCStart)
   				{
   	  				/*Jelzi, hogy a lekerdezes folyamatban bit ervenyes*/
	   				fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetLek, TOPICAL);

	   				fnWriteSPData(sCP.sCPR[nI].nSPOffsetLek,1,   0,0,0,0);
   				}
   				else if (nJ == sCP.sCPR[nI].nSCStart + 1)
   				{
   	   				/*Jelzi, hogy a lekerdezes folyamatban bit ervenyes*/
	   				fnWriteSPStatus(sCP.sCPR[nI].nSPOffsetLek2, TOPICAL);

	   				fnWriteSPData(sCP.sCPR[nI].nSPOffsetLek2,1,   0,0,0,0);   					
   				}
   				
   				            	           
	            /* Beállítja a 'lekérdezés indult' belso bitet, ez indítja a timert is  */
	            setvalue_LiX(nI,1);

	            			
			} /* end else */  			   	
   		} /* end if SC>0  */
   	} /* end for nJ */  
   } /* end for nI */
   
   /* Nyugta parancs: ha talal nullat az SC tablaban, elkuldi a parancsot a megfelelo RTU-nak, majd ujra 1-be irja */
   for (nI=0;nI<sCP.nRtuNum;nI++)
   {
   	for (nJ=sCP.sCPR[nI].nAckStart;nJ<sCP.sCPR[nI].nAckStart+sCP.sCPR[nI].nAckNum;nJ++)
   	{
   		fnSCTblIndx(nJ, &nSCTblIndx, &nOffset, &p_col_SCAct);
   		if (p_col_SCAct[nJ-nOffset]==0)
   		{
   		   	/*tx_buffer[0] = 16;						
   		   	tx_buffer[1] = nJ - sCP.sCPR[nI].nAckStart;	
   		   	tx_buffer[2] = p_col_SC[nJ];				 */ 


   		   	nTxBuf[0] = 0;
   		   	nTxBuf[1] = 0;
   		   	nTxBuf[2] = 0;
   		   	nTxBuf[3] = 0;
   		   	nTxBuf[4] = 1;
   		   	
   		   	nTemp = value_CComX(nI);
   		   	nTxBuf[5] = nTemp+1;
   		   	
   		   	setvalue_CComX(nI,nTemp+1);

		   		/* Mindenkeppen visszanullaz */
   				p_col_SCAct[nJ-nOffset] = 1;


			/* Tavirat elkuldese */
 		  	if (MOSCAD_TxFrm(nI, tx_buffer, COMMAND_LENGTH*2) !=0 )
 		  	{
				MOSCAD_sprintf(message,"Could not send ACK ,nI,nJ: %d",nI);
   			 	MOSCAD_error(message ); 				
   			}
		   	else
		   	{
   				
			}   			   	
   		} /* end if   */
   	} /* end for nJ */  
   } /* end for nI */
 
}

/****************************************************************************/
/* MOTOROLA allomas adatfeldolgozas											*/
/****************************************************************************/
void MOT_DATA(STATION_DESC_MOT	*pMOT, unsigned char *rx_buf)
{
int		nI;				

int		nIEC_Offset;
int		nMoscadOffset;

int		nDPTblIndx;




int		nNMStart;

int		nDPStart;
unsigned int		nData;









int		nVal;
int		nValH;
int		nValL;



int		nMin;
int		nMs1;
int		nMs2;
int		nSynchronized;

	p_col_RxBuf = (short *)(rx_buf);	




 		nMin		 = p_col_RxBuf[18] & 0xff;
		nMs1		 = p_col_RxBuf[19] & 0xff;
		nMs2		 = p_col_RxBuf[19] >>8;
		nSynchronized= p_col_RxBuf[13];




	/* Egesz parameterek */
	
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	



	/* Mérések feldolgozása ----------------------------------------------------------------------------------------*/
	/*  !!!!! Ha LiveZero = 1, akkor azt a letra programban kell jelezni !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

if (pMOT->nNMNum > 0)
{
	nNMStart = pMOT->nIEC_NM;
	
	for (nI=0; nI < pMOT->nNMNum && nI<16; nI++)
	{
		fnWriteNM( nNMStart+nI,p_col_RxBuf[20+nI]);			
	
	} /*end for*/
} /* end if */
	

	
/* Egybites jelzések feldolgozása ----------------------------------------------------------------------------------------*/
if (pMOT->nIEC_SP_NUM > 0)
{
	for (nI=0; nI < pMOT->nIEC_SP_NUM && nI<16; nI++)
	{

		
		nIEC_Offset = pMOT->nIEC_SP + nI;
		nData = p_col_RxBuf[0];
		
		nVal = (nData << nI) & 0x8000;
		if ( nSynchronized == 0)
		{		
		fnWriteSPData(nIEC_Offset,nVal,  0,0,0,0);			
		}
		else
		{
		fnWriteSPData(nIEC_Offset,nVal,  nMs1,nMs2,nMin,1);			
		}
		
	} /*end for*/
} /*end if*/
/* Egybites FLAG jelzések feldolgozása ----------------------------------------------------------------------------------------*/
if (pMOT->nIEC_SP_FLAG_NUM > 0)
{
	for (nI=0; nI < pMOT->nIEC_SP_FLAG_NUM && nI<16; nI++)
	{
		nIEC_Offset = pMOT->nIEC_SP_FLAG + nI;
		nData = p_col_RxBuf[1];
		
		nVal = (nData << nI) & 0x8000;		
		fnWriteSPData(nIEC_Offset,nVal,  0,0,0,0);
		
				
		
	} /*end for*/
} /*end if*/
/* Kétbites állásjelzések, feldolgozása ----------------------------------------------------------------------------------------*/
/* A program feltetelezi, hogy a ketbites jelzesek a 8. szotol kezdodnek az RxBuf-ban*/

	/*Terhelés szakaszolók állásjelzései*/
	
	nDPStart =  	pMOT->nIEC_DP;
	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMoscadOffset);

	/* 2 bites */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}

	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						
		
	nDPStart = 	pMOT->nIEC_DP;
	nData = p_col_RxBuf[8];	
if (	nDPStart > 0)
{
	for (nI=0; nI < pMOT->nIEC_DP_NUM; nI++)
	{	

		p_col_DP_CT[nDPStart+nI- nMoscadOffset]	= 0;
	
		if ( nI < 8 )
		{
			nData = p_col_RxBuf[8];	
			nValH = (nData << nI*2) & 0x8000;		
			nValL = (nData << (nI*2+1)) & 0x8000;				
		}
		else
		{
			nData = p_col_RxBuf[9];	
			nValH = (nData << (nI-8)*2 ) & 0x8000;	
			nValL = (nData << ((nI-8)*2+1)) & 0x8000;								
		}

 				if (nValH > 0)
					{
						p_col_DPH[nDPStart+nI - nMoscadOffset]= 1;
					}
					else
					{
						p_col_DPH[nDPStart+nI - nMoscadOffset]= 0;
					}
		
				if (nValL > 0)
					{
						p_col_DPL[nDPStart+nI - nMoscadOffset]= 1;
					}
					else
					{
						p_col_DPL[nDPStart+nI - nMoscadOffset]= 0;
					}	
	
	
	
	
		
		/*nVal = (nData << nI*2) & 0x8000;
 				if (nVal > 0)
					{
						p_col_DPH[nDPStart+nI - nMoscadOffset]= 1;
					}
					else
					{
						p_col_DPH[nDPStart+nI - nMoscadOffset]= 0;
					}
	
 		
		nVal = (nData << nI*2+1) & 0x8000;
				if (nVal > 0)
					{
						p_col_DPL[nDPStart+nI - nMoscadOffset]= 1;
					}
					else
					{
						p_col_DPL[nDPStart+nI - nMoscadOffset]= 0;
					}		 		*/
	}
}/*end if*/
	
/*Földelõ szakaszolók állásjelzései*/
/* A program feltetelezi, hogy a foldelo szakaszolo jelzesek a 9. szotol kezdodnek az RxBuf-ban*/

	nDPStart = 	pMOT -> nIEC_DP_FSZ1;
	nData = p_col_RxBuf[9];	
	
if (	nDPStart > 0)
{	
	for (nI=0; nI < pMOT->nIEC_DP_FSZ_NUM && nI<4; nI++)
	{			
 		p_col_DP_CT[nDPStart+nI - nMoscadOffset]	= 0;
 		
		nVal = (nData << nI*2) & 0x8000;
 				if (nVal > 0)
					{
						p_col_DPH[nDPStart+nI - nMoscadOffset]= 1;
					}
					else
					{
						p_col_DPH[nDPStart+nI - nMoscadOffset]= 0;
					}
	
 		
		nVal = (nData << (nI*2+1)) & 0x8000;
				if (nVal > 0)
					{
						p_col_DPL[nDPStart+nI - nMoscadOffset]= 1;
					}
					else
					{
						p_col_DPL[nDPStart+nI - nMoscadOffset]= 0;
					}		 		
	}/*end for*/
}/*end if*/	

}

/************************************************************************************************************************/
/****************************************************************************/
/* MOTOROLA allomas adatfeldolgozas											*/
/****************************************************************************/
void MOT_DATA2(STATION_DESC_MOT	*pMOT, unsigned char *rx_buf)
{
int		nI;				

int		nIEC_Offset;

int		nMOSCAD_OffsetDP;

int		nDPTblIndx;




int		nNMStart;

int		nDPStart;
unsigned int		nData;








int		nVal;



int		nMin;
int		nMs1;
int		nMs2;
int		nWord;
int		nBit;


	p_col_RxBuf = (short *)(rx_buf);	




 		nMin		 = p_col_RxBuf[41] & 0xff;
		nMs1		 = p_col_RxBuf[42] & 0xff;
		nMs2		 = p_col_RxBuf[42] >>8;

 

	/* Egesz parameterek */
	
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	




	/* Mérések feldolgozása ----------------------------------------------------------------------------------------*/
	/*  !!!!! Ha LiveZero = 1, akkor azt a letra programban kell jelezni !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	for (nI=0; nI < pMOT->nNMNum && nI<32; nI++)
	{
		nNMStart = pMOT->nIEC_NM;
		if (nNMStart>0)
		{		
	   		/*p_col_NM     = (short *)(table_NM.ColDataPtr[0]);
		   	p_col_NM_LZ  = (short *)(table_NM.ColDataPtr[1]);
			p_col_NM[nNMStart+nI] = p_col_RxBuf[4+nI];*/
			
			fnWriteNM( nNMStart+nI,p_col_RxBuf[9+nI]);			
			
		}
	} /*end for*/
	
/* Egybites jelzések feldolgozása ----------------------------------------------------------------------------------------*/
if (pMOT->nIEC_SP_NUM > 0)
{
	for (nI=0; nI < pMOT->nIEC_SP_NUM && nI<48; nI++)
	{
		nWord = nI/16;
		nBit  = nI - nWord * 16;

		
		nIEC_Offset = pMOT->nIEC_SP + nI;
		nData = p_col_RxBuf[1+nWord];
		
		nVal = (nData << nBit) & 0x8000;		
		fnWriteSPData(nIEC_Offset,nVal,  nMs1,nMs2,nMin,1);			
			
	} /*end for*/

} /*end if*/

/* Kétbites állásjelzések, feldolgozása ----------------------------------------------------------------------------------------*/
/* A program feltetelezi, hogy a ketbites jelzesek a 8. szotol kezdodnek az RxBuf-ban*/

		
	nDPStart = 	pMOT->nIEC_DP;
	
	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);

	/* 2 bites */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}

	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
	p_col_DP_MS1  = (short *)(table_DP.ColDataPtr[2]);
	p_col_DP_MS2  = (short *)(table_DP.ColDataPtr[3]);
	p_col_DP_MIN  = (short *)(table_DP.ColDataPtr[4]);
	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						

	
if (	nDPStart > 0)
{
	for (nI=0; nI < pMOT->nIEC_DP_NUM && nI<32; nI++)
	{	
		nWord = nI/8;
		nBit = nI - nWord * 8;
	
	
		nData = p_col_RxBuf[5 + nWord];
		
		nVal = (nData << (nBit * 2)) & 0x8000;
 										
			/* Perc beirasa */		
			p_col_DP_MIN[nDPStart+nI - nMOSCAD_OffsetDP] = nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nDPStart+nI- nMOSCAD_OffsetDP] = nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nDPStart+nI- nMOSCAD_OffsetDP] = nMs2;
 				 				 				
 				if (nVal > 0)
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}
	
 		
				nVal = (nData << (nBit*2+1)) & 0x8000;
				
				if (nVal > 0)
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}		 		
					
			/* A kapott idõt kell használni */
			p_col_DP_CT[nDPStart+nI- nMOSCAD_OffsetDP]	 = 1;	

	} /* end for */			

}/*end if*/	
} /*MOT_DATA2*/

/************************************************************************************************************************/


/****************************************************************************/
/* Rádiós és Rslink lekérdezõ fuggveny, 1 másodpercenként hívódik meg																*/
/****************************************************************************/
void fnLekR(void)
{
unsigned char tx_buffer[160];

static int	nCtrRS;


static int  nLimitRadioK1;
static int  nLimitRadioK2;
static int  nLimitRadioK3;

static int  nLimitRslink;
int			nTemp;

static int	nCtrK1;
static int	nCtrK2;
static int	nCtrK3;
static int	nActIndxK1;
static int	nActIndxK2;
static int	nActIndxK3;
static int	nActIndxRS;
int			nFirstCycle1;
int			nFirstCycle2;
int			nFirstCycle3;


nFirstCycle1 = p_col_Stat[10];
nFirstCycle2 = p_col_Stat[11];
nFirstCycle3 = p_col_Stat[12];


if (nFirstCycle1 == 0)
{
	nLimitRadioK1 = 2;
}
else
{
	nLimitRadioK1 = 307;
}

if (nFirstCycle2 == 0)
{
	nLimitRadioK2 = 2;
}
else
{
	nLimitRadioK2 = 313;
}

if (nFirstCycle3 == 0)
{
	nLimitRadioK3 = 2;
}
else
{
	nLimitRadioK3 = 309;
}

/*nLimitRadioK1 = 35;
nLimitRadioK2 = 30;
nLimitRadioK3 = 41;*/
	
nLimitRslink = 85;

nCtrRS++;
 
nCtrK1++;
nCtrK2++;
nCtrK3++; 

/*RADIO K1 korzet --------------------------------------------------------------------------------------------------*/
if (nCtrK1 >= nLimitRadioK1)
	{
   		   	tx_buffer[0] = 8;							/* SC parancs */
   		   	p_col_Stat[13] = nActIndxK1;					/* Jelzi, hogy holt tart a lekerdezes*/
   		   	   		
			/* Tavirat elkuldese */
 		  	if (MOSCAD_SndFrm(sRAD_K1.nIndx[nActIndxK1], tx_buffer, 2) !=0 )
 		  	{
 		  		MOSCAD_sprintf(message,"Could not send frame RADIO lekerdezes , index: %d",sRAD_K1.nIndx[nActIndxK1]);
		      	MOSCAD_error(message);
   			}
   			else
   			{
			 	/*MOSCAD_sprintf(message,"Periodikus lekerdezes indult RADIO RTU: %d",sRAD_K1.nIndx[nActIndxK1]);
			 	MOSCAD_error(message ); */
   				
	            /* Beállítja a 'lekérdezés indult' belso bitet, ez indítja a timert is  */
   	            setvalue_LiX(sRAD_K1.nIndx[nActIndxK1],1);
   	            
   	            nTemp = value_CLekX(sRAD_K1.nIndx[nActIndxK1]);
   	            setvalue_CLekX(sRAD_K1.nIndx[nActIndxK1],nTemp + 1);
   	        } /*end else*/
  			
			if (nActIndxK1 < sRAD_K1.nRtuNumRad-1)
			{
				nActIndxK1++;
			}
			else
			{
				nActIndxK1=0;
				p_col_Stat[10] = 1;
			}
			
		nCtrK1 = 0;
			
	} /*  end if nCtr >= nLimitRadioK1 */
	
/*RADIO K2 korzet --------------------------------------------------------------------------------------------------*/
if (nCtrK2 >= nLimitRadioK2)
	{
   		   	tx_buffer[0] = 8;							/* SC parancs */
   		   	p_col_Stat[14] = nActIndxK2;					/* Jelzi, hogy holt tart a lekerdezes*/
   		   	   		
			/* Tavirat elkuldese */
 		  	if (MOSCAD_SndFrm(sRAD_K2.nIndx[nActIndxK2], tx_buffer, 2) !=0 )
 		  	{
 		  		MOSCAD_sprintf(message,"Could not send frame RADIO lekerdezes , index: %d",sRAD_K2.nIndx[nActIndxK2]);
		      	MOSCAD_error(message);
   			}
   			else
   			{
			 	/*MOSCAD_sprintf(message,"Periodikus lekerdezes indult RADIO RTU: %d",sRAD_K2.nIndx[nActIndxK2]);
			 	MOSCAD_error(message ); */
   				
	            /* Beállítja a 'lekérdezés indult' belso bitet, ez indítja a timert is  */
   	            setvalue_LiX(sRAD_K2.nIndx[nActIndxK2],1);
   	            
   	            nTemp = value_CLekX(sRAD_K2.nIndx[nActIndxK2]);
   	            setvalue_CLekX(sRAD_K2.nIndx[nActIndxK2],nTemp + 1);
   	        } /*end else*/
  			
			if (nActIndxK2 < sRAD_K2.nRtuNumRad-1)
			{
				nActIndxK2++;
			}
			else
			{
				nActIndxK2=0;
				p_col_Stat[11] = 1;
			}
			
		nCtrK2 = 0;
			
	} /*  end if nCtr >= nLimitRadioK2 */
/*RADIO K3 korzet --------------------------------------------------------------------------------------------------*/
if (nCtrK3 >= nLimitRadioK3)
	{
   		   	tx_buffer[0] = 8;							/* SC parancs */
   		   	p_col_Stat[15] = nActIndxK3;				/* Jelzi, hogy holt tart a lekerdezes*/
   		   	   		
			/* Tavirat elkuldese */
 		  	if (MOSCAD_SndFrm(sRAD_K3.nIndx[nActIndxK3], tx_buffer, 2) !=0 )
 		  	{
 		  		MOSCAD_sprintf(message,"Could not send frame RADIO lekerdezes , index: %d",sRAD_K3.nIndx[nActIndxK3]);
		      	MOSCAD_error(message);
   			}
   			else
   			{
			 	/* MOSCAD_sprintf(message,"Periodikus lekerdezes indult RADIO RTU: %d",sRAD_K3.nIndx[nActIndxK3]);
			 	MOSCAD_error(message ); */
   				
	            /* Beállítja a 'lekérdezés indult' belso bitet, ez indítja a timert is  */
   	            setvalue_LiX(sRAD_K3.nIndx[nActIndxK3],1);
   	            
   	            nTemp = value_CLekX(sRAD_K3.nIndx[nActIndxK3]);
   	            setvalue_CLekX(sRAD_K3.nIndx[nActIndxK3],nTemp + 1);
   	        } /*end else*/
  			
			if (nActIndxK3 < sRAD_K3.nRtuNumRad-1)
			{
				nActIndxK3++;
			}
			else
			{
				nActIndxK3=0;
				p_col_Stat[12] = 1;
			}
			
		nCtrK3 = 0;
			
	} /*  end if nCtr >= nLimitRadioK3 */
	
/* RSLINK -------------------------------------------------------------------------------------------------------*/	
else if (nCtrRS >=nLimitRslink)
{
   		   	tx_buffer[0] = 8;							/* SC parancs */
   	   		
			/* Tavirat elkuldese */
 		  	if (MOSCAD_SndFrm(sLIN.nIndx[nActIndxRS], tx_buffer, 2) !=0 )
 		  	{
 		  	  MOSCAD_sprintf(message,"Could not send frame RSLINK lekerdezes, index: %d",sLIN.nIndx[nActIndxRS] );
		      MOSCAD_error(message );
   			}
   			else
   			{   				
	            /* Beállítja a 'lekérdezés indult' belso bitet, ez indítja a timert is  */
	            setvalue_LiX(sLIN.nIndx[nActIndxRS],1);
	            
   	            nTemp = value_CLekX(sLIN.nIndx[nActIndxRS]);
   	            setvalue_CLekX(sLIN.nIndx[nActIndxRS],nTemp + 1);

   			} /* end else */
	              			
			if (nActIndxRS < sLIN.nRtuNumLin-1)
			{
				nActIndxRS++;
			}
			else
			{
				nActIndxRS = 0;
			}
		
	nCtrRS = 0;	
	
	} /*  end if nCtrRS >=nLimitRslink */	
	

	

}
/****************************************************************************/
/* TALUS-os állomás felõl érkezõ távirat feldolgozása						*/
/****************************************************************************/
void TALUS_EVENT(STATION_DESC_TALUS	*pTAL, unsigned char *rx_buf)
{
int		nI;				
char	message[100];
int		nEventNum;
int		nIEC_Offset;

int		nMOSCAD_OffsetDP;

int		nDPTblIndx;

int		nTA;

int		nDPStart;
int		nData;
unsigned short	*nRxBuf;





nRxBuf = (unsigned short *)rx_buf;

		


	/* Egesz parameterek */
	/*pTAL->nTableNumPar = 2;  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	





	/* Esemény struktúra tömb kitöltése */
	nEventNum = nRxBuf[1];
	
	    MOSCAD_sprintf(message,"nRxBuf[1]: %d",nRxBuf[1]);
        MOSCAD_error(message );

	
	for (nI=0;nI<nEventNum && nI<4; nI++)
	{
		strTE[nI].nTalusAddr = nRxBuf[nI*8+3];
		strTE[nI].nValue	 = nRxBuf[nI*8+5];
		strTE[nI].nMin		 = nRxBuf[nI*8+8] & 0xff;
		strTE[nI].nMs1		 = nRxBuf[nI*8+9] & 0xff;
		strTE[nI].nMs2		 = nRxBuf[nI*8+9] >>8;
	}
		
	
	nDPStart = pTAL->nIEC_DP;
	
			
	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);
	
        /*MOSCAD_sprintf(message,"nDPStart: %d,nDPTblIndx: %d, nMOSCAD_OffsetDP: %d",nDPStart,nDPTblIndx,nMOSCAD_OffsetDP);
        MOSCAD_error(message );*/
	

	/* 2 bites */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}
								
		   	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);
		   	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);
		   	p_col_DP_MS1  = (short *)(table_DP.ColDataPtr[2]);
		   	p_col_DP_MS2  = (short *)(table_DP.ColDataPtr[3]);
		   	p_col_DP_MIN  = (short *)(table_DP.ColDataPtr[4]);
		   	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						

 	

	/* Események feldolgozása */
for (nI=0;nI<nEventNum && nI<4; nI++)
	{
	if (	pTAL->nIEC_SP > 0)
		{
		/* Ha egybites jelzés jött -------------------------------------------------------------------------------*/
		if (strTE[nI].nTalusAddr >= 896 && strTE[nI].nTalusAddr <= 927 )
		{

		nData = strTE[nI].nValue;		
		nIEC_Offset = strTE[nI].nTalusAddr - 896 + pTAL->nIEC_SP;		
		
		fnWriteSPData(nIEC_Offset,nData ,strTE[nI].nMs1,strTE[nI].nMs2,strTE[nI].nMin,1);			
											
			
		}/*end if egybites */			
	}/*end if nem nulla az IEC cim*/
	
		/* Ha kétbites jelzés jött -----------------------------------------------------------------------------------*/
if (pTAL->nIEC_DP > 0)
{		
        /*MOSCAD_sprintf(message,"strTE[0].nTalusAddr: %d",strTE[0].nTalusAddr);
        MOSCAD_error(message );*/


		if (strTE[nI].nTalusAddr >= 832 && strTE[nI].nTalusAddr <= 839 )
		{
			
			/* Double point  */

			nIEC_Offset = (strTE[nI].nTalusAddr - 832) / 2 + pTAL->nIEC_DP;						
			
        /*MOSCAD_sprintf(message,"nIEC_Offset: %d",nIEC_Offset);
        MOSCAD_error(message );*/

						
			/* A kapott idõt kell használni */
			p_col_DP_CT[nIEC_Offset-nMOSCAD_OffsetDP] = 1;	
						
			/* Perc beirasa */		
			p_col_DP_MIN[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs2;
			
			
        /*MOSCAD_sprintf(message,"strTE[0].nValue: %d",strTE[0].nValue);
        MOSCAD_error(message );*/
			
			
			/* Érték beírása */
			/* Ha páros */
			if ( ((strTE[nI].nTalusAddr - 832) & 1) == 0 )
			{
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nValue;	/* DPL -> OPEN */			
			}
			if ( ((strTE[nI].nTalusAddr - 832) & 1) == 1 )  /* DPH -> CLOSE */
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nValue;	
			}
			

		}/*end if kétbites */
}/*end if iec cim > 0 */
			
		/* Ha 1 bitbõl képzett kétbites jelzés jött, foldelo szakaszolo ------------------------------------------------*/
		if (strTE[nI].nTalusAddr >= 904 && strTE[nI].nTalusAddr <= 907 && pTAL->nIEC_DP_FSZ1!=0)
		{
			
			/* Double point  */
						
			nIEC_Offset = strTE[nI].nTalusAddr - 904  + pTAL->nIEC_DP_FSZ1;			
			
        /*MOSCAD_sprintf(message,"nIEC_Offset: %d",nIEC_Offset);
        MOSCAD_error(message );*/
			

						
			/* A kapott idõt kell használni */
			p_col_DP_CT[nIEC_Offset-nMOSCAD_OffsetDP] = 1;	
						
			/* Perc beirasa */		
			p_col_DP_MIN[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs2;
			

			/* Érték beírása */
			if (strTE[nI].nValue == 1)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
			}
			if (strTE[nI].nValue == 0)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
			}

		}/*end if egy bitbõl képzett kétbites */
			
		/* Ha 2 bitbõl képzett kétbites jelzés jött -------------------------------------------------------------------*/
		if (pTAL->nIEC_DP_2BIT1 !=0  || pTAL->nIEC_DP_2BIT2 !=0 || pTAL->nIEC_DP_2BIT3 !=0)  
		{
			

			
			nTA = strTE[nI].nTalusAddr;
						
			MOSCAD_sprintf(message,"nTA: %d",nTA);
        	MOSCAD_error(message );
			
			
			if  (nTA==pTAL->nIEC_DP_2BIT_KINT1 || nTA==pTAL->nIEC_DP_2BIT_BENT1 || nTA==pTAL->nIEC_DP_2BIT_KINT2 || nTA==pTAL->nIEC_DP_2BIT_BENT2 || nTA==pTAL->nIEC_DP_2BIT_KINT3 || nTA==pTAL->nIEC_DP_2BIT_BENT3)
			{
					nIEC_Offset = pTAL->nIEC_DP_2BIT1;					
					MOSCAD_sprintf(message,"nIEC_Offset: %d",nIEC_Offset);
        			MOSCAD_error(message );

				
				
				if (nTA==pTAL->nIEC_DP_2BIT_KINT1 || nTA==pTAL->nIEC_DP_2BIT_BENT1)
				{
					nIEC_Offset = pTAL->nIEC_DP_2BIT1;					
					MOSCAD_sprintf(message,"nIEC_Offset2: %d",nIEC_Offset);
        			MOSCAD_error(message );

					
				}			
			
				if (nTA==pTAL->nIEC_DP_2BIT_KINT2 || nTA==pTAL->nIEC_DP_2BIT_BENT2)
				{
					nIEC_Offset = pTAL->nIEC_DP_2BIT2;
				}			

				if (nTA==pTAL->nIEC_DP_2BIT_KINT3 || nTA==pTAL->nIEC_DP_2BIT_BENT3)
				{
					nIEC_Offset = pTAL->nIEC_DP_2BIT3;
				}			
			
				/* Double point  */
					
				/* DP tabla indexe, es offsete */
				fnDPTblIndx(nIEC_Offset,&nDPTblIndx,&nMOSCAD_OffsetDP);

	/* 2 bites */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}
								
		   	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);
		   	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);
		   	p_col_DP_MS1  = (short *)(table_DP.ColDataPtr[2]);
		   	p_col_DP_MS2  = (short *)(table_DP.ColDataPtr[3]);
		   	p_col_DP_MIN  = (short *)(table_DP.ColDataPtr[4]);
		   	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						


						
				/* A kapott idõt kell használni */
				p_col_DP_CT[nIEC_Offset-nMOSCAD_OffsetDP] = 1;	
						
				/* Perc beirasa */		
				p_col_DP_MIN[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMin;	
															
				/* MS1 beirasa */		
				p_col_DP_MS1[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs1;
						
				/* MS2 beirasa */		
				p_col_DP_MS2[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs2;
			
			if (nIEC_Offset > 0)
			{
				if (nTA==pTAL->nIEC_DP_2BIT_KINT1 || nTA==pTAL->nIEC_DP_2BIT_KINT2 || nTA==pTAL->nIEC_DP_2BIT_KINT3)
				{					
					/* Érték beírása */
					p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nValue;
				}			

				if (nTA==pTAL->nIEC_DP_2BIT_BENT1 || nTA==pTAL->nIEC_DP_2BIT_BENT2 || nTA==pTAL->nIEC_DP_2BIT_BENT3)
				{
					/* Érték beírása */
					p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nValue;
				}
			}/*end if iec cim >0 */
			
			} /*end if valamelyik ketbites */
		}/*end if két bitbõl képzett kétbites */

		/* Ha 1 bitbõl képzett kétbites jelzés jött, 1. altalanos ---------------------------------------------------------*/
		if (pTAL->nIEC_DP_12BIT1!=0 && strTE[nI].nTalusAddr==pTAL->nIEC_DP_2BIT_BK1)
		{
			
			/* Double point  */
			
			nIEC_Offset = pTAL->nIEC_DP_12BIT1;	
			
				   		
			
						
			/* A kapott idõt kell használni */
			p_col_DP_CT[nIEC_Offset-nMOSCAD_OffsetDP] = 1;	
						
			/* Perc beirasa */		
			p_col_DP_MIN[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs2;
			

			/* Érték beírása */
			if (strTE[nI].nValue == 1)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
			}
			if (strTE[nI].nValue == 0)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
			}

		}/*end if egy bitbõl képzett kétbites */

		/* Ha 1 bitbõl képzett kétbites jelzés jött, 2. altalanos ---------------------------------------------------------*/
		if (pTAL->nIEC_DP_12BIT2!=0 && strTE[nI].nTalusAddr==pTAL->nIEC_DP_2BIT_BK2)
		{
			
			/* Double point  */
	
			nIEC_Offset = pTAL->nIEC_DP_12BIT2;	
			
				   		
			

						
			/* A kapott idõt kell használni */
			p_col_DP_CT[nIEC_Offset-nMOSCAD_OffsetDP] = 1;	
						
			/* Perc beirasa */		
			p_col_DP_MIN[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs2;
			

			/* Érték beírása */
			if (strTE[nI].nValue == 1)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
			}
			if (strTE[nI].nValue == 0)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
			}

		}/*end if egy bitbõl képzett kétbites */
			
		/* Ha 1 bitbõl képzett kétbites jelzés jött, 3. altalanos ---------------------------------------------------------*/
		if (pTAL->nIEC_DP_12BIT3!=0 && strTE[nI].nTalusAddr==pTAL->nIEC_DP_2BIT_BK3)
		{
			
			/* Double point  */
			
			nIEC_Offset = pTAL->nIEC_DP_12BIT3;	
			
				   		
			
						
			/* A kapott idõt kell használni */
			p_col_DP_CT[nIEC_Offset-nMOSCAD_OffsetDP] = 1;	
						
			/* Perc beirasa */		
			p_col_DP_MIN[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs2;
			

			/* Érték beírása */
			if (strTE[nI].nValue == 1)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
			}
			if (strTE[nI].nValue == 0)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
			}

		}/*end if egy bitbõl képzett kétbites */
				
		/* Ha 1 bitbõl képzett kétbites jelzés jött, 4. altalanos ---------------------------------------------------------*/
		if (pTAL->nIEC_DP_12BIT4!=0 && strTE[nI].nTalusAddr==pTAL->nIEC_DP_2BIT_BK4)
		{
			
			/* Double point  */
		
			nIEC_Offset = pTAL->nIEC_DP_12BIT4;	
			
				   								
			/* A kapott idõt kell használni */
			p_col_DP_CT[nIEC_Offset-nMOSCAD_OffsetDP] = 1;	
						
			/* Perc beirasa */		
			p_col_DP_MIN[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nIEC_Offset-nMOSCAD_OffsetDP] = strTE[nI].nMs2;
			

			/* Érték beírása */
			if (strTE[nI].nValue == 1)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
			}
			if (strTE[nI].nValue == 0)
			{
				p_col_DPH[nIEC_Offset-nMOSCAD_OffsetDP] = 0;
				p_col_DPL[nIEC_Offset-nMOSCAD_OffsetDP] = 1;
			}

		}/*end if egy bitbõl képzett kétbites */			
	} /*end for*/
	
				
 	/*Összevont zárlati hiba ------------------------------------------------------------------------------------------*/
				if (pTAL->nIEC_OsszevontHiba != 0)
				{
					
					for (nI=0;nI<8;nI++)
					{
						if (fnReadSPData(pTAL->nIEC_SP + nI) == 1) 
						{
							fnWriteSPData(pTAL->nIEC_OsszevontHiba,1 , 0,0,0,0);
							
							
						}/*end if*/
					} /*end for*/
					if (fnReadSPData(pTAL->nIEC_SP + 0)==0 && fnReadSPData(pTAL->nIEC_SP + 1)==0 && fnReadSPData(pTAL->nIEC_SP + 2)==0 && fnReadSPData(pTAL->nIEC_SP + 3)==0 && fnReadSPData(pTAL->nIEC_SP + 4)==0 && fnReadSPData(pTAL->nIEC_SP + 5)==0 && fnReadSPData(pTAL->nIEC_SP + 6)==0 && fnReadSPData(pTAL->nIEC_SP + 7)==0 )
						{
							fnWriteSPData(pTAL->nIEC_OsszevontHiba,0 , 0,0,0,0);
							
						}/*end if*/
					
				
				}		


}
/************************************************************************************************************/
/* TALUS felõl érkezõ analóg jelváltozás feldolgozása*/
/************************************************************************************************************/
void TALUS_DAT(STATION_DESC_TALUS	*pTAL, unsigned char *rx_buf)
{
int		nI,nJ;				
char	message[300];

int		nIEC_Offset;
int		nMOSCAD_Offset;
int		nMOSCAD_OffsetDP;


int		nDPTblIndx;


int		nEZ;	

int		nNMStart;

int		nDPStart;
unsigned int		nData;
int		nDP_IEC;
int		nDPL;
int		nDPH;
int		nShiftL;
int		nShiftH;
int 	nDataL;
int 	nDataH;
int		nERL;
int		nERH;
int		nER;
int		nDP;
int		nShift;
int		nVal;
unsigned short	*nRxBuf;


nRxBuf = (unsigned short *)rx_buf;

	
	
/* Mérések feldolgozása ----------------------------------------------------------------------------------------*/

if (pTAL->nNMNum > 0)
{		
	nNMStart = pTAL->nIEC_NM;
		
	for (nI=0; nI<4 && nI<pTAL->nNMNum; nI++)
	{
		fnWriteNM( nNMStart+nI,nRxBuf[12+nI]*3200/750);
	} /*end for*/
	
	/*Ha van PM500 vagy SEPAM*/
	for (nI=4; nI<pTAL->nNMNum && nI<16; nI++) 
	{
		nNMStart = pTAL->nIEC_NM;
		if (nNMStart > 0)
		{				
			fnWriteNM( nNMStart+nI,nRxBuf[12+nI]);

		}
		
	} /*end for*/
} /* end if nMNum>0 */	
		
	
/* Egybites jelzések feldolgozása ----------------------------------------------------------------------------------------*/
if (pTAL->nIEC_SP > 0)
{
for (nJ=1; nJ<3; nJ++)
	{	
	for (nI=0; nI<16; nI++)
	{
		
		nIEC_Offset = pTAL->nIEC_SP+(nJ-1)*16+nI;

		nData = nRxBuf[nJ];
		nVal = (nData >> nI) & 1;    
		
		fnWriteSPData(nIEC_Offset,nVal ,0,0,0,0);			
		
			
			
	} /*end for*/
} /*end for*/
} /*end if pTAL->nIEC_SP>0 */	


/* Kétbites jelzések feldolgozása ----------------------------------------------------------------------------------------*/
	/*Terhelés szakaszolók állásjelzései*/
	nDPStart = 	pTAL->nIEC_DP;

	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);


	nData = nRxBuf[9];	
		

	/* DP */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}
	
	
	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						
		
	

	if (nDPStart > 0)
	{ 
	
		for (nI=0; nI<4; nI++)
		{				
 			p_col_DPL[nDPStart+nI-nMOSCAD_OffsetDP] = (nData >> nI*2)   & 1;
	 		p_col_DPH[nDPStart+nI-nMOSCAD_OffsetDP] = (nData >> (nI*2+1)) & 1;
	 		p_col_DP_CT[nDPStart+nI-nMOSCAD_OffsetDP]= 0;
		}
	}  /*end if*/
	
	/*Földelõ szakaszolók állásjelzései*/
	nDPStart = 	pTAL->nIEC_DP_FSZ1;
	nData = nRxBuf[1];	
	
	if (nDPStart > 0)
	{ 
		for (nI=0; nI<4; nI++)
		{			
			if (    ((nData >> (8+nI)) & 1) == 1      )
			{
 				p_col_DPH[nDPStart+nI-nMOSCAD_OffsetDP] = 1;
	 			p_col_DPL[nDPStart+nI-nMOSCAD_OffsetDP] = 0;
			}
			else
			{
 				p_col_DPH[nDPStart+nI-nMOSCAD_OffsetDP] = 0;
	 			p_col_DPL[nDPStart+nI-nMOSCAD_OffsetDP] = 1;
			}
			
			p_col_DP_CT[nDPStart+nI-nMOSCAD_OffsetDP]= 0;	
		}/*end for*/
	}  /*end if*/
	
		/*1 bitbõl képzett 2 bites állásjelzések, 1. altalanos*/	
	if(	pTAL->nIEC_DP_12BIT1 != 0)
	{
		nDP_IEC = pTAL->nIEC_DP_12BIT1;
		
		nDP   = pTAL->nIEC_DP_2BIT_BK1;
		
		/* DP tabla indexe, es offsete */
		fnDPTblIndx(nDP_IEC,&nDPTblIndx,&nMOSCAD_OffsetDP);

		
		nER = nDP/16;
		
		nData = nRxBuf[nDP/16-55];
				
		nShift = nDP - nER * 16;
			
			if (    ((nData >> (nShift)) & 1) == 1      )
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 1;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 0;
			}
			else
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 0;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 1;
			}		
			p_col_DP_CT[nDP_IEC-nMOSCAD_OffsetDP]= 0;
	}
		/*1 bitbõl képzett 2 bites állásjelzések, 2. altalanos*/	
	if(	pTAL->nIEC_DP_12BIT2 != 0)
	{
		nDP_IEC = pTAL->nIEC_DP_12BIT2;
		
		nDP   = pTAL->nIEC_DP_2BIT_BK2;
		
		/* DP tabla indexe, es offsete */
		fnDPTblIndx(nDP_IEC,&nDPTblIndx,&nMOSCAD_OffsetDP);

		
		nER = nDP/16;
		
		nData = nRxBuf[nDP/16-55];
				
		nShift = nDP - nER * 16;
			
			if (    ((nData >> (nShift)) & 1) == 1      )
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 1;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 0;
			}
			else
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 0;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 1;
			}		
			p_col_DP_CT[nDP_IEC-nMOSCAD_OffsetDP]= 0;
	}	
		/*1 bitbõl képzett 2 bites állásjelzések, 3. altalanos*/	
	if(	pTAL->nIEC_DP_12BIT3 != 0)
	{
		nDP_IEC = pTAL->nIEC_DP_12BIT3;
		
		nDP   = pTAL->nIEC_DP_2BIT_BK3;
	
		/* DP tabla indexe, es offsete */
		fnDPTblIndx(nDP_IEC,&nDPTblIndx,&nMOSCAD_OffsetDP);

		
		nER = nDP/16;
		
		nData = nRxBuf[nDP/16-55];
				
		nShift = nDP - nER * 16;
			
			if (    ((nData >> (nShift)) & 1) == 1      )
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 1;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 0;
			}
			else
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 0;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 1;
			}		
			p_col_DP_CT[nDP_IEC-nMOSCAD_OffsetDP]= 0;
	}	
		/*1 bitbõl képzett 2 bites állásjelzések, 4. altalanos*/	
	if(	pTAL->nIEC_DP_12BIT4 != 0)
	{
		nDP_IEC = pTAL->nIEC_DP_12BIT4;
		
		nDP   = pTAL->nIEC_DP_2BIT_BK4;
		
		nER = nDP/16;
		
		nData = nRxBuf[nDP/16-55];
				
		nShift = nDP - nER * 16;
			
			if (    ((nData >> (nShift)) & 1) == 1      )
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 1;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 0;
			}
			else
			{
 				p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = 0;
	 			p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = 1;
			}		
			p_col_DP_CT[nDP_IEC-nMOSCAD_OffsetDP]= 0;
	}	
	
		
	/*2 bitbõl képzett 2 bites állásjelzések*/	
	if(	pTAL->nIEC_DP_2BIT1 != 0)
	{
		nDP_IEC = pTAL->nIEC_DP_2BIT1;
		
		nDPL = pTAL->nIEC_DP_2BIT_KINT1;
		nDPH = pTAL->nIEC_DP_2BIT_BENT1;
		
		nERL = nDPL/16;
		nERH = nDPH/16;
		
		nDataL = nRxBuf[nDPL/16-55];
		nDataH = nRxBuf[nDPH/16-55];
				
		nShiftL = nDPL - nERL * 16;
		nShiftH = nDPH - nERH * 16;
		
		p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = (nDataL >> nShiftL)   & 1;
		p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = (nDataH >> nShiftH)   & 1;		
		p_col_DP_CT[nDP_IEC-nMOSCAD_OffsetDP]   = 0; 		
	}
		
	if(	pTAL->nIEC_DP_2BIT2 != 0)
	{
		nDP_IEC = pTAL->nIEC_DP_2BIT2;
		
		nDPL = pTAL->nIEC_DP_2BIT_KINT2;
		nDPH = pTAL->nIEC_DP_2BIT_BENT2;
		
		nERL = nDPL/16;
		nERH = nDPH/16;
		
		nDataL = nRxBuf[nDPL/16-55];
		nDataH = nRxBuf[nDPH/16-55];
				
		nShiftL = nDPL - nERL * 16;
		nShiftH = nDPH - nERH * 16;
		
		p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = (nDataL >> nShiftL)   & 1;
		p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = (nDataH >> nShiftH)   & 1;		
		p_col_DP_CT[nDP_IEC-nMOSCAD_OffsetDP]   = 0; 		
	}	
	
	if(	pTAL->nIEC_DP_2BIT3 != 0)
	{
		nDP_IEC = pTAL->nIEC_DP_2BIT3;
		
		nDPL = pTAL->nIEC_DP_2BIT_KINT3;
		nDPH = pTAL->nIEC_DP_2BIT_BENT3;
		
		nERL = nDPL/16;
		nERH = nDPH/16;
		
		nDataL = nRxBuf[nDPL/16-55];
		nDataH = nRxBuf[nDPH/16-55];
				
		nShiftL = nDPL - nERL * 16;
		nShiftH = nDPH - nERH * 16;
		
		p_col_DPL[nDP_IEC-nMOSCAD_OffsetDP] = (nDataL >> nShiftL)   & 1;
		p_col_DPH[nDP_IEC-nMOSCAD_OffsetDP] = (nDataH >> nShiftH)   & 1;		
		p_col_DP_CT[nDP_IEC-nMOSCAD_OffsetDP]   = 0; 		
	}	
	
	
	
 	/*Összevont zárlati hiba ------------------------------------------------------------------------------------------*/
				if (pTAL->nIEC_OsszevontHiba != 0)
				{
					nEZ = pTAL->nIEC_SP-nMOSCAD_Offset;
					
					for (nI=0;nI<8;nI++)
					{
						if (fnReadSPData(pTAL->nIEC_SP + nI) == 1)  /*    p_col_SP[nEZ + nI]==1)*/
						{
							fnWriteSPData(pTAL->nIEC_OsszevontHiba,1 , 0,0,0,0);	/*p_col_SP_CT[pTAL->nIEC_OsszevontHiba-nMOSCAD_Offset] = 0;*/
							
							
						}/*end if*/
					} /*end for*/
					if (fnReadSPData(pTAL->nIEC_SP + 0)==0 && fnReadSPData(pTAL->nIEC_SP + 1)==0 && fnReadSPData(pTAL->nIEC_SP + 2)==0 && fnReadSPData(pTAL->nIEC_SP + 3)==0 && fnReadSPData(pTAL->nIEC_SP + 4)==0 && fnReadSPData(pTAL->nIEC_SP + 5)==0 && fnReadSPData(pTAL->nIEC_SP + 6)==0 && fnReadSPData(pTAL->nIEC_SP + 7)==0 )
						{
							fnWriteSPData(pTAL->nIEC_OsszevontHiba,0 , 0,0,0,0);
							/*p_col_SP_CT[pTAL->nIEC_OsszevontHiba-nMOSCAD_Offset] = 0;
							p_col_SP[pTAL->nIEC_OsszevontHiba-nMOSCAD_Offset]    = 0;*/
							
						}/*end if*/
					
				
				}	
				
/*TALUS-Moscad kommunikacio ------------------------------------------------------------------------------------*/
if (pTAL->nIEC_MT_KommHiba != 0)
				{
					if (pTAL->nKommStatusNum == 0)
					{
					nData = nRxBuf[29];	
					nVal =  nData  & 1;    
					
					fnWriteSPData(pTAL->nIEC_MT_KommHiba,nVal , 0,0,0,0);
					}
					else
					{
						
						for (nI=0; nI<pTAL->nKommStatusNum && nI<16; nI++)
						{							
							nData = nRxBuf[29];
							nVal = (nData >> nI) & 1;    

		
							fnWriteSPData(pTAL->nIEC_MT_KommHiba + nI, nVal ,0,0,0,0);			
							
							
						} /*end for*/												
					} /* end else */
				} /* end if */



/*Extra 2 bites ------------------------------------------------------------------------------------*/
if (pTAL->nDP_EXTRA_NUM > 0)
				{
				/*Kezdocim*/
				nDPStart = 	pTAL->nDP_EXTRA_OFFSET;

				/* DP tabla indexe, es offsete */
				fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);
						
				/* DP */
   				if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
		   		{
        			MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
		        	MOSCAD_error(message );
        			return;
		   		}
		
				p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
				p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
				p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 								
				
				nData = nRxBuf[32];	
							
						for (nI=0; nI<pTAL->nDP_EXTRA_NUM && nI<8; nI++)
						{							
							if (  ((nData << nI*2) & 0x8000) > 0     )
							{
								p_col_DPL[nDPStart+nI-nMOSCAD_OffsetDP] = 1;
							}
							else
							{
								p_col_DPL[nDPStart+nI-nMOSCAD_OffsetDP] = 0;
							}
							
							if (  ((nData << (nI*2+1)) & 0x8000) > 0     )
							{
								p_col_DPH[nDPStart+nI-nMOSCAD_OffsetDP] = 1;
							}
							else
							{
								p_col_DPH[nDPStart+nI-nMOSCAD_OffsetDP] = 0;
							}
							
	 						p_col_DP_CT[nDPStart+nI-nMOSCAD_OffsetDP]= 0;
						} /*end for*/																
				} /* end if */


}

/****************************************************************************/
/* TMOK allomas adatfeldolgozas											*/
/****************************************************************************/
void TMOK_DATA(STATION_DESC_MOT	*pMOT, unsigned char *rx_buf)
{
int		nI;				

int		nIEC_Offset;

int		nMOSCAD_OffsetDP;

int		nDPTblIndx;




int		nNMStart;

int		nDPStart;
unsigned int		nData;









int		nVal;



int		nMin;
int		nMs1;
int		nMs2;


	p_col_RxBuf = (short *)(rx_buf);	




 		nMin		 = p_col_RxBuf[8] & 0xff;
		nMs1		 = p_col_RxBuf[9] & 0xff;
		nMs2		 = p_col_RxBuf[9] >>8;

 

	/* Egesz parameterek */
	
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	




	/* Mérések feldolgozása ----------------------------------------------------------------------------------------*/
	/*  !!!!! Ha LiveZero = 1, akkor azt a letra programban kell jelezni !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	for (nI=0; nI < pMOT->nNMNum && nI<4; nI++)
	{
		nNMStart = pMOT->nIEC_NM;
		if (nNMStart>0)
		{		
	   		/*p_col_NM     = (short *)(table_NM.ColDataPtr[0]);
		   	p_col_NM_LZ  = (short *)(table_NM.ColDataPtr[1]);
			p_col_NM[nNMStart+nI] = p_col_RxBuf[4+nI];*/
			
			fnWriteNM( nNMStart+nI,p_col_RxBuf[4+nI]);			
			
		}
	} /*end for*/

	/*  !!!!! Ha LiveZero = 1, akkor azt a letra programban kell jelezni !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	for (nI=0; nI < pMOT->nNMNum2 && nI<4; nI++)
	{
		nNMStart = pMOT->nIEC_NM2;
		if (nNMStart>0)
		{		
	   		/*p_col_NM     = (short *)(table_NM.ColDataPtr[0]);
		   	p_col_NM_LZ  = (short *)(table_NM.ColDataPtr[1]);
			p_col_NM[nNMStart+nI] = p_col_RxBuf[4+nI];*/
			
			fnWriteNM( nNMStart+nI,p_col_RxBuf[10+nI]);			
			
		}
	} /*end for*/

	
/* Egybites jelzések feldolgozása ----------------------------------------------------------------------------------------*/
if (pMOT->nIEC_SP_NUM > 0)
{
	for (nI=0; nI < pMOT->nIEC_SP_NUM && nI<16; nI++)
	{

		
		nIEC_Offset = pMOT->nIEC_SP + nI;
		nData = p_col_RxBuf[1];
		
		nVal = (nData << nI) & 0x8000;		
		fnWriteSPData(nIEC_Offset,nVal,  nMs1,nMs2,nMin,1);			
			
	} /*end for*/
	
	for (nI=16; nI < pMOT->nIEC_SP_NUM && nI<32; nI++)
	{		
		nIEC_Offset = pMOT->nIEC_SP + nI;
		nData = p_col_RxBuf[2];
		
		nVal = (nData << (nI-16)) & 0x8000;		
		fnWriteSPData(nIEC_Offset,nVal,  nMs1,nMs2,nMin,1);			
			
	} /*end for*/
	
} /*end if*/

/* Kétbites állásjelzések, feldolgozása ----------------------------------------------------------------------------------------*/
/* A program feltetelezi, hogy a ketbites jelzesek a 8. szotol kezdodnek az RxBuf-ban*/

		
	nDPStart = 	pMOT->nIEC_DP;
	
	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);

	/* 2 bites */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}

	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
	p_col_DP_MS1  = (short *)(table_DP.ColDataPtr[2]);
	p_col_DP_MS2  = (short *)(table_DP.ColDataPtr[3]);
	p_col_DP_MIN  = (short *)(table_DP.ColDataPtr[4]);
	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						

	nData = p_col_RxBuf[3];	
	
if (	nDPStart > 0)
{
	for (nI=0; nI < pMOT->nIEC_DP_NUM && nI<4; nI++)
	{	
		
		nVal = (nData << nI*2) & 0x8000;
 										
			/* Perc beirasa */		
			p_col_DP_MIN[nDPStart+nI - nMOSCAD_OffsetDP] = nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nDPStart+nI- nMOSCAD_OffsetDP] = nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nDPStart+nI- nMOSCAD_OffsetDP] = nMs2;
 				 				
 				
 				if (nVal > 0)
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}
	
 		
				nVal = (nData << (nI*2+1)) & 0x8000;
				
				if (nVal > 0)
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}		 		
					
			/* A kapott idõt kell használni */
			p_col_DP_CT[nDPStart+nI- nMOSCAD_OffsetDP]	 = 1;	

	}
}/*end if*/	
} /*TMOK_DATA*/
/*-----------------------------------------------------------------------------------------------*/
/****************************************************************************/
/* Gyor G1 allomas adatfeldolgozas											*/
/****************************************************************************/
void G1_DAT(unsigned char *rx_buf)
{
int		nI;				
char	message[100];
int		nIEC_Offset;
int		nVal;

int		nMOSCAD_OffsetDP;


int		nDPTblIndx;




int		nNMStart;

int		nDPStart;
unsigned int		nData;





unsigned short	*nRxBuf;


nRxBuf = (unsigned short *)rx_buf;

	
	
/* Mérések feldolgozása ----------------------------------------------------------------------------------------*/

		
	nNMStart = 14;
		
	for (nI=0; nI<20; nI++)
	{
		fnWriteNM( nNMStart+nI,nRxBuf[12+nI]);
	} /*end for*/
	
/* Kétbites jelzések feldolgozása ----------------------------------------------------------------------------------------*/
	/*Terhelés szakaszolók állásjelzései*/
	nDPStart = 	22;

	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);


	nData = nRxBuf[39];	
		

	/* DP */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}
	
	
	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						
		
	

	if (nDPStart > 0)
	{ 
	
		for (nI=0; nI<4; nI++)
		{				
 			p_col_DPL[nDPStart+nI-nMOSCAD_OffsetDP] = (nData >> nI*2)   & 1;
	 		p_col_DPH[nDPStart+nI-nMOSCAD_OffsetDP] = (nData >> (nI*2+1)) & 1;
	 		p_col_DP_CT[nDPStart+nI-nMOSCAD_OffsetDP]= 0;
		}
	}  /*end if*/
	
/*TALUS-Moscad kommunikacio ------------------------------------------------------------------------------------*/
			nData = nRxBuf[41];	
			fnWriteSPData(122,nData , 0,0,0,0);


/* Uj 1 bites jelzesek feldolgozasa */
	for (nI=0; nI<16; nI++)
	{

		
		nIEC_Offset = 4798 + nI;
		nData = nRxBuf[38];
		
		nVal = (nData << nI) & 0x8000;		
		fnWriteSPData(nIEC_Offset,nVal,  0,0,0,0);			
			
	} /*end for*/



}
/*-----------------------------------------------------------------------------------------------*/
/****************************************************************************/
/* Parameter tabla kiolvasas												*/
/****************************************************************************/
void fnReadPar(void)
{
char 				message[100];



/* parameter tabla feldolgozas */

	/* Egesz parameterek */
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nTableNum2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	


	/* Double command */
/*	nDCTblIndx = p_col_parInt[23];	
	if (MOSCAD_get_table_info (nDCTblIndx,&table_DC)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDCTblIndx);
        MOSCAD_error(message );
        return;
   		}
	p_col_DC = (short *)(table_DC.ColDataPtr[0]);
*/
	/* Double command 2. */
/*	nDCTblIndx2 = p_col_parInt[45];	
	if (MOSCAD_get_table_info (nDCTblIndx2,&table_DC2)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDCTblIndx2);
        MOSCAD_error(message );
        return;
   		}
	p_col_DC2 = (short *)(table_DC2.ColDataPtr[0]);
*/
		/* Single command */
/*	nSCTblIndx = p_col_parInt[31];	
	if (MOSCAD_get_table_info (nSCTblIndx,&table_SC)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nSCTblIndx);
        MOSCAD_error(message );
        return;
   		}
	p_col_SC = (short *)(table_SC.ColDataPtr[0]);
*/	

		/* Single command 2. */
/*	nSCTblIndx2 = p_col_parInt[46];	
	if (MOSCAD_get_table_info (nSCTblIndx2,&table_SC2)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nSCTblIndx2);
        MOSCAD_error(message );
        return;
   		}
	p_col_SC2 = (short *)(table_SC2.ColDataPtr[0]);
*/

	/* Timerek */
	nTimerTblIndx = 33;	
	if (MOSCAD_get_table_info (nTimerTblIndx,&table_Timers)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nTimerTblIndx);
        MOSCAD_error(message );
        return;
   		}
	p_col_T1  = (short *)(table_Timers.ColDataPtr[0]);
	p_col_T2  = (short *)(table_Timers.ColDataPtr[1]);
	p_col_Li1 = (short *)(table_Timers.ColDataPtr[2]);
	p_col_Li2 = (short *)(table_Timers.ColDataPtr[3]);
	p_col_B1  = (short *)(table_Timers.ColDataPtr[4]);
	p_col_B2  = (short *)(table_Timers.ColDataPtr[5]);


	if (MOSCAD_get_table_info (37,&table_CStat1)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",60);
        MOSCAD_error(message );
        return;
   		}
   		
	p_col_CRcvd1  = (short *)(table_CStat1.ColDataPtr[0]);   		
	p_col_Status1 = (short *)(table_CStat1.ColDataPtr[1]);
	p_col_CLek1   = (short *)(table_CStat1.ColDataPtr[2]);   		
	p_col_CCom1   = (short *)(table_CStat1.ColDataPtr[3]);
	p_col_CErr1   = (short *)(table_CStat1.ColDataPtr[4]);


	if (MOSCAD_get_table_info (38,&table_CStat2)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",61);
        MOSCAD_error(message );
        return;
   		}
   		
	p_col_CRcvd2  = (short *)(table_CStat2.ColDataPtr[0]);   		
	p_col_Status2 = (short *)(table_CStat2.ColDataPtr[1]);
	p_col_CLek2   = (short *)(table_CStat2.ColDataPtr[2]);   		
	p_col_CCom2   = (short *)(table_CStat2.ColDataPtr[3]);
	p_col_CErr2   = (short *)(table_CStat2.ColDataPtr[4]);
	
	nTotalRTU = p_col_parInt[66];
	sCP.nRtuNum = nTotalRTU;				/* Osszes RTU szama, a parancskuldes szempontjabol */

	/* Statisztikak */			
	nStatTblIndx = 4;	
	if (MOSCAD_get_table_info (nStatTblIndx,&table_Stat)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nStatTblIndx);
        MOSCAD_error(message );
        return;
   		}
	p_col_Stat = (short *)(table_Stat.ColDataPtr[0]);				


} /* end fnReadPar()*/
/********************************************************************************/
/* Elloallitja az adott indexehez tartozó értéket								*/
/********************************************************************************/
int value_BX(int nI)
{
	if (nI<250)
	{
		return( p_col_B1[nI]);
	}
	else if (nI<500 && nI>=250)
	{
		return( p_col_B2[nI-250]);
	}
return 0;	
} /* end value_B1 */

/********************************************************************************/
/* Elloallitja az adott indexehez tartozó értéket								*/
/********************************************************************************/
int value_CErrX(int nI)
{
	if (nI<250)
	{
		return( p_col_CErr1[nI]);
	}
	else if (nI<500 && nI>=250)
	{
		return( p_col_CErr2[nI-250]);
	}
return 0;	
} /* end value_CErrX */

/********************************************************************************/
/* Elloallitja az adott indexehez tartozó értéket								*/
/********************************************************************************/
int value_CComX(int nI)
{
	if (nI<250)
	{
		return( p_col_CCom1[nI]);
	}
	else if (nI<500 && nI>=250)
	{
		return( p_col_CCom2[nI-250]);
	}
return 0;	
} /* end value_CComX */


/********************************************************************************/
/* Elloallitja az adott indexehez tartozó értéket								*/
/********************************************************************************/
int value_CRcvdX(int nI)
{
	if (nI<250)
	{
		return( p_col_CRcvd1[nI]);
	}
	else if (nI<500 && nI>=250)
	{
		return( p_col_CRcvd2[nI-250]);
	}
return 0;	
} /* end value_CRcvdX */


/********************************************************************************/
/* Elloallitja az adott indexehez tartozó értéket								*/
/********************************************************************************/
int value_CLekX(int nI)
{
	if (nI<250)
	{
		return( p_col_CLek1[nI]);
	}
	else if (nI<500 && nI>=250)
	{
		return( p_col_CLek2[nI-250]);
	}
return 0;	
} /* end value_CLekX */


/********************************************************************************/
/* Modositja az adott indexehez tartozó értéket								*/
/********************************************************************************/
void setvalue_CErrX(int nI, int nValue)
{
	if (nI<250)
	{
		p_col_CErr1[nI]=nValue;
	}
	else if (nI<500 && nI>=250)
	{
		p_col_CErr2[nI-250]=nValue;
	}
	

} /* end setvalue_CErrX */

/********************************************************************************/
/* Modositja az adott indexehez tartozó értéket								*/
/********************************************************************************/
void setvalue_CStatusX(int nI, int nValue)
{
	if (nI<250)
	{
		p_col_Status1[nI]=nValue;
	}
	else if (nI<500 && nI>=250)
	{
		p_col_Status2[nI-250]=nValue;
	}
	
	
} /* end setvalue_StatusX */

/********************************************************************************/
/* Modositja az adott indexehez tartozó értéket								*/
/********************************************************************************/
void setvalue_CComX(int nI, int nValue)
{
	if (nI<250)
	{
		p_col_CCom1[nI]=nValue;
	}
	else if (nI<500 && nI>=250)
	{
		p_col_CCom2[nI-250]=nValue;
	}
	
	
} /* end setvalue_CComX */

/********************************************************************************/
/* Modositja az adott indexehez tartozó értéket								*/
/********************************************************************************/
void setvalue_CRcvdX(int nI, int nValue)
{
	if (nI<250)
	{
		p_col_CRcvd1[nI]=nValue;
	}
	else if (nI<500 && nI>=250)
	{
		p_col_CRcvd2[nI-250]=nValue;
	}
	
	
} /* end setvalue_CRcvdX */

/********************************************************************************/
/* Modositja az adott indexehez tartozó értéket								*/
/********************************************************************************/
void setvalue_LiX(int nI, int nValue)
{
	if (nI<250)
	{
		p_col_Li1[nI]=nValue;
	}
	else if (nI<500 && nI>=250)
	{
		p_col_Li2[nI-250]=nValue;
	}
	
	
} /* end setvalue_LiX */

/********************************************************************************/
/* Modositja az adott indexehez tartozó értéket								*/
/********************************************************************************/
void setvalue_CLekX(int nI, int nValue)
{
	if (nI<250)
	{
		p_col_CLek1[nI]=nValue;
	}
	else if (nI<500 && nI>=250)
	{
		p_col_CLek2[nI-250]=nValue;
	}

	
} /* end setvalue_CLekX */
/********************************************************************************/
/* Modositja a valid/invalid statust a kommunikacios statusztol fuggoen			*/
/* Bemenetek: 																	*/
/*				- nI: az adott RTU-hoz tartozo index a site tablaban			*/
/*				- nValue: VALID (1) vagy INVALID (0)							*/
/********************************************************************************/
void fnSetStatus(int nI, int nValue)
{
int		nJ;

	        /* MOSCAD_sprintf(message,"sTAL[nI].nNMNum: %d, sTAL[nI].nIEC_NM: %d, nI: %d",sTAL[nI].nNMNum,sTAL[nI].nIEC_NM,nI);
	        MOSCAD_error(message ); */
	

if (sTI[nI].nType == TYP_TAL) /* TALUS-os allomas eseten --------------------------*/
	{
		/* Egy bites jelzesek */
		for (nJ=0;nJ<32;nJ++)
		{
			fnWriteSPStatus( nJ+sTAL[nI].nIEC_SP, nValue);
		}
		
		fnWriteSPStatus( sTAL[nI].nIEC_OsszevontHiba, nValue);
		
		if (sTAL[nI].nKommStatusNum>0)
		{
			for (nJ=0;nJ<sTAL[nI].nKommStatusNum;nJ++)
			{
				fnWriteSPStatus( nJ + sTAL[nI].nIEC_MT_KommHiba, nValue);
			}
		}
		else if(sTAL[nI].nKommStatusNum==0)
		{
			fnWriteSPStatus( sTAL[nI].nIEC_MT_KommHiba, nValue);
		}
		
		if (sTAL[nI].nSP_EXTRA_OFFSET>0)
		{
			for (nJ=0;nJ<sTAL[nI].nSP_EXTRA_NUM;nJ++)
			{
				fnWriteSPStatus( nJ + sTAL[nI].nSP_EXTRA_OFFSET, nValue);
			}
		}

		
		/* Ket bites jelzesek */

		for (nJ=0;nJ<4;nJ++)
		{

			fnWriteDPStatus( nJ+sTAL[nI].nIEC_DP, nValue);
		}
		
		if (sTAL[nI].nIEC_DP_FSZ1>0)
		{
			for (nJ=0;nJ<4;nJ++)
			{
				fnWriteDPStatus( nJ+sTAL[nI].nIEC_DP_FSZ1, nValue);
			}
		}

		if (sTAL[nI].nIEC_DP_2BIT1>0)
		{
			fnWriteDPStatus( sTAL[nI].nIEC_DP_2BIT1, nValue);
		}
		if (sTAL[nI].nIEC_DP_2BIT2>0)
		{
			fnWriteDPStatus( sTAL[nI].nIEC_DP_2BIT2, nValue);
		}

		if (sTAL[nI].nIEC_DP_12BIT1>0)
		{
			fnWriteDPStatus( sTAL[nI].nIEC_DP_12BIT1, nValue);
		}
		
		if (sTAL[nI].nIEC_DP_12BIT1>0)
		{
			fnWriteDPStatus( sTAL[nI].nIEC_DP_12BIT1, nValue);
		}
		
		if (sTAL[nI].nDP_EXTRA_OFFSET>0)
		{
			for (nJ=0;nJ<sTAL[nI].nDP_EXTRA_NUM;nJ++)
			{
				fnWriteDPStatus( nJ+sTAL[nI].nDP_EXTRA_OFFSET, nValue);

			}
		}

		/* Meresek ------------------------------------------*/

		if (sTAL[nI].nIEC_NM>0)
		{
			for (nJ=0;nJ<sTAL[nI].nNMNum;nJ++)
			{
				fnWriteNMStatus( nJ+sTAL[nI].nIEC_NM, nValue);
			}
		}


	
	} /* end if TYP_TAL */
	
if (sTI[nI].nType == TYP_MOT || sTI[nI].nType == TYP_TMOK || sTI[nI].nType == TYP_MOT2 || sTI[nI].nType == TYP_TMOK2) /* MOTOROLA-s allomas eseten --------------------------*/
	{
		/* Egy bites jelzesek --------------------------------*/
		for (nJ=0;nJ<sMOT[nI].nIEC_SP_NUM;nJ++)
		{
			fnWriteSPStatus( nJ+sMOT[nI].nIEC_SP, nValue);
		}
		if (sMOT[nI].nIEC_SP_FLAG>0)
		{
			for (nJ=0;nJ<sMOT[nI].nIEC_SP_FLAG_NUM;nJ++)
			{
				fnWriteSPStatus( nJ+sMOT[nI].nIEC_SP_FLAG, nValue);
			}
		}

		/* Ket bites jelzesek --------------------------------*/
		for (nJ=0;nJ<sMOT[nI].nIEC_DP_NUM;nJ++)
		{
			fnWriteDPStatus( nJ+sMOT[nI].nIEC_DP, nValue);
		}
		if (sMOT[nI].nIEC_DP_FSZ1>0)
		{
			for (nJ=0;nJ<sMOT[nI].nIEC_DP_FSZ_NUM;nJ++)
			{
				fnWriteDPStatus( nJ+sMOT[nI].nIEC_DP_FSZ1, nValue);
			}
		}

		/* Meresek --------------------------------*/
		if (sMOT[nI].nIEC_NM>0)
		{
			for (nJ=0;nJ<sMOT[nI].nNMNum;nJ++)
			{
				fnWriteNMStatus( nJ+sMOT[nI].nIEC_NM, nValue);
			}
		}
		

	} /* end if type == TYP_MOT vagy TYP_TMOK*/
	
	if (nI==6) /*Gyor G1 allomas*/
	{
		for (nJ=0;nJ<20;nJ++)
		{
			fnWriteNMStatus( nJ+14, nValue);
		}
		for (nJ=0;nJ<7;nJ++)
		{
			fnWriteDPStatus( nJ+19, nValue);
		}
		for (nJ=0;nJ<16;nJ++)
		{
			fnWriteSPStatus( nJ+4798, nValue);
		}
		/*Motorola-Talus komm. status  */
		for (nJ=0;nJ<16;nJ++)
		{
			fnWriteSPStatus( 122, nValue);
		}
		
		
	}
	
	
} /* end fnSetStatus */

/****************************************************************************/
/* TMOK2 allomas adatfeldolgozas, 3 fázisáram méréssel											*/
/****************************************************************************/
void TMOK_DATA2(STATION_DESC_MOT	*pMOT, unsigned char *rx_buf)
{
int		nI;	

int		nIEC_Offset;

int		nDPTblIndx;
int		nMOSCAD_OffsetDP;

int		nNMStart;

int		nDPStart;
unsigned int		nData;

int		nVal;

int		nMin;
int		nMs1;
int		nMs2;




        MOSCAD_sprintf(message,"TMOK2 data: %d",rx_buf[5]);
        MOSCAD_error(message );



	p_col_RxBuf = (short *)(rx_buf);	




 		nMin		 = p_col_RxBuf[9] & 0xff;
		nMs1		 = p_col_RxBuf[10] & 0xff;
		nMs2		 = p_col_RxBuf[10] >>8;

 





	/* Mérések feldolgozása ----------------------------------------------------------------------------------------*/
	/*  !!!!! Ha LiveZero = 1, akkor azt a letra programban kell jelezni !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	for (nI=0; nI < pMOT->nNMNum && nI<4; nI++)
	{
		nNMStart = pMOT->nIEC_NM;
		if (nNMStart>0)
		{		
	   		/*p_col_NM     = (short *)(table_NM.ColDataPtr[0]);
		   	p_col_NM_LZ  = (short *)(table_NM.ColDataPtr[1]);
			p_col_NM[nNMStart+nI] = p_col_RxBuf[4+nI];*/
			
			fnWriteNM( nNMStart+nI,p_col_RxBuf[5+nI]);			
			
		}
	} /*end for*/

	/*  !!!!! Ha LiveZero = 1, akkor azt a letra programban kell jelezni !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	for (nI=0; nI < pMOT->nNMNum2 && nI<4; nI++)
	{
		nNMStart = pMOT->nIEC_NM2;
		if (nNMStart>0)
		{		
			
			fnWriteNM( nNMStart+nI,p_col_RxBuf[15+nI]);			
			
		}
	} /*end for*/

	
/* Egybites jelzések feldolgozása ----------------------------------------------------------------------------------------*/
if (pMOT->nIEC_SP_NUM > 0)
{
	for (nI=0; nI < pMOT->nIEC_SP_NUM && nI<16; nI++)
	{

		
		nIEC_Offset = pMOT->nIEC_SP + nI;
		nData = p_col_RxBuf[2];
		
		nVal = (nData << nI) & 0x8000;		
		fnWriteSPData(nIEC_Offset,nVal,  nMs1,nMs2,nMin,1);			
			
	} /*end for*/
	
	
	for (nI=16; nI < pMOT->nIEC_SP_NUM && nI<32; nI++)
	{		
		nIEC_Offset = pMOT->nIEC_SP + nI;
		nData = p_col_RxBuf[3];
		
		nVal = (nData << (nI-16)) & 0x8000;		
		fnWriteSPData(nIEC_Offset,nVal,  nMs1,nMs2,nMin,1);			
			
	} /*end for*/
	
	
} /*end if*/

/* Kétbites állásjelzések, feldolgozása ----------------------------------------------------------------------------------------*/
/* A program feltetelezi, hogy a ketbites jelzesek a 8. szotol kezdodnek az RxBuf-ban*/

		
	nDPStart = 	pMOT->nIEC_DP;
	
	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);

	/* 2 bites */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}

	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
	p_col_DP_MS1  = (short *)(table_DP.ColDataPtr[2]);
	p_col_DP_MS2  = (short *)(table_DP.ColDataPtr[3]);
	p_col_DP_MIN  = (short *)(table_DP.ColDataPtr[4]);
	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						

	nData = p_col_RxBuf[4];	
	
if (	nDPStart > 0)
{
	for (nI=0; nI < pMOT->nIEC_DP_NUM && nI<8; nI++)
	{	
		
		nVal = (nData << nI*2) & 0x8000;
 										
			/* Perc beirasa */		
			p_col_DP_MIN[nDPStart+nI - nMOSCAD_OffsetDP] = nMin;	
															
			/* MS1 beirasa */		
			p_col_DP_MS1[nDPStart+nI- nMOSCAD_OffsetDP] = nMs1;
						
			/* MS2 beirasa */		
			p_col_DP_MS2[nDPStart+nI- nMOSCAD_OffsetDP] = nMs2;
 				 				
 				
 				if (nVal > 0)
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}
	
 		
				nVal = (nData << (nI*2+1)) & 0x8000;
				
				if (nVal > 0)
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}		 		
					
			/* A kapott idõt kell használni */
			p_col_DP_CT[nDPStart+nI- nMOSCAD_OffsetDP]	 = 1;	

	}
}/*end if*/	
} /*TMOK_DATA2*/
/*-----------------------------------------------------------------------------------------------*/


/****************************************************************************/
/* A program feladata: a paraméterként (index) megadott TMOK-k állapotváltozását 
elküldi a szintén paraméterként megadott RTU-knak (szintén indexel megadva)
- Az RTU-knak szerepelnie kell a site táblában!!!
- A reteszes TMOK-k száma is paraméter
- Az élesítve parancs értéke 1, a bénítva parancs értéke 2 
- A függvényt az rx() függvény végén célszerû meghívni
- cprog2.c ki lett egészítve 2 db. függvénnyel ( fnReadDPData, fnWriteDPData )
- Ha az RTU másik front endben van, akkor a távirat 3 szó hosszúságú, a 3. szó az állásjelzés offsete

																				*/
/****************************************************************************/
void fnRetesz(void)
{
#define  			RETESZ_TMOK_NUM		25	
#define  			RETESZ_RTU_NUM		10	
#define  			TX_LENGTH			3	


	
unsigned int		ReteszesTMOKNum;									/* Reteszes TMOK-k száma az adott front-endben */
unsigned int		ReteszesRTUIndex[RETESZ_TMOK_NUM][RETESZ_RTU_NUM];	/* A reteszes TMOK-khoz tartozó RTU-k indexei a site táblában */
unsigned int		ReteszesTMOK_RTUNum[RETESZ_TMOK_NUM];				/* Adott reteszes TMOK-khoz tartozó RTU-k száma */
unsigned int		ReteszAllapotokKezdoCim;							/* Retesz állapotok kezdõcíme az IEC táblában */
unsigned int		ReteszParancsokKezdoCim;							/* Retesz élesítés/bénítás parancsok kezdõcíme az IEC táblában */
unsigned int		TMOKAllasjelzesOffsetek[RETESZ_TMOK_NUM];			/* Reteszes TMOK-k állásjelzéseinek az offsete */
unsigned int		TMOK_ID[RETESZ_TMOK_NUM];							/* Reteszes TMOK-k azonosítója a kimenõ táviratban = DP offset */


unsigned int		ReteszAllapotok[RETESZ_TMOK_NUM];
static unsigned int		PrReteszAllapotok[RETESZ_TMOK_NUM];

unsigned int		TMOKAllasjelzesek[RETESZ_TMOK_NUM];


static unsigned int	prevTMOKAllasjelzesek[RETESZ_TMOK_NUM];
unsigned int		i,j;
char				message[500];
int					nDPTblIndx;
int					nOffset;
unsigned short		nTxBuf[80];


short				*p_col_DCAct; 



/**********************************************************************************************************************/
/* Kezdõértékek megadása - minden frontendnél más!!! 																  */
/**********************************************************************************************************************/																													/**/
ReteszAllapotokKezdoCim = 500;  /* DP3, 0 */																		/**/
ReteszParancsokKezdoCim = 770;	/* DC4, 20 */																		/**/
																													/**/
ReteszesTMOKNum = 4;					/* Ennyi reteszfeltételes TMOK van az adott front-endben*/					/**/	
																													/**/
/* 0. TMOK: 90-90 RTU: Front end H -> TMOK -----------------------*/								/**/
TMOKAllasjelzesOffsetek[0] = 301; 		/* Az állásjelzés offsete a DP adatbázisban */								/**/
TMOK_ID[0] =0;						/* TMOK azonosítója a táviratban = DP offset */								/**/															
ReteszesRTUIndex[0][0] = 277;			/* B redundancia */															/**/
ReteszesTMOK_RTUNum[0] = 1;				/* Az adott indexû TMOK ennyi kábelköri állomnással kommunikál */			/**/

/* 1. TMOK: 74-24 RTU: B redundancia     -----------------------*/								/**/
TMOKAllasjelzesOffsetek[1] = 415; 		/* Az állásjelzés offsete a DP adatbázisban */								/**/
TMOK_ID[1] =1;						/* TMOK azonosítója a táviratban = DP offset */								/**/															
ReteszesRTUIndex[1][0] = 277;			/* B redundancia */															/**/
ReteszesTMOK_RTUNum[1] = 1;				/* Az adott indexû TMOK ennyi kábelköri állomnással kommunikál */			/**/
																													/**/

/* 2. TMOK: 10-24 RTU: Front end F     -----------------------*/								/**/
TMOKAllasjelzesOffsetek[2] = 422; 		/* Az állásjelzés offsete a DP adatbázisban */								/**/
TMOK_ID[2] =1251;						/* TMOK azonosítója a táviratban = DP offset */								/**/															
ReteszesRTUIndex[2][0] = 275;			/* F Front end*/															/**/
ReteszesTMOK_RTUNum[2] = 1;				/* Az adott indexû TMOK ennyi kábelköri állomnással kommunikál */			/**/
																													/**/
/* 3. TMOK: 11-35 RTU: Front end H -> Tét, 055-39 -----------------------*/								/**/
TMOKAllasjelzesOffsetek[3] = 385; 		/* Az állásjelzés offsete a DP adatbázisban */								/**/
TMOK_ID[3] =1256;						/* TMOK azonosítója a táviratban = DP offset */								/**/															
ReteszesRTUIndex[3][0] = 276;			/* H front end */															/**/
ReteszesTMOK_RTUNum[3] = 1;				/* Az adott indexû TMOK ennyi kábelköri állomnással kommunikál */			/**/
                                                          
/**********************************************************************************************************************/
/**********************************************************************************************************************/


/* Retesz bénítás/élesítés parancsok kezelése *************************************************************************/	
   	for (i=0;i<RETESZ_TMOK_NUM;i++)
   	{
		/* Elõállítja az offsetbõl a DC tábla indexét, a tábla elsõ eleméhez képesti offsetet, a parancsoszlop pointerét*/
   		fnDCTblIndx(ReteszParancsokKezdoCim+i, &nDCTblIndx, &nOffset, &p_col_DCAct);
   		
   		/* Ha jött egy élesítés parancs */
   		if (p_col_DCAct[ReteszParancsokKezdoCim+i-nOffset]==1)
   		{
   			
   			/* Beírja az éles állapotot a megfelelõ helyre*/
   			fnWriteDPData(ReteszAllapotokKezdoCim+i,1, 0, 0, 0, 0);
   			
        	MOSCAD_sprintf(message,"Retesz állapot -  cím: %d, érték: %d", ReteszAllapotokKezdoCim+i,p_col_DCAct[ReteszParancsokKezdoCim+i-nOffset]);
        	MOSCAD_error(message );
        	
        	/* Visszatörli a parancsot*/
        	p_col_DCAct[ReteszParancsokKezdoCim+i-nOffset]=0;

   			
   			
   		} /* end if */
   		
   		/* Ha jött egy bénítás parancs */
   		if (p_col_DCAct[ReteszParancsokKezdoCim+i-nOffset]==2)
   		{
   			/* Beírja a bénítva állapotot a megfelelõ helyre*/
   			fnWriteDPData(ReteszAllapotokKezdoCim+i,2, 0, 0, 0, 0);

        	MOSCAD_sprintf(message,"Retesz állapot, cím %d, érték: %d", ReteszAllapotokKezdoCim+i,p_col_DCAct[ReteszParancsokKezdoCim+i-nOffset]);
        	MOSCAD_error(message );
        	
        	/* Visszatörli a parancsot*/
        	p_col_DCAct[ReteszParancsokKezdoCim+i-nOffset]=0;

   			
   		} /* end if */
   	} /* end for */
	
	

/* Elõállítja a reteszes TMOK-k állásjelzéseinek a tömbjét *************************************************/

for (i=0;i<ReteszesTMOKNum;i++)
{	
	
	if (TMOKAllasjelzesOffsetek[i]<1500)
	{				
		TMOKAllasjelzesek[i] = fnReadDPData(TMOKAllasjelzesOffsetek[i], 0, 0, 0, 0);
	} /* end if */
	
} /* end for */



/* Elõállítja a retesz állapotok tömbjét ********************************************************************************************/
for (i=0;i<ReteszesTMOKNum;i++)
{
		ReteszAllapotok[i] = fnReadDPData(ReteszAllapotokKezdoCim+i, 0, 0, 0, 0);	
} /* end for */



/* Ha változott az állásjelzés és nincs bénítva a retesz, akkor elküldi a TMOK állásjelzését a kiserõmûnek (RTU-nak), vagy egy másik front endnek *****************/
for (i=0;i<ReteszesTMOKNum ;i++)
{
	if( ((TMOKAllasjelzesek[i] != prevTMOKAllasjelzesek[i]) && ( ReteszAllapotok[i] != 2 ) ) || (ReteszAllapotok[i] == 1 && PrReteszAllapotok[i]!=1) )
	{
		/* elküldi az állapotot a kiserõmûnek */
		for (j=0;j<ReteszesTMOK_RTUNum[i] ;j++)
		{

   		   	nTxBuf[0] = 100; /* Ugyanaz, mintha TMOK lenne */				
   		   	nTxBuf[1] = TMOKAllasjelzesek[i] ; /* << 14; Ez a formátum jön a TMOK-ból*/    	
   		   	nTxBuf[2] = TMOK_ID[i];    	
   		   		
   		   	
 		   	MOSCAD_sprintf(message,"Állásjelzés küldése, index: %d, Value: %d, i: %d, j: %d,nTxBuf[1]: %d ,nTxBuf[2]: %d ",ReteszesRTUIndex[i][j],TMOKAllasjelzesek[i],i,j,nTxBuf[1],nTxBuf[2] );
   			MOSCAD_error(message ); 
 
   		   	
			/* Tavirat elkuldese */
			
	 		  	if (MOSCAD_TxFrm(ReteszesRTUIndex[i][j], nTxBuf, TX_LENGTH*2) !=0 )
 			  	{
					MOSCAD_sprintf(message,"Could not send parancs ,index: %d",ReteszesRTUIndex[i][j]);
   				 	MOSCAD_error(message ); 				
   				}     		    			
		} /* end for*/
	} /* end if */


	if(  ReteszAllapotok[i] == 2 && PrReteszAllapotok[i]!=2 ) /* Ha retesz élesítésre vált akkor nulláz */
	{
		/* elküldi a nulla állapotot a kiserõmûnek */
		for (j=0;j<ReteszesTMOK_RTUNum[i] ;j++)
		{

   		   	nTxBuf[0] = 100; /* Ugyanaz, mintha TMOK lenne */				
   		   	nTxBuf[1] = 0; /* Nullázza az állásjelzést */    	
   		   	nTxBuf[2] = TMOK_ID[i];    	
   		   		
   		   	
 		   	MOSCAD_sprintf(message,"Állásjelzés nullázás, index: %d, Value: %d, i: %d, j: %d,nTxBuf[1]: %d ",ReteszesRTUIndex[i][j],TMOKAllasjelzesek[i],i,j,nTxBuf[1] );
   			MOSCAD_error(message ); 
 
   		   	
			/* Tavirat elkuldese */
			
	 		  	if (MOSCAD_TxFrm(ReteszesRTUIndex[i][j], nTxBuf, TX_LENGTH*2) !=0 )
 			  	{
					MOSCAD_sprintf(message,"Could not send parancs ,index: %d",ReteszesRTUIndex[i][j]);
   				 	MOSCAD_error(message ); 				
   				}     		    			
		} /* end for*/	
	} /* end if */



/* Mindenképpen frissíti az állásjelzések tömbjét 	*/
prevTMOKAllasjelzesek[i] = TMOKAllasjelzesek[i] ;
PrReteszAllapotok[i]=ReteszAllapotok[i];	
} /* end for */

	
} /* end fnRetesz ********************************************************************************************************************************/


/****************************************************************************/
/* Front end adatfogadás egy másik front endbõl, az új típusú reteszkezelés miatt										*/
/****************************************************************************/
void FRONTEND_DATA( unsigned char *rx_buf)
{
int		nI;	

int		nIEC_Offset;

int		nDPTblIndx;
int		nMOSCAD_OffsetDP;

int		nNMStart;

int		nDPStart;
unsigned int		nData;

int		nVal;

int		nMin;
int		nMs1;
int		nMs2;







	p_col_RxBuf = (short *)(rx_buf);	

        MOSCAD_sprintf(message,"Front end data: %d %d %d",p_col_RxBuf[0],p_col_RxBuf[1],p_col_RxBuf [2]);
        MOSCAD_error(message );


/* Kétbites állásjelzések, feldolgozása ----------------------------------------------------------------------------------------*/
/* A program feltetelezi, hogy a ketbites jelzesek a 1. szotol kezdodnek az RxBuf-ban, a DP offset pedig a 2. szóban van*/

		
	nDPStart = 	p_col_RxBuf[2];


if (nDPStart<1500)
{	
	/* DP tabla indexe, es offsete */
	fnDPTblIndx(nDPStart,&nDPTblIndx,&nMOSCAD_OffsetDP);



	/* 2 bites */
   	if (MOSCAD_get_table_info (nDPTblIndx,&table_DP)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
        MOSCAD_error(message );
        return;
   		}

	p_col_DPH     = (short *)(table_DP.ColDataPtr[0]);			/* DPH -> CLOSE */
	p_col_DPL     = (short *)(table_DP.ColDataPtr[1]);			/* DPL -> OPEN */
	p_col_DP_MS1  = (short *)(table_DP.ColDataPtr[2]);
	p_col_DP_MS2  = (short *)(table_DP.ColDataPtr[3]);
	p_col_DP_MIN  = (short *)(table_DP.ColDataPtr[4]);
	p_col_DP_CT   = (short *)(table_DP.ColDataPtr[5]); 						

	nData = p_col_RxBuf[1];	
	

	
	
if (	nDPStart > 0)
{
	for (nI=0; nI < 1 && nI<2; nI++)
	{	
		
				nVal = (nData << nI*2) & 0x0002;
 										
 				 				
 				
 				if (nVal > 0)
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPH[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}
	
 		
				nVal = (nData << (nI*2+1)) & 0x0002;
				
				if (nVal > 0)
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 1;
					}
					else
					{
						p_col_DPL[nDPStart+nI- nMOSCAD_OffsetDP]= 0;
					}		 		
										
					
	    MOSCAD_sprintf(message,"Front end data: nDPTblIndx: %d nMOSCAD_OffsetDP: %d nData: %d, nVal: %d",nDPTblIndx,nMOSCAD_OffsetDP,nData, nVal);
        MOSCAD_error(message );
					
	}
 }/*end if*/	
} /* end if */


} /* FRONTEND data*/
/*-----------------------------------------------------------------------------------------------*/


/****************************************************************************/
/* DP állapot lekérdezésre adott válasz 
Az RTU indítja a lekérdezést, amikor újraindul, hogy kezdeti értéket kapjanak 
az állásjelzések
[0]: 100
[1]: DP offsete											*/
/****************************************************************************/
void fnDP_LEK( unsigned char *rx_buf, int nSite_ID)
{

	
	unsigned short          *p_col_RxBuf;
	unsigned short			nDP;
	int						nOffset;
	unsigned short		nTxBuf[80];	
	
		p_col_RxBuf = (short *)(rx_buf);	

		nOffset = p_col_RxBuf[1];

        MOSCAD_sprintf(message,"DP lekérdezés: %d %d %d",p_col_RxBuf[0],p_col_RxBuf[1],p_col_RxBuf[2]);
        MOSCAD_error(message );
        
        
 if (nOffset <1500)
 {
	nDP=fnReadDPData(nOffset, 0, 0, 0, 0);
	
   	nTxBuf[0] = 100; /* Ugyanaz, mintha TMOK lenne */				
   	nTxBuf[1] = nDP; /* << 14;  Ez a formátum jön a TMOK-ból*/ 
   	nTxBuf[2] = p_col_RxBuf[1];    	
   	
   				/* Tavirat elkuldese */
			
	 		  	if (MOSCAD_TxFrm(nSite_ID, nTxBuf, TX_LENGTH*2) !=0 )
 			  	{
					MOSCAD_sprintf(message,"Could not send parancs ,index: %d",nSite_ID);
   				 	MOSCAD_error(message ); 				
   				}   

	
 } /* end if */

	
}
/* end fnDP_LEK ***************************************************************************/

