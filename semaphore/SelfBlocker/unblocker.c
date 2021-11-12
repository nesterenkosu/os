#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    int semid;
    key_t key;

    //Генерация ключа на основе пути до текущего каталога
    key=ftok(".",'A');

    //Подключение к существующему семафорному объекту -
    //тому, что был создан в программе unblockable.c
    semid=semget(key,1,0);
    if(semid<0) {
	printf("Ошибка подключения к семафору.\n");
	printf("Возможно он не существует.\n");
	return -1;
    }

    //Выполнение операции увеличения счётчика семафора на 1
    struct sembuf myop[1];
    myop[0].sem_num=0;
    myop[0].sem_op=1;
    myop[0].sem_flg=0;
    semop(semid,myop,1);
    
    return 0;
}
