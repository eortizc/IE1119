#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int32_t INT_Counter = 0;
int main() {
    cli();
    DDRB = 0x01 << 5;
    TCCR0B = 2;
    TIMSK0 = 1;
    PORTB = 0x00;
    sei();
    while(1)
    {
    }
    return 0;
}

ISR(TIMER0_OVF_vect)
{
    if (INT_Counter < 3906)
    {
        INT_Counter++;
    }
    else {
        INT_Counter = 0;
        if (PORTB == 0x00)
        {
            PORTB = 0xFF;
        } else{
            PORTB = 0x00;
        };
    }
}
