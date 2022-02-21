/*
 *  main.c
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Contains the main loop which returns a call back to the repective functions in other source files.
 *         Also contains the main while loop of operation.
 */
#include "msp.h"
#include "timer.h"
#include "gpio.h"
#include "irq.h"

int main(void) {
    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
            WDT_A_CTL_HOLD;

    init_gpio();
    init_timer0();
    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();

    // Enable global interrupt
    __enable_irq();

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);

    while (1)
    {
        __sleep();

        __no_operation();                   // For debugger
    }
}
