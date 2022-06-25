#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
// including argp library to ease the pain of processing command line arguments
#include <argp.h>
#include <argz.h>

#define OK          0
#define INIT_ERR    1
#define REQ_ERR     2

#define URL         "http://172.16.72.151:8000" //default URL for host OS.
//#define URL         "http://www.cnn.com:8000"
#define TARGET      "example.txt" //default file to get
#define WORDS       "Hello World" //default message to post

const char *argp_program_version = "Version 1.0"; // Version (a good habit to start)

struct arguments // Struct to gather arguments from command line.
{
  char *argz;
  size_t argz_len;
};

int ret; // Integer to use for calling functions.
int perfHTTP(char *pointer); // declaration of perfHTTP()

char command[7]; //string for HTTP Command (e.g. GET, DELETE, etc...)


static int
parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *a = state->input;
  switch (key)
  {
    case 'u':
    {
      printf("This should replace the default URL with the URL entered.\n");
      // check to see if there is a URL in the arguments
      printf("Default URL = %s\n", URL);
      //ret = 1;
      // if so, change URL to the value in arguments
      // if no URL in args, use default URL
      //ret = basicHTTP();
      //printf("Return value = %d\n", ret);
      break;
    }
    case 'o':
    {
      printf("Post\n");
      strncpy(command, "POST", 4); // set the command to POST
      ret = perfHTTP(command); // Call perfHTTP with command = POST
      printf("Return from perfHTTP() = %d\n", ret);
      break;
    }
    case 'g':
    {
      printf("HTTP GET URL\n");
      strncpy(command, "GET", 3); // set the command to GET
      ret = perfHTTP(command); // Call perfHTTP with command = GET
      printf("Return from perfHTTP() = %d\n", ret);
      // call a routine that performs HTTP GET from the URL using CURL.
      // Pass the argument for --get to the function.
      break;
    }
    case 'p':
    {
      printf("Put\n");
      strncpy(command, "PUT", 3); // set the command to PUT
      ret = perfHTTP(command); // Call perfHTTP with command = GET
      printf("Return from perfHTTP() = %d\n", ret);
      // call a routine that performs HTTP PUT from the URL using CURL.
      // Pass the argument for --put to the function.
      break;
    }
    case 'd':
    {
      printf("Delete\n");
      strncpy(command, "DELETE", 6); // set the command to DELETE
      ret = perfHTTP(command); // Call perfHTTP with command = DELETE
      printf("Return from perfHTTP() = %d\n", ret);
      break;
    }
  }
  return 0;
}


/*
perfHTTP() takes a pointer to a command string and performs an
HTTP Request according to the command.
*/
int perfHTTP(char *pointer){
  CURL      *curl;
  CURLcode  res;
  int index = 0;
  char* array;
  char argument[5];

  curl = curl_easy_init();
  if (curl){
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, pointer);
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    res = curl_easy_perform(curl);
    if (res != CURLM_OK){
      return REQ_ERR;
    }
    curl_easy_cleanup(curl);
  } else {
    return INIT_ERR;
  }
  return OK;
}

int main(int argc, char *argv[]){

  /*
  Handle command line arguments, this seems like a good place for a switch statement
  that would handle the following -u, -o, -g, -p, -d, and -h.
  */
  // Setup arguments and parameters using argp
  // order of fields {NAME, KEY, ARG, FLAGS, DOC, GROUP}
  struct argp_option options[] =
  {
    {"url", 'u', "URL", OPTION_ARG_OPTIONAL, "Set URL. If not set default will be used."},
    {"post", 'o', "MSG", OPTION_ARG_OPTIONAL, "Perform HTTP POST to URL"},
    {"get", 'g', "FILE", OPTION_ARG_OPTIONAL, "Perform HTTP GET from URL"},
    {"put", 'p', "FILE", OPTION_ARG_OPTIONAL, "Perform HTTP PUT at URL"},
    {"delete", 'd', "FILE", OPTION_ARG_OPTIONAL, "Perform HTTP DELETE at URL"},
    {0}
  };
  struct argp argp = {options, parse_opt};
  return argp_parse (&argp, argc, argv, 0, 0, 0);
  return OK;
}
