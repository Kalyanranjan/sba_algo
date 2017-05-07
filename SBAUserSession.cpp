#include <iostream>
#include <cstdlib>


using namespace std;

  class SBAUserSession {

  public:

    SBAUserSession();
    ~SBAUserSession();

    SBAUserSession(int userID);
    SBAUserSession(int userID, int seed);
    void runAuth();

  private:
    int id;
    int state;
    string Tk;

    int getID();
    void setID(int id);

    int getState();
    void updateState();

    int getRandomFromState();

    void blindTemplate();

    void updateTk();

    void readUserData();

    void writeUserData();

    void writeToSandbox();
  };
