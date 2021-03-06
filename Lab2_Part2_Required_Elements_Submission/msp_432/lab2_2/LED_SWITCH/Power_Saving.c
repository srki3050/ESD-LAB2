/*
 * Power_Saving.c
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: A power saving strategy applied here to ensure that the components
 *  enter sleep states once they are out of IRQ handler and wakes up on the next call to ISR.
 */
#include "Power_Saving.h"

void sleeponexit(void){
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();
}
void enable_power_saving(void){
    PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL1_FORCE_LPM_ENTRY;
    SCB->SCR |= (SCB_SCR_SLEEPDEEP_Msk);
    __sleep();
}

