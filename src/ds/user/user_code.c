/*----------------------------------------------------------------------------*/
/**
 * \file         user_code.c
 * \brief        User code function implementation
 * \details
 * \date         20181001
 *
 */
/*----------------------------------------------------------------------------*/
#include "user_code.h"
#include "sys_manager.h"
#include "can_handler.h"

uint16_t timer;
uint8_t timer_100ms = 100;

//Messages definition
#define msgClampStatus = 0x42A
#define msgARAS_01 	   = 0x151

/*----------------------------------------------------------------------------*/
/**
 * \internal
 *
 * \endinternal
 *
 *
 * \test STATUS: *** UNTESTED ***
 */

void usercode_init(void)
{
    // User defined initializations
    // write app name and version to EEPROM (defined in dsl_cfg.h via Applics Studio)
    user_eeprom_write_app_info((const uint8_t*)APPL_MODULE_NAME, (const uint8_t*)APPL_SW_VERSION);
	//user_can_send_msg(CAN_BUS_0, 0x700, STANDARD_ID, 8, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);
	//user_can_send_msg(CAN_BUS_0, 0x701, STANDARD_ID, 8, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);

}


/*----------------------------------------------------------------------------*/
/**
* This user code function is cyclically called from the main loop.
* Use it to write your program in C code.
* For examples refer to usercode_example(void) below and
* see section on C Programming at https://applics.dev/3_C_Programming/User_API/Documentation.html for more information.
*
 */
void usercode(void)
{
	if (clampstatus == true)
	{

	if (timer >= timer_100ms)
	{
	user_can_send_msg(CAN_BUS_0, msgARAS_01, STANDARD_ID, 8, 0x11, MainState >> 4, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55);
	timer = 0;
	}
	else {
		//nothing
	}
	}
	else {
		//nothing
	}

    // User code here
	// Refer to examples bellow and https://applics.dev/3_C_Programming/User_API/Documentation.html for API documentation
}

/*----------------------------------------------------------------------------*/
/**
//
//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   DIGITAL INPUT AND OUTPUT     #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//  Procedure       void user_io_set_do(uint16_t pin, uint8_t state);
//
//	Overview		set digital output pin
//
//	Input			pin			                 - enum_pwm_pin_name 	inside io_tables.h
//					state		                 - uint8_t 				set pin state
//	Output			void

  	Example:		enable vref and set it to 8.5Volt
  	                user_io_set_do(DO_VREF_EN, 1);
  	                user_io_set_do(DCDC_8V5,   1);

// Vref is configured by default as 5V
// The eight output pins of the CC16WP are configured by default as PWM.
// If you use user_io_set_do (..), pwm duty of the corresponding output is set to 100%.

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t user_io_readback_do(pin)
//
//	Overview		readback state of digital output pin
//
//	Input			pin			                 - enum_pwm_pin_name 	inside io_tables.h
//  Output          uint8_t                      - Value of the digital output pin

	Example:		uint8_t check_state_vref;
					check_state_vref = user_io_readback_do(DO_VREF_EN);

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t user_io_get_di(uint16_t pin);
//
//	Overview		get state of digital input pin
//
//	Input			pin			                 - enum_pin_name 		inside io_tables.h
//  Output          uint8_t                      - Return code,  0 = success

	Example:		uint8_t get_di_input;
					get_di_input = user_io_get_di(DI_KL15);

//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   ANALOG INPUT                 #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint16_t user_ai_get_digits(enum_adc_pin_name pin);
//
//	Overview		get value in digits of analog input
//
//	Input			pin			                 - enum_adc_pin_name 		inside io_tables.h
//  Output          uint16_t                     - Value of the analog input in digits

	Example:		uint16_t get_in0_value;
	                get_in0_value = user_ai_get_digits(AI_A_IN0);

// In order to be able to read out the voltage values of KL30_1 and KL30_2, you must first set DO_POWER.
// The measuring range does not have to be set for this.

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint16_t user_ai_get_mv(enum_adc_pin_name pin);
//
//  Overview        get the scaled value in mV/mA of the analog input.
//
//  Input           pin                          - enum_adc_pin_name 		inside io_tables.h
//  Output          uint16_t                     - Value of the analog input in mV

    Example:        uint16_t get_in0_value;
                    get_in0_value = user_ai_get_mv(AI_A_IN0);

// In order to be able to read out the voltage values of KL30_1 and KL30_2, you must first set DO_POWER.
// The measuring range does not have to be set for this.

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint16_t user_ai_get_cal(enum_adc_pin_name pin);
//
//  Overview        get the scaled and calibrated value in mV/mA of the analog input.
//					Note: Calibrated channels are only available on selected modules.
//
//  Input           pin                          - enum_adc_pin_name 		inside io_tables.h
//  Output          uint16_t                     - Value of the analog input in mV

    Example:        uint16_t get_in0_value;
                    get_in0_value = user_ai_get_cal(AI_INA_OUT0);

// In order to be able to read out the voltage values of KL30_1 and KL30_2, you must first set DO_POWER.
// The measuring range does not have to be set for this.

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint16_t user_ai_get_filtered(enum_adc_pin_name pin);
//
//  Overview        get the filtered value in mV/mA of the analog input.
//                  The amount of filter values is defined inside modulehardwarecode.h with the AD_FILTER define.
//                  !!! can currently only be used with the outputs AI_INA_OUTx !!!
//
//  Input           pin                          - enum_adc_pin_name 		inside io_tables.h
//  Output          uint16_t                     - Value of the analog input in mV

    Example:        uint16_t get_in0_value;
                    get_in0_value = user_ai_get_filtered(AI_INA_OUT0);

// In order to be able to read out the voltage values of KL30_1 and KL30_2, you must first set DO_POWER.
// The measuring range does not have to be set for this.

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       void modulhardwarecode_adc_set_measurement_range(enum_adc_pin_name pin, uint8_t range);
//
//  Overview        adjust the measuring range for analog inputs, between 16V and 32V (only for supported AI pins on supported HW)
//
//  Input           pin                          - enum_adc_pin_name  	inside io_tables.h
//                  range                        - uint8_t 				AI_RANGE_16V for 16V range (default)
//                                                   					AI_RANGE_32V for 32V range

//  Output          void

    Example:        modulhardwarecode_adc_set_measurement_range(AI_A_IN0, AI_RANGE_32V);   // adjust measurement range of analog input 0 to 32 volt


//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   CAN-BUS                      #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       enum_HAL_CAN_RETURN_VALUE user_can_send_msg(uint8_t can_bus, uint32_t can_id, enum_CAN_ID_TYPE id_type, uint8_t can_dlc, uint8_t data_byte_0, uint8_t data_byte_1, uint8_t data_byte_2, uint8_t data_byte_3, uint8_t data_byte_4, uint8_t data_byte_5, uint8_t data_byte_6, uint8_t data_byte_7);
//
//  Overview        send can message
//
//  Input           can_bus                     - uint8_t  				CAN bus ID
//                  can_id                      - uint32_t            	CAN ID
//                  id_type                     - enum_CAN_ID_TYPE    	CAN ID type, STANDARD_ID or EXTENDED_ID
//                  can_dlc                     - uint8_t 				data length (1 - 8)
//                  data_byte_0 - data_byte_7   - uint8_t				data of the message   0x12, ...
//  Output          enum_HAL_CAN_RETURN_VALUE   - Return code, 0 = success
                                                 	 	 	   1 = general error
                                                 	 	 	   15 = wrong dlc
                                                 	 	 	   8 = write error (fifo full)

    Example:        user_can_send_msg(CAN_BUS_0, 0x123, STANDARD_ID, 8, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       enum_HAL_CAN_RETURN_VALUE user_can_send_msg_buffer(uint8_t can_bus, uint32_t can_id, enum_CAN_ID_TYPE id_type, uint8_t can_dlc, uint8_t *const data_buffer);
//
//  Overview        send can buffer
//
//  Input           can_bus                     - uint8_t  				CAN bus ID
//                  can_id                      - uint32_t            	CAN ID
//                  id_type                     - enum_CAN_ID_TYPE    	CAN ID type, STANDARD_ID or EXTENDED_ID
//                  can_dlc                     - uint8_t 				CAN Data Length Code, Number of bytes in the data field
//                 	data_buffer                 - uint8_t *const      	Data buffer to be transmitted
//  Output          enum_HAL_CAN_RETURN_VALUE   - Return code, 0 = success
                                                 	 	 	   1 = general error
                                                 	 	 	   15 = wrong dlc
                                                 	 	 	   8 = write error (fifo full)
    Example:        uint16_t can_tx_msg = 0xAABB;
                    user_can_send_msg_buffer(CAN_BUS_0, 0x123, STANDARD_ID, 2, &can_tx_msg);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       enum_HAL_CAN_RETURN_VALUE user_can_fd_msg_buffer_send(uint8_t can_bus, uint32_t can_id, enum_CAN_ID_TYPE id_type, uint8_t can_dlc, uint8_t can_fd_brs, uint8_t *const data_buffer);
//
//  Overview        send can buffer for can-fd up to dlc 15
//
//  Input           can_bus                     - uint8_t  				CAN bus ID
//                  can_id                      - uint32_t            	CAN ID
//                  id_type                     - enum_CAN_ID_TYPE    	CAN ID type, STANDARD_ID or EXTENDED_ID
//                  can_dlc                     - CAN-FD DLC (0-15)   	set to 	    1 - 8   for 	1 - 8 	bytes data length
//																		            9 		for 	12 		bytes data length
//																		            10 		for 	16 		bytes data length
//																		            11 		for 	20 		bytes data length
//																		            12 		for 	24 		bytes data length
//																		            13 		for 	32 		bytes data length
//																		            14 		for 	48 		bytes data length
//																		            15 		for 	64 		bytes data length
//                  data_buffer                 -   uint8_t *const      	Data buffer to be transmitted
//  Output          enum_HAL_CAN_RETURN_VALUE   - Return code, 0 = success
                                                 	 	 	   1 = general error
                                                 	 	 	   15 = wrong dlc
                                                 	 	 	   8 = write error (fifo full)

    Example:        uint8_t data_buffer[12] = {aa};
                    uint32_t dlc = 10;               // DLC != length in bytes
                    uint8_t brs = 0;                 // BRS flag disabled, if BRS is enabled the faster data baudrate will be used

                    // Will always send CAN FD messages depending on the length of DLC.
                    user_can_fd_msg_buffer_send(CAN_BUS_0, 0x123, STANDARD_ID, dlc, brs, data_buffer);

//---------------------------------------------------------------------------------------------------------------------
// Procedure        void user_can_get_error(uint8_t can_bus, struct_error_watermark *watermark);
//
//  Overview        returning the latest can error with timestamp in ms since start of the device
//
//  Input           can_bus                     - uint8_t  			       CAN bus ID
//					*watermark  				- struct_error_watermark   pointer to watermark structure
//  Output          void

    Example:        struct_error_watermark watermark_can_1;
                    user_can_get_error(0, &watermark_can_1);


//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   CAN DB                       #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       void user_can_db_clear_rx_buff();
//
//  Overview        get messages in the CAN RX fifo and process them
//
//  Input           void
//  Output          void

    Example:        user_can_db_clear_rx_buff();

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       void user_can_db_set_signal_value(uint32_t id, uint32_t value_int);
//
//  Overview        set can datapoint value
//
//  Input           id                           - const uint32_t		CAN Datapoint ID from can_db_tables.h
//                  value_int                    - uint32_t				Data value to be transmitted
//  Output          void

    Example:        uint32_t get_in0_value;
                    user_can_db_set_signal_value(MY_CAN_DP_0, get_in0_value);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_can_db_get_signal_value(uint32_t id)
//
//  Overview        get the can datapoint value
//
//  Input           id                           - const uint32_t		CAN Datapoint ID from can_db_tables.h
//  Output          uint32_t                     - datapoint value

    Example:        uint32_t my_can_dp_0;
                    my_can_dp_0 = user_can_db_get_signal_value(MY_CAN_DP_0);

//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_block_received(const uint32_t can_block_id, const uint8_t reset);
//
//  Overview        See if a CAN DB block was received and reset the associated flag
//
//  Input           can_block_id                 - const uint32_t		name of the defined CAN DB block
//                  reset                        - const uint8_t		reset = 1, do not reset = 0
//  Output          uint8_t                      - Return code, 0 no message received
//                                                              1 message received


    Example:        uint8_t message_received = 0;
                    message_received = user_can_db_block_received(MY_CAN_BLOCK_0, 1);
                    if(message_received)
                        // do something

//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_test_dp_value(const uint32_t can_dp_id);
//
//  Overview        Set the transmission flag for the given CAN DB datapoint, to manually send a configured datapoint.
//					Associated CAN block must be configured to transmit.
//
//  Input           can_dp_id                   - const uint32_t		CAN Datapoint ID from can_db_tables.h
//  Output          uint8_t                     - Return code, 0 no message received
//                                                  		   1 message received, datapoint has same value
//                                                  		   2 message received, datapoint has another value

    Example:        uint8_t received = 0;
    				received = user_can_db_test_dp_value(MY_CAN_DP_0);

//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_block_expired(uint8_t block_id);
//
//  Overview        Check if the CAN block has expired based on its timeout.
//
//  Input           block_id                     - uint8_t         ID of the CAN block
//  Output          uint8_t                      - Return code, 0 if the block has not expired
//                                                             	1 if the block has expired
//
//  Example:        uint8_t expired = 0;
//                  expired = user_can_db_block_expired(MY_CAN_BLOCK_0);
//
//  Note:            This function should be used with the timeout and failsafe value feature enabled.
//---------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_datapoint_expired(uint8_t dp_id);
//
//  Overview        Check if the CAN datapoint within the block has expired based on its block timeout.
//
//  Input           dp_id                        - uint8_t         ID of the CAN datapoint
//  Output          uint8_t                      - Return code,	0 if the datapoint has not expired
//                                                           	1 if the datapoint has expired
//
//  Example:        uint8_t expired = 0;
//                  expired = user_can_db_datapoint_expired(MY_CAN_DP_0);
//
//  Note:            This function should be used with the timeout and failsafe value feature enabled.
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// Procedure        void user_can_db_send_dp(const uint32_t can_dp_id);             or
//                  void user_can_db_set_transmit_flag(const uint32_t can_dp_id);
//
//  Overview        Set the transmission flag for the given CAN DB datapoint, to manually send a configured datapoint. Associated CAN block must be configured to transmit.
//                  *Note*: This function was renamed from user_can_db_set_transmit_flag(...) to user_can_db_send_dp(...)
//
//  Input           can_dp_id                    - const uint32_t      	CAN Datapoint ID from can_db_tables.h
//  Output          void

    Example:        user_can_db_send_dp(MY_CAN_DP_0);

//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_get_value_on_change(const uint32_t can_dp_id, uint32_t* const buffer_dp_value);
//
//  Overview        return the value of the given datapoint only when its value is changed. If the datapoint doesn't change, the current value will be returned
//
//  Input           can_dp_id                    - const uint32_t     	CAN Datapoint ID from can_db_tables.h
//                  buffer_dp_value              - const uint32_t*    	buffer in which the datapoint value will be saved in.
//  Output          uint8_t                      - Return code, 0 value didn't change, 1 value changed

    Example:        uint8_t changed_value = 0;
                    uint32_t value_MY_CAN_DP_0 = 0;
                    changed_value = user_can_db_get_value_on_change(MY_CAN_DP_0, &value_MY_CAN_DP_0);
                    if (changed_value)
                        // do something

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint8_t user_can_db_stop_transmission(const uint8_t can_bus, const uint8_t status);
//
//  Overview        stopping or starting can_db transmission for a specific CAN bus
//
//  Input           can_bus                      - const uint8_t     	CAN bus nr.
//                  status                       - const uint8_t     	stop = 1, start = 0
//  Output          uint8_t                      - Return code, 0 = success
//                                                              1 = error

    Example:        user_can_db_stop_transmission(0,1);

//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_transmit_deactivate(const uint8_t status);
//
//  Overview        stopping or starting can_db transmission for a all CAN bus
//
//  Input           status                       - const uint8_t		stop = 1, start = 0
//  Output          uint8_t                      - Return code, 0 = success
//                                                              1 = error

    Example:        user_can_db_transmit_deactivate(1);

//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_stop_gateway_for_known_ids(const uint8_t can_bus, const uint8_t status);
//
//  Overview        stopping or starting can_db gateway for known ids for a specific CAN bus
//
//  Input           can_bus                      - const uint8_t		CAN bus nr.
//                  status                       - const uint8_t		stop = 1, start = 0
//  Output          uint8_t                      - Return code, 0 = success
//                                                              1 = error

    Example:        user_can_db_stop_gateway_for_known_ids(0,1);

//---------------------------------------------------------------------------------------------------------------------
// Procedure        uint8_t user_can_db_stop_gateway_for_unknown_ids(const uint8_t can_bus, const uint8_t status);
//
//  Overview        stopping or starting can_db gateway for unknown ids for a specific CAN bus
//
//  Input           can_bus                      - const uint8_t		CAN bus nr.
//                  status                       - const uint8_t		stop = 1, start = 0
//  Output          uint8_t                      - Return code, 0 = success
//                                                              1 = error

    Example:        user_can_db_stop_gateway_for_unknown_ids(0,1);


//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   PWM                          #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint32_t user_pwm_set_pwm(uint16_t pin, uint16_t freq, uint16_t duty);
//
//	Overview		setting a pwm
//
//	Input			pin                          - uint16_t				enum_pwm_pin_name inside io_tables.h
//					freq	                     - uint16_t				10Hz to 1000Hz
//					duty 	                     - uint16_t				0 - 1000 (0 - 100.0%)
//  Output          uint32_t                     - 0 = success

	Example:		uint32_t ret = user_pwm_set_pwm(PWM_HSD1_OUT0, 250, 500);

// Duty cycle is adjustable for each output
// Frequency is restricted to the related timer channel

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint32_t user_pwm_set_dither(uint16_t pin, uint16_t duty, uint16_t freq, uint16_t dither_duty, uint16_t dither_freq);
//
//	Overview		setting a pwm with dither
//
//	Input			pin                          - uint16_t				enum_pwm_pin_name inside io_tables.h
//					freq	                     - uint16_t				10Hz to 1000Hz
//					duty 	                     - uint16_t				0 - 1000 (0 - 100.0%)
//					dither_duty	                 - uint16_t				duty cycle of the dither signal
//					dither_freq	                 - uint16_t				frequency of the dither signal
//  Output          uint32_t                     - 0 = success

	Example:		uint32_t ret = user_pwm_set_dither(PWM_HSD2_OUT4, 500, 1000, 400, 20);

// Duty cycle is adjustable for each output
// Frequency is restricted to the related timer channel
//
// Attention: Call this function only once for initialization or after a parameter change is required!

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_pwm_set_duty(uint16_t pin, uint16_t duty);
//
//  Overview        setting duty of a pwm pin
//
//	Input			pin                          - uint16_t				enum_pwm_pin_name inside io_tables.h
//					duty 	                     - uint16_t				0 - 1000 (0 - 100.0%)
//  Output          uint32_t                     - 0 = success

    Example:        uint32_t ret = user_pwm_set_duty(PWM_HSD1_OUT0, 500);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_pwm_set_pwm_ramped(uint16_t pin, uint16_t freq, uint16_t duty, uint16_t ramp_time);
//
//  Overview        setting pwm freq and duty with ramp of a pwm pin
//
//  Input           pin     	-   enum_pwm_pin_name inside io_tables.h
//                  freq    	-   0 - 2000
//                  duty    	-   0 - 1000
//					ramp_time	-	0-65535 time in milliseconds to execute ramp
//  Output          result  	-   0 = ramp finished , 1 = ramp in progress, 2 = pin channel error

    Example:        uint32_t ret = user_pwm_set_duty_ramped(PWM_HSD1_OUT0, 200, 500, 1000);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_pwm_set_duty_ramped(uint16_t pin, uint16_t duty, uint16_t ramp_time);
//
//  Overview        setting duty with ramp of a pwm pin
//
//  Input           pin     	-   enum_pwm_pin_name inside io_tables.h
//                  duty    	-   0 - 1000
//					ramp_time	-	0-65535 time in milliseconds to execute ramp
//  Output          result  	-   0 = ramp finished , 1 = ramp in progress, 2 = pin channel error

    Example:        uint32_t ret = user_pwm_set_duty_ramped(PWM_HSD1_OUT0, 500, 1000);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_pwm_set_freq(uint16_t pin, uint16_t freq);
//
//  Overview        setting frequency to the module of a pwm pin
//
//	Input			pin                          - uint16_t				enum_pwm_pin_name inside io_tables.h
//					freq	                     - uint16_t				10Hz to 1000Hz
//  Output          uint32_t                     - 0 = success

    Example:        uint32_t ret = user_pwm_set_freq(PWM_HSD1_OUT0, 500);

// Frequency is restricted to the related timer channel
// If frequency is set to 0, duty of the pin is changed to 0 instead

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_set_pwm_freq_global(uint16_t freq);
//
//  Overview        setting frequency to all pwm modules
//
//	Input			freq	                     - uint16_t				10Hz to 1000Hz
//  Output          uint32_t                     - 0 = success

    Example:        uint32_t ret = user_set_pwm_freq_global(500);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_pwm_current_control(enum_pwm_pin_name pin, uint32_t set_value, uint32_t kp, uint32_t ki);
//
//  Overview        PI controller that set's the PWM duty Output to a level, so that the desired setpoint value (in mA) is set.
//
//                  !!!ATTENTION!!!: To make this function work, a frequency for the PWM output must be set separately. Example (void)user_set_pwm_freq_global(500);
//
//  Input           pin                          - enum_pwm_pin_name 	inside io_tables.h
//                  set_value                    - uint32_t 			The desired target value in mA.
//                  kp                           - uint32_t				Gain factor of the P part in the PI controller
//                  ki                           - uint32_t				Gain factor of the I part in the PI controller
//  Output          uint32_t                     - PI controller calculated duty cycle.

    Example:        user_pwm_current_control(PWM_HSD1_OUT0, 400, 600, 100);


//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   Frequency                    #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_freq_get_measured_freq(uint16_t pin);
//
//  Overview        get frequency of input pin
/
//  Input           pin                          - enum_pwm_pin_name 	inside io_tables.h  FREQ_A_IN0 || ... || FREQ_A_IN5
//  Output          uint32_t                     - measured frequency in Hz

    Example:        uint32_t freq_ai_0 = user_freq_get_measured_freq(FREQ_A_IN0);

    //---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_freq_get_measured_freq_high_res(uint16_t pin);
//
//  Overview        get frequency of input pin
/
//  Input           pin                          - enum_pwm_pin_name 	inside io_tables.h  FREQ_A_IN0 || ... || FREQ_A_IN5
//  Output          uint32_t                     - measured frequency in mHz

    Example:        uint32_t freq_ai_0 = user_freq_get_measured_freq_high_res(FREQ_A_IN0);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_freq_get_measured_duty(uint16_t pin);
//
//  Overview        get measured duty of input pin
/
//  Input           pin                          - enum_pwm_pin_name 	inside io_tables.h  FREQ_A_IN0 || ... || FREQ_A_IN5
//  Output          uint32_t                     - Result 0 - 1000 ( 0.1% )

    Example:        uint32_t duty_ai_0 = user_freq_get_measured_duty(FREQ_A_IN0);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_freq_get_measured_duty_high_res(uint16_t pin);
//
//  Overview        get measured duty of input pin
/
//  Input           pin                          - enum_pwm_pin_name 	inside io_tables.h  FREQ_A_IN0 || ... || FREQ_A_IN5
//  Output          uint32_t                     - Result 0 - 10000 ( 0.01% )

    Example:        uint32_t duty_ai_0 = user_freq_get_measured_duty_high_res(FREQ_A_IN0);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_freq_init_encoder(uint8_t instance, uint8_t channelA, uint8_t channelB, uint8_t mode);
//
//  Overview        Function to initialize quadrature encoder instance
/
//  Input           instance                     - uint8_t encoder instance
//  Input           channelA                     - enum_pwm_pin_name Channel A input pin name
//  Input           channelB                     - enum_pwm_pin_name Channel B input pin name
//  Input           mode                         - enum_encoder_mode_t encoder counting mode (1x,2x,4x)
//  Output          uint32_t                     - 0 = success

    Example:        uint32_t status = user_freq_init_encoder(0, FREQ_A_IN0, FREQ_A_IN1, HAL_ENCODER_MODE_4X);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_freq_get_encoder_value(uint8_t instance, int32_t *value);
//
//  Overview        Function to get the value of quadrature encoder counter
/
//  Input           instance                     - uint8_t encoder instance
//  Input           value                        - int32_t* pointer to return value


    Example:        int32_t enc_cnt;
                    uint32_t status = user_freq_get_encoder_value(0, &enc_cnt);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint32_t user_freq_set_encoder_value(uint8_t instance, int32_t value);
//
//  Overview        Function to reset the value of quadrature encoder counter
/
//  Input           instance                     - uint8_t encoder instance
//  Input           value                        - int32_t value to set

    Example:        uint32_t status = user_freq_set_encoder_value(0, 0);

//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   TIME BEHAVIOR                #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t user_timer_set_timestamp(uint32_t *timestamp, enum_PRECISION precision);
//
//	Overview		set timestamp
//
//	Input			*timestamp		             - uint32_t				pointer to timestamp variable
//					precision		             - enum_PRECISION 		in user_api_timer.h
//
//  Output          uint8_t                      - Return code, 0 = success

	Example:		uint32_t my_timestamp_0;
					user_timer_set_timestamp(&my_timestamp_0, PRECISION_1MS);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t user_timer_time_elapsed(uint32_t timestamp_t0, uint32_t span, enum_PRECISION precision)
//
//	Overview		check elapsed time
//
//	Input			timestamp_t0 	             - uint32_t 			reference time value
//					span			             - uint32_t 			desired timespan[precision]
//					precision		             - enum_PRECISION 		user_api_timer.h
//	Output			uint8_t result	             - Return code, 0 = time not passed

	Example:		// check if a time of 500ms passed since last timestamp
	                if(user_timer_time_elapsed(my_timestamp_0, 500, PRECISION_1MS))
					{
				    // if the time passed, set "timestamp_t0" to a new timestamp to start cycling and do something ...
						user_timer_set_timestamp(&my_timestamp_0, PRECISION_1MS);
					}


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t user_timer_get_prog_cycletime(uint32_t *roundtrip_time, enum_PRECISION precision, uint8_t reset_start)
//
//	Overview		get roundtrip time,  from one function call to the next
//
//	Input			*roundtrip_time		         - uint32_t				Pointer the the variable to store timer data
//					precision			         - enum_PRECISION 		With what precision should be counted, precision should be the same as the one in user_set_timestamp()
//					reset_start			         - uint8_t				If a reset is carried out, measurements are taken again from this point in time
//	Output			uint8_t                      - Return code,  0 = success

	Example:		uint32_t roundtrip_time;
					user_timer_get_prog_cycletime(&roundtrip_time, PRECISION_1MS, 0)
					.
					.
					.
					user_timer_get_prog_cycletime(&roundtrip_time, PRECISION_1MS, 1)


//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   LIN-BUS                      #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint32_t lin_db_get_value(uint32_t datapoint_id);
//
//	Overview		Get the value of a signal/datapoint from the LIN database
//
//	Input			datapoint_id 	             - uint32_t				Index of the LIN datapoint. See values from lin_db_tables.c
//	Return			uint32_t		             - Returns the data-point value.

	Example:		uint32_t value;
					value = lin_db_get_value(LIN0_RX_SIGNAL_NAME_15);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void lin_db_set_value(uint32_t datapoint_id, uint32_t set_value);
//
//	Overview		Set the value of a signal/datapoint from the LIN database
//
//	Input			datapoint_id 	             - uint32_t				Index of the LIN datapoint. See values from lin_db_tables.c
//					set_value		             - uint32_t				The new value to write.
//	Output			void

	Example:		lin_db_set_value(LIN0_TX_SIGNAL_NAME_1, 0x0F);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t lin_check_for_received_frame(uint8_t lin_module, uint8_t frame_index, uint8_t reset);
//
//	Overview		Universal function for checking if a LIN frame (or also frame header only in slave mode) was received
// 					without knowing about request or response frame on master or slave.
// 						NOTE 1: This currently does not enable frame transmission in slave mode even though the "reset" parameter is TRUE.
//								=> additionally use lin_enable_frame_transmission() to clear the flag and enable transmission.
//						NOTE 2: For most use cases, the parameter "reset" can be set to be TRUE.
//								For more details concerning the flag handling, see descriptions of the following functions:
//									- lin_check_for_received_response_frame()
//									- lin_check_for_received_request_frame()
//
//	Input			lin_module		             - uint8_t				LIN index number. See options at #enum_lin_bus_id in lin_db_tables.h.
//					frame_index		             - uint8_t				Frame index number or name from enum_lin_frame_id
//										                            	HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//					reset			             - uint8_t 				TRUE (1) clear the flag to detect a new receive, FALSE (0) don't clear the flag to reset it manual
//	Output			uint8_t			             - Return code,  0 = nothing received
//                                                               1 = received,

	Example:		if( lin_check_for_received_frame(LIN_BUS_0, LIN0_FRM_RX_INDEX_NAME_01, TRUE) == TRUE )
    				{
        				// complete frame / frame header was received
    				}


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t lin_check_for_received_header(uint8_t frame_index);
//
//	Overview		SLAVE only:  Check if a frame header from the master was received that requires transmission of a response by the slave (published frame)
//						NOTE 1:	The corresponding flag has to be cleared manually to enable transmission of the response.
//								This way, the data to be sent can be safely updated before it is actually transmitted.
//  					NOTE 2: This is just an "alias" for lin_check_for_received_response_frame() with a more descriptive name.
//
//
//	Input			frame_index 	             - uint8_t 				frame index number or name from enum_lin_frame_id in lin_db_tables.h
//										                   				HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//	Output			uint8_t			             - Return code,  0 = nothing received
//                                                               1 = received,

	Example (SLAVE mode): 	if (lin_check_for_received_header( frame_index )) 	// TRUE if a header (without payload) was received
  							{
								lin_db_set_value(LIN0_TX_SIGNAL_NAME_1, 0x0F);	// update a certain value within the frame to be transmitted

								lin_enable_frame_transmission( frame_index );	// enable frame transmission
							}


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t lin_check_for_received_response_frame(uint8_t frame_index);
//
//	Overview		MASTER: Check if a response from a slave was received (subscribed frame).
//
//					SLAVE:  Check if a frame header from the MASTER was received that requires transmission of a response by the slave (published frame).
//						NOTE: The corresponding flag has to be cleared manually to enable transmission of the response.
// 							  This way, the data to be sent can be safely updated before it is actually transmitted.
//
//
//	Input			frame_index 	             - uint8_t					frame index number or name from enum_lin_frame_id in lin_db_tables.h
//										                                	HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//	Output			uint8_t			             - Return code,  0 = nothing received
//                                                               1 = received,

	Example (SLAVE mode):	if (lin_check_for_received_response_frame(uint8_t frame_index)) 	// TRUE if a header (without payload) was received (published frame)
  							{
  								lin_db_set_value(LIN0_TX_SIGNAL_NAME_1, 0x0F);					// update a certain value within the frame to be transmitted

  								lin_clear_response_frame_flag( uint8_t frame_index );			// clear the flag to enable transmission of the response
  							}


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t lin_check_for_received_request_frame(uint8_t frame_index);
//
//	Overview		SLAVE:  Check if a complete frame from the MASTER was received.
//						NOTE: The corresponding flag (request frame flag) has to be cleared manually in some scenarios (see lin_clear_request_frame_flag()).
//							  For most applications, using lin_check_for_received_frame( ..., TRUE ) is more convenient for this use case.
//
//	Input			frame_index 	             - uint8_t 				frame index number or name from enum_lin_frame_id in lin_db_tables.h
//										                    			HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//	Output			uint8_t			             - Return code,  0 = nothing received
//                                                               1 = received,

	Example (SLAVE mode):	if (lin_check_for_received_response_frame(uint8_t frame_index)) 	// TRUE if a frame with payload was received (subscribed frame)
  							{
  								received_data = lin_db_get_value(LIN0_RX_SIGNAL_NAME_1);		// get a value from the received frame

  								lin_clear_request_frame_flag( uint8_t frame_index );			// clear the flag to re-enable detection of newly received frames
  							}


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void lin_enable_frame_transmission(uint8_t frame_index);
//
//	Overview		SLAVE: Enable transmission of the slave response data field
//						NOTE: This just an "alias" for lin_clear_response_frame_flag() with a more descriptive name.
//
//	Input			frame_index 	             - uint8_t				frame index number or name from enum_lin_frame_id in lin_db_tables.h
//								                  						HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//	Output			void

	Example:		lin_enable_frame_transmission(LIN0_FRM_RESP_INDEX_NAME_01);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void lin_clear_response_frame_flag(uint8_t frame_index);
//
//	Overview		MASTER: In master mode, resetting the flag is not strictly necessary.
//
//					SLAVE: The response frame flag needs to be cleared to enable transmission of the response data field.
//
//	Input			frame_index 	             - uint8_t				frame index number or name from enum_lin_frame_id in lin_db_tables.h								                  					HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//										                   				HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//	Output			void

	Example:		lin_clear_response_frame_flag(LIN0_FRM_RESP_INDEX_NAME_01);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void lin_clear_request_frame_flag(uint8_t frame_index);
//
//	Overview		This flag needs to be cleared if the detection of newly received frames within a usercode() cycle
//					is required (see example below).
//						NOTE: Alternatively lin_check_for_received_frame(..., TRUE) can be used for frame reception
//							  check and combined automatic clearing of the flag (recommended for most applications).
//
//	Input			frame_index 	             - uint8_t				frame index number or name from enum_lin_frame_id in lin_db_tables.h								                  					HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//										                   				HINT: be sure to use FRAME index only, NOT signal/datapoint index!
//	Output			void

Example:			// With clearing the flag
					void usercode()
					{
						// Check #1
						if (lin_check_for_received_request_frame(LIN0_FRM_REQ_INDEX_NAME_01))
						{
							// this is entered if the frame LIN0_FRM_REQ_INDEX_NAME_01 was actually received

							// clear the flag to re-enable detection of newly received frames
							lin_clear_request_frame_flag(LIN0_FRM_REQ_INDEX_NAME_01);
						}

						// [...]

						// Check #2 (same frame)
						if (lin_check_for_received_request_frame(LIN0_FRM_REQ_INDEX_NAME_01))
						{
							// this is only entered if the frame LIN0_FRM_REQ_INDEX_NAME_01 has been
							// received again between Check #1 and Check #2
						}

					}

					// Without clearing the flag
					void usercode()
					{
						// Check #1
						if (lin_check_for_received_request_frame(LIN0_FRM_REQ_INDEX_NAME_01))
						{
							// this is entered if the frame LIN0_FRM_REQ_INDEX_NAME_01 was actually received
						}

						// [...]

						// Check #2 (same frame)
						if (lin_check_for_received_request_frame(LIN0_FRM_REQ_INDEX_NAME_01))
						{
							// if the flag has not been cleared before, this will be entered even though
							// no new frame has been received between Check #1 and Check #2
						}
					}


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void lin_schedule_handling(uint8_t lin_schedule_table_index, uint8_t lin_st_active);	// only as master
//
//	Overview		MASTER only: Schedule the LIN frames as defined in the selected schedule table
//
//	Input			lin_schedule_table_index	 - uint8_t 				The schedule table affected by the reset (lin_db_tables.h)
//					lin_st_active				 - uint8_t				(TRUE/FALSE) - use TRUE to activate the scheduling
//																		NOTE: Only one schedule table may be active at a time! Otherwise the behaviour is undefined.
//	Output			void

	Example:		lin_schedule_handling(LIN0_SCHEDULE_TABLE_NR1, TRUE);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void lin_schedule_handling_reset(uint8_t lin_schedule_table_index);						// only as master
//
//	Overview		MASTER only: Reset the LIN schedule handling (set schedule table index to 0)
//
//	Input			lin_schedule_table_index	 - uint8_t  			The schedule table affected by the reset (lin_db_tables.h)
//	Output			void

	Example:		lin_schedule_handling_reset(LIN0_SCHEDULE_TABLE_NR1);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint8_t lin_ma_check_frame_resp_timeout(uint8_t frame_index);							// only as master
//
//	Overview		MASTER only: check frame response timeout
//
//	Input			frame_index 	             - uint8_t 				Frame index number or name from enum_lin_frame_id
//	Output			uint8_t			             - Return code,  0 = not timeout reachedTRUE
//                                                               1 = Slave not responding (timeout)

	Example:		if( lin_ma_check_frame_resp_timeout(LIN0_FRM_INDEX_NAME_01) == TRUE )
    				{
        				// timeout reached - Slave not responding
    				}


//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   EEPROM                       #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


// The EEPROM user area spans from EE_USER_START (2048) to EE_USER_END (4095) bytes is reserved as user area.
// Only these 2048 bytes are available for the customer to use.
// The other 2048 bytes are reserved for factory data, calibration data and others.
// The user_eeprom_write and user_eeprom_read functions are working with relative addresses. When writing to addr = 50
// the functions will calculate the absolute address of the data. This means that the customer can access the user EEPROM
// by using the addresses between 0 and 2047.
// Wrong memory address or the combination of length (len) and address (addr) returns an error code.

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       enum_HAL_NVM_RETURN_VALUE user_eeprom_write(uint32_t addr, uint32_t len, const uint8_t *ptr_data)
//
//  Overview        write eeprom
//
//  Input           addr                         - uint32_t  			Relative address of the data [0 - 2047]
//                  len                          - uint32_t				Length of data (Bytes)
//                  *ptr_data                    - const uint8_t		Pointer to uint8_t variable or array, to write data
//  Output          enum_HAL_NVM_RETURN_VALUE    - Return code, 0 = success

    Example:        // Write one byte with the value 4 to address 0x04 and one with the value 2 to address 0x05 in the USER EEPROM
                    uint8_t write_val[2];
                    write_val[0] = 4;
                    write_val[1] = 2;
                    user_eeprom_write(0x04, sizeof(write_val), &write_val[0]);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       enum_HAL_NVM_RETURN_VALUE user_eeprom_read(uint32_t addr, uint32_t len, uint8_t *ptr_data)
//
//  Overview        read eeprom
//
//  Input           addr                         - uint32_t  			Relative address of the data [0 - 2047]
//                  len                          - uint32_t				Length of data (Bytes)
//  Return          *ptr_data                    - uint8_t 				Pointer to where read data is saved
//  Output          enum_HAL_NVM_RETURN_VALUE    - Return code, 0 = success

    Example:        // Read out two bytes starting at address 0x04 of the USER EEPROM area
                    uint8_t read_val[2];
                    user_eeprom_read(0x04, sizeof(read_val), &read_val[0]);

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       uint16_t user_eeprom_read_module_eeprom_version();
//
//  Overview        read specific module data from the EEPROM. Used for integer type values.
//                  There exists one function for every factory data. See user_api_eeprom.h
//
//  Return          uint16_t                     - uint16_t 			Returns the eeprom version of the module
 *
    Example:        // Save the return value of the function in a appropriate type.
                    uint16_t eeprom_version = 0;
                    eeprom_version = user_eeprom_read_module_eeprom_version();

//---------------------------------------------------------------------------------------------------------------------
//  Procedure       enum_HAL_NVM_RETURN_VALUE user_eeprom_read_module_drawing_nr(uint8_t buffer[], uint8_t size_buffer, bool filter);
//
//  Overview        read specific module data from the EEPROM. Used for ASCII coded values.
//                  There exists one function for every factory data. See user_api_eeprom.h
//
//  Input           size_buffer                  - uint8_t 				size of the buffer, must be at least 21 bytes
//                  filter                       - bool const 			FALSE to read the raw data or set TRUE to filter unnecessary characters (whitespace)
//  Return          *buffer                      - uint8_t 				buffer to write the data into, size must be at least 21 bytes
//  Output          enum_HAL_NVM_RETURN_VALUE    - Return code, 0 = success

    Example:        // Part number is a string with up to 21 characters. Example of a drawing number: "2.156.320.00"
                    uint8_t draw_nr[21] = {0};
                    user_eeprom_read_module_drawing_nr(draw_nr, sizeof draw_nr, 1);

//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   LOOK UP TABLE                #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint16_t user_util_get_lookup_value_1D_16(int16_t *table_x, int16_t *table_y, uint8_t count, int16_t val, uint8_t mode);
//					uint32_t user_util_get_lookup_value_1D_32(int32_t *table_x, int32_t *table_y, uint8_t count, int32_t val, uint8_t mode);
//
//	Overview		1D lookup table
//
//	Input			*table_x	                 - int16_t				Pointer to an x-array
//					*table_y	                 - int16_t				Pointer to an y-array
//					count		                 - uint8_t				Counts of x-array elements
//					val			                 - int16_t				x-value
//					mode		                 - enum_LUT_MODE		LUT_MODE_EXTRAPOLATION (Standard): away from the array extrapolate
//                                                  					LUT_MODE_LIMIT: away from the array not extrapolate
//                                  									LUT_MODE_KALIBRATION: y-value always >= 0, extrapolating upwards with difference (y_max - x_max)
//	Return			uint16_t	                 - Returns the approximate value


	Example:		uint16_t ret_val;
					int16_t arr_x[] = {136,200,311,444,666};
					int16_t arr_y[] = {-10,  5, 16, 27, 39};

					ret_val = user_util_get_lookup_value_1D_16(arr_x, arr_y, 5, 250, LUT_MODE_EXTRAPOLATION);


//---------------------------------------------------------------------------------------------------------------------
//	Procedure		uint16_t user_util_get_lookup_value_2D_16(int16_t *table_x, int16_t *table_y, uint8_t count_x, uint8_t count_y, int16_t *table_z, int16_t val_x, int16_t val_y);
//					uint32_t user_util_get_lookup_value_2D_32(int32_t *table_x, int32_t *table_y, uint8_t count_x, uint8_t count_y, int32_t *table_z, int32_t val_x, int32_t val_y);
//
//	Overview		2D lookup table
//
//	Input			*table_x		             - int16_t				Pointer to an x-array (1D)
//					*table_y		             - int16_t				Pointer to an y-array (1D)
//					count_x [in]                 - uint8_t 				Counts of x-array elements
// 			  		count_y [in]                 - uint8_t 				Counts of y-array elements
//					*table_z [in]                - int16_t 				Pointer to an z-array (1D with (count_y * count_x) elements)
// 					val_x [in]		             - int16_t 				x-value (away from the x-array => extrapolation)
//		 	 	 	val_y [in]                   - int16_t 				y-value (away from the y-array => extrapolation)
//   Return 		uint16_t                     - Returns the approximate value
//					uint32_t                     - Returns the approximate value

	Example:		uint16_t ret_val;
					int16_t arr_x_2d[] 	= {10,20,30,40,50};
    				int16_t arr_y_2d[] 	= {100,200,300};
    				int16_t arr_z[] 	= {10,  20,  50, 90,150,
        								   25,  70, 150,250,400,
        								   50, 120, 240,400,860};

        			ret_val = user_util_get_lookup_value_2D_16(arr_x, arr_y, 5, 3, arr_z, 25, 270);


	user_uart_send_buffer_blocking(UART_INTERFACE, rx_buff, RX_BUFF_SIZE);

//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   RS232                        #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_set_baudrate(uint8_t uart_interface, enum_HAL_SCI_BAUD baudrate);
//
//	Overview		change baudrate of uart
//
//	Input			uart_interface	             - uint8_t             	UART interface	inside sci_app.h
//					baudrate		             - enum_HAL_SCI_BAUD   	Baudrate
//  Output          enum_HAL_SCI_RETURN_VALUE    - 0 = success

	Example:		enum_HAL_SCI_RETURN_VALUE err;					
					err = user_uart_set_baudrate(SCI_INTERFACE_2, HAL_SCI_BAUD_19200);

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_set_config_parameter(uint8_t uart_interface, lpuart_parity_mode_t parity, lpuart_stop_bit_count_t stop_bit, lpuart_bit_count_per_char_t bit_per_char );
//
//	Overview		configure additional uart parameter
//
//	Input			uart_interface		         - uint8_t                       UART interface	inside sci_app.h	
//					parity	        	         - lpuart_parity_mode_t          parity mode (LPUART_PARITY_DISABLED, LPUART_PARITY_EVEN, LPUART_PARITY_ODD)
//					stop_bit		             - lpuart_stop_bit_count_t       amount of bits per stop bit (LPUART_ONE_STOP_BIT, LPUART_TWO_STOP_BIT)
//					bit_per_char		         - lpuart_bit_count_per_char_t   amount of bits per char (LPUART_8_BITS_PER_CHAR, LPUART_9_BITS_PER_CHAR, LPUART_10_BITS_PER_CHAR)
//  Output          enum_HAL_SCI_RETURN_VALUE    - Return code, 0 = success

	Example:		enum_HAL_SCI_RETURN_VALUE err;
				
					uint8_t uart_interface = 2;
					lpuart_parity_mode_t parity = LPUART_PARITY_DISABLED;
					lpuart_stop_bit_count_t stop_bit = LPUART_ONE_STOP_BIT;
					lpuart_bit_count_per_char_t bit_per_char = LPUART_8_BITS_PER_CHAR

					err = user_uart_set_config_parameter(uart_interface, parity, stop_bit, bit_per_char );

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_send_buffer_blocking(uint8_t uart_interface, uint8_t send_buffer[], uint8_t send_length)
//
//	Overview		send uart buffer (blocking - halts execution until data is transmitted)
//
//	Input			uart_interface		         - uint8_t              UART interface
//                  send_buffer		             - uint8_t 				Data buffer to send
//					send_length		             - uint8_t				number of bytes to send
//  Output          enum_HAL_SCI_RETURN_VALUE    - Return code, 0 = success

	Example:		uint8_t my_sci_buffer[3];

					my_sci_buffer[0] = 0xAB;
					my_sci_buffer[1] = 0xBC;
					my_sci_buffer[2] = 0xCD;

					user_uart_send_buffer_blocking(0, my_sci_buffer, sizeof(my_sci_buffer));

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_send_buffer(uint8_t uart_interface, uint8_t send_buffer[], uint8_t send_length)
//
//	Overview		send uart buffer (non-blocking - allows simultaneous data transfer and program execution)
//
//	Input			uart_interface		         - uint8_t              UART interface
//                  send_buffer		             - uint8_t 				Data buffer to send
//					send_length		             - uint8_t				number of bytes to send
//  Output          enum_HAL_SCI_RETURN_VALUE    - Return code, 0 = success

	Example:		uint8_t my_sci_buffer[3];

					my_sci_buffer[0] = 0xAB;
					my_sci_buffer[1] = 0xBC;
					my_sci_buffer[2] = 0xCD;

					user_uart_send_buffer(0, my_sci_buffer, sizeof(my_sci_buffer));

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_send_get_status(uint8_t uart_interface)
//
//	Overview        Get the status of the non-blocking send
//
//	Input			uart_interface		         - uint8_t              UART interface	inside sci_app.h
//  Output          enum_HAL_SCI_RETURN_VALUE    - Return code, 0 = success

	Example:		enum_HAL_SCI_RETURN_VALUE status;
					status = user_uart_send_get_status(SCI_INTERFACE_2);

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_send_get_remaining_bytes(uint8_t uart_interface)
//
//	Overview        Get the number of bytes remaining to be sent
//
//	Input			uart_interface		         - uint8_t              UART interface  inside sci_app.h
//  Output          uint32_t                     - Number of bytes remaining to be received

	Example:		uint32_t remaining_bytes;
					remaining_bytes = user_uart_send_get_remaining_bytes(SCI_INTERFACE_2);

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_receive_buffer_blocking(uint8_t uart_interface, uint8_t recv_buffer[], uint8_t recv_length)
//
//	Overview		Receive uart buffer (blocking - halts execution until receive is complete)
//
//	Input			uart_interface		         - uint8_t              UART interface	inside sci_app.h
//                  recv_buffer		             - uint8_t 				Data buffer to send
//					recv_length		             - uint8_t				number of bytes to send
//  Output          enum_HAL_SCI_RETURN_VALUE    - Return code, 0 = success

	Example:		uint8_t my_sci_buffer[3];

					user_uart_receive_buffer_blocking(SCI_INTERFACE_2, my_sci_buffer, sizeof(my_sci_buffer));

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_receive_buffer(uint8_t uart_interface, uint8_t recv_buffer[], uint8_t recv_length)
//
//	Overview        Receive uart buffer in interrupt mode (non-blocking - allows simultaneous data transfer and program execution)
//
//	Input			uart_interface		         - uint8_t              UART interface	inside sci_app.h
//                  recv_buffer 	             - uint8_t 				Data buffer to receive
//					recv_length 	             - uint8_t				number of bytes to receive
//  Output          enum_HAL_SCI_RETURN_VALUE    - Return code, 0 = success

	Example:		uint8_t my_sci_buffer[3];

					user_uart_receive_buffer(SCI_INTERFACE_2, my_sci_buffer, sizeof(my_sci_buffer));

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_receive_get_status(uint8_t uart_interface)
//
//	Overview        Get the status of the non-blocking receive
//
//	Input			uart_interface		         - uint8_t              UART interface	inside sci_app.h
//  Output          enum_HAL_SCI_RETURN_VALUE    - Return code, 0 = success

	Example:		enum_HAL_SCI_RETURN_VALUE status;
					status = user_uart_receive_get_status(SCI_INTERFACE_2);

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		enum_HAL_SCI_RETURN_VALUE user_uart_receive_get_remaining_bytes(uint8_t uart_interface)
//
//	Overview        Get the number of bytes remaining to be received
//
//	Input			uart_interface		         - uint8_t              UART interface
//  Output          uint32_t                     - Number of bytes remaining to be received

	Example:		uint32_t remaining_bytes;
					remaining_bytes = user_uart_receive_get_remaining_bytes(SCI_INTERFACE_2);

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void user_sci_continuous_receive_callback(uint8_t module, uint8_t data)
//
//	Overview		When a message on SCI0 (RS232) is received, this function is called, byte by byte. 
//                  SET_SCI_CONTINUOUS_RECEPTION must be defined in usercode.h
//
//	Output			module	    =	Device instance number
 	 	 	 	 	data		=	receiving data (byte)

	Example:		void user_sci_continuous_receive_callback(uint8_t instance, uint8_t data)
					{
						static uint8_t byte_array[32] = {0};
						static uint8_t byte_cnt = 0;

						byte_array[byte_cnt] = data;
						byte_cnt++;
					}

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void user_sci_rx_full_callback(uint8_t instance)
//
//	Overview		When a message on SCI0 (RS232) is completely received, this routine is called.
//                  SET_SCI_CONTINUOUS_RECEPTION must be commented out in usercode.h
//
//	Output			instance	    =	Device instance number

	Example:		void user_sci_rx_full_callback(uint8_t instance)
					{
                        if (instance == UART_INTERFACE)
                        {
                            rx_full_flag = 1;
                        }
					}

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void user_sci_continuous_transmit_callback(uint8_t instance)
//
//	Overview		When a message on SCI0 (RS232) is sent, this routine is called, byte by byte. 
//                  SET_SCI_CONTINUOUS_RECEPTION must be defined in usercode.h
//
//	Output			instance	    =	Device instance number
 	 	 	 	 	*buff		    =	pointer to sci_app internal transmit buffer

	Example:		#define UART_INTERFACE  SCI_INTERFACE_0
                    uint8_t tx_data[] = "Hello World!\r\n";
                    uint8_t index = 0;
                    
                    void user_sci_continuous_transmit_callback(uint8_t instance, uint8_t *buff)
					{
                        if (instance == UART_INTERFACE)
                        {
                            index++;
                            if(index > sizeof(tx_data)-1)
                            {
                                index = 0;
                            }
                            *buff = tx_data[index];
                        }
					}

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void user_int_tx_empty_sci(uint8_t instance)
//
//	Overview		When a message on SCI0 (RS232) is completely sent, this routine is called.
//                  SET_SCI_CONTINUOUS_TRANSMISSION must be commented out in usercode.h
//
//	Output			instance	    =	Device instance number

	Example:		void user_int_tx_empty_sci(uint8_t instance)
					{
                        if (instance == UART_INTERFACE)
                        {
                            tx_empty_flag = 1;
                        }
					}

//---------------------------------------------------------------------------------------------------------------------
//	Procedure		void user_sci_transfer_complete_callback(uint8_t instance)
//
//	Overview		When a message on SCI0 (RS232) is completely transfered, this routine is called, for TX and RX
//
//	Output			instance	    =	Device instance number

	Example:		void user_sci_transfer_complete_callback(uint8_t instance)
					{
                        if (instance == UART_INTERFACE)
                        {
                            //Process
                        }
					}


//##################################-----------------------------------------------------------------------------------
//#                                #-----------------------------------------------------------------------------------
//#   SYSTEM POWER                 #
//#                                #-----------------------------------------------------------------------------------
//##################################-----------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
//  Procedure       void user_system_soft_reset()
//
//  Overview        System software reset

    Example:        user_system_soft_reset();



*/



/*----------------------------------------------------------------------------*/
/**
	Regardless of what has been received, each CAN message can be evaluated here
*
    TO ENABLE:  set #define SET_CALLBACK_CAN_MESSAGE_RECEIVE in user_code.h
*
*/

void user_can_receive_msg_callback(uint8_t bus_id, bios_can_msg_typ* msg)
{
    // --------------------------------------------------------------------------------
    // in the case of no using to get no compiler INFO set all as (void)xy;
    // --------------------------------------------------------------------------------

	(void)bus_id;
	(void)msg;

	// put your code here

	if( (msg->id == msgClampStatus) && (msg->id_ext == STANDARD_ID) )
    {
        get_clampstatus(msg->data[18]);

    }
    else
    {
        // do nothing
    }

    // put your code here

/*     Example:   When CAN-ID 0x400 is received, send an acknowledge
    if( (msg->id == 0x400) && (msg->id_ext == STANDARD_ID) )
    {
        if( msg->data[0] == 0x33 )
        {
            user_can_send_msg(CAN_BUS_0, 0x720, STANDARD_ID, 8, 0x66, 0x33, 0x11, 0, 0, 0, 0, msg->data[7]);
        }
        else
        {
            // do nothing
        }
    }
    else
    {
        // do nothing
    }

    // Switch the output DO_HSD1_OUT0 when bit8 of byte3 of 0x1FF004AB is "1"
    if( (msg->id == 0x1FF004AB) && (msg->id_ext == EXTENDED_ID) )
    {
        user_io_set_do( DO_HSD1_OUT0, (msg->data[3] & 0x80) );
    }
    else
    {
        // do nothing
    }
    // put your code here
*/

}


/*----------------------------------------------------------------------------*/
/**
*   Receive interrupt of serial communication interface (RS232)
*   instance is the UART interface number, e.g. 0 for UART0
*   data is 8 bit of data. this routine is called for every byte received.
*   TO ENABLE:  set #define SET_SCI_CONTINUOUS_RECEPTION in user_code.h
*/
void user_sci_continuous_receive_callback(uint8_t instance, uint8_t data)
{
    // don't put too much code in here. this is called in an interrupt!
}

/*----------------------------------------------------------------------------*/
/**
*   Receive Buffer Full interrupt of serial communication interface (RS232)
*   instance is the UART interface number, e.g. 0 for UART0
*   This routine is called for every completed receive. 
*	It can be used with sci_rx function (Interrupt mode receive)
*   TO ENABLE:  comment out #define SET_SCI_CONTINUOUS_RECEPTION in user_code.h
*/
// void user_sci_rx_full_callback(uint8_t instance)
// {
// 	// don't put too much code in here. this is called in an interrupt!
// }

/*----------------------------------------------------------------------------*/
/**
*   Transmit interrupt of serial communication interface (RS232)
*   instance is the UART interface number, e.g. 0 for UART0
*   buff is 8 bit buffer..
*   TO ENABLE:  set #define SET_SCI_CONTINUOUS_TRANSMISSION in user_code.h
*/
// void user_sci_continuous_transmit_callback(uint8_t instance, uint8_t *buff)
// {
// 	// don't put too much code in here. this is called in an interrupt!
// }

/*----------------------------------------------------------------------------*/
/**
*   Transmit Empty interrupt of serial communication interface (RS232)
*   instance is the UART interface number, e.g. 0 for UART0
*	It can be used with sci_tx function (Interrupt mode transmit)
*   TO ENABLE:  comment out #define SET_SCI_CONTINUOUS_TRANSMISSION in user_code.h
*/
// void user_sci_tx_empty_callback(uint8_t instance)
// {
//     // don't put too much code in here. this is called in an interrupt!
// }

/*----------------------------------------------------------------------------*/
/**
*   Transfer Complete interrupt of serial communication interface (RS232)
*   instance is the UART interface number, e.g. 0 for UART0
*
*/
// void user_sci_transfer_complete_callback(uint8_t instance)
// {
// 	// don't put too much code in here. this is called in an interrupt!
// }

/*----------------------------------------------------------------------------*/
/**
	Interrupt every 1ms
*
    TO ENABLE:  set #define SET_CALLBACK_1MS_TIMER in user_code.h
*/
void user_int_timer_1ms(void)
{
	timer ++;
	// dont put too much code in here. this is called in an interrupt!
}

