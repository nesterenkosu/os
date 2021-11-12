#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    key_t key;
    int semid;
    key=ftok(".",'A');
 
    //Подключение к семафорному объекту,
    //созданному в программе semop.c
    semid = semget(key,1,0);
    if(semid<0) {
	printf("Ошибка подключения к семафорному объекту\n");
	return -1;
    }
 
    printf(
	    "Текущее значение счётчика семафора: %d\n",
	    semctl(semid,0,GETVAL)
    );
 
    return 0;
}
