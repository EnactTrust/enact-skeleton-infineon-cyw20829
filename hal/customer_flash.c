/* customer_flash.c
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

#include "customer_flash.h"
#include <string.h>

/*
 * On CYW20829, the ROM bootloader initialises the SMIF peripheral and enters
 * XIP (execute-in-place) mode before jumping to the application. The external
 * flash is therefore accessible as ordinary memory at CUSTOMER_UPDATE_ARTIFACT_ADDR
 * by the time this function is called. No SMIF driver initialisation is required.
 */
uint32_t customer_flash_read(uint32_t offset, uint8_t* buffer, size_t size)
{
    memcpy(buffer, (const uint8_t*)(CUSTOMER_UPDATE_ARTIFACT_ADDR + offset), size);
    return 0U;
}