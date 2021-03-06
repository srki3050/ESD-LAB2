/*
 * Switch.c
 *
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Initialize the switch
 */
#include "Switch.h"

void switch_init(void){
    // Configure Port J
    PJ->DIR |= (BIT0| BIT1 | BIT2 | BIT3);
    PJ->OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);
}


