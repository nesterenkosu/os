# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int main(int argc, char *argv[])
{
    char buf[255];
    
    int fd;
    //Открытие файла именованного канала
    fd=open("myfifo.bin",O_RDWR);
 
    //Отправка данных в именованный канал
    write(fd,"Hello\0",6);
    printf("Отправитель: данные переданы.\n");
 
    //Закрытие файла именованного канала
    close(fd);
 
    return 0;
}
