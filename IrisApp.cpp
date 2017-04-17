#include <iostream>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

/* Unix commands headers*/
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
#define USERLIST_LOC "./SERVER/USERS.LIST"

#define ENROLLMENT 1
#define AUTHENTICATION 2

using namespace std;
using namespace osiris;

int main(int argc, char const *argv[]) {
  try
  {
      cout << "Welcome to Iris Authentication App\n";
      cout << "Press 1 for enrollment and 2 for authentication.  => ";

      int choice;
      cin >> choice;

      fstream ulfile(USERLIST_LOC, std::ios_base::in);

      string s;
      int userid;

      if (choice == ENROLLMENT) { //Enrollment
        cout << "You have chosen to enroll\n";

        /*Collect User Info */
        int id;
        string lastName;
        cout << "\nEnter your userid (numbers only): ";
        cin >> id;
        cout << "Enter your LastName: ";
        cin >> lastName;

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
        OsiManager osi;
        osi.loadConfiguration(ENROLLMENT_CONFIG) ;
        // osi.showConfiguration();
        osi.run();



      } else if (choice == AUTHENTICATION) {
        cout << "You have chosen to authenticate\n";
      }

      //
      // int a;
      // string b;
      //
      // while (ulfile >> a)
      // {
      //     cout << a;
      //     ulfile >> b;
      //     // cout << b;
      // }



      // std::string::size_type sz;
      //
      // switch (choice) {
      //   case 1:
      //     cout << "You have chosen to enroll\n";
      //
      //     ulfile.open("./SERVER/USERS.LIST", ios::in);
      //     while (ulfile.good() && !(ulfile.eof())) {
      //       getline(ulfile, s);
      //       userid = stoi(s, nullptr, 10);
      //       cout << userid;
      //     }
      //
      //     break;
      //   case 2:
      //     cout << "You have chosen to authenticate\n";
      //
      //     ulfile.open("./SERVER/USERS.LIST", ios::in);
      //
      //     cout << "Insert your id. Following are the enrolled users.\n";
      //     while (ulfile.good() && !(ulfile.eof())) {
      //       getline(ulfile, s);
      //       cout << s << endl;
      //     }
      //
      //     break;
      // }
      //
      // struct stat st = {0};
      //
      // if (stat("./asd", &st) == -1) {
      //   mkdir("./asd", 0700);
      // }


      /*Read Image file name and put to enrollFileName list*/
      // DIR *dpdf;
      // struct dirent *epdf;
      //
      // bool imageFound = false;
      //
      // dpdf = opendir("./CURRENT");
      // if (dpdf != NULL){
      //    while (epdf = readdir(dpdf)){
      //       if (strlen(epdf->d_name) > 2) {
      //         ofstream efnFile;
      //         efnFile.open(ENROLLFILENAME_LOC);
      //         efnFile << epdf->d_name;
      //         efnFile.close();
      //         imageFound = true;
      //         break;
      //       }
      //    }
      // }
      //
      // if (!imageFound) {
      //   cout << "No Image found for enrollment. Exiting...\n";
      //   return 0;
      // }
      // OsiManager osi;
      // osi.loadConfiguration(ENROLLMENT_CONFIG) ;
      // // osi.showConfiguration();
      // osi.run();

  }
  catch ( std::exception & e )
  {
      std::cout << e.what() << std::endl ;
  }
  return 0;
}
