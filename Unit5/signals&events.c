/*Question
Write a multitasking application program to execute on Keil MCB 1800 to demonstrate creation
of concurrently executing tasks to emulate the excitation of stepper motor coils by toggling of
4 LEDs. Each coil is represented by an LED. The ON status of LED indicate coil is excited.
Create 4 tasks for controlling LEDs to generate pattern as follows:
Use suitable kernel objects and APIs of RL-RTX real time kernel.
The LED interface is supported with following BSPs:
BSP of LED interface: LED.h and corresponding LED_LPC18xx.c
void LED_Init (void); //Initializing LED
void LED_On (uint32_t num); //Turn on specified LED
void LED_Off (uint32_t num); //Turn off specified LED
*/

//solution
#include <RTL.h>
#include <LPC18xx.h>                    /* LPC18xx Definitions               */
#include "GLCD.h"
#include "LED.h"
#include "STEP.h"

#define LED_A 2
#define LED_B 3
#define LED_C 4
#define LED_D 5

OS_TID t_phaseA;                        /* assigned task id of task: phase_a */
OS_TID t_phaseB;
OS_TID t_phaseC;
OS_TID t_phaseD;
OS_TID t_step;


void Switch_On  (unsigned char led) {
  LED_On (led);
  
}


void Switch_Off (unsigned char led) {
  LED_Off (led);
  
}

void signal_func (OS_TID task) {
	os_dly_wait (100);
	os_evt_set (0x0001, task); /* send event to task 'task' */
	os_dly_wait (50); /* delay 50 clock ticks */
}

__task void phaseA (void) {
	for (;;) {
	os_evt_wait_and (0x0001, 0xffff); /* wait for an event flag 0x0001 */
	Switch_On (LED_A);
	signal_func (t_phaseB); /* call common signal function */
	Switch_Off(LED_A);
	}
}

__task void phaseB (void) {
	for (;;) {
		os_evt_wait_and (0x0001, 0xffff); /* wait for an event flag 0x0001 */
		Switch_On (LED_B);
		signal_func (t_phaseC); /* call common signal function */
		Switch_Off(LED_B);
		}
}

__task void phaseC (void) {
	for (;;) {
	os_evt_wait_and (0x0001, 0xffff); /* wait for an event flag 0x0001 */
	Switch_On (LED_C);
	signal_func (t_phaseD); /* call common signal function */
	Switch_Off(LED_C);
	}
}

__task void phaseD (void) {
	for (;;) {
	os_evt_wait_and (0x0001, 0xffff); /* wait for an event flag 0x0001 */
	Switch_On (LED_D);
	signal_func (t_phaseA); /* call common signal function */
	Switch_Off(LED_D);
	}
}
__task void init (void) {
	t_phaseA = os_tsk_create (phaseA, 0); /* start task phaseA */
	t_phaseB = os_tsk_create (phaseB, 0); /* start task phaseB */
	t_phaseC = os_tsk_create (phaseC, 0); /* start task phaseC */
	t_phaseD = os_tsk_create (phaseD, 0); /* start task phaseD */
	os_evt_set (0x0001, t_phaseA); /* send signal event to task phaseA */
	os_tsk_delete_self ();
}
\
int main (void) {
	LED_Init(); /* Initialize the LEDs */
	os_sys_init(init); /* Initialize RTX and start init */
}