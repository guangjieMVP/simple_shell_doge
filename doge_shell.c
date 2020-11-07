#include "doge_shell.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "doge_shell_port.h"

static void get_line(char *buf, uint32_t len)
{
    char i;
    i = 0;
    char tmp;
    memset(buf, 0, len);
    while(len--)
    {
        *buf = get_char_port();
        if(*buf == ENTER_KEY)  //濡傛灉鏄洖杞?杩涜鎹㈣
        {
            putc('\r', stdout);
//            putc('\n', stdout);
//            printf("enter\r\n");
            return;
            break;
        }
        switch(*buf)
        {
            case BACKSPACE_KEY:      //濡傛灉鏄垹闄ら敭  鍒犻櫎shell绐楀彛瀛楃
            {
                if(i > 0)
                {
                    len++;
                    *buf--;
                    put_char_port(BACKSPACE_KEY);
                    i--;
                }
                break;
            }
            default:               //杈撳叆鍛戒护鎯呭喌
            {
                i++;
                *buf++;
//                putc(*buf++, stdout);
                len--;    
            }
            break;
            
        }
    }
}

static char char_is_space(char c)
{
    if (c == SPACE_KEY)
        return 1;
    
    return 0;
}

static int parse_line (char *line, char **argv)
{
    uint8_t nargs = 0;
    
    char *tmp = line;
    int i = 0;
    
    if(*line == ENTER_KEY)      
    {
        nargs = 0;
        return nargs;
    }
    
    while (nargs < SHELL_MAX_ARGS)
    {
        while (char_is_space(*line))    //去掉最前面的空格和Tab键
        {
            ++line;
        }

        if (*line == ENTER_KEY)  //去掉前面空格还是回车 说明
        {
            argv[nargs] = NULL;
            return nargs;
        }
        
        argv[nargs++] = line; 
        
        while ( (*line) && (!char_is_space(*line)) && (*line != ENTER_KEY))
        {
            ++line;
        }

        if (*line == ENTER_KEY)      //命令以回车结束，最后一个字符是回车
        {
          *line++ = '\0';            //将字符串截断，去掉回车符及后面的字符
          return nargs;
        }
        else                         //还不是回车，说明命令还没结束
        {
          *line++ = '\0';
        }
//        printf("nargs = %d\r\n", nargs);
    }
    printf ("** Too many args (max. %d) **\r\n", SHELL_MAX_ARGS);
    return (nargs);
}


static int _match_name(char *str, char *name)
{
  int c1, c2;
  
  c1 = *str;
  c2 = *name;
  
  while((c1 == c2) && c1)
  {
    str++;
    name++;
    c1 = *str;
    c2 = *name;
  }
  
  return (c1 - c2);
}


void shell_loop(char *prompt, struct sh_cmd *cmds, uint16_t cmds_len)
{
    char cmd_buf[CMD_BUF_LEN];
    char *argv[SHELL_MAX_ARGS];
    int argc;
    int index = 0;
    
    while(1)
    {
        printf("%s>>", prompt);
        
        get_line(cmd_buf, CMD_BUF_LEN);
         
        argc = parse_line(cmd_buf, argv);    //解析命令的各个参数
        
//        printf("argument count:%d\r\n", argc);
        
//       for (int i = 0; i < argc; i++)
//       {
//          printf("%s\r\n", argv[i]);
//       }
        
        if (!argc) break;                    //只是按下回车键
        
        for (index = 0; index < cmds_len; index++)
        {
           if (_match_name(argv[0], cmds[index].name) == 0)
          {
            if (cmds[index].fun)
               cmds[index].fun(&cmds[index], argc, argv);
            
            break;
          }
        }
                
        if (index == cmds_len) 
          printf("command not found\r\n");

    }
}