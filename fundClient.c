//#include "inet.h"

  
#include <stdio.h>
#include <string.h>   
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   
#include <arpa/inet.h>    
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 
#include <signal.h>

  
#define TRUE   1
#define FALSE  0
#define PORT 8888

//#include "clientFunct.c"
#define BUFSIZE 1024
void sigproc(){
  signal(SIGINT, sigproc);
  printf("you have pressed ctrl-c \n");
}
void quitproc(){
  printf("ctrl-\\ pressed to quit \n");
  exit(0);
}

char option1[2];
char fileName[20];
char sendBuff[BUFSIZE+1];
char pathname[] = "/home/mohammed1141123586/TCP/client/";
  char recvBuff[BUFSIZE+1];
int bytesReceived = 0;


char *proposals = "proposals.txt";



main(int argc, char *argv[]){
    int clientSocket;
    struct sockaddr_in serverAddr;
  
    memset(recvBuff, '0', sizeof(recvBuff));
    socklen_t addr_size;
    char sig1[]="A";
    char sig2[] = "B";


    if (argc <= 1){
    printf("How to use : %s remoteIPaddress [Example : ./client 127.0.0.1]\n", argv[0]);
    exit(1);
    }

    bzero ( (char *) &serverAddr, sizeof(serverAddr));
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, argv[1], &serverAddr.sin_addr);


  if ( (clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
  perror("client: socket() error \n");
  exit(1);
  }



    /* Attempt a connection */

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("client: connect(error)\n");
        exit(1);
    }

                signal(SIGINT, sigproc);
                signal(SIGQUIT, quitproc);
                printf("ctrl-c disabled use ctrl-\\ to quit \n");
               
   


            
                  

            
                do{
                  printf("_______Welcome to Proving Fund System______\n");
                  printf("\n\nplease specify what action you want to do: \n");
                  printf("A ) Create file and send it\n");
                  printf("B ) Send ready File\n");
                  printf("C ) View Existed Proposals\n");
                  printf("D ) Check files Status \n");
                  printf("E) Exit\n");


               
                      printf("Option => ");
                      scanf("%s", option1);
                      printf("%s\n",option1);
                      send(clientSocket,&option1,sizeof(option1), 0);

                          if(strcmp(option1, "A")==0)
                              {
                                                                    int childpid;
                                      if ((childpid=fork())==-1){
                                      perror("cannot fork");
                                      exit(1);
                                      
                                    }
                                    else if (childpid == 0){
                                               printf("Create proposal \n");
                                               createFile();
                                                printf("Now File will be sent to server\n");
                                                sendFile(clientSocket, fileName);
                                    }else {
                                      wait((int*)0);
                                      //waitpid(childpid, 0,0);
                                      sleep(1);
                                     printf("Thank you for using our application, Please check in later time about the status of your propsal\n");
                                      exit(0);
                                    }

                             
                                   
                                    
                              }
                          else if  (strcmp(option1, "B")==0)
                          {
                                   int childpid;
                                      if ((childpid=fork())==-1){
                                      perror("cannot fork");
                                      exit(1);
                                      
                                    }
                                    else if (childpid == 0){
                                                printf("write the file name: ");
                                                scanf("%s",fileName);
                                                strcat(fileName,".txt");
                                                sendFile(clientSocket, fileName);
                                    }else {
                                      wait((int*)0);
                                      //waitpid(childpid, 0,0);
                                      sleep(1);
                                     printf("Thank you for using our application, Please check in later time about the status of your propsal\n");
                                      exit(0);
                                    }
                                
                          }
                          else if(strcmp(option1, "C")==0)
                          {       

                                   int childpid;
                                      if ((childpid=fork())==-1){
                                      perror("cannot fork");
                                      exit(1);
                                      
                                    }
                                    else if (childpid == 0){
                                              printf("these are the proposals in the Server\n");
                                              ViewFilesReceive(clientSocket);
                                    }else {
                                      wait((int*)0);
                                      //waitpid(childpid, 0,0);
                                      sleep(1);
                                     printf("Thank you for using our application, Please check in later time about the status of your propsal\n");
                                      exit(0);
                                    }
                            
                                

                          }
                           else if(strcmp(option1, "D")==0)
                          {       
                                char FileName[30];
                             
                                char result[50];
                                gets(FileName);
                                printf("please write your file name\n");
                                gets(FileName);
                                send(clientSocket, FileName,sizeof(FileName),0);
                                printf("please wait for a moment to check: \n");
                                recv(clientSocket, &result, sizeof(result), 0);
                                printf("the %s   propsal is %s\n", FileName, result);


                          }
                          else if (strcmp(option1, "E")==0){
                              exit(0);
                              printf("Thank you\n");
                            }
                            else
                              printf("please choose A, B, C or D\n");
                 }while(strcmp(option1 , "E")==0);
                       
  
}
    




  void showProposals() {
  FILE * fp;
  char ch;
  fp = fopen (proposals, "r+");
  
  if (fp == NULL){
    perror("the file cannot open ");
    exit(EXIT_FAILURE);
  }

  while ((ch = fgetc(fp)) != EOF)
    printf("%c ", ch);

    
  fclose(fp);

  }
  



void createFile(){
    char name[50], staffID[20], title[30], org[30], desc[150];
    float fund;
    FILE * fp;
time_t t = time(NULL);
struct tm *tm = localtime(&t);
char Date[64];
strftime(Date, sizeof(Date), "%c", tm);
  gets(name);
    printf("*********Hello To The Fund Proving System!**********\n");
   printf("Could you please write your name?\n");
    gets(name);
    printf("Could you please write your staff ID?\n");
    gets(staffID);
    printf("please write the title of your proposal:\n");
    gets(title);
    printf("please write the name of the club or sociaty:\n");
    gets(org);
  printf("please write a brief description about your proposal:\n");
    gets(desc);
  printf("How much fund you are prposing :\n");
    scanf("%f", &fund);
   printf("Please write your file name\n");
   scanf("%s",fileName);
    strcat(fileName,".txt");
 

  fp = fopen(fileName,"w+");
    if(fp == NULL){
        printf("File Cannot open\n");
        fclose(fp);
     
    }
fprintf(fp, "\t\t\tProposal For Funding\n");
fprintf(fp, "\t\t\tTitle: %s\n", title);
fprintf(fp, "Name: %s\n", name);
fprintf(fp, "ID: %s\n", staffID);
fprintf(fp, "Date and Time: %s\n", Date);
fprintf(fp, "Club / Sociaty: %s\n", org);
fprintf(fp, "\nDesciption: %s\n\n", desc);
fprintf(fp, "\nAmmount Of Money Required: %f\n\n", fund);


fclose(fp);
    
   
    
}



  void sendFile( int socket1, char *Fname){
                          send(socket1,Fname,20, 0);
      
                          FILE *fp2 = fopen(Fname,"rb");
                          if(fp2==NULL)
                          {
                          printf("File opern error");
                                exit(1);  
                          }   

                        /* Read data from file and send it */
                        while(1)
                        {
                            /* First read file in chunks of 256 bytes */
                            unsigned char buff[BUFSIZE]={0};
                            int nread = fread(buff,1,sizeof(buff),fp2);
                            printf("Bytes read %d \n", nread);        

                            /* If read was success, send data. */
                            if(nread > 0)
                            {
                                printf("Sending \n");
                                write(socket1, buff, nread);
                            }

                            /*

                             * Either there was error, or we reached end of file.
                             */
                            if (nread < 256)
                            {
                                if (feof(fp2))
                                    printf("End of file\n");
                                if (ferror(fp2))
                                    printf("Error reading\n");
                                  break;
                            }


                        }

                    }

    void ViewFilesReceive(int sokefd){
 

          /* //Create file where data will be stored 
     FILE *fp;
    fp = fopen("proposals.txt", "ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }*/

    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(sokefd, recvBuff, 256)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        write(1,recvBuff ,bytesReceived);
        // printf("%s \n", recvBuff);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

}
