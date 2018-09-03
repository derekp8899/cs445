//class for keeping stats of the patients relavant to the simulation

class patient{

 private:
  double arrive;
  double serviceTime;
  double depart;

 public:
  patient();
  void setArrive(double,double);
  void setServiceTime(double);
  void setDepart(double);
  double getArrive(void);
  double getTotalTime(void);

};
