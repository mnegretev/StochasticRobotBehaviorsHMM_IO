#ifndef _HMMREC_H_
#define _HMMREC_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>




#include "/home/savage/vision/pattern_recognition/include_vision/basics_vqs_vision.h"
#include "/home/savage/vision/pattern_recognition/vq_vision/new_allocate.h"
#include "/home/savage/opencv/RawCapture.h"
#include "hmm_vision_lib.h"

class HMMRec: public RawCapture
{
private:
	char objects_file[300], in_file[300], **objects_name;
	int num_vectors;
	Centroid *centroids;
	double bigger, prob[NUM_MAX_CENTROIDS], p;
	double vit_prob[NUM_MAX_CENTROIDS];
	int index, i;
	int index_vit;
	double bigger_vit;
	int num_objects;
	int size_vectors;
	Raw *vectors;
	char path[300];
	char data_file[300];
	int size_vq;
	int num_centroids_vision;
	char vq_file[300];
	Centroid *centroids_vision;
	float ***ais, **pis, ***bis;
	int num_states;
	int j, k;
	int *observations, *seq_states[10];
	float average;
public:
	HMMRec() {
		average = 0;
		size_vectors = 3;
		index = 1;
	}

	~HMMRec() {
	}

	int get_inputs(int argc, char **argv) {
		get_inputs(argc, argv, objects_file, data_file, &size_vq, path, vq_file, &num_states);
	}

	int get_inputs(int argc, char **argv, char *objects_file, char *in_file, int *size_vq, char *path, char *vq_file, int *num_states) {
		int i;

		/* It sets default values */
		strcpy(objects_file, "vision_objects");
		strcpy(in_file, "test_image");
		*size_vq = 64;
		strcpy(path, "/home/savage/observations/cmucam/training_hsi/");
		strcpy(vq_file, "all");
		*num_states = NUM_STATES;
		set_camera(0);
		set_type(0);
		set_scale(8);


		/* reads input parameters */
		if (argc > 1) {
			for (i = 1;i < argc;i++) {
				if (!strcmp(argv[i], "-h")) {
					printf("rec_hmm_vision -h\n");
					printf("-f specifies the objects' file\n");
					printf("-c specifies the camera\n");
					printf("-r specifies the image reduction factor (1/n) \n");
					printf("-o specifies the color space, 0: rgb, 1: hsi \n");
					printf("-s specifies the image's file\n");
					printf("-q specifies the VQ's file\n");
					printf("-m specifies the size of the quantizer\n");
					printf("-n specifies the number of states of the HMM\n");
					printf("-p specifies the path\n");
					printf("-h shows this message\n");
					printf("example:\n rec_hmm_vision -c 0 -r 8 -o 0 -f vision_objects -s images_test_top_5 -m 64 -n 9 -p /home/savage/observations/cmucam/training_hsi/\n");

					exit(1);
				}
				if (!strcmp(argv[i], "-p")) {
					strcpy(path, argv[i+1]);
				}
				if (!strcmp(argv[i], "-c")) {
					set_camera(atoi(argv[i+1]));
				}
				if (!strcmp(argv[i], "-o")) {
					set_type(atoi(argv[i+1]));
				}
				if (!strcmp(argv[i], "-r")) {
					set_scale(atoi(argv[i+1]));
				}
				if (!strcmp(argv[i], "-s")) {
					strcpy(in_file, argv[i+1]);
				}
				if (!strcmp(argv[i], "-f")) {
					strcpy(objects_file, argv[i+1]);
				}
				if (!strcmp(argv[i], "-q")) {
					strcpy(vq_file, argv[i+1]);
				}
				if (!strcmp(argv[i], "-m")) {
					*size_vq = atoi(argv[i+1]);
				}
				if (!strcmp(argv[i], "-n")) {
					*num_states = atoi(argv[i+1]);
				}
			}
		} else {
			printf("Using default values \n");
		}

		printf("recognize_vision -f %s -s %s -m %d -p %s -q %s -n %d\n", objects_file, in_file, *size_vq, path, vq_file, *num_states);

		return(0);

	}

	int init() {
		if ((centroids_vision = (Centroid *)
		        malloc( (size_vq + 1) * sizeof(Centroid))) == NULL) {
			fprintf(stdout, "Allocation error: centroids");
			exit(0);
		}
		num_centroids_vision = read_vision_centroids(vq_file, centroids_vision, size_vectors, size_vq, path);

// it reads the names of the objects to be recognized
		if ( (objects_name = (char **) alloc_matrix_char(30, 300)) == 0) {
			printf("\n Memory allocation error ");
			exit(0);
		}

		num_objects = read_objects_name(objects_file, objects_name, path);

		for (i = 1;i <= num_objects;i++) {
			printf("objects %s\n", objects_name[i]);
		}

//it reads each the objects' HMMs
// It allocates the matrices used for the hmm evaluation

		ais = (float ***)  malloc( (unsigned) (num_objects + 1) * sizeof(float *));
		bis = (float ***) malloc( (unsigned) (num_objects + 1) * sizeof(float *));
		pis = (float **)   malloc( (unsigned) (num_objects + 1) * sizeof(float *));

		for (j = 1;j <= num_objects;j++) {

			if ((ais[j] = (float **)alloc_matrix(num_states + 1, num_states + 1 )) == 0) {
				printf("\n Memory allocation error ");
				exit(1);
			}

			if ((bis[j] = (float **)alloc_matrix(num_states + 1, size_vq + 1)) == 0) {
				printf("\n Memory allocation error ");
				exit(1);
			}

			if ((pis[j] = (float *)alloc_vector(num_states + 1)) == 0) {
				printf("\n Memory allocation error ");
				exit(1);
			}

		}

		/* It reads the hmm of each of the symbols */
		read_hmms(objects_name, num_objects, ais, bis, pis, num_states, size_vq, path);

	}
	
	int setImage(){
		// it reads the image vectors
		// it gets the number of vectors and their size
		sprintf(in_file, "%s%s.raw", path, data_file);
		num_vectors = get_size_image_vectors(in_file, &size_vectors);
		printf("%s num. vectors %d size vectors %d\n", in_file, num_vectors, size_vectors);

		/* it allocates raw vectors space */
		if ((vectors = (Raw *) malloc( (num_vectors + 1) * sizeof(Raw))) == NULL) {
			fprintf(stdout, "Allocation error: Raw vectors");
			return(0);
		}

		// it reads the input image vectors
		read_image_vectors(in_file, vectors);

		// it allocates the observations vectors //
		if ((observations = (int *) alloc_vector_int((num_vectors + 1)) ) == 0) {
			printf("\n Memory allocation error: observations ");
			exit(0);
		}

		// it allocates the states vectors
		for (i = 1;i <= num_objects;i++){
			if ((seq_states[i] = (int *) alloc_vector_int((num_vectors + 1))) == 0) {
				printf("\n Memory allocation error: observations ");
				exit(0);
			}
		}
	}
	
	int capture(){
		// it reads the image vectors
		// it gets the number of vectors and their size
		int num_vectors;
		
		get_raw();
		num_vectors = get_vector_size();
		
		
		// it allocates the observations vectors //
		if ((observations = (int *) alloc_vector_int((num_vectors + 1)) ) == 0) {
			printf("\n Memory allocation error: observations ");
			exit(0);
		}

		// it allocates the states vectors
		for (i = 1;i <= num_objects;i++){
			if ((seq_states[i] = (int *) alloc_vector_int((num_vectors + 1))) == 0) {
				printf("\n Memory allocation error: observations ");
				exit(0);
			}
		}
	}
	

	int find(const char *object_name) {
		Raw *vectors;
		
		capture();
		vectors = get_raw();
		quantize_vectors(centroids_vision, num_vectors, vectors, observations, num_centroids_vision, size_vectors);

		bigger = 0;
		bigger_vit = 0;

		for (i = 1;i <= num_objects;i++) {

			// It calculates the probabilities of each of the hmms
			prob[i] = get_hmm_prob(observations, ais[i], bis[i], pis[i], num_vectors, num_states);
			// The result is divided by 10 in order that the result fits the variable size
			prob[i] = exp(prob[i] / 10.);
			//printf("object %s probability %e\n",objects_name[i],prob[i]);

			if (prob[i] > bigger) {
				bigger = prob[i];
				index = i;
			}

			/* It calculates the best sequence of states using the Viterbi algorithm
			 * and the probability of a hmm given a symbol vector */
			vit_prob[i] = viterbi(observations, ais[i], bis[i], pis[i], num_vectors, num_states, seq_states[i]);
			vit_prob[i] = exp(vit_prob[i] / 10.);
			printf("object %s Viterbi probability %e\n", objects_name[i], vit_prob[i]);

			if (vit_prob[i] > bigger_vit) {
				bigger_vit = vit_prob[i];
				index_vit = i;

			}
		}


		for (i = 1;i <= num_objects;i++) {
			printf("object %s probability %e\n", objects_name[i], prob[i]);
			printf("object %s Viterbi probability %e\n", objects_name[i], vit_prob[i]);
		}
		printf("\n\n ****** Winner object %s %e ***** \n", objects_name[index], prob[index]);
		printf("\n\n ****** Winner Vitterbi object %s %e ***** \n", objects_name[index_vit], vit_prob[index_vit]);
		if (observations) free (observations);
		if (vectors) free(vectors);
		for (i = 1;i <= num_objects;i++)
			if (seq_states[i]) free(seq_states[i]);
		
		if (strcmp(object_name,objects_name[index])== 0){
			return 1;
		}
		else{
			return 0;
		}

	}
};

#endif