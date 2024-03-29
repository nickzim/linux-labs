#include <iostream>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <signal.h>

using namespace std;

void pause(int sig){
	raise(SIGKILL);
}

int main(int argc, char *argv[]) {
 
	struct msg{
	long mtype;
	pid_t process_id;
	} mes;

	mes.mtype = 1;
	mes.process_id = getpid();

	signal(SIGALRM, pause);
	alarm(atoi(argv[1]));
	for(;;){
		int msg_queue_id = msgget(280, IPC_EXCL);
		
		if (msg_queue_id == -1){
			//cout << "Ошибка при доступе к очереди\n";
			//cout << strerror(errno) << "\n";
		}
	

		if (msgsnd(msg_queue_id,&mes,256,0) == -1){
			//cout << "Ошибка при отправке сообщений\n";
			//cout << strerror(errno) << "\n";
		} else {
			break;
		}	

	}
	return 0;
}
