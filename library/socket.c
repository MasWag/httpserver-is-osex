#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void
socket_init (int *const s, const int port_num)
{
  struct sockaddr_in addr;

  if ((*s = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
      perror ("socket");
      exit (-1);
    }
  // conf
  addr.sin_family = AF_INET;
  addr.sin_port = htons (port_num);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind (*s, (struct sockaddr *) &addr, sizeof (struct sockaddr_in)) == -1)
    {
      perror ("bind");
      exit (-1);
    }
  if (listen (*s, SOMAXCONN) == -1)
    {
      perror ("listen");
      exit (-1);
    }
}
