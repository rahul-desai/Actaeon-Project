/*
		This file has been auto-generated by WebbotLib tools V1.1
				** DO NOT MODIFY BY HAND **
*/
#ifndef _HARDWARE_H_
#define _HARDWARE_H_
#include "xhardware.h"
// Type of interrupt handler to use for uart interrupts.
// Do not change unless you know what you're doing.
#ifndef UART_INTERRUPT_HANDLER
#define UART_INTERRUPT_HANDLER	ISR
#endif

// ------------------- uart1 -------------------

// Create hardware UART uart1
HW_UART _uart1 = MAKE_UART_BUFFERED(null,null,UCSR1A,UCSR1B,UBRR1L,UBRR1H,UDR1,null,BV(U2X1),D2,D3,&uart1GetByte,&uart1SendByte);

// Create a routine to write bytes to uart1
// You can set rprintf to use it by calling rprintfInit(&uart1SendByte)
MAKE_WRITER(uart1SendByte){
	return uartSendByte(uart1,byte);
}

// Create a routine to read a byte from uart1
// Returns -1 if there was no data
MAKE_READER( uart1GetByte){
	return uartGetByte(uart1);
}

#ifndef USART1_TX_vect
# error Uart1 Tx complete vector undefined
#else
UART_INTERRUPT_HANDLER(USART1_TX_vect){
	uartTransmitService(uart1);
}
#endif

#ifndef USART1_RX_vect
# error Uart1 Rx complete vector undefined
#else
UART_INTERRUPT_HANDLER(USART1_RX_vect){
	uartReceiveService(uart1);
}
#endif

// ------------------- lidar -------------------
// Make a receive buffer for lidar
static unsigned char rx_lidar_Buf[8];
static cBuffer rx_lidar_Buffer = MAKE_BUFFER(rx_lidar_Buf);


// Create hardware UART lidar
HW_UART _lidar = MAKE_UART_BUFFERED(&rx_lidar_Buffer,null,UCSR2A,UCSR2B,UBRR2L,UBRR2H,UDR2,null,BV(U2X2),H0,H1,&lidarGetByte,&lidarSendByte);

// Create a routine to write bytes to lidar
// You can set rprintf to use it by calling rprintfInit(&lidarSendByte)
MAKE_WRITER(lidarSendByte){
	return uartSendByte(lidar,byte);
}

// Create a routine to read a byte from lidar
// Returns -1 if there was no data
MAKE_READER( lidarGetByte){
	return uartGetByte(lidar);
}

#ifndef USART2_TX_vect
# error Uart2 Tx complete vector undefined
#else
UART_INTERRUPT_HANDLER(USART2_TX_vect){
	uartTransmitService(lidar);
}
#endif

#ifndef USART2_RX_vect
# error Uart2 Rx complete vector undefined
#else
UART_INTERRUPT_HANDLER(USART2_RX_vect){
	uartReceiveService(lidar);
}
#endif

// ----------- Define the ADC channels ----------
const uint8_t NUM_ADC_CHANNELS = 16;
const uint16_t PROGMEM AVcc_MV = 5000;

// ----------- My devices -----------------------
SWITCH button = MAKE_SWITCH(G5);
SERVO wheel_right = MAKE_SERVO(true,H6,1500,500);
SERVO wheel_left = MAKE_SERVO(false,H5,1500,500);
static SERVO_LIST bank1_list[] = {
	&wheel_right,
	&wheel_left
};
SERVO_DRIVER bank1 = MAKE_SERVO_DRIVER(bank1_list);

// ----------- Initialise built in devices ------
void sysInitHardware(void){
	SWITCH_init(&button);
	setErrorLog(&uart1SendByte);
	rprintfInit(&uart1SendByte);
	uartInit(uart1,115200);
}

// ----------- Initialise my added devices ------
void initHardware(void){
	servosInit(&bank1,TIMER1);
	uartInit(lidar,115200);
}
// ----------- Register the statusLED -----------
void registerLED(void){
	statusLEDregister(B6,false);
}

// ----------- Ports are configured on the fly --
void configure_ports(void){
}

#endif
