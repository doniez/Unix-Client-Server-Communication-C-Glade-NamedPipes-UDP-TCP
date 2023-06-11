#!/bin/bash

#set -x 

error1() {
	echo "Missing Client files!" >/dev/stderr
	exit 1
}

error2() {
	echo "Missing Server files!" >/dev/stderr
	exit 1
}
error3() {
	echo "Missing Client TCP files!" >/dev/stderr
	exit 1
}
error4() {
	echo "Missing Server TCP files!" >/dev/stderr
	exit 1
}
error5() {
	echo "Missing Interface files!" >/dev/stderr
	exit 1
}

error6() {
	echo "Missing Client UDP files!" >/dev/stderr
	exit 1
}

error7() {
	echo "Missing Server UDP files!" >/dev/stderr
	exit 1
}

server_source="serveurunix.c"
server_header="Handlers_Serv.h"
server_third_party="serv_cli_fifo.h"
server_executable="serveur"

client_source="clientunix.c"
client_header="Handlers_Cli.h"
client_executable="client"

servertcp_source="ServeurTCP.c"
servertcp_header="serv_cli_socket.h"
servertcp_executable="serveurtcp"

clienttcp_source="ClientTCP.c"
clienttcp_header="serv_cli_socket.h"
clienttcp_executable="clienttcp"

serverudp_source="ServeurUDP.c"
serverudp_header="serv_cli_socket.h"
serverudp_executable="serveurudp"

clientudp_source="ClientUDP.c"
clientudp_header="serv_cli_socket.h"
clientudp_executable="clientudp"

interface_source="ClientServer.c"
interface_executable="ServerClient"

if [ ! -f "$server_source" ] || [ ! -f "$server_header" ] || [ ! -f "$server_third_party" ]; then
	error2
fi

if [ ! -f "$client_source" ] || [ ! -f "$client_header" ] ; then
        error1
fi
 
if [ ! -f "$servertcp_source" ] || [ ! -f "$servertcp_header" ] ; then
	error4
fi

if [ ! -f "$clienttcp_source" ] || [ ! -f "$clienttcp_header" ] ; then
        error3
fi
  if [ ! -f "$interface_source" ] ; then
        error5
fi

if [ ! -f "$serverudp_source" ] || [ ! -f "$serverudp_header" ] ; then
	error7
fi

if [ ! -f "$clientudp_source" ] || [ ! -f "$clientudp_header" ] ; then
        error6
fi
  
Build_server(){
	gcc $server_source -o $server_executable
}

Build_client(){
	gcc $client_source -o $client_executable
}
Build_server_tcp(){
	gcc $servertcp_source -o $servertcp_executable
}

Build_client_tcp(){
	gcc $clienttcp_source -o $clienttcp_executable
}
Build_server_udp(){
	gcc $serverudp_source -o $serverudp_executable
}

Build_client_udp(){
	gcc $clientudp_source -o $clientudp_executable
}
Build_interface(){
gcc -o $interface_executable $interface_source -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
}

Build_server
Build_client
Build_server_tcp
Build_client_tcp
Build_server_udp
Build_client_udp
Build_interface
clear 

echo "Running interface!"
gnome-terminal -- /bin/sh -c './ServerClient; bash'

echo "Script has been succefully executed!"

exit 0

