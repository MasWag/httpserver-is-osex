#pragma once

char *get_file_path (const char *);
int read_and_write (int ifd, int ofd);
int send_msg(const int fd,const char *msg);
