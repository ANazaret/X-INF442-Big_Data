#include "instances.h"

#include <cstdio>
#include <iostream>

using namespace std;

Instances::Instances(const char* file) {
    // Reads the number of instances and the feature dimension
    // from the input file
    FILE* f = fopen(file, "r");
    if (f ==  NULL) {
        fprintf(stderr, "ERR: Impossible to open %s\n", file);
        return;
    }
    num_ham_ = 0;
    num_spam_ = 0;
    // writing the results of fscanf into a variable to avoid intimidating warnings...
    int ignore = fscanf(f, "%i", &num_instances_);
    ignore = fscanf(f, "%i", &feature_dimension_);
    ignore++;

    for (int instance = 0; instance < num_instances_; ++instance) {
        // Creates an object for the new instance
        Mail* mail = new Mail(instance, feature_dimension_);
        // Reads the label
        int label;
        ignore = fscanf(f, "%i", &label);
        mail->SetLabel(label);
        // Update the number of ham/spam
        if (label == 0) {
            num_ham_++;
        } else {
            num_spam_++;
        }
        // Reads the features
        int feature;
        for (int i = 0; i < feature_dimension_; ++i) {
            ignore = fscanf(f, "%i", &feature);
            mail->SetFeature(i, feature);
        }
        instances_.push_back(mail);  
    }
    fclose(f);
}

Instances::~Instances() {
    for (unsigned int i = 0; i < instances_.size(); ++i) {
        delete(instances_[i]);
    } 
}

void Instances::print_information() const {
    cout <<"Number of instances: "
        <<this->num_instances()
        <<" ("
        <<this->num_ham()
        <<" ham, " 
        <<this->num_spam()
        <<" spam)\n";
    cout <<"Feature dimension: "
        <<this->feature_dimension()
        <<endl;
}
