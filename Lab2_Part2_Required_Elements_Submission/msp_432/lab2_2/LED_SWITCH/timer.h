/*
 * timer.h
 *  Created on: Feb 20, 2022
 *  Author: Sricharan Kidambi
 *  Brief: Defined for starting the timer and ensure that interrupt is handled when timer overflows.
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "msp.h"
#define TIME 50000

void timer_enable(void);

#endif /* TIMER_H_ */
