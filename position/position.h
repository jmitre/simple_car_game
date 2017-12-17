#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


static const int TIC_MILLI = 300;

struct position {
    int x_pos, y_pos, x_vel, y_vel, x_acc, y_acc;
    pthread_mutex_t *m;
};

struct position* init_position(int start_x, int start_y);
void *manage_position(void *x_void_ptr);
void update_position(struct position* pos);
void update_velocity(struct position* pos);
void accelerate(struct position* pos, int xdelta,int ydelta);

#endif
