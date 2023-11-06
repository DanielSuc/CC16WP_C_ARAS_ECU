
#ifndef PINS_GPIO_HW_ACCESS_H
#define PINS_GPIO_HW_ACCESS_H

#include "pins_driver.h"





#if defined(__cplusplus)
extern "C" {
#endif


#if defined(FEATURE_PINS_DRIVER_USING_PORT)
static inline pins_channel_type_t PINS_GPIO_GetPinsDirection(const GPIO_Type * const base)
{
    return (pins_channel_type_t)base->PDDR;
}

static inline void PINS_GPIO_SetPinDirection(GPIO_Type * const base,
                                             pins_channel_type_t pin,
                                             pins_level_type_t direction)
{
    pins_channel_type_t pinsDirections = (pins_channel_type_t)base->PDDR;
    pinsDirections &= (pins_channel_type_t)(~((pins_channel_type_t)1U << pin));
    pinsDirections |= (pins_channel_type_t)((pins_channel_type_t)direction << pin);
    base->PDDR = GPIO_PDDR_PDD(pinsDirections);
}

static inline void PINS_GPIO_SetPinsDirection(GPIO_Type * const base,
                                              pins_channel_type_t pins)
{
    base->PDDR = GPIO_PDDR_PDD(pins);
}

#if FEATURE_PORT_HAS_INPUT_DISABLE
static inline void PINS_GPIO_SetPortInputDisable(GPIO_Type * const base,
                                                 pins_channel_type_t pins)
{
    base->PIDR = GPIO_PIDR_PID(pins);
}

static inline pins_channel_type_t PINS_GPIO_GetPortInputDisable(const GPIO_Type * const base)
{
    return (pins_channel_type_t)base->PIDR;
}
#endif 

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
static inline uint16_t REV_BIT_16(uint16_t value)
{
    uint8_t i;
    uint16_t ret = 0U;

    for (i = 0U; i < 8U; i++)
    {
        ret |= (uint16_t)((((value >> i) & 1U) << (15U - i)) | (((value << i) & 0x8000U) >> (15U - i)));
    }

    return ret;
}

#endif 

static inline void PINS_GPIO_WritePin(GPIO_Type * const base,
                                      pins_channel_type_t pin,
                                      pins_level_type_t value)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    pins_channel_type_t pinsValues = (pins_channel_type_t)base->PDOR;
    pinsValues &= (pins_channel_type_t)(~((pins_channel_type_t)1U << pin));
    pinsValues |= (pins_channel_type_t)((pins_channel_type_t)value << pin);
    base->PDOR = GPIO_PDOR_PDO(pinsValues);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    pins_channel_type_t pinsValues = (pins_channel_type_t)base->PGPDO;
    pinsValues &= (pins_channel_type_t)(~((pins_channel_type_t)1U << (15U - pin)));
    pinsValues |= (pins_channel_type_t)((pins_channel_type_t)value << (15U - pin));
    base->PGPDO = pinsValues;
#endif 
}

static inline void PINS_GPIO_WritePins(GPIO_Type * const base,
                                       pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PDOR = GPIO_PDOR_PDO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO = REV_BIT_16(pins);
#endif 
}

static inline pins_channel_type_t PINS_GPIO_GetPinsOutput(const GPIO_Type * const base)
{
    pins_channel_type_t returnValue = 0U;

#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    returnValue = (pins_channel_type_t)(base->PDOR);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    returnValue = (pins_channel_type_t)REV_BIT_16(base->PGPDO);
#endif 

    return returnValue;
}

static inline void PINS_GPIO_SetPins(GPIO_Type * const base,
                                     pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PSOR = GPIO_PSOR_PTSO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO |= REV_BIT_16(pins);
#endif 
}

static inline void PINS_GPIO_ClearPins(GPIO_Type * const base,
                                       pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PCOR = GPIO_PCOR_PTCO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO &= (pins_channel_type_t)(~REV_BIT_16(pins));
#endif 
}

static inline void PINS_GPIO_TogglePins(GPIO_Type * const base,
                                        pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PTOR = GPIO_PTOR_PTTO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO ^= REV_BIT_16(pins);
#endif 
}

static inline pins_channel_type_t PINS_GPIO_ReadPins(const GPIO_Type * const base)
{
    pins_channel_type_t returnValue = 0U;

#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    returnValue = (pins_channel_type_t)(base->PDIR);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    returnValue = (pins_channel_type_t)REV_BIT_16(base->PGPDI);
#endif 

    return returnValue;
}


#if defined(__cplusplus)
}
#endif


#endif 

