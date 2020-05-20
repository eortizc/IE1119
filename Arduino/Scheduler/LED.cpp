#include "LED.hpp"

LED::LED(SchedulerTypes::UInt8 i_u8Pin)
{
	m_u8Pin = i_u8Pin;
}

SchedulerTypes::ErrorCodes LED::run()
{
    // - Toggle the pin, assuming PORTB
    PORTB = PORTB ^ (0x01 << m_u8Pin);
    return(SchedulerTypes::NO_ERR);
}

SchedulerTypes::ErrorCodes LED::setup()
{
    // ****************************
    //         PORT CONFIG
    // ****************************
    // - Set the correct direction
    // for the pin
    DDRB = DDRB | (0x01 << m_u8Pin);
    // - Init the pin to 0
    PORTB = PORTB & (~(0x01 << m_u8Pin));

    return(SchedulerTypes::NO_ERR);
}

