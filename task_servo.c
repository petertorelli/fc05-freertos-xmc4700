#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cybsp.h"
#include <stdio.h>

#include "task_rx_api.h"

/**
 * I'm using servos from GoBilda, the high-torque version. They spec
 * min PWM window of 0.5msec and a max of 2.5ms. Clock is 144 MHz on
 * the XMC4700, and I'm using the 16-bit CCU4 with a prescalar of 32
 * to get nice integral duty cycles. (4% to 20%). With this setup the
 * (PERIOD=56250) it runs at 80 Hz. 45000 = 0.5ms, 54000 = 2.5ms.
 */
#define SERVO_PWM_MIN 45000
#define SERVO_PWM_MAX 54000
#define SERVO_PWM_MID ((SERVO_PWM_MAX + SERVO_PWM_MIN) >> 1)

// +/-DEAD ZONE nothing happens (+/-2%, 4% wide)
#define SERVO_DZ       990U
#define SERVO_DZ_LO    (SERVO_PWM_MID - SERVO_DZ)
#define SERVO_DZ_HI    (SERVO_PWM_MID + SERVO_DZ)
#define SERVO_IN_DZ(x) ((x > SERVO_DZ_LO) && (x < SERVO_DZ_HI))

#if 0
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
#endif

// Transmitter jitter makes servos twitchy when idle
#define SERVO_SBUS_JITTER_FILTER ~0x1f

extern SemaphoreHandle_t sem_rx_packet_rdy;

void
task_servo(void)
{
    uint32_t v = SERVO_PWM_MID;
    uint32_t front;
    uint32_t rear;
    uint32_t delay = 100;

    for (;;)
    {
        delay = 100;
        if (xSemaphoreTake(sem_rx_packet_rdy, 10))
        {
            v = rx_get_sbus_steering();
            xSemaphoreGive(sem_rx_packet_rdy);
            delay = 90;
            /* Shave off the last 5 bits, really? Why so big TODO */
            v &= SERVO_SBUS_JITTER_FILTER;
            v = map32u(v, SBUS_MIN, SBUS_MAX, SERVO_PWM_MIN, SERVO_PWM_MAX);

            // why do we need a dead zone if we're filtering the signal? TODO NO
            if (SERVO_IN_DZ(v))
            {
                rear  = SERVO_PWM_MID;
                front = SERVO_PWM_MID;
            }
            else
            {
                front = v;
                /// ummm... these are the same thing....
                if (v > SERVO_PWM_MID)
                {
                    rear = (SERVO_PWM_MID - v) + SERVO_PWM_MID;
                }
                else
                {
                    rear = SERVO_PWM_MID - (v - SERVO_PWM_MID);
                }
            }

            /**
             * TODO: Scale these to inner & outer radii.
             */

            XMC_CCU4_SLICE_SetTimerCompareMatch(PWM1_HW, rear);
            XMC_CCU4_SLICE_SetTimerCompareMatch(PWM2_HW, rear);
            XMC_CCU4_SLICE_SetTimerCompareMatch(PWM3_HW, front);
            XMC_CCU4_SLICE_SetTimerCompareMatch(PWM4_HW, front);
        }
        vTaskDelay(delay);
    }
}