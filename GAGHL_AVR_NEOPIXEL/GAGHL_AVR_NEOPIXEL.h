/**
 * @file GAGHL_AVR_NEOPIXEL.h
 * @brief Lightweight WS2812B (NeoPixel) control library for AVR microcontrollers.
 * 
 * This library allows control of a strip or array of WS2812B addressable RGB LEDs
 * using precise timing via bit-banging, suitable for bare-metal AVR environments.
 * 
 * @author GAGHL
 * @date July 16, 2025
 */

#ifndef GAGHL_AVR_NEOPIXEL_H_
#define GAGHL_AVR_NEOPIXEL_H_

#include <stdint.h>
#include <util/delay.h>

#if defined(__AVR_ATtiny13__) || defined(__AVR_ATtiny13A__)

#ifndef F_CPU
	#define F_CPU 9600000UL
	#warning "F_CPU is not defined! Default value will be used."
#endif

#else // If MCU is not ATtiny13 or ATtiny13A

#ifndef F_CPU
	#define F_CPU 8000000UL
	#warning "F_CPU is not defined! Default value will be used."
#endif

#endif // defined(__AVR_ATtiny13__) || defined(__AVR_ATtiny13A__)

/**
 * @def NEOPIXEL_MAX_LEDS
 * @brief Maximum number of LEDs supported in the strip.
 * 
 * This value defines the size of the internal buffer used for color data.
 */
#define NEOPIXEL_MAX_LEDS 28

/**
 * @var neopixel_buffer
 * @brief Internal data buffer (size: NEOPIXEL_MAX_LEDS * 3) for LED color values.
 * 
 * Each LED requires 3 bytes (R, G, B). This buffer is used during transmission.
 */
extern uint8_t neopixel_buffer[NEOPIXEL_MAX_LEDS * 3];

/**
 * @brief Initializes the NeoPixel output pin.
 * 
 * Must be called before any other NeoPixel functions. Configures the data pin as output.
 */
void neopixel_init(void);

/**
 * @brief Sends raw data to the LED strip using precise timing.
 * 
 * This function is called internally by `neopixel_display()` and usually shouldn't be called directly.
 * 
 * @param data Pointer to the RGB byte array.
 * @param length Number of bytes to send (typically 3 * number of LEDs).
 */
void neopixel_send(uint8_t *data, uint8_t length);

/**
 * @brief Updates the LED strip to reflect changes in the internal buffer.
 * 
 * This function applies the current brightness and sends the data to the LEDs.
 */
void neopixel_display(void);

/**
 * @brief Clears the LED color buffer (sets all colors to 0).
 * 
 * You still need to call `neopixel_display()` to send the cleared data to the strip.
 */
void neopixel_clear(void);

/**
 * @brief Sets the RGB color of a specific LED in the strip.
 * 
 * @param index Index of the LED (0-based).
 * @param r Red component (0–255).
 * @param g Green component (0–255).
 * @param b Blue component (0–255).
 */
void neopixel_setPixel(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Sets the global brightness level for all LEDs.
 * 
 * @param brightness Brightness value (0–255). Affects all LEDs during `neopixel_display()`.
 */
void neopixel_setBrightness(uint8_t brightness);

/**
 * @brief Displays a rainbow gradient across the LED strip.
 * 
 * @param offset Hue offset for animation (0–255).
 * @param spacing Distance between hues (lower = faster color change).
 */
void neopixel_rainbow(uint8_t offset, uint8_t spacing);

#endif // GAGHL_AVR_NEOPIXEL_H_
