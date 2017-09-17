#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
//#include <sys/select.h>
#include <sys/time.h>
#include <poll.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define LOGSIZE 1024
#define NAMESIZE 16
#define COLON "&:"
#define SPLIT "&/"

struct log_item
{
    int pid;
    int ppid;
    char syscall[NAMESIZE];
    char name[NAMESIZE];
    char pname[NAMESIZE];
    char buf[LOGSIZE];
};

struct addrinfo
{
    int len;
    int fd;
    char data[256];
};



int check_registry()
{
    int fd;
    int registry_pid;

    fd = open("/proc/antiylm/registry", O_RDONLY);
    printf("%d\n", fd);
    if(fd == -1)
    {
        printf("open failed,error:%d\n", errno);
        return errno;
    }

    read(fd, &registry_pid, sizeof(int));
    close(fd);

    if(registry_pid == -1)
    {
        return 1;
    }else{
        printf("pid:%d already registry!\n", registry_pid);
        return 0;
    }
}


void registry()
{
    int fd;
    int pid = getpid();

    fd = open("/proc/antiylm/registry", O_WRONLY);
    printf("%d\n", fd);
    if(fd == -1)
    {
        printf("open failed,error:%d\n", errno);
    }
    
    write(fd, &pid, sizeof(int));

    close(fd);
}

void registry_out()
{
    int fd;
    int pid = -1;

    fd = open("/proc/antiylm/registry", O_WRONLY);
    printf("%d\n", fd);
    if(fd == -1)
    {
        printf("open failed,error:%d\n", errno);
    }

    write(fd, &pid, sizeof(int));

    close(fd);
}




int main()
{
    int fd;
    int ret;
    int ready;
    int read_size;
    struct pollfd poll_fd;
    
    check_registry();
    registry();

    fd = open("/proc/antiylm/lmlog", O_RDONLY | O_NONBLOCK);
    printf("%d\n", fd);
    if(fd == -1)
    {
        printf("open failed,error:%d", errno);
        return errno;
    }

    poll_fd.fd = fd;
    poll_fd.events = POLLIN;

    while(1)
    {
        ready = poll(&poll_fd, 1, 5000);
        printf("ready:%d\n", ready);
        if (ready == -1)
        {
            printf("select,error:%d", errno);
            return errno;
        }else if (ready == 0){
            printf("time out\n");
            continue;
        }else{
            printf("ret:%d\n", ready);

            struct log_item item;
            read_size = read(fd, &item, sizeof(item));
            if (read_size == 0) continue;

            printf("pid:%d\n", item.pid);
            printf("ppid:%d\n", item.ppid);
            printf("name:%s\n", item.name);
            printf("pname:%s\n", item.pname);
            printf("syscall:%s\n", item.syscall);
            if(strcmp(item.syscall, "sys_execve") == 0)
            {
                printf("buf:%s\n", item.buf);
            }
            else if(strcmp(item.syscall, "sys_connect") == 0)
            {
                struct addrinfo *info = (struct addrinfo *)(item.buf);
                if (info->len == 16)
                {
                    struct sockaddr_in* addr = (struct sockaddr_in*)(info
->data);
                    printf("ip:%s, port:%u", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
                    
                }
            }
        }
    }

    close(fd);

    registry_out();
    return 0;
}



