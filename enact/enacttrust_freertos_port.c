/* enacttrust_freertos_port.c
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

#include "enact/enacttrust_freertos_port.h"
#include "enact/enacttrust.h"

static TaskHandle_t enacttrust_task_handle_internal = NULL;
static enact_hal_init_cb_t enacttrust_hal_init_callback = NULL;

void enacttrust_freertos_set_hal_init(enact_hal_init_cb_t callback)
{
    enacttrust_hal_init_callback = callback;
}

/**
 * @brief The FreeRTOS task function for EnactTrust.
 * This function acts as a wrapper, calling into the agnostic EnactTrust core.
 * @param pvParameters Parameters passed to the task (unused in this case).
 */
static void enacttrust_freertos_task(void* pvParameters)
{
    (void)pvParameters;

    enacttrust_init();
    if (enacttrust_hal_init_callback != NULL) {
        if (enacttrust_hal_init_callback() != 0U) {
            vTaskDelete(NULL);
            return;
        }
    }
    for(;;)
    {
        /* Run one cycle of the hardware EnactTrust state machine */
        enacttrust_process();
        vTaskDelete(NULL);
    }
}

/**
 * @brief Creates the EnactTrust FreeRTOS task.
 * This function should be called by the application's main function.
 * @param task_handle Pointer to a TaskHandle_t variable to store the handle of the created task.
 * @return pdPASS if the task was created successfully, otherwise an error code.
 */
BaseType_t enacttrust_freertos_task_create(TaskHandle_t *task_handle)
{
    BaseType_t status;

    status = xTaskCreate(enacttrust_freertos_task,
                         ENACTTRUST_TASK_NAME,
                         ENACTTRUST_TASK_STACK_SIZE,
                         NULL,
                         ENACTTRUST_TASK_PRIORITY,
                         &enacttrust_task_handle_internal);

    if (task_handle != NULL) {
        *task_handle = enacttrust_task_handle_internal;
    }

    return status;
}

/* Function to notify the EnactTrust task from an ISR */
void enacttrust_freertos_notify_from_isr(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (enacttrust_task_handle_internal != NULL) {
        xTaskNotifyFromISR(enacttrust_task_handle_internal, 0, eNoAction, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}