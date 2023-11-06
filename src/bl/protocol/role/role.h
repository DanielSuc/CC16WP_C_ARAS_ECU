

#ifndef MRS_ROLE_H_
#define MRS_ROLE_H_

#if defined(__cplusplus)
extern "C" {
#endif


#define ROLE_PARAM_NONE             ((uint32_t)0u)              



#ifndef ROLE_DO_PARAM_LIST_ANY
#define ROLE_DO_PARAM_LIST_ANY
#endif 

#ifndef ROLE_DO_PARAM_LIST_BOARD
#define ROLE_DO_PARAM_LIST_BOARD
#endif 

#ifndef ROLE_DO_PARAM_LIST_SYS
#define ROLE_DO_PARAM_LIST_SYS
#endif 

#ifndef ROLE_DO_PARAM_LIST_TICK
#define ROLE_DO_PARAM_LIST_TICK
#endif 

#ifndef ROLE_DO_PARAM_LIST_FLASH
#define ROLE_DO_PARAM_LIST_FLASH
#endif 

#ifndef ROLE_DO_PARAM_LIST_CAN
#define ROLE_DO_PARAM_LIST_CAN
#endif 

#ifndef ROLE_DO_PARAM_LIST_SPI
#define ROLE_DO_PARAM_LIST_SPI
#endif 

#ifndef ROLE_DO_PARAM_LIST_BL_PROTOCOL
#define ROLE_DO_PARAM_LIST_BL_PROTOCOL
#endif 

#ifndef ROLE_DO_PARAM_LIST_BL_WBX
#define ROLE_DO_PARAM_LIST_BL_WBX
#endif 

#ifndef ROLE_DO_PARAM_LIST_SPI_PROTOCOL
#define ROLE_DO_PARAM_LIST_SPI_PROTOCOL
#endif 


enum_CODE role_dothis(role_id_t id, role_do_id_t typeid, role_do_param_t type_num, ...);

void role_play(void);


#define role_dothis(handle, opt, type_num, param) role_dothis(handle, opt, type_num, param)


#if __STDC_VERSION__ >= 201112L 
#define ROLE_PARAM_TO_NUM(param) _Generic( (param), \
        ROLE_DO_PARAM_LIST_ANY \
        ROLE_DO_PARAM_LIST_BOARD \
        ROLE_DO_PARAM_LIST_SYS \
        ROLE_DO_PARAM_LIST_TICK \
        ROLE_DO_PARAM_LIST_FLASH \
        ROLE_DO_PARAM_LIST_CAN \
		ROLE_DO_PARAM_LIST_SPI \
        ROLE_DO_PARAM_LIST_BL_PROTOCOL \
        ROLE_DO_PARAM_LIST_BL_WBX \
		ROLE_DO_PARAM_LIST_SPI_PROTOCOL \
        )

#ifdef __GNUC__

#define role_do(role, opt, param) __extension__ ({ \
                            _Static_assert((uint32_t)(ROLE_DO_PARAM(opt)) == (uint32_t)(ROLE_PARAM_TO_NUM(param)), \
                                            "Role action ID does not match the parameter type"); \
                            role_dothis(role, opt, ROLE_PARAM_TO_NUM(param), param); \
                                    })
#else
#define role_do(role, opt, param) role_dothis(role, opt, ROLE_PARAM_TO_NUM(param), param)

#endif 

#else 

#error "C11 standard is needed. Try to compile with -std=c11 flag."

#endif 

#ifdef __cplusplus
}
#endif

#endif 

