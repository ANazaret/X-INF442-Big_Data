#ifndef INSTANCES_H_
#define INSTANCES_H_

#include <vector>

#include "mail.h"

class Instances {

    public:
        Instances(const char* file);
        ~Instances();

        int num_instances() const { return num_instances_; };
        int num_ham() const { return num_ham_; };
        int num_spam() const { return num_spam_; };
        int feature_dimension() const { return feature_dimension_; };

        std::vector<Mail*> instances() const { return instances_; }
        Mail* instance(int index) const { return instances_[index]; }

        void print_information() const;

    private:
        std::vector<Mail*> instances_;
        const char* input_file_;

        int feature_dimension_; 
        int num_instances_;
        int num_spam_;
        int num_ham_;
};

#endif    // END_INSTANCES_H_
