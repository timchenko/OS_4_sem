#define _GNU_SOURCE			/* for accept4 */
#include <sys/types.h>		/* for socket(2) */
#include <sys/socket.h>		/* for socket(2) */
#include <stdlib.h>			/* for itoa */
#include <errno.h>			/* for errno */
#include <netinet/ip.h>		/* for sockaddr_in */
#include <string.h>			/* for memset */
#include <unistd.h>			/* for pipe */
#include <fcntl.h>			/* for fcntl */

#define BUFF_SIZE 1023

int sfd;

void handle_error(char* msg) 
{
	perror(msg);
	exit(errno);
}

void init_listener(int port) 
{
    struct sockaddr_in addr;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
		handle_error("socket error");
	fcntl(sfd, F_SETFL, O_NONBLOCK);		// TEMP
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (bind(sfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) == -1)
		handle_error("bind error");
	if (listen(sfd, 1) == -1)				// TODO: (sfd, -1)
		handle_error("listen error");
}

void daemonize() 
{
	int file = open("/tmp/rshd.pid", O_RDONLY);
	if (file > 0) {
		char* tmp_buff = (char *) malloc(10 * sizeof(char));
		int lenght = 0, shift = 0;
		while (lenght < 10 && shift = read(file, buffer + lenght, 10 - lenght)) {
			if (shift < 0) break;
			lenght += shift;
		}
		buffer[lenght] = 0;
		if (!kill(atoi(buffer), 0)) {
			printf("Already running.\n");
			close(file);
			exit(0);
		} else close(file);
	}

	int pid = fork();
	if (pid < 0)
		handle_error("daemonize error");
	if (f1 != 0)
		exit(0);
	setsid();

	int pid = fork();
	if (pid < 0)
		handle_error("daemonize error");
	if (pid != 0) {
		file = creat("/tmp/rshd.pid", 00664);
		if (file < 0)
			handle_error("create rshd.pid error");
		char *tmp_buff = (char *) malloc(10 * sizeof(char));
		itoa(pid, tmp_buff, 10);
		int lenght = strlen(tmp_buff), shift = 0, wr_len = 0;
		while (shift < lenght) {
			wr_len = write(file, tmp_buff + shift, lenght - shift);
			if (wr_len < 0)
				handle_error("write rshd.pid error")
			shift += wr_len;
		}
		waitpid(
		close(file);
		exit(0);
	}
}

int main(int argc, char* argv[]) 
{
	if (argc < 2) 
		handle_error("few arguments");
	
	daemonize();

	init_listener(atoi(argv[1]));

	int cfd = 0;
	do
	{
		if (cfd == 0)
			perror("in cycle");
		errno = 0;
		cfd = accept4(sfd, NULL, NULL, O_NONBLOCK);		//TEMP
	} while (errno == EAGAIN);
	if (cfd == -1) 
		handle_error("accept error");
	else
		perror("Good");
	//fcntl(cfd, F_SETFL, O_NONBLOCK);		// TEMP


	char stoc_buf[BUF_SIZE], ctos_buf[BUF_SIZE];
	memset(stoc_buf, 0, BUF_SIZE);
	memset(ctos_buf, 0, BUF_SIZE);	
	int stoc_pfd[2], ctos_pfd[2];
	if (pipe(stoc_pfd) == -1 || pipe(ctos_pfd) == -1)
		handle_error("pipe error");
	perror("here1");

	pid_t child_pid = fork();
	if (child_pid == -1) 
		handle_error("fork error");
	if (child_pid == 0)
	{
		perror("here2");
		close(stoc_pfd[1]);
		close(ctos_pfd[0]);
		dup2(stoc_pfd[0], STDIN_FILENO);
		dup2(ctos_pfd[1], STDOUT_FILENO);
		close(stoc_pfd[0]);
		close(ctos_pfd[1]);
		execl("/bin/sh", "/bin/sh", NULL);
		handle_error("exec error");
	}

	
	perror("here3");
	

	return 0;
}



