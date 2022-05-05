#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <string.h>

int main()
{
	char rd_buffer[30]; 					//az bemeneti buffer méretének megadása
	char msg[] = "Kopecskó Zsolt IVO46O"; 		// a pipe-ba beírandó szöveg
	int pipefds[2], childpid, nbytes;
	
	if (pipe(pipefds) < 0){ 				//A pipe létrejöttének leellenőrzése!
		printf("Nem sikerült a pipe-ot létrehozni!\n");
		exit(1);
        }
        
        if ((childpid = fork()) == -1){ 			//A gyermek process létrejöttének leellenőrzése!
        	printf("Nem sikerült a gyermek process létrehozása!\n");
        	exit(1);
        }

	if (childpid == 0){
		/*Gyerek process beír a pipe-ba.*/
		close(pipefds[0]); 				//A pipe olvásási végének bezárása, az írás előtt!
		printf("Gyerek process beír a pipe-ba.\n");
		write(pipefds[1], msg, (strlen(msg)));	//az üzenet beírása a pipe-ba
		exit(0); 					//sikeres lefutás után 0 értéket ad vissza a szülő processnek.
	}
	else {
		/*Szülő process megvárja míg a gyermek process befejeződik,
		majd kiolvas az adatokat a pipe-ból.*/
		wait(0);
        	close(pipefds[1]);				//a pipe beírási végének lezárása
              	printf("A szülő process kiolvassa a pibe-ba írt üzenetet!\n");
              	
		while ((nbytes = read(pipefds[0], rd_buffer, sizeof(rd_buffer))) > 0)
			printf("[%s]\n", rd_buffer);
			
		if (nbytes != 0)				// Ha nem ürül ki a pipe akkor 2 érték
			exit(2);				// visszaadásával terminálódik a program.
		
		printf("Finished reading\n"); 		//A sikeres kiolvasás visszaigazolása.
	}
	return 0;
}

