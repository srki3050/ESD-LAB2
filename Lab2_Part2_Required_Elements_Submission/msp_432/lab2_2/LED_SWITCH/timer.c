/*
 * timer.c
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Defined for starting the timer and ensure that interrupt is handled when timer overflows.
 */

#include "timer.h"

void timer_enable(void){
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] = TIME;
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_ID_2 |// SMCLK, continuous mode
    TIMER_A_CTL_MC__CONTINUOUS;
}

