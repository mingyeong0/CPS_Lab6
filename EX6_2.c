// EX 6_2

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void SPI_MasterInit() {
	DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2);  // MOSI(PB3), SCK(PB5), SS(PB2) 

	PORTB |= (1 << PB2);  // SS HIGH idle

	// SPI Enable, Master, Mode 3 (CPOL=1, CPHA=1)
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA);

	SPCR |= (1 << SPR0);  // Speed = Fosc/16 → SPR0 = 1
}

void SPI_MasterTransmit(uint8_t data) {
	PORTB &= ~(1 << PB2);   // SS LOW

	SPDR = data;
	while (!(SPSR & (1 << SPIF)));

	PORTB |= (1 << PB2);    // SS HIGH
}

int main(void) {
	SPI_MasterInit();

	while (1) {
		SPI_MasterTransmit(0xAA);  // test data
		_delay_ms(500);
	}
}
