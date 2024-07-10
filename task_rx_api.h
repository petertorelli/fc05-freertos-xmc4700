#pragma once

#define SBUS_MAX 1811u
#define SBUS_MIN 172u
#define SBUS_MID (((SBUS_MAX - SBUS_MIN) >> 1) + SBUS_MIN)

void     rx_task(void *);
void     rx_setup(void);
uint32_t rx_get_sbus_steering(void);
