#include <stdlib.h>
#include <string.h>
#include "request_parser.h"


http_method_t parse_http_method (char * str)
{
  char *type;
  http_method_t ret;
  
  type = strtok (str," ");
  // GET
  if (!strcmp (type,"GET"))
    {
      ret.type = GET;
      ret.data = malloc (sizeof (http_method_get_data_t));
      ((http_method_get_data_t*) ret.data)->path = strtok (NULL," ");
    }
  return ret;
}

  
