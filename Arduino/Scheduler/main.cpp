#include <avr/io.h>
#include "main.hpp"
#include "Scheduler.hpp"
#include "SchedulerDefines.hpp"
#include "Mailbox.hpp"
#include "Task.hpp"
#include "LED.hpp"
#include "avr/interrupt.h"

// ##########################
// Global/Static declarations
// ##########################
uint8_t Task::m_u8NextTaskID = 0; // - Init task ID
volatile static SchedulerTypes::UInt64 g_SystemTicks = 0; // - The system counter.
Scheduler g_MainScheduler; // - Instantiate a Scheduler
SchedulerTypes::UInt32 INT_Counter = 0;
Mailbox g_MailBox; //TODO - Not being used yet

// #########################
//          MAIN
// #########################
int main(void)
{
    // - Instantiate two new Tasks
    LED OnBoardLED(5);
    LED RedLED(0);
    // - Run the overall setup function for the system
    Setup();
    // - Attach the Tasks to the Scheduler;
    g_MainScheduler.attach(&OnBoardLED,TaskType_Periodic, TaskActiveTrue,1000);
    g_MainScheduler.attach(&RedLED, TaskType_Periodic,TaskActiveFalse,500);
    // - Run the Setup for the scheduler and all tasks
    g_MainScheduler.setup();
    // - Main Loop
    while(1)
    {
    	g_MainScheduler.Sleep();
        if(g_SystemTicks != g_MainScheduler.m_u64ticks)
        {
            //- Only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64ticks = g_SystemTicks;
            g_MainScheduler.run();
        }
    }
    return 0;
}

// **********************************
// Setup function for the application
// @input - none
// @output - none
// **********************************
void Setup(void)
{
	// ****************************
	//         DEVICE CONFIG
	// ****************************
	// N/A

	// ****************************
	//       TIMER CONFIG
	// ****************************
	// - Disable interrupts
	cli();
	// - Configure Timer0 with
	// Division by 8, enable the
	// interrupt
	TCCR0B = CLK_DIVIDER_BY_8;
	TIMSK0 = T0_OVRF_IE;
	// - Re-enable interrupts
	sei();
}

ISR(TIMER0_OVF_vect)
{
    // - Disable System interrupts
    cli();
    // - Scale the interrupt for 1ms Tick
    if (INT_Counter < 4)
    {
        INT_Counter++;
    }
    else
    {
        // - Advance the global tick
        g_SystemTicks++;
        INT_Counter = 0;
    }
    sei();

}


