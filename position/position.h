#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


static const int TIC_MILLI = 100;
static const int MAX_ABS_VEL = 200;
static const int MAX_ABS_ACC = 100;
static const int OPPOSING_ACC = 1;


struct position {
    int x_pos, y_pos, x_vel, y_vel, x_acc, y_acc;
    pthread_mutex_t *m;
};

struct position* init_position(int start_x, int start_y);
void *manage_position(void *x_void_ptr);
void update_position(struct position* pos);
void update_velocity(struct position* pos);
void accelerate(struct position* pos, int xdelta,int ydelta);
void apply_resistance(struct position* pos);
int val_inbounds(int val, int max_abs);
void apply_resistance(struct position* pos);
void destroy_position(struct position *pos);
int get_x(struct position* pos);
int get_y(struct position* pos);

#endif
