//#include "patient.h"
#include <vector>
class server{

 private:
  int status;
  int numInQ;
  double nextArr;
  double nextDep;
  double lArr;
  double lServ;//lamda for the exponential distributions
  //vector <patient>queue;
  void genPatient();

 public:
  server(int,int);
  int getStatus(void);
  void setStatus(int);
  double getArr(void);
  double getDep(void);


};