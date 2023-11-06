#ifndef _GRAPH_DEFINES_H_
#define _GRAPH_DEFINES_H_


#define MEMBITARRAY_INDICES    1
#define MEM16ARRAY_INDICES     0
#define MEM32ARRAY_INDICES     0
#define CONST32ARRAY_INDICES   0

#define MEMBITARRAY_SIZE       1
#define MEM16ARRAY_SIZE        1
#define MEM32ARRAY_SIZE        1
#define CONST32ARRAY_SIZE      1

extern uint16_t ext_graph_cycle_time;

void graphcode_init(void);
void graphcode(void);
#endif
