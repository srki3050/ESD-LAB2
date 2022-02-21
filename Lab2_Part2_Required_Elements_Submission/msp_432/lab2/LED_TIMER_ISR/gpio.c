/*
 *  gpio.c
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Initializes some bits to set RED LED ON
 */

#include "gpio.h"

void init_gpio(void){
    // Configure GPIO
    P1->DIR |= BIT0;
    P1->OUT |= BIT0;
}


