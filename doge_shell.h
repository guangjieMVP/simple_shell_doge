#ifndef _DOGE_SHELL_H_
#define _DOGE_SHELL_H_

#define ESC_KEY          0x1BU
#define ENTER_KEY        0x0AU           
#define BACKSPACE_KEY    0x7FU           
#define SPACE_KEY        0x20U        

#define SHELL_MAX_ARGS   10
#define CMD_BUF_LEN      100

#include "stdint.h"

struct sh_cmd {
    char *name;         //
    char *help;         //
    int (*fun)(struct sh_cmd *thiz, int argc, char *argv[]);   //
};

void shell_loop(char *prompt, struct sh_cmd *cmds, uint16_t len);

#endif