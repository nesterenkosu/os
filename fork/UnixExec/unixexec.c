# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>

int UnixExec(char *path) {
    if(fork()==0)
	execl(path,path,0);
	
    int ret;
    wait(&ret);

    return WEXITSTATUS(ret);
}

int main(int argc, char *argv[])
{
    printf("Запускаем внешнюю программу...\n");
    printf("Программа завершилась с кодом %d [%d]\n",UnixExec("./prog2"),errno);
    return 0;
}
