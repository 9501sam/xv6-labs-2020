#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

char buf[512];
char argstr[512];

void
execALine(int argc, char *argv[], char *argstr){
  char *cmd = argv[1];
  char *allargs[MAXARG];
  int i;
  for(i = 1; i < argc; i++)
    allargs[i] = argv[i];
  char *start = argstr;
  char *p;
  for(p = argstr; *p != '\0'; p++)
    if(*p == ' '){
      allargs[i++] = start;
      *p = '\0';
      start = (p+1);
    }
  //exec(cmd, allargs);
  printf("cmd = %s\n", cmd);
  for(int j = 0; j < i; j++)
    printf("%s\n", allargs[j]);
}

void
xargs(int argc, char *argv[])
{
  int n, i, j = 0;
  while((n = read(0, buf, sizeof(buf))) > 0){
    for(i = 0; i < n; i++){
      if(buf[i] == '\n'){
        int pid = fork();
        switch(pid){
        case 0:
          execALine(argc, argv, argstr);
          break;
        case -1:
          fprintf(2, "xargs fork error.\n");
          break;
        default:
          wait((int *) 0);
          j = 0;
          break;
        }
      }else{
        argstr[j++] = buf[i];
      }
    }
  }
}

int
main(int argc, char *argv[])
{
  if(argc < 2)
    fprintf(2, "Usage: xargs command\n");
  xargs(argc, argv);

  exit(0);
}

