#include <random>

class control{

 private:
  double simClock;
  double nextArrive;
  double nextDepart;
  int nextType;
  
 public:
  double genArrive(void);
  double genDepart(void);
  void update(void);
  int decide(void);
  
};

