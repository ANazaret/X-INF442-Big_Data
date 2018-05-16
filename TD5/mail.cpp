#include "mail.h"        

using namespace std;

#include <cassert>
#include <cmath> // std::abs

// Manhattan distance
int Mail::Distance(Mail* mail) const {
    assert(mail->features_.size() == features_.size());
    int distance = 0;
    for (unsigned int i = 0; i < features_.size(); ++i) {
        distance += abs(mail->features_[i] - features_[i]);
    }
    return distance;
}
