
#ifndef SRC_RING_H_
#define SRC_RING_H_


#if defined(__cplusplus)
extern "C" {
#endif

typedef uint8_t span_t;

typedef struct
{
    uint8_t b_visited;
    uint8_t b_hidden;
} struct_RING_FEATURE;

typedef struct
{
    void * const ptr_buff;
    span_t head;
    span_t tail;
    span_t n;
    span_t const size;
    span_t const elem_size;
} struct_RING;

#define DEFINE_STATIC_RINGBUFFER(type, name, sz)    \
                                                    \
    typedef struct                                  \
    {                                               \
        type obj;                                   \
        struct_RING_FEATURE prop;                   \
    } type ## _ ## name ## _visitable;   \
                                                    \
    static type ## _ ## name ## _visitable mgl_ring_buff_ ## type ## _ ## name [sz]; \
    static struct_RING name = {                     \
        .ptr_buff = (void*)(& mgl_ring_buff_ ## type ## _ ## name [0]), \
        .head = 0u,                                 \
        .tail = 0u,                                 \
        .n = 0u,                                    \
        .size = sz,                                 \
        .elem_size = sizeof(type)                   \
    }



span_t    ringbuff_get_count        (struct_RING *ptr_ring) __attribute__((unused));

void      ringbuff_reset            (struct_RING *ptr_ring) __attribute__((unused));

enum_CODE ringbuff_push             (struct_RING *ptr_ring, void *ptr_data, uint8_t b_hidden) __attribute__((unused));

enum_CODE ringbuff_pop              (struct_RING *ptr_ring, void *ptr_data) __attribute__((unused));

enum_CODE ringbuff_read_shadow      (struct_RING *ptr_ring, void *ptr_data) __attribute__((unused));

enum_CODE ringbuff_read_shadow_ptr  (struct_RING *ptr_ring, void **ptr_ptr_data) __attribute__((unused));

enum_CODE ringbuff_pop_if_visited   (struct_RING *ptr_ring) __attribute__((unused));

uint8_t   ringbuff_is_node_visited  (struct_RING *ptr_ring) __attribute__((unused));

enum_CODE ringbuff_unhide_if_hidden (struct_RING *ptr_ring);


#ifdef __cplusplus
}
#endif

#endif 

