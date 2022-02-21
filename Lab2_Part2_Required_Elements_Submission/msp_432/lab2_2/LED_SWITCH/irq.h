/*
 * irq.h
 *
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: A prototype to call the IRQ handler function during NVIC is enabled
 */

#ifndef IRQ_H_
#define IRQ_H_

#include "stdbool.h"
#include "msp.h"
#include "timer.h"

void PORT1_IRQHandler(void);
void TA0_0_IRQHandler(void);

#endif /* IRQ_H_ */
