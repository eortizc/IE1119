/*
 * Mailbox.hpp
 *
 *  Created on: May 1, 2018
 *      Author: eortiz
 */

#ifndef MAILBOX_HPP_
#define MAILBOX_HPP_
#define MAX_MESSAGE_QUEUE 10
#include <avr/io.h>
#include "SchedulerDefines.hpp"

struct st_Message
{
    bool    bMessageValid;   // - True when message is valid
    SchedulerTypes::UInt8   u8DestinationID; // - Destination Task ID
    SchedulerTypes::UInt8   u8SourceID;      // - Source Task ID
    SchedulerTypes::UInt8   u8MessageCode;   // - Message code, interpreted by Destination
    SchedulerTypes::UInt32  u32MessageData;  // - Message data, interpreted by Destination
    SchedulerTypes::UInt8 * pPayload;       // - Message Payload, interpreted by Destination
};

class Mailbox
{
public:
    Mailbox(){};
    static Mailbox* getMailbox();
    bool sendMessage(st_Message i_stMessage);
    bool sendMessage();
    st_Message getMessage(SchedulerTypes::UInt8 i_u8MailboxID);

private:
    static Mailbox* MailObj;
    st_Message m_stMessageQueue[MAX_MESSAGE_QUEUE];
};

#endif /* MAILBOX_HPP_ */
