/* customer_spi.c
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

#include "customer_spi.h"
#include "cy_pdl.h"
#include "cy_result.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <string.h>
#include <stdint.h>

/* SPI interface */
#define ENACT_SPI_CLK_100kHz      (100000u)
#define ENACT_SPI_CLK_1MHz        (1000000u)
#define ENACT_SPI_CLK_10MHZ       (10000000u)
/* CYW920829 EVK with silicon revision B0
 * 10-pin GPIO HEADER marked as J18 on the PCB
 */
#define ENACT_SPI_MOSI                  (P0_2)
#define ENACT_SPI_MISO                  (P0_3)
#define ENACT_SPI_CLK                   (P0_4)
#define ENACT_SPI_CS                    (P0_0)
#define ENACT_SPI_MANUAL_CS             (NC)
/* cyhal_spi_init() takes a `is_slave` argument, thus set to false */
#define ENACT_SPI_AS_MASTER             (false)

static cyhal_spi_t enact_spi;

cy_rslt_t customer_spi_init(void)
{
    cy_rslt_t res = CY_RSLT_SUCCESS;

    memset(&enact_spi, 0, sizeof(enact_spi));

    /* TPM 2.0 requires SPI mode with CPOL=0 CPHA=0 equals to SPI MODE 0 */
#ifdef TPM_WAIT_STATES
    res = cyhal_gpio_init(ENACT_SPI_CS, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, true);
    if (res != CY_RSLT_SUCCESS) {
        printf("Error: CS GPIO Init failed\n");
        return res;
    }
    res = cyhal_spi_init(&enact_spi, ENACT_SPI_MOSI, ENACT_SPI_MISO, ENACT_SPI_CLK,
                         ENACT_SPI_MANUAL_CS, NULL, 8, CYHAL_SPI_MODE_00_MSB,
                         ENACT_SPI_AS_MASTER);
#else
    res = cyhal_spi_init(&enact_spi, ENACT_SPI_MOSI, ENACT_SPI_MISO, ENACT_SPI_CLK,
                         ENACT_SPI_CS, NULL, 8, CYHAL_SPI_MODE_00_MSB,
                         ENACT_SPI_AS_MASTER);
#endif
    if (res != CY_RSLT_SUCCESS) {
        printf("Error: SPI Init failed\n");
        return res;
    }

    res = cyhal_spi_set_frequency(&enact_spi, ENACT_SPI_CLK_1MHz);
    if (res != CY_RSLT_SUCCESS) {
        printf("Error: SPI Setting frequency failed\n");
    }
    return res;
}

uint32_t customer_spi_transfer(const uint8_t* transmit_data, uint8_t* received_data, size_t size)
{
    cy_rslt_t res = CY_RSLT_SUCCESS;
    /* This is a blocking function */
    res = cyhal_spi_transfer(&enact_spi, transmit_data, size, received_data, size, 0x00);
    return (uint32_t)res;
}

#ifdef TPM_WAIT_STATES
void customer_spi_cs(bool drive_low)
{
    cyhal_gpio_write(ENACT_SPI_CS, !drive_low); /* CS is active low */
}
#endif

