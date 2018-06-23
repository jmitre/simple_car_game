#include "npcs.h"
#include "../position/position.h"


struct npcs* init_npcs(int num_npcs)
{
    struct position **positions = (struct position**) malloc(num_npcs * 4);
    
    for(int i = 0; i < num_npcs; i++)
    {
        positions[i] = init_position(10,10);
    }

    struct npcs *npcs = malloc(sizeof(struct npcs));
    
    npcs->count = num_npcs;
    npcs->positions = positions;

    return npcs;
}

void destroy_npcs(struct npcs *npcs)
{
    for(int i = 0; i < npcs->count; i++)
    {
        destroy_position(npcs->positions[i]);
    }
    free(npcs->positions);
    free(npcs);
}
