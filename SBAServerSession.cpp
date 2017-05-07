#include <iostream>
#include <cstdlib>

using namespace std;


  class SBAServerSession {

  public:
    SBAServerSession();
    ~SBAServerSession();

    SBAServerSession(int userID);
    SBAServerSession(int userID, int seed);

    void runAuth();

  private:
    int id;
    int state;
    string Rk;

    int getID();
    void setID(int id);

    int getState();
    void updateState();

    void getRandomFromState();

    void updateRk();

    void readUserData();

    void writeUserData();

    void writeToSandbox();
  };
