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

char* get_statue_line (enum http_status);

