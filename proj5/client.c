#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 8192 /* Max text line length */

int open_clientfd(char* hostname, int port) {
  // The client's socket file descriptor.
  int clientfd;

  // The hostent struct is used to get the IP address of the server
  // using DNS.
  //
  // struct hostent {
  //   char *h_name;        // official domain name of host
  //   char **h_aliases;    // null-terminated array of domain names
  //   int  h_addrtype;     // host address type (AF_INET)
  //   int  h_length;       // length of an address, in bytes
  //   char **h_addr_list;  // null-terminated array of in_addr structs
  // };
  struct hostent *hp;

  // serveraddr is used to record the server information (IP address
  // and port number).
  //
  // struct sockaddr_in {
  //   short            sin_family;   // e.g. AF_INET
  //   unsigned short   sin_port;     // e.g. htons(3490)
  //   struct in_addr   sin_addr;     // see struct in_addr, below
  //   char             sin_zero[8];  // zero this if you want to
  // };
  struct sockaddr_in serveraddr;

  printf("Echo Client is creating a socket.\n");

  // First, we create the socket file descriptor with the given
  // protocol and protocol family.
  if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

  // The socket API requires that you zero out the bytes!
  bzero((char *)&serveraddr, sizeof(serveraddr));

  // Record the protocol family we are using to connect.
  serveraddr.sin_addr.s_addr = inet_addr(hostname);
  serveraddr.sin_family = AF_INET;
  // Convert the port from host byte order to network byte order and
  // store this in the server address structure.
  serveraddr.sin_port = htons(port);

  printf("Echo Client is trying to connect to %s (%s:%d).\n", hostname,
         inet_ntoa(serveraddr.sin_addr), port);

  // Establish a connection with the server.
  if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    return -1;

  printf("Echo Client connected.\n");

  // Return the connected file descriptor.
  return clientfd;
}

int calculate(char** buf){ //return 1 if flag was not received
  //takes in "cs230 STATUS 37 / 5\n" or "cs230 <FLAG> BYE\n"
  //changes buf to "cs230 <ANSWER>\n"

  // char in[20] = "cs230 STATUS 37 / 5\n";

  char *buf1;
    
  /* calloc() function will allocate the memory & initialize its to the NULL*/
  buf1 = calloc(strlen(*buf)+1, sizeof(char)); 
  strcpy(buf1, *buf);

  char* pch = strtok(buf1, " "); 
  char* toks[5];
  int i = 0;
  while(pch){
    toks[i] = pch;
    i++;
    pch = strtok(NULL, " "); 
  }

  if(strcmp(toks[1], "STATUS") == 0){
    int op1 = atoi(toks[2]);
    int op2 = atoi(toks[4]);
    int sol;

    switch (toks[3][0]){
    case '+':
      sol = op1 + op2;
      break;
    case '-':
      sol = op1 - op2;
      break;
    case '*':
      sol = op1 * op2;
      break;
    case '/':
      sol = op1 / op2;
      break;
    case '%':
      sol = op1 % op2;
      break;        
    default:
      printf("oopsie\n");
      break;
    }
    
    sprintf(buf1, "cs230 %i\n", sol);
    strcpy(*buf, buf1);
    free(buf1);


    return 1;
  } else if(strcmp(toks[1], "FLAG") == 0){
    free(buf1);
    return 0;
  }
}

int client(int argc, char **argv) {
  // The client socket file descriptor.
  int clientfd;

  // The port number.
  int port;

  // Variable to store the host/server domain name.
  char* host;

  // A buffer to receive data from the server.
  char buf[MAXLINE];

  // First, we check the program arguments:
  if (argc != 4) {
    fprintf(stderr, "usage: %s <email> <host> <port>\n", argv[0]);
    exit(0);
  }

  // First argument is host, second is port:
  host = argv[3];
  port = atoi(argv[2]);

  // Open the client socket file descriptor given the host and port:
  clientfd = open_clientfd(host, port);
  char* greeting = "cs230 HELLO etrimble@umass.edu\n";
  ssize_t ns = send(clientfd, greeting, strlen(greeting), 0);
  printf("send: %s", greeting);

  while(1) {
    ssize_t nr = recv(clientfd, buf, MAXLINE, 0);
    
    buf[strlen(buf)] = '\0';
    printf("receive: %s", buf);

    char* bufptr = &(buf[0]);
    if(calculate(&bufptr) == 1){
      printf("send: %s", buf);
      ssize_t ns = send(clientfd, buf, strlen(buf), 0);
    }
    else{
      printf("flag received: %s", buf);
      break;
    }

    // Add a newline back on:
    buf[strlen(buf) + 1] = '\0';
    buf[strlen(buf)] = '\n';
    fputs(buf, stdout);

    // Display and read again:
    printf("echo (%u bytes): ", nr);

  }

  // Close the file descriptor:
  close(clientfd);
  exit(0);
}

int main(int argc, char **argv) {
  client(argc, argv);
}