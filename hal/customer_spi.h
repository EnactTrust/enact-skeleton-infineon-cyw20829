/* customer_spi.h
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

#ifndef CUSTOMER_SPI_H_
#define CUSTOMER_SPI_H_

#include "cybsp.h"
#include <stdint.h>
#ifdef TPM_WAIT_STATES
#include <stdbool.h>
#endif

/**
 * @brief Initialises the SPI peripheral for EnactTrust to use.
 * @return 0 for success, non-zero for error.
 */
cy_rslt_t customer_spi_init(void);

/**
 * @brief Blocking SPI transfer.
 * @param transmit_data Pointer to data to transmit.
 * @param received_data Pointer to buffer for received data.
 * @param size Number of bytes to transfer.
 * @return 0 for success, non-zero for error.
 */
uint32_t customer_spi_transfer(const uint8_t* transmit_data, uint8_t* received_data, size_t size);

#ifdef TPM_WAIT_STATES
/**
 * @brief Drives the SPI chip select line.
 * @param drive_low true to assert CS (active low), false to deassert.
 */
void customer_spi_cs(bool drive_low);
#endif

#endif /* CUSTOMER_SPI_H_ */
