#define _POSIX_C_SOURCE 200809L
#define LINE_SIZE 200
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

size_t fsize(const char* file);
log_t** load_lines(FILE* input,size_t disp_mem,size_t* total_read);
int line_cmp (void* a,void*b);
bool merge_file(size_t partitions,FILE* output);
void write_out(FILE* output,log_t* data);
adhoc_t* load_log(FILE** files,size_t i);
void save_lines(FILE* part_file,log_t* logs[],size_t tope);

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
int cmp_adhoc(void* a,void*b){
  int resultado;
  resultado = strcmp(((log_t*)a)->fecha , ((log_t*)b)->fecha);
  if (resultado == 0){
    resultado = strcmp(((log_t*)a)->ip , ((log_t*)b)->ip);
    if(resultado == 0){
      resultado = strcmp(((log_t*)a)->metodo , ((log_t*)b)->metodo);
    }
  }
  if(resultado == 1) resultado = -1;
  else if(resultado == -1 ) resultado = 1;
  return resultado;
}


bool ordenar_archivo(const char* input_file,const char* out_file,const size_t max_memory){

  if(input_file == NULL || out_file == NULL) return false;
  FILE* input = fopen(input_file,"rt");
  if(!input) return false;
  FILE* output = fopen(out_file,"wt");
  if(!output){fclose(input);return false;}

  size_t num_lines = (max_memory*1000)/LINE_SIZE;
  size_t partitions = 0;
  for(partitions; !feof(input) ;partitions++){
    char file_name[30];
    sprintf(file_name,"sort.part%i",partitions);
    FILE* part_file = fopen(file_name,"w");//creo el archivo
    size_t total_read = 0;
    log_t** logs = load_lines(input,num_lines,&total_read);//Cargo num_lines del input
    heap_sort(logs,total_read,line_cmp);//ordeno
    save_lines(part_file,logs,total_read);//guardo
    fclose(part_file);
  }
  bool result = merge_file(partitions,output);
  fclose(input);
  fclose(output);
  return result;
}


log_t** load_lines(FILE* input,size_t lines_read,size_t* total_read){
  log_t** logs = malloc(sizeof(log_t*) * lines_read);
  if(!logs) return NULL;
  char* buffer = NULL;
  size_t cant = 0;
  size_t pos = 0;
  for((*total_read);getline(&buffer,&cant,input)>0 && (*total_read) <= lines_read;(*total_read)++,pos++){
    char** line = split(buffer,'\t');
    logs[pos] = malloc(sizeof(log_t));
    logs[pos]->ip = strdup(line[0]);
    logs[pos]->fecha = strdup(line[1]);
    logs[pos]->metodo = strdup(line[2]);
    logs[pos]->url = strdup(line[3]);
    free_strv(line);
    free(buffer);
    buffer = NULL;
    cant = 0;
  }
  return logs;
}

void save_lines(FILE* part_file,log_t* logs[],size_t tope){
  for(size_t i = 0 ; i < tope ; i++){
    fwrite(logs[i],sizeof(log_t),1,part_file);
    free(logs[i]->ip);
    free(logs[i]->fecha);
    free(logs[i]->metodo);
    free(logs[i]->url);
  }
 free(logs);
}

bool merge_file(size_t partitions,FILE* output){
  FILE* *files[partitions];
  heap_t* heap = heap_crear(cmp_adhoc);
  if(!heap) return false;
  for(int i=0;i<partitions;i++){// ABRIR ARCHIVOS y CARGAR HEAP
    char file_name[30];
    sprintf(file_name,"sort.part%i",i);
    files[i] = fopen(file_name,"r");
    if(!files[i]) return false;;
    adhoc_t* encolar = load_log(files,i);
    heap_encolar(heap,encolar);
  }
  while(!heap_esta_vacio(heap)){
      adhoc_t* actual = heap_desencolar(heap);
      size_t prox_read = actual->file_num;
      write_out(output,actual->data);
      free(actual);
      actual = load_log(files,prox_read);
      if(actual)
        heap_encolar(heap,actual);
  }
  return true;
}

void write_out(FILE* output,log_t* data){
  fprintf(output,"%s\t",data->ip);
  free(data->ip);
  fprintf(output,"%s\t",data->fecha);
  free(data->fecha);
  fprintf(output,"%s\t",data->metodo);
  free(data->metodo);
  fprintf(output,"%s\n",data->url);
  free(data->url);
  printf("OK\n" );
  free(data);
}

adhoc_t* load_log(FILE** files,size_t i){
  adhoc_t* line = NULL;
  while (!feof(files[i])){
    line = malloc(sizeof(adhoc_t));
    log_t* data = malloc(sizeof(log_t));
    fread(data,sizeof(log_t),1,files[i]);
    line->file_num = i;
    line->data = data;
  }
  return line;
}


bool agregar_archivo(const char* file){
  return true;
}

bool ver_visitantes(const char* file){
  return true;
}
