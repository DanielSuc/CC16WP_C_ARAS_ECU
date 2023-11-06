#ifndef HAL_CAN_H
#define HAL_CAN_H



#include "hal_data_types.h"
#include "hal_version.h"

#define HAL_CAN_DLC_MAX         16u 
#define HAL_CAN2_0_DATA_LENGTH_MAX		8u	

#define USE_PRECALCULTED_CAN_BAUDRATE_TABLES


typedef enum
{
    HAL_CAN_BAUD_INVALID     = 0,       
    HAL_CAN_BAUD_10             ,       
    HAL_CAN_BAUD_20             ,       
    HAL_CAN_BAUD_33             ,       
    HAL_CAN_BAUD_50             ,       
    HAL_CAN_BAUD_83             ,       
    HAL_CAN_BAUD_100            ,       
    HAL_CAN_BAUD_125            ,       
    HAL_CAN_BAUD_250            ,       
    HAL_CAN_BAUD_500            ,       
	HAL_CAN_BAUD_800            ,       
    HAL_CAN_BAUD_1000           ,       
    HAL_CAN_BAUD_EXT            ,       
    HAL_CAN_FD_BAUD_EXT         ,       
    HAL_CAN_BAUD_MAX                    
} enum_HAL_CAN_BAUDRATE;

typedef enum
{
    HAL_CAN_OK                        = 0u,   
    HAL_CAN_ERROR_GENERAL                 ,   
    HAL_CAN_ERROR_INIT_FAILED             ,   
    HAL_CAN_ERROR_NO_CHANNEL_LEFT         ,   
    HAL_CAN_ERROR_NO_MESSAGE              ,   
    HAL_CAN_ERROR_SET_FILTER              ,   
    HAL_CAN_ERROR_CHANNEL_INVALID         ,   
    HAL_CAN_ERROR_WHILE_READING           ,   
    HAL_CAN_ERROR_WHILE_WRITING           ,   
    HAL_CAN_ERROR_BUSY                    ,   
    HAL_CAN_ERROR_READ_EMPTY              ,   
    HAL_CAN_ERROR_READ_RUN                ,   
    HAL_CAN_ERROR_SET_CALLBACK            ,   
    HAL_CAN_ERROR_BAUDRATE                ,   
    HAL_CAN_ERROR_NOT_IMPLEMENTED         ,   
    HAL_CAN_ERROR_DLC_INVALID                 

} enum_HAL_CAN_RETURN_VALUE;

typedef enum
{
    HAL_CAN_RX                        = 0u,   
    HAL_CAN_TX                                
} enum_HAL_CAN_DIRECTION;


typedef uint32_t hal_canid_t;

typedef struct
{
    hal_canid_t  can_id;            
    uint8_t      can_dlc;           
    uint8_t      can_fd;            
    uint8_t      can_fd_brs;        
    uint8_t      can_fd_esi;        
} struct_hal_can_header_t;
typedef struct
{
    struct_hal_can_header_t   header; 
    uint8_t                 data[64] __attribute__((aligned(8))); 
}struct_hal_can_frame_t;

typedef struct {
    uint32_t prop_seg;         
    uint32_t phase_seg1;       
    uint32_t phase_seg2;       
    uint32_t pre_divider;      
    uint32_t jumpwidth;        
} hal_can_time_segment;


typedef void (*hal_can_rx_callback_function_type)(struct_hal_can_frame_t* ptr_can_msg);

typedef void (*hal_can_err_callback_function_type)(uint16_t can_error);


typedef struct
{
    void*   can_handle_ptr;                             
    int32_t can_handle_number;                          
    int32_t can_handle_mb_idx;                          
    enum_HAL_CAN_BAUDRATE can_baudrate;                 
    enum_HAL_CAN_BAUDRATE can_fd_data_baudrate;         
    enum_HAL_CAN_DIRECTION can_handle_direction;        
    hal_can_rx_callback_function_type rx_cb_function;   
    hal_can_err_callback_function_type err_cb_function; 
    hal_can_time_segment can_ext_baudrate;              
    hal_can_time_segment can_fd_ext_baudrate;           
    uint8_t is_can_fd;                                  
    uint8_t is_can_listen_only;                          
} struct_hal_can_handle;

typedef struct
{
    hal_canid_t  can_id;                                
    hal_canid_t  can_mask;                              
    uint8_t id_type;					                
} struct_hal_can_filter;



enum_HAL_CAN_RETURN_VALUE hal_can_init( struct_hal_can_handle* ptr_can_handle, uint8_t bus_id, _Bool block_mode );

enum_HAL_CAN_RETURN_VALUE hal_can_deinit( struct_hal_can_handle* ptr_can_handle );

enum_HAL_CAN_RETURN_VALUE hal_can_send( const struct_hal_can_handle* ptr_can_handle, const struct_hal_can_frame_t* ptr_can_msg );

enum_HAL_CAN_RETURN_VALUE hal_can_receive( const struct_hal_can_handle* ptr_can_handle, struct_hal_can_frame_t* ptr_can_msg );

enum_HAL_CAN_RETURN_VALUE hal_can_set_filter( const struct_hal_can_handle* ptr_can_handle, const struct_hal_can_filter* ptr_can_filter );

bool hal_can_is_mb_filter_extended( const struct_hal_can_handle* ptr_can_handle, uint32_t mb_idx );

enum_HAL_CAN_RETURN_VALUE hal_can_set_receive_callback( struct_hal_can_handle* ptr_can_handle, hal_can_rx_callback_function_type ptr_cb_function );

enum_HAL_CAN_RETURN_VALUE hal_can_set_error_callback( struct_hal_can_handle* ptr_can_handle, hal_can_err_callback_function_type ptr_cb_function );

enum_HAL_CAN_RETURN_VALUE hal_can_dump( const struct_hal_can_frame_t* ptr_can_msg );

enum_HAL_CAN_RETURN_VALUE hal_can_set_baudrate( struct_hal_can_handle* ptr_can_handle, enum_HAL_CAN_BAUDRATE baudrate );

enum_HAL_CAN_RETURN_VALUE hal_can_set_fd_data_baudrate( struct_hal_can_handle* ptr_can_handle, enum_HAL_CAN_BAUDRATE baudrate );

enum_HAL_CAN_RETURN_VALUE hal_can_set_tx_mode( struct_hal_can_handle* ptr_can_handle, bool enable_fd, uint8_t fd_padding, bool enable_brs );

enum_HAL_CAN_RETURN_VALUE hal_can_get_baudrate( struct_hal_can_handle* ptr_can_handle, enum_HAL_CAN_BAUDRATE* baudrate );

enum_HAL_CAN_RETURN_VALUE hal_can_recover_from_bus_error( struct_hal_can_handle* ptr_can_handle );

uint8_t hal_can_get_msg_box_idx( uint32_t can_handle_number );


uint8_t hal_can_len_to_dlc( uint8_t len );

uint8_t hal_can_dlc_to_len( uint8_t dlc );

#endif 


