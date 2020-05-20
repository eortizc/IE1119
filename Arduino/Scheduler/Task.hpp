#ifndef TASK_HPP_
#define TASK_HPP_
#include "SchedulerDefines.hpp"
#include "Mailbox.hpp"

class Task
{
	public:
		        Task();
		        SchedulerTypes::UInt8   m_u8TaskID;
		virtual SchedulerTypes::ErrorCodes  run(void){return(SchedulerTypes::NO_ERR);};
		virtual SchedulerTypes::ErrorCodes  setup(void){return(SchedulerTypes::NO_ERR);};
		bool    IsTaskFinished(void){return m_bIsFinished;};
                SchedulerTypes::UInt8   GetTaskPriority(void) {return m_u8Priority;};
		void    SetTaskPriority(SchedulerTypes::UInt8 i_u8NewPriority){m_u8Priority = i_u8NewPriority;};
		        st_Message  getMessage(SchedulerTypes::UInt8 i_u8TaskID);
		bool    sendMessage(st_Message i_stMessage);

	private:
	   static   SchedulerTypes::UInt8 m_u8NextTaskID;
	            SchedulerTypes::UInt8 m_u8Priority;
	            Mailbox*  m_pMailbox;
	protected:
	   bool     m_bIsFinished;
};

#endif /* TASK_HPP_ */
