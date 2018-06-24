#define _POSIX_C_SOURCE 200809L
#define LINE_SIZE 200
#include "tp2.h"
#include "heap.h"
#include "lista.h"
#include "abb.h"
#include "hash.h"


typedef struct log{
    char ip[20];
    char fecha[30];
    char metodo[5];
    char url[145];
}log_t;

typedef struct adhoc{
    size_t file_num;
    log_t data;
}adhoc_t;
/************************* FUNCIONES DE COMPARACION***************************/
int ipcmp (const char* s1,const char* s2){
    char** left = split(s1,'.');
    char** right = split(s2,'.');
    size_t i = 0;
    int resultado = 0;
    while(resultado == 0 && i < 4){
      resultado = (atoi(left[i])-atoi(right[i]));
      i++;
    }
    free_strv(left);
    free_strv(right);
    return resultado;
}
int line_cmp (const void* a,const void*b){
    int resultado;
    resultado = strcmp(((log_t*)a)->fecha , ((log_t*)b)->fecha);
    if (resultado == 0){
        resultado = ipcmp(((log_t*)a)->ip , ((log_t*)b)->ip);
        if(resultado == 0){
            resultado = strcmp(((log_t*)a)->metodo , ((log_t*)b)->metodo);
        }
          if(resultado == 0){
              resultado = strcmp(((log_t*)a)->url , ((log_t*)b)->url);
        }

    }
    return resultado;
}
int heap_cmp (const void* a,const void*b){
    adhoc_t* left = (adhoc_t*) a;
    adhoc_t* right = (adhoc_t*) b;
    int resultado = 0 - line_cmp(&(left->data),&(right->data));
    return resultado;
}
/*****************************************************************************/
/************************* Primitivas internas *******************************/
bool divide_and_sort(FILE* input,size_t max_lines,size_t* parts);
log_t** read_lines(FILE* input,size_t max_lines,size_t* read_lines);
bool save_lines(log_t** lines,size_t part_file_num,size_t top);
FILE* create_part_file(size_t part);
void free_lines(log_t**lines,size_t top);
bool merge_files(FILE* output,size_t num_parts);
heap_t* heapifile(FILE* files[],size_t num_parts);
bool open_part_files(FILE* files [],size_t num_parts);
bool load_heap(heap_t* out_heap,FILE* files[],size_t file_to_read);
bool write_out(heap_t* out_heap,FILE* output,FILE* files[],size_t num_parts);
/*****************************************************************************/
bool ordenar_archivo(const char* input_file,const char* output_file,const size_t max_memory){
    if(!input_file || !output_file) return false;
    FILE* input = fopen(input_file,"rt");
    FILE* output = fopen(output_file,"wt");
    size_t lines_in_parts = (max_memory*1000)/LINE_SIZE;
    bool error = false;
    size_t num_parts = 0;
    error = divide_and_sort(input,lines_in_parts,&num_parts);
    error = merge_files(output,num_parts);//tendrias que revisar si error es true antes de llamar esto y pisar el valor
    system("rm *.part");
    fclose(input);
    fclose(output);
    return !error;
}

bool divide_and_sort(FILE* input,size_t max_lines,size_t* parts){
    while(!feof(input)){
        size_t total_read_lines = 0;
        log_t** lines = read_lines(input,max_lines,&total_read_lines);
        if(!lines) return false;
        heap_sort((void**)lines,total_read_lines,line_cmp);
        bool save = save_lines(lines,*parts,total_read_lines);
        if(!save) return false;
        free_lines(lines,total_read_lines);
        (*parts)++;
    }
    return true;
}

log_t** read_lines(FILE* input,size_t max_lines,size_t* read_lines){
    log_t** logs = malloc(sizeof(log_t*) * max_lines);
    size_t i;
    for(i = 0; i < max_lines && !feof(input);i++){
        logs[i] = malloc(sizeof(log_t));
        fscanf(input,"%s\t%s\t%s\t%s\n",logs[i]->ip,logs[i]->fecha,logs[i]->metodo,logs[i]->url);
    }
    (*read_lines) = i;
    return logs;
}

bool save_lines(log_t** lines,size_t part_file_num,size_t top){
    FILE* part_file = create_part_file(part_file_num);
    if(!part_file) return false;
    for(size_t i=0;i<top;i++){
      fwrite(lines[i],sizeof(log_t),1,part_file);
    }
    fclose(part_file);
    return true;
}

FILE* create_part_file(size_t part){
    char file_name[30];
    sprintf(file_name,"%i.part",(int)part);
    FILE* file = fopen(file_name,"w");
    return file;
}

void free_lines(log_t**lines,size_t top){
    for(size_t i = 0; i<top;i++){
        free(lines[i]);
    }
    free(lines);
}

bool merge_files(FILE* output,size_t num_parts){
    FILE** files = malloc(sizeof(FILE*) * num_parts);
    if(!open_part_files(files,num_parts))return false;
    heap_t* out_heap = heapifile(files,num_parts);
    bool estate = write_out(out_heap,output,files,num_parts);
    heap_destruir(out_heap,NULL);
    for(size_t i = 0; i<num_parts; i++){
        fclose(files[i]);
    }
    free(files);
    return estate;
}

heap_t* heapifile(FILE* files[],size_t num_parts){
  adhoc_t** to_heap = malloc(sizeof(adhoc_t*) * num_parts);
  for(size_t i = 0; i < num_parts ;i++){
    to_heap[i] = malloc(sizeof(adhoc_t));
    to_heap[i]->file_num = i;
    fread(&(to_heap[i]->data),sizeof(log_t),1,files[i]);
  }
  heap_t* heap = heap_crear_arr((void*)to_heap,num_parts,heap_cmp);
  free(to_heap);
  return heap;
}

bool open_part_files(FILE* files [],size_t num_parts){
    for(size_t i=0 ; i<num_parts;i++){
        char file_name[30];
        sprintf(file_name,"%i.part",(int)i);
        files[i] = fopen(file_name,"r");
        if (!files[i]) return false;
    }
    return true;
}

bool load_heap(heap_t* out_heap,FILE* files[],size_t file_to_read){
    if(feof(files[file_to_read])) return true;
    adhoc_t* queue = malloc(sizeof(adhoc_t));
    if(!queue) return false;
    fread(&(queue->data),sizeof(log_t),1,files[file_to_read]);
    queue->file_num = file_to_read;
    if(!feof(files[file_to_read]))
      heap_encolar(out_heap,queue);
    else
      free(queue);
    return true;
}

bool write_out(heap_t* out_heap,FILE* output,FILE* files[],size_t num_parts){
    while (! heap_esta_vacio(out_heap)) {
        adhoc_t* to_save = heap_desencolar(out_heap);
        fprintf(output,"%s\t%s\t%s\t%s\n",(to_save->data).ip,(to_save->data).fecha,(to_save->data).metodo,(to_save->data).url);
        int to_load = to_save->file_num;
        free(to_save);
        if(!load_heap(out_heap,files,to_load)) return false;
    }
    return true;
}
