/*
 *  irq.h
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: A prototype handle the ISR when NVIC is enabled. Goes to sleep once interrupt is handled.
 */

#ifndef IRQ_C_
#define IRQ_C_

#include "msp.h"
#include "timer.h"
#include "stdio.h"

#define LOOP 10

void TA0_0_IRQHandler(void);

#endif /* IRQ_C_ */
