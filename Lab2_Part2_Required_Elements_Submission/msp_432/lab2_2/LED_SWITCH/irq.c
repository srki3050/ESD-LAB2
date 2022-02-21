/*
 * irq.h
 *
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: A prototype to call the IRQ handler function during NVIC is enabled.
 *  The timer handler toggles green and blue light at 300ms.
 *  The switch controls whether the toggle occurs or not.
 */
/* Port1 ISR */
#include "irq.h"

#define LOOP 10
volatile int i = LOOP;
volatile bool flag = true;

void PORT1_IRQHandler(void)
{
    volatile uint32_t i;

    // Toggling the output on the LED
    if(P1->IFG & BIT1)
        flag = !flag;

    // Delay for switch debounce
    for(i = 0; i < 10000; i++)

    P1->IFG &= ~BIT1;
}
void TA0_0_IRQHandler(void) {
    //check
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    if(i == 0){
        if(flag){
        P2->OUT ^= BIT1;
        P2->OUT ^= BIT2;
        i = LOOP;
        }
    }
    else{
        i--;
    }
    TIMER_A0->CCR[0] += TIME;              // Add Offset to TACCR0
}


