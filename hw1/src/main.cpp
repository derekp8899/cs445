#include <iostream>
#include "control.h"
#include "server.h"
#include "patient.h"

using namespace std;
int main(){

  server a;

  cout << a.getStatus() << endl;

  a.setStatus(1);

  cout << a.getStatus() << endl;

  return 0;
}

