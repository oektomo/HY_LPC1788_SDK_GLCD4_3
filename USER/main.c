/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            This example describes how to use GLCD on LPC177x_8x
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2012-8-16
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "system_LPC177x_8x.h"
#include "GLCD.h"
#include "AsciiLib.h"
#include "lpc_types.h"
#include "lpc177x_8x.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_pinsel.h"

/* Private function prototypes -----------------------------------------------*/
void USART_Configuration(void);
void welcomeMessage(void);
void checkDRAM(void);

/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
	
	USART_Configuration();
	welcomeMessage();
	//extern uint32_t SystemCoreClock;
	SystemCoreClockUpdate ();
	UARTPutDec32(UART_0, SystemCoreClock);
	//UARTPutHex32 (UART_0, SystemCoreClock);
	UARTPuts_( UART_0, " MHz" );

    SDRAM_32M_32BIT_Init();	  
    GLCD_Init();
	while( 1 )
	{
	GLCD_Clear(Black);
	Delay(0xffffff);

	GLCD_Clear(Red);
	Delay(0xffffff);

	GLCD_Clear(Blue);
	Delay(0xffffff);

	GLCD_Clear(Green);
	Delay(0xffffff);

	GLCD_Clear(White);
	Delay(0xffffff);
	 
	GUI_Text( ( GLCD_X_SIZE - 120 ) / 2, GLCD_Y_SIZE / 2 - 8, "HY-LPC1788-Core", White, Blue);
	GUI_Text( ( GLCD_X_SIZE - 136 ) / 2, GLCD_Y_SIZE / 2 + 8, "Development Board", White, Blue);
	Delay(0xffffff);
	 
	}
}
/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure USART0
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Configuration(void)
{ 
	UART_CFG_Type UARTConfigStruct;

	/*
	 * Initialize UART0 pin connect
	 * P0.2: TXD
	 * P0.3: RXD
	 */
	PINSEL_ConfigPin(0, 2, 1);
	PINSEL_ConfigPin(0, 3, 1);

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 115200bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	/* Re-configure baudrate to 115200bps */
	UARTConfigStruct.Baud_rate = 115200;

	/* Initialize DEBUG_UART_PORT peripheral with given to corresponding parameter */
	UART_Init(UART_0, &UARTConfigStruct);

	/* Enable UART Transmit */
	UART_TxCmd(UART_0, ENABLE);

}

void welcomeMessage(void)
{
	UARTPuts_( UART_0, "=================================================================" );
	UARTPuts_( UART_0, "*                                                               *" );
	UARTPuts_( UART_0, "*   Thank you for using HY-LPC1788-SDK Development Board V^_^   *" );
	UARTPuts_( UART_0, "*                                                               *" );
	UARTPuts_( UART_0, "=================================================================" );
}

// print the content of LCD_VRAM_BASE_ADDR
void checkDRAM(void)
{
	#define XPOS 100
	#define YPOS 100
	
	volatile uint16_t *pLCDbuf = (uint16_t *)LCD_VRAM_BASE_ADDR;  /* LCD buffer start address */
	UARTPutHex16 (UART_0, pLCDbuf[0]);
	UARTPuts( UART_0, " ");	
	UARTPutHex16 (UART_0, pLCDbuf[ YPOS * GLCD_X_SIZE + XPOS ]);
	UARTPuts( UART_0, "\n\r");
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
