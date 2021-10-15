#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main() {
    char buf[255];
    int fd[2];
    
    //Создание канала
    pipe(fd);
 
    printf("Предок [PID=%d] создал неименованный канал.\n",getpid());
 
    if(fork()==0) { //Потомок #1
	//Формирование сообщения
	strcpy(buf,"Hello");
	//Отправка сообщения
	write(fd[1],buf,6);
	printf("Потомок #1 [PID=%d] отправил сообщение: %s\n",
	    getpid(),
	    buf
	);
	
	//Завершение потомка #1
	return 0;
    }

     if(fork()==0) { //Потомок #2
	sleep(1);
	//Приём сообщения
	read(fd[0],buf,6);
	printf(
	    "Потомок #2 [PID=%d] принял сообщение: %s\n",
	    getpid(),
	    buf
	);
	//Завершение потомка #2
	return 0;
    }
 
    //Чтобы потомки могли взаимодействовать через
    //неименованный канал, необходимо, чтобы создавший
    //его предок не завершался до окончания
    //взаимодействия потомков.
    //Ожидание завершения 1-го потомка
    wait();
    //Ожидание завершения 2-го потомка
    wait();
    
    printf("Предок [PID=%d] дождался завершения потомков и завершается сам.\n",getpid());
    
    return 0;
}
