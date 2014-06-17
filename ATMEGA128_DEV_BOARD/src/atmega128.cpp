#include "atmega128.h"

/* ======================================================= */
// Set up a memory regions to access GPIO
void setup_io()
{
	_out(DDB0, DDRB); // CSN
	_out(DDB1, DDRB); // SCK
	_out(DDB2, DDRB); // MOSI
	 _in(DDB3, DDRB); // MISO
	_out(DDB4, DDRB); // CE
} // setup_io

/* ======================================================= */
// Set up SPI interface
void setup_spi()
{
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
} // setup_spi

/* ======================================================= */
void setCSN(uint8_t value)
{
	if (value) {
		_on(SPI_CSN, PORTB);
	} else {
		_off(SPI_CSN, PORTB);
	}
}

/* ======================================================= */
void setCE(uint8_t value)
{
	if (value) {
		_on(SPI_CE, PORTB);
	} else {
		_off(SPI_CE, PORTB);
	}
}

/* ======================================================= */
// SPI transfer
uint8_t transfer_spi(uint8_t tx_)
{
	/* Start transmission */
	SPDR = tx_;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
} // transfer_spi

/* ======================================================= */
void __start_timer()
{
	TCNT1=0x00;
	TCCR1B = _BV(CS12)|_BV(CS10);
}

/* ======================================================= */
uint16_t __millis()
{
	return TCNT1;
}

