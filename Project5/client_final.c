#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PACKET_SIZE 1024
#define maxNumOfPackets 100 //max number of packets client can accept

int packetNum;  //current packet number being read in
int numOfPacks; //number of packets added to packets
char * packets[maxNumOfPackets];   //data structure to store all of our packets we will initialize it to be able to receive 100 packets but we could increase this to handle more packets

pthread_mutex_t packetNumMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t packetsMutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct SERVER   //struct to pass with each thread
{
    char * ip;
    int port;
}SERVER;

/*
    This client will spawn a thread for each server passed in and each thread will run get packets
*/

/*
    getPackets will continue reading in packets until it gets 0 bytes and then it will return. It will store all of its packets in packets[]
*/
void * getPackets(void * serv)
{
    SERVER * myserv = serv;
    int bytesRead = 1;
    while(1)
    {
        char * buffer = malloc(PACKET_SIZE+1);  //need room for null term
        int mySocket;
        int myPackNum; //local variable so your current packet number is not changed
        char blockReq[150];
        struct sockaddr_in serv_addr;

        pthread_mutex_lock(&packetNumMutex);
        myPackNum = packetNum;  //store my packet number
        packetNum++;
        pthread_mutex_unlock(&packetNumMutex);

        if((mySocket = socket(AF_INET,SOCK_STREAM,IPPROTO_IP)) < 0)    //create a socket
        {
            perror("Socket");
            exit(errno);
        }

        memset(&serv_addr,0,sizeof(serv_addr)); //create & zero struct
        serv_addr.sin_family = AF_INET; //Select internet protocol
        serv_addr.sin_port = htons(myserv->port);   //set the port
        serv_addr.sin_addr.s_addr = inet_addr(myserv->ip);

        if((connect(mySocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))!=0) //connect
        {
            printf("Couldn't connect to port %d\n",myserv->port);
            exit(errno);
        }

        bzero(buffer,PACKET_SIZE);
        sprintf(blockReq,"%d",myPackNum);
        if(send(mySocket,blockReq,sizeof(blockReq),0)<0)
        {
            perror("Couldn't write to socket");
            exit(errno);
        }
        bytesRead = recv(mySocket,buffer,PACKET_SIZE,0);

        if(bytesRead <= 0)  //clean up and exit if no bytes received
        {
            free(myserv);
            free(buffer);
            close(mySocket);
            return (void*)1;
        }

        pthread_mutex_lock(&packetsMutex);
        packets[myPackNum] = buffer;
        numOfPacks++;
        pthread_mutex_unlock(&packetsMutex);

        close(mySocket);
    }
}

/*
    Main spawns all the threads and cleans them up. Once they are all finished grabbing packets it will write them all to output.txt.
    The packets will be in order in packets[];
*/
int main(int argc,char *argv[])
{
    FILE *output;    //will be the output we write to
    int i;

    int numServers;

    if(argc < 3 || !argc%2)
    {
        printf("Usage: ./client2 <ip addr1> <port1> <ip addr2> <port2>....");
        exit(-1);
    }

    numServers = (argc-1)/2;
    pthread_t threads[numServers];
    void * threadSuc[numServers];

    for(i = 1; i <= numServers; i++)    //fill up buffers with each buffer
    {
        SERVER * serv = malloc(sizeof(SERVER));
        serv->ip = argv[(i*2)-1];
        serv->port = atoi(argv[i*2]);
        pthread_create(&threads[i-1], NULL, getPackets, serv);
    }

    for(i = 0; i < numServers; i++) //wait til threads all finish
    {
        pthread_join(threads[i], &threadSuc[i]);
    }

    output = fopen("output.txt","w");   //open our file output.txt to be written to
    for(i = 0; i < numOfPacks; i++) //write each buffer to output.txt and free each buffer
    {
        fwrite(packets[i],1,strlen(packets[i]),output);
        free(packets[i]);   //free each buffer
    }
    fclose(output);

    return 0;
}


