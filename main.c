#include "position/position.h"

void main()
{
    struct position* pos = init_position(2,3);
    accelerate(pos, -300, 300);
    sleep(100000);
    sleep(20);
    sleep(10);
}
