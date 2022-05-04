#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
int main(void) {
  pid_t pid = fork();
 
  if(pid == 0) {
    char *prog = "ls";
	char *arg1 = "-lh";
	char *arg2 = "/home/kzsolt/os/gyak2";
	execlp(prog, prog, arg1, arg2, NULL);
    exit(0);
  }
  else if(pid > 0) {
    wait(NULL);
    printf("Sikeresen lefutott a gyermek process.\n");
  }
  else {
    printf("Nem sikerült létrehozni a gyermek processzt.");
  }
 
  return 0;
}
