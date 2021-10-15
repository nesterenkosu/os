# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int main(int argc, char *argv[])
{
    char buf[255];
    
    //Создание именованного канала
    mkfifo("myfifo.bin",0600);
 
    int fd;
    //Открытие фаила именованного канала
    fd=open("myfifo.bin",O_RDWR);
 
    printf("Получатель: ожидание передачи данных отправителем...\n");
    
    //Ожидание данных в канале и их принятие
    read(fd,buf,6);
 
    //Вывод принятых данных на экран
    printf("Получатель: данные приняты: %s\n",buf);
 
    //Закрытие файла именованного канала
    close(fd);

     //Удаление файла именованного канала
    unlink("myfifo.bin");
 
    return 0;
}
