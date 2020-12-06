
#define _WINSOCK_DEPCRECATED 
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) // disabilita warnings su visual studio 


const char SERVER_IP[15] = "127.0.0.1";
const int SERVER_PORT = 70;

int main(int argc, char* argv[]) {

    // Dichiarazioni
    struct sockaddr_in serverAddr;  /*server address*/

    int clientSock; /*client sock*/
    char buf[100], buf1[100]; /*buffer the message send and receive*/
    int len = sizeof(struct sockaddr), n;

    // Inizializzazioni
    WSADATA wsaData;
    WSAStartup(0x0202, &wsaData); /*windows socket startup */

    serverAddr.sin_family = AF_INET; /*Valore speciale - IP su cui gira il server*/
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);/*trasforma l'IP server in int*/ //InetPton(AF_INET, _T(SERVER_IP),&serverAddr.sin_addr.s_addr);
    serverAddr.sin_port = htons((u_short)SERVER_PORT);/*prende la porta da riga di comando*/


 // Creazione Socket
    clientSock = socket(PF_INET, SOCK_DGRAM, 0);/*Viene creato il socket; PF_INET = IPv4; SOCK_DGRAM = UDP */
    if (clientSock < 0) {
        fprintf(stderr, "socket creating failed\n");
        exit(1);
    }

    while (1) {
        // Inviamo un messaggio al server
        memset(buf, 0, sizeof(buf)); //Puliamo il buffer

        printf("\nScrivi una frase: ");
        gets(buf);
        sendto(clientSock, buf, strlen(buf), 0, (LPSOCKADDR)&serverAddr, len);




        printf("\nScegli: ");
        printf("\na)Maiuscolo ");
        printf("\nb)Minuscolo ");
        printf("\nc)Primo carattere maiuscolo");
        printf("\n");
        gets(buf1);




        //   Invio Del messaggio al server


        sendto(clientSock, &buf1, 1, 0, (LPSOCKADDR)&serverAddr, len);


        //riceve messaggio
        memset(buf, 0, sizeof(buf));
        recvfrom(clientSock, buf, sizeof(buf), 0, (LPSOCKADDR)&serverAddr, &len);
        printf("\n--->Dal server: ");
        printf("%s\n\n", buf);

    }

    // Chiusura del socket
    closesocket(clientSock);
    WSACleanup();

    system("pause");
    return 1;
}
