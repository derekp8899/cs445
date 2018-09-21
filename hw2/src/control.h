#include "server.h"
class control{

 private:
  double simClock;
  double nextArrive;
  double nextDepart;
  double aMean;
  double sMean;
  double intArrival;
  double MST;
  double avgWait;
  double avgQue;
  double lastEvent;
  double p[4];//probability for each queue
  int stopCond;
  int numServed;
  int nextType;
  int arriveMean;//for hw 1 these is will be set by command line args from main
  int serviceMean;
  int numInQue;
  int totalArrivals;
  int departFrom;

  
 public:
  control();
  void simulate(void);
  static double genArrive(double);
  static double genService(double);
  void update(void);
  void decide(void);
  void procArr(server *);
  void procDepart(server **);
  char * sendReport(void);
  int getQueueSize();
  double findDepart(server**);
  void moveServer(server**,int);
  static int genType(double[]);  
};

