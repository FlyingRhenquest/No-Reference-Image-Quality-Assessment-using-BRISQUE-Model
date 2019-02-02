#ifndef JD_BRISQUE
#define JD_BRISQUE
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <libsvm/svm.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <opencv2/opencv.hpp>

/*
 * All right, hopefully I've got this to the point where all you need to
 * call is jd_brisque::load_model against the allmodel file, and then
 * dump the model and a cv::Mat into jd_brisque::computescore. Lower
 * score is better.
 */

namespace jd_brisque {

  template<class T> class Image
    {
    private:

      cv::Mat imgp;
    public:
      Image(cv::Mat img=0)
        {
	  imgp=img.clone();
        }
      ~Image()
        {
	  imgp=0;
        }
      cv::Mat equate(cv::Mat img) 
      {
	img = imgp.clone();
	return img;
      }
      
      void showimage() {
	cv::imshow("imgp", imgp);
	cv::waitKey(0);
	cv::destroyAllWindows();
      }
      inline T* operator[](const int rowIndx)
      {
	//imgp->data and imgp->width
	return (T*)(imgp.data + rowIndx*imgp.step);
      }
    };

  typedef Image<double> BwImage;
  //function declarations
  cv::Mat AGGDfit(cv::Mat structdis, double& lsigma_best, double& rsigma_best, double& gamma_best);
  void ComputeBrisqueFeature(cv::Mat& orig, std::vector<double>& featurevector);
  float computescore(cv::Mat &orig, svm_model *model);
  svm_model *load_model(std::string filename);

}
#endif
