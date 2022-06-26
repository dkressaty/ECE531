#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <argp.h> // including argp library to ease the pain of processing command line arguments

#define OK          0
#define INIT_ERR    1
#define REQ_ERR     2

#define URL         "http://172.16.72.151:8000" //default URL for host OS.
#define TARGET      "example.txt" //default file to get
#define MSG         "Hello World" //default message to post

const char *argp_program_version = "Version 1.0"; // Version (a good habit to start)


int ret; // Integer to use for calling functions.
int perfHTTP_POST(char *pointer);
int perfHTTP_GET();
int perfHTTP_PUT(char *pointer);
int perfHTTP_DELETE(char *pointer);

char usrURL[50];

static int
parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments *a = state->input;
  switch (key)
  {
    case 'u': // command line input to change URL target from Default, Text is required as input
    {
      printf("Set URL target.\n");
      printf("\tDefault URL = %s\n", URL);
      printf("\tUser Argument = %s\n", arg);
      // set the value of usrURL to arg
      // this will be used to construct the follow on CURL actions.
      strcpy(usrURL, arg);
      printf("\tUser Entered URL = %s\n", usrURL);
      // perform some input validation (e.g. look for "http://", look for ":" after the first 7 chars... etc)
      // return an error if these conditions aren't met. "Improperly formatted URL"
      // else move on.
      break;
    }
    case 'o': // command line option for HTTP POST Request: Text is required as input.
    {
      ret = perfHTTP_POST(arg); // call POST routine, passing it the argument from the command line
      printf("Return from Post = %d\n", ret);
      break;
    }
    case 'g': // command line option for HTTP GET Request, no argument allowed
    {
      ret = perfHTTP_GET(); // call GET routine, no argument necessary
      printf ("Return from perfHTTP_GET = %d\n", ret);
      break;
    }
    case 'p': // command line option for HTTP PUT Request: Text is required as input.
    {
      printf("Put\n");
      printf("\tUser Argument = %s\n", arg);
      ret = perfHTTP_PUT(arg); // call PUT routine, passing it the argument from the command line
      break;
    }
    case 'd': // command line option for HTTP DELETE Request: Text is required as input.
    {
      printf("Delete\n");
      printf("\tUser Argument = %s\n", arg);
      ret = perfHTTP_DELETE(arg);
      printf("Return value from DELETE: %d\n", ret);
      break;
    }
  }
  return 0;
}


/*
perfHTTP_POST() takes a pointer to a message string and performs an
HTTP POST command to the target website using the meassage as the contents of the post..
*/
int perfHTTP_POST(char *pointer){
  CURL      *curl;
  CURLcode  res;
  int index = 0;
  char* array;
  char argument[5];

  curl = curl_easy_init();
  if (curl){
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pointer);
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

/*
perfHTTP_GET() simple HTTP GET on target URL.
*/
int perfHTTP_GET(){
  CURL      *curl;
  CURLcode  res;
  int index = 0;
  char* array;
  char argument[5];

  curl = curl_easy_init();
  if (curl){
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
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

/*
perfHTTP_PUT() takes a pointer to a message string and performs an
HTTP PUT command to the target website using the meassage as the contents of the post..
*/
int perfHTTP_PUT(char *pointer){
  CURL      *curl;
  CURLcode  res;
  int index = 0;
  char* array;
  char argument[5];

  curl = curl_easy_init();
  if (curl){
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_PUT, pointer);
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

/*
perfHTTP_DELETE() takes a pointer to a message string and executes an
HTTP DELETE Request to the target website using the meassage as the contents of the delete action..
*/
int perfHTTP_DELETE(char *pointer){
  CURL      *curl;
  CURLcode  res;
  int index = 0;
  char* array;
  char argument[5];

  curl = curl_easy_init();
  if (curl){
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pointer);
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
  Handle command line arguments like a decent GNU utility.
  accept the following inputs -u/--url, -o/--post, -g/--get, -p/--put
  -d/--delete.
  if an option is selected it has a mandatory input as described in the help.
  */
  // Setup arguments and parameters using argp
  // order of fields {NAME, KEY, ARG, FLAGS, DOC, GROUP}
  strcpy(usrURL, URL); // set the default value of the URL used to the default URL.
                        // NOTE: There MUST be a better way to do this rathar than use a global variable.
  struct argp_option options[] =
  {
    {"url", 'u', "URL", 0, "Set URL. If not set default will be used."},
    {"post", 'o', "MSG", 0, "Post this Message at the URL"},
    {"get", 'g', 0, 0, "Perform HTTP GET operation on URL"},
    {"put", 'p', "MSG", 0, "Put this stuff at the URL"},
    {"delete", 'd', "FILE", 0, "Perform HTTP DELETE at URL"},
    {0}
  };
  struct argp argp = {options, parse_opt};
  return argp_parse (&argp, argc, argv, 0, 0, 0);
  return OK;
}
