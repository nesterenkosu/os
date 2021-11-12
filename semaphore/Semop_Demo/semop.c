#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    key_t key;
    int semid;
    
    //Генерация ключа
    key=ftok(".",'A');
 
    //Создание нового или подключение
    //к существующему семафорному объекту
    semid=semget(key,1,IPC_CREAT | 0666);
    printf("Выполнение операции…\n");
 
    struct sembuf buf[1];
    buf[0].sem_num=0;
    buf[0].sem_op=atoi(argv[1]);
    buf[0].sem_flg=0;
    semop(semid,buf,1);
    printf("Операция выполнена.\n");
 
    return 0;
}
