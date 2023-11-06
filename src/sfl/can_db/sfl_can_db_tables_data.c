#include "sfl_can_db_tables_data.h"
#include "sfl_db.h"
#include "sfl_can_db.h"
#include "sfl_bl_protocol.h"
#include "can_app.h"
#include "user_api_eeprom.h"
#include "user_code.h"
#include "sfl_bl_protocol_s32k.h"




#define CAN_RX_MB_MAX       2
#define CAN_RX_MB_IDX		1

can_db_typ can_db;
can_block_db_ram_typ can_block_db_ram[CAN_BLOCK_MAX+1] __attribute__((section(".bss_mrs")));    
extern volatile const can_datenpunkt_db_const_typ can_datenpunkt_db_const[];
extern volatile const can_block_db_const_typ can_block_db_const[];
extern volatile const can_bus_db_const_typ can_bus_db_const[];

uint8_t ext_sfl_can_stop_gw_unknown_ids[CAN_BUS_MAX] = {0u};

struct_sfl_can_fifo_frame fifo_msg_tx_can0[CAN0_TX_FIFO_SIZE] __attribute__((section(".bss_mrs")));
struct_sfl_can_fifo_frame fifo_msg_tx_can1[CAN1_TX_FIFO_SIZE] __attribute__((section(".bss_mrs")));
struct_sfl_can_fifo_frame fifo_msg_tx_can2[CAN2_TX_FIFO_SIZE] __attribute__((section(".bss_mrs")));

struct_sfl_can_fifo_frame fifo_msg_rx_can0[CAN0_RX_FIFO_SIZE] __attribute__((section(".bss_mrs")));
struct_sfl_can_fifo_frame fifo_msg_rx_can1[CAN1_RX_FIFO_SIZE] __attribute__((section(".bss_mrs")));
struct_sfl_can_fifo_frame fifo_msg_rx_can2[CAN2_RX_FIFO_SIZE] __attribute__((section(".bss_mrs")));

SFL_FIFO_CONFIG_TYPE fifo_tx_can0_config __attribute__((section(".bss_mrs")));
SFL_FIFO_CONFIG_TYPE fifo_tx_can1_config __attribute__((section(".bss_mrs")));
SFL_FIFO_CONFIG_TYPE fifo_tx_can2_config __attribute__((section(".bss_mrs")));

SFL_FIFO_CONFIG_TYPE fifo_rx_can0_config __attribute__((section(".bss_mrs")));
SFL_FIFO_CONFIG_TYPE fifo_rx_can1_config __attribute__((section(".bss_mrs")));
SFL_FIFO_CONFIG_TYPE fifo_rx_can2_config __attribute__((section(".bss_mrs")));


struct_hal_can_handle can_handle[CAN_HANDLE_MAX_NR];     

struct_can_fifo_config can_fifo_config[] =
    {
        {
            .rx_fifo_size = CAN0_RX_FIFO_SIZE,
            .tx_fifo_size = CAN0_TX_FIFO_SIZE,
            .ptr_tx_fifo_buffer = fifo_msg_tx_can0,
            .ptr_rx_fifo_buffer = fifo_msg_rx_can0,
            .rx_fifo_config = &fifo_rx_can0_config,
            .tx_fifo_config = &fifo_tx_can0_config
        },
        {
            .rx_fifo_size = CAN1_RX_FIFO_SIZE,
            .tx_fifo_size = CAN1_TX_FIFO_SIZE,
            .ptr_tx_fifo_buffer = fifo_msg_tx_can1,
            .ptr_rx_fifo_buffer = fifo_msg_rx_can1,
            .rx_fifo_config = &fifo_rx_can1_config,
            .tx_fifo_config = &fifo_tx_can1_config
        },
        {
            .rx_fifo_size = CAN2_RX_FIFO_SIZE,
            .tx_fifo_size = CAN2_TX_FIFO_SIZE,
            .ptr_tx_fifo_buffer = fifo_msg_tx_can2,
            .ptr_rx_fifo_buffer = fifo_msg_rx_can2,
            .rx_fifo_config = &fifo_rx_can2_config,
            .tx_fifo_config = &fifo_tx_can2_config
        }
    };

struct_can_fifo_config* can_fifo_config_actual[MAX_CAN_DEFAULT_SET] =
{
    &can_fifo_config[0],
    &can_fifo_config[1],
    &can_fifo_config[2]
};



#define CAN_BIOS_HAL_MAPTABLE_MAX       16



typedef struct
{
    uint8_t propseg_min;
    uint8_t propseg_max;
    uint8_t pseg1_min;
    uint8_t pseg1_max;
    uint8_t pseg2_min;
    uint8_t pseg2_max;
    uint8_t rjw_min;
    uint8_t rjw_max;
    uint16_t presc_min;
    uint16_t presc_max;
} struct_PHASE_LIMITS;

#define ARBITR_PROPSEG_MIN      (1u)
#define ARBITR_PROPSEG_MAX      (64u)
#define ARBITR_PSEG1_MIN        (1u)
#define ARBITR_PSEG1_MAX        (32u)
#define ARBITR_PSEG2_MIN        (1u)
#define ARBITR_PSEG2_MAX        (32u)
#define ARBITR_RJW_MIN          (1u)
#define ARBITR_RJW_MAX          (32u)
#define ARBITR_PREDIV_MIN       (1u)
#define ARBITR_PREDIV_MAX       (1024u)

#define DATA_PROPSEG_MIN        (0u)
#define DATA_PROPSEG_MAX        (31u)
#define DATA_PSEG1_MIN          (1u)
#define DATA_PSEG1_MAX          (8u)
#define DATA_PSEG2_MIN          (1u)
#define DATA_PSEG2_MAX          (8u)
#define DATA_RJW_MIN            (1u)
#define DATA_RJW_MAX            (8u)
#define DATA_PREDIV_MIN         (1u)
#define DATA_PREDIV_MAX         (1024u)

#ifndef STATIC_ARR_ELEMENTS_COUNT
    #define STATIC_ARR_ELEMENTS_COUNT(x)    ( sizeof(x) / sizeof(x[0]) ) 
#endif 

#define CAN_BAUD_TOL_TOINT_FACTOR   (100000u)

#define MAX(a,b)    ((a) > (b) ? (a) : (b))
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define ABS_DIFF(a,b) ( MAX(a,b) - MIN(a,b) )

#ifdef USE_PRECALCULTED_CAN_BAUDRATE_TABLES

static const uint8_t precalc_baud_map[HAL_CAN_BAUD_MAX][2] =
{
    {NONE,                     HAL_CAN_BAUD_INVALID },
    {BIOS_CAN_EXT_BAUDRATE,    HAL_CAN_BAUD_EXT     },
    {BIOS_CAN_FD_EXT_BAUDRATE, HAL_CAN_FD_BAUD_EXT  },
    {BIOS_CAN_1MBIT,           HAL_CAN_BAUD_1000    },
    {BIOS_CAN_500KBIT,         HAL_CAN_BAUD_500     },
    {BIOS_CAN_250KBIT,         HAL_CAN_BAUD_250     },
    {BIOS_CAN_125KBIT,         HAL_CAN_BAUD_125     },
    {BIOS_CAN_100KBIT,         HAL_CAN_BAUD_100     },
    {BIOS_CAN_800KBIT,         HAL_CAN_BAUD_800     },
    {BIOS_CAN_83_33KBIT,       HAL_CAN_BAUD_83      },
    {BIOS_CAN_50KBIT,          HAL_CAN_BAUD_50      },
    {BIOS_CAN_33_33KBIT,       HAL_CAN_BAUD_33      },
    {BIOS_CAN_20KBIT,          HAL_CAN_BAUD_20      },
    {BIOS_CAN_10KBIT,          HAL_CAN_BAUD_10      },
};
#endif

uint32_t calculate_can_baudrate( struct_ROLE_CAN_EXT_BAUD_DEMO* ptr_io )
{
    bool bad_input = ( ( ptr_io->inp.arbitr_baud < 10000u || ptr_io->inp.arbitr_baud > 1000000u )
                           || ( ptr_io->inp.data_baud > 0u && ptr_io->inp.data_baud < ptr_io->inp.arbitr_baud ) );
    if( bad_input )
    {
        return 1;
    }
    else
    {
    }

    uint32_t retval = 0;

    const struct_PHASE_LIMITS cphase_lims[2] =
        {
            {
                .propseg_min = ARBITR_PROPSEG_MIN, .propseg_max = ARBITR_PROPSEG_MAX,
                .pseg1_min = ARBITR_PSEG1_MIN, .pseg1_max = ARBITR_PSEG1_MAX,
                .pseg2_min = ARBITR_PSEG2_MIN, .pseg2_max = ARBITR_PSEG2_MAX,
                .rjw_min = ARBITR_RJW_MIN, .rjw_max = ARBITR_RJW_MAX,
                .presc_min = ARBITR_PREDIV_MIN, .presc_max = ARBITR_PREDIV_MAX,
            },
            {
                .propseg_min = DATA_PROPSEG_MIN, .propseg_max = DATA_PROPSEG_MAX,
                .pseg1_min = DATA_PSEG1_MIN, .pseg1_max = DATA_PSEG1_MAX,
                .pseg2_min = DATA_PSEG2_MIN, .pseg2_max = DATA_PSEG2_MAX,
                .rjw_min = DATA_RJW_MIN, .rjw_max = DATA_RJW_MAX,
                .presc_min = DATA_PREDIV_MIN, .presc_max = DATA_PREDIV_MAX,
            }
        };

    const float bus_length = 2.;
    const float bus_propag_delay = 5e-9;
    const float phys_rx_tx_delay = 150e-9;
    const float t_prop_seg = 2 * ( phys_rx_tx_delay + ( bus_length * bus_propag_delay ) );

    struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE_DEMO arbitr_params_best = { 0 }, data_params_best = { 0 };

    const uint8_t n = ( ptr_io->inp.data_baud > 0u ) ? 2u : 1u;
    uint8_t iphase;
    for( iphase = 0u; iphase < n; ++iphase )
    {
        uint32_t baud = ( CAN_FD_FRAME_PHASE_ARBITRATION == iphase ) ? ptr_io->inp.arbitr_baud : ptr_io->inp.data_baud;

        uint16_t prod_n_tq_with_divpresc = (uint16_t) ( ( (float) ptr_io->inp.can_clock ) / baud + 0.5f );

        const uint8_t n_tq_min = ( CAN_FD_FRAME_PHASE_ARBITRATION == iphase ) ? 8u : 5u;
        const uint8_t n_tq_max = ( CAN_FD_FRAME_PHASE_ARBITRATION == iphase ) ? 129u : 48u;

        uint16_t list_of_presc[30]; 

        uint16_t presc;
        uint8_t presc_cnt = 0u;
        for( presc = ( prod_n_tq_with_divpresc / n_tq_max ); presc <= ( prod_n_tq_with_divpresc / n_tq_min ); ++presc )
        {
            if( 0u == prod_n_tq_with_divpresc % presc )
            {
                uint8_t n_tq = prod_n_tq_with_divpresc / presc;
                if( n_tq_min <= n_tq && n_tq <= n_tq_max )
                {
                    list_of_presc[presc_cnt++] = presc;
                    if( STATIC_ARR_ELEMENTS_COUNT(list_of_presc) == presc_cnt )
                        break;
                }
            }
        }
        if( 0u == presc_cnt )
        {
            break;
        }
        else
        {
        }

        uint16_t k;
        for( k = 0u; k < presc_cnt; ++k )
        {
            struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE_DEMO params = { 0 };

            presc = list_of_presc[k];

            params.propseg = ( CAN_FD_FRAME_PHASE_ARBITRATION == iphase ) ? (uint8_t) ( ( t_prop_seg * ptr_io->inp.can_clock + presc - 1 ) / presc )
                                                                            : (uint8_t) ( ( phys_rx_tx_delay * ptr_io->inp.can_clock + presc - 1 ) / presc );
            if( params.propseg < cphase_lims[iphase].propseg_min || params.propseg > cphase_lims[iphase].propseg_max )
                continue;

            uint8_t n_tq = (uint8_t) ( prod_n_tq_with_divpresc / presc );

            uint8_t phase1_phase2 = n_tq - 1u - params.propseg;
            params.propseg -= 2u - MIN( 2u, phase1_phase2 ); 
            phase1_phase2 = n_tq - 1u - params.propseg;

            int8_t smp_wanted = ( CAN_FD_FRAME_PHASE_ARBITRATION == iphase ) ? ptr_io->inp.arbitr_smp : ptr_io->inp.data_smp;

            params.pseg1 = (uint8_t) ( ( smp_wanted * n_tq ) / 100. + 0.5f ) - params.propseg - 1u;
            params.pseg2 = phase1_phase2 - params.pseg1;

            if( params.pseg1 > cphase_lims[iphase].pseg1_max )
            {
                uint8_t diff = params.pseg1 - cphase_lims[iphase].pseg1_max;
                if( params.propseg + diff < cphase_lims[iphase].propseg_max )
                {
                    params.propseg += diff;
                    params.pseg1 -= diff;
                }
                else
                {
                }
            }
            else if( params.propseg > cphase_lims[iphase].propseg_max )
            {
                uint8_t diff = params.propseg - cphase_lims[iphase].propseg_max;
                if( params.pseg1 + diff < cphase_lims[iphase].pseg1_max )
                {
                    params.propseg -= diff;
                    params.pseg1 += diff;
                }
                else
                {
                }
            }
            else
            {
            }

            params.rjw = ( CAN_FD_FRAME_PHASE_ARBITRATION == iphase ) ? MIN( 16u, MIN(params.pseg1, params.pseg2) )
                                                                            : MIN( 4u, MIN(params.pseg1, params.pseg2) );

            if( ( params.propseg < cphase_lims[iphase].propseg_min ) || ( params.propseg > cphase_lims[iphase].propseg_max )
                || ( params.pseg1 < cphase_lims[iphase].pseg1_min ) || ( params.pseg1 > cphase_lims[iphase].pseg1_max )
                || ( params.pseg2 < cphase_lims[iphase].pseg2_min ) || ( params.pseg2 > cphase_lims[iphase].pseg2_max )
                || ( params.rjw < cphase_lims[iphase].rjw_min ) || ( params.rjw > cphase_lims[iphase].rjw_max )
                || ( presc < cphase_lims[iphase].presc_min ) || ( presc > cphase_lims[iphase].presc_max ) )
            {
                continue;
            }
            else
            {
            }

            uint16_t tol1 = ( ( CAN_BAUD_TOL_TOINT_FACTOR * params.rjw ) / ( 2u * ( 10u * n_tq ) ) );
            uint16_t tol2 = ( ( CAN_BAUD_TOL_TOINT_FACTOR * MIN( params.pseg1, params.pseg2 ) ) / ( 2u * ( 13u * n_tq - params.pseg2 ) ) );
            params.tolerance = MIN( tol1, tol2 );
            params.smp = (uint8_t) ( ( 100u * ( 1u + params.propseg + params.pseg1 ) ) / n_tq );
            params.presc = presc;


            if( n_tq != ( params.propseg + params.pseg1 + params.pseg2 + 1u ) )
            {
                continue;
            }
            else
            {
            }

            switch( iphase )
            {
                case CAN_FD_FRAME_PHASE_ARBITRATION:
                {
                    uint8_t diff_prev = ABS_DIFF( smp_wanted, arbitr_params_best.smp ), diff_curr = ABS_DIFF( smp_wanted, params.smp );
                    if( ( diff_prev > diff_curr ) || ( ( diff_prev == diff_curr ) && ( arbitr_params_best.tolerance < params.tolerance ) ) )
                    {
                        arbitr_params_best = params;
                    }
                    else
                    {
                    }
                }
                break;

                case CAN_FD_FRAME_PHASE_DATA:
                {
                    uint8_t diff_prev = ABS_DIFF( smp_wanted, data_params_best.smp ), diff_curr = ABS_DIFF( smp_wanted, params.smp );
                    if( ptr_io->inp.data_baud > 1000000u )
                    {
                        uint8_t pseg_prev = data_params_best.pseg1 + data_params_best.pseg2;
                        uint8_t pseg_curr = params.pseg1 + params.pseg2;
                        if( ( pseg_curr > pseg_prev ) || ( diff_prev > diff_curr ) )
                        {
                            data_params_best = params;
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                        if( ( diff_prev > diff_curr ) || ( ( diff_prev == diff_curr ) && ( data_params_best.tolerance < params.tolerance ) ) )
                        {
                            data_params_best = params;
                        }
                        else
                        {
                        }
                    }
                }
                break;
            }
        }
    }

    if( arbitr_params_best.tolerance > 0u && arbitr_params_best.smp > 0u )
    {
        if( ptr_io->inp.data_baud > 0u )
        {
            if( data_params_best.tolerance > 0u && data_params_best.smp > 0u )
            {
                ptr_io->out.phase[CAN_FD_FRAME_PHASE_ARBITRATION] = arbitr_params_best;
                ptr_io->out.phase[CAN_FD_FRAME_PHASE_DATA] = data_params_best;
                retval = 0;
            }
            else
            {
            }
        }
        else
        {
            ptr_io->out.phase[CAN_FD_FRAME_PHASE_ARBITRATION] = arbitr_params_best;
            memset( &data_params_best, 0, sizeof( data_params_best ) );
            ptr_io->out.phase[CAN_FD_FRAME_PHASE_DATA] = data_params_best;
            retval = 0;
        }
    }
    else
    {
    }

    return retval;
}

uint32_t set_can_baudrate_timing( hal_can_time_segment *ptr_tseg, const struct_ROLE_CAN_EXT_BAUD_OUTPUT_PHASE_DEMO *params, enum_PHY_CAN_FRAME_PHASE_DEMO iphase )
{
    if( ( ptr_tseg->prop_seg || ptr_tseg->phase_seg1 || ptr_tseg->phase_seg1
        || ptr_tseg->pre_divider || ptr_tseg->jumpwidth ) == 0 )
    {
        return 1;
    }
    ptr_tseg->prop_seg = params->propseg - 1;
    ptr_tseg->phase_seg1 = params->pseg1 - 1;
    ptr_tseg->phase_seg2 = params->pseg2 - 1;
    ptr_tseg->pre_divider = params->presc - 1;
    ptr_tseg->jumpwidth = params->rjw - 1;

    if( CAN_FD_FRAME_PHASE_DATA == iphase )
    {
        ++ptr_tseg->prop_seg;
    }
    else
    {
    }

    return 0;
}

uint8_t sfl_can_db_tables_convert_baud( uint8_t const baudrate, uint8_t ident )
{
    uint8_t ret = 0;		
    ident = ident & 0x01;	

    for( uint8_t i = 0; i < HAL_CAN_BAUD_MAX; ++i )
    {
        if( precalc_baud_map[i][ident] == baudrate )
        {
            ret = precalc_baud_map[i][ !ident];
        }
    }

    return ret;
}

void sfl_can_db_tables_data_init_baudrate( struct_hal_can_handle can_bus_handle, const can_bus_db_const_typ can_config )
{
    can_bus_handle.can_baudrate = HAL_CAN_BAUD_INVALID;
    can_bus_handle.can_fd_data_baudrate = HAL_CAN_BAUD_INVALID;

    can_bus_handle.can_handle_number = can_config.hw_module_id;

    if( can_config.hw_module_active == TRUE )
    {
        can_bus_handle.can_ext_baudrate.phase_seg1 = can_config.baudrate.t_seg1;
        can_bus_handle.can_ext_baudrate.phase_seg2 = can_config.baudrate.t_seg2;
        can_bus_handle.can_ext_baudrate.pre_divider = can_config.baudrate.pre;
        can_bus_handle.can_ext_baudrate.prop_seg = can_config.baudrate.prop;
        can_bus_handle.can_ext_baudrate.jumpwidth = can_config.baudrate.sj;

        if( can_config.can_fd_capability == true )
        {
            can_bus_handle.can_fd_ext_baudrate.phase_seg1 = can_config.baudrate_fd_data.t_seg1;
            can_bus_handle.can_fd_ext_baudrate.phase_seg2 = can_config.baudrate_fd_data.t_seg2;
            can_bus_handle.can_fd_ext_baudrate.pre_divider = can_config.baudrate_fd_data.pre;
            can_bus_handle.can_fd_ext_baudrate.prop_seg = can_config.baudrate_fd_data.prop;
            can_bus_handle.can_fd_ext_baudrate.jumpwidth = can_config.baudrate_fd_data.sj;

            can_bus_handle.can_baudrate = HAL_CAN_FD_BAUD_EXT;
            can_bus_handle.can_fd_data_baudrate = HAL_CAN_FD_BAUD_EXT;
        }
        else
        {

            can_bus_handle.can_baudrate = HAL_CAN_BAUD_EXT;
            can_bus_handle.can_fd_data_baudrate = HAL_CAN_BAUD_INVALID;

            for( uint8_t i = 0; i < HAL_CAN_BAUD_MAX; ++i )
            {
                if( precalc_baud_map[i][0] == (uint8_t) can_config.bios_baudrate_id )
                {
                    can_bus_handle.can_baudrate = precalc_baud_map[i][1];
                }
            }
        }

#if (CAN_BL_BAUDRATE_MODE == 1) 
        uint8_t eeprom_baudrate = sfl_bl_protocol_s32k_get_baudrate();

        can_bus_handle.can_baudrate = sfl_can_db_tables_convert_baud(eeprom_baudrate, 0);

        hal_can_set_baudrate(&can_bus_handle, can_bus_handle.can_baudrate );
        hal_can_set_fd_data_baudrate(&can_bus_handle, can_bus_handle.can_fd_data_baudrate);

        #else 
            hal_can_set_baudrate(&can_bus_handle, can_bus_handle.can_baudrate );
            hal_can_set_fd_data_baudrate(&can_bus_handle, can_bus_handle.can_fd_data_baudrate);

            if( can_config.bios_baudrate_id < BIOS_CAN_FD_START_ID)
            {
                (void)sfl_bl_protocol_s32k_set_baudrate(&can_bus_handle, can_config.bios_baudrate_id);
            }
            else
            {
            	if((can_config.bios_baudrate_id >= BIOS_CAN_FD_125_250) && (can_config.bios_baudrate_id <= BIOS_CAN_FD_125_5000))
            	{
            		sfl_bl_protocol_s32k_set_baudrate(&can_bus_handle, BIOS_CAN_125KBIT);
            	}
            	else if((can_config.bios_baudrate_id >= BIOS_CAN_FD_250_500) && (can_config.bios_baudrate_id <= BIOS_CAN_FD_250_5000))
            	{
            		sfl_bl_protocol_s32k_set_baudrate(&can_bus_handle, BIOS_CAN_250KBIT);
            	}
            	else if((can_config.bios_baudrate_id >= BIOS_CAN_FD_500_800) && (can_config.bios_baudrate_id <= BIOS_CAN_FD_500_5000))
            	{
            		sfl_bl_protocol_s32k_set_baudrate(&can_bus_handle, BIOS_CAN_500KBIT);
            	}
            	else if((can_config.bios_baudrate_id >= BIOS_CAN_FD_800_1000) && (can_config.bios_baudrate_id <= BIOS_CAN_FD_800_5000))
            	{
            		sfl_bl_protocol_s32k_set_baudrate(&can_bus_handle, BIOS_CAN_800KBIT);
            	}
            	else if((can_config.bios_baudrate_id >= BIOS_CAN_FD_1000_2000) && (can_config.bios_baudrate_id <= BIOS_CAN_FD_1000_5000))
            	{
            		sfl_bl_protocol_s32k_set_baudrate(&can_bus_handle, BIOS_CAN_1MBIT);
            	}
            }
        #endif 
    } 
}

void sfl_can_db_tables_data_init( void )
{
    uint16_t i;

    can_db.DP_MAX = CAN_DP_MAX;
    can_db.BUS_MAX = CAN_BUS_MAX;
    can_db.BLOCK_MAX = CAN_BLOCK_MAX;
    can_db.GATEWAY_DB_MAX = CAN_GATEWAY_DB_MAX; 
    can_db.BAUDRATE = CAN_BAUDRATE; 
    can_db.BAUDRATE = CAN_BAUDRATE; 
    can_db.BUS_1 = CAN_BUS_0;	

    for( i = 0; i < can_db.BLOCK_MAX; i++ )
    {
        if( can_block_db_const[i].mux_length )
        {
            sfl_db_put_signal_value_to_data_block( can_block_db_const[i].mux_val, can_block_db_ram[i].msg.data, can_block_db_const[i].mux_start, can_block_db_const[i].mux_length, DF_INTEL );
        }
    }

    for( i = 0; i < CAN_DP_MAX; i++ )
    {
        can_datenpunkt_db_const_typ dp = can_datenpunkt_db_const[i];

        if( can_block_db_const[dp.nr_can_block].timeout_ms > 0 )
        {
            sfl_db_put_signal_value_to_data_block( dp.init_value, can_block_db_ram[dp.nr_can_block].msg.data, dp.pos_bit_0, dp.bit_laenge, dp.data_format );
            can_block_db_ram[dp.nr_can_block].failsafe = 1;
        }
        else
        {
            can_block_db_ram[dp.nr_can_block].failsafe = 0;           
        }

        can_block_db_ram[dp.nr_can_block].expired = 0;
    }

    return;
}

void sfl_can_db_fifo_init( void )
{
    uint8_t i = 0;
    for( i = 0; i < CAN_BUS_MAX; i++ )
    {
        sfl_can_get_handle( i, &can_handle[i] );

        can_handle[i].can_handle_number = can_bus_db_const[i].hw_module_id;

        if( can_bus_db_const[i].hw_module_active == TRUE )
        {
            sfl_can_db_tx_fifo_init( i );                         
            sfl_can_db_rx_fifo_init( i );                         

        }
    }

}

void sfl_can_db_init( can_db_filter_typ* can_db_filter_config )
{
    can_db_filter_typ* ptr_can_db_filter_config;

    uint8_t id_type_mb[sizeof( can_db_filter_config->filter ) / sizeof( can_db_filter_config->filter[0] )] = { STAND_ID };

    for( uint8_t i = 0; i < CAN_BUS_MAX; i++ )
    {
        can_handle[i].can_handle_number = can_bus_db_const[i].hw_module_id;

        can_handle[i].is_can_listen_only = can_bus_db_const[i].listen_only_mode_active;

        can_handle[i].is_can_fd = FALSE;

        if( ( can_bus_db_const[i].hw_module_active == TRUE ) )
        {
            if( can_bus_db_const[i].can_fd_capability == TRUE )
            {
                if( can_bus_db_const[i].bios_baudrate_id > BIOS_CAN_FD_START_ID )
                {
                    can_handle[i].is_can_fd = TRUE;

                }
                else
                {
                }

            }
            else
            {
            }
            hal_can_init( &can_handle[i], can_bus_db_const[i].hw_module_id, FALSE );

            ptr_can_db_filter_config = &can_db_filter_config[i];

            if( ( ( IS_GW_INPUT ) == can_bus_db_const[i].gw_input ) || ( can_db_filter_config == NULL ) ||
                ( can_db_filter_config[i].mask_division == BIOS_CAN_ID_ALL_OPEN ) )
            {
                ptr_can_db_filter_config->filter[0] = ptr_can_db_filter_config->filter[1] = 0x0;
                ptr_can_db_filter_config->mask[0] = 0x7FF;                                  
                ptr_can_db_filter_config->mask[1] = 0x1FFFFFFF;                             

                id_type_mb[0] = STAND_ID;                                               
                id_type_mb[1] = EXT_ID;                                                 

            }
            else
            {
                switch( can_db_filter_config[i].mask_division )
                {
                    case BIOS_CAN_ID_NORM_A_AND_B:

                        id_type_mb[0] = STAND_ID;  
                        id_type_mb[1] = STAND_ID;  
                    break;

                    case BIOS_CAN_ID_NORM_A_EXT_B:

                        id_type_mb[0] = STAND_ID;  
                        id_type_mb[1] = EXT_ID;    
                    break;

                    case BIOS_CAN_ID_EXT_A_AND_B:

                        id_type_mb[0] = EXT_ID;    
                        id_type_mb[1] = EXT_ID;    
                    break;

                    case BIOS_CAN_ID_ALL_CLOSED:
                        id_type_mb[0] = NO_ID;     
                        id_type_mb[1] = NO_ID;     
                    break;

                    default:
                        ptr_can_db_filter_config->filter[0] = ptr_can_db_filter_config->filter[1] = 0x0;
                        ptr_can_db_filter_config->mask[0] = 0x7FF;                                  
                        ptr_can_db_filter_config->mask[1] = 0x1FFFFFFF;                             

                        id_type_mb[0] = STAND_ID;                                               
                        id_type_mb[1] = EXT_ID;                                                 
                    break;

                } 

            } 

            sfl_can_db_config_mb_set_filter_mask( &can_handle[i], ptr_can_db_filter_config, id_type_mb );
        }
        else
        {
        }
    } 

    (void) sfl_bl_protocol_s32k_rx_tx_init( BL_CAN_RX_IDX, BL_CAN_TX_IDX );
}
void sfl_can_rx_int_enable( uint8_t instance, uint32_t buffIdx )
{
    struct_hal_can_frame_t temp_can_msg = { 0 };

    can_handle[instance].can_handle_mb_idx = buffIdx;

    hal_can_receive( &can_handle[instance], &temp_can_msg );
}

void sfl_can_get_handle( uint8_t interface, struct_hal_can_handle* ptr_handle )
{

    ptr_handle->can_handle_ptr = NULL;

    if( interface < CAN_HANDLE_MAX_NR )
    {
        *ptr_handle = can_handle[interface];
        ptr_handle->can_handle_ptr = ptr_handle;
    }
    else
    {
    }
}

void sfl_can_db_config_mb_set_filter_mask( struct_hal_can_handle* const can_handle, const can_db_filter_typ* can_db_filter_config, const uint8_t id_type_mb[] )
{
    uint8_t mbs_to_iterate = sizeof( can_db_filter_config->filter ) / sizeof( can_db_filter_config->filter[0] );

    struct_hal_can_filter hal_can_filter_config = { 0 };
    for( uint8_t i = 0; i < mbs_to_iterate; i++ )
    {
        if( id_type_mb[i] == NO_ID )
        {
        }
        else
        {
            can_handle->can_handle_mb_idx = ( i + CAN_RX_MB_IDX );
            hal_can_filter_config.id_type = id_type_mb[i];
            hal_can_filter_config.can_id = can_db_filter_config->filter[i];
            hal_can_filter_config.can_mask = ~can_db_filter_config->mask[i];
            hal_can_set_filter( can_handle, &hal_can_filter_config );              
        }
    }
}

uint8_t sfl_can_db_get_fifo_size( uint8_t bus_id, uint8_t tx_or_rx )
{
    uint8_t temp[2] = { 0 }, ret_val = 0;

    if( bus_id < CAN_BUS_MAX && tx_or_rx < 2 )
    {
        switch( bus_id )
        {
            case ( 0 ):
                temp[0] = CAN0_RX_FIFO_SIZE;
                temp[1] = CAN0_TX_FIFO_SIZE;
            break;
            case ( 1 ):
                temp[0] = CAN1_RX_FIFO_SIZE;
                temp[1] = CAN1_TX_FIFO_SIZE;
            break;
            case ( 2 ):
                temp[0] = CAN2_RX_FIFO_SIZE;
                temp[1] = CAN2_TX_FIFO_SIZE;
            break;
            default:    
            break;
        }

        ret_val = temp[tx_or_rx];
    }
    else
    {
        ret_val = 0; 
    }

    return ret_val;
}

