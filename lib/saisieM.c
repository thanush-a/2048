#include "saisieM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>


#define MAX 2048

static struct termios   save_termios;
static int term_saved;
static int fd = 0;

static int tty_raw() {
  struct termios  buf;

  if (tcgetattr(fd, &save_termios) < 0)
    return -1;

  buf = save_termios;
  buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  buf.c_iflag &= ~(BRKINT | ICRNL | ISTRIP | IXON);
  buf.c_cflag &= ~(CSIZE | PARENB);
  buf.c_cflag |= CS8;
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;

  if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
    return -1;

  term_saved = 1;
  return 0;
}

static void tty_reset() {
  if (term_saved)
    if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
      exit(-1);
}


void finTerminalSansR()
{
  
   if (term_saved)
    if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
      exit(-1);
}

int debutTerminalSansR()
{
  if (tty_raw() != 0)
    return 0;
  atexit(tty_reset);
  return 1;
}

Key lectureFleche()
{
  char buf[MAX];
  int n = read(0, (void*) buf, MAX);
  switch (n)
  {
    case 1:
      return buf[0] == '' ? KEY_ESCAPE : NO_KEY;
    case 3:
      if (buf[0] == '' && buf[1] == '[')
      {
        switch (buf[2])
        {
          case 'A': return KEY_UP;
          case 'B': return KEY_DOWN;
          case 'C': return KEY_RIGHT;
          case 'D': return KEY_LEFT;
        }
      }
  }
  return NO_KEY;
}

