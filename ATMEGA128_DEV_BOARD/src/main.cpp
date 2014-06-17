/********************************************************************************
Includes
********************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifdef	__cplusplus
extern "C" {
#endif
#include "usart.h"

#ifdef	__cplusplus
}
#endif

#include "RF24.h"

/********************************************************************************
Function Prototypes
********************************************************************************/
void loop();

/********************************************************************************
Global Variables
********************************************************************************/
RF24 radio;
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

/********************************************************************************
Main
********************************************************************************/
int main(void) {
    // initialize code
	usart_init();

    // enable interrupts
    //sei();

	_delay_ms(2000);

    printf("Start NRF24L01P test...");

    radio.begin();
    radio.setRetries(15,15);
    radio.setPayloadSize(8);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(120);

    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);

    radio.startListening();

    radio.printDetails();

	loop();

    // main loop
    while (true) {
    	_delay_ms(1000);
    	printf("Elapsed: %u \n", TCNT1);
    }
}

void loop() {
	radio.stopListening();

	uint8_t data[] = {111, 101};
	bool ok = radio.write(data, 2);

    if (ok)
      printf("ok...\n\r");
    else
      printf("failed.\n\r");
}
