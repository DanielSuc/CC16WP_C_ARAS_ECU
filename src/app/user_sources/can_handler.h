#ifndef __CAN_HANDLER_H_
#define __CAN_HANDLER_H_

/*----------------------------------------------------------------------------*/
/**
*   @file         can_handler.h
*   @brief        CAN Handler header. 
*/

/** @addtogroup STM
 *  @{
 */
/*----------------------------------------------------------------------------*/
/* - - - - - - VARIABLES - - - - - - */
/**
*   @name Variables CAN Handler
*   Variables used by CAN Handler.
*/
bool SW_KL15 = 0;   /*!< Software variable of KL15 state. */

/* - - - - - - FUNCTIONS - - - - - - */
/**
*   @name Functions CAN Handler
*   Functions used by CAN handler. 
*/
/**
*    @brief      Setter for KL15 State from CAN message.
*/
void get_rx_msg(bios_can_msg_typ* rx_msg);
/**
*    @brief      Getter for KL15 state 
*             
*    @return     Returns KL15 state.
*/
bool getValueKL15();


#endif
