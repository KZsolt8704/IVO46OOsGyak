#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(){
    int sc;
    char parancs[10];
    do{
 	printf("\nKérem adjon meg egy system() parancsot (pl.: date, pwd, who),\n vagy a kilépéshez ctr+c :");
	scanf("%s", parancs);
 	sc=system(parancs);
    }while(parancs[10]!=SIGQUIT);
    return 0;
}
