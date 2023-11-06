
#ifndef PHY_H
#define PHY_H

#include <stdint.h>
#include <stdbool.h>
#include "status.h"



typedef enum
{
    PHY_SPEED_RESERVED = 3,  
    PHY_SPEED_1_GBPS   = 2,  
    PHY_SPEED_100_MBPS = 1,  
    PHY_SPEED_10_MBPS  = 0   
} phy_speed_t;

typedef enum
{
    PHY_ROLE_AUTO   = 2,  
    PHY_ROLE_MASTER = 1,  
    PHY_ROLE_SLAVE  = 0   
} phy_role_t;

typedef enum
{
    PHY_LOCATION_EXTERNAL = 1,  
    PHY_LOCATION_INTERNAL = 0   
} phy_location_t;

typedef enum
{
    PHY_LOOPBACK_REMOTE   = 3,  
    PHY_LOOPBACK_EXTERNAL = 2,  
    PHY_LOOPBACK_INTERNAL = 1,  
    PHY_LOOPBACK_NONE     = 0   
} phy_loopback_t;

typedef struct
{
    uint32_t oui;         
    uint8_t  typeNo;      
    uint8_t  revisionNo;  
} phy_id_t;

typedef struct
{
    uint8_t type;             
    uint32_t addr;            
    phy_location_t location;  
    phy_role_t role;          
    uint8_t enetInstance;     
    void (*linkUpEventCB)(uint8_t phy);       
    void (*linkDownEventCB)(uint8_t phy);     
    void (*autonegCompleteCB)(uint8_t p_phy); 
    void (*autonegFailedCB)(uint8_t p_phy);   
    uint32_t privateData;     
} phy_config_t;

typedef struct
{
    status_t (*init)(uint8_t phy);
    status_t (*reset)(uint8_t phy);
    status_t (*mainFunction)(uint8_t phy);
    status_t (*getId)(uint8_t phy, phy_id_t* p_id);
    status_t (*getLinkStatus)(uint8_t phy, bool* p_linkUp);
    status_t (*getLinkSpeed)(uint8_t phy, phy_speed_t* p_speed);
    status_t (*suspend)(uint8_t p_phy);
    status_t (*resume)(uint8_t p_phy);
    status_t (*sleep)(uint8_t p_phy);
    status_t (*wakeup)(uint8_t p_phy);
    status_t (*setRole)(uint8_t phy, phy_role_t role);
    status_t (*setLoopback)(uint8_t phy, phy_loopback_t loopbackMode);
    status_t (*enableInterrupts)(uint8_t p_phy);
    status_t (*handleInterrupt)(uint8_t p_phy);
    status_t (*enableAutoneg)(uint8_t p_phy);
    status_t (*disableAutoneg)(uint8_t p_phy);
    status_t (*restartAutoneg)(uint8_t p_phy);
} phy_driver_t;

extern phy_config_t* g_phyConfig;


#ifdef __cplusplus
extern "C"{
#endif


status_t PHY_FrameworkInit(phy_config_t *phyConfig, phy_driver_t **phyDrivers);



status_t PHY_Init(uint8_t phy);

status_t PHY_Reset(uint8_t phy);

status_t PHY_MainFunction(uint8_t phy);

status_t PHY_GetId(uint8_t phy, phy_id_t *id);

status_t PHY_GetLinkStatus(uint8_t phy, bool *linkUp);

status_t PHY_GetLinkSpeed(uint8_t phy, phy_speed_t *speed);

status_t PHY_Suspend(uint8_t phy);

status_t PHY_Resume(uint8_t phy);

status_t PHY_Sleep(uint8_t phy);

status_t PHY_Wakeup(uint8_t phy);

status_t PHY_SetRole(uint8_t phy, phy_role_t role);

status_t PHY_SetLoopback(uint8_t phy, phy_loopback_t loopbackMode);

status_t PHY_EnableInterrupts(uint8_t phy);

status_t PHY_HandleInterrupt(uint8_t phy);



status_t PHY_EnableAutoneg(uint8_t phy);

status_t PHY_DisableAutoneg(uint8_t phy);

status_t PHY_RestartAutoneg(uint8_t phy);



status_t PHY_Write(uint8_t phy, uint8_t registerAddr, uint16_t value);

status_t PHY_Read(uint8_t phy, uint8_t registerAddr, uint16_t *value);

status_t PHY_RMR(uint8_t phy, uint8_t registerAddr, uint16_t value, uint16_t mask);


#ifdef __cplusplus
}
#endif


#endif 


