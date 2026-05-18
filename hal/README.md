# HAL — Customer Integration Layer

This folder contains the customer-provided Hardware Abstraction Layer that wires EnactTrust to your specific MCU peripherals. 

`customer_spi.c` implements the SPI transport (Mode 0, MSB-first, 8-bit, 1 MHz) required by TPM 2.0. 

`customer_timer.c` implements the one-shot timer (10 kHz base clock, millisecond periods) used for TPM timeouts.

`customer_flash.c` implements the firmware update artifact read function. On CYW20829 the ROM bootloader initialises the SMIF peripheral and enters XIP mode before the application starts, so the external flash is directly readable as memory — no driver calls are required. `CUSTOMER_UPDATE_ARTIFACT_ADDR` in `customer_flash.h` sets the base address of the artifact in flash and must be adjusted to match your product's flash layout.

`customer_setup.c` ties everything together: it initializes all peripherals and registers their callbacks with the EnactTrust core. It is called synchronously from within the EnactTrust FreeRTOS task before the state machine starts.

This reference Customer Integration Layer targets Infineon AIROC™ CYW20829. `customer_spi.c` and `customer_timer.c` use `cyhal` directly; `customer_flash.c` uses direct memory access and requires no HAL. On any other MCU, replace these four files while keeping every function signature and callback contract intact — the EnactTrust core and FreeRTOS port never need to change.