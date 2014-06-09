#include "status.h"

char * get_statue_line (http_status_t status)
{
  switch (status)
    {
    case OK : 
      return "HTTP/1.1 200 OK\r\n";
    case NOT_FOUND : 
      return "HTTP/1.1 404 Not Found\r\n";
    case NOT_IMPLEMENTED :
      return "HTTP/1.1 501 Not Implemented\r\n";
    }
  return "ERROR";  
}


