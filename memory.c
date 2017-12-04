
#include <p18cxxx.h>
#include "delay.h"
#include "canf8.h"


/*------------------*/



void mem_wr(unsigned char adress, unsigned char Data)
{

EEADR=adress;
EEDATA=Data;
EECON1bits.CFGS=0;
EECON1bits.EEPGD=0;
EECON1bits.WREN=1;
INTCONbits.GIE=0;

EECON2=0x55;
EECON2=0xAA;

EECON1bits.WR=1;

INTCONbits.GIE=1;

while(!PIR2bits.EEIF)
{}

PIR2bits.EEIF=0;

EECON1bits.WREN=1;

}




/*------------------*/




void  mem_rd(unsigned char adress,unsigned char *Data)
{
unsigned char Dataread=0;

EEADR=adress;
EECON1bits.CFGS=0;
EECON1bits.EEPGD=0;
EECON1bits.RD=1;

while(EECON1bits.RD)
{}

Dataread=EEDATA;
*Data=Dataread;


}



/*------------------*/

void send_m1(void)
{
unsigned char m0=0, m1=0, m4=0, m5=0;
delay(20);
mem_rd(0x00,&m0);

delay(20);
mem_rd(0x01,&m1);

delay(20);
mem_rd(0x02,&m4);

delay(20);
mem_rd(0x03,&m5);
delay(20);

tr_can1(0b01110000, m0,m1,0,0, m4, m5, 0, 0 );

}


/*------------------*/

void send_m2(void)
{
unsigned char m0=0,m1=0,m4=0,m5=0;
delay(20);
mem_rd(0x04,&m0);

delay(20);
mem_rd(0x05,&m1);

delay(20);
mem_rd(0x06,&m4);

delay(20);
mem_rd(0x07,&m5);
delay(20);

tr_can1(0b10110000,m0,m1,0,0,m4,m5,0,0);

}

/*------------------*/

void send_m3(void)
{
unsigned char m0=0,m1=0,m2=0,m3=0,m4=0,m5=0;

delay(20);
mem_rd(0x08,&m0);

delay(20);
mem_rd(0x09,&m1);

delay(20);
mem_rd(0x0A,&m2);

delay(20);
mem_rd(0x0B,&m3);

delay(20);
mem_rd(0x0C,&m4);

delay(20);
mem_rd(0x0D,&m5);
delay(20);

tr_can1(0b11010000,m0,m1,m2,m3,m4,m5,0,0);
}

/*------------------*/

void send_m4(void)
{
unsigned char m0=0, m1=0, m2=0;

delay(20);
mem_rd(0x0E,&m0);

delay(20);
mem_rd(0x0F,&m1);

delay(20);
mem_rd(0x10,&m2);
delay(20);

tr_can1(0b11100000,m0,m1,m2,0,0,0,0,0);
}

/*------------------*/


void send_did(unsigned int i)
{
unsigned int buff=0;
unsigned char m4=0, m5=0;
m4=i;
m5=(i>>8);
tr_can1(0b10000000,0,0,0,0,m4,m5,0,0);
}






