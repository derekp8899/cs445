//class for keeping stats of the patients relavant to the simulation

class patient{

 private:
  double arrive;
  double serviceTime;
  double depart;
  double totalWait;
  int type;//for final server number

 public:
  patient();
  void setArrive(double);
  void setServiceTime(double);
  void setDepart(double);
  double getArrive(void);
  double getTotalTime(void);
  double getDepart();
  double getServiceTime();
  void setWait(double);
  double getWait();
  int getType();
  void setType(int);
  
};
