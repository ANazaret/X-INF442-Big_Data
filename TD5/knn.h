#ifndef KNN_H_
#define KNN_H_

#include <list>
#include <utility>  // Library for std::pair

#include "instances.h"
#include "mail.h"

class Knn {

  public:
    /*
     * Knn contructor, already implemented.
     * The syntax "train_instances_(train_instances), k_(k)" is equivalent to
     *   train_instances_ = train_instances;
     *   k_ = k;
     * It is used to initialize class members in constructors.
     */
    Knn(Instances* train_instances, int k):
      train_instances_(train_instances), k_(k) {};

    /*
     * Knn destructor, already implemented (it does nothing).
     */
    ~Knn() {};

    /*
     * Returns the predicted label for mail_to_classify
     * This method is for a sequential version of k-NN
     */
    int Classify(Mail* mail_to_classify) const;
    
    /*
     * Returns many label predictions (based on a threshold)
     *   for mail_to_classify
     * This methods is for a sequential version of k-NN
     */
    void Classify(Mail* mail_to_classify, double* thresholds,
            int* predicted_labels, int num_predictions) const;

    /*
     * Returns the predicted label for mail_to_classify
     * This methods is for an MPI version of k-NN
     *
     * The parallelization occurs in the computation of 
     *   the labels and distances from each training mail to
     *   the mail to classify (each node is assigned a subset
     *   of the training set)
     */
    int ClassifyMpi(Mail* mail_to_classify) const;

    /*
     * Takes an array containing k labels and returns the most represented 
     * label.
     * If there are as many ham as spam then the function must return ham
     * (in order to reduce the number of false alarms).
     */
    int PredictedLabel(int* labels) const;

    /*
     * Takes an array containing k labels and returns the most represented 
     * label --- ROC version
     * If there are as many ham as spam then the function must return ham
     * (in order to reduce the number of false alarms).
     */
    int PredictedLabel(int* labels, double threshold) const;

    /*
     * The labels of the k nearest neighbours are stored in the array labels
     * and the corresponding distances in distances.
     * Labels are sorted according to distances.
     *
     * This works as follows: initially the labels are set at some
     *   large value (see InitNearestNeighbours()), then a loop on the 
     *   training instances is carried out (in NearestNeighbours()), 
     *   and for each given training mail, Insert() computes the distance
     *   to mail_to_classify, and inserts it at the right place in the
     *   distances array (the label is inserted in the labels array
     *   in the corresponding position).
     *
     * labels[0] and distances[0] refer to the nearest neighbour
     * labels[k_-1] and distances[k_-1] refer to the k_th nearest neighbour
     *
     * Insert updates labels and distances to include train_mail in the array
     * of the k nearest neighbors if needed
     *
     * If train_mail is as close to mail_to_classify as a current neighbour
     * then it is inserted after this neighbour.
     *
     */
    void Insert(int* labels, int* distances, Mail* mail_to_classify,
        Mail* train_mail) const;

    /*
     * Merges the current k_ nearest neighbours
     *   (stored in local_labels and local_distances) found at 
     *   the root node of the MPI cluster, with the k_ nearest 
     *   neighbours computed at another node (other_labels, other_distances)
     *   The result holds the k_ closest training mails labels
     *   and distances among those found in the local_ and other_;
     *   the updated kNN list is stored in local_labels, local_distances
     *
     * local_distances and local_labels refer to 
     * the current k_ nearest neighbours in the root node.
     * other_distances and other_labels refer to 
     * the k_ nearest neighbours computed by another node
     * on its training data.
     *
     * If two neighbours are at equal distance, the one stored
     * in the root node is inserted before the one stored
     * in another node.
     *
     * This method is used in the MPI implementation only
     */
    void Merge(int* local_labels, int* local_distances, 
        const int* other_labels, const int* other_distances) const;

  private:
    // pointer to the training instances
    //   (stored as a vector of pointers to Mail, see instances.h)
    Instances* train_instances_; 
    int k_; // the number of nearest neighbours to be considered
    
    /* 
       This method initializes the array of k_ neighbours (of the
       mail_to_classify) to the maximum allowed numerical value,
       which is used in a simple descent algorithm which replaces
       current values with new values if they're smaller.
    */
    void InitNearestNeighbours(int* labels, int* distances) const;

    /*
     * labels and distances have been initialised with InitNearestNeighbours
     * Computes the nearest neighbours for mail_to_classify 
     * (labels and distances)
     */
    void NearestNeighbours(Mail* mail_to_classify,
			   int* labels, int* distances) const;
};

#endif    // END_KNN_H_
