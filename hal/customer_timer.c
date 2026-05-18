/* customer_timer.c
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

#include "customer_timer.h"
#include "cy_pdl.h"
#include "cy_result.h"
#include "cyhal.h"
#include "cybsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cy_retarget_io.h"
#include "enact/enacttrust.h"           /* For notifying the agnostic core */

static cyhal_timer_t timer_obj;

static void customer_timer_callback(void *callback_arg, cyhal_timer_event_t event);

cy_rslt_t customer_timer_init(void)
{
    cy_rslt_t rslt;
    /* Initialize the timer object. Does not use pin output ('pin' is NC) and
     * does not use a pre-configured clock source ('clk' is NULL). */
    rslt = cyhal_timer_init(&timer_obj, NC, NULL);
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
    rslt = cyhal_timer_set_frequency(&timer_obj, CUSTOMER_TIMER_HZ);
    if(rslt == CY_RSLT_SUCCESS) {
        /* Assign the ISR to execute on timer interrupt */
        cyhal_timer_register_callback(&timer_obj, customer_timer_callback, NULL);
        /* Set the event on which timer interrupt occurs and enable it */
        cyhal_timer_enable_event(&timer_obj, CYHAL_TIMER_IRQ_TERMINAL_COUNT, CUSTOMER_TIMER_INTERRUPT_PRIORITY, true);
    }
    return rslt;
}

void customer_timer_callback(void *callback_arg, cyhal_timer_event_t event)
{
    (void)callback_arg;
    (void)event;

    /* Signal timeout to the agnostic core; state machine checks this on its next scheduled cycle. */
    enacttrust_timeout_occurred();
}

uint32_t customer_timer_start(uint32_t timeout_ms)
{
    cy_rslt_t result;

    const cyhal_timer_cfg_t timer_cfg =
    {
        .compare_value = 0,                 /* Timer compare value, not used */
        .period = timeout_ms * CUSTOMER_TIMER_TICKS_PER_MS,
        .direction = CYHAL_TIMER_DIR_UP,    /* Timer counts up */
        .is_compare = false,                /* Don't use compare mode */
        .is_continuous = false,             /* Run the timer once (per event */
        .value = 0                          /* Initial value of counter */
    };

    result = cyhal_timer_configure(&timer_obj, &timer_cfg);
    if(result == CY_RSLT_SUCCESS) {
        result = cyhal_timer_reset(&timer_obj);
        if(result == CY_RSLT_SUCCESS) {
            result = cyhal_timer_start(&timer_obj);
        }
    }

    return (uint32_t)result;
}
