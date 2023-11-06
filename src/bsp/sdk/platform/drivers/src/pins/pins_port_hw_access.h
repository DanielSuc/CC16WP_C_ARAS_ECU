
#ifndef PINS_PORT_HW_ACCESS_H
#define PINS_PORT_HW_ACCESS_H

#include "pins_driver.h"




#if defined(__cplusplus)
extern "C" {
#endif


void PINS_Init(const pin_settings_config_t * config);

#if FEATURE_PINS_HAS_PULL_SELECTION
static inline void PINS_SetPullSel(PORT_Type * const base,
                                   uint32_t pin,
                                   port_pull_config_t pullConfig)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    switch (pullConfig)
    {
        case PORT_INTERNAL_PULL_NOT_ENABLED:
            {
                base->PCR[pin] &= ~(PORT_PCR_PE_MASK);
            }
            break;
        case PORT_INTERNAL_PULL_DOWN_ENABLED:
            {
                uint32_t regValue = base->PCR[pin];
                regValue &= ~(PORT_PCR_PS_MASK);
                regValue |= PORT_PCR_PE(1U);
                base->PCR[pin] = regValue;
            }
            break;
        case PORT_INTERNAL_PULL_UP_ENABLED:
            {
                uint32_t regValue = base->PCR[pin];
                regValue |= PORT_PCR_PE(1U);
                regValue |= PORT_PCR_PS(1U);
                base->PCR[pin] = regValue;
            }
            break;
        default:
            DEV_ASSERT(false);
            break;
    }
}

#endif 

void PINS_SetMuxModeSel(PORT_Type * const base,
                        uint32_t pin,
                        port_mux_t mux);

static inline void PINS_SetPinIntSel(PORT_Type * const base,
                                     uint32_t pin,
                                     port_interrupt_config_t intConfig)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue &= ~(PORT_PCR_IRQC_MASK);
    regValue |= PORT_PCR_IRQC(intConfig);
    base->PCR[pin] = regValue;
}

static inline port_interrupt_config_t PINS_GetPinIntSel(const PORT_Type * const base,
                                                        uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue = (regValue & PORT_PCR_IRQC_MASK) >> PORT_PCR_IRQC_SHIFT;

    return (port_interrupt_config_t)regValue;
}

static inline void PINS_ClearPinIntFlagCmd(PORT_Type * const base,
                                           uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue &= ~(PORT_PCR_ISF_MASK);
    regValue |= PORT_PCR_ISF(1U);
    base->PCR[pin] = regValue;
}

static inline void PINS_EnableDigitalFilter(PORT_Type * const base,
                                            uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    base->DFER |= (uint32_t)1U << pin;
}

static inline void PINS_DisableDigitalFilter(PORT_Type * const base,
                                             uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    base->DFER &= ~((uint32_t)1U << pin);
}

static inline void PINS_ConfigDigitalFilter(PORT_Type * const base,
                                            const port_digital_filter_config_t * const config)
{
    DEV_ASSERT(config->width <= PORT_DFWR_FILT_MASK);
    base->DFCR = PORT_DFCR_CS(config->clock);
    base->DFWR = PORT_DFWR_FILT(config->width);
}

static inline uint32_t PINS_GetPortIntFlag(const PORT_Type * const base)
{
    uint32_t regValue = base->ISFR;

    return regValue;
}

static inline void PINS_ClearPortIntFlagCmd(PORT_Type * const base)
{
    base->ISFR = PORT_ISFR_ISF_MASK;
}

void PINS_SetGlobalPinControl(PORT_Type * const base,
                              uint16_t pins,
                              uint16_t value,
                              port_global_control_pins_t halfPort);

void PINS_SetGlobalIntControl(PORT_Type * const base,
                              uint16_t pins,
                              uint16_t value,
                              port_global_control_pins_t halfPort);


#if FEATURE_PINS_HAS_OVER_CURRENT
static inline uint32_t PINS_GetOverCurPortIntFlag(const PORT_Type * const base)
{
    return ((uint32_t)(base->OCFR));
}

static inline void PINS_ClearOverCurPortIntFlag(PORT_Type * const base)
{
    base->ISFR = PORT_OCFR_OCF_MASK;
}
#endif 



#if defined(__cplusplus)
}
#endif


#endif 

