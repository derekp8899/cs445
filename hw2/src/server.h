#include "patient.h"
#include <queue>
#include <vector>
class server{

 private:
  int status;//number of working servers for 1 server if queue length is > 1  for n servers if queue length is > n (indexed at 0)
  int numInQ;
  double nextArr;
  double nextDep;
   int nextMove;
  double lArr;
  double lServ;//lamda for the exponential distributions
  //double l2nd;//landa for service time of 2nd queue if needed(redundant??)
  //int serverType;//either triage or trauma/prompt/acute
  int numDischared;
  double avgDelay;
  double avgque;
  double serverUtl;
  int numServers;
  double *p;
  double serverUtil[3];
  std::queue <patient>queue;
  std::vector<double>departList;
  
 public:
    server(int,int,int,double[]);
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
  void patientDep(double);
  double getServiceTime();
  int getNumDischarged();
  double getAvgDelay();
  double getAvgQue();
  double getServerUtl();
  void updateWait(double);
  void moveIn(patient *);
  patient* moveOut();
  void setNextMove();
  int getNextMove();
  void updateTotals(double, double);
  void updateDepartureTime(double,int);
  void report(double);
};
