/*
 * program.c
 *
 *  Created on: May 20, 2018
 *      Author: Micha³
 */

#include "program.h"
#include "RNG1.h"
#include "ASerialLdd1.h"


static UART_Desc deviceData;

static void SendChar(unsigned char ch, UART_Desc *desc){
	desc->isSent =FALSE;
	while(ASerialLdd1_SendBlock(desc->handle,(LDD_TData*)&ch,1)!=ERR_OK){}
	while (!desc->isSent){}
}
static void SendString(const unsigned char *str, UART_Desc *desc){
while(*str!='0'){
	SendChar(*str++,desc);
}
}

static void Init(void){
	deviceData.handle=ASerialLdd1_Init(&deviceData);
	deviceData.isSent=FALSE;
	deviceData.rxChar='0';
	deviceData.rxPutFct=RNG1_Put;
	
	RNG1_Init();
	while(ASerialLdd1_ReceiveBlock(deviceData.handle,(LDD_TData*)&deviceData.rxChar, sizeof(deviceData.rxChar))!=ERR_OK){}
	
}

void Prog_Start(void){
	Init();
	SendString((unsigned char*)"Hello",&deviceData);
	for(;;){
		if (RNG1_NofElements()!=0){
			SendString((unsigned char*)"echo",&deviceData);
			while(RNG1_NofElements()!=0){
				unsigned char ch;
				
				(void)RNG1_Get(&ch);
				SendChar(ch,&deviceData);
				
			}
			SendString((unsigned char*)"rn",&deviceData);
		}
	}
}
