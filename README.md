<h1 align="center">In the name of GOD</h1>

# GAGHL_AVR_NEOPIXEL

**A lightweight and fast WS2812B (NeoPixel) driver library for AVR microcontrollers**

Designed for bare-metal AVR development using register-level code and precise bit-banging.


## 📦 Features

- ✅ Supports up to **85** WS2812B LEDs (configurable)
- ✅ Built-in `rainbow()` animation function
- ✅ Global brightness control
- ✅ Automatic `display()` after color/buffer updates
- ✅ Simple C-style API
- ✅ Customizable Port and Pin macros
- ✅ Optimized for 8MHz clock with inline assembly

## 📚 API Overview

| Function                   | Parameters                        | Description                                                         |
| -------------------------- | --------------------------------- | ------------------------------------------------------------------- |
| `neopixel_init()`          | *(void)*                          | Initializes the LED port/pin and clears the LED buffer              |
| `neopixel_send()`          | `uint8_t *data, uint8_t length`   | Sends raw data to the LED strip (used internally by `display()`)    |
| `neopixel_display()`       | *(void)*                          | Sends the current buffer (`neopixel_buffer`) to the LED strip       |
| `neopixel_clear()`         | *(void)*                          | Sets all pixels in the buffer to black (off)                        |
| `neopixel_setPixel()`      | `uint8_t index, uint8_t r, g, b`  | Sets the RGB color of the pixel at given index                      |
| `neopixel_setBrightness()` | `uint8_t brightness`              | Applies a global brightness scaling (0–255) to all pixel data       |
| `neopixel_rainbow()`       | `uint8_t offset, uint8_t spacing` | Fills the buffer with a rainbow gradient starting at offset         |
| `neopixel_shift()`         | `int8_t amount`                   | Shifts the LED buffer left/right by `amount` positions (circularly) |


## 🚀 Getting Started

### 1. Add the files to your project

Copy these files into your AVR project:

- `GAGHL_AVR_NEOPIXEL.c`
- `GAGHL_AVR_NEOPIXEL.h`

### 2. Configuration

You can customize the following macros in the .c file:

```c
#define LED_PORT PORTC
#define LED_DDR  DDRC
#define LED_PIN  0
```


### 3. Example
```c
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "GAGHL_AVR_NEOPIXEL.h"

int main(void) {
	neopixel_init();
	neopixel_setBrightness(255);

	while (1) {
		for (uint8_t i = 0; i < 10; i++) {
			neopixel_setPixel(i, 255, 0, 0); // Red
			_delay_ms(100);
			neopixel_display();
		}
		for (uint8_t i = 0; i < 10; i++) {
			neopixel_setPixel(i, 0, 255, 0); // Green
			_delay_ms(100);
			neopixel_display();
		}
		for (uint8_t i = 0; i < 10; i++) {
			neopixel_setPixel(i, 0, 0, 255); // Blue
			_delay_ms(100);
			neopixel_display();
		}
	}
}

```

## Wiring
```c
MCU PIN -----------------> DIN on first WS2812B
+5V ---------------------> VCC
GND ---------------------> GND
```
⚠️ Make sure you use a 100nF capacitor near the LED and optionally a resistor (≈330Ω) in series with the DIN line

## 🤝 Contributing

Contributions are welcome!  
Whether it's bug fixes, feature suggestions, or improvements — your help is appreciated.

- Fork the repository
- Create a new branch (`git checkout -b feature/my-feature`)
- Commit your changes (`git commit -am 'Add new feature'`)
- Push to the branch (`git push origin feature/my-feature`)
- Open a Pull Request

If you’re using this library in your project, feel free to let me know — I’d love to check it out!

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0).

You are free to:
- Share — copy and redistribute the material in any medium or format
- Adapt — remix, transform, and build upon the material

Under the following terms:
- **Attribution** — You must give appropriate credit to the author (GAGHL).
- **NonCommercial** — You may not use the material for commercial purposes without explicit permission.

For more information, see the full license: [https://creativecommons.org/licenses/by-nc/4.0/](https://creativecommons.org/licenses/by-nc/4.0/)

© 2025 GAGHL. All rights reserved.

## Author

Developed by [GAGHL](https://github.com/GAGHL)
