#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "request_parser.h"
#include "header_gen.h"

int tests_run = 0;

static char *
request_parser_get_test (void)
{
  http_method_t val;
  char str[512];
  strcpy (str,
	  "GET /index.php HTTP/1.1\r\nHost: www.is.s.u-tokyo.ac.jp\r\nUser-Agent: Mozilla/5.0 (X11; U; Linux x86_64; ja;rv:1.9.2.3) Gecko/20100423 Ubuntu/10.04 (lucid) Firefox/3.6.3\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: ja,en-us;q=0.7,en;q=0.3\r\nAccept-Encoding: gzip,deflate\r\nAccept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.7\r\nKeep-Alive: 115\r\nConnection: keep-alive\r\n\r\n");


  val = parse_http_method (str);
  if ((val.type == GET)
      && !strcmp (((http_method_get_data_t *) val.data)->path, "/index.php"))
    return NULL;
  else
    return "request_parser_get_test not passed!!\n";

}

static char *
request_parser_head_test (void)
{
  http_method_t val;
  char str[512];
  strcpy (str,
	  "HEAD /index.php HTTP/1.1\r\nHost: www.is.s.u-tokyo.ac.jp\r\nUser-Agent: Mozilla/5.0 (X11; U; Linux x86_64; ja;rv:1.9.2.3) Gecko/20100423 Ubuntu/10.04 (lucid) Firefox/3.6.3\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: ja,en-us;q=0.7,en;q=0.3\r\nAccept-Encoding: gzip,deflate\r\nAccept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.7\r\nKeep-Alive: 115\r\nConnection: keep-alive\r\n\r\n");


  val = parse_http_method (str);
  if ((val.type == HEAD)
      && !strcmp (((http_method_get_data_t *) val.data)->path, "/index.php"))
    return NULL;
  else
    return "request_parser_head_test not passed!!\n";

}

static char *
get_date_line_test (void)
{
  char *str;
  char in;
  str = get_date_line ();

  while (1)
    {
      printf ("is This ok? [Y/N]\n%s", str);

      in = 'Y';			//getchar ();
      switch (in)
	{
	case 'y':
	case 'Y':
	  return NULL;
	case 'n':
	case 'N':
	  return "get_date_line_test not passed!!\n";
	default:
	  break;
	}
    }
  return NULL;
}


static char *
all_tests ()
{
  mu_run_test (request_parser_get_test);
  mu_run_test (request_parser_head_test);
  mu_run_test (get_date_line_test);
  return 0;
}

int
main (int argc, char **argv)
{
  char *result = all_tests ();
  if (result != 0)
    {
      printf ("%s\n", result);
    }
  else
    {
      printf ("ALL TESTS PASSED\n");
    }
  printf ("Tests run: %d\n", tests_run);

  return result != 0;
}
