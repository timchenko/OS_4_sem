#include <unistd.h>		//rdwr
#define BUF_SIZE 1023

int main() {
	char buf[BUF_SIZE];
	int rd_len = 0, wr_len = 0;
	while (rd_len = read(STDIN_FILENO, buf, BUF_SIZE)) {
		if (rd_len == -1) {
			write(STDERR_FILENO, "READ ERROR\n", 12);
			break;
		}
		int cmpl_len = 0;
		while (rd_len - cmpl_len > 0) {
			wr_len = write(STDOUT_FILENO, buf + cmpl_len, rd_len - cmpl_len);
			if (wr_len == -1) {
				write(STDERR_FILENO, "WRITE ERROR\n", 13);
				break;
			}
			cmpl_len += wr_len;
		}
	}
	return 0;
}
