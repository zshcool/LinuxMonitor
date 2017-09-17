#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include <sys/types.h>
//#include <sys/select.h>
#include <sys/time.h>
#include <poll.h>

struct log_item
{
    int pid;
    int ppid;
    char buf[1024];
};

int unblockfd(int fd)
{
    int flag;
    flag = fcntl(fd, F_GETFL, 0);
    if(flag == -1) return -1;
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
    if(flag == -1) return -1;

    return 0;
}


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




int main1()
{
    int fd;
    int ret;
    int ready;
    int read_size;
    fd_set fdset;
    struct timeval timeout;
    
    check_registry();
    registry();

    fd = open("/proc/antiylm/lmlog", O_RDONLY | O_NONBLOCK);
    printf("%d\n", fd);
    if(fd == -1)
    {
        printf("open failed,error:%d", errno);
        return errno;
    }
/*
    ret = unblockfd(fd);
    if(ret == -1)
    {
        printf("set unblock failed,error:%d", errno);
        return errno;
    }
*/    
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    FD_SET(fd, &fdset);

    while(1)
    {
        ready = select(1, &fdset, NULL, NULL, &timeout);
        if (ready == -1)
        {
            printf("select,error:%d", errno);
            return errno;
        }else if (ready == 0){
            printf("time out\n");
            continue;
        }else{
            printf("ret:%d\n", ready);
            if(FD_ISSET(fd, &fdset))
                {printf("ready!\n");}
            struct log_item item;
            read_size = read(fd, &item, sizeof(item));
            if (read_size == 0) continue;
            printf("size:%d", read_size);
            printf("pid:%d\n", item.pid);
            printf("ppid:%d\n", item.ppid);
        }
    }

    close(fd);

    registry_out();
}



int main2()
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
            printf("size:%d", read_size);
            printf("pid:%d\n", item.pid);
            printf("ppid:%d\n", item.ppid);
        }
    }

    close(fd);

    registry_out();
    return 0;
}

int main()
{
    main2();
}


