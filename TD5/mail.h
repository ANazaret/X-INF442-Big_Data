#ifndef MAIL_H_
#define MAIL_H_

#include <vector>

class Mail {

    public:
        Mail(int id, int feature_dimension):
            id_(id), label_(-1), features_(feature_dimension) {};
        ~Mail() {};

        int id() const { return id_; }
        int label() const { return label_; }
        std::vector<int> features() const { return features_; }

        void SetLabel(int label) { label_ = label; }
        void SetFeature(int index, int feature) { 
            features_[index] = feature;
        }

        int Distance(Mail* mail) const;

    private:
        int id_;
        // 0 for ham, 1 for spam
        int label_;

        std::vector<int> features_;
};

#endif    // END_MAIL_H_
