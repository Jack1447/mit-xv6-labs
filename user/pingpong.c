// user/pingpong.c
#include "kernel/types.h"
#include "user/user.h"

int main() {
  int pipe1[2]; // parent -> child
  int pipe2[2]; // child -> parent
  char buf[1];

  pipe(pipe1);
  pipe(pipe2);

  int pid = fork();

  if (pid < 0) {
    // fork failed
    fprintf(2, "fork failed\n");
    exit(1);
  } else if (pid == 0) {
    // child process
    close(pipe1[1]); // close write end of pipe1
    close(pipe2[0]); // close read end of pipe2

    read(pipe1[0], buf, 1);
    printf("%d: received ping\n", getpid());

    write(pipe2[1], buf, 1);

    close(pipe1[0]);
    close(pipe2[1]);
    exit(0);
  } else {
    // parent process
    close(pipe1[0]); // close read end of pipe1
    close(pipe2[1]); // close write end of pipe2

    buf[0] = 'x';
    write(pipe1[1], buf, 1);

    read(pipe2[0], buf, 1);
    printf("%d: received pong\n", getpid());

    close(pipe1[1]);
    close(pipe2[0]);
    wait(0);
    exit(0);
  }
}
