#include "patient.h"
#include <queue>
#include <vector>
class server{

 private:
  int status;
  int numInQ;
  double nextArr;
  double nextDep;
  double lArr;
  double lServ;//lamda for the exponential distributions
  //std::vector <patient>queue;
  std::queue <patient>queue;
  //void genPatient();

 public:
  server(int,int);
  int getStatus(void);
  void setStatus(int);
  double getArr(void);
  double getDep(void);
  void genPatient(double);
  double patientArr(int);
  int queueLen();
  void setNextDep();
  double newArrive();
  void departure();
  double patientDep(double);
  double getServiceTime();
};
