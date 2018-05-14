/******************************************************************************
 * FILE: mpi_helloBsend.cpp
 * DESCRIPTION:
 *   MPI tutorial example code: Simple hello world program that uses blocking
 *   send/receive routines.  Based on a C program by Blaise Barney.
 * AUTHOR: Benjamin Smith
 * LAST REVISED: 20/04/2016
 ******************************************************************************/
#include "mpi.h"
#include <iostream>

const int MASTER = 0;

int main(int argc, char *argv[]) {
	int numtasks, taskid, len, partner, message;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	// We require an even number of tasks.
	if (numtasks % 2 != 0) {
		if (taskid == MASTER) {
			std::cout << "Quitting. Need an even number of tasks: numtasks="
				<< numtasks << std::endl;
		} else {
			// do nothing: we quit silently.
		}
	} else {
		MPI_Get_processor_name(hostname, &len);
		std::cout << "Hello from task " << taskid << " on " << hostname << "!"
			<< std::endl;

		if (taskid == MASTER) {
			std::cout << "MASTER: Number of MPI tasks is " << numtasks << std::endl;
		}

		// Determine partner id and then send/receive with partner.
		// Eg. If numtasks = 2d, then the partner pairs are
		// (0,d),(1,d+1),...,(d-1,numtasks-1).
		if (taskid < numtasks / 2) {
			partner = numtasks / 2 + taskid;
		} else { // (taskid >= numtasks / 2)
			partner = taskid - numtasks / 2;
		}

		MPI_Send(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
		MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

		// print partner info and exit
		std::cout << "Task " << taskid << " is partner with " << message
			<< std::endl;
	}

	MPI_Finalize();
}
