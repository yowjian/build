#include <stdio.h>
#include <string.h>
#include "multipart_parser.h"
#include "multipart_helper.h"

int read_header_name(multipart_parser* p, const char *at, size_t length)
{
   /* Check if Content-Disposition and set flag */
   printf("NAME %.*s: ", length, at);
   return 0;
}

int read_header_value(multipart_parser* p, const char *at, size_t length)
{
   /* check starts with form-data, get name */
   printf("VALUE %.*s\n", length, at);
   return 0;
}

int read_part_data(multipart_parser* p, const char *at, size_t length)
{
   /* associate data with field */
   printf("DATA %.*s", length, at);
   return 0;
}

char *guess_boundary(const char *foo) {
  char * boundary = strchr(foo,'\r');
  if (!boundary) return NULL;
  int len = boundary - foo;
  boundary = (char *) malloc(len + 1);
  strncpy(boundary,foo,len);
  boundary[len]='\0';
  return boundary;
}

int multipart_helper(const char *foo) {
  multipart_parser_settings callbacks;
  memset(&callbacks, 0, sizeof(multipart_parser_settings));
  callbacks.on_header_field = read_header_name;
  callbacks.on_header_value = read_header_value;
  callbacks.on_part_data = read_part_data;
  char * boundary = guess_boundary(foo);
  if(!boundary) return -1;
  multipart_parser* parser = multipart_parser_init(boundary, &callbacks);
  multipart_parser_execute(parser, foo, strlen(foo));
  multipart_parser_free(parser);
  free(boundary);
  /* collect all name-value pairs and return */
  return 0;
}

