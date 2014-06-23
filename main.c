#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
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
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, SIGPIPE );
  sigprocmask( SIG_BLOCK,&sigset, NULL );

  if (argc < 3)
    {
      puts ("httpserver [port] [document root]");
      return 1;
    }
  port = atoi (argv[1]);
  doc_root = argv[2];

  //! call httpd's main func
  socket_init (&s, port);

  while (1)
    {
      pthread_t pth;
      fd = accept (s, NULL, NULL);
      if (fd == -1)
	{
	  perror ("accept");
	  continue;
	}

      pthread_create (&pth, NULL,(void*) node, (void*) fd);
      pthread_detach (pth);
    }

  return 0;
}
