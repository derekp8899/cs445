
#include "server.h"

server::server(){

  status = 0;

}

int server::getStatus(void){

  return status;

}

void server::setStatus(int n){

  status = n;

}
