#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd, pid;
    char rd_buffer[20]; //az olvasási buffer méretének megadása
    char msg[20] = "Kopecskó Zsolt"; //a gyermek process által elhelyezendő adat
    char * myfifo = "/home/kzsolt/os/gyak3/ivo46o"; //FIFO file elérési útvonala és neve
    int test = mkfifo(myfifo, 0666); // FIFO file létrehozása
    
    if(test == -1){  //vizsgélat, hogy létezik-e a FIFO file
	perror("hiba történt a FIFO létrehozása közben - a file lehetséges, hogy meár létezik\n");
	unlink("ivo46o"); //törli a létező FIFO filet
	test = mkfifo(myfifo, 0666); // létrehozza a FIFO filet
	printf("A létező FIFO file törölve lett és egy új lett létrehozva!\n\n");
	}
	
    if ((pid = fork()) == -1){ //A gyermek process létrejöttének leellenőrzése!
        printf("Nem sikerült a gyermek process létrehozása!\n");
        exit(1);
        }
        
    if (pid == 0){
	/*Gyerek process beír a pipe-ba.*/
	printf("Gyerek process beír a pipe-ba.\nGyerek PID: [%d] ---> Szülő PID: [%d]\n\n",getpid(), getppid());
	fd = open(myfifo, O_WRONLY); //A FIFO file megnyitása írásra.
	
	if(fd == -1){ //vizsgálat, hogy megnyitható-e a FIFO file
	    perror("Nem lehet megnyitni a fifo file-t!");
	    exit(1);
	}
	
	write(fd, msg, strlen(msg)); //a megadott adat beírása a FIFO file-ba.
	close(fd); //FIFO file bezárása
	exit(0); //sikeres lefutás után 0 értéket ad vissza a szülő processnek.
	}else {
	/*Szülő process megvárja míg a gyermek process befejeződik,
	majd kiolvas az adatokat a pipe-ból.*/	
	fd = open(myfifo, O_RDONLY); //FIFO file megnyitása olvasásra.
	wait(0); //A gyermek process lefutásának megvására.
	printf("A szülő process kiolvassa a pibe-ba írt üzenetet! Szülő PID: [%d]\n\n", getpid());
	read(fd, rd_buffer, sizeof(rd_buffer)); //FIFO file tartalmának kiolvasása
	printf("[%s]\n\n", rd_buffer); //A kiolvasott adat kiírása 
	close(fd); // FIFO file beztárása		
	printf("Finished reading\n"); //A sikeres kiolvasás visszaigazolása.
	}
return 0;
}

