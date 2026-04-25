#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>        // >>> ADDED

// >>> ADDED: client structure
typedef struct s_client {
    int id;
    char *buf;
} t_client;

t_client clients[FD_SETSIZE];
struct pollfd fds[FD_SETSIZE];
int nfds = 0;
int next_id = 0;

char recv_buf[1000000];
char send_buf[1000000];
// <<< END

// >>> COPIED FROM SUBJECT (unchanged)
int extract_message(char **buf, char **msg)
{
    char *newbuf;
    int i;

    *msg = 0;
    if (*buf == 0)
        return (0);
    i = 0;
    while ((*buf)[i])
    {
        if ((*buf)[i] == '\n')
        {
            newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
            if (newbuf == 0)
                return (-1);
            strcpy(newbuf, *buf + i + 1);
            *msg = *buf;
            (*msg)[i + 1] = 0;
            *buf = newbuf;
            return (1);
        }
        i++;
    }
    return (0);
}

char *str_join(char *buf, char *add)
{
    char *newbuf;
    int len;

    if (buf == 0)
        len = 0;
    else
        len = strlen(buf);
    newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
    if (newbuf == 0)
        return (0);
    newbuf[0] = 0;
    if (buf != 0)
        strcat(newbuf, buf);
    free(buf);
    strcat(newbuf, add);
    return (newbuf);
}
// <<< END

// >>> ADDED
void fatal_error(void)
{
    write(2, "Fatal error\n", 12);
    exit(1);
}

void broadcast(int except_fd)
{
    for (int i = 0; i < nfds; i++)
    {
        int fd = fds[i].fd;
        if (fd != except_fd && fd >= 0)
            send(fd, send_buf, strlen(send_buf), 0);
    }
}

void handle_messages(int fd)
{
    char *msg;
    int r;

    while (1)
    {
        r = extract_message(&clients[fd].buf, &msg);
        if (r < 0)
            fatal_error();
        if (r == 0)
            break;

        sprintf(send_buf, "client %d: %s", clients[fd].id, msg);
        broadcast(fd);
        free(msg);
    }
}
// <<< END


int main(int ac, char **av)
{
    int sockfd, connfd;
    unsigned int len;
    struct sockaddr_in servaddr, cli;

    // >>> MODIFIED: argument check
    if (ac != 2)
    {
        write(2, "Wrong number of arguments\n", 26);
        exit(1);
    }
    // <<< END

    memset(clients, 0, sizeof(clients));
    memset(fds, 0, sizeof(fds));

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        fatal_error();

    // >>> ADDED: register listening socket in poll array
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;
    nfds = 1;
    // <<< END

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
    servaddr.sin_port = htons(atoi(av[1]));

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        fatal_error();

    if (listen(sockfd, 10) != 0)
        fatal_error();

    // >>> ADDED: main poll loop
    while (1)
    {
        if (poll(fds, nfds, -1) < 0)
            continue;

        for (int i = 0; i < nfds; i++)
        {
            if (!(fds[i].revents & POLLIN))
                continue;

            if (fds[i].fd == sockfd)
            {
                len = sizeof(cli);
                connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
                if (connfd < 0)
                    fatal_error();
                if (connfd >= FD_SETSIZE)
                {
                    close(connfd);
                    continue;
                }

                fds[nfds].fd = connfd;
                fds[nfds].events = POLLIN;
                clients[connfd].id = next_id++;
                clients[connfd].buf = NULL;
                nfds++;

                sprintf(send_buf, "server: client %d just arrived\n", clients[connfd].id);
                broadcast(connfd);
            }
            else
            {
                int fd = fds[i].fd;
                int r = recv(fd, recv_buf, sizeof(recv_buf) - 1, 0);

                if (r <= 0)
                {
                    sprintf(send_buf, "server: client %d just left\n", clients[fd].id);
                    broadcast(fd);

                    close(fd);
                    free(clients[fd].buf);
                    clients[fd].buf = NULL;

                    // When client disconnects:
                    if (i != 0)                 // <--- DO NOT overwrite index 0
                        fds[i] = fds[nfds - 1];
                    nfds--;
                    i--;
                }
                else
                {
                    recv_buf[r] = 0;
                    clients[fd].buf = str_join(clients[fd].buf, recv_buf);
                    if (!clients[fd].buf)
                        fatal_error();
                    handle_messages(fd);
                }
            }
        }
    }
    // <<< END

    return (0);
}
