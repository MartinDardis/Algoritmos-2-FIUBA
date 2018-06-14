#define _POSIX_C_SOURCE 200809L
#define LINE_SIZE 200

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

typedef struct log{
  char* ip;
  char* fecha;
  char* metodo;
  char* url;
}log_t;

size_t fsize(const char* file);
log_t** load_lines(FILE* input,size_t disp_mem,size_t* total_read);
int line_cmp (void* a,void*b);
bool merge_file(size_t partitions);


bool ordenar_archivo(const char* input_file,const char* out_file,const size_t max_memory){
  if(input_file == NULL || out_file == NULL) return false;
      size_t size_file = fsize(input_file);
  FILE* input = fopen(input_file,"rt");
  if(!input) return false;
  FILE* output = fopen(out_file,"wt");
  if(!output){fclose(input);return false;}
      size_t num_lines = (disp_mem*1000)/LINE_SIZE;
      size_t partitions = size_file/num_lines;
  for(int i = 0; 0 < partitions ;i++){
    char file_name[30];
    sprintf(file_name,"sort.part%i",partitions);
    FILE* part_file = fopen(file_name,"w");
    log_t** logs = load_lines(input,num_lines,&total_read);
    heap_sort(logs,total_read,strcmp);
    save_lines(part_file,logs,total_read);
    fclose(part_file);
  }
  return merge_file(partitions);
}

size_t fsize(const char* dir){
  size_t size = 0;
  FILE* file = fopen(dir,"rt");
  while(!feof(file)){
    fseek(file,1,SEEK_CUR);
    size++;
  }
  fclose(file);
  return size;
}

log_t** load_lines(FILE* input,size_t lines_read,size_t* total_read){
  log_t** logs = malloc(sizeof(log_t) * lines_read);
  char* buffer;
  size_t cant;
  size_t pos = 0;
  while( !feof(input) || lines_read > 0){
    lines_read--;
    char** line = split(buffer);
    strdup(logs[pos]->ip,line[0]);
    strdup(logs[pos]->fecha,line[1]);
    strdup(logs[pos]->metodo,line[2]);
    strdup(logs[pos]->url,line[3]);
    free_strv(line);
    free(buffer);
    buffer = NULL;
    cant = 0;
    pos++;
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
