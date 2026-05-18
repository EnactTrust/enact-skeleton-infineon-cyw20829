# EnactTrust for TPM 2.0 firmware update

EnactTrust keeps the firmware on your Trusted Platform Module up to date — securely and automatically. It either connects to the EnactTrust cloud or performs offline update.

A. EnactTrust can regularly check whether a newer firmware version is available, download the update, and apply it to the TPM.   
B. EnactTrust can also perform a completely offline update from a locally provisioned package — all without any manual intervention.   

EnactTrust is hardware-agnostic by design: a thin customer integration layer wires it to your SPI bus and timer peripherals, so it can run on any microcontroller. Run the included project example or follow the instructions below to use EnactTrust inside your existing project.


>The files in this directory are the EnactTrust header and FreeRTOS port. They are complete and must not be modified.

## Quick start in 5 lines of code

This variant of EnactTrust runs as a FreeRTOS task. EnactTrust itself is hardware agnostic and there is a strict initialization routine.

1) Include EnactTrust in your project

`#include "enact/enacttrust.h"`
 
2) Interface EnactTrust with your hardware

```
enacttrust_set_log_callback(app_log_callback);
enacttrust_set_error_log_callback(app_error_log_callback);
enacttrust_freertos_set_hal_init(customer_hal_init);
```

3) Create the EnactTrust TPM Update task

`status = enacttrust_freertos_task_create(NULL);`

Note: Do not forget to start the FreeRTOS scheduler when starting from an empty project. The skeleton implementation already calls `vTaskStartScheduler();`.

## Expected Hardware Abstraction Layer

Reference implementation for Infineon CYW920829M2EVK is available under [hal/](../hal/). Below are details when using different hardware.

### HAL initialization callback

Define a `customer_hal_init` callback without arguments and return value that performs the SPI & Timer initialization as described below. Reference implementation is provided in `hal/customer_setup.c`.

### SPI

SPI initialization using the defined values in `hal/customer_spi.h`. Reference implementation of working SPI configuration for TPM 2.0 is provided in `hal/customer_spi.c`.

```
TPM 2.0 requires SPI mode with CPOL=0 CPHA=0 (SPI MODE 0). Most Significant Byte is sent first and data width is 8 bits.
```

### Timer

Timer initialization using the defined values in `hal/customer_timer.h`. Reference implementation of working Timer configuration for TPM 2.0 is provided in `hal/customer_timer.c`.

```
Timer frequency is 10kHz and EnactTrust starts one-shot timer with millisecond periods
```

### Read update binary

EnactTrust reads the firmware update artifact from customer storage in chunks via a registered callback. The library owns the destination buffer and passes a pointer to it; the customer implementation must fill it (zero-copy).

Register the callback in your HAL init function:

```c
enacttrust_set_read_callback(customer_flash_read);
```

The callback signature is:

```c
uint32_t customer_flash_read(uint32_t offset, uint8_t* buffer, size_t size);
```

- `offset` — byte offset from the start of the artifact (not an absolute flash address)
- `buffer` — library-owned destination buffer to fill
- `size` — number of bytes to read
- returns 0 on success, non-zero on error

Define `CUSTOMER_UPDATE_ARTIFACT_ADDR` in `hal/customer_flash.h` to point to the base address of the artifact in your flash layout. The reference implementation in `hal/customer_flash.c` uses a direct memory read (SMIF XIP is active before the application starts on CYW20829, so no driver calls are required).

## Important notice

The files in this directory are the EnactTrust core and FreeRTOS port. They are complete and must not be modified.