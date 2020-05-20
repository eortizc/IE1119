#include "Scheduler.hpp"

// - Scheduler constructor
Scheduler::Scheduler()
{
    m_u8OpenSlots = static_cast<SchedulerTypes::UInt8>(NUMBER_OF_SLOTS);
    m_u8NextSlot = 0;
    m_pMailbox = Mailbox::getMailbox();
    for(SchedulerTypes::UInt8 l_u8index = 0; l_u8index < NUMBER_OF_SLOTS; l_u8index++)
    {
        m_aSchedule[l_u8index].pTask = 0; // Init to an invalid pointer
    }
}

// - The attach function, inserts the task into the schedule slots.
SchedulerTypes::ErrorCodes Scheduler::attach(Task * i_pTask, TaskType i_enTaskType, TaskActive i_enTaskIsActive,
                                        SchedulerTypes::UInt64 i_u64TickInterval)
{
    SchedulerTypes::ErrorCodes l_ErrorCode = SchedulerTypes::NO_ERR;
    st_TaskInfo l_stTaskInfo;

    l_stTaskInfo.pTask = i_pTask;
    l_stTaskInfo.bTaskIsActive = i_enTaskIsActive;
    l_stTaskInfo.u64Ticks = this->m_u64ticks;
    l_stTaskInfo.u64TickInterval = 0;
	l_stTaskInfo.u64TickIntervalInitValue = i_u64TickInterval;
	l_stTaskInfo.enTaskType = i_enTaskType;

    if((m_u8OpenSlots>0) && (m_u8NextSlot < NUMBER_OF_SLOTS))
    {
        m_aSchedule[m_u8NextSlot] =  l_stTaskInfo;
        m_u8OpenSlots--;
        m_u8NextSlot++;
    }
    else
    {
        l_ErrorCode = SchedulerTypes::NO_ERR;
    }
    return l_ErrorCode;
}

// - Execute the current schedule
SchedulerTypes::ErrorCodes Scheduler::run(void)
{
    SchedulerTypes::UInt8 l_u8NextSlot = 0U;
    Task * l_pNextTask = 0;
    SchedulerTypes::ErrorCodes l_u8ReturnCode = SchedulerTypes::NO_ERR;

    while(l_u8NextSlot < NUMBER_OF_SLOTS)
    {
        l_pNextTask = static_cast<Task *> (m_aSchedule[l_u8NextSlot].pTask);
        if(l_pNextTask != 0)
        {
            if(m_aSchedule[l_u8NextSlot].bTaskIsActive)
            {
                // - Execute the task slot
                if(m_aSchedule[l_u8NextSlot].u64TickInterval == 0)
                {
                    l_pNextTask->run();
                }

                // - Depending on the task type, handle the tick count
                switch(m_aSchedule[l_u8NextSlot].enTaskType)
                {
                    case(TaskType_OneShot):
                        m_aSchedule[l_u8NextSlot].bTaskIsActive = TaskActiveFalse;
                        // - Intentional fall-through
                    case(TaskType_Always):
                        m_aSchedule[l_u8NextSlot].u64TickInterval = 0;
                        break;
                    case(TaskType_Periodic):
                        m_aSchedule[l_u8NextSlot].u64TickInterval ++;
                        if(m_aSchedule[l_u8NextSlot].u64TickInterval > m_aSchedule[l_u8NextSlot].u64TickIntervalInitValue)
                        {
                            m_aSchedule[l_u8NextSlot].u64TickInterval = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            // - If we found an uninitialized slot, break from the execution loop
            break;
        }
		l_u8NextSlot++;
    }
    //CalculateNextSchedule(); // TODO

    return l_u8ReturnCode;
}
// - Execute the setup function for all tasks
SchedulerTypes::ErrorCodes Scheduler::setup(void)
{
    SchedulerTypes::UInt8 l_iNextTaskSlot = 0U;
    Task * l_pNextTask = 0;
    SchedulerTypes::ErrorCodes l_u8ReturnCode = SchedulerTypes::NO_ERR;
    // - Run the setup function for all available tasks.
    while(l_iNextTaskSlot < NUMBER_OF_SLOTS)
    {
        l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pTask);
        if(l_pNextTask != 0)
        {
            l_pNextTask->setup();
        }
        l_iNextTaskSlot++;
    }
    return l_u8ReturnCode;
}

SchedulerTypes::ErrorCodes Scheduler::CalculateNextSchedule(void)
{
    //TODO
    return(SchedulerTypes::NO_ERR);
}

SchedulerTypes::ErrorCodes Scheduler::SortScheduleByPriority(Task * i_pSchedule)
{
    //TODO
    return(SchedulerTypes::NO_ERR);
}

// *****************************
//          SLEEP
// *****************************
// - Sets the CPU to sleep while
// waiting for an interrupt
//
// *****************************
//         PORT_ME
// *****************************
void Scheduler::Sleep()
{
   sleep_enable();
}
