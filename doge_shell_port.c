#include "doge_shell_port.h"
#include "stdio.h"

char get_char_port(void)
{
  return getc(stdin);
}

void put_char_port(char c)
{
  putc(c, stdout);
}