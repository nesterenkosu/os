#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "myenvelope.h"

int main() {
    key_t key;
    int msgid;
    struct myenvelope myenv;

    //Генерация ключа на основе пути до текущего каталога
    key=ftok(".",'A');
    
    //Подключение к очереди, созданной получателем
    msgid=msgget(key,0);
 
    if(msgid<0) {
	printf("Отправитель: ошибка подключения к очереди.\n");
	printf("Возможно, она не создана.\n");
	return -1;
    }
    
    //Формирование сообщения
    //Задание адресата
    myenv.to=1;
    //Задание содержимого сообщения
    strcpy(myenv.buf,"Hello");
    printf("Отправитель: отправка сообщения...\n");
    
    //Отправка сообщения
    msgsnd(msgid,&myenv,sizeof(struct myenvelope)-sizeof(long),0);
    
    printf("Отправитель: сообщение отправленно.\n");
    
    return 0;
}
