KNN = launch_knn
KNN_ROC = launch_knn_roc
KNN_MPI = launch_knn_mpi

TEST_KNNSEQ_1 = test_knnSequential_PredictedLabel
TEST_KNNSEQ_2 = test_knnSequential_Insert
TEST_MERGE = test_merge

HFILES=$(wildcard *.h)
OBJECTS = mail.o instances.o confusion_matrix.o knn.o

CXX = mpic++ -O3

all : $(KNN) $(KNN_MPI) $(KNN_ROC)

$(KNN) : $(OBJECTS) $(KNN).o
	$(CXX) $(INCLUDES) -o $@ $^ $(LIBS)

$(KNN_ROC) : $(OBJECTS) $(KNN_ROC).o
	$(CXX) $(INCLUDES) -o $@ $^ $(LIBS)

$(TEST_KNNSEQ_1) : $(OBJECTS) $(TEST_KNNSEQ_1).o
	$(CXX) $(INCLUDES) -o $@ $^ $(LIBS)

$(TEST_KNNSEQ_2) : $(OBJECTS) $(TEST_KNNSEQ_2).o
	$(CXX) $(INCLUDES) -o $@ $^ $(LIBS)

$(TEST_MERGE) : $(OBJECTS) $(TEST_MERGE).o
	$(CXX) $(INCLUDES) -o $@ $^ $(LIBS)


$(KNN_MPI) : $(OBJECTS) $(KNN_MPI).o
	$(CXX) $(INCLUDES) -o $@ $^ $(LIBS)

%o: %.cpp
	$(CXX) -c $< -o $@

.PHONY: clean

clean :
	rm -f $(KNN) $(KNN_ROC) $(KNN_MPI) $(TEST_KNNSEQ_1) $(TEST_KNNSEQ_2) $(TEST_MERGE)
	rm -f *.o *.out
