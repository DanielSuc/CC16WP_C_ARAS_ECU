
#ifndef SRC_ROLE_PHY_SPI_H_
#define SRC_ROLE_PHY_SPI_H_

#if defined(__cplusplus)
extern "C" {
#endif


#if defined(SPECIFICS_CONNECTED_LOGGER) || defined(SPECIFICS_CONNECTED_WALLBOX)
#if !defined(ROLE_MINIMAL)


#define ROLE_DO_PARAM_LIST_SPI \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_SPI_SETTINGS*, ROLE_SPI_PARAM_SETTINGS) \
		, ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_SPI_MSG*, ROLE_SPI_PARAM_MSG)


typedef enum
{
	ROLE_SPI_PARAM_SETTINGS = ROLE_COMPOSE_DO_PARAM_BASE(ROLE_TYPE_SPI),
	ROLE_SPI_PARAM_MSG

} enum_ROLE_SPI_DO_PARAM;


typedef enum
{
      ROLE_SPI_CONFIGURE     = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI,    0u,     ROLE_SPI_PARAM_SETTINGS)
	, ROLE_SPI_TXRX_MSG      = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI,    1u,     ROLE_SPI_PARAM_MSG)
    , ROLE_SPI_CAN_ID        = ROLE_COMPOSE_DO_ID(ROLE_TYPE_SPI,    2u,     ROLE_ANY_PARAM_UINT32)

} enum_ROLE_SPI_DO_ID;

#endif 
#endif 

typedef struct
{
	uint8_t bus;
	uint16_t cs;
	uint32_t partition_offset;
	uint32_t baudrate;
	uint8_t clock_pol_phase;
	uint8_t cs_pol;
	uint8_t frame_sz;
} __attribute__((packed)) struct_ROLE_SPI_SETTINGS;

typedef struct
{
	uint8_t *ptr_tx;
	uint8_t *ptr_rx;
	uint32_t len;
} struct_ROLE_SPI_MSG;

#if defined(SPECIFICS_CONNECTED_LOGGER) || defined(SPECIFICS_CONNECTED_WALLBOX)
#if !defined(ROLE_MINIMAL)

void role_phy_spi_constructor(role_id_t id, pf_role_constructor parent);

#endif 
#endif 

#ifdef __cplusplus
}
#endif

#endif 

