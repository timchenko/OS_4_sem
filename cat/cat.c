#include <sys/types.h>	//open
#include <sys/stat.h>   //open
#include <fcntl.h>      //open
#include <unistd.h>		//rdwr
#define BUF_SIZE 1023

int main(int argc, char **argv) {
	int fd;
	if (argc < 2) {
		fd = STDIN_FILENO;
	} else {
		fd = open(argv[1], O_RDONLY);
	}
	if (fd == -1) {
		write(STDERR_FILENO, "OPEN ERROR\n", 12);
	}
	char buf[BUF_SIZE];
	int rd_len = 0, wr_len = 0;
	while (rd_len = read(fd, buf, BUF_SIZE)) {
		if (rd_len == -1) {
			write(STDERR_FILENO, "READ ERROR\n", 12);
			continue;
		}
		int cmpl_len = 0;
		while (rd_len - cmpl_len > 0) {
			wr_len = write(STDOUT_FILENO, buf + cmpl_len, rd_len - cmpl_len);
			if (wr_len == -1) {
				write(STDERR_FILENO, "WRITE ERROR\n", 13);
				continue;
			}
			cmpl_len += wr_len;
		}
	}
	return 0;
}
