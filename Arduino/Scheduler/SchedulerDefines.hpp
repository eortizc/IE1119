//
// Created by eortiz on 19/5/20.
//
///*************************
///          PORT_ME
///*************************
#include "avr/io.h"
///*************************

#ifndef ARDUINO_SCHEDULERDEFINES_H
#define ARDUINO_SCHEDULERDEFINES_H
namespace SchedulerTypes
{
    typedef uint8_t UInt8;
    typedef uint16_t UInt16;
    typedef uint32_t UInt32;
    typedef uint64_t UInt64;

    enum ErrorCodes {NO_ERR = 0, RET_ERR};
}
#endif //ARDUINO_SCHEDULERDEFINES_H
