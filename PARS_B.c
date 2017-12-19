/****************************************************************************
*																			*		
* REV    	DATE     	PROGRAMMER         	REVISION HISTORY                *
* V2.1.1	2007.05.16	Matus Zsolt			60-03 							*
* V2.1.2	2007.06.04	Matus Zsolt			11-10 		1/4 -> 1/5			*
* V2.1.3	2007.06.19	Gergely Zsolt		64-68 		1/6 -> 1/5			*
* V2.1.4	2007.06.28	Gergely Zsolt		50-86 		2/2 -> 2/4			*
* V2.1.5	2007.07.11	Gergely Zsolt		90-63 		9/5 -> 9/6			*
* V2.1.6	2007.07.17	Gergely Zsolt		10-19 		1/4 -> 1/5			*
* V2.1.7	2007.08.01	Gergely Zsolt		37-199 		2/6 -> 2/1			*
* V2.1.8	2008.04.16	Gergely Zsolt		41-99 		3/2 -> 3/1			*
* V2.1.9	2008.08.18	Gergely Zsolt		71-65 		1/5 -> 4/6			*
* V2.1.10	2010.04.29	Gergely Zsolt		86-88 		4/8 -> 4/6			*
* V2.1.11	2011.06.16	Gergely Zsolt		40-70 		5/6 -> 5/7			*
* V2.1.12	2012.01.11	Gergely Zsolt		21-84 		8/6 -> 8/2			*
* V2.1.13	2012.08.27	Gergely Zsolt		64-30 		1/7 -> 1/6			*
* V2.1.14	2012.09.20	Gergely Zsolt		15-50 		1/5 -> 4/6			*
* V2.1.15	2012.09.20	Gergely Zsolt		62-23 		1/5 -> 1/6			*
* V2.1.16	2012.10.16	Gergely Zsolt		10-24 		1/5 -> 1/2			*
* V2.1.17	2012.11.19	Gergely Zsolt		51-53 		2/7 -> 2/3			*
* V2.1.18	2012.12.11	Gergely Zsolt		13-01 		1/4 -> 1/1			*
* V2.1.19	2013.04.10	Gergely Zsolt		61-40 		1/6 -> 1/8			*
* V2.1.20	2013.05.23	Gergely Zsolt		Wolf,Plastic 3/5 -> 3/1			*
* V2.1.21	2013.07.02	Gergely Zsolt		71-65		4/6 -> 4/4	MEGSE		*
* V2.1.22	2013.09.27	Gergely Zsolt		74-24		1/5 -> 1/6	MEGSE		*
* V2.1.23	2013.10.29	Gergely Zsolt		51-42				*
* V2.1.24	2014.03.10	Gergely Zsolt		Kapuvár	DAC RSLINK4 -> LINE1	*
* V2.1.25	2014.03.12	Gergely Zsolt		71-43, 71-44 4/6 -> 2/2			*
* V2.1.26	2014.04.16	Gergely Zsolt		51-41			*
* V2.1.27	2014.04.22	Gergely Zsolt		51-74 2/6 -> 2/3			*
* V2.1.28	2014.06.19	Gergely Zsolt		21-81 8/6 -> 8/3			*
* V2.1.29	2014.07.21	Gergely Zsolt		21-81 8/3 -> 8/6			*
* V2.1.30	2014.08.25	Gergely Zsolt		Bicske	DAC RSLINK19 -> LINE1			*
* V2.1.31	2014.08.26	Gergely Zsolt		Dorog	DAC RSLINK9 -> LINE1			*
* V2.1.32	2014.09.01	Gergely Zsolt		Körmend	DAC RSLINK18 -> LINE1			*
* V2.1.33	2014.09.05	Gergely Zsolt		51-74, 51-01, 50-49, Almádi gázmotor -> Aszófó DAC			*
* V2.1.34	2014.09.08	Gergely Zsolt		51-12 2/2 -> 2/7			*
* V2.1.35	2014.09.22	Gergely Zsolt		PÁPA	DAC RSLINK17 -> LINE1			*
* V2.1.36	2014.10.01	Gergely Zsolt		SÜMEG	DAC RSLINK14 -> LINE1			*
* V2.1.37	2014.10.01	Gergely Zsolt		15-55 1/1		*
* V2.1.38	2014.11.14	Gergely Zsolt		Sopronkövesd	DAC RSLINK -> LINE1			*
* V2.1.39	2014.08.26	Gergely Zsolt		Dorog	DAC LINE1 -> RSLINK9 			*
* V2.1.40	2014.08.26	Gergely Zsolt		Esztergom	DAC Radio8/4 -> LINE1 			*
* V2.1.41	2015.03.24	Gergely Zsolt		42-12, 41-70  -> Radio7/5 			*
* V2.1.42	2015.04.02	Gergely Zsolt		Körmend	DAC LINE1 -> RSLINK18 			*
* V2.1.43	2015.04.09	Gergely Zsolt		11-54, 15-50, 71-65, 71-91 			*
* V2.1.44	2015.04.10	Gergely Zsolt		66-92 		Radio5_1	*
* V2.1.45	2015.08.07	Gergely Zsolt		Dorog DAC  RSLINK9 -> LINE1			*
* V2.1.46	2015.10.27	Gergely Zsolt		Veszprém DAC  RSLINK13 -> LINE1			*
* V2.1.47	2015.11.23	Gergely Zsolt		Körmend DAC   -> LINE1			*
* V2.1.48	2016.04.19	Gergely Zsolt		Kékkút, kábelköri Radio9/9			*
* V2.1.49	2016.09.20	Gergely Zsolt		71-43 2/6			*
* V2.1.50	2016.09.26.	Gergely Zsolt		87-40, 87-43, 31-67, 87-34, 87-90			*




****************************************************************************
* NAME           :  PARS_B.c                                                 *
* DESCRIPTION    :  
* PROCESS        :  
*                                                                            *
* [C] Copyright Zsolt Gergely,  2003.  All Rights Reserved                 *
*                                                                            *
* REV    DATE     PROGRAMMER         REVISION HISTORY                        *
* 2.0   2013.04.11 Gergely Zsolt	Checking dynamic site table				 *
*									Write non-zero to 4th table, 16th row 
*****************************************************************************/

#include "CAPPLIC.H"
#include <stdio.h>
/* Parameterek strukturaja */
#include "strPar.H"




/*--------------------------------------------------------------------------*/
/* Prototypes and defines                                                   */
/*--------------------------------------------------------------------------*/


extern void fnSCTblIndx(int nIECOffset, int *nSCTblIndx, int *nOffset, short **p_col_SCAct);

/**********************************************/
/* Globals                                     */
/**********************************************/
/*extern STATION_DESC_MOT		sMOT[];
extern STATION_DESC_TALUS	sTAL[];
extern STATION_TYPE_INDEX 	sTI[];*/

extern COM_PAR				sCP;
/*extern STATION_COMM_DATA	sCD[];*/
/*extern RTU_RAD				sRAD;*/
/*extern RTU_LIN				sLIN;)*/
extern unsigned short		nNumOfSites;
/*extern unsigned short		ST[0].nSiteList[];
extern unsigned short		ST[0].nLinkList[];*/
/*unsigned char		byComStat[250];*/
extern int					nTotalRTU;

/*extern RTU_RAD_NEW			ST[0].ssRAD_K1;
extern RTU_RAD_NEW			ST[0].sRAD_K2;
extern RTU_RAD_NEW			ST[0].sRAD_K3;*/

extern void setdat2(unsigned char *input);


CB_TABLE_INFO   table_ParStat;
short          *p_col_ParStat;

/*--------------------------------------------------------------------------*/
/* The list of the function included in this block                          */
/*--------------------------------------------------------------------------*/
/*const CB_JUMPTBL user_jumptable[]=
{
   {"setd2"   , setdat2},  	
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
void setdat2(unsigned char *input)
{
unsigned short	nSiteId[100];
unsigned char	cLinkId[100];
unsigned char	message[500];
int				nI;

unsigned short	nSiteIdCheck[100];



	TOTAL_PAR			*ST;
	
	

	ST = (TOTAL_PAR *)input;


	/* Statisztikák tábla */	
   	if (MOSCAD_get_table_info (4,&table_ParStat)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",4);
        MOSCAD_error(message );
        return;
   		}
	p_col_ParStat = (short *)(table_ParStat.ColDataPtr[0]);	 




/*nNumOfSites=250;*/

ST[0].nSiteList[0]	=3000; 	ST[0].nLinkList[0]	=LINE1;	/* Veszprem atjatszo*/
ST[0].nSiteList[1]	=3001;	ST[0].nLinkList[1]	=RADIO2_1;	/* RADIO2_1, Veszprem NATO				VESZ*/
ST[0].nSiteList[2]	=42;	ST[0].nLinkList[2]	=LINE1;		/* Kapuvar atjatszo	 RSLINK4					GYR*/
ST[0].nSiteList[3]	=41;	ST[0].nLinkList[3]	=RADIO1_4;	/* Nyul domb atjatszo					GYR*/
ST[0].nSiteList[4]	=31;	ST[0].nLinkList[4]	=LINE1;		/* Tapolca atjatszo	*/
ST[0].nSiteList[5]	=32;	ST[0].nLinkList[5]	=RADIO9_1;	/* Tapolca, Kazinczy II.				TAP*/
ST[0].nSiteList[6]	=33;	ST[0].nLinkList[6]	=RADIO1_4;	/* Gyor G1								GYR*/
ST[0].nSiteList[7]	=28;	ST[0].nLinkList[7]	=LINE1;  	/* Esztergom atjatszo*/
ST[0].nSiteList[8]	=29;	ST[0].nLinkList[8]	=RADIO7_1;	/* Esztergom, Vasary RADIO8_1			ESZT*/
ST[0].nSiteList[9]	=60;	ST[0].nLinkList[9]	=RADIO1_6;	/* TMOK, 62-77							GYR*/
ST[0].nSiteList[10]	=3002;	ST[0].nLinkList[10]	=LINE1;	/* Sopronkovesd atjatszo*/
ST[0].nSiteList[11]	=62;	ST[0].nLinkList[11]	=RADIO1_6;	/* TMOK, 64-67 							GYR*/
ST[0].nSiteList[12]	=64;	ST[0].nLinkList[12]	=RADIO3_1;	/* TMOK, 61-71, 		RADIO1_6 		GYR*/
ST[0].nSiteList[13]	=63;	ST[0].nLinkList[13]	=RADIO1_6;	/* TMOK, 61-76, 		RADIO1_6 		GYR*/
ST[0].nSiteList[14]	=61;	ST[0].nLinkList[14]	=RADIO1_6;	/* TMOK, 61-64 							GYR*/
ST[0].nSiteList[15]	=3003;	ST[0].nLinkList[15]	=LINE1;		/* Pápa atjatszo, 		RST[0].sLINK17*/
ST[0].nSiteList[16]	=3005;	ST[0].nLinkList[16]	=RADIO6_1;	/* TMOK, 51-48, 		RADIO2_1 		VESZ*/
ST[0].nSiteList[17]	=3004;	ST[0].nLinkList[17]	=RADIO4_1;	/* Korishegy atjatszo, 	RADIO4_5		PAP*/
ST[0].nSiteList[18]	=69;	ST[0].nLinkList[18]	=RADIO1_6;	/* TMOK 65-13 							GYR*/
ST[0].nSiteList[19]	=71;	ST[0].nLinkList[19]	=RADIO1_6;	/* TMOK 65-14, 			RADIO1_6 		GYR*/
ST[0].nSiteList[20]	=79;	ST[0].nLinkList[20]	=RADIO1_5;	/* TMOK 11-02, 			RADIO1_5 		GYR*/
ST[0].nSiteList[21]	=80;	ST[0].nLinkList[21]	=RADIO4_1;	/* TMOK 11-54, 			RADIO1_5 		GYR*/
ST[0].nSiteList[22]	=82;	ST[0].nLinkList[22]	=RADIO1_5;	/* TMOK 11-78, 			RADIO1_5 		GYR*/
ST[0].nSiteList[23]	=3051;	ST[0].nLinkList[23]	=RADIO1_5;	/* TMOK 10-77, 			RADIO1_5 		GYR*/
ST[0].nSiteList[24]	=3031;	ST[0].nLinkList[24]	=RADIO1_5;	/* TMOK 11-08, 			RADIO1_5 		GYR*/
ST[0].nSiteList[25]	=3032;	ST[0].nLinkList[25]	=RADIO1_5;	/* TMOK 11-87, 			RADIO1_5 		GYR*/
ST[0].nSiteList[26]	=70;	ST[0].nLinkList[26]	=RADIO1_6;	/* TMOK 62-20, 			RADIO1_6 		GYR*/
ST[0].nSiteList[27]	=67;	ST[0].nLinkList[27]	=RADIO1_6;	/* TMOK 64-30, 			RADIO1_6 		GYR*/
ST[0].nSiteList[28]	=68;	ST[0].nLinkList[28]	=RADIO1_6;	/* TMOK 61-62, 			RADIO1_6 		GYR*/
ST[0].nSiteList[29]	=72;	ST[0].nLinkList[29]	=RADIO1_6;	/* TMOK 60-65, 			RADIO1_6 		GYR*/
ST[0].nSiteList[30]	=84;	ST[0].nLinkList[30]	=RADIO5_1;	/* TMOK 60-81, 			RADIO1_6 		GYR*/
ST[0].nSiteList[31]	=3006;	ST[0].nLinkList[31]	=RADIO5_1;	/* TMOK 60-83, 			RADIO1_6 		GYR*/
ST[0].nSiteList[32]	=3033;	ST[0].nLinkList[32]	=RADIO3_3;	/* TMOK 64-17, 			RADIO3_1 		SOP*/
ST[0].nSiteList[33]	=3034;	ST[0].nLinkList[33]	=RADIO3_1;	/* TMOK 41-99, 			RADIO3_1		SOP*/
ST[0].nSiteList[34]	=3035;	ST[0].nLinkList[34]	=RADIO3_4;	/* TMOK 60-17, 			RADIO3_4 		SOP*/
ST[0].nSiteList[35]	=3036;	ST[0].nLinkList[35]	=RADIO3_4;	/* TMOK 60-20, 			RADIO3_7 		SOP*/
ST[0].nSiteList[36]	=3020;	ST[0].nLinkList[36]	=RADIO3_2;	/* TMOK 60-45, 			RADIO3_2 		SOP*/
ST[0].nSiteList[37]	=83;	ST[0].nLinkList[37]	=RADIO4_1;	/* TMOK 11-49, 			RADIO1_5 		GYR*/
ST[0].nSiteList[38]	=3007;	ST[0].nLinkList[38]	=RADIO5_1;	/* TMOK 60-75, 			RADIO1_6 		GYR*/
ST[0].nSiteList[39]	=3008;	ST[0].nLinkList[39]	=RADIO1_6;	/* TMOK 64-72, 			RADIO1_6 		GYR*/
ST[0].nSiteList[40]	=3037;	ST[0].nLinkList[40]	=RADIO3_4;	/* TMOK 60-39, 			RADIO3_4 		SOP*/
ST[0].nSiteList[41]	=81;	ST[0].nLinkList[41]	=RADIO5_1;	/* TMOK 61-11, 			RADIO1_5 		GYR*/
ST[0].nSiteList[42]	=78; 	ST[0].nLinkList[42]	=RADIO5_1;	/* TMOK 61-08, 			RADIO1_5 		GYR*/
ST[0].nSiteList[43]	=3009;	ST[0].nLinkList[43]	=RADIO1_6;	/* TMOK 61-36, 			RADIO1_6 		GYR*/
ST[0].nSiteList[44]	=3010;	ST[0].nLinkList[44]	=RADIO1_6;	/* TMOK 61-37, 			RADIO1_6 		GYR*/
ST[0].nSiteList[45]	=3023;	ST[0].nLinkList[45]	=RADIO1_1;	/* TMOK 13-01, 			RADIO1_5 		GYR*/
ST[0].nSiteList[46]	=3024;	ST[0].nLinkList[46]	=RADIO1_4;	/* TMOK 13-96, 			RADIO1_5 		GYR*/
ST[0].nSiteList[47]	=3038;	ST[0].nLinkList[47]	=RADIO3_1;	/* TMOK 65-08, 			RADIO3_4 		GYR*/
ST[0].nSiteList[48]	=3039;	ST[0].nLinkList[48]	=RADIO3_4;	/* TMOK 60-07, 			RADIO3_4 		SOP*/
ST[0].nSiteList[49]	=3040;	ST[0].nLinkList[49]	=RADIO3_4;	/* TMOK 60-05, 			RADIO3_4 		SOP*/
ST[0].nSiteList[50]	=3041;	ST[0].nLinkList[50]	=RADIO3_4;	/* TMOK 60-03, 			RADIO3_6 		SOP*/
ST[0].nSiteList[51]	=57; 	ST[0].nLinkList[51]	=RADIO5_1;	/* TMOK 66-92, 			RADIO1_5 		GYR*/
ST[0].nSiteList[52]	=59;	ST[0].nLinkList[52]	=RADIO5_1;	/* TMOK 60-97, 			RADIO1_5 		GYR*/
ST[0].nSiteList[53]	=3011;	ST[0].nLinkList[53]	=RADIO1_8;	/* TMOK 61-38, 			RADIO1_6 		GYR*/
ST[0].nSiteList[54]	=3012;	ST[0].nLinkList[54]	=RADIO1_6;	/* TMOK 64-31, 			RADIO1_6 		GYR*/
ST[0].nSiteList[55]	=3025;	ST[0].nLinkList[55]	=RADIO1_5;	/* TMOK 10-23, 			RADIO1_5 		GYR*/
ST[0].nSiteList[56]	=3026;	ST[0].nLinkList[56]	=RADIO1_4;	/* TMOK 10-26, 			RADIO1_5 		GYR*/
ST[0].nSiteList[57]	=3042;	ST[0].nLinkList[57]	=RADIO3_4;	/* TMOK 60-02, 			RADIO3_4 		SOP*/
ST[0].nSiteList[58]	=58;	ST[0].nLinkList[58]	=RADIO5_1;	/* TMOK 61-19, 			RADIO1_5 		GYR*/
ST[0].nSiteList[59]	=56;	ST[0].nLinkList[59]	=RADIO5_1;	/* TMOK 61-05, 			RADIO1_5 		GYR*/
ST[0].nSiteList[60]	=3013;	ST[0].nLinkList[60]	=RADIO1_6;	/* TMOK 64-68, 			RADIO1_6 		GYR*/
ST[0].nSiteList[61]	=3014;	ST[0].nLinkList[61]	=RADIO5_1;	/* TMOK 62-81, 			RADIO1_6 		GYR*/
ST[0].nSiteList[62]	=3015;	ST[0].nLinkList[62]	=RADIO3_1;	/* TMOK 60-31, 			RADIO3_1 		SOP*/
ST[0].nSiteList[63]	=3016;	ST[0].nLinkList[63]	=RADIO3_1;	/* TMOK 60-30, 			RADIO3_1 		SOP*/
ST[0].nSiteList[64]	=3027;	ST[0].nLinkList[64]	=RADIO1_1;	/* TMOK 10-43, 			RADIO1_5 		GYR*/
ST[0].nSiteList[65]	=3028;	ST[0].nLinkList[65]	=RADIO1_5;	/* TMOK 10-72, 			RADIO1_5 		GYR*/
ST[0].nSiteList[66]	=3043;	ST[0].nLinkList[66]	=RADIO3_3;	/* TMOK 60-14, 			RADIO3_4 		SOP*/
ST[0].nSiteList[67]	=3044;	ST[0].nLinkList[67]	=RADIO3_3;	/* TMOK 62-24, 			RADIO3_4 		SOP*/
ST[0].nSiteList[68]	=3058;	ST[0].nLinkList[68]	=RADIO2_3;	/* TMOK 70-94, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[69]	=3059;	ST[0].nLinkList[69]	=RADIO2_3;	/* TMOK 70-97, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[70]	=3017;	ST[0].nLinkList[70]	=RADIO3_1;	/* TMOK 60-28, 			RADIO3_1 		SOP*/
ST[0].nSiteList[71]	=3029;	ST[0].nLinkList[71]	=RADIO1_5;	/* TMOK 11-15, 			RADIO1_5 		GYR*/
ST[0].nSiteList[72]	=3030;	ST[0].nLinkList[72]	=RADIO1_5;	/* TMOK 13-10, 			RADIO1_5 		GYR*/
ST[0].nSiteList[73]	=3018;	ST[0].nLinkList[73]	=RADIO3_2;	/* TMOK 60-43, 			RADIO3_2 		SOP*/
ST[0].nSiteList[74]	=3019;	ST[0].nLinkList[74]	=RADIO3_2;	/* TMOK 60-41, 			RADIO3_2 		SOP*/
ST[0].nSiteList[75]	=2007;	ST[0].nLinkList[75]	=LINE1;		/* Kormend atjatszo,	RST[0].sLINK18 */
ST[0].nSiteList[76]	=3053;	ST[0].nLinkList[76]	=RADIO2_1;	/* TMOK 53-31, 			RADIO2_1 		VESZ*/
ST[0].nSiteList[77]	=3047;	ST[0].nLinkList[77]	=RADIO2_1;	/* TMOK 53-39, 			RADIO2_1 		VESZ*/
ST[0].nSiteList[78]	=3020;	ST[0].nLinkList[78]	=RADIO3_1;	/* TMOK 60-45, 			RADIO3_1 		SOP*/
ST[0].nSiteList[79]	=3060;	ST[0].nLinkList[79]	=RADIO4_1;	/* TMOK 86-55, 			RADIO4_6 		PAP*/
ST[0].nSiteList[80]	=3054;	ST[0].nLinkList[80]	=RADIO4_1;	/* TMOK 71-65, 			RADIO4_6 		GYR*/
ST[0].nSiteList[81]	=3050;	ST[0].nLinkList[81]	=RADIO2_3;	/* TMOK 72-04, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[82]	=3094;	ST[0].nLinkList[82]	=RADIO2_8;	/* TMOK 71-11, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[83]	=3021;	ST[0].nLinkList[83]	=RADIO3_1;	/* TMOK 61-79, 			RADIO3_1 		SOP*/
ST[0].nSiteList[84]	=3022;	ST[0].nLinkList[84]	=RADIO3_1;	/* TMOK 61-81, 			RADIO3_1 		SOP*/
ST[0].nSiteList[85]	=3048;	ST[0].nLinkList[85]	=RADIO4_6;	/* TMOK 70-65, 			RADIO4_6 		PAP*/
ST[0].nSiteList[86]	=3052;	ST[0].nLinkList[86]	=RADIO4_6;	/* TMOK 70-67, 			RADIO4_6 		PAP*/
ST[0].nSiteList[87]	=3061;	ST[0].nLinkList[87]	=RADIO2_3;	/* TMOK 71-06, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[88]	=3062;	ST[0].nLinkList[88]	=RADIO2_3;	/* TMOK 72-91, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[89]	=3063;	ST[0].nLinkList[89]	=RADIO4_5;	/* TMOK 72-53, 			RADIO4_5 		PAP*/
ST[0].nSiteList[90]	=3064;	ST[0].nLinkList[90]	=RADIO4_5;	/* TMOK 72-75, 			RADIO4_5 		PAP*/
ST[0].nSiteList[91]	=3065;	ST[0].nLinkList[91]	=RADIO2_3;	/* TMOK 50-93, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[92]	=3066;	ST[0].nLinkList[92]	=RADIO2_3;	/* TMOK 50-97, 			RADIO2_2 		VESZ*/
ST[0].nSiteList[93]	=2006;	ST[0].nLinkList[93]	=RADIO2_1;	/* Kabhegy atjatszo, 	RADIO4_5 		PAP*/
ST[0].nSiteList[94]	=106;	ST[0].nLinkList[94]	=RADIO4_5;	/* TMOK 72-27,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[95]	=107;	ST[0].nLinkList[95]	=RADIO4_5;	/* TMOK 71-93,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[96]	=110;	ST[0].nLinkList[96]	=RADIO2_3;	/* TMOK 50-64,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[97]	=111;	ST[0].nLinkList[97]	=RADIO2_2;	/* TMOK 50-69,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[98]	=114;	ST[0].nLinkList[98]	=RADIO4_5;	/* TMOK 72-93,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[99]	=115;	ST[0].nLinkList[99]	=RADIO4_5;	/* TMOK 72-98,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[100]	=118;	ST[0].nLinkList[100]	=RADIO2_2;	/* TMOK 51-43,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[101]	=119;	ST[0].nLinkList[101]	=RADIO2_1;	/* TMOK 51-69,		 	RADIO2_1 		VESZ*/
ST[0].nSiteList[102]	=122;	ST[0].nLinkList[102]	=RADIO4_5;	/* TMOK 70-82,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[103]	=123;	ST[0].nLinkList[103]	=RADIO4_5;	/* TMOK 70-81,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[104]	=126;	ST[0].nLinkList[104]	=RADIO9_1;	/* TMOK 52-48,		 	RADIO9_1 		TAP*/
ST[0].nSiteList[105]	=127;	ST[0].nLinkList[105]	=RADIO9_9;	/* TMOK 52-62,		 	RADIO9_2 		TAP*/
ST[0].nSiteList[106]	=134;	ST[0].nLinkList[106]	=RADIO2_3;	/* TMOK 50-82,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[107]	=135;	ST[0].nLinkList[107]	=RADIO9_9;	/* TMOK 52-57,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[108]	=142;	ST[0].nLinkList[108]	=RADIO9_1;	/* TMOK 52-42,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[109]	=154;	ST[0].nLinkList[109]	=RADIO9_9;	/* TMOK 54-11,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[110]	=151;	ST[0].nLinkList[110]	=RADIO3_5;	/* TMOK 51-22,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[111]	=3076;	ST[0].nLinkList[111]	=RADIO6_1;	/* TMOK 51-28,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[112]	=130;	ST[0].nLinkList[112]	=RADIO4_5;	/* TMOK 70-75,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[113]	=131;	ST[0].nLinkList[113]	=RADIO4_6;	/* TMOK 74-01,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[114]	=152;	ST[0].nLinkList[114]	=RADIO6_3;	/* TMOK 51-20,		 	RADIO2_2 		VESZ*/
ST[0].nSiteList[115]	=3072;	ST[0].nLinkList[115]	=RADIO4_6;	/* TMOK 70-88,		 	RADIO4_6 		PAP*/
ST[0].nSiteList[116]	=138;	ST[0].nLinkList[116]	=RADIO4_5;	/* TMOK 74-02,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[117]	=139;	ST[0].nLinkList[117]	=RADIO4_6;	/* TMOK 72-65,		 	RADIO4_6 		PAP*/
ST[0].nSiteList[118]	=3151;	ST[0].nLinkList[118]	=RADIO8_4;	/* Dorog atjatszo,	 	RADIO8_1 		ESZT*/
ST[0].nSiteList[119]	=3073;	ST[0].nLinkList[119]	=RADIO4_1;	/* TMOK 71-91,		 	RADIO4_6 		PAP*/
ST[0].nSiteList[120]	=3074;	ST[0].nLinkList[120]	=RADIO4_1;	/* TMOK 71-37,		 	RADIO4_6 		PAP*/
ST[0].nSiteList[121]	=3075;	ST[0].nLinkList[121]	=RADIO4_5;	/* TMOK 72-44,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[122]	=153;	ST[0].nLinkList[122]	=RADIO5_1;	/* TMOK 72-77,		 	RADIO1_5 		GYR*/
ST[0].nSiteList[123]	=150;	ST[0].nLinkList[123]	=RADIO4_5;	/* TMOK 70-14,		 	RADIO4_2 		PAP*/
ST[0].nSiteList[124]	=146;	ST[0].nLinkList[124]	=RADIO5_5;	/* TMOK 40-63,		 	RADIO5_5 		KOR*/
ST[0].nSiteList[125]	=147;	ST[0].nLinkList[125]	=RADIO5_6;	/* TMOK 40-61,		 	RADIO5_6 		KOR*/
ST[0].nSiteList[126]	=3087;	ST[0].nLinkList[126]	=RADIO4_6;	/* TMOK 11-38,		 	RADIO1_5 		GYR*/
ST[0].nSiteList[127]	=3088;	ST[0].nLinkList[127]	=RADIO4_1;	/* TMOK 15-50,		 	RADIO4_6 		GYR*/
ST[0].nSiteList[128]	=2008;	ST[0].nLinkList[128]	=RADIO1_6;	/* LINDE, Repcelak		RADIO1_6 		GYR*/
ST[0].nSiteList[129]	=310;	ST[0].nLinkList[129]	=RADIO5_5;	/* Vasvar, regioho		RADIO5_5		KOR*/
ST[0].nSiteList[130]	=3082;	ST[0].nLinkList[130]	=RADIO4_6;	/* TMOK 72-16,		 	RADIO4_6 		PAP*/
ST[0].nSiteList[131]	=3080;	ST[0].nLinkList[131]	=RADIO4_5;	/* TMOK 71-31,		 	RADIO4_5 		PAP*/
ST[0].nSiteList[132]	=3068;	ST[0].nLinkList[132]	=RADIO5_5;	/* TMOK 42-11			RADIO5_5 		KOR*/
ST[0].nSiteList[133]	=3069;	ST[0].nLinkList[133]	=RADIO5_5;	/* TMOK 42-34			RADIO5_5 		KOR*/
ST[0].nSiteList[134]	=3070;	ST[0].nLinkList[134]	=RADIO5_5;	/* TMOK 42-12			RADIO5_7 		KOR*/
ST[0].nSiteList[135]	=3071;	ST[0].nLinkList[135]	=RADIO5_5;	/* TMOK 48-938			RADIO5_5 		KOR*/
ST[0].nSiteList[136]	=3078;	ST[0].nLinkList[136]	=RADIO2_3;	/* TMOK 71-02			RADIO4_6 		PAP*/
ST[0].nSiteList[137]	=3081;	ST[0].nLinkList[137]	=RADIO4_6;	/* TMOK 71-58			RADIO4_6 		PAP*/
ST[0].nSiteList[138]	=3079;	ST[0].nLinkList[138]	=RADIO4_6;	/* TMOK 71-28			RADIO4_6 		PAP*/
ST[0].nSiteList[139]	=3077;	ST[0].nLinkList[139]	=RADIO4_6;	/* TMOK 70-24			RADIO4_6 		PAP*/
ST[0].nSiteList[140]	=2016;	ST[0].nLinkList[140]	=RADIO7_1;	/* Esztergom,Suzuki2.		RADIO8_1 	ESZT*/
ST[0].nSiteList[141]	=2010;	ST[0].nLinkList[141]	=RADIO7_1;	/* Esztergom,TYCO			RADIO8_1 	ESZT*/
ST[0].nSiteList[142]	=2012;	ST[0].nLinkList[142]	=RADIO7_1;	/* Esztergom,Lotus Foods 	RADIO8_1 	ESZT*/
ST[0].nSiteList[143]	=2015;	ST[0].nLinkList[143]	=RADIO7_1;	/* Esztergom,TESCO			RADIO8_1 	ESZT*/
ST[0].nSiteList[144]	=2013;	ST[0].nLinkList[144]	=RADIO7_1;	/* Esztergom,Ipari Park 1.	RADIO8_1 	ESZT*/
ST[0].nSiteList[145]	=2014;	ST[0].nLinkList[145]	=RADIO7_1;	/* Esztergom,Ipari Park 2.	RADIO8_1 	ESZT*/
ST[0].nSiteList[146]	=2011;	ST[0].nLinkList[146]	=RADIO7_1;	/* Esztergom,Ipari Park 3.	RADIO8_1 	ESZT*/
ST[0].nSiteList[147]	=2018;	ST[0].nLinkList[147]	=RADIO6_2;	/* Balatonfured, Furedho 				VESZ*/
ST[0].nSiteList[148]	=2009;	ST[0].nLinkList[148]	=RADIO5_5;	/* Kormend, Kormendho 					KOR*/
ST[0].nSiteList[149]	=3089;	ST[0].nLinkList[149]	=RADIO1_4;	/* TMOK 12-90			RADIO1_5 		GYR*/
ST[0].nSiteList[150]	=3092;	ST[0].nLinkList[150]	=RADIO1_6;	/* TMOK 61-24			RADIO1_6 		GYR*/
ST[0].nSiteList[151]	=3090;	ST[0].nLinkList[151]	=RADIO2_1;	/* TMOK 50-22			RADIO2_1 		VESZ*/
ST[0].nSiteList[152]	=3091;	ST[0].nLinkList[152]	=RADIO2_1;	/* TMOK 50-23			RADIO2_1 		VESZ*/
ST[0].nSiteList[153]	=2019;	ST[0].nLinkList[153]	=RADIO1_4;	/* Gyor, Raba repter	RADIO1_4 		GYR*/
ST[0].nSiteList[154]	=2017;	ST[0].nLinkList[154]	=RADIO1_4;	/* Gyor, EETEK			RADIO1_4 		GYR*/
ST[0].nSiteList[155]	=3095;	ST[0].nLinkList[155]	=RADIO3_1;	/* TMOK 61-80, PM6		RADIO1_6 		GYR*/
ST[0].nSiteList[156]	=2020;	ST[0].nLinkList[156]	=RADIO3_7;	/* Balf, gazmotor 		RADIO3_4 		SOP*/
ST[0].nSiteList[157]	=109;	ST[0].nLinkList[157]	=RADIO5_5;	/* TMOK 40-70	 		RADIO5_7 		KOR*/
ST[0].nSiteList[158]	=3096;	ST[0].nLinkList[158]	=RADIO7_6;	/* TMOK 31-67	 		RADIO7_5 		BI*/
ST[0].nSiteList[159]	=3153;	ST[0].nLinkList[159]	=RADIO6_3;	/* Balatonalmadi,gazmotor				VESZ*/
ST[0].nSiteList[160]	=3101;	ST[0].nLinkList[160]	=RADIO2_2;	/* TMOK 90-05	 		RADIO2_2 		SUM*/
ST[0].nSiteList[161]	=3099;	ST[0].nLinkList[161]	=RADIO2_1;	/* TMOK 37-21	 		RADIO2_1 		VESZ*/
ST[0].nSiteList[162]	=3100;	ST[0].nLinkList[162]	=RADIO3_5;	/* TMOK 37-33	 		RADIO2_1 		VESZ*/
ST[0].nSiteList[163]	=2021;	ST[0].nLinkList[163]	=LINE1;		/* Bicske atjatszo,		 */
ST[0].nSiteList[164]	=2022;	ST[0].nLinkList[164]	=LINE1;		/* Sumeg atjatszo,		RST[0].sLINK14 */
ST[0].nSiteList[165]	=3104;	ST[0].nLinkList[165]	=RADIO9_5;	/* TMOK 90-32	 		RADIO9_5 		SUM*/
ST[0].nSiteList[166]	=3105;	ST[0].nLinkList[166]	=RADIO9_7;	/* TMOK 90-40	 		RADIO9_5 		SUM*/
ST[0].nSiteList[167]	=3102;	ST[0].nLinkList[167]	=RADIO9_5;	/* TMOK 90-10	 		RADIO9_5 		SUM*/
ST[0].nSiteList[168]	=3125;	ST[0].nLinkList[168]	=RADIO9_5;	/* TMOK 90-11	 		RADIO9_5 		SUM*/
ST[0].nSiteList[169]	=3103;	ST[0].nLinkList[169]	=RADIO9_5;	/* TMOK 90-18	 		RADIO9_5 		SUM*/
ST[0].nSiteList[170]	=3126;	ST[0].nLinkList[170]	=RADIO9_5;	/* TMOK 90-23	 		RADIO9_5 		SUM*/
ST[0].nSiteList[171]	=3127;	ST[0].nLinkList[171]	=RADIO9_5;	/* TMOK 90-55	 		RADIO9_5 		SUM*/
ST[0].nSiteList[172]	=3106;	ST[0].nLinkList[172]	=RADIO9_6;	/* TMOK 90-63	 		RADIO9_5 		SUM*/
ST[0].nSiteList[173]	=3107;	ST[0].nLinkList[173]	=RADIO9_5;	/* TMOK 90-79	 		RADIO9_5 		SUM*/
ST[0].nSiteList[174]	=3108;	ST[0].nLinkList[174]	=RADIO9_5;	/* TMOK 90-86	 		RADIO9_5 		SUM*/
ST[0].nSiteList[175]	=3136;	ST[0].nLinkList[175]	=RADIO1_1;	/* TMOK 11-48	 		RADIO1_5 		GYR*/
ST[0].nSiteList[176]	=3112;	ST[0].nLinkList[176]	=RADIO7_5;	/* TMOK 87-28	 		RADIO7_5 		BI*/
ST[0].nSiteList[177]	=3115;	ST[0].nLinkList[177]	=RADIO7_5;	/* TMOK 87-33	 		RADIO7_5 		BI*/
ST[0].nSiteList[178]	=3116;	ST[0].nLinkList[178]	=RADIO7_6;	/* TMOK 87-34	 		RADIO7_6 		BI*/
ST[0].nSiteList[179]	=3117;	ST[0].nLinkList[179]	=RADIO7_5;	/* TMOK 87-35	 		RADIO7_5 		BI*/
ST[0].nSiteList[180]	=3118;	ST[0].nLinkList[180]	=RADIO7_7;	/* TMOK 87-40	 		RADIO7_5 		BI*/
ST[0].nSiteList[181]	=3120;	ST[0].nLinkList[181]	=RADIO7_7;	/* TMOK 87-43	 		RADIO7_5 		BI*/
ST[0].nSiteList[182]	=3121;	ST[0].nLinkList[182]	=RADIO7_5;	/* TMOK 87-62	 		RADIO7_5 		BI*/
ST[0].nSiteList[183]	=3122;	ST[0].nLinkList[183]	=RADIO7_5;	/* TMOK 87-71	 		RADIO7_5 		BI*/
ST[0].nSiteList[184]	=3123;	ST[0].nLinkList[184]	=RADIO7_5;	/* TMOK 87-72	 		RADIO7_5 		BI*/
ST[0].nSiteList[185]	=3124;	ST[0].nLinkList[185]	=RADIO7_6;	/* TMOK 87-90	 		RADIO7_5 		BI*/
ST[0].nSiteList[186]	=3134;	ST[0].nLinkList[186]	=RADIO4_1;	/* TMOK 86-88	 		RADIO4_6 		PAP*/
ST[0].nSiteList[187]	=3135;	ST[0].nLinkList[187]	=RADIO1_5;	/* TMOK 86-95	 		RADIO1_5 		GYR*/
ST[0].nSiteList[188]	=45;	ST[0].nLinkList[188]	=RADIO1_1;	/* TMOK 62-23	 		RADIO1_1 		GYR*/
ST[0].nSiteList[189]	=3154;	ST[0].nLinkList[189]	=RADIO7_1;	/* Esztergom,elmenyfurdoRADIO8_1 		ESZT*/
ST[0].nSiteList[190]	=3223;	ST[0].nLinkList[190]	=RADIO8_4;	/* Nyergesújfalu, Etertech RADIO8_5		ESZT*/
ST[0].nSiteList[191]	=5042;	ST[0].nLinkList[191]	=RADIO9_6;	/* TMOK 90-82	 		RADIO9_5 		SUM*/
ST[0].nSiteList[192]	=3130;	ST[0].nLinkList[192]	=RADIO8_3;	/* TMOK 21-66	 		RADIO8_2 		ESZT*/
ST[0].nSiteList[193]	=3131;	ST[0].nLinkList[193]	=RADIO8_6;	/* TMOK 21-81	 		RADIO8_3 		ESZT*/
ST[0].nSiteList[194]	=3132;	ST[0].nLinkList[194]	=RADIO8_6;	/* TMOK 21-84	 		RADIO8_2 		ESZT*/
ST[0].nSiteList[195]	=5089;	ST[0].nLinkList[195]	=RADIO9_5;	/* TMOK 90-90	 		RADIO9_5 		SUM*/
ST[0].nSiteList[196]	=3137;	ST[0].nLinkList[196]	=RADIO1_5;	/* TMOK 11-81	 		RADIO1_5 		GYR*/
ST[0].nSiteList[197]	=3138;	ST[0].nLinkList[197]	=RADIO1_5;	/* TMOK 10-01, 10-20	RADIO1_5 		GYR*/
ST[0].nSiteList[198]	=3140;	ST[0].nLinkList[198]	=RADIO5_5;	/* TMOK 40-62	 		RADIO5_5 		KOR*/
ST[0].nSiteList[199]	=3141;	ST[0].nLinkList[199]	=RADIO3_1;	/* Fertoszentmiklos		RADIO3_1 		SOP*/
ST[0].nSiteList[200]	=3142;	ST[0].nLinkList[200]	=RADIO2_2;	/* TMOK 71-44			RADIO2_2 		PAP*/
ST[0].nSiteList[201]	=3143;	ST[0].nLinkList[201]	=RADIO1_5;	/* TMOK 13-85			RADIO1_5 		GYR*/
ST[0].nSiteList[202]	=3144;	ST[0].nLinkList[202]	=RADIO8_2;	/* TMOK 21-21,21-22		RADIO8_2 		ESZT*/
ST[0].nSiteList[203] 	=3145;	ST[0].nLinkList[203]	=RADIO3_3;	/* Sopron, Ipari Park	RADIO3_4 		SOP*/
ST[0].nSiteList[204]	=3146;	ST[0].nLinkList[204]	=RADIO2_1;	/* Veszpr, Balat. Plaza RADIO2_1 		VESZ*/
ST[0].nSiteList[205]	=3147;	ST[0].nLinkList[205]	=RADIO3_3;	/* Sopron, Szemettelep 	RADIO3_4 		SOP*/
ST[0].nSiteList[206]	=3148;	ST[0].nLinkList[206]	=RADIO2_1;	/* Veszpr, Csolnoky kor RADIO2_1 		VESZ*/
ST[0].nSiteList[207]	=3149;	ST[0].nLinkList[207]	=RADIO9_1;	/* Tapolca, Talus		RADIO9_1 		TAP*/
ST[0].nSiteList[208]	=3150;	ST[0].nLinkList[208]	=RADIO9_9;	/* Kekkut, MOSCAD-L 	RADIO9_3		TAP*/
ST[0].nSiteList[209]	=305;	ST[0].nLinkList[209]	=RADIO1_4;	/* TMOK 11-10			RADIO1_5 		GYR*/
ST[0].nSiteList[210]	=3155;	ST[0].nLinkList[210]	=RADIO8_2;	/* TMOK 21-15,21-73		RADIO8_1 		ESZT*/
ST[0].nSiteList[211]	=3157;	ST[0].nLinkList[211]	=RADIO1_1;	/* TMOK 10-74			RADIO1_5 		GYR*/
ST[0].nSiteList[212]	=3158;	ST[0].nLinkList[212]	=RADIO1_1;	/* TMOK 11-22      		RADIO1_5 		GYR*/
ST[0].nSiteList[213]	=3159;	ST[0].nLinkList[213]	=RADIO1_5;	/* TMOK 11-35      		RADIO1_5 		GYR*/
ST[0].nSiteList[214]	=3160;	ST[0].nLinkList[214]	=RADIO1_5;	/* TMOK 10-19      		RADIO1_5 		GYR*/
ST[0].nSiteList[215]	=3161;	ST[0].nLinkList[215]	=RADIO5_1;	/* TMOK 11-80      		RADIO1_5 		GYR*/
ST[0].nSiteList[216]	=3162;	ST[0].nLinkList[216]	=RADIO1_5;	/* TMOK 11-99      		RADIO1_5 		GYR*/
ST[0].nSiteList[217]	=3163;	ST[0].nLinkList[217]	=RADIO2_1;	/* TMOK 52-50      		RADIO2_1 		VESZ*/
ST[0].nSiteList[218]	=3164;	ST[0].nLinkList[218]	=RADIO2_2;	/* TMOK 54-02      		RADIO2_2 		VESZ*/
ST[0].nSiteList[219]	=3165;	ST[0].nLinkList[219]	=RADIO2_7;	/* TMOK 51-12      		RADIO2_7 		VESZ*/
ST[0].nSiteList[220]	=3166;	ST[0].nLinkList[220]	=RADIO6_3;	/* TMOK 50-49      		RADIO2_6 		VESZ*/
ST[0].nSiteList[221]	=3167;	ST[0].nLinkList[221]	=RADIO2_2;	/* TMOK 51-39,51-41		RADIO2_2 		VESZ*/
ST[0].nSiteList[222]	=3169;	ST[0].nLinkList[222]	=RADIO2_2;	/* TMOK 51-40,51-42		RADIO2_2 		VESZ*/
ST[0].nSiteList[223]	=3171;	ST[0].nLinkList[223]	=RADIO5_1;	/* TMOK 61-15      		RADIO1_5 		GYR*/
ST[0].nSiteList[224]	=3172;	ST[0].nLinkList[224]	=RADIO1_6;	/* TMOK 64-84      		RADIO1_6 		GYR*/
ST[0].nSiteList[225]	=3173;	ST[0].nLinkList[225]	=RADIO1_6;	/* TMOK 74-24      		RADIO1_6 		GYR*/
ST[0].nSiteList[226]	=3174;	ST[0].nLinkList[226]	=RADIO6_1;	/* TMOK 51-74      		RADIO2_6 		VESZ*/
ST[0].nSiteList[227]	=3178;	ST[0].nLinkList[227]	=RADIO2_6;	/* TMOK 37-29      		RADIO2_6 		VESZ*/
ST[0].nSiteList[228]	=3179;	ST[0].nLinkList[228]	=RADIO4_6;	/* TMOK 73-06      		RADIO4_6 		PAP*/
ST[0].nSiteList[229]	=3156;	ST[0].nLinkList[229]	=LINE1;		/* Dorog DAC      		Rslink9 		*/
ST[0].nSiteList[230]	=3200;	ST[0].nLinkList[230]	=RADIO6_3;	/* TMOK 51-01      		RADIO2_6 		VESZ*/
ST[0].nSiteList[231]	=3201;	ST[0].nLinkList[231]	=RADIO5_1;	/* TMOK 11-66      		RADIO1_5 		GYR*/
ST[0].nSiteList[232]	=3202;	ST[0].nLinkList[232]	=RADIO4_5;	/* TMOK 70-60      		RADIO4_5 		PAP*/
ST[0].nSiteList[233]	=3180;	ST[0].nLinkList[233]	=RADIO1_5;	/* TMOK 10-24      		RADIO1_2 		GYR*/
ST[0].nSiteList[234]	=3181;	ST[0].nLinkList[234]	=RADIO1_5;	/* TMOK 11-28      		RADIO1_5 		GYR*/
ST[0].nSiteList[235]	=3210;	ST[0].nLinkList[235]	=RADIO2_3;	/* TMOK 50-96      		RADIO2_2 		VESZ*/
ST[0].nSiteList[236]	=3204;	ST[0].nLinkList[236]	=RADIO6_2;	/* TMOK 51-53      		RADIO2_3 		VESZ*/
ST[0].nSiteList[237]	=3191;	ST[0].nLinkList[237]	=RADIO1_5;	/* TMOK 13-73      		RADIO1_5 		GYR*/
ST[0].nSiteList[238]	=3215;	ST[0].nLinkList[238]	=RADIO3_5;	/* TMOK 37-03      		RADIO2_5 		VESZ*/
ST[0].nSiteList[239]	=3182;	ST[0].nLinkList[239]	=RADIO3_3;	/* TMOK 60-08      		RADIO3_4 		SOP*/
ST[0].nSiteList[240]	=3188;	ST[0].nLinkList[240]	=RADIO1_1;	/* TMOK 15-55      		RADIO1_5 		GYR*/
ST[0].nSiteList[241]	=3208;	ST[0].nLinkList[241]	=RADIO6_1;	/* TMOK 51-13      		RADIO2_3 		VESZ*/
ST[0].nSiteList[242]	=3183;	ST[0].nLinkList[242]	=RADIO4_5;	/* TMOK 60-71      		RADIO4_5 		PAP*/
ST[0].nSiteList[243]	=9999;	ST[0].nLinkList[243]	=RADIO4_5;	/* TMOK 34-04      		RADIO4_5 		PAP*/
ST[0].nSiteList[244]	=3192;	ST[0].nLinkList[244]	=RADIO5_1;	/* TMOK 60-90      		RADIO1_6 		GYR*/
ST[0].nSiteList[245]	=3185;	ST[0].nLinkList[245]	=RADIO1_6;	/* TMOK 61-59      		RADIO1_6 		GYR*/

ST[0].nSiteList[246]	=3110;	ST[0].nLinkList[246]	=RADIO8_4;	/* TMOK 20-14      		RADIO8_1 		ESZT*/
ST[0].nSiteList[247]	=3217;	ST[0].nLinkList[247]	=RADIO2_1;	/* TMOK 51-09      		RADIO2_1 		VESZ*/
ST[0].nSiteList[248]	=3206;	ST[0].nLinkList[248]	=RADIO9_1;	/* TMOK 52-60      		RADIO9_1 		TAP*/

ST[0].nSiteList[249]	=3213;	ST[0].nLinkList[249]	=RADIO4_5;	/* TMOK 71-16      		RADIO4_5 		PAP*/





/*for (nI=0;nI<nNumOfSites && nI<MAX_RTU;nI++)
{
	byComStat[nI] = 0;
}*/


  /* MOSCAD_set_sitetable(250,ST[0].nSiteList,ST[0].nLinkList,byComStat);*/


 /* endfnSetStatSiteTable()*/

/****************************************************************************/
/* Dinamikus site tabla feltoltese											*/
/****************************************************************************/

	
/*-------------------------------*/
/* Clear the dynamic site table. */
/*-------------------------------*/
nSiteIdCheck[0] = 3184;
nSiteIdCheck[1] = 3187;
nSiteIdCheck[2] = 3198;
nSiteIdCheck[3] = 3199;
nSiteIdCheck[4] = 3203;
nSiteIdCheck[5] = 3211;
nSiteIdCheck[6] = 3207;
nSiteIdCheck[7] = 3212;
nSiteIdCheck[8] = 3221;
nSiteIdCheck[9] = 3222;

nSiteIdCheck[10] = 3205;
nSiteIdCheck[11] = 3214;
nSiteIdCheck[12] = 3193;
nSiteIdCheck[13] = 3209;
nSiteIdCheck[14] = 3186;
nSiteIdCheck[15] = 3219;
nSiteIdCheck[16] = 3196;
nSiteIdCheck[17] = 3220;
nSiteIdCheck[18] = 3197;
nSiteIdCheck[19] = 5072;

nSiteIdCheck[20] = 3233;
nSiteIdCheck[21] = 3224;

MOSCAD_init_sitetable(); 
/* 250--------------------------------------259*/
/* 250 61-40	RADIO1_8		GYR			*/ MOSCAD_add_new_site(3184,RADIO1_8);		
/* 251 65-07	RADIO1_6		GYR			*/ MOSCAD_add_new_site(3187,RADIO5_1);	
/* 252 80-87	RADIO7_5		BI			*/ MOSCAD_add_new_site(3198,RADIO7_5);		
/* 253 87-66	RADIO7_5		BI			*/ MOSCAD_add_new_site(3199,RADIO7_5);	
/* 254 50-68	RADIO2_2		VESZ		*/ MOSCAD_add_new_site(3203,RADIO2_2);	
/* 255 51-78	RADIO2_5		VESZ		*/ MOSCAD_add_new_site(3211,RADIO6_3);	
/* 256 52-70	RADIO9_1		TAP			*/ MOSCAD_add_new_site(3207,RADIO9_1);	
/* 257 54-19	RADIO2_2		VESZ		*/ MOSCAD_add_new_site(3212,RADIO2_3);	
/* 258 64-89	RADIO3_8		SOP			*/ MOSCAD_add_new_site(3221,RADIO3_3);	
/* 259 65-25	RADIO3_4		SOP			*/ MOSCAD_add_new_site(3222,RADIO3_4);	

/* 260 71-61	RADIO4_5		PAP			*/ MOSCAD_add_new_site(3205,RADIO4_5);	
/* 261 72-89	RADIO4_6		PAP			*/ MOSCAD_add_new_site(3214,RADIO4_6);	
/* 262 90-83	RADIO9_5		SUM			*/ MOSCAD_add_new_site(3193,RADIO9_6);	
/* 263 50-86	RADIO2_4		VESZ		*/ MOSCAD_add_new_site(3209,RADIO2_3);
/* 264 62-29	RADIO1_6		GYR			*/ MOSCAD_add_new_site(3186,RADIO5_1);
/* 265 20-02	RADIO8_1		ESZT		*/ MOSCAD_add_new_site(3219,RADIO7_2);
/* 266 21-05	RADIO8_1		ESZT		*/ MOSCAD_add_new_site(3196,RADIO7_1);
/* 267 72-90	RADIO4_5		PAP			*/ MOSCAD_add_new_site(3220,RADIO4_5);
/* 268 21-07	RADIO8_1		ESZT		*/ MOSCAD_add_new_site(3197,RADIO7_1);
/* 269 37-199   RADIO3_5        VESZ        */ MOSCAD_add_new_site(5072,RADIO3_5);
/* 270--------------------------------------279*/
/* 270 71-43	RADIO2_2		PAP			*/ MOSCAD_add_new_site(3233,RADIO2_6);
/* 271 Balatonfured Anna Grand Hotel RADIO2_3 VESZ*/ 	MOSCAD_add_new_site(3224,RADIO6_1);
/* 272 51-42	RADIO2_2					*/ MOSCAD_add_new_site(3170,RADIO2_2);
/* 273 51-41	RADIO2_2					*/ MOSCAD_add_new_site(3168,RADIO2_2);
/* 274 Front end D										*/ MOSCAD_add_new_site(6000,RSLINK11);  /* Újfajta retesz kezelés miatt */
/* 275 Front end F										*/ MOSCAD_add_new_site(8000,RSLINK11);  /* Újfajta retesz kezelés miatt */
/* 276 Front end H										*/ MOSCAD_add_new_site(10000,RSLINK11);  /* Újfajta retesz kezelés miatt */
/* 277 B redumdancia									*/ MOSCAD_add_new_site(8999,RSLINK11);  /* Újfajta retesz kezelés miatt */





p_col_ParStat[16] = 0;	/* Assuming good dynamic site table */
p_col_ParStat[17] = 1;
for (nI=0;nI<22;nI++)
{
	MOSCAD_find_siteid (250 + nI, &nSiteId[nI], &cLinkId[nI]);
        MOSCAD_sprintf(message,"nI: %d, site ID: %d",nI+250,nSiteId[nI]);
        MOSCAD_error(message );
	
		MOSCAD_find_siteid (250 + nI, &nSiteId[nI], &cLinkId[nI]);
		p_col_ParStat[27+nI] = nSiteId[nI];

	
	
if ( (nSiteId[nI]!=nSiteIdCheck[nI]) && (p_col_ParStat[16] == 0) )
	{
		p_col_ParStat[16] = nI;
		p_col_ParStat[17] = nSiteId[nI];
	} /* end if */
	
} /* end for */

	

MOSCAD_sprintf(message,"Site index 250,251... site ID: %d  %d  %d  %d  %d",nSiteId[0],nSiteId[1],nSiteId[2],nSiteId[3],nSiteId[4]);
MOSCAD_message(message );

	
	
	
 /*end fnSetDinamicSiteTable() */


/****************************************************************************/
/* Parancskuldes parameterei      											*/
/****************************************************************************/


	

/* IEC cimnek megfelelo RTU cimek -----------------------------------------------------------------------*/
/* Ha valamelyik darabszam = 0, akkor olyan tipusu parancs nem tartozik az RTU-hoz */
        	
         	






/* Radios RTU-k indexei, periodikus lekerdezes miatt*/
/* K1 : GYOR*/
ST[0].sRAD_K1[0].nRtuNumRad = 84; /*72*/
ST[0].sRAD_K1[0].nIndx[0]=2; 
ST[0].sRAD_K1[0].nIndx[1]=3;/*3*/
ST[0].sRAD_K1[0].nIndx[2]=6;/*3*/
ST[0].sRAD_K1[0].nIndx[3]=9;
ST[0].sRAD_K1[0].nIndx[4]=11;
ST[0].sRAD_K1[0].nIndx[5]=12;
ST[0].sRAD_K1[0].nIndx[6]=13;
ST[0].sRAD_K1[0].nIndx[7]=14;
ST[0].sRAD_K1[0].nIndx[8]=209;
ST[0].sRAD_K1[0].nIndx[9]=18;
ST[0].sRAD_K1[0].nIndx[10]=19; 
ST[0].sRAD_K1[0].nIndx[11]=20;
ST[0].sRAD_K1[0].nIndx[12]=21;
ST[0].sRAD_K1[0].nIndx[13]=22;
ST[0].sRAD_K1[0].nIndx[14]=23;
ST[0].sRAD_K1[0].nIndx[15]=24;
ST[0].sRAD_K1[0].nIndx[16]=25;
ST[0].sRAD_K1[0].nIndx[17]=26;
ST[0].sRAD_K1[0].nIndx[18]=27;
ST[0].sRAD_K1[0].nIndx[19]=28;
ST[0].sRAD_K1[0].nIndx[20]=29; 
ST[0].sRAD_K1[0].nIndx[21]=30;
ST[0].sRAD_K1[0].nIndx[22]=31;
ST[0].sRAD_K1[0].nIndx[23]=37;
ST[0].sRAD_K1[0].nIndx[24]=38;
ST[0].sRAD_K1[0].nIndx[25]=39;
ST[0].sRAD_K1[0].nIndx[26]=41;
ST[0].sRAD_K1[0].nIndx[27]=42;
ST[0].sRAD_K1[0].nIndx[28]=43;
ST[0].sRAD_K1[0].nIndx[29]=44;
ST[0].sRAD_K1[0].nIndx[30]=45; 
ST[0].sRAD_K1[0].nIndx[31]=46;
ST[0].sRAD_K1[0].nIndx[32]=47;
ST[0].sRAD_K1[0].nIndx[33]=51;
ST[0].sRAD_K1[0].nIndx[34]=52;
ST[0].sRAD_K1[0].nIndx[35]=53;
ST[0].sRAD_K1[0].nIndx[36]=54;
ST[0].sRAD_K1[0].nIndx[37]=55;
ST[0].sRAD_K1[0].nIndx[38]=56;
ST[0].sRAD_K1[0].nIndx[39]=58;
ST[0].sRAD_K1[0].nIndx[40]=59; 
ST[0].sRAD_K1[0].nIndx[41]=60;
ST[0].sRAD_K1[0].nIndx[42]=61;
ST[0].sRAD_K1[0].nIndx[43]=64;
ST[0].sRAD_K1[0].nIndx[44]=65;
ST[0].sRAD_K1[0].nIndx[45]=71;
ST[0].sRAD_K1[0].nIndx[46]=72;
ST[0].sRAD_K1[0].nIndx[47]=122;
ST[0].sRAD_K1[0].nIndx[48]=126;
ST[0].sRAD_K1[0].nIndx[49]=127;
ST[0].sRAD_K1[0].nIndx[50]=128; 
ST[0].sRAD_K1[0].nIndx[51]=149;
ST[0].sRAD_K1[0].nIndx[52]=150;
ST[0].sRAD_K1[0].nIndx[53]=153;
ST[0].sRAD_K1[0].nIndx[54]=154;
ST[0].sRAD_K1[0].nIndx[55]=155;
ST[0].sRAD_K1[0].nIndx[56]=175;
ST[0].sRAD_K1[0].nIndx[57]=187;
ST[0].sRAD_K1[0].nIndx[58]=188;
ST[0].sRAD_K1[0].nIndx[59]=196;
ST[0].sRAD_K1[0].nIndx[60]=197; 
ST[0].sRAD_K1[0].nIndx[61]=201;
ST[0].sRAD_K1[0].nIndx[62]=202;
ST[0].sRAD_K1[0].nIndx[63]=211;
ST[0].sRAD_K1[0].nIndx[64]=212;
ST[0].sRAD_K1[0].nIndx[65]=213;
ST[0].sRAD_K1[0].nIndx[66]=214;
ST[0].sRAD_K1[0].nIndx[67]=215;
ST[0].sRAD_K1[0].nIndx[68]=216;
ST[0].sRAD_K1[0].nIndx[69]=223;
ST[0].sRAD_K1[0].nIndx[70]=224;
ST[0].sRAD_K1[0].nIndx[71]=225;
ST[0].sRAD_K1[0].nIndx[72]=231;
ST[0].sRAD_K1[0].nIndx[73]=233;
ST[0].sRAD_K1[0].nIndx[74]=234;
ST[0].sRAD_K1[0].nIndx[75]=233;
ST[0].sRAD_K1[0].nIndx[76]=234;
ST[0].sRAD_K1[0].nIndx[77]=237;
ST[0].sRAD_K1[0].nIndx[78]=240;
ST[0].sRAD_K1[0].nIndx[79]=244;
ST[0].sRAD_K1[0].nIndx[80]=245;
ST[0].sRAD_K1[0].nIndx[81]=250;
ST[0].sRAD_K1[0].nIndx[82]=251;
ST[0].sRAD_K1[0].nIndx[83]=254;



/* K2 : VESZ, TAP, PAP, SUM */
ST[0].sRAD_K2[0].nRtuNumRad = 113; 

ST[0].sRAD_K2[0].nIndx[0]=1;
ST[0].sRAD_K2[0].nIndx[1]=5; /*5*/
ST[0].sRAD_K2[0].nIndx[2]=17; /*17*/
ST[0].sRAD_K2[0].nIndx[3]=68;
ST[0].sRAD_K2[0].nIndx[4]=69;
ST[0].sRAD_K2[0].nIndx[5]=76;
ST[0].sRAD_K2[0].nIndx[6]=77;
ST[0].sRAD_K2[0].nIndx[7]=79;
ST[0].sRAD_K2[0].nIndx[8]=80;
ST[0].sRAD_K2[0].nIndx[9]=81;
ST[0].sRAD_K2[0].nIndx[10]=82;
ST[0].sRAD_K2[0].nIndx[11]=85;
ST[0].sRAD_K2[0].nIndx[12]=86;
ST[0].sRAD_K2[0].nIndx[13]=87;
ST[0].sRAD_K2[0].nIndx[14]=88;
ST[0].sRAD_K2[0].nIndx[15]=89;
ST[0].sRAD_K2[0].nIndx[16]=90;
ST[0].sRAD_K2[0].nIndx[17]=91;
ST[0].sRAD_K2[0].nIndx[18]=92;
ST[0].sRAD_K2[0].nIndx[19]=93;
ST[0].sRAD_K2[0].nIndx[20]=94;
ST[0].sRAD_K2[0].nIndx[21]=95;
ST[0].sRAD_K2[0].nIndx[22]=96;
ST[0].sRAD_K2[0].nIndx[23]=97;
ST[0].sRAD_K2[0].nIndx[24]=98;
ST[0].sRAD_K2[0].nIndx[25]=99;
ST[0].sRAD_K2[0].nIndx[26]=100;
ST[0].sRAD_K2[0].nIndx[27]=101;
ST[0].sRAD_K2[0].nIndx[28]=102;
ST[0].sRAD_K2[0].nIndx[29]=103;
ST[0].sRAD_K2[0].nIndx[30]=104;
ST[0].sRAD_K2[0].nIndx[31]=105;
ST[0].sRAD_K2[0].nIndx[32]=106;
ST[0].sRAD_K2[0].nIndx[33]=107;
ST[0].sRAD_K2[0].nIndx[34]=108;
ST[0].sRAD_K2[0].nIndx[35]=109;
ST[0].sRAD_K2[0].nIndx[36]=110;
ST[0].sRAD_K2[0].nIndx[37]=111;
ST[0].sRAD_K2[0].nIndx[38]=112;
ST[0].sRAD_K2[0].nIndx[39]=113;
ST[0].sRAD_K2[0].nIndx[40]=114;
ST[0].sRAD_K2[0].nIndx[41]=115;
ST[0].sRAD_K2[0].nIndx[42]=116;
ST[0].sRAD_K2[0].nIndx[43]=117;
ST[0].sRAD_K2[0].nIndx[44]=119;
ST[0].sRAD_K2[0].nIndx[45]=120;
ST[0].sRAD_K2[0].nIndx[46]=121;
ST[0].sRAD_K2[0].nIndx[47]=123;
ST[0].sRAD_K2[0].nIndx[48]=130;
ST[0].sRAD_K2[0].nIndx[49]=131;
ST[0].sRAD_K2[0].nIndx[50]=136;
ST[0].sRAD_K2[0].nIndx[51]=137;
ST[0].sRAD_K2[0].nIndx[52]=138;
ST[0].sRAD_K2[0].nIndx[53]=139;
ST[0].sRAD_K2[0].nIndx[54]=151;
ST[0].sRAD_K2[0].nIndx[55]=152;
ST[0].sRAD_K2[0].nIndx[56]=160;
ST[0].sRAD_K2[0].nIndx[57]=161;
ST[0].sRAD_K2[0].nIndx[58]=162;
ST[0].sRAD_K2[0].nIndx[59]=165;
ST[0].sRAD_K2[0].nIndx[60]=166;
ST[0].sRAD_K2[0].nIndx[61]=167;
ST[0].sRAD_K2[0].nIndx[62]=168;
ST[0].sRAD_K2[0].nIndx[63]=169;
ST[0].sRAD_K2[0].nIndx[64]=170;
ST[0].sRAD_K2[0].nIndx[65]=171;
ST[0].sRAD_K2[0].nIndx[66]=172;
ST[0].sRAD_K2[0].nIndx[67]=173;
ST[0].sRAD_K2[0].nIndx[68]=174;
ST[0].sRAD_K2[0].nIndx[69]=186;
ST[0].sRAD_K2[0].nIndx[70]=200;
ST[0].sRAD_K2[0].nIndx[71]=204;
ST[0].sRAD_K2[0].nIndx[72]=206;
ST[0].sRAD_K2[0].nIndx[73]=207;
ST[0].sRAD_K2[0].nIndx[74]=208;
ST[0].sRAD_K2[0].nIndx[75]=16;
ST[0].sRAD_K2[0].nIndx[76]=159;
ST[0].sRAD_K2[0].nIndx[77]=217;
ST[0].sRAD_K2[0].nIndx[78]=218;
ST[0].sRAD_K2[0].nIndx[79]=219;
ST[0].sRAD_K2[0].nIndx[80]=220;
ST[0].sRAD_K2[0].nIndx[81]=221;
ST[0].sRAD_K2[0].nIndx[82]=222;
ST[0].sRAD_K2[0].nIndx[83]=226;
ST[0].sRAD_K2[0].nIndx[84]=227;
ST[0].sRAD_K2[0].nIndx[85]=228;
ST[0].sRAD_K2[0].nIndx[86]=230;
ST[0].sRAD_K2[0].nIndx[87]=232;
ST[0].sRAD_K2[0].nIndx[88]=235;
ST[0].sRAD_K2[0].nIndx[89]=236;
ST[0].sRAD_K2[0].nIndx[90]=238;
ST[0].sRAD_K2[0].nIndx[91]=241;
ST[0].sRAD_K2[0].nIndx[92]=242;
ST[0].sRAD_K2[0].nIndx[93]=242;
ST[0].sRAD_K2[0].nIndx[94]=247;
ST[0].sRAD_K2[0].nIndx[95]=248;
ST[0].sRAD_K2[0].nIndx[96]=249;
ST[0].sRAD_K2[0].nIndx[97]=254;
ST[0].sRAD_K2[0].nIndx[98]=255;
ST[0].sRAD_K2[0].nIndx[99]=256;
ST[0].sRAD_K2[0].nIndx[100]=257;
ST[0].sRAD_K2[0].nIndx[101]=260;
ST[0].sRAD_K2[0].nIndx[102]=261;
ST[0].sRAD_K2[0].nIndx[103]=262;
ST[0].sRAD_K2[0].nIndx[104]=263;
ST[0].sRAD_K2[0].nIndx[105]=267;
ST[0].sRAD_K2[0].nIndx[106]=269;
ST[0].sRAD_K2[0].nIndx[107]=191;
ST[0].sRAD_K2[0].nIndx[108]=195;
ST[0].sRAD_K2[0].nIndx[109]=271;
ST[0].sRAD_K2[0].nIndx[110]=270;
ST[0].sRAD_K2[0].nIndx[111]=272;
ST[0].sRAD_K2[0].nIndx[112]=273;



/* K3 : ESZT, SOP, KOR, BI */
ST[0].sRAD_K3[0].nRtuNumRad = 71; /*55*/

ST[0].sRAD_K3[0].nIndx[0]=8; /*8*/
ST[0].sRAD_K3[0].nIndx[1]=32; /*32*/
ST[0].sRAD_K3[0].nIndx[2]=33;/*33*/
ST[0].sRAD_K3[0].nIndx[3]=34; /*34*/
ST[0].sRAD_K3[0].nIndx[4]=35; /*35*/
ST[0].sRAD_K3[0].nIndx[5]=36; /*36*/
ST[0].sRAD_K3[0].nIndx[6]=40;
ST[0].sRAD_K3[0].nIndx[7]=48;
ST[0].sRAD_K3[0].nIndx[8]=49;
ST[0].sRAD_K3[0].nIndx[9]=50;
ST[0].sRAD_K3[0].nIndx[10]=57;
ST[0].sRAD_K3[0].nIndx[11]=62; 
ST[0].sRAD_K3[0].nIndx[12]=63;
ST[0].sRAD_K3[0].nIndx[13]=66;
ST[0].sRAD_K3[0].nIndx[14]=67;
ST[0].sRAD_K3[0].nIndx[15]=70;
ST[0].sRAD_K3[0].nIndx[16]=73;
ST[0].sRAD_K3[0].nIndx[17]=74;
ST[0].sRAD_K3[0].nIndx[18]=78;
ST[0].sRAD_K3[0].nIndx[19]=83;
ST[0].sRAD_K3[0].nIndx[20]=84;
ST[0].sRAD_K3[0].nIndx[21]=124; 
ST[0].sRAD_K3[0].nIndx[22]=125;
ST[0].sRAD_K3[0].nIndx[23]=132;
ST[0].sRAD_K3[0].nIndx[24]=133;
ST[0].sRAD_K3[0].nIndx[25]=134;
ST[0].sRAD_K3[0].nIndx[26]=135;
ST[0].sRAD_K3[0].nIndx[27]=140;
ST[0].sRAD_K3[0].nIndx[28]=141;
ST[0].sRAD_K3[0].nIndx[29]=142;
ST[0].sRAD_K3[0].nIndx[30]=143;
ST[0].sRAD_K3[0].nIndx[31]=144; 
ST[0].sRAD_K3[0].nIndx[32]=145;
ST[0].sRAD_K3[0].nIndx[33]=146;
ST[0].sRAD_K3[0].nIndx[34]=147;
ST[0].sRAD_K3[0].nIndx[35]=148;
ST[0].sRAD_K3[0].nIndx[36]=156;
ST[0].sRAD_K3[0].nIndx[37]=157;
ST[0].sRAD_K3[0].nIndx[38]=158;
ST[0].sRAD_K3[0].nIndx[39]=205;
ST[0].sRAD_K3[0].nIndx[40]=176;
ST[0].sRAD_K3[0].nIndx[41]=177; 
ST[0].sRAD_K3[0].nIndx[42]=178;
ST[0].sRAD_K3[0].nIndx[43]=179;
ST[0].sRAD_K3[0].nIndx[44]=180;
ST[0].sRAD_K3[0].nIndx[45]=181;
ST[0].sRAD_K3[0].nIndx[46]=182;
ST[0].sRAD_K3[0].nIndx[47]=183;
ST[0].sRAD_K3[0].nIndx[48]=184;
ST[0].sRAD_K3[0].nIndx[49]=185;
ST[0].sRAD_K3[0].nIndx[50]=192;
ST[0].sRAD_K3[0].nIndx[51]=194; 
ST[0].sRAD_K3[0].nIndx[52]=198;
ST[0].sRAD_K3[0].nIndx[53]=199;
ST[0].sRAD_K3[0].nIndx[54]=203;
ST[0].sRAD_K3[0].nIndx[55]=193;
ST[0].sRAD_K3[0].nIndx[56]=129;
ST[0].sRAD_K3[0].nIndx[57]=189;
ST[0].sRAD_K3[0].nIndx[58]=210;
ST[0].sRAD_K3[0].nIndx[59]=7;
ST[0].sRAD_K3[0].nIndx[60]=239;
ST[0].sRAD_K3[0].nIndx[61]=246;
ST[0].sRAD_K3[0].nIndx[62]=252;
ST[0].sRAD_K3[0].nIndx[63]=253;
ST[0].sRAD_K3[0].nIndx[64]=258;
ST[0].sRAD_K3[0].nIndx[65]=259;
ST[0].sRAD_K3[0].nIndx[66]=265;
ST[0].sRAD_K3[0].nIndx[67]=266;
ST[0].sRAD_K3[0].nIndx[68]=268;
ST[0].sRAD_K3[0].nIndx[69]=190;
ST[0].sRAD_K3[0].nIndx[70]=118;







/*RST[0].sLINK RTUk indexei*/
ST[0].sLIN[0].nRtuNumLin = 8;
ST[0].sLIN[0].nIndx[0] =0;
ST[0].sLIN[0].nIndx[1] =4;
ST[0].sLIN[0].nIndx[2] =229;
ST[0].sLIN[0].nIndx[3] =10;
ST[0].sLIN[0].nIndx[4] =15;
ST[0].sLIN[0].nIndx[5] =75;
ST[0].sLIN[0].nIndx[6] =163;
ST[0].sLIN[0].nIndx[7] =164;



} /* end fnSetComPar()*/

