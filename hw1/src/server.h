#include "patient.h"
#include <vector>
using namespace std;
class server{

 private:
  int status;
  int numInQ;
  double nextArr;
  double nextDep;
  vector <patient>queue;
  
 public:
  server();
  int getStatus(void);
  void setStatus(int);

};
