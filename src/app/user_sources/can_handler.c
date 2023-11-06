/*----------------------------------------------------------------------------*/
/**
*   @file         can_handler.c
*   @brief        Implementation of function for CAN handler. 
*/
/*----------------------------------------------------------------------------*/
#include <can_handler.h>

union 
{
	struct 
	{
		uint64_t unused_1: 18;
		uint64_t sw_kl15: 1;
		uint64_t unused2: 45;
	}sig;

	uint8_t data[8];		// Data encapsulates all the variables above
							// When data is filled, the whole struct and 
							// its variables is filled as well. 
}msg;

SW_KL15 = 0;

void get_rx_msg(bios_can_msg_typ* rx_msg)
{
	if(rx_msg->id == 0x42)
	{
		for(int i = 0; i < rx_msg->len)
		{
			msg.data[i] = rx_msg->data[i];
		}
	}
}

bool getValueKL15()
{
	return msg.sig.sw_kl15;
}


void user_output_processing()
{
	union 
	{
		struct
		{
			uint64_t unused1:12;
			uint64_t STM_State:4;
		}sig;
		uint8_t data[8];
	}msg;
	
	msg.sig.STM_state = FCT_getMainState();

	for(int i = 0; i < tx_msg.len; i++)
	{
		tx_msg.data[i] = msg.data[i];
	}

	user_can_send_msg(CAN_BUS_0; 0x151. STANDARD_ID, 8, tx_msg.data[0], tx_msg.data[1], tx_msg.data[2], tx_msg.data[3]
														tx_msg.data[4], tx_msg.data[5], tx_msg.data[6], tx_msg.data[7]);

}