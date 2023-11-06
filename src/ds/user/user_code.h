#ifndef _USER_CODE_H_
#define _USER_CODE_H_
/*----------------------------------------------------------------------------*/
/**
* \file         user_code.h
* \brief        User code function header
* \date         20181001
*
*/
/*----------------------------------------------------------------------------*/
/**
* \defgroup
* \brief
* \details
*/
/*----------------------------------------------------------------------------*/

#include "graph_support.h"

#define SET_CALLBACK_1MS_TIMER
#define SET_CALLBACK_CAN_MESSAGE_RECEIVE

//Use SET_CAN_RETRANSMISSION_ENABLE to enable frame retransmission in case of CAN Error, all other SET_CAN_RETRANSMISSION options must be commented out!
//Use SET_CAN_RETRANSMISSION_DISABLE to disable frame retransmission in case of CAN Error, all other SET_CAN_RETRANSMISSION options must be commented out!
//Use SET_CAN_RETRANSMISSION_RETRY to specify a number of wanted retries in case of CAN Error, all other SET_CAN_RETRANSMISSION options must be commented out!
//#define SET_CAN_RETRANSMISSION_ENABLE
#define SET_CAN_RETRANSMISSION_DISABLE
//#define SET_CAN_RETRANSMISSION_RETRY 20 //change the number according to wanted number of retries in application, never leave it empty


#define CAN_BL_BAUDRATE_MODE 0  //0 = default, application writes baudrate to EEPROM from can_db_tables and initialises the bootloader CAN with the same baudrate
                                //1 = application reads baudrate from EEPROM and (re)initialise after reboot

// Comment out SET_SCI_CONTINUOUS_RECEPTION if using user_uart_receive_buffer function (non-blocking)
// In case it's commented out, use user_sci_rx_full_callback instead of user_sci_continuous_receive_callback
// At the end of the transfer user_sci_transfer_complete_callback is called
#define SET_SCI_CONTINUOUS_RECEPTION
// if continuous transmission feature is enabled, buffer data is constantly sent on SCI
//#define SET_SCI_CONTINUOUS_TRANSMISSION


// Define the threshold levels for hysteresis of the digital input emulation of the analog inputs. 
// Hysteresis is used to switch digital states. When the input voltage reaches the high voltage threshold (default set to 6V),
// it is set to digital "1". It remains in that state until the voltage drops to the low voltage threshold (default set to 4V).
// Then it is set to digital "0" and remains in that state until the voltage reaches 6V or higher.
// The value of DI_EMULATION_THRESHOLD_HIGH and DI_EMULATION_THRESHOLD_LOW is referencing to mV levels.
// Input voltage >= 6000u digital "1" (6V)
// Input voltage <= 4000u digital "0" (4V)
//#define DI_EMULATION_THRESHOLD_HIGH 6000u  //unit: mV
//#define DI_EMULATION_THRESHOLD_LOW 4000u   //unit: mV


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    This function is called prior to the main-loop. The user can place his
*           own initializations here.
* \details
*
* \pre
*
* \return   void
*/
void usercode_init(void);


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    This function is called periodically in the main function. The user
*           can place his application here.
* \details
*
* \pre      none
*
* \return   void
*/
void usercode(void);


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    Receive a message from CAN bus
*
* \details
*
* \pre      none
*
* \return   void
*/
void user_can_receive_msg_callback(uint8_t bus_id, bios_can_msg_typ* msg);


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    Receive a message from SCI bus
*
* \details  Rx Transfer completed callback (called for each byte received)
*
* \pre      none
*
* \return   void
*/
void user_sci_continuous_receive_callback(uint8_t instance, uint8_t data);
#define user_int_rx_sci(instance, data) user_sci_continuous_receive_callback(instance, data)


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    Full message received on SCI bus
*
* \details  RX Transfer completed callback (called for each full message received)
*
* \pre      none
*
* \return   void
*/
void user_sci_rx_full_callback(uint8_t instance);


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    TX Empty event on SCI bus (each byte)
*
* \details
*
* \pre      none
*
* \return   void
*/
void user_sci_continuous_transmit_callback(uint8_t instance, uint8_t *buff);


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    TX Empty event on SCI bus
*
* \details
*
* \pre      none
*
* \return   void
*/
void user_sci_tx_empty_callback(uint8_t instance);


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    Transfer Complete Event on SCI bus
*
* \details
*
* \pre      none
*
* \return   void
*/
void user_sci_transfer_complete_callback(uint8_t instance);


/*----------------------------------------------------------------------------*/
/**
* \ingroup  usercode
* \brief    Interrupt each 1ms
*
* \details
*
* \pre      none
*
* \return   void
*/
void user_int_timer_1ms(void);


#endif
