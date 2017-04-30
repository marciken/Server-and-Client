#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
#include <stdlib.h>
#define STR_LEN 500

void binary_converter(char *);

void binary_converter(char *p)
{
	int str_len = strlen(p);
	int i, j, k = 8 ,num;
	int binary[8 * str_len];

	for(i = 0; i < 8*str_len; i++){
		binary[i] = 0;
	}
	
	for(i = 0; i < str_len; i++){
		j = k - 1;
		num = p[i];//num = *(p+i);

		while(num != 0){
			binary[j--] = num % 2;
			num /= 2;
		}

		k += 9; // because the next position of second character is 				at index of (7+8)=15
		}

	printf("\nBinary Converter :");

	for(i = 1; i < 8*str_len; i++){
		printf("%d", binary[i - 1]);
			
		if(i % 8 == 0){
			printf(" ");
		}
	}
	printf("\n");
}

int main(int argc , char *argv[])
{
        
	int sock;
	struct sockaddr_in server;
	char message[300];
	char server_reply[STR_LEN];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("COULD NOT create socket\n\n");
	}
	puts("\nSocket SUCCESSFULLY created\n\n");
	
	server.sin_addr.s_addr = inet_addr("192.168.254.130");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8000 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. ERROR! \n\n");
		return 1;
	}
	
	puts("......CONNECTED!\n");
	
	//keep communicating with server
	while(1)
	{
		printf("Text a string of characters/digits: ");
		scanf("%s" , message);
		
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("\nFailed to send data");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , STR_LEN , 0) < 0)
		{
			puts("\nrecv failed");
			break;
		}

		puts("\nServer reply :");
		puts(server_reply);

		fgets(server_reply, STR_LEN + 1, stdin);
		server_reply[strlen(server_reply) - 1] = '\0';
		binary_converter(server_reply);

		
	}
	
	//close(sock);
	return 0;
}
