#pragma once

typedef enum http_method_type
{
  GET
} http_method_type_t;

typedef struct http_method_data 
{

} http_method_data_t;

typedef struct http_method_get_data 
{
  char *path; 
} http_method_get_data_t;

typedef struct http_method
{
  http_method_type_t type;
  http_method_data_t *data;  
} http_method_t;

http_method_t parse_http_method (char *);
