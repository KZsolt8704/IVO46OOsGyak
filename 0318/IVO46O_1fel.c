#include <stdlib.h>
#include<stdio.h>
#include<signal.h>
int main(){
    int sc;
    char parancs[10];
    
	printf("Kérem adjon meg egy system() parancsot (pl.: date, pwd, who):");
	scanf("%s", parancs);
    	sc=system(parancs);
    
    return 0;
}
