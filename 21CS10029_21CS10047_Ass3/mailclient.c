
/*    THE CLIENT PROCESS */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFFER 100


int verify_ip(char* ip){
    if (strlen(ip)>15) return -1;
    char delim[] = ".";
    int dotcount = (0);
    // ip[strlen(ip)] = '\0';
    for (int i = 0;i<strlen(ip);i++) {
        if(ip[i]=='.')dotcount++;
    }
    //printf("%d\n", dotcount);
    if (dotcount!=3) return -2;
    
    char* ptr =strtok(ip,delim);

    while(ptr!= NULL) {
        int part_of_ip = atoi(ptr);
        //printf("%d\n",part_of_ip);
        if(part_of_ip>255 || part_of_ip<0) return -3;
        ptr = strtok(NULL, delim);
    }

    return 0;
}


int main()
{
	int			sockfd ;
	struct sockaddr_in	serv_addr;

	int i;
	char buf[100];

	/* Opening a socket is exactly similar to the server process */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Unable to create socket\n");
		exit(0);
	}

	/* Recall that we specified INADDR_ANY when we specified the server
	   address in the server. Since the client can run on a different
	   machine, we must specify the IP address of the server. 

	   In this program, we assume that the server is running on the
	   same machine as the client. 127.0.0.1 is a special address
	   for "localhost" (this machine)
	   
	/* IF YOUR SERVER RUNS ON SOME OTHER MACHINE, YOU MUST CHANGE 
           THE IP ADDRESS SPECIFIED BELOW TO THE IP ADDRESS OF THE 
           MACHINE WHERE YOU ARE RUNNING THE SERVER. 
    	*/

	char required_ip[BUFFER];
    printf("Enter server's IP: ");
    scanf("%s", required_ip);
    printf("\n");
    
    char ipcopy[BUFFER];
    strcpy(ipcopy,required_ip);
    // printf("ipcopy %s\n",ipcopy);
    // printf("required_ip %s\n",required_ip);
    int ipcode = verify_ip(ipcopy);
    // printf("ipcode %d\n",ipcode);

    while (ipcode != 0) {
        printf("Enter vaild ip\n");
        printf("Enter server's IP: ");
        scanf("%s", required_ip);
        char ipcopy[BUFFER];
        strcpy(ipcopy,required_ip);
        ipcode = verify_ip(ipcopy);
        
        printf("ipcode %d\n",ipcode);
        printf("\n");
    }

    printf("required_ip after verify %s\n",required_ip);


	serv_addr.sin_family	= AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
	// inet_aton(required_ip, &serv_addr.sin_addr);
	serv_addr.sin_port	= htons(20000);

	/* With the information specified in serv_addr, the connect()
	   system call establishes a connection with the server process.
	*/
	if ((connect(sockfd, (struct sockaddr *) &serv_addr,
						sizeof(serv_addr))) < 0) {
		perror("Unable to connect to server\n");
		exit(0);
	}

	char username[BUFFER];
    char password[BUFFER];

    printf("\nEnter username: ");
    scanf("%s",username);

    printf("Enter password: ");
    scanf("%s",password);
    printf("\n");


    while (1) {
        int option;
        printf("Choose option: \n 1. Manage Mail : Shows the stored mails of the logged in user only\n 2. Send Mail : Allows the user to send a mail\n 3. Quit : Quits the program.\n: ");
        scanf("%d",&option);
        if (option==1) {
            printf("This part is to be covered during final during submission.\n");
            continue;
        }

        if (option==2) {
            // SKIPPING THIS FORMAT CHECK METHOD FOR NOW AS MENTIONED IN THE ASSIGNMENT
            char mydomain[BUFFER];
            printf("\nEnter your domain: ");
            scanf("%s", mydomain);

            char recipient[BUFFER];

            printf("Enter recipient: ");
            scanf("%s", recipient);

            char theirdomain[BUFFER];
            printf("Enter their domain: ");
            scanf("%s", theirdomain);

            char subject[BUFFER];
            printf("\nEnter mail subject: ");
            scanf(" %[^\n]s", subject);

            char fromline[BUFFER];
            char toline[BUFFER];
            char subjectline[BUFFER];
            char messagebody[BUFFER][BUFFER];

            strcat(fromline,"From: ");
            strcat(toline,"To: ");
            strcat(subjectline, "Subject: ");
            
            strcat(fromline,username);
            strcat(fromline,"@");
            strcat(fromline, mydomain);

            strcat(toline, recipient);
            strcat(toline, "@");
            strcat(toline, theirdomain);

            strcat(subjectline, subject);

            printf("\n%s\n",fromline);
            printf("%s\n",toline);
            printf("%s\n",subjectline);

            // char tcpbuffer[BUFFER];

            // for(i=0; i < BUFFER; i++) tcpbuffer[i] = '\0';

            // recv(sockfd,tcpbuffer,BUFFER,0);
            // //tcpbuffer should have 220 <server_domain> wala msg
            // char* ptr;

            // ptr = strtok(tcpbuffer," ");
            // int received_code = atoi(ptr);

            // if(received_code!=220) {
            //     printf("Invalid connection");
            //     return 2;
            // }

            // //tcpbuffer should start from just after the first space (the < char)

            // ptr = strtok(tcpbuffer,">");
            // //ptr should now have the server domain name

            // char helomessage[BUFFER];
            // strcat(helomessage,"HELO ");
            // strcat(helomessage,mydomain);

            // strcpy(tcpbuffer, helomessage);

            // send(sockfd, tcpbuffer, strlen(tcpbuffer)+1, 0);
            // //sends HELO <clientdom>

            // for(i=0; i < BUFFER; i++) tcpbuffer[i] = '\0';

            // recv(sockfd, tcpbuffer,BUFFER,0);
            // //should have 250 if nothing broke
            // ptr = strtok(tcpbuffer," ");
            // received_code = atoi(ptr);

            // if(received_code!=250) {
            //     printf("Domain handshake(?) didn't work");
            //     return 3;
            // } 

            

            /*
            SAMPLE TCP

            C: <client connects to SMTP port>
            S: 220 <iitkgp.edu> Service ready
            C: HELO iitkgp.edu // sending host identifies self
            S: 250 OK Hello iitkgp.edu // receiver acknowledges
            C: MAIL FROM: <ag@iitkgp.edu> // identify sending user
            S: 250 <ag@iitkgp.edu>... Sender ok // receiver acknowledges
            C: RCPT TO: gb@iitkgp.edu // identify target user
            S: 250 root... Recipient ok // receiver acknowledges, if doesn't exist, will be 550
            C: DATA
            S: 354 Enter mail, end with "." on a line by itself
            C: From: ag@iitkgp.edu
            C: To: gb@iitkgp.edu
            C: Subject: Test mail
            C: This is a test mail.
            C: How are you doing?
            C: . // end of multiline send
            S: 250 OK Message accepted for delivery
            C: QUIT // sender signs off
            S: 221 iitkgp.edu closing connection // receiver disconnects
            C: <client hangs up>
            */


            exit(0);
        }

        if (option==3) {
            printf("\nThank you for using our email software\nQuitting process ...\n");
            exit(0);
        }

    }


// 1.1.1.1
// harsh
// 1234
// 2
// gmail.com
// omair
// hotmail.com
// SUBJECT SUCCESSFULL!


    
	/* After connection, the client can send or receive messages.
	   However, please note that recv() will block when the
	   server is not sending and vice versa. Similarly send() will
	   block when the server is not receiving and vice versa. For
	   non-blocking modes, refer to the online man pages.
	*/
	for(i=0; i < 100; i++) buf[i] = '\0';
	recv(sockfd, buf, 100, 0);
	printf("%s\n", buf);

	for(i=0; i < 100; i++) buf[i] = '\0';
	recv(sockfd, buf, 100, 0);
	printf("%s\n", buf);	
	
	strcpy(buf,"Message from client");
	send(sockfd, buf, strlen(buf) + 1, 0);
		
	close(sockfd);
	return 0;

}

