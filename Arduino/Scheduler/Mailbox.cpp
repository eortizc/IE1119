/*
 * Mailbox.cpp
 *
 *  Created on: May 1, 2018
 *      Author: eortiz
 */

#include "Mailbox.hpp"
#include <avr/io.h>
Mailbox g_Mailbox;
Mailbox* Mailbox::MailObj = &g_Mailbox;

extern "C"
{
    Mailbox* Mailbox::getMailbox()
    {
        if(MailObj == 0)
        {
            while(1){};
        }

        return MailObj;
    }

    st_Message Mailbox::getMessage(uint8_t i_u8MailboxID)
    {
        st_Message l_stMessage;

        l_stMessage = m_stMessageQueue[i_u8MailboxID];

        return(l_stMessage);
    }

    bool Mailbox::sendMessage(st_Message i_stMessage)
    {
        if(m_stMessageQueue[i_stMessage.u8DestinationID].bMessageValid == false)
        {
            m_stMessageQueue[i_stMessage.u8DestinationID] = i_stMessage;
            return(true);
        }
        else
        {
            return(false);
        }
    }
    bool Mailbox::sendMessage()
    {
        return true;
    }
}


