

class server{

 private:
  int status;
  int numInQ;
  int nextAdd;
  int nextRem;
  int queue[];
  
 public:
  server();
  int getStatus(void);
  void setStatus(int);

};
