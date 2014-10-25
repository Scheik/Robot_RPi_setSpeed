/*
 * Robot_RPi_setSpeed_main.cpp
 *
 *  Created on: 18.10.2014
 *      Author: scheik
 */

#include <iostream>
#include <stdio.h>   								/* Standard input/output definitions */
#include <stdlib.h>  								/* exit */
#include <string.h>  								/* String function definitions */
#include <unistd.h>  								/* UNIX standard function definitions */
#include <fcntl.h>  	 							/* File control definitions */
#include <errno.h>   								/* Error number definitions */
#include <termios.h> 								/* POSIX terminal control definitions */
#include <ctype.h>   								/* isxxx() */
#include "../libs/serial_communications_lib.h"		/* serial communications library*/

using namespace std;

void set_MD49_Speed (void);

unsigned char set_Speed1=128;
unsigned char set_Speed2=128;

int main(int argc, char *argv[]){

	if(argc != 3) {														// Fehlerbehandlung: nicht alle Parameter angegeben
	  printf("Programm needs both arguments <speed1> and <speed2>!\n");
	  printf("Call with: %s <speed2> <speed2> \n", *argv);
	  return EXIT_FAILURE;
	}
	// Fehlerbehandlung: Parameter haben unlogische Werte
	// to code
	filedesc = openSerialPort("/dev/ttyAMA0", B38400);					// open RPis serial port
	if (filedesc == -1) exit(1);
	usleep(80000);														// Sleep for UART to power up and set options
	set_Speed1=strtol(argv[1], NULL, 10);								//convert string of argument1 to decimal
	set_Speed2=strtol(argv[2], NULL, 10);
	set_MD49_Speed();
	//close(fd);															// Close port
	return 0;															// exit
}//end.mainfunction

void set_MD49_Speed (void){
	serialBuffer[0] = 88;							// 88 =X Steuerbyte um alle Commands an MD49 zu senden
	serialBuffer[1] = 115;							// 115=s Steuerbyte setSpeed
	serialBuffer[2] = set_Speed1;					// speed1
	serialBuffer[3] = set_Speed2;					// speed2
	serialBuffer[4] = 0;							// all following bytes are
	serialBuffer[5] = 0;							// dummy-bytes to
	serialBuffer[6] = 0;							// fill message
	serialBuffer[7] = 0;
	serialBuffer[8] = 0;
	serialBuffer[9] = 0;
	serialBuffer[10] = 0;
	serialBuffer[11] = 0;
	serialBuffer[12] = 0;
	serialBuffer[13] = 0;
	serialBuffer[14] = 0;
	serialBuffer[15] = 0;
	writeBytes(fd, 16);								// write 16 Bytes from serialbuffer to UART
	usleep(50000);
	writeBytes(fd, 16);
	usleep(50000);
	writeBytes(fd, 16);


}


