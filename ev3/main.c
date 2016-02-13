#include "serial.h"
#include "ev3.h"
#include <string.h>

/*
 * ev3 <cmd> <param1> <param2>
 *
 * cmd:
 *   dance
 *   go
 *   turn
 *
 */
#define TURN_DURATION 2
#define SPIN_DURATION 2

enum {
  LEFT,
  RIGHT,
  BACK
};

static void ev3go( int speed, int duration )
{
  ev3motor_move_sync(MOTOR_B | MOTOR_D, speed, 0, duration, 1);
  sleep(duration/1000);
}

static void ev3turn( int direction )
{
  int duration = TURN_DURATION * 1000;
  switch (direction)
  {
    case LEFT:
      //printf("turning left\n");
      ev3motor_move_sync(MOTOR_B | MOTOR_D, 100, 200, duration, 1);
      sleep(duration/1000);
      break;
    case RIGHT:
      //printf("turning right\n");
      ev3motor_move_sync(MOTOR_B | MOTOR_D, 100, 100, duration, 1);
      sleep(duration/1000);
      break;
    case BACK:
      //printf("turning back\n");
      ev3motor_move_sync(MOTOR_B | MOTOR_D, 100, -100, duration, 1);
      sleep(duration/1000);
      break;
  }
}

static void ev3dance( void )
{
    ev3motor_move_sync(MOTOR_B | MOTOR_D, 100, -100, SPIN_DURATION * 1000, 1);
    sleep(SPIN_DURATION);
    ev3motor_move_sync(MOTOR_B | MOTOR_D, 100, 200, SPIN_DURATION * 1000, 1);
    sleep(SPIN_DURATION);
}

static void printusage( const char *argv0 ) 
{
      printf("ERROR!\n");
      printf("usage: %s <cmd> [<param1> [<param2>] .. ]\n", argv0);
      printf("   command:                              \n"
             "       go <speed:0-100> <duration:second>\n"
             "       turn <left|right|back>            \n"
             "       dance                             \n");
}

int main( int argc, const char *argv[] )
{
#if 0
  ev3motor_stop(MOTOR_B, 1); // stop and brake
  ev3motor_move(MOTOR_B, 20, MOTOR_DIRECTION_NEGATIVE);
  sleep(2);
  ev3motor_move(MOTOR_B, 10, MOTOR_DIRECTION_POSITIVE);
  sleep(2);
  ev3motor_stop(MOTOR_B, 1); // stop and brake
  ev3motor_move_sync(MOTOR_B | MOTOR_D, 150, -150, 4000, 1);
#endif
  if (argc < 2) {
      printusage(argv[0]);
      return 1;
  }

  if (ev3motor_init())  return 1;

  int len = strlen(argv[1]);
  int speed, duration;
  int turn;

  if (len == 2 && !strcmp("go", argv[1])) {
    if (argc < 4) { printusage(argv[0]); return 1; }
    speed = atoi(argv[2]);
    duration = atoi(argv[3]);
    ev3go(speed, duration * 1000);
  } else if (len == 5 && !strcmp("dance", argv[1])) {
    ev3dance();
  } else if (len == 4 && !strcmp("turn", argv[1])) {
    if (argc < 3) { printusage(argv[0]); return 1; }
    if (!strcmp("left", argv[2])) turn = LEFT;
    else if (!strcmp("right", argv[2])) turn = RIGHT;
    else if (!strcmp("back", argv[2])) turn = BACK;
    else { printusage(argv[0]); return 1; }
    ev3turn(turn);
  } else { printusage(argv[0]); return 1; }

  return 0;
}
