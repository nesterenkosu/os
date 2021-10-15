#include <sys/types.h>
#include <unistd.h>

int main() {
    //Запуск копии процесса
    if(fork()>0) {
	//Предок работает 60 сек
	sleep(60);
    } else {
	//Потомок работает 30 сек
	sleep(30);
    }
    return 0;
}
