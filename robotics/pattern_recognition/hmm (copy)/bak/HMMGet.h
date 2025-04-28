#ifndef _HMM_GET_H_
#define _HMM_GET_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "/home/savage/vision/pattern_recognition/include_vision/basics_vqs_vision.h"
#include "/home/savage/vision/pattern_recognition/vq_vision/new_allocate.h"
#include "hmm_vision_lib.h"

#define SIZE_IMAGE_VECTORS 500
#define ERROR .000001

int num_centroids_sonar=NUM_CENTROIDS_SONAR;
extern int *alloc_vector_int();

class HMMGet {
private:
    int num_vectors;
    int update,show_prob;
    char object[128];
    Raw *vectors,*total_vectors[100];
    Centroid *centroids_vision;
    int *observations[100], num_states,flg_sonar;
    char path[300];
    char data_file[300];
    int num_file,flag,num_total_vectors[100];
    int size_vectors;
    int i,j,k,l;
    int size_vq;
    int num_centroids_vision;
    char vq_file[300];
    int state[NUM_STATES+1][NUM_STATES+1];
    double bigger,prob[NUM_MAX_CENTROIDS],p;
    double vit_prob[NUM_MAX_CENTROIDS];
    float **ais,*pis,**bis;
    double p_old,error;
public:
    void show_help(char *file);
    int get_inputs(int argc, char **argv, char *object, int *show, int *num_states, char *path, int *size_vq, char *vq_file);
    int update_hmm_viterbi(char *object, int num_images, int *num_vectors, int **obs, int num_states, char *path, int num_symbols);
    int create_initial_hmm(char *object, int num_images, int *size_images, int **obs, int num_states, char *path, int num_symbols);
    void init_hmm();
};

#endif