
#ifndef SOURCE_HCS12_XEQ384_CAN_GATEWAY_CANGRAPH_CODE_BIT_ACCESS_MACROS_H_
#define SOURCE_HCS12_XEQ384_CAN_GATEWAY_CANGRAPH_CODE_BIT_ACCESS_MACROS_H_


#define CONVERT_BIT_TO_BYTE_SIZE(bit_size)	( ((bit_size-1u)/8u) + 1u )

#define BYTE_ARRAY_CLEAR_BIT( byte_array, bit_index )   ( byte_array[bit_index/8u]  &= ~( 1u << (bit_index & 7u) ) )

#define BYTE_ARRAY_SET_BIT( byte_array, bit_index )    	( byte_array[bit_index/8u] |= (1u << (bit_index & 7u)) )

#define BYTE_ARRAY_GET_BIT( byte_array, bit_index )		( byte_array[bit_index/8u]  & (1u << (bit_index & 7u)) )

#endif 

