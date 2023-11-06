
#ifndef SRC_ROLE_PHY_TICK_H_
#define SRC_ROLE_PHY_TICK_H_

#if defined(__cplusplus)
extern "C" {
#endif


#define ROLE_DO_PARAM_LIST_TICK \
    , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_TICK_DELAY*,   ROLE_TICK_PARAM_DELAY) \
    , ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_TICK_STAMP*,   ROLE_TICK_PARAM_STAMP) \
	, ROLE_MAP_REAL_PARAM_TO_NUM(struct_ROLE_TICK_TWO_DELAYS*, ROLE_TICK_PARAM_TWO_DELAYS)


typedef enum
{
    ROLE_TICK_PARAM_DELAY = ROLE_COMPOSE_DO_PARAM_BASE(ROLE_TYPE_TICK),
    ROLE_TICK_PARAM_STAMP,
    ROLE_TICK_PARAM_TWO_DELAYS,

} enum_ROLE_TIMER_DO_PARAM;

typedef enum
{
    ROLE_TIMER_START_DELAY = ROLE_COMPOSE_DO_ID(ROLE_TYPE_TICK,             0u, ROLE_TICK_PARAM_DELAY),
    ROLE_TIMER_CHECK_TIMEOUT = ROLE_COMPOSE_DO_ID(ROLE_TYPE_TICK,           1u, ROLE_TICK_PARAM_DELAY),
    ROLE_TIMER_START_DELAY_BLOCKING = ROLE_COMPOSE_DO_ID(ROLE_TYPE_TICK,    2u, ROLE_TICK_PARAM_DELAY),
    ROLE_TIMER_RECORD_TIMESTAMP = ROLE_COMPOSE_DO_ID(ROLE_TYPE_TICK,        3u, ROLE_TICK_PARAM_STAMP),
    ROLE_TIMER_CHECK_ELAPSED_PERIOD = ROLE_COMPOSE_DO_ID(ROLE_TYPE_TICK,    4u, ROLE_TICK_PARAM_STAMP),
    ROLE_TIMER_ELAPSED_MS_FROM_START = ROLE_COMPOSE_DO_ID(ROLE_TYPE_TICK,   5u, ROLE_ANY_PARAM_UINT32PTR),
    ROLE_TIMER_UPDATE_DELAY_IF_NEW_WILL_LAST_LONGER = ROLE_COMPOSE_DO_ID(ROLE_TYPE_TICK,   6u, ROLE_TICK_PARAM_TWO_DELAYS),
} enum_ROLE_TIMER_DO_ID;


typedef enum
{
    TICK_PRECISION_1US               = 0u,   
    TICK_PRECISION_10US                  ,   
    TICK_PRECISION_100US                 ,   
    TICK_PRECISION_1MS                   ,   
    TICK_PRECISION_10MS                  ,   
    TICK_PRECISION_100MS                 ,   
    TICK_PRECISION_1S                    ,   

    TICK_PRECISION_DUMMY_END
} enum_ROLE_TICK_PRECISION;

typedef struct
{
    uint32_t us_lo;
    uint32_t us_hi;
} struct_ROLE_PHY_TIMESTAMP;

typedef struct
{
	uint16_t delay;
	enum_ROLE_TICK_PRECISION precision;
	bool b_elapsed;
	struct_ROLE_PHY_TIMESTAMP endtime;
} struct_ROLE_TICK_DELAY;

typedef struct
{
	uint16_t period;
	enum_ROLE_TICK_PRECISION precision;
	bool b_elapsed;
	struct_ROLE_PHY_TIMESTAMP timestamp;
} struct_ROLE_TICK_STAMP;

typedef struct
{
	struct_ROLE_TICK_DELAY *running_delay;
	struct_ROLE_TICK_DELAY *new_delay;
} struct_ROLE_TICK_TWO_DELAYS;


void role_phy_tick_constructor(role_id_t id, pf_role_constructor parent);


#ifdef __cplusplus
}
#endif

#endif 

