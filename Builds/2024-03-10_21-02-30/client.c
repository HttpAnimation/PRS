#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <curses.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Initialize curses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (1) {
        clear();
        printw("Press 'p' to pause, 'r' to resume, 'q' to quit: ");
        refresh();

        int ch = getch();
        if (ch == 'q') {
            break;
        } else if (ch == 'p') {
            strcpy(buffer, "pause");
            sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        } else if (ch == 'r') {
            strcpy(buffer, "play");
            sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        }
    }

    // End curses mode
    endwin();
    close(sockfd);
    return 0;
}
