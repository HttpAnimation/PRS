#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

GtkWidget *entry;
int sockfd;

void send_command(GtkWidget *widget, gpointer data) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    sendto(sockfd, text, strlen(text), MSG_CONFIRM, NULL, 0);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *vbox;

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

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), "Enter 'pause' or 'play'");
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("Send Command");
    g_signal_connect(button, "clicked", G_CALLBACK(send_command), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    gtk_main();

    close(sockfd);
    return 0;
}
