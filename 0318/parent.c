#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "child.c"
 
void parentTask() {
  printf("Sikeresen lefutott a gyermek process.\n");
}
 
int main(void) {
  pid_t pid = fork();
 
  if(pid == 0) {
    childTask();
    exit(0);
  }
  else if(pid > 0) {
    wait(NULL);
    parentTask();
  }
  else {
    printf("Nem sikerült létrehozni a gyermek processzt.");
  }
 
  return 0;
}
