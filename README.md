# 🛰️ STM32 Learning Journey

A collection of my firmware projects for STM32, covering both high-level abstraction (HAL) and low-level hardware control (Bare Metal).

> **Note:** For HAL projects, I wrote the `main.c`, `msp.c`, `it.c`, and header files manually to deeply understand the library structure and interrupt handling, rather than relying on auto-generated code.
---
.
├── Bare_Metal/
│   ├── 01_LED_Toggle_Bitfields/                
│   ├── 02_LED_ON/  
│   └── 03_Read_Pin/              
├── HAL_Projects/
│   ├── 01_HSE_SYSCLK/           
│   ├── 02_PLL_SYSCLK/            
│   ├── 03_Timer_Time_100ms_IT/   
│   ├── 04_UART_RX_TX_IT/         
│   └── 05_Timer_Input_Capture_UART/   
└── README.md                    

## 🛠️ Project Categories

### 🔴 [Bare Metal Projects](./Bare_Metal)
*Direct register access (No HAL) to understand the ARM Cortex-M architecture.*
* **[LED ON](./Bare_Metal/02_LED_ON)**: Basic GPIO initialization using address-based register access.
* **[LED Toggle (Bit-fields)](./Bare_Metal/01_LED_Toggle_Bitfields)**: Toggling LEDs using C-structures and bit-field mapping for cleaner code.
* **[Read Pin](./Bare_Metal/03_READ_PIN)**: Reading digital input by polling the Input Data Register (IDR).

### 🔵 [HAL / Manual Integration](./HAL_Projects)
*Hand-written HAL implementation focusing on peripheral initialization and ISR management.*
* **[HSE System Clock](./HAL_Projects/01_HSE_SYSCLK)**: Manually configured the RCC to bypass the internal oscillator and use the External High-Speed crystal for a stable clock source.
* **[PLL System Clock](./HAL_Projects/02_PLL_SYSCLK)**: Implemented Phase-Locked Loop (PLL) configuration to overclock the system to its maximum frequency while managing bus prescalers.
* **[BASIC TIMER with 100ms Time Base with IT](./HAL_Projects/03_Timer_Time_100ms_IT)**: Configured a basic timer with custom ISR handling in it.c to trigger precise 100ms periodic events.
* **[Recieving and Transmitting data with UART](./HAL_Projects/04_UART_RX_TX_IT)**: Developed non-blocking serial communication using Interrupts (RXNE/TXE), handling data flow without stalling the CPU.
* **[Input Capture & UART](./HAL_Projects/05_Timer_Input_Capture_UART)**: Measured LSE Clock signal frequency via Timer Input Capture mode and reported results through UART peripheral.
---


**Hardware Used:** STM32-F446-RE Nucleo Board
**Tools:** STM32CubeIDE, ARM Compiler

---
