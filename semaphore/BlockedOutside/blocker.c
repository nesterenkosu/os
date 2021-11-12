#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    int semid;
    key_t key;

    //Генерация ключа на основе пути до текущего каталога
    key=ftok(".",'A');

    //Создание семафорного объекта, содержащего один
    //счётчик семафора.
    semid=semget(key,1, IPC_CREAT | IPC_EXCL | 0600);
    if(semid<0) {
	printf("Ошибка создания семафорного объекта.");
	printf("\nВозможно он уже существует.\n");
	return -1;
    }

    //Выполнение операции увеличения счётчика
    //семафора на 1
    struct sembuf myop[1];
    myop[0].sem_num=0;
    myop[0].sem_op=1;
    myop[0].sem_flg=0;
    semop(semid,myop,1);
    printf("Блокировка установлена. Для снятия блокирвки\
нажмите Enter.\n");

    getchar();
    //Выполнение операции уменьшения счётчика
    //семафора на 1 (т.е. в данном случае – сброс в 0).
    myop[0].sem_num=0;
    myop[0].sem_op=-1;
    myop[0].sem_flg=0;
    semop(semid,myop,1);
    printf("Блокировка снята.\n");

    //Удаление семафорного объекта
    semctl(semid,0,IPC_RMID);
    return 0;
}
