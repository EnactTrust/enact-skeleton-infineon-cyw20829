/* enacttrust.c
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

#include "enacttrust.h"

/*
 * NOTE: This file is a build stub. The full implementation is distributed as
 * libenacttrust.a after a written Commercial License Agreement with DesignFirst OU.
 * Replace this file with the pre-compiled library for production use.
 */

 #define ENACT_SPI_MAX_BUFFER (1024u)

static enact_log_cb_t enact_log_callback = NULL;

void enacttrust_init(void) {}

void enacttrust_process(void)
{
    enact_log_callback("Success.");
}

void enacttrust_timeout_occurred(void) {}

void enacttrust_set_spi_callback(enact_spi_transfer_cb_t callback)
{
    (void)callback;
}

void enacttrust_set_timer_callback(enact_timer_start_cb_t callback)
{
    (void)callback;
}

#ifdef TPM_WAIT_STATES
void enacttrust_set_spi_cs_callback(enact_spi_cs_cb_t callback)
{
    (void)callback;
}
#endif

size_t enacttrust_get_spi_max_buffer(void)
{
    return ENACT_SPI_MAX_BUFFER;
}

void enacttrust_set_log_callback(enact_log_cb_t callback)
{
    enact_log_callback = callback;
}

void enacttrust_set_error_log_callback(enact_error_log_cb_t callback)
{
    (void)callback;
}

void enacttrust_set_read_callback(enact_read_cb_t callback)
{
    (void)callback;
}
