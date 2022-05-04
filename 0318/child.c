#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
void childTask() {
	
  for(int i=0; i<10; i++){
  printf("[%d]: Kopecskó Zsolt IVO46O\n",i+1);
  }
exit(0);
}
