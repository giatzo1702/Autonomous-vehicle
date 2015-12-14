/*
+-----------------------------+
| Date: 06/02/2013            |
| Author: Giannis Tzortzis    |
| Project: Autonomous Vehicle |
| Course: Autonomous Agents   |
+-----------------------------+
*/

#include <Servo.h>
#include <math.h>
#include "defines.h"



void setup()
{
	Serial.begin(9600); 
	
	speed_servo.attach(8);
	sensor_servo.attach(9);
	steer_servo.attach(7);
	
	motion_test();
	
	initial();
	
	print_crds();
	
	vehicle();
	
	relax();
	
}

void loop()
{}

/*Motion_test function is used for the testing of some basic
motions of the vehicle before it starts.*/
void motion_test()
{
	Serial.println("Speed servo: Testing...");
	delay(1000);
	speed_servo.write(CENTER);
	delay(1000);
	speed_servo.write(CENTER-SPEED);
	delay(1000);
	speed_servo.write(CENTER);
	delay(1000);
	
	Serial.println("Steer servo: Testing...");
	delay(1000);
	steer_servo.write(CENTER_ST);
	delay(1000);
	steer_servo.write(CENTER_ST-TURN);
	delay(1000);
	steer_servo.write(CENTER_ST);
	delay(1000);
	steer_servo.write(CENTER_ST-TURN);
	delay(1000);
	steer_servo.write(CENTER_ST);
	delay(1000);
	
	Serial.println("Sensor servo: Testing...");
	delay(1000);
	sensor_servo.write(MIN_THETA);
	delay(1000);
	sensor_servo.write(MAX_ANGLE);
	delay(1000);
}

/*Check_distance function is used to count the distance of 
the sensor given a specified theta for the servo of sensor.*/
float check_distance(int echo, int trigger, int theta)
{
	float dis;
	sensor_servo.write(theta);
	delay(1000);
	dis = sensor(echo, trigger);
	return dis;
}


/*Relax: this function is used to detach the servo motors of
the vehicle*/
void relax()
{
	speed_servo.detach();
	delay(10);
	steer_servo.detach();
	delay(10);
	sensor_servo.detach();
	delay(10);
	Serial.println();
	Serial.println("Relaxing...");
}


/*Vehicle: this is the main function of the project that com-
bines all the moves to make the vehicle to reach the target 
point of the map.*/
void vehicle()
{
	int i, dir = 30;
	char instructions[10] = {'d', 'd', 'd', 
						'd', 'd', 'w','w', 'w', 'w', 'd'};
	
	for (i=0; i<10; i++){
		if (CHECK_PNT == ON){
			if ((vcl.x == checkpoint_1.x) && 
							(vcl.y == checkpoint_1.y)){
				checkpoint(CHECK_1, ECHO, TRIGGER);
			}
			
			if ((vcl.x == checkpoint_2.x) && 
							(vcl.y == checkpoint_2.y)){
				checkpoint(CHECK_2, ECHO, TRIGGER);
			}
			
			if ((vcl.x == checkpoint_3.x) && 
							(vcl.y == checkpoint_3.y)){
				checkpoint(CHECK_3, ECHO, TRIGGER);
			}
		}
		
		if (instructions[i] == 'd'){
			d(SPEED, dir);
		}
		else{
			w(SPEED, dir);
		}
		delay(100);
	}
}

/*Init_chk_pnts: initialize checkpoints*/
void init_chk_pnts()
{
	checkpoint_1.x = 7;//checkpoint_1: (7, 5)
	checkpoint_1.y = 4;
	checkpoint_2.x = 7;//checkpoint_2: (7, 6)
	checkpoint_2.y = 6;
	checkpoint_3.x = 5;//checkpoint_3: (5, 7)
	checkpoint_3.y = 7;
}

/*Checkpoint function is used to check if the vehicle follows
the map in the real world.*/
void checkpoint(int chk_point, int echo, int trig)
{
	int check_1, check_2;
	if (chk_point == CHECK_1){
		Serial.println("Checkpoint1: (7, 4)");
		check_1 = chk_pnt_1(echo, trig);
		if (check_1 == 1){ //Everything is ok
			return;
		}
		else{
			relax();
		}
	}
	else if (chk_point == CHECK_2){
		Serial.println("Checkpoint2: (7, 6)");
		check_2 = chk_pnt_2(echo, trig);
		if (check_2 == 1){ //Everything is ok
			return;
		}
		else{
			relax();
		}
	}
	else{
		Serial.println("Checkpoint3: (5, 7)");
		check_1 = chk_pnt_1(echo, trig);
		if (check_1 == 1){ //Everything is ok
			return;
		}
		else{
			relax();
		}
	}
}

/*Chk_pnt_1: function for the first checkpoint*/
int chk_pnt_1(int echo, int trig)
{
	int dis_1, dis_2;
	sensor_servo.write(0);
	delay(1000);
	dis_1 = sensor(echo, trig);
	sensor_servo.write(178);
	delay(2000);
	dis_2 = sensor(echo, trig);
	if ((dis_1 <= MIN_DIS) && (dis_2 <= MIN_DIS)){
		return 1;
	}
	if (dis_2 >= MIN_DIS){
		alter(echo, trig);
		//vcl.x = checkpoint_2.x;
		//vcl.y = checkpoint_2.y;
		//return 1;
	}
	return 0;
}

/*Chk_pnt_2: function for the first checkpoint*/
int chk_pnt_2(int echo, int trig)
{
	int dis_1, dis_2;
	sensor_servo.write(0);
	delay(1000);
	dis_1 = sensor(echo, trig);
	sensor_servo.write(178);
	delay(1000);
	dis_2 = sensor(echo, trig);
	if ((dis_1 <= MIN_DIS) && (dis_2 >= MIN_DIS)){
		return 1;
	}
	alter(echo, trig);
	//return 1;
}

/*Alter: this function is used when vehicle loose the path.*/
void alter(int echo, int trig)
{
	Serial.println("Alternative");
	sensor_servo.write(180);
	delay(1000);
	while (sensor(echo, trig) <= MIN_DIS){
		go(SPEED, ON, GO_TIME);
	}
	//vcl.x = checkpoint_2.x;
	//vcl.y = checkpoint_2.y;
	w(SPEED, 30);
	w(SPEED, 30);
	w(SPEED, 30);
	w(SPEED, 30);
	d(SPEED, 30);
	exit(0);
}

/*D function is called when the given instruction is 'd'.*/
void d(int speed, int dir)
{
	if (vcl.th == MIN_THETA){
		Serial.println("up, right");
		delay(2000);
		go_diag(dir, SPEED, GO_TURN_TIME);
		delay(100);
		print_crds();
	}
	else{
		Serial.println("right");
		delay(2000);
		go(SPEED, ON, GO_TIME);
		delay(100);
		print_crds();
	}
}
	
/*W function is called when the given instruction is 'w'.*/
void w(int speed, int dir)
{
	if (vcl.th == MIN_THETA){
		Serial.println("up");
		delay(2000);
		go(SPEED, ON, GO_TIME);
		delay(100);	
		print_crds();
	}
	else{
		Serial.println("up, left");
		delay(2000);
		go_diag(-dir, SPEED, GO_TURN_TIME);
		delay(100);
		print_crds();
	}
}

/*Initial: this function initializes the state of every element
of the autonomous vehicle*/
void initial()
{
	speed_servo.write(CENTER);
	delay(1000);
	sensor_servo.write(CENTER);
	delay(1000);
	steer_servo.write(CENTER_ST);
	delay(1000);
	pinMode(TRIGGER, OUTPUT);
	pinMode(ECHO, INPUT);
	init_crds();
	init_chk_pnts();
}
	

/*Print_obsacle: prints the elements of obstacle_rec array.*/
void print_obstacle()
{
	for (int j=0; j<90; j++){
		Serial.print(obstacle_rec[j]);
		if (j == 29){
			Serial.print("\t");
		}
		if (j == 59){
			Serial.print("\t");
		}
		delay(10);
	}
}

/*Limiter function is used to prevet vehicle to turn more than
some special values of theta.*/
int limiter(int dir)
{
	int limit = OFF;
	if (dir > 0){
		if (vcl.th == 180){
			limit = ON;
		}
	}
	else{
		if (vcl.th == -180){
			limit = OFF;
		}
	}
	return limit;
}

/*Init_crds: this function initializes the coordinates x, y, th 
of the vehicle.*/
void init_crds()
{
	vcl.x = 8;
	vcl.y = 1;
	vcl.th = MIN_THETA;
}

/*Print_crds: this function prints the courdinates x, y, th of 
the vehicle*/
void print_crds()
{
	Serial.println("Coordinates:");
	delay(1000);
	Serial.print("x =");
	delay(10);
	Serial.print(vcl.x);
	delay(10);
	Serial.print("\t");
	delay(10);
	Serial.print("y =");
	delay(10);
	Serial.print(vcl.y);
	delay(10);
	Serial.print("\t");
	delay(10);
	Serial.print("theta =");
	delay(10);
	Serial.println(vcl.th);
	delay(10);
	Serial.println();
}

/*Go function moves the vehicle frontwards or backwards. If the
current position of the vehicle is (x, y, th), the new will be 
(x, y+1, th) or (x+1, y, th) or (x-1, y, th)...*/
void go(int speed, int en_crds, int gotime)
{
	speed_servo.write(CENTER);
	delay(1000);
	speed_servo.write(CENTER + speed);
	delay(gotime);
	speed_servo.write(CENTER);
	delay(1000);
	if (en_crds == ON){
		update_crds(0, speed);
	}
}

/*Steer function is used to turn the front wheels of the vehicle.*/
void steer(int dir)
{
	steer_servo.write(90);
	delay(1000);
	if (dir > 0){
		steer_servo.write(CENTER_ST - (dir+10));
		delay(1000);
	}
	else{
		steer_servo.write(CENTER_ST - dir);
		delay(1000);
	}
}

/*Center_steer function is used to return front wheels to the init-
ial state.*/
void center_steer()
{
	steer_servo.write(90);
	delay(1000);
}

/*Go_diag function: makes the vehicle to follow a diagonal route.
Rightwards or leftwards.*/
void go_diag(int dir, int speed, int gotime)
{
	//if (limiter(dir) == ON){
	//	return;
	//}
	steer(dir);
	go(speed, OFF, gotime);
	center_steer();
	if (dir > 0){
		update_crds(1, speed);
	}
	else if (dir < 0){
		update_crds(-1, speed);
	}
	else{
		Serial.println("TO DIRECTION EINAI 0");
		delay(1000);
	}
}

/*Update_crds: this function updates the coordinates of the vehicle
depending on movements of the car.*/
void update_crds(int dir, int t_speed)
{
	//Serial.println(dir);
	if (dir == 0){
		update_aux(t_speed);
	}
	else{
		//Serial.println("Swstos");
		delay(1000);
		update_aux_dir(dir, t_speed);
	}
}

/*Update_aux: is an auxiliary function that updates vehicle's 
coordinates when it goes straight frontwards or backwards.*/
void update_aux(int t_speed)
{
	Serial.println("--------update_aux---------");
	if (vcl.th == MIN_THETA){
		vcl.x = vcl.x - 1;
	}
	else if (vcl.th == MAX_THETA){
		vcl.y = vcl.y + 1;
	}
}

/*Update_aux_dir: is an auxiliary function that updates vehicle's 
coordinates when it makes diagonal movements.*/
void update_aux_dir(int dir, int t_speed)
{
	Serial.println("------update_aux_dir-------");
	if (dir == 1){
		if (vcl.th == MIN_THETA){
			vcl.x = vcl.x - 1;
			vcl.y = vcl.y + 1;
			vcl.th = MAX_THETA;
		}
	}
	else if (dir == -1){
		//if (vcl.th == MAX_THETA){
			vcl.x = vcl.x - 1;
			vcl.y = vcl.y + 1;
			vcl.th = MIN_THETA;
		//}
	}
}

/*Radar function: turns the sensor's servo rightwards and left-
wards. If an obstacle is close enough to the sensor, then sensor's
servo will stop and its theta wiil be saved.*/
void radar(int echo, int trig)
{
	Serial.println("Radar function");
	int i;
	int y = 0;
	float dis;
	for (i=0; i<90; i++){
		obstacle_rec[i] = 0;
	}
	sensor_servo.write(MIN_ANGLE);
	delay(1000);
	for (i=MIN_ANGLE; i<MAX_ANGLE; i++){
		sensor_servo.write(i);
		dis = sensor(echo, trig);
		//Serial.println(dis);
		if (dis <= MIN_DIS){
			obstacle_rec[y] = 1;
		}  
		y++;
		delay(100);
	}
}  


/*Sensor_func function computes the distance from sensor's info.
The sensor is defined by echo_pin and trig_pin variables.*/
float sensor(int echo_pin, int trig_pin)
{
	//Serial.println("Sensor function");
	digitalWrite(trig_pin, LOW);
	delayMicroseconds(INIT_DL);
	digitalWrite(trig_pin, HIGH);
	delayMicroseconds(WAIT_DL);
	digitalWrite(trig_pin, LOW);
	float distance = pulseIn(echo_pin, HIGH);
	distance = distance/NORM_FACT;
	//Serial.print("Sensor:");
	//Serial.println(distance);
	//Serial.print("\t");
	return distance;
	//delay(PRT_DL);
}


