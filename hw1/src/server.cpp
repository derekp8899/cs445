
#include "server.h"
#include "control.h"

server::server(int arrMean, int servMean){

  lArr=(double)1/arrMean;
  lServ = (double)1/servMean;
  status = 0;
  genPatient();
}

int server::getStatus(void){

  return status;

}

void server::setStatus(int n){

  status = n;

}
void server::genPatient(){

nextArr = control::genArrive(lArr);


}

double server::getArr(void){

return nextArr;

}
