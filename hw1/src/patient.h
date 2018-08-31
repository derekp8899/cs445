//class for keeping stats of the patients relavant to the simulation

class patient{

 private:
  double arrive;
  double serviceTime;
  double depart;

 public:
  patient();
  void setArrive(double);
  void setServiceTime(double);
  void setDepart(double);
  double getArrival(void);
  double getTotalTime(void);

};
