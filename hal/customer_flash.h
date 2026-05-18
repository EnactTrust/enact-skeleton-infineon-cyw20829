/* customer_flash.h
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

#ifndef CUSTOMER_FLASH_H_
#define CUSTOMER_FLASH_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Base address of the firmware update artifact in external flash.
 * Adjust to match the actual flash layout of your product.
 * On CYW20829 the SMIF XIP window starts at 0x60000000 and is live
 * before the application runs (initialised by the ROM bootloader).
 */
#define CUSTOMER_UPDATE_ARTIFACT_ADDR   (0x60000000U)

/**
 * @brief Reads a chunk of the firmware update artifact from external flash.
 * Registered with EnactTrust via enacttrust_set_read_callback().
 * @param offset Byte offset from the start of the artifact.
 * @param buffer Library-owned destination buffer to fill.
 * @param size Number of bytes to read.
 * @return 0 for success, non-zero for error.
 */
uint32_t customer_flash_read(uint32_t offset, uint8_t* buffer, size_t size);

#endif /* CUSTOMER_FLASH_H_ */
