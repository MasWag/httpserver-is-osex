#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "request_parser.h"
#include "header_gen.h"
#include "node.h"

#define BUFF_SIZE 128

void node (int* p_fd)
{
  http_method_t method;
  int fd = *p_fd;
  char * str;
  int str_size = BUFF_SIZE;
  str = malloc (str_size);
  
  // request
  while (1)
    {      
      int size = read (fd,str,BUFF_SIZE);
      if (size == -1 )
        {
          perror ("read");
          return;
        }
      else if (size == 0)
        {
          break;
        }
      else
        {
          str_size += BUFF_SIZE;          
          str = realloc (str,str_size);
        }
    }
  method = parse_http_method (str);
  
  // いずれもheaderを送るまでは共通
  if (method.type == GET || method.type == HEAD)
    {
      fprintf (stderr,"THIS IS STUB!! DO NOT CALL!!\n");      
      abort ();      
    } 
  // GETとHEAD以外は今のところない
  else
    {
      const char * status_line = get_statue_line (NOT_IMPLEMENTED);      
      write (fd,status_line,30);
      char * date_line = get_date_line ();
      write (fd,date_line,32);
      const char * server_inf_line = get_server_inf_line ();
      write (fd,server_inf_line,36);
      write (fd,"\r\n\0",3);
      
      free (date_line);      
    }
  
 

}
