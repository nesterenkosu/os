#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    int semid;
    key_t key;
    
    //Генерация ключа на основе пути до текущего каталога
    key=ftok(".",'A');

    //Подключение к семафорному объекту, созданному в
    //программе blocker.c.
    semid=semget(key,1,0);
    if(semid<0) {
	printf("Ошибка подключения к семафорному объекту.");
	printf("\nВозможно он не существует.\n");
	return -1;
    }

    printf("Проверка блокировки… Если процесс «завис»,\
значит блокировка присутствует.\n");

    //Выполнение блокирующей операции над семафором -
    //ожидание установления счётчика в значение 0
    struct sembuf myop[1];
    myop[0].sem_num=0;
    myop[0].sem_op=0;
    myop[0].sem_flg=0;
    semop(semid,myop,1);
    printf("Проверка завершена. Блокировка снята или отсутствует.\n");

    return 0;
}

