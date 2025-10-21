#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 50000
#define BUF_SIZE 1024

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];
    // Winsock initialisieren
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup misslyckades\n");
        return 1;
    }
    // skapa socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // UDP: SOCK_DGRAM; IPv4 weil AF_INET
    if (server_fd == INVALID_SOCKET) {
        printf("Socket skapas inte\n");
        WSACleanup();
        return 1;
    }
    // konfigurera adress
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    // Bind
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind misslyckades: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
     // vänta på förbindelse
    listen(server_fd, 5);
    printf("Servern körs på port %d ...\n", PORT);
    // acceptera anslutning
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd == INVALID_SOCKET) {
        printf("Accept misslyckades\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Klient ansluten.\n");
    // Eko-Loop
    while (1) {
        int n = recv(client_fd, buffer, BUF_SIZE - 1, 0);
        if (n <= 0) {
            printf("Client okopplad.\n");
            break;
        }
        buffer[n] = '\0';
        printf("Mottagen: %s", buffer);

        send(client_fd, buffer, n, 0);
    }
    closesocket(client_fd);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}