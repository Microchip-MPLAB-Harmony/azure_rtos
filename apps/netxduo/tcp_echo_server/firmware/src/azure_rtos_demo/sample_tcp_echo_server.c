/* This is a small demo of the high-performance NetX Duo TCP/IP stack.
   This program demonstrates ICMPv6 protocols Neighbor Discovery and
   Stateless Address Configuration for IPv6, ARP for IPv4, and
   TCP packet sending and receiving with a simulated Ethernet driver.  */


#include   "tx_api.h"
#include   "nx_api.h"

#ifndef DEMO_ECHO_SERVER_PORT
#define DEMO_ECHO_SERVER_PORT 7
#endif /* DEMO_ECHO_SERVER_PORT */

/* Define the counters used in the demo application...  */
static ULONG error_counter;
NX_TCP_SOCKET server_socket;

/* Define demo prototypes.  */

void server_connect_received(NX_TCP_SOCKET *server_socket, UINT port);
void server_disconnect_received(NX_TCP_SOCKET *server_socket);


void sample_tcp_echo_server_entry(NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr)
{
UINT          status;
NX_PACKET    *packet_ptr;

    /* Create a socket.  */
    status =  nx_tcp_socket_create(ip_ptr, &server_socket, "Server Socket",
                                   NX_IP_NORMAL, NX_FRAGMENT_OKAY, NX_IP_TIME_TO_LIVE, 100,
                                   NX_NULL, server_disconnect_received);

    /* Check for error.  */
    if (status)
    {
        error_counter++;
    }

    /* Setup this thread to listen.  */
    status =  nx_tcp_server_socket_listen(ip_ptr, DEMO_ECHO_SERVER_PORT, &server_socket, 5, server_connect_received);

    /* Check for error.  */
    if (status)
    {
        error_counter++;
    }

    /* Loop to create and establish server connections.  */
    while (1)
    {

        /* Accept a client socket connection.  */
        status =  nx_tcp_server_socket_accept(&server_socket, NX_WAIT_FOREVER);

        /* Receive and echo.  */
        if (status == NX_SUCCESS)
        {
    
            /* Receive a TCP message from the socket.  */
            status =  nx_tcp_socket_receive(&server_socket, &packet_ptr, NX_WAIT_FOREVER);

            /* Check for error.  */
            if (status)
            {
                error_counter++;
            }
            else
            {
                
                printf("Received data!\r\n");

                /* Echo the received data.  */
                status = nx_tcp_socket_send(&server_socket, packet_ptr, NX_IP_PERIODIC_RATE);

                /* Determine if the status is valid.  */
                if (status)
                {
                    error_counter++;
                    nx_packet_release(packet_ptr);
                }
            }

            /* Disconnect the server socket.  */
            printf("Server will close the connection...\r\n");
            status =  nx_tcp_socket_disconnect(&server_socket, NX_IP_PERIODIC_RATE);

            /* Check for error.  */
            if (status)
            {
                error_counter++;
            }
        }

        /* Unaccept the server socket.  */
        status =  nx_tcp_server_socket_unaccept(&server_socket);

        /* Check for error.  */
        if (status)
        {
            error_counter++;
        }

        /* Setup server socket for listening again.  */
        status =  nx_tcp_server_socket_relisten(ip_ptr, DEMO_ECHO_SERVER_PORT, &server_socket);

        /* Check for error.  */
        if (status)
        {
            error_counter++;
        }
    }
}

void  server_connect_received(NX_TCP_SOCKET *socket_ptr, UINT port)
{

    /* Check for the proper socket and port.  */
    if ((socket_ptr != &server_socket) || (port != DEMO_ECHO_SERVER_PORT))
    {
        error_counter++;
    }
    else
    {
        printf("Server accepted connection...\r\n");
    }
}


void  server_disconnect_received(NX_TCP_SOCKET *socket)
{

    /* Check for proper disconnected socket.  */
    if (socket != &server_socket)
    {
        error_counter++;
    }
    else
    {
        printf("Server remotely disconnected...\r\n");
    }
}

