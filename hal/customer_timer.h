/* customer_timer.h
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

#ifndef CUSTOMER_TIMER_H_
#define CUSTOMER_TIMER_H_

#include "cybsp.h"
#include <stdint.h>

#define CUSTOMER_TIMER_INTERRUPT_PRIORITY  (3)
#define CUSTOMER_TIMER_HZ                  (10000u)
#define CUSTOMER_TIMER_TICKS_PER_MS        (CUSTOMER_TIMER_HZ / 1000u)

/**
 * @brief Configures a FreeRTOS timer for EnactTrust to use
 * @return 0 for success, non-zero for error.
 */
cy_rslt_t customer_timer_init(void);

/**
 * @brief Starts the guard timer.
 * @return 0 for success, non-zero for errors.
 */
uint32_t customer_timer_start(uint32_t timeout_ms);

#endif /* CUSTOMER_TIMER_H_ */
