#ifndef _NPCS_H_
#define _NPCS_H_

#include "../position/position.h"

struct npcs {
    int count;
    struct position** positions;
};

struct npcs* init_npcs(int num_npcs);
void destroy_npcs(struct npcs *npcs);

#endif

