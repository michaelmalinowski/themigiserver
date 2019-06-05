#include<signal.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
    printf("Starting\n");
    struct sockaddr_in myaddr ,clientaddr;
    int sockid,newsockid;
    sockid=socket(AF_INET,SOCK_STREAM,0);
    memset(&myaddr,'0',sizeof(myaddr));
    myaddr.sin_family=AF_INET;
    myaddr.sin_port=htons(8888);
    myaddr.sin_addr.s_addr=inet_addr("migiserver.ddns.net");
    if(sockid==-1)
    {
        printf("socket");
    }
    int len=sizeof(myaddr);
    if(bind(sockid,( struct sockaddr*)&myaddr,len)==-1)
    {
        printf("bind");
    }
    if(listen(sockid,10)==-1)
    {
        printf("listen");
    }
    int pid,new;
    static int counter=0;
    printf("Listening...");
    while(1)
    {
        printf("Listening...");
        new = accept(sockid, (struct sockaddr *)&clientaddr, &len);

        if ((pid = fork()) == -1)
        {
            close(new);
            continue;
        }
        else if(pid > 0)
        {
            close(new);
            counter++;
            printf("here2\n");
            continue;
        }
        else if(pid == 0)
        {
            char buf[100];

            counter++;
            printf("here 1\n");
            snprintf(buf, sizeof buf, "hi %d", counter);
            send(new, buf, strlen(buf), 0);
            close(new);
            break;
        }
      }
    printf("here3");
    close(sockid);
    return 0;
}
