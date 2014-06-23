#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include "library/whole_conf.h"
#include "library/socket.h"
#include "library/node.h"

typedef void *(*pthfunc) (void *);

int
main (int argc, char *argv[])
{
  int port;
  int s;
  int fd;
  pthread_attr_t attr;

  //! @todo sigpipeをmaskして無視する. 

  if (argc < 3)
    {
      puts ("httpserver [port] [document root]");
      return 1;
    }
  port = atoi (argv[1]);
  doc_root = argv[2];

  //! @todo call httpd's main func
  socket_init (&s, port);
  pthread_attr_init (&attr);

  while (1)
    {
      pthread_t pth;
      fd = accept (s, NULL, NULL);
      if (fd == -1)
	{
	  perror ("accept");
	  continue;
	}

      pthread_create (&pth, &attr, (pthfunc) node, &fd);
      pthread_detach (pth);
    }

  return 0;
}
