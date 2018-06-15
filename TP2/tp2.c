#define _POSIX_C_SOURCE 200809L
#define LINE_SIZE 200
#define PARTS_PATH "/parts"
#include "tp2.h"


typedef struct log{
  char* ip;
  char* fecha;
  char* metodo;
  char* url;
}log_t;

typedef struct adhoc{
  size_t file_num;
  log_t* data;
}adhoc_t;
/************************* FUNCIONES DE COMPARACION***************************/
int line_cmp (void* a,void*b){
  int resultado;
  resultado = strcmp(((log_t*)a)->fecha , ((log_t*)b)->fecha);
  if (resultado == 0){
    resultado = strcmp(((log_t*)a)->ip , ((log_t*)b)->ip);
    if(resultado == 0){
      resultado = strcmp(((log_t*)a)->metodo , ((log_t*)b)->metodo);
    }
  }
  return resultado;
}
/*****************************************************************************/
/************************* Primitivas internas *******************************/
bool divide_and_sort(FILE* input,size_t max_lines,size_t* parts);
log_t** read_lines(FILE* input,size_t max_lines,size_t* read_lines);
bool save_lines(log_t* lines,size_t part_num,size_t top);
FILE* create_part_file(size_t part);
void free_lines(log_t**lines,size_t top);
/*****************************************************************************/
bool ordenar_archivo(const char* input_file,const char* out_file,const size_t max_memory){
  if(!input_file || !output_file) return false;
  FILE* input = fopen(input_file,"rt");
  FILE* output = fopen(output_file,"wt");
  size_t lines_in_parts = (max_memory*1000)/LINE_SIZE;
  bool error = false;
  size_t num_parts = 0;
  error = divide_and_sort(input,lines_in_parts,num_parts);
  error = merge_files(output,num_parts);
  remove(PARTS_PATH);
  fclose(input);
  fclose(output);
  return !error;
}

bool divide_and_sort(FILE* input,size_t max_lines,size_t* parts){
  while(!feof(input)){
    size_t read_lines = 0;
    log_t** lines = read_lines(input,max_lines,&read_lines);
    if(!lines) return false;
    heap_sort(lines,line_cmp);
    bool save = save_lines(lines,parts,read_lines);
    if(!save) return false;
    free_lines(lines,read_lines);
    *(parts)++;
  }
  return true;
}
log_t** read_lines(FILE* input,size_t max_lines,size_t* read_lines){
  log_t** lines = malloc(sizeof(log_t*) * max_lines);
  char* buffer = NULL;
  size_t cant = 0;
  size_t i=0;
  for(i; i < max_lines && !feof(input);i++){
    if(getline(&buffer,&cant,input)>0){
      char** line = split(buffer,'\t');
      logs[i] = malloc(sizeof(log_t));
      logs[i]->ip = strdup(line[0]);
      logs[i]->fecha = strdup(line[1]);
      logs[i]->metodo = strdup(line[2]);
      logs[i]->url = strdup(line[3]);
      free_strv(line);
      free(buffer);
      buffer = NULL;
      cant = 0;
    }
    else i--;
  }
  *(read_lines) = i;
  return lines;
}
bool save_lines(log_t* lines,size_t part_num,size_t top){
  FILE* part_file = create_part_file(part_num);
  if(!part_file) return false;
  for(size_t i=0;i<top;i++){
    fwrite(lines[i],sizeof(log_t),1,part_file);
  }
  fclose(part_file);
  return true;
}
FILE* create_part_file(size_t part){
  char file_name[30];
  sprintf(file_name,"%s/%i.part",PARTS_PATH,part);
  FILE* file = fopen(file_name,"w");
  return file;
}
void free_lines(log_t**lines,size_t top){
  for(size_t i = 0; i<top;i++){
    free(lines[i]->ip);
    free(lines[i]->fecha);
    free(lines[i]->metodo);
    free(lines[i]->url);
    free(lines[i]);
  }
    free(lines);
}
