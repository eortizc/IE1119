/*
 * LED.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef LED_HPP_
#define LED_HPP_

#include "Task.hpp"


class LED : public Task
{
    public:
        LED(SchedulerTypes::UInt8);
        virtual SchedulerTypes::ErrorCodes run(void);
        virtual SchedulerTypes::ErrorCodes setup(void);
    protected:
        SchedulerTypes::UInt8 m_u8Pin;

    private:
};

#endif /* LED_HPP_ */
