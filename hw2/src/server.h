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
  //double l2nd;//landa for service time of 2nd queue if needed(redundant??)
  //int serverType;//either triage or trauma/prompt/acute
  int numDischared;
  double avgDelay;
  double avgque;
  double serverUtl;
  int numServers;
    std::queue <patient>queue;

 public:
    server(int,int,int);
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
  int getNumDischarged();
  double getAvgDelay();
  double getAvgQue();
  double getServerUtl();
  void updateWait(double);
  void moveIn(patient *);
  patient* moveOut();

};
