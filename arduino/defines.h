/*
+-----------------------------------------------------------+
| This is a header file for the project of autonomous vehi- |
| cle. This file contains the prototypes of functions that  |
| that are used in the main program, and also the definiti- |
| tion of some constants or global variables............... |
+-----------------------------------------------------------+
*/

// General
#define SPEED 15
#define CHECK_PNT 1

// Go function constants
#define CENTER 90
#define GO_TIME 1400
#define GO_TURN_TIME 1600

// Steering
#define CENTER_ST 90
#define TURN 25
#define SMOOTH_FACT 100
#define RIGHT 1
#define LEFT -1

// Radar function constants
#define ECHO 10
#define TRIGGER 11
#define MIN_ANGLE 45
#define MAX_ANGLE 135
#define MIN_DIS 40

// Sensor function constants
#define INIT_DL 2
#define WAIT_DL 50
#define PRT_DL 1000
#define NORM_FACT 60

// Steer function constants
#define CENTER_ST 103
#define TURN_DIR_TIME 1000

// THETA
#define MIN_THETA 0
#define MID_THETA 45
#define MAX_THETA 90

//LIMITER
#define ON 1
#define OFF 0

//PATH PLANNING
#define SIZE 10

#define ST_X 8
#define ST_Y 1
#define TRG_X 2
#define TRG_Y 8
#define MIN_TH 0
#define MAX_TH 90
#define CHEAT 200

// Checkpoint
#define CHECK_1 1
#define CHECK_2 2
#define CHECK_3 3



//STRUCTURES
typedef struct p{
	float x;
	float y;
	float th;
}point;
//typedef p point;

typedef struct sq{
	point p;
	float g, h, f;
}cell;
//typedef node square;

typedef struct mystruct{
	int a;
	int b;
}str;


int obstacle_rec[90];

// Vehicle's variables
Servo sensor_servo, speed_servo, steer_servo;
point vcl, checkpoint_1, checkpoint_2, checkpoint_3;

//FUNCTIONS PROTOTYPES

/*Init_chk_pnts: initialize checkpoints*/
void init_chk_pnts();

/*Checkpoint function is used to check if the vehicle follows
the map in the real world.*/
void checkpoint(int, int, int, int);

/*Chk_pnt_1: function for the first checkpoint*/
int chk_pnt_1(int, int);

/*Chk_pnt_2: function for the first checkpoint*/
int chk_pnt_2(int, int, int);

/*Chk_pnt_1: function for the first checkpoint*/
void chk_pnt_3();

/*Alter: this function is used when vehicle loose the path.*/
void alter(int, int);

/*D function is called when the given instruction is 'd'.*/
void d();

/*W function is called when the given instruction is 'w'.*/
void w();

/*Check_distance function is used to count the distance of 
the sensor given a specified theta for the servo of sensor.*/
float check_distance(int, int, int);

/*Relax: this function is used to detach the servo motors of
the vehicle*/
void relax();

/*Vehicle: this is the main function of the project that com-
bines all the moves to make the vehicle to reach the target 
point of the map.*/
void vehicle();

/*Initial: this function initializes the state of every element
of the autonomous vehicle*/
void initial();

/*Print_obsacle: prints the elements of obstacle_rec array.*/
void print_obstacle();

/*Limiter function is used to prevet vehicle to turn more than
some special values of theta.*/
int limiter(int);

/*Init_crds: this function initializes the coordinates x, y, th 
of the vehicle.*/
void init_crds();

/*Go function moves the vehicle frontwards or backwards. If the
current position of the vehicle is (x, y, th), the new will be 
(x, y+1, th) or (x+1, y, th) or (x-1, y, th)...*/
void go(int, int);

/*Steer function is used to turn the front wheels of the vehicle.*/
void steer(int);

/*Center_steer function is used to return front wheels to the init-
ial state.*/
void center_steer(int);

/*Go_diag function: makes the vehicle to follow a diagonal route.
Rightwards or leftwards.*/
void go_diag(int, int, int);

/*Update_crds: this function updates the coordinates of the vehicle
depending on movements of the car.*/
void update_crds(int, int);

/*Update_aux: is an auxiliary function that updates vehicle's 
coordinates when it goes straight frontwards or backwards.*/
void update_aux(int);

/*Update_aux_dir: is an auxiliary function that updates vehicle's 
coordinates when it makes diagonal movements.*/
void update_aux_dir(int, int);

/*Radar function: turns the sensor's servo rightwards and left-
wards. If an obstacle is close enough to the sensor, then sensor's
servo will stop and its theta wiil be saved.*/
void radar(int, int);

/*Sensor_func function computes the distance from sensor's info.
The sensor is defined by echo_pin and trig_pin variables.*/
float sensor(int, int);
