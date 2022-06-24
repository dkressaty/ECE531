#include <stdio.h>
#include <curl/curl.h>
// including argp library to ease the pain of processing command line arguments
#include <argp.h>

#define OK          0
#define INIT_ERR    1
#define REQ_ERR     2

#define URL         "http://172.16.72.151:8000"

static int
parse_opt(int key, char *arg, struct argp_state *state)
{
  switch (key)
  {
    case 'u':
      printf("Enter URL\n");
      break;
    case 'o':
      printf("Post\n");
      break;
    case 'g':
      printf("Get\n");
      break;
    case 'p':
      printf("Put\n");
      break;
    case 'd':
      printf("Delete\n");
      break;
  }
  return 0;
}


int main(int argc, char *argv[]){
  CURL      *curl;
  CURLcode  res;
  int index = 0;
  char* array;
  char argument[5];
/* Commented out while working on input parsing. Un-comment when done.
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    res = curl_easy_perform(curl);
    if (res != CURLM_OK) {
      return REQ_ERR;
    }
    curl_easy_cleanup(curl);
  } else {
    return INIT_ERR;
  }
 Commented out while working on input parsing. Un-comment when done.
*/
  /*
  Handle command line arguments, this seems like a good place for a switch statement
  that would handle the following -u, -o, -g, -p, -d, and -h.
  */
  // Setup arguments and parameters
  struct argp_option options[] =
  {
    {0, 'u', 0, 0, "Set URL"},
    {0, 'o', 0, 0, "Perform HTTP POST"},
    {0, 'g', 0, 0, "Get Something"},
    {0, 'p', 0, 0, "Put Something"},
    {0, 'd', 0, 0, "Delete Something"},
    {0}
  };
  struct argp argp = {options, parse_opt};
  return argp_parse (&argp, argc, argv, 0, 0, 0);
/* Commenting this out so I can work up using argp__parse
  if (argc > 1){
    printf("argc = %d\n", argc);
    int i = argc;
    for (index = 0; index < i; index++){
      printf("Argv is %s\n", argv[index]);
      array = strdup(argv[index]);
      printf("array = %s\n", array);

    }
  } else printf("Too few comand line arguments\nTry %s --help for more information\n", argv[0]);
*/
  return OK;
}
