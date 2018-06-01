

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
char trama[60] = {
	0x00, 0xa0, 0x24, 0x14, 0x49, 0x4a, 0x00, 0xa0, /* ..$.IJ.. */
	0x24, 0x14, 0x49, 0xaa, 0x00, 0x04, 0xf0, 0xf0, /* $.I..... */
	0x0a, 0x3b, 0x00, 0x00, 0xff, 0xef, 0x16, 0x0c, /* .;...... */
	0x00, 0x00, 0x28, 0x00, 0x28, 0x00, 0x0c, 0x0f, /* ..(.(... */
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, /*          */
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, /*          */
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, /*          */
	0x20, 0x20, 0x20, 0x20                          /*      */
	};

	char trama2[60]={

	0x00,  0xa0,  0x24,  0x14,  0x49,  0x4a,  0x00,  0xa0,
	0x24  ,0x14  ,0x49  ,0x08  ,0x00  ,0x03  ,0xf0  ,0xf0  ,
	0x8f  ,0x3b  ,0x00  ,0x00  ,0xff  ,0xef  ,0x16  ,0x0c  ,
	0x00  ,0x00  ,0x28  ,0x00  ,0x28  ,0x00  ,0x0c  ,0x0f  ,
	0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,
	0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,
	0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,0x20  ,
	0x20  ,0x20  ,0x20  ,0x20  };
	char resultado[100];

char *PF[] = {"p", "f"};
char *RC[] = {"(C)", "(R)"};
int  llc( char  trama[],  int  longitud, char  resultado[]){ 
  
    strcpy(resultado,"");
    int tam;
    tam = trama[12]*256+trama[13];
    //char *cad="";
    if(tam<1500){
    switch(trama[16]&3){
    case 0:
    case 2:
  
     sprintf(resultado,"I, N(S)=%d, N(R)=%d, %s %s", trama[16]>>1,trama[17]>>1,
     PF[trama[15]&1],RC[trama[15]&1]);
       strcat(resultado,"");
 
    break;
    case 1:
    switch(trama[16]&12){
			case 1: //SS=00 RR
				sprintf(resultado,"RR, N(R)=%d, %s %s",trama[17]>>1,PF[trama[15]&1],RC[trama[15]&1]);
				strcat(resultado,"");
				
			break;
			case 8: //SS=01 REJ
				sprintf(resultado,"REJ, N(R)=%d, %s %s",trama[17]>>1,PF[trama[15]&1],RC[trama[15]&1]);
				strcat(resultado,"");
				//strcat(resultado,"REJ\0");
			break;
			case 4: //SS=10 RNR	
				sprintf(resultado,"RNR, N(R)=%d, %s %s",trama[17]>>1,PF[trama[15]&1],RC[trama[15]&1]);
				strcat(resultado,"");
			//	strcat(resultado,"RNR\0");
			break;
			case 12: //SS=11 SREJ
				sprintf(resultado,"SREJ, N(R)=%d, %s %s",trama[17]>>1,PF[trama[15]&1],RC[trama[15]&1]);
				strcat(resultado,"");
			//	strcat(resultado,"SREJ\0");
			break;			
		
    
 		}
 	break;
    case 3:
	switch(trama[16]&12){
			case 0: ///MM=00
				switch(trama[16]&224){
					case 0:///UI M=000 && SAPOrigen 1 en bit menos significativo resultado 
						sprintf(resultado,"UI, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 32:///UP M=001
						sprintf(resultado,"UP, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 64:///DISC M=010 && SAPOrigen 1 en bit menos sign resultado
						if((trama[15]&1)==1){
							sprintf(resultado,"RD, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
							strcat(resultado,"");
						}
					else if((trama[15]&1)==0){
							sprintf(resultado,"DISC, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
							strcat(resultado,"");
						}
						
					break;
					case 96:///UA M= 011
						sprintf(resultado,"UA, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 128:///SNRM M=100  
						sprintf(resultado,"SNRM, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
				}
			break;
		
			case 8: ///MM=10
				if((trama[16]&224)==0 && (trama[15]&1)==1){///RIM M=000 && SAPOrigen 1 en bit menos sign resultado
					sprintf(resultado,"RIM, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
					strcat(resultado,"");
				}
				else if(((trama[16]&224)==0) && ((trama[15]&1)==0)){//SIM M=000 && SAPOrigen 0 en bit menos sign command
					sprintf(resultado,"SIM, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
					strcat(resultado,"");
				}
				else if((trama[16]&224)==0){//SIM/RIM M=000
					sprintf(resultado,"FRMR, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
					strcat(resultado,"");
				}
				
			break;
			
			case 12: ///MM=11
				switch(trama[16]&224){
					case 192: ///SNRME MMM=110
						sprintf(resultado,"SNRME, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 0: ///SARM MMM=000 && SAPOrigen 1 en bit menos significativo = DM, si SAPOrigen 0 en bit menos significativo = SARM;
						if((trama[15]&1)==1){
							sprintf(resultado,"DM, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
							strcat(resultado,"");
						}
						else if((trama[15]&1)==0){
							sprintf(resultado,"SARM, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
							strcat(resultado,"");
						}
					break;
					case 64: ///SARME MMM=010
						sprintf(resultado,"SARME, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 32: ///SABM MMM=001
						sprintf(resultado,"SABM, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 96:///SABME MMM=011
						sprintf(resultado,"SABME, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 128:///RSET MMM=100 
						sprintf(resultado,"RSET, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
					case 160: ///XID MMM=101 && SAPOrigen 1 en bit menos sign resultado
						sprintf(resultado,"XID, %s %s",PF[trama[15]&1],RC[trama[15]&1]);
						strcat(resultado,"");
					break;
				}
			break;
			
			}
		    
        }
        

        return 1;
     }

        return 0; 
    }
    
void main()
{ 
if(llc(trama,sizeof(trama),resultado))
    printf("%s\n",resultado);

if(llc(trama2,sizeof(trama),resultado))
    printf("%s",resultado);

}