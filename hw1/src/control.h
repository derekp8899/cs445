#include <random>

class control{

 private:
  double simClock;
  double nextArrive;
  double nextDepart;
  int nextType;
  int arriveMean;//for hw 1 these is will be set by command line args from main
  int serviceMean;
  
 public:
  control();
  static double genArrive(double);
  static double genDepart(void);
  void update(void);
  int decide(void);
  
};

