#include "simlib.h"
#include "simlibdefs.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){

  init_simlib();
  transfer[0] = 1;transfer[1]=2;
  list_file(FIRST,1);
  transfer[0]=0;transfer[1]=0;
  list_remove(FIRST,1);
  printf("transfer array value: %d,%d\n",(int)transfer[0],(int)transfer[1]);
  sampst(2,1);
  sampst(1,1);
  sampst(4,1);
  sampst(0,-1);
  printf("sampst out\n");
  int i;
  for(i = 1; i < 5;i++){

    printf("index %d: %2.2f\n",i,transfer[i]);
  }

}