#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 50000
#define BUF_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // init Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSASTartup fehlgeschlagen\n");
        return 1;
    }
    // Socket anlegen
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket konnte nicht erstellt werden\n");
        WSACleanup();
        return 1;
    }
    // Serveradresse konfigurieren
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Verbindung herstellen
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Verbindung zum Server fehlgeschlagen\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    // Nachrichten
    printf("Mit dem Server verbunden. Tippe Nachrichten:\n");
    while (1) {
        printf("> ");
        if (!fgets(buffer, BUF_SIZE, stdin)) break;
        send(sock, buffer, strlen(buffer), 0);
        int n = recv(sock, buffer, BUF_SIZE - 1, 0);
        if (n<=0) {
            printf("Verbindung beendet.\n");
            break;
        }
        buffer[n] = '\0';
        printf("Echo vom Server: %s", buffer);
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}