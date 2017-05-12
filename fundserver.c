/**
    Handle multiple socket connections with select and fd_set on Linux
*/
  
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
  #define BUFSIZE 1024
#define TRUE   1
#define FALSE  0
#define PORT 8888
 char fileName[20];
#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);


char *proposals = "proposals.txt";
char recvBuff[BUFSIZE+1];
char pathname[] = "/home/mohammed1141123586/TCP/server/proposals/";
int bytesReceived=0;
   FILE *fp;
time_t ticks;
char option1[2], option2[2], option3[2];
int main(int argc , char *argv[])
{
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;
      
    char buffer[1025];  //data buffer of 1K
      
    //set of socket descriptors
    fd_set readfds;
      
    //a message
   // char *message = "ECHO Daemon v1.0 \r\n";
  
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
      
    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
  
    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);
     
    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
      
    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");
     
    while(TRUE) 
    {
        //clear the socket set
        FD_ZERO(&readfds);
  
        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
         
        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            sd = client_socket[i];
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
  
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
    
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("select error");
        }
          
        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master_socket, &readfds)) 
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
          
            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

            for (i = 0; i < max_clients; i++) 
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                     
                    break;
                }
            }
        }

                                    do{
                                            printf("_______Welcome to Proving Fund System______\n");
                                            printf("\n\nYou are now in the server \n");
                                            printf("Student or stuff hass logged in\n");
                                            recv(new_socket,&option1,sizeof(option1), 0);
                                            printf("User chooses %s\n",option1);
                                                if (strcmp(option1, "A")==0)
                                                    {
                                                        bzero(option1, sizeof(option1));
                                                        printf("Staff wants to create proposals \n");
                                                        fileReceive(new_socket, fileName);
                                            
                                                    }
                                                else if  (strcmp(option1, "B")==0)
                                                    {
                                                                 bzero(option1, sizeof(option1));
                                                                 fileReceive(new_socket, fileName);
                                                                 printf("file was received is : %s\n",fileName);
                                                    }
                                                    else if(strcmp(option1, "C")==0)
                                                    {
                                                         printf("sending current propsals");
                                                         viewFiles();
                                                           ViewFilesSend(new_socket);


                                                    }
                                                     else if(strcmp(option1, "D")==0)
                                                     {
                                                        char FileName[30]; 
                                                        char fund[30];
                                                      
                                                        char result[50];


                                                            recv(new_socket, &FileName, sizeof(FileName), 0);
                                                            strcat(FileName, ".txt");
                                                            printf("please enter a status of the file\n");
                                                            gets(result);
                                                            send(new_socket, result, sizeof(result), 0);
                                                            
                                                       // strcpy(fund, recvBuff);
                                                        printf("%s\n, %f\n",FileName);
                                                        printf("wants to exit\n");
                                                        

                                                     }
                                                      else if(strcmp(option1, "E")==0)
                                                     {
                                                         bzero(option1, sizeof(option1));
                                                        printf("wants to exit\n");
                                                       // exit(0);
                                                    }
                                                
                                                      else 
                                                         bzero(option1, sizeof(option1));
                                                        printf("please choose A, B, C D or E \n");
                                         }while(strcmp(option1, "E")==0);

               
                        


        //else its some IO operation on some other socket :)
        for (i = 0; i < max_clients; i++) 
        {
            sd = client_socket[i];
              
            if (FD_ISSET( sd , &readfds)) 
            {
                //Check if it was for closing , and also read the incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                      
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }
                  
                //Echo back the message that came in
                else
                {
                    //set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                    send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    
      }
    return 0;
} 




void fileReceive(int newSocket , char *nameFile){
   recv(newSocket, recvBuff, 20, 0);
      strcpy(fileName, recvBuff);
      printf("Server is receiving file called : %s\n",fileName);
      strcat(pathname,fileName);
      printf("%s\n", pathname);

     // bzero(recvBuff, sizeof(recvBuff));
        /* Open the file that we wish to transfer */
        /* Create file where data will be stored */
 
    fp = fopen(pathname, "ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
          exit(1);
    }

    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(newSocket, recvBuff, BUFSIZE)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        bzero(recvBuff, sizeof(recvBuff));
        // printf("%s \n", recvBuff);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

     
        sleep(1);
        fclose(fp);
}

void viewFiles() {
 
    int link[2];
  pid_t pid;
  char foo[4096];

  if (pipe(link)==-1)
    die("pipe");

  if ((pid = fork()) == -1)
    die("fork");

  if(pid == 0) {

    dup2 (link[1], STDOUT_FILENO);
    close(link[0]);
    close(link[1]);
    execl("/bin/ls", "ls", "/home/mohammed1141123586/TCP/server/proposals", NULL);
    die("execl");

  } else {

    close(link[1]);
    int nbytes = read(link[0], foo, sizeof(foo));
    //printf("Output: (%.*s)\n", nbytes, foo);
    wait(NULL);



    FILE * fp2;

      fp2 = fopen(proposals,"w+");
    if(fp2 == NULL){
        printf("File Cannot open\n");
        fclose(fp2);
        exit(0);
    }
fprintf(fp2, "\t\t\tProposals files\n");
 fprintf(fp2, "Proposals Files Received:\n(%.*s)\n\n", nbytes, foo);
  fclose(fp2);

  }  

  
  
}


void ViewFilesSend(int newsocket){
            
    

         FILE *fp = fopen("proposals.txt","rb");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        } 
        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(newsocket, buff, nread);
            }
            close(newsocket);

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }

       // close(connfd);
        sleep(1);
        }
 