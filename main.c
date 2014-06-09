#include <stdio.h>
#include <stdlib.h>
#include "whole_conf.h"

int
main (int argc, char *argv[])
{
  int port;

  //! @todo sigpipeをmaskして無視する. 

  if (argc < 3)
    {
      puts ("httpserver [port] [document root]");
      return 1;
    }
  port = atoi (argv[1]);
  doc_root = argv[2];

  //! @todo call httpd's main func

  return 0;
}
