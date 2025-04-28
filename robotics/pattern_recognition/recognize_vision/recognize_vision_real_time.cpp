
//
// recognize_vision.cpp
//
// This program recognizes an image pattern using vector quantizers of a set of points that
// represent images' readings
//
//  J. Savage, Israel Figueroa, 5-6-2009
//      FI- UNAM
//


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "/home/savage/vision/pattern_recognition/include_vision/basics_vqs_vision.h"
#include "/home/savage/vision/pattern_recognition/vq_vision/new_allocate.h"
#include "/home/savage/opencv/opencv_images.h"

#include "cv.h"
#include "highgui.h"


/* it gets line inputs */
#define SECTIONS 3
bool write_ready = false;
const int reads = 4;
char objects_file[300], in_file[300], **objects_name;
int size_vq;
int num_vectors;
Centroid *centroids;
double bigger, tdistance[NUM_MAX_CENTROIDS];
int object_index = 1, i;
int num_objects;
int size_vectors = 0;
Raw *vectors;
Raw *screen_vectors;
char path[300];
int num_camera = 0, scale = 16, convert = 1;
int type;
bool record = false;
struct object_averages {
	char name[300];
	float average_recognized;
	float average_unrecognized;
};

typedef struct object_averages averages;

averages object;

int get_inputs_file(const char *config, char *objects_file, int *size_vq, char *path, int *scale, int *type, int *camera) {
	int i;
	FILE *cfg;
	char param0[4];
	char param1[128];

	puts("Reading config file");
	/* It sets default values */
	strcpy(objects_file, "vision_objects_rgb");
	*size_vq = 32;
	strcpy(path, "/home/savage/observations/imagecap/");
	*scale = 16;
	*type = 0;
	*camera = 0;

	cfg = fopen(config, "r");

	do {
		fscanf(cfg, "%s %s", param0, param1);
		printf("=== %s %s \n", param0, param1);

		if (!strcmp(param0, "-p")) {
			strcpy(path, param1);
		}
		if (!strcmp(param0, "-f")) {
			strcpy(objects_file, param1);
		}
		if (!strcmp(param0, "-r")) {
			*scale = atoi(param1);
		}
		if (!strcmp(param0, "-s")) {
			*type = atoi(param1);
		}
		if (!strcmp(param0, "-v")) {
			*camera = atoi(param1);
		}
		if (!strcmp(param0, "-m")) {
			*size_vq = atoi(param1);
			/*
			    if (*size_vq > NUM_CENTROIDS_SONAR) {
			        printf("\n Increase constant NUM_CENTROIDS_SONAR >= %d\n",*size_vq);
			        exit(1);
			    }
			*/
		}
	} while (!feof(cfg));
	fclose(cfg);

	return(0);

}


int get_inputs(int argc, char **argv, char *objects_file, int *size_vq, char *path, int *scale, int *type, int *camera) {
	int i;

	/* It sets default values */
	strcpy(objects_file, "vision_objects_rgb");
	*size_vq = 32;
	strcpy(path, "/home/savage/observations/imagecap/");
	*scale = 16;
	*type = 0;
	*camera = 0;




	/* reads input parameters */
	if (argc > 1) {
		for (i = 1;i < argc;i++) {
			if (!strcmp(argv[i], "-h")) {
				printf("recognize_vision -h\n");
				printf("-v selects camera\n");
				printf("-f specifies the objects' file\n");
				printf("-m specifies the size of the quantizer\n");
				printf("-p specifies the path\n");
				printf("-r specifies the scale\n");
				printf("-s specifies the type of values used, 0 rgb; 1 hsi\n");
				printf("-h shows this message\n");
				printf("example:\n ./recognize_vision_real_time -v 0 -f vision_objects_rgb -m 4 -s 0 -r 16 -p /home/savage/observations/imagecap/\n");

				exit(1);
			}
			if (!strcmp(argv[i], "-p")) {
				strcpy(path, argv[i+1]);
			}
			if (!strcmp(argv[i], "-f")) {
				strcpy(objects_file, argv[i+1]);
			}
			if (!strcmp(argv[i], "-r")) {
				*scale = atoi(argv[i+1]);
			}
			if (!strcmp(argv[i], "-s")) {
				*type = atoi(argv[i+1]);
			}
			if (!strcmp(argv[i], "-v")) {
				*camera = atoi(argv[i+1]);
			}
			if (!strcmp(argv[i], "-m")) {
				*size_vq = atoi(argv[i+1]);
				if (*size_vq > NUM_CENTROIDS_SONAR) {
					printf("\n Increase constant NUM_CENTROIDS_SONAR >= %d\n", *size_vq);
					exit(1);
				}
			}
		}
	} else {
		printf("Using default values \n");
	}

	printf("recognize_vision -f %s -m %d -r %d -s %d -p %s \n", objects_file, *size_vq, *scale, *type, path);

	return(0);

}


int read_objects_name(char *objects_file, char **objects_name, char *path) {
	char input_file[300], name[300];
	FILE *fp2;
	int i;


	/* It opens the file that contains the names of the objects to be recognized */
	sprintf(input_file, "%s%s.txt", path, objects_file);

	printf("Objects FILE: %s\n", input_file);

	fp2 = fopen(input_file, "r");
	if (fp2 == 0) {
		printf("\n Can not open %s ", input_file);
		return(0);
	}

	i = 1;

	/* it reads the names */
	while (fscanf(fp2, "%s", name) != EOF) {
		strcpy(objects_name[i], name);
		i++;
	}

	fclose(fp2);

	return(i -1);

}



double quantize_image(char **objects_name, Raw *vectors, int num_vectors, int size_vectors, int id_obj, int size_quantizer, char *path) {
	int cnt_errors = 0;
	float error = 0.0f, error_real = 0.0f;
	int num_centroids_vision;
	Centroid *centroids_vision;
	double t_distance = 0;
	float log_lrg_negative = -10;



	/* it reads the centroids */
	/* it allocates centroids space */
	if ((centroids_vision = (Centroid *)
	        malloc( (NUM_MAX_CENTROIDS + 1) * sizeof(Centroid))) == NULL) {
		fprintf(stdout, "Allocation error: centroids");
		exit(0);
	}

	num_centroids_vision =
	    read_vision_centroids(objects_name[id_obj], centroids_vision, size_vectors, size_quantizer, path);


	t_distance = quantize_vectors_vision(centroids_vision, num_vectors, vectors, num_centroids_vision, size_vectors);

	free (centroids_vision);

	return(t_distance);

}

int run_vq_recognition(Raw *vectors, int num_vectors) {
	bigger = LARGEST_POSITIVE;
	for (i = 1;i <= num_objects;i++) {
		tdistance[i] = quantize_image(objects_name, vectors, num_vectors, size_vectors, i, size_vq, path);

		if (tdistance[i] < bigger) {
			bigger = tdistance[i];
			object_index = i;
		}
		printf("object %s distance %f\n",objects_name[i],tdistance[i]);
	}


	if (strcmp(objects_name[object_index], "piso_rgb") == 0) {
		//printf("mv %d %");
	}
	printf("\n\n ****** Winner object %s %f ***** \n", objects_name[object_index], tdistance[object_index]);

	write_ready = false;
	if (record_recognized && snaps_count < reads) {
		printf("\n\n ****** Winner object %s %f ***** \n", objects_name[object_index], tdistance[object_index]);
		if (snaps_count == 0) {
			object.average_recognized = 0;
		}
		strcpy(object.name, objects_name[object_index]);
		object.average_recognized += tdistance[object_index] / reads;
		snaps_count ++;
	} else if (record_unrecognized && snaps_count < reads) {
		printf("\n\n ****** Winner object %s %f ***** \n", objects_name[object_index], tdistance[object_index]);
		if (snaps_count == 0) {
			object.average_unrecognized = 0;
		}
		strcpy(object.name, objects_name[object_index]);
		object.average_unrecognized += tdistance[object_index] / reads;
		snaps_count ++;
	} else if (snaps_count >= reads) {
		write_ready = true;
		record_recognized = false;
		record_unrecognized = false;
		snaps_count = 0;
		lock = false;
	}

	//~ for (i = 1;i <= num_objects;i++) {
	//~ printf("object %s distance %f\n", objects_name[i], tdistance[i]);
	//~ }
	return object_index;

}


int capture_and_recognize() {
	int found = 0;
	int floor = 0;
	int num_vectors = 0;
	IplImage *frame  = 0;
	char c;


	capture_resized(capture, scale, &img);

	cvShowImage("Full", img);

	c = cvWaitKey(10);
	if ((char)c == 27) {
		finish = true;
	}

	if ((char)c == 'r' && !lock) {
		puts("checking out");
		record_recognized  = true;
		record_unrecognized = false;
		snaps_count  = 0;
		lock = true;
	}

	if ((char)c == 'R' && !lock) {
		puts("checking out");
		record_recognized  = false;
		record_unrecognized  = true;
		snaps_count  = 0;
		lock = true;
	}

	num_vectors = get_image_section(img, screen_vectors, 1, 0);

	if (lock) {
		puts("Full");
		if (num_vectors > 0) {
			floor = run_vq_recognition(screen_vectors, num_vectors);
		}
	}
	return found;

}

int init_vq_recognition(int argc, char **argv) {

	/* it gets line inputs */
	if (argc > 1)
		get_inputs(argc, argv, objects_file, &size_vq, path, &scale, &type, &num_camera);
	else
		get_inputs_file("recognize.cfg", objects_file, &size_vq, path, &scale, &type, &num_camera);


// it reads the names of the objects to be recognized
	if ( (objects_name = (char **) alloc_matrix_char(30, 300)) == 0) {
		printf("\n Memory allocation error ");
		exit(0);
	}

	num_objects = read_objects_name(objects_file, objects_name, path);

	if (num_objects == 0)exit(0);


	for (i = 1;i <= num_objects;i++) {
		printf("objects %s\n", objects_name[i]);
	}



//it reads each the objects VQs
	if ((centroids = (Centroid *) malloc( (num_objects + 1) * sizeof(Centroid))) == NULL) {
		fprintf(stdout, "Allocation error: centroids");
		exit(0);
	}


// it gets the number of vectors and their size

	num_vectors = get_max_vectors(num_camera, scale);
	size_vectors = 3;
	printf("Num. vectors %d size vectors %d\n", num_vectors, size_vectors);


	num_vectors = get_max_vectors(num_camera, scale) / SECTIONS;
	size_vectors = 3;
	printf("Section: Num. vectors %d size vectors %d\n", num_vectors, size_vectors);
	/* it allocates raw vectors space */
	if ((vectors = (Raw *) malloc( (num_vectors + 1) * sizeof(Raw))) == NULL) {
		fprintf(stdout, "Allocation error: Raw vectors");
		return(0);
	}

	num_vectors = get_max_vectors(num_camera, scale);
	size_vectors = 3;
	printf("FullScreen: Num. vectors %d size vectors %d\n", num_vectors, size_vectors);
	/* it allocates raw vectors space */
	if ((screen_vectors = (Raw *) malloc( (num_vectors + 1) * sizeof(Raw))) == NULL) {
		fprintf(stdout, "Allocation error: Raw vectors");
		return(0);
	}
	init_camera(num_camera);
}



int main(int argc, char *argv[]) {
	FILE *data;


	finish = false;
	lock = false;
	record_recognized  = true;
	record_unrecognized = false;
	snaps_count = 0;
	write_ready = false;

	puts("Opening averages.dat");

	cvNamedWindow( "Full", 0 );

	init_vq_recognition(argc, argv);
	while (!finish) {
		capture_and_recognize();
	}
	return 0;
}

