/* customer_setup.c
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

#include "hal/customer_setup.h"
#include "hal/customer_spi.h"
#include "hal/customer_timer.h"
#include "hal/customer_flash.h"
#include "enact/enacttrust.h"
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

uint32_t customer_hal_init(void)
{
    cy_rslt_t res;

    res = customer_spi_init();
    if (res != CY_RSLT_SUCCESS)
    {
        printf("[CUSTOMER_SETUP]: SPI init failed.\n");
        return (uint32_t)res;
    }
    enacttrust_set_spi_callback(customer_spi_transfer);
#ifdef TPM_WAIT_STATES
    enacttrust_set_spi_cs_callback(customer_spi_cs);
#endif

    res = customer_timer_init();
    if (res != CY_RSLT_SUCCESS)
    {
        printf("[CUSTOMER_SETUP]: Timer init failed.\n");
        return (uint32_t)res;
    }
    enacttrust_set_timer_callback(customer_timer_start);
    enacttrust_set_read_callback(customer_flash_read);

    printf("[CUSTOMER_SETUP]: HAL setup is ready.\n");
    return 0U;
}
