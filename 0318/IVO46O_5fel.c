#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
int main(void) {
  pid_t pid = fork();
  pid_t pid1, pid2;
  int a;
  if(pid == 0) {
    printf("Szülő pid: [%d] ---> Gyerek pid: [%d]\n",getppid(), getpid());
    exit(0); //kilép a metódusból és 0 értéket ad vissza
    printf("vajon ez megjelenik? Remélem nem!");
  }
  else if((pid1=fork()) == 0){
    printf("Szülő pid: [%d] ---> Gyerek pid: [%d]\n",getppid(), getpid());
    abort(); //kilép a metódusból de nem ad vissza értéket.
    printf("vajon ez megjelenik? Remélem nem!");
  }else if((pid2=fork()) == 0){  // a nullával való osztás végett a 
    int x=6;                     // a metódus le se fut.
    int y=0;
    printf("lássuk lehet-e nullával osztani");
    int z=x/y;
    printf("z=[%d]\n",z);
  }
    wait(NULL);
    printf("Sikeresen lefutott a gyermek process.\n");
  
  
 
  return 0;
}
