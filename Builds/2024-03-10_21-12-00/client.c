#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int sockfd;

void send_command(const char *command) {
    sendto(sockfd, command, strlen(command), MSG_CONFIRM, NULL, 0);
}

void pause_audio(GtkWidget *widget, gpointer data) {
    send_command("pause");
}

void play_audio(GtkWidget *widget, gpointer data) {
    send_command("play");
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *pause_button;
    GtkWidget *play_button;
    GtkWidget *hbox;

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

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Audio Control Client");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    pause_button = gtk_button_new_with_label("Pause");
    g_signal_connect(pause_button, "clicked", G_CALLBACK(pause_audio), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), pause_button, TRUE, TRUE, 0);

    play_button = gtk_button_new_with_label("Play");
    g_signal_connect(play_button, "clicked", G_CALLBACK(play_audio), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), play_button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    gtk_main();

    close(sockfd);
    return 0;
}
