/*
 * program.h
 *
 *  Created on: May 20, 2018
 *      Author: Micha³
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
	LDD_TDeviceData *handle;
	volatile uint8_t isSent;
	uint8_t rxChar;
	uint8_t (*rxPutFct)(uint8_t);
} UART_Desc;

void Prog_Start(void);
#endif /* PROGRAM_H_ */
