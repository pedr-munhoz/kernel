/* testing */
#include <stdio.h>
#include <oe.H>

void far ProcessoA(){
    long int i = 0;
     while(i < 100000) {
        printf("A ");
        i++;
     }
     end_process();
}

void far ProcessoB(){
    long int i = 0;
     while(i < 100000) {
        printf("B ");
        i++;
     }
     end_process();
}

void main(){
    process_creator(ProcessoA,"P1");
    process_creator(ProcessoB,"P2");
    system_init();
}
