#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  int childPid = fork();

  if(childPid == -1) {
    fprintf(2, "fork error\n");

  } else if(childPid == 0){     /*child*/
    char child_buffer[5];
    read(p[0], child_buffer, 4);
    child_buffer[4] = '\0';
    printf("%d: received %s\n", getpid(), child_buffer);
    char child_input[5] = "pong";
    write(p[1], child_input, 4);
    exit(0);
    
  } else {                      /*parent*/
    char parent_input[5] = "ping";
    write(p[1], parent_input, 4);
    wait((int *) 0);
    char parent_buffer[5];
    read(p[0], parent_buffer, 4);
    parent_buffer[4] = '\0';
    printf("%d: received %s\n", getpid(), parent_buffer);
    exit(0);

  }

  exit(0);
}
