/* testing */
#include <stdio.h>
#include <oe.H>

void far ProcessoA(){
    long int i = 0;
     while(i < 1000) {
        printf("A ");
        i++;
     }
     end_process();
}

void far ProcessoB(){
    long int i = 0;
     while(i < 1000) {
        printf("B ");
        i++;
     }
     end_process();
}

void far ProcessoC(){
    long int i = 0;
     while(i < 1000) {
        printf("C ");
        i++;
     }
     end_process();
}

void main(){
    process_creator(ProcessoA,"P1",3);
    process_creator(ProcessoB,"P2",2);
    process_creator(ProcessoC,"P3",1);
    system_init();
}
