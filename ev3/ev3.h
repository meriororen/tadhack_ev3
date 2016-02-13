#ifndef EV3_H
#define EV3_H
#include <stdint.h>

#define MOTOR_A 0x01
#define MOTOR_B 0x02
#define MOTOR_C 0x04
#define MOTOR_D 0x08

#define BUFFER_SIZE 255

#define MOTOR_DIRECTION_POSITIVE 0x01
#define MOTOR_DIRECTION_NEGATIVE 0xFF
#define MOTOR_DIRECTION_TOGGLE 0x00

#define SERIAL_DEVICE "/dev/cu.EV3-SerialPort"

enum {
  CMD_OUTPUT_GET_TYPE           = 0xA0, //     00000
  CMD_OUTPUT_SET_TYPE           = 0xA1, //     00001
  CMD_OUTPUT_RESET              = 0xA2, //     00010
  CMD_OUTPUT_STOP               = 0xA3, //     00011
  CMD_OUTPUT_POWER              = 0xA4, //     00100
  CMD_OUTPUT_SPEED              = 0xA5, //     00101
  CMD_OUTPUT_START              = 0xA6, //     00110
  CMD_OUTPUT_POLARITY           = 0xA7, //     00111
  CMD_OUTPUT_READ               = 0xA8, //     01000
  CMD_OUTPUT_TEST               = 0xA9, //     01001
  CMD_OUTPUT_READY              = 0xAA, //     01010
  CMD_OUTPUT_POSITION           = 0xAB, //     01011
  CMD_OUTPUT_STEP_POWER         = 0xAC, //     01100
  CMD_OUTPUT_TIME_POWER         = 0xAD, //     01101
  CMD_OUTPUT_STEP_SPEED         = 0xAE, //     01110
  CMD_OUTPUT_TIME_SPEED         = 0xAF, //     01111
  CMD_OUTPUT_STEP_SYNC          = 0xB0, //     10000
  CMD_OUTPUT_TIME_SYNC          = 0xB1, //     10001
  CMD_OUTPUT_CLR_COUNT          = 0xB2, //     10010
  CMD_OUTPUT_GET_COUNT          = 0xB3, //     10011
};


int ev3motor_init( void );
void ev3motor_move(
    uint8_t portnum,
    uint8_t speed,
    uint8_t direction);
void ev3motor_stop(
    uint8_t portnum,
    uint8_t brake
    );

/*
 * Copied from ev3 source. oOUTPUT_TIME_SYNC -> evmotor_move_sync
 * ignore “layer”
 *
 *
 * SYNCRONIZATION:
 *
 *  Speed -100 to +100 is move forward or move backwards
 *  Turn ratio is how tight you turn and to what direction you turn
 *   - 0 value is moving straight forward
 *   - Negative values turns to the left
 *   - Positive values turns to the right
 *   - Value -100 stops the left motor
 *   - Value +100 stops the right motor
 *   - Values less than -100 makes the left motor run the opposite
 *     direction of the right motor (Spin)
 *   - Values greater than +100 makes the right motor run the opposite
 *     direction of the left motor (Spin)
 *
 *  Example: opOUTPUT_TIME_SYNC(0, 10, 100, 50, 10000,1)
 *
 *  0     = Layer
 *  10    = Motor bit field - Motor B and D
 *  100   = Motor speed     - Motor B will run at speed 100 (because ratio is positive)
 *  10    = Turn ratio      - Motor D will run at speed 50
 *  10000 = time in mS      - Motors will run for 10 sec.
 *  1     = Brake bit       - When 10 sec. has elapsed then brake both motors
 *
 *
 *  Example: opOUTPUT_TIME_SYNC(0, 10, 100, 150, 10000,1)
 *
 *  0     = Layer
 *  10    = Motor bit field - Motor B and D
 *  100   = Motor speed     - Motor B will run at speed 100 (because ratio is positive)
 *  10    = Turn ratio      - Motor D will run at speed -50
 *  10000 = time in mS      - Motors will run for 10 sec.
 *  1     = Brake bit       - When 10 sec. has elapsed then brake both motors
 *
 *
 *  Example: opOUTPUT_TIME_SYNC(0, 10, 100, -50, 10000,1)
 *
 *  0     = Layer
 *  10    = Motor bit field - Motor B and D
 *  100   = Motor speed     - Motor B will run at speed  50 (because ratio is positive)
 *  10    = Turn ratio      - Motor D will run at speed 100
 *  10000 = time in mS      - Motors will run for 10 sec.
 *  1     = Brake bit       - When 10 sec. has elapsed then brake both motors
 *
 *
 *  Example: opOUTPUT_TIME_SYNC(0, 10, 200, -150, 10000,1)
 *
 *  0     = Layer
 *  10    = Motor bit field - Motor B and D
 *  100   = Motor speed     - Motor B will run at speed -50 (because ratio is positive)
 *  10    = Turn ratio      - Motor D will run at speed 100
 *  10000 = time in mS      - Motors will run for 10 sec.
 *  1     = Brake bit       - When 10 sec. has elapsed then brake both motors
 *
 */
void ev3motor_move_sync(
    uint8_t portmask,
    int8_t speed,
    int16_t turn,
    uint32_t duration,
    uint8_t brake);
void ev3motor_exit( void );
#endif
