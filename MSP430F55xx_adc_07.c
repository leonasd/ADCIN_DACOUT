#include <msp430.h>
#include <DAC7811.h>
//#include <LCD5510_V2.H>
//#include <stdio.h>

volatile unsigned int result = 0;

void SetVcoreUp (unsigned int level)
{
  PMMCTL0_H = PMMPW_H;
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  PMMCTL0_L = PMMCOREV0 * level;
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  PMMCTL0_H = 0x00;
}

void GPIO_Init()
{
    //P3DIR |= BIT3 + BIT7;
    //P4DIR |= BIT0 + BIT3;
//    P8DIR |= BIT1 + BIT2;
    P1DIR |= BIT0 + BIT2;
    P1SEL |= BIT2;
    P6SEL |= BIT0;                            // Enable A/D channel A0
}

int main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer

    SetVcoreUp (0x01);
    SetVcoreUp (0x02);
    SetVcoreUp (0x03);

    UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO
    UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

    __bis_SR_register(SCG0);                  // Disable the FLL control loop
    UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_7;                      // Select DCO range 50MHz operation
    UCSCTL2 = FLLD_0 + 762;                   // Set DCO Multiplier for 25MHz

    __bic_SR_register(SCG0);                  // Enable the FLL control loop
    __delay_cycles(782000);

    // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
    do
    {
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                              // Clear XT2,XT1,DCO fault flags
      SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag


  GPIO_Init();
  DAC8411_Init();
  //LCD5510_Init();

  ADC12CTL0 = ADC12ON+ADC12SHT0_4 + ADC12REFON + ADC12REF2_5V;
  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_2 + ADC12SHS_1;       // Use sampling timer, set mode
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 |= ADC12ENC;
  //ADC12CTL0 |= ADC12SC;

    //TA0CCTL1 = CCIE;                          // CCR0 interrupt enabled
    TA0CCR0 = 3050;
    TA0CCR1 = 20;
    TA0CCTL1 |= OUTMOD_3;                       // CCR1 set/reset mode
    TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, upmode, clear TAR

  __enable_interrupt();
  while(1)
  {
	  //__bis_SR_register(LPM0_bits + GIE);       // Enter LPM4, Enable interrupts
	  __no_operation();                         // For debugger
  }
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
	switch(__even_in_range(ADC12IV,34))
	{
		case  0: break;                           // Vector  0:  No interrupt
		case  2: break;                           // Vector  2:  ADC overflow
		case  4: break;                           // Vector  4:  ADC timing overflow
		case  6:
			           result = ADC12MEM0;        // Vector  6:  ADC12IFG0
				       P1OUT ^= 0x01;
				       write2DAC8411(result);
		               break;
		case  8: break;                           // Vector  8:  ADC12IFG1
		case 10: break;                           // Vector 10:  ADC12IFG2
		case 12: break;                           // Vector 12:  ADC12IFG3
		case 14: break;                           // Vector 14:  ADC12IFG4
		case 16: break;                           // Vector 16:  ADC12IFG5
		case 18: break;                           // Vector 18:  ADC12IFG6
		case 20: break;                           // Vector 20:  ADC12IFG7
		case 22: break;                           // Vector 22:  ADC12IFG8
		case 24: break;                           // Vector 24:  ADC12IFG9
		case 26: break;                           // Vector 26:  ADC12IFG10
		case 28: break;                           // Vector 28:  ADC12IFG11
		case 30: break;                           // Vector 30:  ADC12IFG12
		case 32: break;                           // Vector 32:  ADC12IFG13
		case 34: break;                           // Vector 34:  ADC12IFG14
		default: break;
	}
}


//#pragma vector=TIMER0_A1_VECTOR
//__interrupt void TIMER0_A1_ISR(void)
//{
//	//P1OUT ^= 0x01;                            // Toggle P1.0
//	//ADC12CTL0 |= ADC12SC;
//	TA0CCTL1 &= ~CCIFG;
//}

