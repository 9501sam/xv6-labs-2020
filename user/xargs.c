//https://github.com/gaofanfei/xv6-riscv-fall20/blob/util/user/xargs.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

char buf[1024];

int main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "usage: xargs command\n");
    exit(1);
  }

  char *argv_exec[MAXARG];
  char ch = '\0';
  int stat = 1;

  for(int i = 1; i < argc; i++)
    argv_exec[i-1] = argv[i];

  while (stat) {
    int buf_end = 0;
    int buf_begin = 0;
    int argc_exec = argc - 1;
    
    while (1) {                     //read a line
      stat = read(0, &ch, 1);
      if (stat == 0)
        exit(0);

      if (ch == ' ' || ch == '\n'){ //read a argument
        buf[buf_end++] = '\0';
        argv_exec[argc_exec] = &buf[buf_begin];
        if (ch == '\n')
          break;

      } else {
        buf[buf_end++] = ch;

      }
    }

    argv_exec[buf_end] = '\0';

    if(fork() == 0){
      exec(argv_exec[0], argv_exec);
    }else{
      wait((int*) 0);
    }

  }

  exit(0);
}
