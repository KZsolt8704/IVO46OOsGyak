#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>

void howtouse(void); /*Súgó a program működéséhez!*/
void shmwrite(int shmid, char *shmsegpt, char *text); /*Osztott memóriaterületre való írás*/
void shmread(int shmid, char *shmsegpt); /*Osztott memóriaterületről való olvasás*/
void shmdelete(int shmid, char *shmsegpt); /*Osztott memóriaterület törlése*/

int main (int argc, char* argv[]){ /*paraméterek a parancssorban*/
	key_t key; /*jogosultságot meghatározó kulcs*/
	int shmid; /*osztott memóriaterület ID-je*/
	int execshmid; /*létező osztott memória terület címe*/
	int shmsegsize; /*osztott memória mérete*/
	shmsegsize = 100; /*osztott memória mérete béjtban megadva*/
	char *shmsegpt; /*osztott memória címe*/
		
	if(argc == 1){ /*ha csak egy argumentum kerül megadásra a parancssorban, akkor lefut a súgó függvény*/
		howtouse(); /*Súgó a program működéséhez*/
	}
	/*Külcs generálás*/
	key = ftok(".", 'A'); /*key generáló függvény egy kulcsot ad vissza az elérési út és az azonosító alapján.*/
								 /*A függvény ugyanazt a kulcsot adja vissza minden olyan elérési úthoz, */
								 /*amely ugyanarra a fájlra mutat, ha ugyanazzal az azonosító értékkel hívják meg.*/
	/*oszotott memóriaterület létrehozása*/
	shmid = shmget(key, shmsegsize, IPC_CREAT|IPC_EXCL|0666);
	/*A shmget függvény visszatérési értéke a key kulcshoz rendelt memóriazóna azonosítója. Hiba esetén -1.*/
	if(shmid == -1){ //ha -1 a visszatérési érték, akkor már van a kulcshoz rendelt osztott memóriaterület.
		execshmid = shmget(key, 0, 0); //a létező osztott memóriaterület ID-jének lekérdezése.
		printf("Már létezik az osztott memóriterület!\nMegnyitom a [%d] ID-jű memóriaterületet!\n", execshmid);
		if ((shmid = shmget(key, shmsegsize, 0)) == -1){
      perror("shmget hiba");
      exit(1);
   	}
	}else if(shmid != -1){ //Ha nem -1 a visszatérési érték, akkor sikeresen létrejött az osztott memóriaterület.
				printf("Létrehozom az új osztott memóriát!\n");
				printf("Az osztott memória ID-je: [%d]\n", shmid);	
	}
	/*Memórirész hozzárendelés*/
	/*A *shmat(int shmid, void *addr, int flg) függvény feladata egy folyamat címterületéhez hozzárendelni
	egy osztott memórioazónát. A hozzárendelés után a folyamat írhat, olvashat erről a memóriaterületről.
	A függvény visszatérési értéke egy pointer a közös memóriazónára ha a művelet sikeres volt. Ellenkező esetben -1.
	Az addr égy pointer típusú voltozó a közös memórirész hozzáférési címe a hivó folyamat adatszegmensében.
	Az addr=NULL, a memóriarész a rendszer által kiválasztott első szabad címe.*/
	shmsegpt = shmat(shmid, 0, 0);
	printf("osztott memória címe: [%p]\n", &shmsegpt);
	
	/*műveletek szerinti bontás*/
	switch (tolower(argv[1][0])){ //tolower fv. segítségével a bevitt nagybetűt kisbetűre változtatjuk
		case 'w':
			shmwrite(shmid, shmsegpt, argv[2]); //beíró fv. meghívása
			break;
		case 'r':
			shmread(shmid, shmsegpt); //kiolvasó fv. meghívása
			break;
		case 'd':
			shmdelete(shmid, shmsegpt); //memória törlő fv. meghívása
			break;
	}	
return 0;
}

void howtouse(void){
	printf("Az osztott memória kezelő program használara parancssorban:\n");
	printf("Osztott memóriába való írás: ---> ./ivo46o_25 (w)rite \"beírandó szöveg\"\n");
	printf("Osztott memória kiolvasása:  ---> ./ivo46o_25 (r)ead\n");
	printf("Osztott memória törlése:     ---> ./ivo46o_25 (d)elete\n");
	exit(1);
}

void shmwrite(int shmid, char *shmsegpt, char *text){
	if(text==NULL){
		printf("A [%d] ID-jű memóriaterületre nem lett beállítva beírandó szöveg!\n", shmid);
		strcpy(shmsegpt, "");
		exit(1);
	}else
	printf("A [%d] ID-jű memóriába beírásra került a [%s] szöveg\n", shmid, text);
	strcpy(shmsegpt, text);
}

void shmread(int shmid, char *shmsegpt){
	printf("A [%d] ID-jű memóriaterület a következő adatot tartalmazza: [%s]\n", shmid, shmsegpt);
}

void shmdelete(int shmid, char *shmsegpt){
	/*A shmctl(int shmid, int cmd, struct shmid_ds *buf) függvény az osztott memóriarész információinak
	lekérdezésére, módosítására és törlésére használható.
	A függvény visszatérési értéke 0, ha a művelet sikeres volt, ellenkező esetben -1.
	A cmd argumnetumban megadott IPC_RMID az osztott memóriarész törlésére szolgál.
	A végleges törlés akkor kerül sor, amikor az utolsó folyamat is, amelyik ezt a területet használja,
	megszakítja a kpcsolatot ezzel a memóriarésszel.*/
	shmctl(shmid, IPC_RMID, 0);
	printf("A [%d] számú osztott memóriaterület törlésre került!\n", shmid);
}
