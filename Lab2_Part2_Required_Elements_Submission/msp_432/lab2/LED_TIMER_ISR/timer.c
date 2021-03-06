/*
 *  timer.c
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: start the timer A0 in continuous mode post doing appropriate frequency division.
 */

#include "timer.h"

void init_timer0(void){
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] = TIME;
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_ID_2 |// SMCLK, continuous mode
            TIMER_A_CTL_MC__CONTINUOUS;

    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;    // Enable sleep on exit from ISR
}


