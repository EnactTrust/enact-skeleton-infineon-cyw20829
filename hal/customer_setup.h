/* customer_setup.h
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

#ifndef CUSTOMER_SETUP_H_
#define CUSTOMER_SETUP_H_

#include <stdint.h>

/**
 * @brief Initializes all HAL peripherals (SPI, timer, flash) and
 *        registers their callbacks with the EnactTrust core.
 *        Must be called from task context (FreeRTOS scheduler running).
 * @return 0 for success, non-zero if a peripheral failed to initialize.
 */
uint32_t customer_hal_init(void);

#endif /* CUSTOMER_SETUP_H_ */
