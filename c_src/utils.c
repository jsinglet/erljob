// analysis.c - Erlang FFI for matching audio segments against frequency ranges 
// 
// John L. Singleton <jsinglet@gmail.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "erl_nif.h"
#include "is_match_multi_points.h"

#define SAMPLE_RATE 44100
#define MAX_KEY_BUFFER_SZ 20
#define NUM_SECONDS     (1)
#define NUM_CHANNELS 1
#define AUDIO_BUFFER_SZ (SAMPLE_RATE*NUM_SECONDS)
#define FILE_NAME_LEN 1024
#define UNLOCK_DOOR 1

typedef FILE* teensy_t;


int read_audio(const char* file, double* buffer)
{

  FILE *f;
  
  f = fopen(file, "rb");
  
  signed short int rec_buffer[AUDIO_BUFFER_SZ];
 
  if(f){
    fread(rec_buffer, sizeof(signed short int), AUDIO_BUFFER_SZ, f);
  }else{
    return -1;
  }

  int i=0;

  //convert the integer buffer to a buffer of doubles.
  for(i=0; i< AUDIO_BUFFER_SZ; i++){
    buffer[i] = rec_buffer[i]/(double)32768;
  }
 
  fclose(f);
  return 1;
}


static ERL_NIF_TERM is_match(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{

  printf("[C] Match Init\n");

  // Erlang type magic
  int key_size;
  const ERL_NIF_TERM* ent_args;
  char file[FILE_NAME_LEN];
  int i = 0;


  // holds sample data
  double sample_master[AUDIO_BUFFER_SZ];
  // holds keys
  double keys_master[MAX_KEY_BUFFER_SZ];
  // activation threshold  
  double threshold;

  
  // clean our memory
  memset(sample_master, 0, AUDIO_BUFFER_SZ);
  memset(keys_master, -1, MAX_KEY_BUFFER_SZ);
  memset(file, 0, FILE_NAME_LEN);
  
  //get the file
  if (!enif_get_string(env, argv[0], file, FILE_NAME_LEN, ERL_NIF_LATIN1)) {
    return enif_make_badarg(env);
  }

  if (!enif_get_tuple(env, argv[1], &key_size, &ent_args)) {
    return enif_make_badarg(env);
  }

  for(i = 0; i < key_size && i < MAX_KEY_BUFFER_SZ; i++){
    int a;
    enif_get_int(env, ent_args[i], &a);

    keys_master[i] = (double)a;
  }

  // get the threshold
  enif_get_double(env, argv[2], &threshold);


  read_audio(file, sample_master);

  // Debug prints
  printf("[C] Sample: %s\n", file);

  printf("[C] Keys: [");

  int k=0;
  for(k=0; k < MAX_KEY_BUFFER_SZ; k++){
    printf("%lf, ", keys_master[k]);
  }
  printf("]\n");

  return enif_make_int(env, is_match_multi_points(sample_master, SAMPLE_RATE, keys_master, threshold));
}


int write_teensy(const char* device, const char* what)
{

  /** get a handle to teensy **/
  teensy_t handle = fopen(device, "w+b");

  if(!handle){
    perror("Can't open handle to USB Device");
    return -1;
  }

  fprintf(handle, what);
  fflush(handle);  
  fclose(handle);
 
  return 0;
}

static ERL_NIF_TERM blink(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]){

  char device[1024];
  char color[2];
  char buff[3];
  int  times;


  if (!enif_get_string(env, argv[0], device, 1024, ERL_NIF_LATIN1)) {
    return enif_make_badarg(env);
  }
  
  if (!enif_get_string(env, argv[1], color, 2, ERL_NIF_LATIN1)) {
    return enif_make_badarg(env);
  }
  
  if (!enif_get_int(env, argv[2], &times)){
    return enif_make_badarg(env);
  }
  
  sprintf(buff, "%s%d", color, times);
  
 

  return enif_make_int(env,  write_teensy(device, buff));

}

static ERL_NIF_TERM unlock(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  char buff[2];
  char device[1024];

  if (!enif_get_string(env, argv[0], device, 1024, ERL_NIF_LATIN1)) {
    return enif_make_badarg(env);
  }
  
  sprintf(buff, "%d", UNLOCK_DOOR);
  

  return enif_make_int(env,  write_teensy(device, buff));
}




static ErlNifFunc nif_funcs[] =
{
  {"is_match", 3, is_match},
  {"blink", 3, blink},
  {"unlock", 1, unlock},


};

ERL_NIF_INIT(utils,nif_funcs,NULL,NULL,NULL,NULL)
