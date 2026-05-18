/* main.c
 *
 * Copyright (C) 2026 DesignFirst OU. All rights reserved.
 * SPDX-License-Identifier: PolyForm-Strict-1.0.0
 *
 * https://enacttrust.com
 *
 * This EnactTrust software is source-available under the PolyForm Strict License 1.0.0.
 * Noncommercial use is permitted without a separate agreement. Any commercial use —
 * including integration into a product, deployment in production, or use as part of
 * a commercial service — requires a written Commercial License Agreement with DesignFirst OU.
 * Contact licensing@enacttrust.com to obtain a commercial license.
 */

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"

/* Customer-specific */
#include "hal/customer_setup.h"

/* EnactTrust owned */
#include "enact/enacttrust.h"
#include "enact/enacttrust_freertos_port.h"

/* Application-specific logging and error handling */
static void app_log_callback(const char* message) {
    printf("[ENACT_LOG]: %s\n", message);
}

static void app_error_log_callback(uint32_t error_code, const char* file, int line, const char* message) {
    printf("[ENACT_ERROR]: %s (Code: 0x%lX) at %s:%d\n", message, error_code, file, line);
}

/* This enables RTOS aware debugging. */
volatile int uxTopUsedPriority;

/* Example FreeRTOS-based application using EnactTrust for offline TPM Update */
int main(void)
{
    cy_rslt_t result;
    BaseType_t status;
    /* This enables RTOS aware debugging in OpenOCD. */
    uxTopUsedPriority = configMAX_PRIORITIES - 1;
    
    result = cybsp_init();
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    __enable_irq();
    /* Disable CTS on CYW20829 to workaround UART issue with B0 silicon */
    result = cy_retarget_io_init_fc(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, NC,
                                    CYBSP_DEBUG_UART_RTS,CY_RETARGET_IO_BAUDRATE);
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    /* Eliminate buffering of the UART output */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    /* Set EnactTrust logging and error callbacks */
    enacttrust_set_log_callback(app_log_callback);
    enacttrust_set_error_log_callback(app_error_log_callback);
    enacttrust_freertos_set_hal_init(customer_hal_init);

    status = enacttrust_freertos_task_create(NULL);
    if(status != pdPASS) {
        printf("Failed to register the %s.\n", ENACTTRUST_TASK_NAME);
    }
    
    vTaskStartScheduler();
    /* Halt the CPU if scheduler exits */
    CY_ASSERT(0);
}
