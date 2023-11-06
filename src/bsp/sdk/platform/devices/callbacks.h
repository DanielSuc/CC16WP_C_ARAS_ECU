
#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <stdint.h>

 #include <stdint.h>


typedef enum
{
    I2C_SLAVE_EVENT_RX_FULL = 0x00U,
    I2C_SLAVE_EVENT_TX_EMPTY = 0x01U,
    I2C_SLAVE_EVENT_TX_REQ = 0x02U,
    I2C_SLAVE_EVENT_RX_REQ = 0x03U,
    I2C_SLAVE_EVENT_STOP = 0X04U,
}i2c_slave_event_t;

typedef enum
{
    I2C_MASTER_EVENT_END_TRANSFER                      = 0x4U,
}i2c_master_event_t;


typedef void (*i2c_slave_callback_t)(i2c_slave_event_t event, void *userData);

typedef void (*i2c_master_callback_t)(i2c_master_event_t event, void *userData);

typedef enum
{
    SPI_EVENT_END_TRANSFER = 0
} spi_event_t;

typedef void (*spi_callback_t)(void *driverState, spi_event_t event, void *userData);

typedef enum
{
    UART_EVENT_RX_FULL      = 0x00U,    
    UART_EVENT_TX_EMPTY     = 0x01U,    
    UART_EVENT_END_TRANSFER = 0x02U,    
    UART_EVENT_ERROR        = 0x03U,    
    UART_EVENT_IDLE         = 0x04u,    
} uart_event_t;

typedef void (*uart_callback_t)(void *driverState, uart_event_t event, void *userData);


typedef void (*timer_callback_t)(void *userData);


typedef struct
{
    uint32_t groupIndex;         
    uint16_t resultBufferTail;   
} adc_callback_info_t;

typedef void (* const adc_callback_t)(const adc_callback_info_t * const callbackInfo, void * userData);

typedef enum
{
    I2S_EVENT_RX_FULL      = 0x00U,    
    I2S_EVENT_TX_EMPTY     = 0x01U,    
    I2S_EVENT_END_TRANSFER = 0x02U,    
    I2S_EVENT_ERROR        = 0x03U,    
} i2s_event_t;

typedef void (*i2s_callback_t)(i2s_event_t event, void *userData);

typedef enum {
    CAN_EVENT_RX_COMPLETE,     
    CAN_EVENT_TX_COMPLETE,     
} can_event_t;

typedef void (*can_callback_t)(uint32_t instance,
                               can_event_t eventType,
                               uint32_t objIdx,
                               void *driverState);

typedef void (*security_callback_t)(uint32_t completedCmd, void *callbackParam);

typedef enum
{
    OC_EVENT_GENERATION_OUTPUT_COMPLETE = 0x00U    
} oc_event_t;

typedef void (*oc_callback_t)(oc_event_t event, void *userData);
typedef enum
{
    IC_EVENT_MEASUREMENT_COMPLETE = 0x00U,   
    IC_EVENT_FALLING_EDGE,
    IC_EVENT_RISING_EDGE
} ic_event_t;

typedef void (*ic_callback_t)(ic_event_t event, uint8_t instance, uint8_t channel);

#endif 


