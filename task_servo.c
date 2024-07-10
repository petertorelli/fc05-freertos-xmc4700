#include "FreeRTOS.h"
#include "task.h"
#include "cybsp.h"
#include <stdio.h>

#include "task_rx_api.h"

#define SERVO2_TRIM -10
// 120 MHz, prescalar is 100, period is 24000
// 50 Hz frequency, or 20 ms period

#define SERVO_PWM_MIN 1
#define SERVO_PWM_MAX 24000
#define SERVO_PWM_MID (SERVO_PWM_MAX >> 1)

// 1.0 ms
// #define SERVO_MIN 540
#define SERVO_MIN 1600
// 1.5 ms
#define SERVO_MID 1790
//    1790 // 1800 was off just a teeny bit for all 4 motors, probably pwm
// precision
// 2.0 ms
// #define SERVO_MAX 3060
#define SERVO_MAX 2000

// +/-DEAD ZONE nothing happens (+/-2%, 4% wide)
#define SERVO_DZ       36u
#define SERVO_DZ_LO    (SERVO_MID - SERVO_DZ)
#define SERVO_DZ_HI    (SERVO_MID + SERVO_DZ)
#define SERVO_IN_DZ(x) ((x > SERVO_DZ_LO) && (x < SERVO_DZ_HI))

// Transmitter jitter makes servos twitchy when idle
#define SERVO_JITTER_FILTER ~0x1f

uint32_t g_angles[4];

void
task_servo(void)
{
    uint32_t v = SERVO_MID;
    uint32_t front;
    uint32_t rear;
    while (1)
    {
        vTaskDelay(100);
        v = rx_get_sbus_steering();
        v = map32u(v, SBUS_MIN, SBUS_MAX, SERVO_MIN, SERVO_MAX);

        v &= SERVO_JITTER_FILTER;

// why do we need a dead zone if we're filtering the signal?
        if (SERVO_IN_DZ(v))
        {
            rear  = SERVO_MID;
            front = SERVO_MID;
        }
        else
        {
            front = v;
            /// ummm... these are the same thing....
            if (v > SERVO_MID)
            {
                rear = (SERVO_MID - v) + SERVO_MID;
            }
            else
            {
                rear = SERVO_MID - (v - SERVO_MID);
            }
        }

        /*
        TIM_SERVO->CCR1 = rear;
        TIM_SERVO->CCR2 = rear;
        TIM_SERVO->CCR3 = front;
        TIM_SERVO->CCR4 = front;
        */
    }
}