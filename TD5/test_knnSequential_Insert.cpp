#include <ctime>
#include <iostream>

#include "knn.h"

using namespace std;

void printArray(int k, int* array) {
      for(int i = 0; i < k; i++) {
        cout <<" " <<array[i];
      }
      cout <<endl;
}

void printLabelsDistances(int k, int* labels, int* distances) {
  cout <<"labels:      ";
  printArray(k, labels);
  cout <<"distances:   ";
  printArray(k, distances);
}

int main(int argc, char* argv[]) {

    int k_1 = 4;
    Knn classifier_1(NULL, k_1);
    int labels_1[]    = { 0, 0, 1, 0 };
    int distances_1[] = { 1, 2, 3, 4 }; 
    Mail* mail_to_classify_1 = new Mail(0, 1);
    mail_to_classify_1->SetFeature(0, 5);
    Mail* train_mail_1 = new Mail(0, 1);
    train_mail_1->SetLabel(1);
    
    cout <<endl <<endl <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
    cout <<"Train mail is too far away, not inserted" <<endl;
    cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
    cout <<"mail_to_classify: " <<"features: [5], " <<"label: 0" <<endl;
    cout <<"train_mail: " <<"features: [0], " <<"label: 1" <<endl;
    cout <<endl <<"%%%%% INPUTS %%%%" <<endl;
    printLabelsDistances(k_1, labels_1, distances_1);
    train_mail_1->SetFeature(0, 0);
    classifier_1.Insert(labels_1, distances_1,
            mail_to_classify_1, train_mail_1); 
    cout <<endl <<"%%%% OUTPUTS %%%%" <<endl;
    printLabelsDistances(k_1, labels_1, distances_1);
   
    cout <<endl <<endl <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
    cout <<"Train_mail is as close as the first current neighbour" <<endl;
    cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
    cout <<"mail_to_classify: " <<"features: [5], " <<"label: 0" <<endl;
    cout <<"train_mail: " <<"features: [4], " <<"label: 1" <<endl;
    train_mail_1->SetFeature(0, 4);
    cout <<endl <<"%%%%% INPUTS %%%%" <<endl;
    printLabelsDistances(k_1, labels_1, distances_1);
    classifier_1.Insert(labels_1, distances_1,
            mail_to_classify_1, train_mail_1); 
    cout <<endl <<"%%%% OUTPUTS %%%%" <<endl;
    printLabelsDistances(k_1, labels_1, distances_1);
    
    cout <<endl <<endl <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
    cout <<"Train_mail is as close as the last current neighbour" <<endl;
    cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
    cout <<"mail_to_classify: " <<"features: [5], " <<"label: 0" <<endl;
    cout <<"train_mail: " <<"features: [2], " <<"label: 0" <<endl;
    train_mail_1->SetFeature(0, 1);
    train_mail_1->SetLabel(0);
    cout <<endl <<"%%%%% INPUTS %%%%" <<endl;
    printLabelsDistances(k_1, labels_1, distances_1);
    classifier_1.Insert(labels_1, distances_1,
            mail_to_classify_1, train_mail_1); 
    cout <<endl <<"%%%% OUTPUTS %%%%" <<endl;
    printLabelsDistances(k_1, labels_1, distances_1);
    
    // Deletes the allocated memory
    delete mail_to_classify_1;
    delete train_mail_1;
    
    return 0;
}
