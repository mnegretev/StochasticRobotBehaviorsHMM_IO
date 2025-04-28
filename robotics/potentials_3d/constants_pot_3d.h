#define DELTA_POT 3.50f
#define D0  5.0f // DO repulsion distance
#define D1 8.5 // D1 attraction distance
#define E1 240.05f // E1 and E2 attraction factors
#define E2 240.35f
#define ETA 2000.35 // eta repulsion factor
//#define EPS_DEST DELTA_POT/2.0f
#define EPS_DEST DELTA_POT*2
#define NUM_POT 500/DELTA_POT
//#define EPS_LOCAL_MINIMUM  0.1
//#define EPS_LOCAL_MINIMUM  5.1
#define EPS_LOCAL_MINIMUM  1*MAG_ADVANCE
