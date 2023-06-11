#include <gtk/gtk.h>
#include<stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include<ctype.h>
GtkWidget *window;
GtkLabel *mylabel;
int main (int argc, char *argv[])
{
const char *cmd ="gnome-terminal -- bash -c \" gcc serveurunix.c -o serveur ; gcc ServeurTCP.c -o serveurtcp ;gcc clientunix.c -o client ;gcc ClientTCP.c -o clienttcp ;gcc ClientUDP.c -o clientudp ;gcc ServeurUDP.c -o serveurudp ; exec bash\" ";
system(cmd);
GtkBuilder *builder;
gtk_init(&argc, &argv);
builder=gtk_builder_new();
gtk_builder_add_from_file(builder,"interface.glade",NULL);

window= GTK_WIDGET(gtk_builder_get_object(builder,"MyWindow"));

gtk_builder_connect_signals(builder,NULL);
g_object_unref(builder);

gtk_widget_show_all(window);
gtk_main();

return 0;
}
void exit_app(){
gtk_main_quit();
}
void button_named(){

GtkBuilder *builder;

builder=gtk_builder_new();
gtk_builder_add_from_file(builder,"interface.glade",NULL);

window= GTK_WIDGET(gtk_builder_get_object(builder,"MyWindowNamed"));

gtk_builder_connect_signals(builder,NULL);
g_object_unref(builder);

gtk_widget_show_all(window);
}
void button_tcp(){

GtkBuilder *builder;

builder=gtk_builder_new();
gtk_builder_add_from_file(builder,"interface.glade",NULL);

window= GTK_WIDGET(gtk_builder_get_object(builder,"MyWindowTCP"));

gtk_builder_connect_signals(builder,NULL);
g_object_unref(builder);

gtk_widget_show_all(window);
}
void button_udp(){

GtkBuilder *builder;

builder=gtk_builder_new();
gtk_builder_add_from_file(builder,"interface.glade",NULL);

window= GTK_WIDGET(gtk_builder_get_object(builder,"MyWindowUDP"));

gtk_builder_connect_signals(builder,NULL);
g_object_unref(builder);

gtk_widget_show_all(window);
}
void button_server_named(){

const char *cmd ="gnome-terminal -- bash -c \"./serveur ; exec bash\" ";
system(cmd);

}
void button_client_named(){
GtkBuilder *builder;

builder=gtk_builder_new();
gtk_builder_add_from_file(builder,"interface.glade",NULL);
mylabel=GTK_LABEL(gtk_builder_get_object(builder,"LabelNamedClient"));
window= GTK_WIDGET(gtk_builder_get_object(builder,"MyWindowNamedClient"));
gtk_builder_connect_signals(builder,NULL);
g_object_unref(builder);
gtk_widget_show_all(window);
const char *cmd ="gnome-terminal -- bash -c \"./client | tee clientnamedpipe.txt ; exit ; exec bash\" ";
system(cmd);

   FILE *fp;
   int i=0;
   char ch;
   char *buff=calloc(1000,sizeof(char));
  sleep(3);
   fp=fopen("/home/doni/Desktop/unixFIFO/clientnamedpipe.txt","r");

   while ((ch=fgetc(fp)) != EOF){
   	buff[i++]=ch;      
   }
    fclose(fp);
 buff[i]='\0';
 

gtk_label_set_text(mylabel,buff);

}
button_server_tcp(){

const char *cmd ="gnome-terminal -- bash -c \" ./serveurtcp ; exec bash\" ";
system(cmd);
}

void button_client_tcp(){
GtkBuilder *builder;

builder=gtk_builder_new();
gtk_builder_add_from_file(builder,"interface.glade",NULL);
mylabel=GTK_LABEL(gtk_builder_get_object(builder,"LabelClientTcp"));
window= GTK_WIDGET(gtk_builder_get_object(builder,"MyWindowClientTcp"));
gtk_builder_connect_signals(builder,NULL);
g_object_unref(builder);
gtk_widget_show_all(window);
const char *cmd ="gnome-terminal -- bash -c \"./clienttcp | tee clienttcp.txt ; exit ; exec bash\" ";
system(cmd);

   FILE *fp;
   int i=0;
   char ch;
   char *buff=calloc(1000,sizeof(char));
  sleep(3);
   fp=fopen("/home/doni/Desktop/unixFIFO/clienttcp.txt","r");

   while ((ch=fgetc(fp)) != EOF){
   	buff[i++]=ch;      
   }
    fclose(fp);
 buff[i]='\0';
 

gtk_label_set_text(mylabel,buff);

}


button_server_udp(){

const char *cmd ="gnome-terminal -- bash -c \" ./serveurudp ; exec bash\" ";
system(cmd);
}



void button_client_udp(){
GtkBuilder *builder;

builder=gtk_builder_new();
gtk_builder_add_from_file(builder,"interface.glade",NULL);
mylabel=GTK_LABEL(gtk_builder_get_object(builder,"LabelClientUdp"));
window= GTK_WIDGET(gtk_builder_get_object(builder,"MyWindowClientUdp"));
gtk_builder_connect_signals(builder,NULL);
g_object_unref(builder);
gtk_widget_show_all(window);
const char *cmd ="gnome-terminal -- bash -c \"./clientudp | tee clientudp.txt ; exit ; exec bash\" ";
system(cmd);

   FILE *fp;
   int i=0;
   char ch;
   char *buff=calloc(1000,sizeof(char));
  sleep(3);
   fp=fopen("/home/doni/Desktop/unixFIFO/clientudp.txt","r");

   while ((ch=fgetc(fp)) != EOF){
   	buff[i++]=ch;      
   }
    fclose(fp);
 buff[i]='\0';
 

gtk_label_set_text(mylabel,buff);

}

