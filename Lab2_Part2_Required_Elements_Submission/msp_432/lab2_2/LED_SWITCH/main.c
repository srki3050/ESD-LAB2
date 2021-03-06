/*
 * main.c
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Main function that handles an infinite loop and adds a call back to the init, timer and IRQ function based on requirements.
 *  References: Sample programs on slac69 on interrupt and timer configuration.
 */
#include "msp.h"

int main(void)
{
    // Hold the watchdog
    watchdog_disable();
    init_port1();
    // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);   //ENABLE PORT1 INTERRUPT
    init_port2();
    // Terminate all remaining pins on the device
    disable_rest();
    timer_enable();

    __enable_irq();

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);   //ENABLE TA0 INTERRUPT

    switch_init();

    // Enable PCM rude mode, which allows to device to enter LPM3 without waiting for peripherals
    enable_power_saving();

    sleeponexit();
}
