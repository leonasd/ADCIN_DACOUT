#include <msp430f5529.h>

#define SYNC_HIGH   P6OUT |= BIT5
#define SYNC_LOW    P6OUT &= ~BIT5
#define SCLK_HIGH   P4OUT |= BIT1
#define SCLK_LOW    P4OUT &= ~BIT1
#define DIN_HIGH    P1OUT |= BIT6
#define DIN_LOW     P1OUT &= ~BIT6


void gpio_init()
{
    P1DIR |= BIT6;
    P4DIR |= BIT1;
    P6DIR |= BIT5;
}

void DAC8411_Init()
{
    gpio_init();

    SCLK_HIGH;
    SYNC_HIGH;
}

void write2DAC8411(unsigned int Data)
{
    unsigned int Temp = 0;
    unsigned char i = 0;

    Temp = Data;
    SYNC_LOW;
    SCLK_HIGH;
    DIN_LOW;
    SCLK_LOW;
    SCLK_HIGH;
    DIN_LOW;
    SCLK_LOW;

    for(i=0; i<16; i++)
    {
    	SCLK_HIGH;

    	if(Temp & BITF)   DIN_HIGH;
    	else                     DIN_LOW;

    	SCLK_LOW;
    	Temp = Temp << 1;
    }

    SYNC_HIGH;
}


