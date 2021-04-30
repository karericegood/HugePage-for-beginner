#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef ON
#define PAGESIZE 2*1024*1024
#define flag 0
#else
#define PAGESIZE 4*1024
#define flag 1
#endif

int main(){
    char* memory[1024] ; 
    int Loop = 100;
    // flag = 1 => basic mmap / flag = 0 => hugetlb mmap  
    if (flag == 0){
        for (int i = 0 ; i < Loop ; i++){
            memory[i] = mmap(0,1, PROT_READ | PROT_WRITE, MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS, -1, PAGESIZE*i); 
            if (memory[i] == MAP_FAILED){
                perror("mmap");
            }
            *(memory[i]) = (char) i ;  
        }
    }
    else{
        for (int i = 0 ; i < Loop ; i++){
            memory[i] = mmap(0,1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, PAGESIZE*i);
            if (memory[i] == MAP_FAILED){
                perror("mmap");
            }
            *(memory[i]) = (char) i ;        
        }
    }
    pause() ;    
    
}