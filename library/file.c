#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "whole_conf.h"

#define BUFF_SIZE 256

char *
get_file_path (const char *path)
{
  char *str = malloc (sizeof (char) *(strlen (path) + strlen (doc_root) + 1));
  strcpy (str, doc_root);
  strcat (str, path);
  return str;
}

int
read_and_write (int ifd, int ofd)
{
  char buff[BUFF_SIZE];
  int size;
  int wsize;

  while (1)
    {
      size = read (ifd, buff, BUFF_SIZE);
      switch (size)
	{
	case -1:
	  perror ("read");
	  return -1;
	case 0:          
          return 0;
	default:
	  wsize = 0;
	  while (wsize < size)
	    wsize += write (ofd, buff, size - wsize);
	}
    }
  return 0;
}

int send_msg(const int fd,const char *msg) {

  int len;
  int wsize = 0;
  len = strlen(msg);

  while ( wsize < len ){
    wsize += write(fd, msg, len);
  }

  return len;

}
