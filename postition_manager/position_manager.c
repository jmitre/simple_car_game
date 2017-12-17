#include "position_manager.h"



struct position* init_position(int start_x, int start_y)
{
    struct position *pos;
    pos  = (struct position*) malloc(sizeof(struct position));

    pos->x_pos = start_x;
    pos->y_pos = start_y;

    pos->x_vel = 0;
    pos->y_vel = 0;
    pos->x_acc = 0;
    pos->y_acc = 0;

    pthread_t *pos_thread = (pthread_t*) malloc(sizeof(pthread_t));
    printf("starting thread\n");
    pthread_create(pos_thread, NULL,*manage_position, (void*)pos);
    
    return pos;
}


void *manage_position(void *x_void_ptr)
{
    printf("starting loop\n");
    struct position* pos_manager = (struct position*)x_void_ptr;
    while(1)
    {
        sleep(1);
        printf("Managing position (%d, %d)\n", pos_manager->x_pos, pos_manager->y_pos);
    }
    printf("exiting loop\n");
}
