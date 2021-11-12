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
    semid=semget(key,1,IPC_CREAT | IPC_EXCL | 0600);
    if(semid<0) {
	printf("Ошибка создания семафорного объекта.\n");
	printf("Возможно он уже существует.\n");
	return -1;
    }

    printf("Ожидание разблокировки…\n");
    
    //Выполнение блокирующей операции над семафором -
    //ожидание установления счётчика в значение 1.
    struct sembuf myop[1];
    myop[0].sem_num=0;
    myop[0].sem_op=-1;
    myop[0].sem_flg=0;
    semop(semid,myop,1);
    printf("Процесс разблокирован.\n");

    //Удаление семафорного объекта
    semctl(semid,0,IPC_RMID);
    return 0;
}
