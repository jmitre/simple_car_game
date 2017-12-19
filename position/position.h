#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


static const int TIC_MILLI = 10;
static const int MAX_ABS_VEL = 150;
static const int MAX_ABS_ACC = 100;
static const int OPPOSING_ACC = 50;
static const float X_POS_BOUND = 900.0f;
static const float Y_POS_BOUND = 900.0f;


struct position {
    float x_pos, y_pos, x_vel, y_vel, x_acc, y_acc;
    pthread_mutex_t *m;
    pthread_t *t;
};

struct position* init_position(int start_x, int start_y);
void *manage_position(void *x_void_ptr);
void update_position(struct position* pos);
void update_velocity(struct position* pos);
void accelerate(struct position* pos, int xdelta,int ydelta);
void apply_resistance(struct position* pos);
float val_inbounds(float val, float max_abs);
void apply_resistance(struct position* pos);
void destroy_position(struct position *pos);
int get_x(struct position* pos);
int get_y(struct position* pos);

#endif
