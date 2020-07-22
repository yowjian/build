#include <stdio.h>
#include <string.h>
#include "multipart_parser.h"
#include "multipart_helper.h"

int read_header_name(multipart_parser* p, const char *at, size_t length)
{
   /* printf("%.*s\n", length, at); */
   return 0;
}

int read_header_value(multipart_parser* p, const char *at, size_t length)
{
   char *tmp = NULL;
   char *v1  = NULL;
   char *v2  = NULL;
   char *v3  = NULL;
   int len;
   tmp = (char *) malloc(length + 1);
   if (tmp) {
     strncpy(tmp, at, length);
     tmp[length]='\0';
     if(strstr(tmp, "form-data")) {
       v1 = strstr(tmp, "name=\"");
       v1 += strlen("name=\"");
       if (v1) {
         v2 = strchr(v1, '"');
         if (v2) {
           len  = v2 - v1;
           v3 = (char *) malloc(len + 1);
           if (v3) {
             strncpy(v3, v1, len);
             v3[len] = '\0';
           }
         }
       }
     }
     free(tmp);
   }
   if (v3) printf("%s: ", v3);
   /* save v3 */
   return 0;
}

int read_part_data(multipart_parser* p, const char *at, size_t length)
{
   /* associate data with field */
   printf("%.*s\n", (int)length, at);
   fflush(stdout);
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

