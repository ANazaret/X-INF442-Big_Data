#include <ctime>
#include <cstdlib>
#include <iostream>

#include "confusion_matrix.h"
#include "instances.h"
#include "knn.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Checks the number of input arguments
    if (argc < 5) {
        cerr << "./launch_knn \"train_file\" \"test_file\" \"k\" \"num_points\""
            << endl;
        return -1;
    }

    const char* train_file = argv[1];
    const char* test_file = argv[2];
    // Number of nearest neighbours for k-NN
    int k = atoi(argv[3]);
    // Number of points to generate the ROC curve
    int num_points = atoi(argv[4]);

    Instances train_instances(train_file);
    Instances test_instances(test_file);
    Knn classifier(&train_instances, k);

    // Generates the list of thresholds
    double* thresholds = new double[num_points];
    thresholds[0] = 0;
    // Adds a thresholds > 1 in order to have the point (1,1) in the ROC curve
    for (int t = 1; t < num_points; t++) {
        thresholds[t] = double(t) / double(num_points-2);
    }
    // A confusion matrix for each threshold
    ConfusionMatrix* confusion_matrices = new ConfusionMatrix[num_points];

    // Starts predicting
    int* predicted_labels = new int[num_points];
    for (int i = 0; i < test_instances.num_instances(); i++) {
        Mail* mail_to_classify = test_instances.instance(i);
        classifier.Classify(mail_to_classify, thresholds,
                predicted_labels, num_points);
        for (int t = 0; t < num_points; t++) {
            confusion_matrices[t].AddPrediction(mail_to_classify,
                predicted_labels[t]);
        }
    }

    // Print the couples 'false alarm rate' 'detection rate'
    for (int t = 0; t < num_points; t++) {
        confusion_matrices[t].PrintRocEvaluation();
    }

    // Frees the allocated memory
    delete[] confusion_matrices;
    delete[] predicted_labels;
    delete[] thresholds;

    return 0;
}
