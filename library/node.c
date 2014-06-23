#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "request_parser.h"
#include "header_gen.h"
#include "node.h"
#include "file.h"

#define BUFF_SIZE 128

void
node (int *p_fd)
{
  http_method_t method;
  int fd = *p_fd;
  int rfd;
  char *str;
  int str_size = BUFF_SIZE;
  str = malloc (str_size);

  // request
  while (1)
    {
      str[0] = '\0';
      while (1)
	{
	  char buff[BUFF_SIZE];
	  int size = read (fd, buff, BUFF_SIZE);
	  strcat (str, buff);
	  if (size == -1)
	    {
	      perror ("read");
	      free (str);
	      pthread_exit (EXIT_SUCCESS);
	    }
	  else if (strstr (str, "\r\n\r\n") || strstr (str, "\n\n"))
	    {
	      break;
	    }
	  else if (size == 0)
	    {
	      free (str);
	      pthread_exit (EXIT_SUCCESS);
	    }
	  else
	    {
	      str_size += BUFF_SIZE;
	      str = realloc (str, str_size);
	    }
	}
      method = parse_http_method (str);

      // いずれもheaderを送るまでは共通
      if (method.type == GET || method.type == HEAD)
	{
	  char *fpath =
	    get_file_path (((http_method_get_data_t *) method.data)->path);
	  rfd = open (fpath, O_RDONLY);
          free (fpath);
	  if (rfd == -1)
	    {
	      switch (errno)
		{
		case ENOENT:
		case EACCES:
		  {
		    perror ("open");
		    const char *status_line = get_statue_line (NOT_FOUND);
		    send_msg (fd, status_line);
		    char *date_line = get_date_line ();
		    send_msg (fd, date_line);
		    free (date_line);
		    const char *server_inf_line = get_server_inf_line ();
		    send_msg (fd, server_inf_line);
		    send_msg (fd, "\r\n");
                    int ifd = open ("htmls/404.html",O_RDONLY);
                    read_and_write (ifd,fd);
                    close (ifd);
		    continue;
		  }
		default:
		  {
		    perror ("open");
		    const char *status_line =
		      get_statue_line (NOT_IMPLEMENTED);
		    send_msg (fd, status_line);
		    char *date_line = get_date_line ();
		    send_msg (fd, date_line);
		    free (date_line);
		    const char *server_inf_line = get_server_inf_line ();
		    send_msg (fd, server_inf_line);
		    send_msg (fd, "\r\n");

		    continue;
		  }
		}
	    }
	  const char *status_line = get_statue_line (OK);
	  send_msg (fd, status_line);
	  char *date_line = get_date_line ();
	  send_msg (fd, date_line);
	  const char *server_inf_line = get_server_inf_line ();
	  send_msg (fd, server_inf_line);
	  send_msg (fd, "\r\n");
	  free (date_line);
	}
      // GETとHEAD以外は今のところない
      else
	{
	  printf ("HERE\n");
	  const char *status_line = get_statue_line (NOT_IMPLEMENTED);
	  send_msg (fd, status_line);
	  char *date_line = get_date_line ();
	  send_msg (fd, date_line);
	  const char *server_inf_line = get_server_inf_line ();
	  send_msg (fd, server_inf_line);
	  send_msg (fd, "\r\n");

	  free (date_line);
	}

      if (method.type == GET && rfd != -1)
	{
          read_and_write (rfd,fd);
	}
      close (rfd);
      close (fd);
      pthread_exit (EXIT_SUCCESS);
    }
}
