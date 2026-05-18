/* enacttrust.h
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

#ifndef ENACTTRUST_H_
#define ENACTTRUST_H_

#include <stdint.h>
#include <stddef.h>
#ifdef TPM_WAIT_STATES
#include <stdbool.h>
#endif

/**
 * @brief Generic logging callback type.
 * @param message The string to log.
 */
typedef void (*enact_log_cb_t)(const char* message);

/* Status Codes */
typedef enum {
    ENACT_STATUS_OK      = 0,
    ENACT_STATUS_HAL_ERR = 1,
    ENACT_STATUS_ERROR   = 2,
    ENACT_STATUS_BUSY    = 3,
    ENACT_STATUS_TIMEOUT = 4,
    ENACT_STATUS_ABORTED = 5,
    ENACT_STATUS_MAX     = 6
} enact_status_t;

/**
 * @brief Generic error logging callback type.
 * @param error_code The specific error code.
 * @param file The file where the error occurred.
 * @param line The line number where the error occurred.
 * @param message A descriptive error message string.
 */
typedef void (*enact_error_log_cb_t)(uint32_t error_code, const char* file, int line, const char* message);

/**
 * @brief Type definition for the SPI transfer callback function.
 * This function should perform a blocking SPI transfer.
 * @param tx_buffer Pointer to the transmit data buffer.
 * @param rx_buffer Pointer to the receive data buffer.
 * @param size The number of bytes to transfer.
 * @return A status code (0 for success, non-zero for error).
 */
typedef uint32_t (*enact_spi_transfer_cb_t)(const uint8_t* tx_buffer, uint8_t* rx_buffer, size_t size);

/**
 * @brief Type definition for the Timer start function.
 * This function should trigger a new timer period (event).
 * @param ms the timer period set in milliseconds
 * @return A status code (0 for success, non-zero for error).
 */
typedef uint32_t (*enact_timer_start_cb_t)(const uint32_t ms);

/**
 * @brief Type definition for the firmware update artifact read callback.
 * The library calls this to read chunks of the update binary from customer storage.
 * The buffer is library-owned; the customer implementation must fill it.
 * @param offset Byte offset from the start of the update artifact.
 * @param buffer Pointer to the library-owned destination buffer.
 * @param size Number of bytes to read.
 * @return A status code (0 for success, non-zero for error).
 */
typedef uint32_t (*enact_read_cb_t)(uint32_t offset, uint8_t* buffer, size_t size);

#ifdef TPM_WAIT_STATES
/**
 * @brief Type definition for the SPI chip-select control callback.
 * Required when manual CS is used to support TPM 2.0 busy-wait polling
 * under a single CS assertion.
 * @param drive_low true to assert CS (drive low), false to deassert (drive high).
 */
typedef void (*enact_spi_cs_cb_t)(bool drive_low);
#endif


/**
 * @brief Initializes the EnactTrust core module.
 * This function should be called once before any other EnactTrust functions.
 */
void enacttrust_init(void);

/**
 * @brief Runs one cycle of the EnactTrust state machine.
 * This function should be called periodically by the application's main loop or task.
 */
void enacttrust_process(void);

/**
 * @brief Notifies the EnactTrust core that a timer event has occurred.
 * This function should be called by the application's timer handler.
 */
void enacttrust_timeout_occurred(void);

/**
 * @brief Sets the SPI transfer callback function.
 * @param callback A function pointer to the application's SPI transfer implementation.
 */
void enacttrust_set_spi_callback(enact_spi_transfer_cb_t callback);

/**
 * @brief Sets the Timer start callback function.
 * @param callback A function pointer to the application's Timer start implementation.
 */
void enacttrust_set_timer_callback(enact_timer_start_cb_t callback);

#ifdef TPM_WAIT_STATES
/**
 * @brief Sets the SPI chip-select control callback.
 * @param callback Function pointer to the customer CS assert/deassert implementation.
 */
void enacttrust_set_spi_cs_callback(enact_spi_cs_cb_t callback);
#endif

/**
 * @brief Returns the maximum SPI transfer buffer size in bytes.
 * @return The size of the internal SPI buffer.
 */
size_t enacttrust_get_spi_max_buffer(void);

/**
 * @brief Sets the general logging callback function.
 * @param callback A function pointer to the application's log output implementation.
 */
void enacttrust_set_log_callback(enact_log_cb_t callback);

/**
 * @brief Sets the error logging callback function.
 * @param callback A function pointer to the application's error log implementation.
 */
void enacttrust_set_error_log_callback(enact_error_log_cb_t callback);

/**
 * @brief Sets the firmware update artifact read callback function.
 * @param callback A function pointer to the customer's storage read implementation.
 */
void enacttrust_set_read_callback(enact_read_cb_t callback);

#endif /* ENACTTRUST_H_ */
