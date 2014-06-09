#pragma once

typedef enum http_status
{
  // Success
  OK,

  // Client Error
  NOT_FOUND,

  // Server Error
  NOT_IMPLEMENTED
} http_status_t;

const char * get_statue_line (enum http_status);
#define get_server_inf_line() "Server: MasWag's Http Server/0.0.0\r\n"
char *get_date_line (void);
