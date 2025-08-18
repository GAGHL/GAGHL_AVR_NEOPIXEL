/*
 * CONFIG.h
 *
 * Created: 8/18/2025 12:48:57 PM
 *  Author: GAGHL
 */ 


#ifndef GAGHL_AVR_NEOPIXEL_CONFIG_H_
#define GAGHL_AVR_NEOPIXEL_CONFIG_H_

#define F_CPU 9600000UL

#ifndef F_CPU
	#if defined(__AVR_ATtiny13__) || defined(__AVR_ATtiny13A__)
		#define F_CPU 9600000UL
	#else // If MCU is not ATtiny13 or ATtiny13A
		#define F_CPU 8000000UL
	#endif
	#warning "F_CPU is not defined! Default value will be used."
#endif

#endif /* GAGHL_AVR_NEOPIXEL_CONFIG_H_ */