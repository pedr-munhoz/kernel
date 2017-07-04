/*
    Projeto Sistemas Operacionais II
    Simulacao de um Sistema Operacional multiprogramado no DOS
    (processador 8086)

    Operational Systems II project
    Simulating an multi-programmed Operational System to run
    on the 8086 processor DOS

    Frederico Gomes
    Luccas Quadros
    Pedro Munhoz
*/

/* Including the libraries */
#include <stdio.h>
#include <conio.h>
#include <system.h>

/* primary functions headers */
void far system_init(); /* initiates the system */
void far scheduler(); /* process scheduler */
void far DOS_return(); /* gives the control back to DOS */
void far end_process(); /* finishes the process */
int far round_robin(); /* round robin scheduler algorithm */
int far priority(); /* simple priority scheduler */
int far process_creator(void far (*end_proc)(), char p_name[], int p_priority); /* initiates a process */
int far next_process(); /* finds the next active process in the queue */




/* Structures */

/* Base registers */
typedef struct base_registers {
  unsigned bx1, esl;
}
registers;

/* Critic region register handler */
typedef union critic_region_register_handler {
  registers r; /* base registers to be handled */
  char far *y; /* process status */
}
critic_handler;

/* Process descriptor */
typedef struct process_descriptor{
  char name[255]; /* process name */
  int status; /* process status (active, blocked, done) */
  int priority; 
  PTR_DESC pointer; /* process pointer */
}bla;

typedef bla *process_descriptor_pointer;



/* System constants and global variables */

/* Max number of running process */
#define MAX 10

char
  /* Error table */
  ERROR_01 = MAX+1, /* too many process */
  ERROR_02 = MAX+12, /* called process does not exist */
  ERROR_03 = MAX+13, /* not enough memory */
  ERROR_04 = MAX+5, /* generic error */

  /* System status */
  ACTIVE = 0,
  DONE = 1,
  BLOCKED = 2;

int
  index = 0, /* index of the current running process */
  queue_size = 0; /* size of the process queue */

process_descriptor_pointer process_queue[MAX]; /* Process queue, 10 maximo */

/*bla **process_queue;
process_queue = malloc(MAX * sizeof(bla*));   /* array of 3 pointers */

PTR_DESC my_scheduler; /* Pointer to the scheduler process */

critic_handler handler; /* Handler containing the required registers to deal with critic zone situations */



/* Functions */

/* initiates the system */
void far system_init() {
  PTR_DESC auxiliar_descriptor;

  my_scheduler = cria_desc(); /* Create the scheduler descriptor */
  auxiliar_descriptor = cria_desc(); /* Create the auxiliar descriptor */

  newprocess(scheduler, my_scheduler); /* Creates the scheduler process */
  transfer(auxiliar_descriptor, my_scheduler); /* Gives the control to the scheduler */
}

/* process scheduler */
void far scheduler() {
  p_est->p_origem = my_scheduler; /* Setting the scheduler as the origin process, */
                               /* any interruptions will return the control to it */
  p_est->p_destino = process_queue[0]->pointer;
  p_est->num_vetor = 8;

  while(1) {
    disable();
    _AL = 0;
    _AH = 0x34;

    geninterrupt(0x21);

    handler.r.bx1 = _BX;
    handler.r.esl = _ES;

    if(handler.y != 0) {
      iotransfer();
      index = next_process();
      if(index>=MAX)
        DOS_return();
      p_est->p_destino = process_queue[index]->pointer;
    }
  enable();
  }
}

/* gives the control back to DOS */
void far DOS_return() {
  disable(); /* Creates a critical region */
  setvect(8, p_est->int_anterior); /* recovers the previous interruption */
  enable(); /* Exits the critical region */
  exit(0);
}

/* finishes the process */
void far end_process() {
  disable(); /* Creates a critical region */
  process_queue[queue_size]->status = DONE; /* Flags the process as finished */
  enable(); /* Exits the critical region */
  while (1); /* Waits for the finished process CPU time to end */
}

/* round robin scheduler algorithm */
int far priority() {
  int previous, p = 1, nhe;
  previous = index;
  /*printf("opa\n");*/

  do {
    index++;                /* Goes through all the processes in the queue */
    if(queue_size < index)  /* If the index passes the last process */
      index = 0;            /* The index returns to the first */

    /*printf("%d\t%d\n", index, p);*/
    /*for(nhe=0; nhe<1000; nhe++);*/
    /*scanf("%d",&nhe);*/

    if(process_queue[index]->priority==p) { /* if the index returs to the process where it started */
      if(process_queue[index]->status == ACTIVE) {
        (process_queue[index]->priority)++;
        if(process_queue[index]->priority == 4)
          process_queue[index]->priority = 3;
        return index;     /* The function retuns that process' index, if active */
      }
    }
    else if(index==previous) {
      p++;
      if(p==4) {
        DOS_return();
      }
    }
  }while (1); /* forever */
}

/* initiates a process returns 0 if succeeds */
int far process_creator(void far (*end_proc)(), char p_name[], int p_priority) {
  if (queue_size < MAX) /* Checks if there's room in the process queue */
  {
    if ((process_queue[queue_size] = (process_descriptor_pointer)malloc(sizeof(struct process_descriptor)))==NULL)
    {
      return ERROR_03;
    }
    process_queue[queue_size]->pointer = cria_desc();
    process_queue[queue_size]->status = ACTIVE;
    process_queue[queue_size]->priority = p_priority;
    strcpy (process_queue[queue_size]->name, p_name);
    newprocess(end_proc, process_queue[queue_size]->pointer);
    queue_size ++;
  }
  else
  {
    return ERROR_01;
  }
  return 0;
}

int far round_robin() {
  int previous = index;
  do {
    index++;                /* Goes through all the processes in the queue */
    if(queue_size < index)  /* If the index passes the last process */
      index = 0;            /* The index returns to the first */

    if(index==previous) { /* if the index returs to the process where it started */
      if(process_queue[index]->status == ACTIVE)
        return index;     /* The function retuns that process' index, if active */
      else
        return ERROR_04;        /* Or returns a number x, in a way that x > MAX */
    }
  }while (process_queue[index]->status != ACTIVE); /* when a active process is found */
                                                   /* the loop is broken */

  return index; /*  and that process' index is returned */
}

/* finds the next active process in the queue */
int far next_process() {
  int aux = ERROR_04;
  /* aux = round_robin(); */
  aux = priority();
  return aux;
}
