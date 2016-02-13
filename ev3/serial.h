#ifndef SERIAL_H
#define SERIAL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

int serial_init(const char *stty);
ssize_t serial_send(const uint8_t *buffer, int count);
void serial_exit( void );

#endif
