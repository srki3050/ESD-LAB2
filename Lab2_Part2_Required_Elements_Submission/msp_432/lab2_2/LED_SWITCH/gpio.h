/*
 *  gpio.h
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Disables unnecessary GPIO peripherals including watchdog timer and initializes gpio ports for the ARM cortex device.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "msp.h"

void watchdog_disable(void);
void init_port1(void);
void init_port2(void);
void disable_rest(void);



#endif /* GPIO_H_ */
