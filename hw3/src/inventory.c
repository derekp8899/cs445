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
int amount, bigs[4], initialInv, invLevel, nextEventType, numEvents, numMonths, numValuesDemand, smalls[4], numPolicies,currentCase;
float meanInterDemand, setupCost, incCost, holdCost, shortCost, minLag, maxLag, probDistDemand[26], lastEvent, avgHold, avgShort, avgOrderCost;

int main(int argc, char* argv[]){

  //  init_simlib();
  init();
  printf("starting the simulation\n");
  while(1){//start the simulation loop
    timing();
    updateStats();
    if(next_event_type == 3)//check if we are ending the simulation
      break;
    else{ //else one of the main events
      if(next_event_type == 1)
	arrival();
      if(next_event_type == 2)
	order();
      if(next_event_type == 4)
	endMonth();
    }
  }
  report();
}

void init(void){//initialize simlib and local variables(from input file), create initial events

  init_simlib();
  numEvents = 4;
  lastEvent = 0;
  currentCase = 0;
  avgOrderCost, avgHold, avgShort = 0;
  FILE *in = fopen("inv.in","r");// read all the values in from the input file 'inv.in'
  fscanf(in, "%d %d %d %d %f %f %f %f %f %f %f", &initialInv,&numMonths,&numPolicies,&numValuesDemand,&meanInterDemand,
	 &setupCost, &incCost, &holdCost, &shortCost, &minLag, &maxLag);

  int i;
  for( i = 0; i < numValuesDemand;i++){

    fscanf(in,"%f",&probDistDemand[i]);

  }
  for(i = 0;i < numPolicies;i++){

    fscanf(in,"%d %d", &smalls[i],&bigs[i]);

  }
  transfer[0] = initialInv; 
  list_file(FIRST,INV_LIST);//use simlib list to store the inventory value
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
void endMonth(void){//end of a month event (type 4)

  event_schedule((sim_time + 1), EVENT_END_MONTH);//schedule the end of month/beginng of the next month
  list_remove(FIRST,INV_LIST);
  float tempinv = transfer[0]; //temp variable for the inventory level;
  if(tempinv < smalls[currentCase]){
    amount = bigs[currentCase] - tempinv;
    avgOrderCost += setupCost + (incCost * amount);
    event_schedule(sim_time + uniform(minLag, maxLag, STREAM_LAG), EVENT_ARRIVAL);
  }
  transfer[0] = tempinv;
  list_file(FIRST,INV_LIST);//readd inv to the list

}

void order (void){//order from customer event (type 2)

  
  list_remove(FIRST,INV_LIST);
  //int orderSize =  random_integer(probDistDemand,STREAM_DEMAND);//need to ask about rand int function
  transfer[0] -= 1;//update inventory and restore the list
  list_file(FIRST,INV_LIST);
  
}

void arrival(void){ //arrival of new inventory from the supplier (type 1)

  list_remove(FIRST,INV_LIST);
  float tempinv = transfer[0];
  tempinv += amount;
  event_schedule(1e+30,EVENT_ARRIVAL);//new inventory has arrived will event will not occur until inventory is needed again
  transfer[0] = tempinv;
  list_file(FIRST,INV_LIST);//readd inv to the list

}

void updateStats(void){ //update the simulation statistics

  list_remove(FIRST,INV_LIST);
  float lastEventDelta = sim_time - lastEvent; //calc time since the last event
  lastEvent = sim_time; //set the new last event time for next loop cycle
  float tempinv = transfer[0];//temp variable to hold the current inventory level
  if(tempinv < 0){
    //transfer[0] = tempinv * lastEventDelta;
    avgShort -= tempinv * lastEventDelta;
  }
  else if(tempinv > 0){
    avgHold += tempinv * lastEventDelta;
  }
  transfer[0] = tempinv;
  list_file(FIRST,INV_LIST);//readd inv to the list
}
void report(void){

  printf("Simulation ended after %d months\n",numMonths);

}
