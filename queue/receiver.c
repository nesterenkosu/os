#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "myenvelope.h"

int main(int argc, char *argv[])
{
    key_t key;
    int msgid;
    struct myenvelope myenv;
    
    //Генерация ключа на основе пути до текущего каталога
    key=ftok(".",'A');
 
    //Создание очереди
    msgid=msgget(key,IPC_CREAT | IPC_EXCL | 0600);
    if(msgid<0) {
	printf("Получатель: Невозможно создать очередь.\n");
	printf("Возможно, она существует.\n");
	return -1;
    }
 
    printf("Получатель: ожидание сообщения...\n");
 
    //Принятие сообщения
    msgrcv(msgid,&myenv,sizeof(struct myenvelope)-sizeof(long),1,0);
    
    //Вывод сообщения на экран
    printf("Получатель: сообщение получено:%s\n",myenv.buf);
 
    //Удаление очереди
    msgctl(msgid,IPC_RMID,NULL);
    
    return 0;
}
