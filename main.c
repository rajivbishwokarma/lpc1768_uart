
#include <LPC17xx.h>

void TransmitChar(char ch)
{
	while ( !(LPC_UART0->LSR & (1 << 5)));	// Wait for the data to be sent
	LPC_UART0->THR = ch;										// Loading data into THR	
}

char ReceiveChar()
{
	while( !(LPC_UART0->LSR & (1 << 0)));
	return LPC_UART0->RBR;
}

void initUART0(void)
{
	//Power
	LPC_SC->PCONP |= 1 << 3;		// Powering up UART0
	
	//Peripheral Clock
	//LPC_SC->PCLKSEL0 = 0x00 << 6;	// Providing 25Mhz clock to UART
	
	//PIN function select
	LPC_PINCON->PINSEL0  |= (1<<6)|(1<<4);	// Selecting UART0 as a transmitter
	LPC_PINCON->PINSEL0  &= ~(1<<7)|(1<<5);	// Selecting UART0 as a receiver
	//LPC_PINCON->PINMODE0 |= 3 << 0;	// Enabling pull-down resistors 
	
	//Baud Rate
	LPC_UART0->LCR |= (1 << 7)|(3 << 0);	// Setting DLAB 1 for DLL and DLM access and settin 8-bit character length
	LPC_UART0->DLL = 10;	// Setting 92 	in DLL	BR = 115200
	LPC_UART0->DLM = 0;
	LPC_UART0->FDR = 229;		//Setting DIVADDVAL and MULVAL
	
	//FIFO Enable
	LPC_UART0->FCR |= 1  << 0;	// Enabling FIFO
	
	//Interrupts
	LPC_UART0->LCR &= ~(1 << 7);			// Enabling access to interrupts
//	LPC_UART0->IER |= 1 << 1;			  // Enabling THRE Interrupt
	
	LPC_UART0->TER |= 0x1 << 7;		// Enable data sending; default is 1
	
	//Data Transfer
	//LPC_UART0->LCR |= 0x0  << 7;	// Setting DLAB for allowing the UART0 THR access
    //LPC_UART0->LCR |= 3;	// Selecting 8-character length for transmission
	//LPC_UART0->LCR = 0x00 << 2;	  // 1-bit stop signal and disable parity
}

int main()
{
	//char helloWorld[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\n','\0'};
//	char helloWorld[] = {(char) 2, (char) 4, (char) 6, (char) 8};
	
	int32_t index = 0;
	char ch_receive = 0;
	int32_t loop_counter = 0;
	//Initialize all the required parameters
	initUART0();
		
	//Transmitting Hello World
//	while(1)
//	{
		//while (helloWorld[index] ) != '\0') 
//		while (loop_counter < 5)
//		{
//				TransmitChar(helloWorld[index]);
//				index++;
//				loop_counter++;
//		}
//		index=0;	
//		for (int32_t i = 0; i < 10000000; i++);
//	}
	
	Receive and transmit
	while(1)
	{
		ch_receive = ReceiveChar();
		TransmitChar(ch_receive);
	}

	return 0;
}
