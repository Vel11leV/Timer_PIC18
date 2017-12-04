
#include <p18cxxx.h>
#include "delay.h"
#include "timer.h"
#include "canf8.h"
#include "memory.h"

void main(void)
{
unsigned int  command=0;

unsigned int T11,T12;
unsigned int cycles1;

unsigned int T21,T22;
unsigned int cycles2;

unsigned int T31,T32,T33,T34;
unsigned int cycles3;

unsigned int T41,T42,T43;

unsigned char mode=0;
unsigned char  ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
unsigned int buff=0,ident=0;
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*---------------инициализация портов таймера и CAN----------------------*/
initports();
PORTA=0b000000;
timer2init();
Init_can ();
RXB0CONbits.RXFUL=0;
resrb0_init();
delay(10);
//tr_can1(0,0,0,0,0,0,0,0,0);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

while(1)
{
can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );

/*-----------------------*/
if(ident==0b111)
{
	ident=0;
	command=ms0;
	ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
		if (command==0x0F)
		{
		command=0;
		PORTA=0b000000;
		delay(50);
		PORTA=0b000110;
		delay(10);
		PORTA=0b000010;
		delay(40);
		PORTA=0b000000;
		}


		if (command==0xF0)
		{
		command=0;
		PORTA=0b000000;
		delay(50);
		PORTA=0b000101;
		delay(10);
		PORTA=0b000001;
		delay(40);
		PORTA=0b000000;
		}
		
		if(command==0x11)
		{
		command==0;
		delay(10);

		send_m1();
		delay(10);

		send_m2();
		delay(10);

		send_m3();
		delay(10);

		send_m4();
		delay(10);
		}

/*-+_+-----------------------------+_+-*//*-+_+-----------------------------+_+-*/

		if(command==0xAA&&mode==1)
		{
		
		unsigned int i, j;
		unsigned int tg1=0, tg2=0;
		unsigned char esc=0,pause=0;
		command=0;

		PORTA=0b000000;
		delay(200);
		
		if((T12*1000)>(T11*100))
			{	
				tg1=(T11*100)-50;
				tg2=(T12*1000)-(T11*100)-50;

				for(i=0;i<cycles1;i++)
				{
				PORTA=0b000110;
				delay(10);
				PORTA=0b000010;
				delay(40);
				PORTA=0b000000;
					for(j=0;j<tg1;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}

					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}

					}

				if(esc)
				{esc=0;break;}
				command=0;
				PORTA=0b000101;
				delay(10);
				PORTA=0b000001;
				delay(40);
				PORTA=0b000000;
				send_did(i+1);
					for(j=0;j<tg2;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}

					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}
					}

					if(esc)
					{esc=0;break;}

					

				}
			}
		PORTA=0b000000;
		}



/*-+_+-----------------------------+_+-*//*-+_+-----------------------------+_+-*/


		if(command==0xAA&&mode==2)
		{
		unsigned int i, j;
		unsigned int tg21=0, tg22=0;
		unsigned char esc2=0,pause=0;
		command=0;

		PORTA=0b000000;
		delay(200);
/////////////////////
		if(T21>=50)
			{	
				tg21=(T21-50);
				tg22=(T22*1000)-T21-50;

				for(i=0;i<cycles2;i++)
				{
				PORTA=0b000110;
				delay(10);
				PORTA=0b000010;
				delay(40);
				PORTA=0b000000;
					for(j=0;j<tg21;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc2=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}
					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc2=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}

					}
				if(esc2)
				{esc2=0;break;}
				command=0;
				PORTA=0b000101;
				delay(10);
				PORTA=0b000001;
				delay(40);
				PORTA=0b000000;
	`			send_did(i+1);
					for(j=0;j<tg22;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc2=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}
					
					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc2=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}
					}
					if(esc2)
					{esc2=0;break;}
				}
			}
////////////////////////
			if(T21<=40)
			{
				tg21=T21;
				tg22=(T22*1000)-T21-50;

				for(i=0;i<cycles2;i++)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(tg21-10);
					PORTA=0b000111;
					delay(10);
					PORTA=0b000011;
					delay(40-tg21);
					PORTA=0b000001;
					delay(tg21);
					PORTA=0b000000;
					send_did(i+1);
					for(j=0;j<tg22;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc2=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}
					
					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc2=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}

					}
					if(esc2)
					{esc2=0;break;}
					}

			}
///////////////////////
			if(T21>40&&T21<50)
			{
				
				tg21=T21;
				tg22=(T22*1000)-T21-50;

				for(i=0;i<cycles2;i++)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(tg21-10);
					PORTA=0b000111;
					delay(50-tg21);
					PORTA=0b000101;
					delay(tg21-40);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					send_did(i+1);
					for(j=0;j<tg22;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc2=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}
					
					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc2=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}

					}
					if(esc2)
					{esc2=0;break;}
					}
			}

PORTA=0b000000;
		
}


/*-+_+-----------------------------+_+-*//*-+_+-----------------------------+_+-*/



	if(command==0xAA&&mode==3)

	{

		unsigned int i, j;
		unsigned int tg31=0, tg32=0;
		unsigned char esc3=0,pause=0;
		command=0;
		tg31=(T32*1000)-50-T31;
		tg32=(T34*1000)-50;
		PORTA=0b000000;
		delay(200);

	
			for(i=0;i<cycles3;i++)
			{
				PORTA=0b000101;
				delay(10);
				PORTA=0b000001;
				delay(40);
				PORTA=0b000000;
				//////////////////////
				if(T31>=50)
					{
					delay(T33-50);
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(40);
					PORTA=0b000000;

					delay(T31-50);
					PORTA=0b000101;
					delay(10);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				if(T31<=40)
					{
					delay(T33-50);
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T31-10);
					PORTA=0b000111;
					delay(10);
					PORTA=0b000011;
					delay(40-T31);
					PORTA=0b000001;
					delay(T31);
					PORTA=0b000000;
					}
				//////////////////////
				if(T31>40&&T31<50)
					{
					delay(T33-50);
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T31-10);
					PORTA=0b000111;
					delay(50-T31);
					PORTA=0b000101;
					delay(T31-40);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				
			
					for(j=0;j<tg31;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc3=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}
					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc3=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}
					

					}
					if(esc3)
					{esc3=0;break;}

				delay(T33-50);
				PORTA=0b000110;
				delay(10);
				PORTA=0b000010;
				delay(40);
				PORTA=0b000000;	
				send_did(i+1);
			
					for(j=0;j<tg32;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc3=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}
					
					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc3=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}

					}
					if(esc3)
					{esc3=0;break;}
			}

			PORTA=0b000000;		
			
			
			
			
				
		
		}





/*-+_+-----------------------------+_+-*//*-+_+-----------------------------+_+-*/

if(command==0xAA&&mode==4)
{
		unsigned int i, j;
		unsigned int tg41=0;
		unsigned char esc4=0, pause=0;;
		command=0;
		tg41=(T42*1000)-50-T41;
		
		PORTA=0b000000;
		delay(200);



	for (i=0;i<1;i++)
	{
				PORTA=0b000101;
				delay(10);
				PORTA=0b000001;
				delay(40);
				PORTA=0b000000;
				//////////////////////
				if(T41>=50)
					{
					delay(T43-50);
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(40);
					PORTA=0b000000;

					delay(T41-50);
					PORTA=0b000101;
					delay(10);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				if(T41<=40)
					{
					delay(T43-50);
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T41-10);
					PORTA=0b000111;
					delay(10);
					PORTA=0b000011;
					delay(40-T41);
					PORTA=0b000001;
					delay(T41);
					PORTA=0b000000;
					}
				//////////////////////
				if(T41>40&&T41<50)
					{
					delay(T43-50);
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T41-10);
					PORTA=0b000111;
					delay(50-T41);
					PORTA=0b000101;
					delay(T41-40);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				
			
					for(j=0;j<tg41;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc4=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}

					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc4=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}
					}
					if(esc4)
					{esc4=0;break;}

				//////////////////////
				if(T41>=50)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(40);
					PORTA=0b000000;

					delay(T41-50);
					PORTA=0b000101;
					delay(10);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				if(T41<=40)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T41-10);
					PORTA=0b000111;
					delay(10);
					PORTA=0b000011;
					delay(40-T41);
					PORTA=0b000001;
					delay(T41);
					PORTA=0b000000;
					}
				//////////////////////
				if(T41>40&&T41<50)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T41-10);
					PORTA=0b000111;
					delay(50-T41);
					PORTA=0b000101;
					delay(T41-40);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				
			
					for(j=0;j<tg41;j++)
					{
					delay(1);
							if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xFF)
								{
								command=0;
								esc4=1;
								break;
								}
								if(command==0xDD)
								{
								command=0;
								pause=1;
								}
								else
								{
								command=0;
								}
							}
					while(pause)
					{
						if (RXB0CONbits.RXFUL)
							{
								can_read(&ident,&ms0,&ms1,&ms2,&ms3,&ms4,&ms5,&ms6,&ms7 );
								if(ident==0b111)
								{
								command=ms0;
								ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
								}
								if(command==0xAA)
								{
								command=0;
								pause=0;
								}
								if(command==0xFF)
								{
								command=0;
								pause=0;
								esc4=1;
								break;
								}
								else
								{
								command=0;
								}
							}
					}					


					}
					if(esc4)
					{esc4=0;break;}

				//////////////////////
				if(T41>=50)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(40);
					PORTA=0b000000;

					delay(T41-50);
					PORTA=0b000101;
					delay(10);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				if(T41<=40)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T41-10);
					PORTA=0b000111;
					delay(10);
					PORTA=0b000011;
					delay(40-T41);
					PORTA=0b000001;
					delay(T41);
					PORTA=0b000000;
					}
				//////////////////////
				if(T41>40&&T41<50)
					{
					PORTA=0b000110;
					delay(10);
					PORTA=0b000010;
					delay(T41-10);
					PORTA=0b000111;
					delay(50-T41);
					PORTA=0b000101;
					delay(T41-40);
					PORTA=0b000001;
					delay(40);
					PORTA=0b000000;
					}
				//////////////////////
				PORTA=0b000000;
		send_did(i+1);
		}
}
/*-+_+-----------------------------+_+-*//*-+_+-----------------------------+_+-*/		
		else (command=0);

}

/*----------------------*/
//////////////////////////
/*----------------------*/






if(ident==0b01110000000)
{
T11=ms0;
T12=ms1;
cycles1=ms5;
cycles1=(cycles1<<8);
cycles1=(cycles1+ms4);
mode=1;
ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
		
}

/*----------------------*/
if(ident==0b10110000000)
{
T21=ms0;
T22=ms1;
cycles2=ms5;
cycles2=(cycles2<<8);
cycles2=(cycles2+ms4);
mode=2;
ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
	
}

/*----------------------*/
if(ident==0b11010000000)
{
T31=ms0;
T32=ms1;
T33=ms2;
T34=ms3;
cycles3=ms5;
cycles3=(cycles3<<8);
cycles3=(cycles3+ms4);
mode=3;
ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
		
}

/*----------------------*/
if(ident==0b11100000000)
{
T41=ms0;
T42=ms1;
T43=ms2;
mode=4;
ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
	
}











/*----------------------*/
//////////////////////////
/*----------------------*/

if(ident==0b01110000111)
{
unsigned char m0=0, m1=0, m4=0, m5=0;

T11=ms0;
T12=ms1;
cycles1=ms5;
cycles1=(cycles1<<8);
cycles1=(cycles1+ms4);

mem_wr(0x00,ms0);
delay(20);
mem_rd(0x00,&m0);
delay(20);

mem_wr(0x01,ms1);
delay(20);
mem_rd(0x01,&m1);
delay(20);

mem_wr(0x02,ms4);
delay(20);
mem_rd(0x02,&m4);
delay(20);

mem_wr(0x03,ms5);
delay(20);
mem_rd(0x03,&m5);
delay(20);

while(!(m0==ms0&&m1==ms1&&m4==ms4&&m5==ms5))
{ }


ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
		
}


/*----------------------*/
/*----------------------*/

if(ident==0b10110000111)
{

unsigned char m0=0, m1=0, m4=0, m5=0;

T21=ms0;
T22=ms1;
cycles2=ms5;
cycles2=(cycles2<<8);
cycles2=(cycles2+ms4);


mem_wr(0x04,ms0);
delay(20);
mem_rd(0x04,&m0);
delay(20);

mem_wr(0x05,ms1);
delay(20);
mem_rd(0x05,&m1);
delay(20);

mem_wr(0x06,ms4);
delay(20);
mem_rd(0x06,&m4);
delay(20);

mem_wr(0x07,ms5);
delay(20);
mem_rd(0x07,&m5);
delay(20);

while(!(m0==ms0&&m1==ms1&&m4==ms4&&m5==ms5))
{ }
ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
		
}


/*----------------------*/
/*----------------------*/


if(ident==0b11010000111)
{

unsigned char m0=0, m1=0, m2=0, m3=0, m4=0, m5=0;

T31=ms0;
T32=ms1;
T33=ms2;
T34=ms3;
cycles3=ms5;
cycles3=(cycles3<<8);
cycles3=(cycles3+ms4);


mem_wr(0x08,ms0);
delay(20);
mem_rd(0x08,&m0);
delay(20);

mem_wr(0x09,ms1);
delay(20);
mem_rd(0x09,&m1);
delay(20);

mem_wr(0x0A,ms2);
delay(20);
mem_rd(0x0A,&m2);
delay(20);

mem_wr(0x0B,ms3);
delay(20);
mem_rd(0x0B,&m3);
delay(20);

mem_wr(0x0C,ms4);
delay(20);
mem_rd(0x0C,&m4);
delay(20);

mem_wr(0x0D,ms5);
delay(20);
mem_rd(0x0D,&m5);
delay(20);

while(!(m0==ms0&&m1==ms1&&m2==ms2&&m3==ms3&&m4==ms4&&m5==ms5))
{ }


ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
	
}

/*----------------------*/
/*----------------------*/

if(ident==0b11100000111)
{
unsigned char m0=0, m1=0, m2=0;

T41=ms0;
T42=ms1;
T43=ms2;

mem_wr(0x0E,ms0);
delay(20);
mem_rd(0x0E,&m0);
delay(20);

mem_wr(0x0F,ms1);
delay(20);
mem_rd(0x0F,&m1);
delay(20);

mem_wr(0x10,ms2);
delay(20);
mem_rd(0x10,&m2);
delay(20);

while(!(m0==ms0&&m1==ms1&&m2==ms2))
{ }


ident=0, ms0=0, ms1=0, ms2=0, ms3=0, ms4=0, ms5=0, ms6=0, ms7=0;
	
}
/*----------------------*/
//////////////////////////
/*----------------------*/



}
}
