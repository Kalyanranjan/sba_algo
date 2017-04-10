
#include <fstream>
#include <iterator>
#include <stdexcept>

#include "./OsiManager.h"
#include "./OsiStringUtils.h"
using namespace std;
using namespace osiris;

int main(int argc, char const *argv[]) {
  // Create black empty images
  // cv::Mat image = cv::Mat::zeros( 400, 400, CV_8UC3 );
  //
  // // Draw a line
  // cv::line( image, cv::Point( 15, 20 ), cv::Point( 70, 50), cv::Scalar( 110, 220, 0 ),  2, 8 );
  // cv::imshow("Image",image);
  //
  // cv::waitKey( 0 );
  try
  {
      OsiManager osi ;
      osi.loadConfiguration(argv[1]) ;
      osi.showConfiguration();
      osi.run();
  }
  catch ( std::exception & e )
  {
      std::cout << e.what() << std::endl ;
  }
  return 0;
}
