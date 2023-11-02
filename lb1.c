#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  FILE *myfile;
  int cnt_bytes, cnt_words,cnt_lines;
  int a,a1,i;
  cnt_bytes = 0,cnt_words = 0,cnt_lines = 0;
  a = 0, a1 = 0, i = 0;
  int tc = 0;
  int tw = 0;
  int tl = 0;
  
  
  
  
  myfile = fopen(argv[1],"r");  
  if(myfile != NULL){
    while(!feof(myfile)){
      a1 = a;
      a = fgetc(myfile);
      if(a != EOF){
        cnt_bytes++;
      }
      if((a1 >= 33) && (a < 33)){
        cnt_words++;  
      }
      if(a == '\n'){
        cnt_lines++;
      }
    }  
  fclose(myfile);
  
  if(argc == 2){
    printf("Количество байт: %d\n",cnt_bytes);
    printf("Количество слов: %d\n",cnt_words);  
    printf("Количество строк: %d\n",cnt_lines);    
  }
}
else if((argc >= 1)&&(myfile == NULL)){
  myfile = stdin;
  while(!feof(myfile)){
    a1 = a;
    a = fgetc(myfile);
    
    if(a != EOF){
      cnt_bytes++;
    }
    if((a1 >= 33) && (a < 33)){
      cnt_words++;  
    }
    if(a == '\n'){
      cnt_lines++;
    }
    i++;
  }
  if(argc == 1){
    printf("Количество байт: %d\n",cnt_bytes);
    printf("Количество слов: %d\n",cnt_words);  
    printf("Количество строк: %d\n",cnt_lines);    
  }
}

for(int i = 1; i < argc;i++){
  if((strcmp(argv[i],"-c") == 0) &&(tc == 0)){
    printf("Количество байт = %d\n",cnt_bytes);
    tc++;
  }
  if((strcmp(argv[i],"-w") == 0) &&(tw == 0)){
    printf("Количество слов = %d\n",cnt_words);
    tw++;
  }
  if((strcmp(argv[i],"-l") == 0) &&(tl == 0)){
    printf("Количество строк = %d\n",cnt_lines);
    tl++;
  }
}
return 0;
}
