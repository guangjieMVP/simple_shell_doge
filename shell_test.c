#include "doge_shell.h"
#include "stdio.h"

#define ARRAY_SIZE(a)  (sizeof(a)/sizeof(a[0]))

int do_test1(struct sh_cmd *thiz, int argc, char *argv[])
{
   printf("test1 argc : %d\r\n", argc);
   printf("test1 help : %s\r\n", thiz->help);
}

int do_test2(struct sh_cmd *thiz, int argc, char *argv[])
{
   printf("test2 argc : %d\r\n", argc);
   printf("test2 help : %s\r\n", thiz->help);
}

struct sh_cmd cmds[] = {
  {"test1", "This is a tes1t", do_test1},
  {"test2", "This is a test2", do_test2},
};

int main(int argc, char **argv)
{
  while(1)
  {
    shell_loop("DogeShell", cmds, ARRAY_SIZE(cmds));
  }
}