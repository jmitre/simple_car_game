#include "position.h"



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

    pos->m = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));

    pthread_t *pos_thread = (pthread_t*) malloc(sizeof(pthread_t));
    printf("starting thread\n");
    pthread_create(pos_thread, NULL,*manage_position, (void*)pos);
    
    return pos;
}


void *manage_position(void *x_void_ptr)
{
    struct position* pos_manager = (struct position*)x_void_ptr;
    while(1)
    {
        usleep(TIC_MILLI * 1000);
        update_position(pos_manager);
        update_velocity(pos_manager);
        
        printf("(%d, %d)\n", pos_manager->x_pos, pos_manager->y_pos);
    }
}


void update_position(struct position* pos)
{
    float  xdelta = (float)(pos->x_vel) * ((float)TIC_MILLI/1000.0f);
    float  ydelta = (float)(pos->y_vel) * ((float)TIC_MILLI/1000.0f);

    pos->x_pos = pos->x_pos + xdelta;
    pos->x_pos = pos->x_pos + ydelta;
}

void update_velocity(struct position* pos)
{
    pthread_mutex_lock(pos->m);
    float  xdelta = (float)(pos->x_acc) * ((float)TIC_MILLI/1000.0f);
    float  ydelta = (float)(pos->y_acc) * ((float)TIC_MILLI/1000.0f);
    pthread_mutex_unlock(pos->m);

    pos->x_vel = pos->x_vel + xdelta;
    pos->x_vel = pos->x_vel + ydelta;
}

void accelerate(struct position* pos, int xdelta,int ydelta)
{
    printf("current velocity(%d, %d)\n", pos->x_vel, pos->y_vel);
    pthread_mutex_lock(pos->m);
    pos->x_acc = pos->x_acc + xdelta;
    pos->x_acc = pos->x_acc + ydelta;
    pthread_mutex_unlock(pos->m);
    printf("New Acceleration\n (%d, %d)\n", pos->x_acc, pos->y_acc);
}
