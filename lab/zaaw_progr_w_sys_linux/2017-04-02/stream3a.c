#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

//kolejki nazwane
// mknod, mkfifo - można utworzyc kolejki z basha
int main(void){

	int connection_socket, ret, data_socket, result;
	char * buffer;
	char * myfifo = "/tmp/myfifo";

	connection_socket = socket(AF_UNIX, SOCK_SEQPACKET,0);
	struct sockaddr_un name;
	name.sun_family = AF_UNIX;	
	strncpy(name.sun_path, myfifo, sizeof(name.sun_path)-1);
	ret = bind(connection_socket, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));

	ret = listen(connection_socket, 20);

	for(;;){
		data_socket = accept(connection_socket, NULL, NULL);
		result = 0;

		for(;;){
			ret = read(data_socket, buffer, 10);
			buffer[9] = 0;
			break;
		}
		break;
	}

	printf("%s \n", buffer);
	close(data_socket);
	close(connection_socket);

	return 0;

}
