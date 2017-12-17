#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct position {
    int x_pos, y_pos, x_vel, y_vel, x_acc, y_acc;
};

struct position* init_position(int start_x, int start_y);
void *manage_position(void *x_void_ptr);
