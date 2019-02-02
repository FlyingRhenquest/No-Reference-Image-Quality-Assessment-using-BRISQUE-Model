## Intro

Ok, so this is my attempt to turn [Krshrimali's brisque code](https://github.com/krshrimali/No-Reference-Image-Quality-Assessment-using-BRISQUE-Model) into a useful library.

To that end I:

 * Removed extraneous code (svm training, various files that include main, cmake artifacts from building in the directory, svm source and some data that he apparently hard-coded into a function at some point.

 * Put the whole thing in a namespace.

 * Removed using namespaces and added namespaces to things that he'd been using using namespace for previously.

 * Rewrote his cmake file to disable in-source build, compile files to a library add install targets.

 * Also broke model loading out from compute_score, because I don't want to load a model every time I call the function. So now you load_model first and then hand the model to compute_score whenever you want to use it. This does require you to svm_free_and_destroy the model later on, if you want to avoid a memory leak.

 * Wrote little unit test to do a basic sanity check that usage works correctly and returns some sort of value (I do not validate that the value in question is particularly correct, just that it returns.)

## Building

 * git clone this to a reasonable directory (lke maybe brisque_cpp)

 * Make a build directory somewhere. Like /tmp/build or something.

 * Run cmake on the C++ directory ie: cmake ~/sandbox/brisque_cpp/C++ (You can specify -DCMAKE_INSTALL_PREFIX if you want to, it'll default to /usr/local)

 * make && make install (or sudo make install)

 * You can also optionally ctest --verbose

## Using

 * Assuming it's installed, #include <brisque/brisque.h>

 * Load an image into a cv::Mat with OpenCV in the usual way

 * Load ${INSTALL_PREFIX}/share/brisque/allmodel with svm_model *my_model = jd_brisque::load_model("/usr/local/share/brisque/allmodel") (Or wherever your install prefix was.

 * Check that my_model is not null.

 * run jd_brisque::computescore against your mat with the model: float result = jd_brisque::computescore(my_cv_mat, my_model);

 * Do something with result

 * svm_free_and_destroy(&my_model) or leak memory