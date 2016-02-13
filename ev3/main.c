#include "serial.h"
#include "ev3.h"

int main( int argc, const char *argv[] )
{
  printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
  ev3motor_init();
#if 0
  ev3motor_stop(MOTOR_B, 1); // stop and brake
  ev3motor_move(MOTOR_B, 20, MOTOR_DIRECTION_NEGATIVE);
  sleep(2);
  ev3motor_move(MOTOR_B, 10, MOTOR_DIRECTION_POSITIVE);
  sleep(2);
  ev3motor_stop(MOTOR_B, 1); // stop and brake
#else
  ev3motor_move_sync(MOTOR_B | MOTOR_D, 150, -150, 4000, 1);
#endif
  printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
}
