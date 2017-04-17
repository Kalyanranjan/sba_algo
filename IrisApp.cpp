#include <iostream>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

/* Unix FileSystem commands headers*/
// #include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/*OSIRIS headers*/
#include "./OsiManager.h"
#include "./OsiStringUtils.h"

#define ENROLLMENT_CONFIG "./.config/EnrollmentConfig.ini"
#define AUTH_CONFIG "./.config/AuthConfig.ini"
#define PREAUTHENROLL_CONFIG "./.config/PreAuthEnrollmentConfig.ini"
#define ENROLLFILENAME_LOC "./.numOfImage/enrollFileName.txt"
#define AUTHFILENAME_LOC "./.numOfImage/authFileNames.txt"
#define UPLOAD_LOC "./UPLOAD/"
#define USERLIST_LOC "./SERVER/userlist/USERS.LIST"
#define MATCHRESULT_LOC "./.SANDBOX/LASTMATCHRESULT.txt"

#define ENROLLMENT 1
#define AUTHENTICATION 2

#define MATCHTHRESHOLD 0.29

using namespace std;
using namespace osiris;

int main(int argc, char const *argv[]) {
  try
  {
      cout << "Welcome to Iris Authentication App\n";
      cout << "Press 1 for enrollment and 2 for authentication.  => ";

      int choice;
      cin >> choice;

      int id;
      string uName;
      fstream ulFile(USERLIST_LOC, std::ios_base::in); //File for list of users in SERVER
      OsiManager osi;

      if (choice == ENROLLMENT) { //Enrollment
        cout << "You have chosen to enroll\n";

        cout << "\nFollowing user-ids are already taken\n";
        while (ulFile >> id) {
            cout << id << " ";
            ulFile >> uName;
        }
        ulFile.close();
        cout << "\n";

        /*Collect User Info */
        cout << "\nEnter your userid (numbers only): ";
        cin >> id;
        cout << "\nNOW GO AND UPLOAD AN IMAGE WITH THE SAME FILE NAME AS THIS ID!!! ";
        cout << "\nThen press any key followed by ENTER to continue";
        cin >> uName; //Wait for Arbitrary input
        cout << "Enter your Name followed by underscore and L or R (Alex_R): ";
        cin >> uName;
        cout << id;
        /*Save to USERLIST in SERVER*/
        fstream ulFile(USERLIST_LOC, std::fstream::app);
        ulFile << id << " " << uName << endl;
        ulFile.close();

        /*Read Image file name and put to enrollFileName list*/
        DIR *dpdf;
        struct dirent *epdf;
        bool imageFound = false;
        dpdf = opendir(UPLOAD_LOC);
        if (dpdf != NULL){
           while (epdf = readdir(dpdf)){
              if (strlen(epdf->d_name) > 2) {
                ofstream efnFile;
                efnFile.open(ENROLLFILENAME_LOC);
                efnFile << epdf->d_name;
                efnFile.close();
                imageFound = true;
                break;
              }
           }
        }
        if (!imageFound) {
          cout << "No Image found for enrollment. Exiting...\n";
          return 0;
        }

        /* Run OSIRIS algorithm with configuration */
        osi.loadConfiguration(ENROLLMENT_CONFIG) ;
        osi.run();



      } else if (choice == AUTHENTICATION) {
        cout << "You have chosen to authenticate\n";

        /*Display Users%*/
        cout << "\nWhich User are you?\n";
        while (ulFile >> id) {
          ulFile >> uName;
          cout << id << " " << uName << endl;
        }
        ulFile.close();

        /*Ask user for identity*/
        cout << "\nEnter your userid (number only): ";
        cin >> id;
        cout << "\nNOW GO AND UPLOAD AN IMAGE WITH THE SAME FILE NAME AS THIS ID!!! ";
        cout << "\nThen press any key followed by ENTER to continue";
        cin >> uName; //Wait for Arbitrary input

        /*Generate template of authenticating image*/
        osi.loadConfiguration(PREAUTHENROLL_CONFIG) ;
        osi.run();

        /* Copy Original Template to the Sandbox*/
        std::ifstream  src("./SERVER/"+to_string(id)+"_code.bmp", std::ios::binary);
        std::ofstream  dst("./.SANDBOX/"+to_string(id)+"_code.bmp", std::ios::binary);
        dst << src.rdbuf();
        src.close();
        dst.close();
        std::ifstream src2("./SERVER/"+to_string(id)+"_mano.bmp", std::ios::binary);
        std::ofstream dst2("./.SANDBOX/"+to_string(id)+"_mano.bmp", std::ios::binary);
        dst2 << src2.rdbuf();
        src2.close();
        dst2.close();

        /*Make a list for Authenticating (SERVER and UPLOAD) images*/
        std::ofstream afnFile(AUTHFILENAME_LOC);
        afnFile << to_string(id)+".jpg  "+to_string(id)+"i.jpg";
        afnFile.close();

        /* Run Match*/
        OsiManager osi2;
        osi2.loadConfiguration(AUTH_CONFIG);
        osi2.showConfiguration();
        osi2.run();

        /* Read MatchResult */
        string str;
        float matchRes = 100;
        fstream mrFile(MATCHRESULT_LOC, std::ios_base::in); //File for list of users in SERVER
        while (mrFile >> str) {
          mrFile >> str;
          mrFile >> matchRes;
        }

        /*Check match Value */
        cout << "\n\nThe match value is:  " << matchRes << endl;
        cout << "The match threshold value is: " << MATCHTHRESHOLD << endl;
        if (matchRes < MATCHTHRESHOLD) {
          cout << "AUTHENTICATION SUCCESSFUL!!!\n\n";
        } else {
          cout << "AUTHENTICATION FAILED!!!\n\n";
        }

      }
  }
  catch ( std::exception & e )
  {
      std::cout << e.what() << std::endl ;
  }
  return 0;
}
