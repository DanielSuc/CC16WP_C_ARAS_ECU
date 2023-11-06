
#ifndef SRC_ROLE_PROTOCOL_ALLOC_H_
#define SRC_ROLE_PROTOCOL_ALLOC_H_

void* static_alloc(uint32_t size);

void* static_calloc(uint32_t num_elements, uint32_t size_element);

void static_free(void *p);


#endif 

