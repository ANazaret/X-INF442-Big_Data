#include "knn.h"
#include "mpi.h"

#include <cstdio>
#include <limits>
#include <iostream>

using namespace std;

int Knn::Classify(Mail* mail_to_classify) const {
    int* labels = new int[k_];
    int* distances = new int[k_];
    this->InitNearestNeighbours(labels, distances);

    this->NearestNeighbours(mail_to_classify, labels, distances);

    int label = PredictedLabel(labels);

    // Frees the allocated memory
    delete[] labels;
    delete[] distances;

    return label;
}

void Knn::Classify(Mail* mail_to_classify, double* thresholds, int* predicted_labels, int num_predictions) const {
    int* labels = new int[k_];
    int* distances = new int[k_];
    this->InitNearestNeighbours(labels, distances);

    this->NearestNeighbours(mail_to_classify, labels, distances);

    for (int i = 0; i < num_predictions; i++) {
        predicted_labels[i] = PredictedLabel(labels, thresholds[i]);
    }

    // Frees the allocated memory
    delete[] labels;
    delete[] distances;
}

void Knn::InitNearestNeighbours(int* labels, int* distances) const {
    // Arrays to store the k nearest neighbours
    for (int i = 0; i < k_; ++i) {
        labels[i] = -1;
        distances[i] = std::numeric_limits<int>::max();
    }
}




void Knn::Merge(int* local_labels, int* local_distances,
        const int* other_labels, const int* other_distances) const{
  int cur_local = k_;
    int cur_other = k_;
    // Gets rid of the neighbours which are too far away
    while (cur_local + cur_other > k_) {
        if (local_distances[cur_local-1] > other_distances[cur_other-1]) {
            cur_local--;
        } else {
            cur_other--;
        }
    }
    // Merges the two arrays in the local one
    while (cur_local || cur_other ) {
        if (!cur_local || (cur_other &&
                    local_distances[cur_local-1] <= other_distances[cur_other-1])) {
            cur_other--;
            local_distances[cur_local + cur_other] = other_distances[cur_other];
            local_labels[cur_local + cur_other] = other_labels[cur_other];
        } else {
            cur_local--;
            local_distances[cur_local + cur_other] = local_distances[cur_local];
            local_labels[cur_local + cur_other] = local_labels[cur_local];
        }
    }
}


int Knn::PredictedLabel(int* labels) const {
    int num_spam = 0;
    int num_ham = 0;
    for (int i = 0; i < k_; ++i) {
        switch(labels[i]) {
            case 0:
                num_ham++;
                break;
            case 1:
                num_spam++;
                break;
            default:
                break;
        }
    }
    return num_spam > num_ham ? 1 : 0;
}

void Knn::NearestNeighbours(Mail* mail_to_classify, int* labels, int* distances) const {
  // Iteration de Insert sur les train_mail
  int n_train = train_instances_->num_instances();
  for(int i=0; i < n_train; i++){
    Mail* train_mail = train_instances_->instance(i);
    this->Insert(labels, distances, mail_to_classify, train_mail);
  }
}

int Knn::ClassifyMpi(Mail* mail_to_classify) const {
  int nb_proc;
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  int n_train = train_instances_->num_instances();
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  int* labels = new int[k_];
  int* distances = new int[k_];
  this->InitNearestNeighbours(labels, distances);
  
  
  for(int i=rank; i < n_train; i += nb_proc){
    Mail* train_mail = train_instances_->instance(i);
    this->Insert(labels, distances, mail_to_classify, train_mail);
  }
  
  
  //std::cout << "Processus " << rank << " a fini, pret pour l'envoi" << std::endl;
  
  MPI_Send(labels, k_, MPI_INT, 0, 1, MPI_COMM_WORLD);
  MPI_Send(distances, k_, MPI_INT, 0, 0, MPI_COMM_WORLD);
  
  int label = -1;
  
  if (rank == 0){
      
      int* local_labels = new int[k_];
      int* local_distances = new int[k_];
      this->InitNearestNeighbours(local_labels, local_distances);
      
      int* other_labels = new int[k_];
      int* other_distances = new int[k_];
      for(int i=0; i < nb_proc; i++){
	  //MPI_Recv(local_labels, k_, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	  MPI_Recv(other_labels, k_, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	  MPI_Recv(other_distances, k_, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	  this->Merge(local_labels, local_distances, other_labels, other_distances);
	  //std::cout << i << std::endl;
      }
      
      for (int jj=0; jj<k_; jj++){
      cout << local_distances[jj] << " ";}
      cout <<endl;
      label = PredictedLabel(local_labels);
      cout << label <<endl;
      
      delete[] other_labels;
      delete[] other_distances;
      delete[] local_labels;
      delete[] local_distances;
      
  } 
  
  

  // Frees the allocated memory
  delete[] labels;
  delete[] distances;

  return label;
}
int Knn::PredictedLabel(int* labels, double threshold) const {
  int nb = 0;
  for(int i=0; i<k_; i++){
    nb += labels[i];
  }
  
  return nb >= k_*threshold;
}

void Knn::Insert(int* labels, int* distances, Mail* mail_to_classify,
        Mail* train_mail) const {
	  
    int distance = mail_to_classify->Distance(train_mail);
    
    for(int i=0; i<k_; i++){
      if(distances[i] > distance){	
	//Insertion
	for(int j=k_-1;j>i; j--){
	  distances[j] = distances[j-1];
	  labels[j] = labels[j-1];
	}
	distances[i] = distance;
	labels[i] = train_mail->label();
	break;
      }
    }
    
      
      
}

