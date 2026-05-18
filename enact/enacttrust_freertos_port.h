/* enacttrust_freertos_port.h
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

#ifndef ENACTTRUST_FREERTOS_PORT_H_
#define ENACTTRUST_FREERTOS_PORT_H_

#include "FreeRTOS.h"
#include "task.h"

/* FreeRTOS related */
#define ENACTTRUST_TASK_PRIORITY     (3)
#define ENACTTRUST_TASK_STACK_SIZE   (512u)
#define ENACTTRUST_TASK_NAME         "EnactTrust"

/**
 * @brief Type definition for the HAL initialization callback.
 * Called once by the port task after the scheduler starts, before the state machine loop.
 * @return 0 for success, non-zero to abort — the task will delete itself on failure.
 */
typedef uint32_t (*enact_hal_init_cb_t)(void);

/**
 * @brief Registers the HAL initialization callback.
 * Must be called before enacttrust_freertos_task_create().
 * @param callback Function pointer to the customer HAL init implementation.
 */
void enacttrust_freertos_set_hal_init(enact_hal_init_cb_t callback);

/**
 * @brief Creates the EnactTrust FreeRTOS task.
 * @param task_handle Pointer to a TaskHandle_t to store the created task handle, or NULL.
 * @return pdPASS if the task was created successfully, otherwise an error code.
 */
BaseType_t enacttrust_freertos_task_create(TaskHandle_t *task_handle);

/**
 * @brief Notifies the EnactTrust task from an ISR.
 * For example, can be used from the application timer ISR.
 */
void enacttrust_freertos_notify_from_isr(void);

#endif /* ENACTTRUST_FREERTOS_PORT_H_ */