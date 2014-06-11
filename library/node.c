#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "request_parser.h"
#include "header_gen.h"
#include "node.h"
#include "file.h"

#define BUFF_SIZE 128

void node (int* p_fd)
{
  http_method_t method;
  int fd = *p_fd;
  int rfd;  
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
      rfd = open (get_file_path (((http_method_get_data_t*) method.data)->path),O_RDONLY); 
      if (rfd == -1) 
        {
          switch (errno) 
            {
            case EACCES: 
              {
                const char * status_line = get_statue_line (NOT_FOUND);      
                write (fd,status_line,24);
                char * date_line = get_date_line ();
                write (fd,date_line,32);
                const char * server_inf_line = get_server_inf_line ();
                write (fd,server_inf_line,36);
                write (fd,"\r\n\0",3);
                free (date_line);
                
                return;                
              }
            default: 
              {
                const char * status_line = get_statue_line (NOT_IMPLEMENTED);      
                write (fd,status_line,30);
                char * date_line = get_date_line ();
                write (fd,date_line,32);
                const char * server_inf_line = get_server_inf_line ();
                write (fd,server_inf_line,36);
                write (fd,"\r\n\0",3);
                free (date_line);
                
                return;                
              }
            }
        }
      const char * status_line = get_statue_line (OK);      
      write (fd,status_line,18);
      char * date_line = get_date_line ();
      write (fd,date_line,32);
      const char * server_inf_line = get_server_inf_line ();
      write (fd,server_inf_line,36);
      write (fd,"\r\n\0",3);
      free (date_line);      
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
  
  if (method.type == GET && rfd != -1)
    {
      fprintf (stderr,"STUBBBBBB!B!B!B!B!B!");
      abort ();      
    } 
  

}
