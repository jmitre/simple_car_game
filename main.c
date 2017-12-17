#include "position/position.h"

void main(){
    struct position* pos = init_position(2,3);
    accelerate(pos, 100, 0);
    sleep(10);
    accelerate(pos, -200, 0);
    sleep(10);
    accelerate(pos, 100, 0);
    sleep(10);
}
