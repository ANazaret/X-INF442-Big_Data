#include <cstdlib>
#include <ctime>
#include <iostream>

#include "confusion_matrix.h"
#include "instances.h"
#include "knn.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Checks the number of input arguments
	if (argc < 4){
        cout <<"./launch_knn \"train_file\" \"test_file\" \"k\"" <<endl;
        return -1;
    }
	const char* train_file = argv[1];
	const char* test_file = argv[2];
	int k = atoi(argv[3]);

	Instances train_instances(train_file);
	Instances test_instances(test_file);
	Knn classifier(&train_instances, k);
	ConfusionMatrix confusion_matrix;

	// Displays some information on the data
	cout <<"Train instances \n";
	train_instances.print_information();
	cout <<endl <<"Test instances" <<endl;
	test_instances.print_information();

	// Starts predicting
	clock_t t = clock();
	for (int i = 0; i < test_instances.num_instances(); ++i) {
		Mail* mail_to_classify = test_instances.instance(i);
		int predicted_label = classifier.Classify(mail_to_classify);
		confusion_matrix.AddPrediction(mail_to_classify, predicted_label);
	}
	t = clock() - t;

	cout <<endl
         <<"execution time: "
         <<(t*1000)/CLOCKS_PER_SEC
         <<"ms\n\n";

    confusion_matrix.PrintEvaluation();

	return 0;
}
