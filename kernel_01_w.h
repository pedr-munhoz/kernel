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

/* Checks if the "KERNEL_01" token have been defined, if not, */
/* runs the following */
#ifndef KERNEL_01
  #define KERNEL_01
  /* c basic libraries */
  #include <stdio.h>
  #include <conio.h>
  #include "system.h"

  /* primary functions headers */
  void far system_init(); /* initiates the system */
  void far scheduler(); /* process scheduler */
  void far DOS_return(); /* gives the control back to DOS */
  void far end_process(); /* finishes the process */
  int far round_robin(); /* round robin scheduler algorithm */
  int far process_creator(void far (*end_proc)(), char p_name[]); /* initiates a process */
  int far next_process(); /* finds the next active process in the queue */


#endif
