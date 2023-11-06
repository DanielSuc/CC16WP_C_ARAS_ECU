#include "sys_manager.h"
#include "stdint.h"
#include "can_handler.h"


void FCT_MainState(uint8_t MainState)
{

    switch(MainState)
{
    case STM_INACTIVE:
        if( clampstatus == INACTIVE)
        {
            FCT_setMainState(STM_INIT);
        }
        break;
    
    case STM_INIT:
        if(clampstatus == ACTIVE)
        {
            FCT_setMainState(STM_INACTIVE);
        }
        break;

    case STM_ACTIVE:
        if( clampstatus == ACTIVE && motorrunning == true)
        {
            FCT_setMainState(STM_ACTIVE);
        }
        break;

    case STM_PASSVE:
        if( clampstatus == ACTIVE && motorrunning == false)
        {
            FCT_setMainState(STM_PASSVE);
        }    
        break;
}

}



/* CODE FROM TEACH
#define STM_INACTIVE 0
#define STM_INIT     1
#define STM_READY    2
#define STM_ACTIVE   3

#define INACTIVE    0
#define ACTIVE      1

#define DISABLED    0
#define ENABLED     1   

uint8_t MainState = STM_INACTIVE;

swtich(aMainState)
{
    case STM_INACTIVE:
        if(aKL15 == ACTIVE)
        {
            FCT_setMainState(STM_INIT);
        }
        break;
    
    case STM_INIT:
        if(aKL15 == INACTIVE)
        {
            FCT_setMainState(STM_INACTIVE);
        }
        else if (aMotorRunning = ACTIVE)
        {
            FCT_setMainState(STM_READY);
        }
        break;
    case STM_READY:
        if(aMotorRUnning == INACTIVE)
        {
            FCT_setMainState(STM_INIT);
        }
        else if(aFuncEnablement == ENABLED)
        {
            FCT_setMainState(STM_ACTIVE);
        }
        break;
    case STM_ACTIVE:

        break;
}

*/