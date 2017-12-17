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
        apply_resistance(pos_manager);
        
        printf("P(%d, %d) V(%d,%d) A(%d,%d)\n", pos_manager->x_pos, pos_manager->y_pos, pos_manager->x_vel, pos_manager->y_vel, pos_manager->x_acc, pos_manager->y_acc);
    }
}


void update_position(struct position* pos)
{
    float  xdelta = (float)(pos->x_vel) * ((float)TIC_MILLI/1000.0f);
    float  ydelta = (float)(pos->y_vel) * ((float)TIC_MILLI/1000.0f);

    pos->x_pos = pos->x_pos + xdelta;
    pos->y_pos = pos->y_pos + ydelta;
}

int get_x(struct position* pos)
{
    pthread_mutex_lock(pos->m);
    int x = pos->x_pos;
    pthread_mutex_unlock(pos->m);

    return x;
}

int get_y(struct position* pos)
{
    pthread_mutex_lock(pos->m);
    int y = pos->y_pos;
    pthread_mutex_unlock(pos->m);

    return y;
}

void update_velocity(struct position* pos)
{
    pthread_mutex_lock(pos->m);
    float  xdelta = (float)(pos->x_acc) * ((float)TIC_MILLI/1000.0f);
    float  ydelta = (float)(pos->y_acc) * ((float)TIC_MILLI/1000.0f);
    pthread_mutex_unlock(pos->m);

    pos->x_vel = val_inbounds(pos->x_vel + xdelta, MAX_ABS_VEL);
    pos->y_vel = val_inbounds(pos->y_vel + ydelta, MAX_ABS_VEL);
    printf("NEW VELOCITY %d %d\n", pos->x_vel, pos->y_vel);
}


void accelerate(struct position* pos, int xdelta,int ydelta)
{
    printf("current velocity(%d, %d)\n", pos->x_vel, pos->y_vel);
    pthread_mutex_lock(pos->m);

    pos->x_acc = val_inbounds(pos->x_acc + xdelta, MAX_ABS_ACC);
    pos->y_acc = val_inbounds(pos->y_acc + ydelta, MAX_ABS_ACC);

    printf("New Acceleration (%d, %d)\n", pos->x_acc, pos->y_acc);
    pthread_mutex_unlock(pos->m);
}

int val_inbounds(int val, int max_abs)
{
    if(val > max_abs)
        return max_abs;
    if(val < -1*max_abs)
        return -1*max_abs;
    return val;
}

void apply_resistance(struct position* pos)
{
    if (pos->x_vel > 0)
    {
        pos->x_acc = pos->x_acc - OPPOSING_ACC;
    }
    if (pos->x_vel < 0)
    {
        pos->x_acc = pos->x_acc + OPPOSING_ACC;
    }
    if (pos->y_vel > 0)
    {
        pos->y_acc = pos->y_acc - OPPOSING_ACC;
    }
    if (pos->y_vel < 0)
    {
        pos->y_acc = pos->y_acc + OPPOSING_ACC;
    }
    /* if (pos->x_vel == 0) pos->x_acc = 0; */
    /* if (pos->y_vel == 0) pos->y_acc = 0; */
}

void destroy_position(struct position *pos)
{
    free(pos->m);
    free(pos);
}
