#ifndef SFL_FIFO
#define SFL_FIFO


#include "hal_data_types.h"




typedef enum
{
    SFL_FIFO_ERROR_NONE = 0u,               
    SFL_FIFO_ERROR_PARAM,                   
    SFL_FIFO_ERROR_BUSY,                    
    SFL_FIFO_ERROR_OVERFLOW,                
    SFL_FIFO_ERROR_EMPTY,                   
    SFL_FIFO_ERROR_UNKNOWN,                 
    SFL_FIFO_ERROR_MAX                      
}enum_SFL_FIFO_ERROR_CODES;


typedef enum
{
    SFL_FIFO_READLOCK_DISABLED = 0,         
    SFL_FIFO_READLOCK_ENABLED               
}enum_SFL_FIFO_READLOCK_TYPE;



typedef struct
{
    uint32_t count;                         
    uint32_t next_write;                    
    uint32_t next_read;                     
    uint32_t element_size;                  
    uint32_t max;                           
    uint8_t  write_in_progress;             
    uint8_t  read_in_progress;              
    enum_SFL_FIFO_READLOCK_TYPE read_lock;  
}SFL_FIFO_CONFIG_TYPE;


enum_SFL_FIFO_ERROR_CODES sfl_fifo_init( SFL_FIFO_CONFIG_TYPE* config, uint32_t element_count, uint32_t element_size );

uint32_t sfl_fifo_get_count( SFL_FIFO_CONFIG_TYPE* config );

uint32_t sfl_fifo_get_free( SFL_FIFO_CONFIG_TYPE* config );

void sfl_fifo_lock_read( SFL_FIFO_CONFIG_TYPE* config );

enum_SFL_FIFO_READLOCK_TYPE sfl_fifo_get_read_lock( SFL_FIFO_CONFIG_TYPE* config );

void sfl_fifo_unlock_read( SFL_FIFO_CONFIG_TYPE* config );

enum_SFL_FIFO_ERROR_CODES sfl_fifo_put( SFL_FIFO_CONFIG_TYPE* config, uint8_t* new_data, uint8_t* buff );

enum_SFL_FIFO_ERROR_CODES sfl_fifo_get( SFL_FIFO_CONFIG_TYPE* config, uint8_t* result, uint8_t* buff );

enum_SFL_FIFO_ERROR_CODES sfl_fifo_get_preview( SFL_FIFO_CONFIG_TYPE* config, uint8_t* result, uint8_t* buff );

enum_SFL_FIFO_ERROR_CODES sfl_fifo_search( uint8_t* val, SFL_FIFO_CONFIG_TYPE* config, int32_t* result, uint8_t* buff );

enum_SFL_FIFO_ERROR_CODES sfl_fifo_remove( SFL_FIFO_CONFIG_TYPE* config, uint32_t count );

uint32_t sfl_fifo_get_distance( uint32_t actual, uint32_t destination, uint32_t max );

enum_SFL_FIFO_ERROR_CODES sfl_fifo_clear( SFL_FIFO_CONFIG_TYPE* config );

#endif

