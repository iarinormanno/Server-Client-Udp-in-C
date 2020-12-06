#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

const int SERVER_PORT = 70; /*the default serverport number*/
int visits = 0; /*In numero di client connessi*/

int main(int argc, char* argv[]) {

    // Dichiarazioni
    struct sockaddr_in serverAddr; /*server address*/
    struct sockaddr_in clientAddr; /*client address*/

    int serverSock; /*server socket e client sock*/
    char buf[100], buf1;; /*buffer per i messaggi di invio e ricezione*/
    int len = sizeof(struct sockaddr), n;
    char ip[15]; /*client address*/
    int serverPort, clientPort; /*client e server address*/

 // Inizializzazioni
    WSADATA wsaData;
    WSAStartup(0x0202, &wsaData); /*windows socket startup */

    memset((char*)&serverAddr, 0, sizeof(serverAddr)); /*Tutti 0 nel serverAddr*/
    serverAddr.sin_family = AF_INET; /*set server address protocol family*/
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverPort = SERVER_PORT;
    serverAddr.sin_port = htons((u_short)serverPort);/*set port*/

 // Creazione Socket
    serverSock = socket(PF_INET, SOCK_DGRAM, 0);/*create a socket*/
    if (serverSock < 0) {
        fprintf(stderr, "socket creating failed\n");
        exit(1);
    }

    // Leghiamo il client a indirizzo e porta
    if (bind(serverSock, (LPSOCKADDR)&serverAddr, len) < 0) {/*bind a server address and port*/
        fprintf(stderr, "bind failed\n");
        exit(1);
    }

    // Set Non Blocking Mode, specified via last parameter
    // 0 Disabled
    // !0 Enabled
    unsigned long int nonBlockingMode = 0;
    int result = ioctlsocket(serverSock, FIONBIO, &nonBlockingMode);

    if (result)
    {
        fprintf(stderr, "ioctlsocket failed\n");
        exit(1);
    }

    while (1) {
        //  Ricevo il messaggio dal client
        memset(buf, 0, sizeof(buf));
        recvfrom(serverSock, buf, sizeof(buf), 0, (LPSOCKADDR)&clientAddr, &len);
        recvfrom(serverSock, &buf1, 1, 0, (LPSOCKADDR)&clientAddr, &len);


        switch (buf1) {
        case 'a':


            for (int i = 0; buf[i] != 0; i++)
            {
                if (buf[i] >= 'a' && buf[i] <= 'z')
                    buf[i] = buf[i] - 32;
            }


            break;
        case 'b':
            for (int i = 0; buf[i] != '\0'; i++) {
                if (buf[i] >= 'A' && buf[i] <= 'Z')
                    buf[i] = buf[i] + 32;
            }
            break;
        case 'c':

            for (int i = 0; buf[i] != '\0'; i++) {
                if (buf[i] >= 'a' && buf[i] <= 'z') {
                    buf[i] = buf[i] - 32;
                    break;
                }
            }
            break;
        }

        //rimanda messaggio al client
        sendto(serverSock, buf, strlen(buf), 0, (LPSOCKADDR)&clientAddr, len);
    }

    system("Pause");
    return 1;
}
