//https://github.com/gaofanfei/xv6-riscv-fall20/blob/util/user/xargs.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

char buf[512];

int main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "usage: xargs command\n");
    exit(1);
  }

  char *argv_exec[MAXARG];
  char ch = 0;
  int stat = 1;

  for(int i = 1; i < argc; i++)
    argv_exec[i-1] = argv[i];

  while(stat){

  }


  exit(0);
}
