
#include<TM4C123.h>
void timer0_delay(int ms);
int main()
{
 SYSCTL->RCGCGPIO |= 0x20; // turn on bus clock for GPIOF
 GPIOF->DIR |= 0xE; // set RBG pins as digital output pin
 GPIOF->DEN |= 0xE; // Enable PF1-3 pinw as digital pin
while (1)
{
// implement Traffic Light sequence here
// GPIOF->DATA = 0x__; //Turn on RED LED at PF1
	//turning red on
	GPIOF->DATA ^= (1<<1);
	timer0_delay(1000); //Delay in milliseconds
	GPIOF->DATA &= ~(1<<1); //turning off after swtiching on for 1 sec 
// ...rest of the logic should go here for traffic system
	//turning red to green  
	timer0_delay(2000);
	GPIOF->DATA ^= (1<<3);
	timer0_delay(2000); //Delay in milliseconds
	GPIOF->DATA &= ~(1<<3); //turning off after swtiching on for 2 sec 
	
	//turning green to yellow (yellow is displayed just by swtiching on red and green ) on
	timer0_delay(2000);
	GPIOF->DATA ^= (1<<1);
	GPIOF->DATA ^= (1<<3);
	timer0_delay(1000); //Delay in milliseconds
	
	//turning off red and green
	GPIOF->DATA ^= ~(1<<1);
	GPIOF->DATA ^= ~(1<<3);
	
	timer0_delay(1000);
	
}
}
void timer0_delay(int ms) // ms is in milliseconds
{
SYSCTL->RCGCTIMER |= (1<<0); //enable clock for Timer 0
	
TIMER0->CTL |= 0x0; //disable timer 0 before initialization
TIMER0->CFG = 0x0; //select configuration for timer 0
TIMER0->TAMR = 0x1; //configure timer A for one shot mode
TIMER0->TAILR = 16000*ms - 1; //timer A interval load value register
TIMER0->ICR = 0x1; //clear status flag
TIMER0->CTL |= 0x1; //enable timer 0 to start counting afterinitializtion
while ((TIMER0->RIS & 0x1) == 0); //Wait for the GPTM Raw Interrupt Status flag to set
}
