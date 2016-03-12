#include <sys/types.h>	//open
#include <sys/stat.h>	//open
#include <fcntl.h>		//open
#include <unistd.h>		//rdwr
#define BUF_SIZE 1023

int main(int argc, char *argv[]) {
	for (int pos = 1; pos < argc; pos++) {
		int fd = open(argv[pos], O_RDWR);
		if (fd < 0) {
			if (argv[pos] = "-") {
				fd = STDIN_FILENO;
			} else {
				write(STDERR_FILENO, "OPEN ERROR", 11);
				continue;
			}
		}
		char buf[BUF_SIZE];
		int rd_len = 0, wr_len = 0;
		while (rd_len = read(fd, buf, BUF_SIZE)) {
			if (rd_len < 0) {
				write(STDERR_FILENO, "READ ERROR", 11);
			}
			int cmpl_len = 0;
			while (rd_len - cmpl_len > 0) {
				wr_len = write(STDOUT_FILENO, buf, rd_len - cmpl_len);
				if (wr_len < 0) {
					write(STDERR_FILENO, "WRITE ERROR", 12);
				}
				cmpl_len += wr_len;
			}
		}
	}
	return 0;
}
