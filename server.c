#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 50000
#define BUF_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];
    // Winsock initialisieren
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup fehlgeschlagen\n");
        return 1;
    }
    // Socket anlegen
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // UDP: SOCK_DGRAM; IPv4 weil AF_INET
    if (server_fd == INVALID_SOCKET) {
        printf("Socket konnte nicht erstellt werden\n");
        WSACleanup();
        return 1;
    }
    // Adresse konfigurieren
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    // Binden
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind fehlgeschlagen: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
     // Auf Verbindungen warten
    listen(server_fd, 5);
    printf("Server läuft auf Port %d ...\n", PORT);
    // Verbindung annehmen
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd == INVALID_SOCKET) {
        printf("Accept fehlgeschlagen\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Client verbunden.\n");
    // Echo-Schleife
    while (1) {
        int n = recv(client_fd, buffer, BUF_SIZE - 1, 0);
        if (n <= 0) {
            printf("Client getrennt.\n");
            break;
        }
        buffer[n] = '\0';
        printf("Empfangen: %s", buffer);

        send(client_fd, buffer, n, 0);
    }
    closesocket(client_fd);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}