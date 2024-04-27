/*multitasking LED and GLCD Display*/

#include <RTL.h>
#include <LPC18xx.h>                    /* LPC18xx Definitions               */
#include "GLCD.h"
#include "LED.h"

OS_TID t_led;                           /* assigned task id of task: led      */
OS_TID t_lcd;                           /* assigned task id of task: lcd     */

#define __FI       1                    /* Font index 16x24                  */



__task void led (void) {
  for (;;) {
   
    LED_On(0);
		os_dly_wait (100);
    LED_Off(0);
		os_dly_wait (100);
  }
}

__task void lcd (void) {
    GLCD_SetBackColor(Blue);                           /* Set the Text Color */

  for (;;) {
    
    GLCD_SetTextColor(White);                          /* Set the Text Color */
    GLCD_DisplayString(0, 0, __FI, "Hello world");
    os_dly_wait (100);
    GLCD_SetBackColor(Blue);                           /* Set the Text Color */
    GLCD_SetTextColor(Red);                            /* Set the Text Color */
    GLCD_DisplayString(0, 0, __FI, "How are you!");
    os_dly_wait (100);
   
  }
}

__task void init (void) {
	
  t_led = os_tsk_create (led, 0);           /* start task led               */              
  t_lcd    = os_tsk_create (lcd, 0);       /* start task lcd  */ 
  os_tsk_delete_self ();
	
}

int main (void) {
  LED_Init();                               /* Initialize the LEDs           */  
  GLCD_Init();                              /* Initialize the GLCD           */
  GLCD_Clear(White);                        /* Clear the GLCD                */
  os_sys_init(init);                        /* Initialize RTX and start init */
}
