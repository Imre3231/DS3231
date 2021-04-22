
 


void  OpenI2C(void)
{
    
    TRISCbits.TRISC5 = 0;
	TRISCbits.TRISC4 = 0;
	//This function will initialize the I2C(1) peripheral.
	
	//Set the I2C(1) BRG Baud Rate.
	//(((1/400KHz)-130ns)x40MIPs)-2 = 93
	I2C1BRG = 0x90; 
	

	//Now we will initialise the I2C peripheral for Master Mode, No Slew Rate
	//Control, SMbus levels, and leave the peripheral switched off.
	
	I2C1CONbits.I2CEN = 0;
	I2C1CONbits.I2CSIDL = 0;
	I2C1CONbits.SCLREL = 1;
	I2C1CONbits.IPMIEN = 0;
	I2C1CONbits.A10M = 0;
	I2C1CONbits.DISSLW = 1;
	I2C1CONbits.SMEN = 0;
	I2C1CONbits.GCEN = 0;
	I2C1CONbits.STREN = 0;
	I2C1CONbits.ACKDT = 0;
	I2C1CONbits.ACKEN = 0;
	I2C1CONbits.RCEN = 0;
	I2C1CONbits.PEN = 0;
	I2C1CONbits.RSEN = 0;
	I2C1CONbits.SEN = 0;
	
	//Clearing the recieve and transmit buffers
	I2C1RCV = 0x0000;
	I2C1TRN = 0x0000;
	
	//Now we can enable the peripheral	
	I2C1CONbits.I2CEN = 1;
 

}






void StartI2C(void)
{
	//This function generates an I2C start condition and returns status 
	//of the Start.

	I2C1CONbits.SEN = 1;		//Generate Start Condition
	Nop();
	while (I2C1CONbits.SEN);	//Wait for Start Condition
	//return(I2C1STATbits.S);	//Optionally return status
}


/*********************************************************************
* Function:        RestartI2C()
* Overview:		Generates a restart condition and optionally returns status
********************************************************************/
void RestartI2C(void)
{
	//This function generates an I2C Restart condition and returns status 
	//of the Restart.

	I2C1CONbits.RSEN = 1;		//Generate Restart		
	Nop();
	while (I2C1CONbits.RSEN);	//Wait for restart	
	//return(I2C1STATbits.S);	//Optional - return status
}


/*********************************************************************
* Function:        StopI2C()
* Overview:		Generates a bus stop condition
********************************************************************/
void StopI2C(void)
{
	//This function generates an I2C stop condition and returns status 
	//of the Stop.

	I2C1CONbits.PEN = 1;		//Generate Stop Condition
	Nop();
	while (I2C1CONbits.PEN);	//Wait for Stop
	//return(I2C1STATbits.P);	//Optional - return status
}


/*********************************************************************
* Function:        WriteI2C()
* Overview:		Writes a byte out to the bus
********************************************************************/
void WriteI2C(unsigned char byte)
{
	//This function transmits the byte passed to the function
	//while (I2C1STATbits.TRSTAT);	//Wait for bus to be idle
	I2C1TRN = byte;					//Load byte to I2C1 Transmit buffer
	Nop();
	while (I2C1STATbits.TBF);		//wait for data transmission

}


/*********************************************************************
* Function:        IdleI2C()
* Overview:		Waits for bus to become Idle
********************************************************************/
void IdleI2C(void)
{
	while (I2C1STATbits.TRSTAT);		//Wait for bus Idle
}

/*********************************************************************
* Function:        ACKStatus()
* Output:		Acknowledge Status.
* Overview:		Return the Acknowledge status on the bus
********************************************************************/
unsigned int ACKStatus(void)
{
	return (!I2C1STATbits.ACKSTAT);		//Return Ack Status
}


/*********************************************************************
* Function:        NotAckI2C()
* Overview:		Generates a NO Acknowledge on the Bus
********************************************************************/
void NotAckI2C(void)
{
	I2C1CONbits.ACKDT = 1;			//Set for NotACk
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN);		//wait for ACK to complete
	I2C1CONbits.ACKDT = 0;			//Set for NotACk
}


/*********************************************************************
* Function:        AckI2C()
* Overview:		Generates an Acknowledge.
********************************************************************/
void AckI2C(void)
{
	I2C1CONbits.ACKDT = 0;			//Set for ACk
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN);		//wait for ACK to complete
}
/*********************************************************************
* Function:        getI2C()
* Input:		None.
* Output:		contents of I2C1 receive buffer.
* Overview:		Read a single byte from Bus
********************************************************************/
unsigned char ReadI2C(void)
{
	I2C1CONbits.RCEN = 1;			//Enable Master receive
	Nop();
	while(!I2C1STATbits.RBF);		//Wait for receive buffer to be full
	return(I2C1RCV);				//Return data in buffer
}




/*


*/