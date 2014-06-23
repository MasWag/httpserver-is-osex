#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "header_gen.h"

const char *
get_statue_line (http_status_t status)
{
  switch (status)
    {
    case OK:
      return "HTTP/1.1 200 OK\r\n";
    case NOT_FOUND:
      return "HTTP/1.1 404 Not Found\r\n";
    case NOT_IMPLEMENTED:
      return "HTTP/1.1 501 Not Implemented\r\n";
    }
  return "ERROR";
}

char *
get_date_line (void)
{
  char *str;
  time_t tm;
  const char *ti;

  tm = time (NULL);
  str = malloc (sizeof (char) * 33);
  strcpy (str, "Date: ");
  ti = ctime (&tm);
  strcat (str, ti);
  str[30] = '\r';
  str[31] = '\n';
  str[32] = '\0';

  return str;
}
