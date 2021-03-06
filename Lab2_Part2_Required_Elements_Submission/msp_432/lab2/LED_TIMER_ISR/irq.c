/*
 *  irq.c
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: handle the ISR when NVIC is enabled. In this case toggle the LED.
 *  Goes to sleep once interrupt is handled.
 */

// Timer A0 interrupt service routine
#include "irq.h"
volatile int i = LOOP;
void TA0_0_IRQHandler(void) {
    //check
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    if(i == 0){
        P1->OUT ^= BIT0;
        i = LOOP;
    }
    else{
        i--;
    }
    TIMER_A0->CCR[0] += TIME;              // Add Offset to TACCR0
}



