#include <ctime>
#include <iostream>

#include "knn.h"

using namespace std;

int main(int argc, char* argv[]) {

    int k_1 = 4;
	Knn classifier_1(NULL, k_1);
    int* labels_1 = new int[k_1];
    labels_1[0] = 0;
    labels_1[1] = 0;
    labels_1[2] = 1;
    labels_1[3] = 0;
    int pred_1 = classifier_1.PredictedLabel(labels_1);
    if (pred_1 != 0) {
        cout << "ERR: Your function is not returning the most represented label"
            << endl;
        return -1;
    }

    int k_2 = 1;
	Knn classifier_2(NULL, k_2);
    int* labels_2 = new int[k_2];
    labels_2[0] = 1;
    int pred_2 = classifier_2.PredictedLabel(labels_2);
    if (pred_2 != 1) {
        cout << "ERR: Your function is not returning the most represented label"
            << endl;
        return -1;
    }

    int k_3 = 2;
	Knn classifier_3(NULL, k_3);
    int* labels_3 = new int[k_3];
    labels_3[0] = 0;
    labels_3[1] = 1;
    int pred_3 = classifier_3.PredictedLabel(labels_3);
    if (pred_3 != 0) {
        cout << "ERR: When there are as many ham as spam, "
            << "your function should return ham" << endl;
        return -1;
    }

    cout <<"CONGRATS! TESTS PASSED"<<endl;

    // Deletes the allocated memory
    delete[] labels_1;
    delete[] labels_2;
    delete[] labels_3;

    return 0;
}
