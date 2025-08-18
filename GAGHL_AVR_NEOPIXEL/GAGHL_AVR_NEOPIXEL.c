/*
 * GAGHL_AVR_NEOPIXEL.c
 *
 * Created: 7/16/2025 5:36:02 PM
 *  Author: GAGHL
 */ 

#include "GAGHL_AVR_NEOPIXEL.h"

// Customize these macros for your LED port/pin
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN 0

uint8_t neopixel_rawBuffer[NEOPIXEL_MAX_LEDS * 3];
static uint8_t neopixel_brightness = 255;

#ifdef __AVR_ATtiny13A__

void neopixel_display(void) {
	
	cli();

	for (uint16_t i = 0; i < (NEOPIXEL_MAX_LEDS * 3); i++) {
		
		uint16_t scaled = ((uint16_t)neopixel_rawBuffer[i] * neopixel_brightness) >> 8;
		uint8_t byte = (uint8_t)scaled;

		
		for (uint8_t b = 0; b < 8; b++) {
			if (byte & 0x80) {
				// Send bit '1' (HIGH ~0.729us, LOW ~0.625us)
				asm volatile (
				"sbi %[port], %[pin]\n\t"   // HIGH (2 clk)
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"cbi %[port], %[pin]\n\t"   // LOW (2 clk)
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				:
				: [port] "I" (_SFR_IO_ADDR(LED_PORT)),
				[pin] "I" (LED_PIN)
				);
				} else {
				// Send bit '0' (HIGH ~0.416us, LOW ~0.833us)
				asm volatile (
				"sbi %[port], %[pin]\n\t"   // HIGH (2 clk)
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"cbi %[port], %[pin]\n\t"   // LOW (2 clk)
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				:
				: [port] "I" (_SFR_IO_ADDR(LED_PORT)),
				[pin] "I" (LED_PIN)
				);
			}
			byte <<= 1;
		}
	}

	sei();

	_delay_us(50);
}

#else

void neopixel_display(void) {
	uint8_t temp[NEOPIXEL_MAX_LEDS * 3];
	for (uint8_t i = 0; i < sizeof(neopixel_rawBuffer); i++) {
		uint16_t scaled = ((uint16_t)neopixel_rawBuffer[i] * neopixel_brightness) >> 8;
		temp[i] = (uint8_t)scaled;
	}
	neopixel_send(temp, sizeof(temp));
}

void neopixel_send(uint8_t *data, uint8_t length) {
	cli();

	for (uint8_t i = 0; i < length; i++) {
		uint8_t byte = data[i];
		for (uint8_t b = 0; b < 8; b++) {
			if (byte & 0x80) {
				// Send bit '1' (HIGH ~0.8us, LOW ~0.45us)
				asm volatile (
				"sbi %[port], %[pin]\n\t"   // HIGH (2 clk)
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"cbi %[port], %[pin]\n\t"   // LOW (2 clk)
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				:
				: [port] "I" (_SFR_IO_ADDR(LED_PORT)),
				[pin] "I" (LED_PIN)
				);
				} else {
				// Send bit '0' (HIGH ~0.4us, LOW ~0.85us)
				asm volatile (
				"sbi %[port], %[pin]\n\t"   // HIGH (2 clk)
				"nop\n\t"                   // 1 clk
				"cbi %[port], %[pin]\n\t"   // LOW (2 clk)
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				"nop\n\t"                   // 1 clk
				:
				: [port] "I" (_SFR_IO_ADDR(LED_PORT)),
				[pin] "I" (LED_PIN)
				);
			}
			byte <<= 1;
		}
	}

	sei();

	_delay_us(50);
}

#endif

void neopixel_init(void) {
	LED_DDR |= (1 << LED_PIN);
	LED_PORT &= ~(1 << LED_PIN);
}

void neopixel_setBrightness(uint8_t brightness) {
	neopixel_brightness = brightness;
}

void neopixel_clear(void) {
	for (uint8_t i = 0; i < sizeof(neopixel_rawBuffer); i++) {
		neopixel_rawBuffer[i] = 0;
	}
}

void neopixel_setPixel(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
	if (index >= NEOPIXEL_MAX_LEDS) return;

	uint8_t i = index * 3;
	neopixel_rawBuffer[i]     = g;
	neopixel_rawBuffer[i + 1] = r;
	neopixel_rawBuffer[i + 2] = b;
}

static void wheel(uint8_t pos, uint8_t *r, uint8_t *g, uint8_t *b) {
	pos = 255 - pos;
	if (pos < 85) {
		*r = 255 - pos * 3;
		*g = 0;
		*b = pos * 3;
	} else if (pos < 170) {
		pos -= 85;
		*r = 0;
		*g = pos * 3;
		*b = 255 - pos * 3;
	} else {
		pos -= 170;
		*r = pos * 3;
		*g = 255 - pos * 3;
		*b = 0;
	}
}

void neopixel_rainbow(uint8_t offset, uint8_t spacing) {
	if (spacing == 0) spacing = 1;

	for (uint8_t i = 0; i < NEOPIXEL_MAX_LEDS; i++) {
		uint8_t r, g, b;

		uint8_t pos = (i * spacing + offset) & 0xFF;
		wheel(pos, &r, &g, &b);
		neopixel_setPixel(i, r, g, b);
	}
}
