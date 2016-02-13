#include "ev3.h"
#include "serial.h"

static uint16_t message_counter = 0x0000;
uint8_t gbuf[BUFFER_SIZE];

int ev3motor_init( void )
{
  return serial_init(SERIAL_DEVICE);
}

static void _ev3motor_power(
    uint16_t *count,
    uint8_t portnum,
    uint8_t speed)
{
  uint16_t cnt = *count;
  gbuf[cnt++] = CMD_OUTPUT_POWER;
  gbuf[cnt++] = 0x00;
  gbuf[cnt++] = portnum; 
  gbuf[cnt++] = speed;
  *count += 4;
}

static void _ev3motor_start(
    uint16_t *count,
    uint8_t portnum)
{
  uint16_t cnt = *count;
  gbuf[cnt++] = CMD_OUTPUT_START;
  gbuf[cnt++] = 0x00;
  gbuf[cnt++] = portnum;
  *count += 3;
}

static void _ev3motor_direction(
    uint16_t *count,
    uint8_t portnum,
    uint8_t direction)
{
  uint16_t cnt = *count;
  gbuf[cnt++] = CMD_OUTPUT_POLARITY;
  gbuf[cnt++] = 0x00;
  gbuf[cnt++] = portnum;
  gbuf[cnt++] = direction;
  *count += 4;
}

static void _ev3motor_stop(
    uint16_t *count,
    uint8_t portnum,
    uint8_t brake)
{
  uint16_t cnt = *count;
  gbuf[cnt++] = CMD_OUTPUT_STOP;
  gbuf[cnt++] = 0x00;
  gbuf[cnt++] = portnum;
  gbuf[cnt++] = brake;
  *count += 4;
}

/* ev3motor_move : Move one motor individually */

void ev3motor_move(
    uint8_t portnum,
    uint8_t speed,
    uint8_t direction)
{
  uint16_t count = 2;
  message_counter++;
  memset(gbuf, 0, sizeof(gbuf));
  
  // message counter
  gbuf[count++] = message_counter & 0xFF; 
  gbuf[count++] = (message_counter >> 8) & 0xFF; 

  // local & global
  gbuf[count++] = 0x80;
  gbuf[count++] = 0x00; 
  gbuf[count++] = 0x00; 

  _ev3motor_power(&count, portnum, speed);
  _ev3motor_direction(&count, portnum, direction);
  _ev3motor_start(&count, portnum);

  count -= 2;
  // lastly, put count
  gbuf[1] = (count >> 8) & 0xFF;
  gbuf[0] = count & 0xFF;

  serial_send(gbuf, (int)count + 2);
}

/* ev3motor_stop : Stop one motor individually */

void ev3motor_stop(
    uint8_t portnum,
    uint8_t brake)
{
  uint16_t count = 2;
  message_counter++;
  memset(gbuf, 0, sizeof(gbuf));

  // message counter
  gbuf[count++] = message_counter & 0xFF; 
  gbuf[count++] = (message_counter >> 8) & 0xFF; 

  // local & global
  gbuf[count++] = 0x80;
  gbuf[count++] = 0x00; 
  gbuf[count++] = 0x00; 

  _ev3motor_stop(&count, portnum, brake);

  count -= 2;
  // lastly, put count
  gbuf[1] = (count >> 8) & 0xFF;
  gbuf[0] = count & 0xFF;

  serial_send(gbuf, (int)count + 2);
}

void ev3motor_move_sync(
    uint8_t portmask,
    int8_t speed,
    int16_t turn,
    uint32_t duration,
    uint8_t brake)
{
  uint16_t count = 2;
  message_counter++;
  memset(gbuf, 0, sizeof(gbuf));

  // message counter
  gbuf[count++] = message_counter & 0xFF;
  gbuf[count++] = (message_counter >> 8) & 0xFF;

  // local & global
  gbuf[count++] = 0x80;
  gbuf[count++] = 0x00;
  gbuf[count++] = 0x00;

  gbuf[count++] = CMD_OUTPUT_TIME_SYNC;
  gbuf[count++] = 0x00;
  gbuf[count++] = portmask;
  gbuf[count++] = 0x81;
  gbuf[count++] = (uint8_t)speed;
  gbuf[count++] = 0x82;
  gbuf[count++] = (uint8_t)(turn & 0x00FF);
  gbuf[count++] = (uint8_t)((turn >> 8) & 0x00FF);
  gbuf[count++] = 0x83;
  gbuf[count++] = (uint8_t)(duration & 0x000000FF);
  gbuf[count++] = (uint8_t)((duration >> 8) & 0x000000FF);
  gbuf[count++] = (uint8_t)((duration >> 16) & 0x000000FF);
  gbuf[count++] = (uint8_t)((duration >> 24) & 0x000000FF);
  gbuf[count++] = brake;

  //_ev3motor_start(&count, MOTOR_A);
  //_ev3motor_start(&count, MOTOR_B);

  count -= 2;
  // lastly, put count
  gbuf[1] = (count >> 8) & 0xFF;
  gbuf[0] = count & 0xFF;

  serial_send(gbuf, (int)count + 2);
}

void ev3motor_exit( void )
{
  serial_exit();
}
