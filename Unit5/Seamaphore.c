#include <RTL.h>
#include <LPC18xx.h>                    /* LPC18xx Definitions               */
#include "GLCD.h"
#include "LED.h"

OS_TID t_led;                   /* assigned task id of task: phase_a */
OS_TID t_lcd;                           /* assigned task id of task: lcd     */

OS_SEM semaphore;                         /* sem to controll GLCD access     */

#define LED_A      2
#define __FI       1                    /* Font index 16x24                  */


void Switch_On  (unsigned char led) {

  LED_On (led);
  os_sem_wait (&semaphore, 0xffff);
  GLCD_SetBackColor(White);                         /* Set the Back Color */
  GLCD_SetTextColor(Green);                         /* Set the Text Color */
  GLCD_DisplayChar(4, 5+led, __FI, 0x80+1);         /* Circle Full        */
  os_sem_send(&semaphore);
}


void Switch_Off (unsigned char led) {

  LED_Off (led);
  os_sem_wait (&semaphore, 0xffff);
  GLCD_SetBackColor(White);                         /* Set the Back Color */
  GLCD_SetTextColor(Green);                         /* Set the Text Color */
  GLCD_DisplayChar(4, 5+led, __FI, 0x80+0);         /* Circle Empty       */
  os_sem_send(&semaphore);
}
*/
__task void led (void) {
  for (;;) {
   
    Switch_On (LED_A);
    os_dly_wait (100);
    Switch_Off(LED_A);
		os_dly_wait (100);
  }
}


__task void lcd (void) {

  for (;;) {
    os_sem_wait (&semaphore, 0xffff);
    GLCD_SetBackColor(Blue);                           /* Set the Text Color */
    GLCD_SetTextColor(White);                          /* Set the Text Color */
    GLCD_DisplayString(0, 0, __FI, " Hello world ");
    os_sem_send(&semaphore);
    os_dly_wait (50);

    os_sem_wait (&semaphore, 0xffff);
    GLCD_SetBackColor(Yellow);                           /* Set the Text Color */
    GLCD_SetTextColor(Red);                            /* Set the Text Color */
    GLCD_DisplayString(0, 0, __FI, "Seamaphore api");
    os_sem_send(&semaphore);
    os_dly_wait (100);
  }
}

__task void init (void) {

      os_sem_init (&semaphore, 1);
  t_led = os_tsk_create (led, 0);         /* start task phaseA                */
  t_lcd    = os_tsk_create (lcd, 0);     /* start task lcd                   */
  os_tsk_delete_self ();
}

int main (void) {
  LED_Init();                               /* Initialize the LEDs           */  
  GLCD_Init();                              /* Initialize the GLCD           */
  GLCD_Clear(White);                        /* Clear the GLCD                */
  os_sys_init(init);                        /* Initialize RTX and start init */
}


