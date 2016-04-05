#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string>
#include <vector>
#include <string.h>
#define BUF_SIZE 1024

using namespace std;

vector<pid_t> son_pids(0);

void handler(int signum, siginfo_t* siginfo, void* context) {
    for (int pos = 0; pos < son_pids.size(); pos++) {
		kill(son_pids[pos], SIGINT);
	}
}

void init_catcher(struct sigaction &catcher) {
    catcher.sa_sigaction = &handler;
    catcher.sa_flags = SA_SIGINFO;
    if (sigemptyset(&catcher.sa_mask) ||
        sigaddset(&catcher.sa_mask, SIGINT) ||
        sigaction(SIGINT, &catcher, NULL)) {
      perror("Init sigaction error!\n");
	}
}

int reader(vector<vector<string> > &pipe_comms) {
	char buf[BUF_SIZE];
	int read_len = 0;
	string comm = "";
	pipe_comms.clear();
	vector<string> comms(0);
	bool cont = true;
	while (cont) {
		read_len = read(STDIN_FILENO, buf, BUF_SIZE);
		for (int pos = 0; pos < read_len; pos++) {
			if (buf[pos] == ' ') {
				comms.push_back(comm);
				comm = "";
			} else if (buf[pos] == '|') {
				comms.push_back(comm);
				comm = "";
				pipe_comms.push_back(comms);
				comms.clear();
			} else if (buf[pos] == '\n') {
				comms.push_back(comm);
				comm = "";
				pipe_comms.push_back(comms);
				comms.clear();
				cont = false;
			} else {
				comm += buf[pos];
			}
		}
		if (read_len == 0) 
			return 0;
	}
	return 1;
}

int forker(vector<vector<string> > const &comms, int pos) {
	int comm_stat;
	son_pids.push_back(fork());
	if (son_pids.back() == 0) {
		execvp(comms[pos][0].c_str(), (char* const*)comms[pos].data());
		return 0;
	}
	else {
		if (pos < comms.size()) {
			forker(comms, pos + 1);
		} else {
			for (int i = 0; i < comms.size(); i++) {
				waitpid(son_pids[i], &comm_stat, WIFEXITED(comm_stat));
				son_pids.erase(son_pids.begin() + i);
			}
			write(STDOUT_FILENO, "$\n", 2);
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
    struct sigaction catcher;
	init_catcher(catcher);
	vector<vector<string> > comms(0);
	write(STDOUT_FILENO, "$\n", 2);
	if (!reader(comms)) return 0;
	do {
		forker(comms, 0);
	} while (reader(comms));
	return 0;
}

	




	/*int pipefd[2];
	pipe(pipefd);
	pid_t cat, grep;
	int cat_status, grep_status;
	cat = fork();
	if (cat == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execlp("cat", "cat", argv[1], NULL);
	}
	else {
		grep = fork();
		if (grep == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			execlp("grep", "grep", "int", NULL);
		}
		else {
			waitpid(cat, &cat_status, WIFEXITED(cat_status));
			waitpid(grep, &grep_status, WIFEXITED(grep_status));
		}
	}
	return;*/

