#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* A signal kezelő deklarálása */
void handleSignals(int sig_num){
    if(sig_num == 2){
       signal(SIGINT,SIG_DFL); // a SIGINT vezérlését alaphelyzetbe állítja
       printf("A következő SIGINT jelre a program leáll! [%d]\n",sig_num);
    }else
    printf("Ez nem SIGINT jel! [%d]\n",sig_num);
    
    fflush(stdout); //kiüríti az outpt buffert
}

int main(){

    signal(SIGINT, handleSignals); //SIGINT jelre átadja a vezérlést a signálkezelőnke, a jel értékével
    signal(SIGQUIT, handleSignals); //SIGQUIT jelre átadja a vezérlést a signálkezelőnke, a jel értékével
    
    /* végtelen ciklus a semmittevéshez */
    
    for ( ;; )
        pause();
        
return 0;
}

