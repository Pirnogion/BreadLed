#include "BreadLed.h"

BreadLed::BreadLed(uint8_t pin) : pin(pin)
{
	// Nothing
}

void BreadLed::send(uint8_t green, uint8_t red, uint8_t blue)
{
	asm volatile(
		"cli\n"

		"ldi r20, 0\n"

		"ldi r18, 8\n"
		"mov r19, %[GREEN_CHANNEL]\n"
		"rjmp send_byte_loop_%=\n"

		"send_red_channel_%=: ldi r18, 8\n"
		"mov r19, %[RED_CHANNEL]\n"
		"rjmp send_byte_loop_%=\n"

		"send_blue_channel_%=: ldi r18, 8\n"
		"mov r19, %[BLUE_CHANNEL]\n"
		"rjmp send_byte_loop_%=\n"

		"send_byte_loop_%=:\n"
		"lsl r19\n"
		"brcc zero_bit_%=\n"
		"brcs one_bit_%=\n"
		"bit_ret_%=: cbi %[PORT], 2\n"
		"dec r18\n"
		"brne send_byte_loop_%=\n"

		"inc r20\n"

		"cpi r20, 1\n"
		"breq send_red_channel_%=\n"

		"cpi r20, 2\n"
		"breq send_blue_channel_%=\n"

		"rjmp end_%=\n"

		"zero_bit_%=: sbi %[PORT], 2\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"cbi %[PORT], 2\n"
		"nop\n"
		"nop\n"
		"rjmp bit_ret_%=\n"

		"one_bit_%=: sbi %[PORT], 2\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"nop\n"
		"rjmp bit_ret_%=\n"

		"end_%=: sei\n"
		:
		: [PORT]"I"(_SFR_IO_ADDR(PORTD)), [GREEN_CHANNEL]"r"(green), [RED_CHANNEL]"r"(red), [BLUE_CHANNEL]"r"(blue)
		: "r18", "r19", "r20", "cc", "memory"
	);
}