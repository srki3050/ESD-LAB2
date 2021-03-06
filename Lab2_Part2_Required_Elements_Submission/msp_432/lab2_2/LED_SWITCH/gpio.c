/*
 * gpio.c
 *
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Disables the watchdog timer, other unused peripherals. Initializes the LED and switch.
 */
#include "gpio.h"

void watchdog_disable(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
}
void init_port1(void){
    // Configuring P1.0 as output and P1.1 (switch) as input with pull-up
        // resistor. Rest of pins are configured as output low.
        // Notice intentional '=' assignment since all P1 pins are being
        // deliberately configured
        P1->DIR = ~(uint8_t) BIT1;
        P1->OUT = BIT1;
        P1->REN = BIT1;                         // Enable pull-up resistor (P1.1 output high)
        P1->SEL0 = 0;
        P1->SEL1 = 0;
        P1->IES = BIT1;                         // Interrupt on high-to-low transition
        P1->IFG = 0;                            // Clear all P1 interrupt flags
        P1->IE = BIT1;                          // Enable interrupt for P1.1
}
void init_port2(void){
    //P2->DIR |= 0xFF; P2->OUT = 0;
    P2->DIR |= BIT1;
    P2->OUT |= BIT1;

    P2->DIR |= BIT2;
    P2->OUT &= ~BIT2;
}
void disable_rest(void){
   P3->DIR |= 0xFF; P3->OUT = 0;
   P4->DIR |= 0xFF; P4->OUT = 0;
   P5->DIR |= 0xFF; P5->OUT = 0;
   P6->DIR |= 0xFF; P6->OUT = 0;
   P7->DIR |= 0xFF; P7->OUT = 0;
   P8->DIR |= 0xFF; P8->OUT = 0;
   P9->DIR |= 0xFF; P9->OUT = 0;
   P10->DIR |= 0xFF; P10->OUT = 0;
}

