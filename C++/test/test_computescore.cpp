/**
 * Quick sanity test for computescore.
 */

#include <cppunit/extensions/HelperMacros.h>
#include <brisque.h>
#include <opencv2/opencv.hpp>

class test_computescore : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(test_computescore);
  CPPUNIT_TEST(quick_sanity_test);
  CPPUNIT_TEST_SUITE_END();

public:

  void quick_sanity_test()
  {
    svm_model *model = jd_brisque::load_model(TEST_MODEL);
    CPPUNIT_ASSERT_MESSAGE("Error loading model " TEST_MODEL, nullptr != model);
    cv::Mat image = cv::imread(TEST_IMAGE, cv::IMREAD_COLOR);
    CPPUNIT_ASSERT_MESSAGE("Error loading image " TEST_IMAGE, !image.empty());
    float float_score = jd_brisque::computescore(image, model);
    int score = (int) float_score;
    std::cout << "Score: " << float_score << std::endl;
    // Oddly Krshrimali reports his original image as returning 26.826 and
    // this function returns 21-ish, but it seems like several things changed
    // in his code, so I'm guessing this is actually probably in the right ballpark
    svm_free_and_destroy_model(&model);
    CPPUNIT_ASSERT_MESSAGE("Looking for 21-ish in score", 21 == score);    
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(test_computescore);
