#include "serial.h"

int fd;

#define DEBUG

ssize_t serial_send(const uint8_t *buffer, int count)
{
#ifdef DEBUG
  int i;
  for (i = 0; i < count; i++) {
    printf("%02X ", buffer[i]);
  }
  printf("\n");
#endif
  return write(fd, buffer, (size_t)count);
}

int serial_init(const char * stty)
{
  struct termios tmios;

  fd = open(stty, O_RDWR | O_NONBLOCK);
  if (fd == -1)
  {
    printf("Unable to open %s\n", stty);
    return -1;
  }

  memset(&tmios, 0, sizeof(struct termios));
  cfmakeraw(&tmios);
  cfsetspeed(&tmios, 115200);

  tmios.c_cflag |= (CREAD | CLOCAL | CS8);
  tmios.c_oflag &= ~ONLCR;
  tmios.c_cc[VMIN] = 0;
  tmios.c_cc[VTIME] = 10;
  ioctl(fd, TIOCSETA, &tmios);

  return 0;
}

void serial_exit( void )
{
  close(fd);
}
