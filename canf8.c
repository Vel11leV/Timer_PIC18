/*500kBt*/


#include "p18cxxx.h"


void Init_can (void)
{
/*------------------------------настройка портов------------------------------*/
TRISBbits.TRISB3=1;
TRISBbits.TRISB2=0;

/*---------------------------вход в режим настройки---------------------------*/
CANCONbits.REQOP2=0b1;
CANCONbits.REQOP1=0b0;
CANCONbits.REQOP0=0b0;
while(!CANCONbits.REQOP2){};

/*-------------------------сброс всех масок и фильтров------------------------*/
RXM0SIDH=0;
RXM1SIDH=0;

RXM0SIDL=0;
RXM1SIDL=0;

RXM0EIDH=0;
RXM1EIDH=0;

RXM0EIDL=0;
RXM1EIDL=0;

/*--------------------------настройка приемных буферов-------------------------*/
RXB0CONbits.RXM1=0b0;
RXB0CONbits.RXM0=0b1;
RXB0CONbits.RXB0DBEN=0b0; //запрет на дублирование


CIOCONbits.CANCAP=0;


/*--------------------------настройка скорости передачи-----2*4/Fosc-------------------*/
BRGCON1bits.BRP5=0b0;
BRGCON1bits.BRP4=0b0;
BRGCON1bits.BRP3=0b0;
BRGCON1bits.BRP2=0b0;
BRGCON1bits.BRP1=0b1;
BRGCON1bits.BRP0=0b1;


/*----------------------свободное программирование второго фазового сегмента---*/
BRGCON2bits.SEG2PHTS=1;

/*---------------------------------выборка 1 раз-------------------------------*/
BRGCON2bits.SAM=0b0;

/*------------------------no wake up when bus is active------------------------*/
BRGCON3bits.WAKFIL=0;



/*----------------------------------PropSeg=2TQ--------------------------------*/
BRGCON2bits.PRSEG2=0b0;
BRGCON2bits.PRSEG1=0b0;    //
BRGCON2bits.PRSEG0=0b1;

/*------------------------------------PS1=7TQ-----------------------------------*/
BRGCON2bits.SEG1PH2=0b1;
BRGCON2bits.SEG1PH1=0b1;
BRGCON2bits.SEG1PH0=0b1;

/*------------------------------------PS2=6TQ-----------------------------------*/
BRGCON3bits.SEG2PH2=0b1;
BRGCON3bits.SEG2PH1=0b1;
BRGCON3bits.SEG2PH0=0b0;

/*------------------------------------SJW=1TQ-----------------------------------*/
BRGCON1bits.SJW1=0b0;
BRGCON1bits.SJW0=0b0;

/*-----------------выход из режима настройки в нормальный режим работы----------*/
CANCONbits.REQOP2=0b0;
CANCONbits.REQOP1=0b0;
CANCONbits.REQOP0=0b0;
while((CANCONbits.REQOP2)&&(CANCONbits.REQOP1)&&(CANCONbits.REQOP0=0b0)){};
}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void tr_can1(unsigned char ident, unsigned char mes1,unsigned char mes2,unsigned char mes3,unsigned char mes4, unsigned char mes5, unsigned char mes6, unsigned char mes7, unsigned char mes8 )
{

TXB0SIDH=ident;

TXB0SIDLbits.SID2=0b0;
TXB0SIDLbits.SID1=0b0;
TXB0SIDLbits.SID0=0b0;

TXB0SIDLbits.EXIDE=0b0;

TXB0SIDLbits.EID17=0b0;
TXB0SIDLbits.EID16=0b0;




TXB0D0=mes1;
TXB0D1=mes2;
TXB0D2=mes3;
TXB0D3=mes4;
TXB0D4=mes5;
TXB0D5=mes6;
TXB0D6=mes7;
TXB0D7=mes8;
TXB0DLC=8;
TXB0CONbits.TXREQ=0b1;
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void tr_can2(unsigned char ident, unsigned char mes1,unsigned char mes2,unsigned char mes3,unsigned char mes4, unsigned char mes5, unsigned char mes6, unsigned char mes7, unsigned char mes8 )
{

TXB0SIDH=ident;

TXB0SIDLbits.SID2=0b1;
TXB0SIDLbits.SID1=0b1;
TXB0SIDLbits.SID0=0b1;

TXB0SIDLbits.EXIDE=0b0;

TXB0SIDLbits.EID17=0b0;
TXB0SIDLbits.EID16=0b0;




TXB0D0=mes1;
TXB0D1=mes2;
TXB0D2=mes3;
TXB0D3=mes4;
TXB0D4=mes5;
TXB0D5=mes6;
TXB0D6=mes7;
TXB0D7=mes8;
TXB0DLC=8;
TXB0CONbits.TXREQ=0b1;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void resrb0_init()
{
RXB0CONbits.RXM1=0b1; //принимать 
RXB0CONbits.RXM0=0b1; //все сообщения
RXB0CONbits.RXFUL=0;  //приемный буфер готов к приему сообщения
}

//++++++++++++++++++++//

void can_read(unsigned int *ident, unsigned int *ms0, unsigned int *ms1, unsigned int *ms2, unsigned int *ms3, unsigned int *ms4, unsigned int *ms5, unsigned int *ms6, unsigned int *ms7 )
{
if (RXB0CONbits.RXFUL)
{
unsigned int iden=0, m0=0, m1=0, m2=0, m3=0, m4=0, m5=0, m6=0, m7=0;

iden=RXB0SIDH;
iden=(iden<<3);
if(RXB0SIDLbits.SID1==1)
{iden=iden+0b10;}
if(RXB0SIDLbits.SID0==1)
{iden=iden+0b1;}
if(RXB0SIDLbits.SID2==1)
{iden=iden+0b100;}

*ident=iden;

*ms0=RXB0D0;
*ms1=RXB0D1;
*ms2=RXB0D2;
*ms3=RXB0D3;
*ms4=RXB0D4;
*ms5=RXB0D5;
*ms6=RXB0D6;
*ms7=RXB0D7;
RXB0CONbits.RXFUL=0;
}
}
//++++++++++++++++++++//
