#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdio.h>

#include "confusion_matrix.h"
#include "instances.h"
#include "knn.h"
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Disables buffering to display progress
    setbuf(stdout, NULL);

    // Initializes MPI
    int rc, rank;
    rc = MPI_Init(&argc, &argv);
    if(rc != MPI_SUCCESS) {
        cout <<"Error starting MPI program. Terminating.\n";
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    // Checks the number of input arguments
    if (argc < 4){
        cout <<"./launch_knn \"train_file\" \"test_file\" \"k\"" <<endl;
        return -1;
    }
    const char* train_file = argv[1];
    const char* test_file = argv[2];
    int k = atoi(argv[3]);

    // All nodes need the train instances
    Instances train_instances(train_file);
    Instances test_instances(test_file);
    Knn classifier(&train_instances, k);
    ConfusionMatrix confusion_matrix;

    // Displays some information on the data
    if(rank == 0) {
        cout <<"Train instances \n";
        train_instances.print_information();
        cout <<endl <<"Test instances" <<endl;
        test_instances.print_information();
    }

    // Starts predicting
    MPI_Barrier(MPI_COMM_WORLD);
    clock_t t = clock();
    for (int i = 1; i < test_instances.num_instances(); ++i) {
        Mail* mail_to_classify = test_instances.instance(i);
        int predicted_label = classifier.ClassifyMpi(mail_to_classify);
        if(rank == 0) {
            confusion_matrix.AddPrediction(mail_to_classify,
                    predicted_label);
        }
        MPI_Barrier(MPI_COMM_WORLD);
	
	break;
    }
    t = clock() - t;

    if(rank == 0) {
	    cout <<endl
             <<"execution time: "
             <<(t*1000)/CLOCKS_PER_SEC
             <<"ms\n\n";
        //confusion_matrix.PrintEvaluation();
    }

    MPI_Finalize();
    return 0;
}
