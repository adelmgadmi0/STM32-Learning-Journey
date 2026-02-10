# 🛰️ STM32 Learning Journey

A collection of my firmware projects for STM32, covering both high-level abstraction (HAL) and low-level hardware control (Bare Metal).

---

## 🛠️ Project Categories

### 🔴 Bare Metal Projects
*Projects written by directly manipulating registers (No HAL), focusing on memory maps and bit-fields.*

* **01_LED_ON**: Basic GPIO initialization using address-based register access.
* **02_LED_Toggle_Bitfields**: Toggling LEDs using C-structures and bit-field mapping for cleaner code.
* **03_IO_Toggle_Structures**: Implementing full port control using Nucleo-specific register structures.

### 🔵 HAL / CubeMX Projects
*Projects utilizing the STM32 Hardware Abstraction Layer for rapid development.*

* **01_HSE_SYSCLK_8MHz**: System clock configuration using External High-Speed crystal.
* **02_Configuring_Time_100ms_IT**: Timer configuration using interrupts for precise 100ms timing.
* **03_Timer_Input_Capture_UART**: Measuring signal frequency using Input Capture and reporting data via UART.
* **04_UART_Communication**: Basic serial transmission and file handling.


---


**Hardware Used:** STM32-F446-RE Nucleo Board
**Tools:** STM32CubeIDE, ARM Compiler

---
