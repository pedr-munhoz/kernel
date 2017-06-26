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
typedef struct base_registers
{
  unsigned bx1, esl;
}registers;

// Critic region register handler
typedef union critic_region_register_handler
{
  registers r;
  char far *y;
}critic_handler;

// Process descriptor
typedef struct process_descriptor{
  char name[255]; // process name
  int status; // process status (active or waiting)
  descriptor_pointer pointer; // process pointer
}*process_descriptor_pointer;
