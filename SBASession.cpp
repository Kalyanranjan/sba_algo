#include <stdexcept>
#include "SBAUserSession.cpp"
#include "SBAServerSession.cpp"


using namespace std;


class SBASession {
  // CONSTRUCTORS & DESTRUCTORS
  /////////////////////////////

  SBASession() {
     // Do nothing
  }
  ~SBASession() {} //Do nothing

  SBASession(bool enroll) {
    enrollment = enroll;
  }

  int getUserID() { return userID; }
  void setUserID(int uid) { userID = uid; }

  bool getEnrollment() { return enrollment; }
  void setEnrollment(bool enroll) { enrollment = enroll; }

  bool getUserIDexists() { return userIDExists; }
  void setUserIDexists(bool uide) { userIDExists = uide; }

  void initializeSession();
  void initializeSession(int seed);
  void runAuth();

  std::string readUserIDs();


  private:
  bool enrollment;
  int userID;
  bool userIDExists;
  int seed;
  SBAUserSession sba_user;
  SBAServerSession sba_server;


  int generateSeed();
  float match();

  };
