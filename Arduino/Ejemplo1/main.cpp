#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB = (0x01 << 5) | (0x01);
    PORTB = 0x00;

    while(1)
    {
        _delay_ms(500);
        PORTB = 0xFF;
        _delay_ms(500);
        PORTB = 0x00;
    }
}