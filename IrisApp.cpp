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

#define ENROLLMENT_CONFIG "./config/EnrollmentConfig.ini"
#define AUTH_CONFIG "./config/AuthConfig.ini"
#define ENROLLAUTH_CONFIG "./config/TemplateAndMatchConfig.ini"

using namespace std;
using namespace osiris;

int main(int argc, char const *argv[]) {
  try
  {
      // cout << "Welcome to Iris Authentication App\n";
      // cout << "Press 1 for enrollment and 2 for authentication.  => ";
      //
      // int choice;
      // cin >> choice;
      //
      // fstream ulfile("./SERVER/USERS.LIST", std::ios_base::in);
      //
      // string s;
      // int userid;
      //
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
      DIR *dpdf;
      struct dirent *epdf;

      dpdf = opendir("./CURRENT");
      if (dpdf != NULL){
         while (epdf = readdir(dpdf)){
            if (strlen(epdf->d_name) > 2) {
              ofstream efnFile;
              efnFile.open("./numOfImage/enrollFileName.txt");
              efnFile << epdf->d_name;
              efnFile.close();
              break;
            }
         }
      }

      // OsiManager osi;
      // osi.loadConfiguration(ENROLLAUTH_CONFIG) ;
      // osi.showConfiguration();
      // osi.run();

  }
  catch ( std::exception & e )
  {
      std::cout << e.what() << std::endl ;
  }
  return 0;
}
