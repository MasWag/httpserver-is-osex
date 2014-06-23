#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request_parser.h"


http_method_t
parse_http_method (char *str)
{
  char *type;
  http_method_t ret;
  char * save_ptr;
  save_ptr = malloc (sizeof (char) * strlen (str));
  type = strtok_r (str, " ",&save_ptr);
  // GET
  if (!strcmp (type, "GET"))
    {
      ret.type = GET;
      ret.data = malloc (sizeof (http_method_get_data_t));
      ((http_method_get_data_t *) ret.data)->path = strtok_r (NULL, " ",&save_ptr);
      ((http_method_get_data_t *) ret.data)->var = strtok_r (NULL, " ",&save_ptr);
    }
  // HEAD
  else if (!strcmp (type, "HEAD"))
    {
      ret.type = HEAD;
      ret.data = malloc (sizeof (http_method_head_data_t));
      ((http_method_head_data_t *) ret.data)->path = strtok_r (NULL, " ",&save_ptr);
      ((http_method_head_data_t *) ret.data)->var = strtok_r (NULL, " ",&save_ptr);
    }
  return ret;
}
