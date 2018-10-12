/*

Derek Popowski
derek.a.popowski@und.edu
CSci 445 - Mathematical Simulation and Modeling

*/

#include "simlib.h"
#include <stdio.h>
#include <stdlib.h>

//define the simlib list numbers
#define EVENT_ARRIVAL 1
#define EVENT_ORDER 2
#define EVENT_END_SIM 3
#define EVENT_END_MONTH 4
#define STREAM_DEMAND 1
#define STREAM_DEMAND_TIME 2
#define STREAM_LAG 3
#define INV_LIST 1
#define AVG_ORDER 1
#define AVG_HOLD 2
#define AVG_SHORT 3

void arrival(void); //arrival of new inventory
void order(void); //new order from customer
void endMonth(void); //end of month (eval inventory)
void updateStats(void); //update the time average statistics
void report(void); //send the end report of the simulation (to output file or screen)
void init(void); // initialize all the variables for the inventory simulation(read input file)

//define variables for the inventory simulation
int amount, bigs, initialInv, invLevel, nextEventType, numEvents, numMonths, numValuesDemand, smalls, numPolicies;
float meanInterDemand, setupCost, incCost, holdCost, shortCost, minLag, maxLag, probDistDemand[26], lastEvent;

int main(int argc, char* argv[]){

  //  init_simlib();
  init();
  while(1){//start the simulation loop

    timing();
    if(next_event_type == 3)
      break;
    

  }
  
}

void init(void){//initialize simlib and local variables(from input file), create initial events

  init_simlib();
  numEvents = 4;
  lastEvent = 0;
  FILE *in = fopen("inv.in","r");
  fscanf(in, "%d %d %d %d %f %f %f %f %f %f %f", &initialInv,&numMonths,&numPolicies,&numValuesDemand,&meanInterDemand,
	 &setupCost, &incCost, &holdCost, &shortCost, &minLag, &maxLag);

  int i;
  for( i = 0; i < numValuesDemand;i++){

    fscanf(in,"%f",&probDistDemand[i]);

  }
  transfer[0] = initialInv;
  list_file(FIRST,INV_LIST);
  event_schedule(1.0e+30,EVENT_ARRIVAL);//no current incoming inventory
  event_schedule((sim_time + expon(meanInterDemand, STREAM_DEMAND)),EVENT_ORDER);//schedule the first customer order event
  event_schedule(numMonths, EVENT_END_SIM);//end of the simulation
  event_schedule(0,EVENT_END_MONTH);//run this event first since a new month begins at the start of the simulation
  
  /*
  printf("inv list init to : %.2f",transfer[0]);
  printf("set the initial inventory to : %d\n",initialInv);
  printf("set the number of months to : %d\n",numMonths);
  */
}
void endMonth(){

  event_schedule((sim_time + 1), EVENT_END_MONTH);//schedule the end of month/beginng of the next month
  
}
