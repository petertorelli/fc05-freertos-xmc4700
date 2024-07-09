#include <stdlib.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "cybsp.h"
#include "cy_utils.h"
#include "cy_retarget_io.h"

#include "task_rx_api.h"

#ifdef UNIT_TEST_01_JAM_RX
__NO_RETURN static void
main_task(void *pvParameters)
{
    XMC_UNUSED_ARG(pvParameters);

    for (;;)
    {
        vTaskDelay(100);
        float frand = (float)rand() / (float)RAND_MAX;
        if (frand < 0.10)
        {
            printf("jamming...\n");
            // if (g_rx_synced)
            {
                rx_force_resync();
            }
        }
    }
}
#endif

volatile uint32_t idleTick = 0;
void
vApplicationIdleHook( void )
{
    ++idleTick;
}

__NO_RETURN static void
utilization_task(void *pvParameters)
{
    XMC_UNUSED_ARG(pvParameters);

    for (;;)
    {
        vTaskDelay(1000);
        printf("Utilization : %lu\n", idleTick);
        idleTick = 0;
    }
}

int
main(void)
{
    BaseType_t retval;

    if (CY_RSLT_SUCCESS != cybsp_init())
    {
        CY_ASSERT(0);
    }

    if (CY_RSLT_SUCCESS != cy_retarget_io_init(CYBSP_DEBUG_UART_HW))
    {
        CY_ASSERT(0);
    }

    retval = xTaskCreate(utilization_task,
                         "utilization_task",
                         configMINIMAL_STACK_SIZE,
                         NULL,
                         tskIDLE_PRIORITY + 1,
                         NULL);
    if (retval != pdPASS)
    {
        CY_ASSERT(0);
    }

    rx_setup();

    printf("\n\nStarting task scheduler\n");

    vTaskStartScheduler();

    for (;;)
    {
    }
}
