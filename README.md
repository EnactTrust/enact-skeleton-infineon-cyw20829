# EnactTrust Skeleton — Quick Customer Integration

> EnactTrust keeps the firmware on your Trusted Platform Module up to date — securely and automatically.

No modifications are needed for Infineon AIROC™ CYW20829 (Cortex-M33).

Customers using non-Infineon MCU have to translate all vendor-specific `cyhal` calls. The code skeleton clearly outlines *what* to implement and DesignFirst can assist with the *how* when needed.

## Integration Checklist

✅ FreeRTOS integration ready to flash on target    
✅ MCU-agnostic Hardware Abstraction Layer (HAL)   
✅ Correct SPI configuration for TPM 2.0   
✅ One-shot Timer configuration for handling timeouts   
✅ Safe "Setter" API for HAL callbacks          
✅ Example main.c application with expected UART output:

```
[CUSTOMER_SETUP]: HAL setup is ready.
[ENACT_LOG]: Success.
```

## True Plug-and-play Integration

The customer does not write the FreeRTOS task for TPM update. The customer also does not have to figure out the interfacing between the HAL and EnactTrust TPM Update process.

> Baremetal applications do not need to use the `enacttrust_freertos_port.c`. Simply call `enacttrust_process()` from your firmware.

## Customer HAL layer (customer_spi.c, customer_timer.c, customer_setup.c)

The skeleton's HAL answers the hardest questions a customer on any platform faces:
- Exact SPI configuration required for TPM 2.0 (Mode 0, MSB, 8-bit, 1 MHz)
- How the timer callback must behave (one-shot, calls `enacttrust_timeout_occurred()` on expiry)
- The order callbacks must be registered before the TPM Update task starts

HAL integration available under [hal/](https://github.com/enacttrust/enact-skeleton/hal) is ready to flash on target for AIROC CYW20829.

## Complete Firmware Example (main.c)

Demonstration of how the EnactTrust TPM Update process interacts with the real hardware and makes the HAL init pattern explicit: the HAL init runs inside the FreeRTOS task after the scheduler starts, not before. Out-of-the-box experience for supported development and evaluation boards:
- CYW920829M2EVK

## Supported TPM 2.0 solutions

- Infineon SLI 9670, SLM 9670, SLB 9670
- Infineon SLB 9673, SLB 9672
- Nuvoton (requires pre-approval process)

## Project Structure

```
enact-skeleton/
│
├── main.c                               # Application entry point
├── FreeRTOSConfig.h                     # FreeRTOS configuration
├── Makefile                             # Build system
│
├── enact/                               # EnactTrust core (do not modify)
│   ├── enacttrust.h                     # Public API
│   ├── libenacttrust.a                  # Binary of the licensed library
│   ├── enacttrust_freertos_port.c/.h    # FreeRTOS porting layer
│
├── hal/                                 # Customer HAL layer(platform-specific)
│   ├── customer_setup.c/.h              # HAL init and callback registration
│   ├── customer_spi.c/.h                # SPI transport implementation
│   └── customer_timer.c/.h              # One-shot timer implementation
│
└── deps/                                # ModusToolbox dependency manifests
```

## License

This software is source-available under the [PolyForm Strict License 1.0.0](LICENSE.md) — free for noncommercial evaluation, study, and testing. Commercial use requires a written commercial agreement with DesignFirst OU. Contact [licensing@enacttrust.com](mailto:licensing@enacttrust.com).
