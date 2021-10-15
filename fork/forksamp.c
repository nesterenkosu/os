#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    //Запуск копии процесса

    if(fork()>0) {
	//Этот код выполнится в предке
	printf("Это предок PID=[%d]\n",getpid());
	wait();
    } else {
	//Этот код выполнится в потомке
	sleep(1);//для предотвращения одновременного с предком вывода
	printf("Это потомок PID=[%d] PPID=[%d]\n",getpid(),getppid());
    }

    //Этот код выполнится и в предке,
    //и в потомке.
    printf("Выполнится и в предке, и в потомке PID=%d\n",getpid());

    return 0;
}
