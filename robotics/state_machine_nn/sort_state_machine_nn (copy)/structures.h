
// *****************************************************************************
// * Structures.                                                               *
// *****************************************************************************


#define NUM_MAX_LAYERS 10

typedef struct _coord{
        float xc,yc,anglec;
} coord;

typedef struct _Behavior{
        float xc,yc,status;
        int flg_vector;
} Behavior;

typedef struct _AdvanceAngle{
        float distance,angle;
} AdvanceAngle;


typedef struct _Inputs{

 char path[256];
 char file[256];
 char environment[100];
 char output[100];
 char sensor[100];
 float xo,yo,xd,yd;
 float angle_robot;
 float theta_sensor;
 int num_sensors;
 float range_sensor;
 int num_vectors;
 float Mag_Advance;
 float radio_robot;
 float max_angle;
 int number_steps;
 int selection;
 float largest_value;
 int noise;

} Inputs;

typedef struct _weights{
        //float w[NUM_MAX_NN][NUM_MAX_NN];
        float **w;
} weights;



typedef struct _neural_net{
        char file[300];
        int num_layers; // number of layers
        int num_inputs; // number of inputs
        int num_outputs; // number of outputs
        int num_neurons_layer[NUM_MAX_LAYERS]; // number of neurons per layer
        int num_recurrent; // number of recurrent neurons <= num_outputs
        int num_inputs_delayed; // number of delayed inputs
        weights layer[NUM_MAX_LAYERS]; // weights between layers
        float **x; // inputs and outputs between layers
        float **prev_x; // previous inputs
} neural_net;



typedef struct _nn_inputs{
        int num_tests; // number of tests
        int num_inputs; // number of inputs
        int num_bits_inputs; // number of bits per inputs
        int **x; // inputs in input layer per test
        int **xb; // inputs in input layer per test
} nn_inputs;


