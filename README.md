# 🛰️ STM32 Learning Journey

A collection of my firmware projects for STM32, covering both high-level abstraction (HAL) and low-level hardware control (Bare Metal).

> **Note:** For HAL projects, I wrote the `main.c`, `msp.c`, `it.c`, and header files manually to deeply understand the library structure and interrupt handling, rather than relying on auto-generated code.
---

## 🛠️ Project Categories

### 🔴 [Bare Metal Projects](./Bare_Metal)
*Direct register access (No HAL) to understand the ARM Cortex-M architecture.*
* **[LED ON](./Bare_Metal/02_LED_ON)**: Basic GPIO initialization using address-based register access.
* **[LED Toggle (Bit-fields)](./Bare_Metal/01_LED_Toggle_Bitfields)**: Toggling LEDs using C-structures and bit-field mapping for cleaner code.
* **[Read Pin](./Bare_Metal/03_READ_PIN)**: Reading digital input by polling the Input Data Register (IDR).

### 🔵 [HAL / Manual Integration](./HAL_Projects)
*Hand-written HAL implementation focusing on peripheral initialization and ISR management.*
* **[HSE System Clock](./HAL_Projects/01_HSE_SYSCLK)**: Manual configuration of the HSE crystal and Bus clocks.
* **[Timer Interrupts](./HAL_Projects/03_Timer_Time_100ms_IT)**: Implementing `it.c` handlers for precise 100ms timing.
* **[Input Capture & UART](./HAL_Projects/04_Timer_Input_Capture_UART)**: Frequency measurement with custom UART transmission logic.


---


**Hardware Used:** STM32-F446-RE Nucleo Board
**Tools:** STM32CubeIDE, ARM Compiler

---
