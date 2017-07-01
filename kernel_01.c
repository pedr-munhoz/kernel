//****************************************************************
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
//****************************************************************

// Including our library
#include "kernel_01.h"



// Structures

// Base registers
typedef struct base_registers {
  unsigned bx1, esl;
}
registers;

// Critic region register handler
typedef union critic_region_register_handler {
  registers r; // base registers to be handled
  char far *y; // process status
}
critic_handler;

// Process descriptor
typedef struct process_descriptor{
  char name[255]; // process name
  int status; // process status (active, blocked, done)
  descriptor_pointer pointer; // process pointer
}
*process_descriptor_pointer;



// System constants and global variables

// Max number of running process
#define MAX 10

char
  // Error table
  error_01 = MAX+1, // too many process
  error_02 = MAX+12, // called process does not exist
  error_03 = MAX+13, // not enough memory
  error_04 = MAX+13, // generic error

  // System status
  active = 0,
  done = 1,
  blocked = 2;

int
  index = 0, // index of the current running process
  queue_size = 0, // size of the process queue
  scheduler = 0; // which scheduling algorithm to use
                 // 0 = round robin

process_descriptor_pointer process_queue[MAX]; // Process queue, 10 maximo

descriptor_pointer my_scheduler; // Pointer to the scheduler process

critic_handler handler; // Handler containing the required registers to deal with critic zone situations



// Functions

// initiates the system
void far system_init() {
  descriptor_pointer auxiliar_descriptor;

  my_scheduler = create_desc(); // Create the scheduler descriptor
  auxiliar_descriptor = create_desc(); // Create the auxiliar descriptor

  newprocess(scheduler, my_scheduler); // Creates the scheduler process
  transfer(auxiliar_descriptor, my_scheduler); // Gives the control to the scheduler
}

// process scheduler
void far scheduler()

// gives the control back to DOS
void far DOS_return()

// finishes the process
void far end_process() {
  disable(); // Creates a critical region 
  process_queue[queue_size]->status = done; // Flags the process as finished
  enable; // Exits the critical region
  while (1); // Waits for the finished process CPU time to end
}

// clear the process array
void far clear_queue()

// round robin scheduler algorithm
int far round_robin()

// initiates a process returns 0 if succeeds
int far process_creator(void far (*end_proc)(), char p_name[]) {
  if (queue_size < MAX) // Checks if there's room in the process queue
  {
    if (process_queue[queue_size] = (process_descriptor_pointer)malloc(sizeof(struct process_descriptor)))
    {
      return error_03;
    }
    process_queue[queue_size]->pointer = create_desc();
    process_queue[queue_size]->status = active;
    strcpy (process_queue[queue_size]->name, p_nome);
    newprocess(end_proc, process_queue[queue_size]->pointer);
    queue_size ++;
  }
  else
  {
    return error_01;
  }
  return 0;
}

// finds the next active process in the queue
int far next_process()
