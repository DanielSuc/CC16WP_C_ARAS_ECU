
#ifndef SRC_ROLE_BASE_H_
#define SRC_ROLE_BASE_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct struct_ROLE_VTBL struct_ROLE_VTBL;

struct struct_ROLE_VTBL
{
    enum_CODE (*dothis)(role_id_t, role_do_id_t, va_list *ptr_arg_list);
    void (*play)(role_id_t);
};

struct struct_ROLE
{
    struct_ROLE_VTBL    *vptr;
    const role_id_t      id;
    enum_ROLE_STATE      state;
};


#ifdef __cplusplus
}
#endif

#endif 

