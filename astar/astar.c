//Astar implemantation

#include <stdio.h>
#include <math.h>


/********************************************************************************/

#define SIZE 10

#define ST_X 8
#define ST_Y 1
#define TRG_X 2
#define TRG_Y 8
#define MIN_TH 0
#define MAX_TH 90
#define CHEAT 200

/********************************************************************************/

typedef struct p{
	float x;
	float y;
	float th;
}point;

typedef struct node{
	point p;
	float g, h, f;
}square;

/********************************************************************************/

point set_point(float, float, float);
float distance(float, float, float, float);
float minimum(float, float, float, float, float, 
					float, float, float);
/********************************************************************************/


int main()
{
	float dis = distance(ST_X, ST_Y, TRG_X, TRG_Y);
	printf("Distance: %f\n", dis); 
	printf("\n");

	int i, j;
	
	point start_point, target_point, cur_point;
	start_point = set_point(ST_X, ST_Y, MIN_TH);
	target_point = set_point(TRG_X, TRG_Y, MAX_TH);

	square map_elem[SIZE][SIZE];
	
	float x1, y1, x2, y2, x3, y3;

	char map[SIZE][SIZE] = {
	        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
	        {'x', '0', '0', '0', '0', '0', '0', '0', '0', 'x'},
	        {'x', '0', '0', '0', '0', '0', '0', '0', '.', 'x'},
	        {'x', '0', '0', 'x', 'x', 'x', 'x', '0', '0', 'x'},
	        {'x', '0', '0', 'x', 'x', 'x', 'x', '0', '0', 'x'},
	        {'x', '0', '0', 'x', 'x', 'x', 'x', '0', '0', 'x'},
	        {'x', '0', '0', 'x', 'x', 'x', 'x', '0', '0', 'x'},
	        {'x', '0', '0', '0', '0', '0', '0', '0', '0', 'x'},
	        {'x', '.', '0', '0', '0', '0', '0', '0', '0', 'x'},
		{'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}
	};



	for (i=0; i<SIZE; i++){
		for (j=0; j<SIZE; j++){
			map_elem[i][j].p.x = i;
			map_elem[i][j].p.y = j;

			x1 = start_point.x;
			y1 = start_point.y;

			x2 = map_elem[i][j].p.x;
			y2 = map_elem[i][j].p.y;

			x3 = target_point.x;
			y3 = target_point.y;

			if ((i == 0) || (i == SIZE-1)){
				map_elem[i][j].g = 100;
				map_elem[i][j].h = 100;
			}
			else if (((i>2) && (i<7)) && ((j>2) && (j<7))){
				map_elem[i][j].g = 100;
                                map_elem[i][j].h = 100;
			}
			else if((j == 0) || (j == SIZE-1)){
				map_elem[i][j].g = 100;
                                map_elem[i][j].h = 100;
			}
			else{
				map_elem[i][j].g = distance(x1, y1, x2, y2);
				map_elem[i][j].h = distance(x2, y2, x3, y3);
			}
			map_elem[i][j].f = map_elem[i][j].g + map_elem[i][j].h;
		}
	}
	

	
	printf("\n");
	for (i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			printf("Square: (%.2f, %.2f)\n", 
					map_elem[i][j].p.x, map_elem[i][j].p.y);
			printf("h(n): %.2f\n", map_elem[i][j].h);
			printf("g(n): %.2f\n", map_elem[i][j].g);
			printf("f(n): %.2f\n", map_elem[i][j].f);
			printf("\n");
		}
		printf("\n");
	}

	for (i=0; i<SIZE; i++){
                for(j=0; j<SIZE; j++){
			if (map_elem[i][j].f < 10){
				printf(" %.2f_+", map_elem[i][j].f);
			}
			else if (map_elem[i][j].f > 100){
				printf("%.2f+", map_elem[i][j].f);
			}
			else{
                        	printf(" %.2f+", map_elem[i][j].f);
			}
                }
                printf("\n");
        }

	printf("\n");


	
	for (i=0; i<10; i++){
		for (j=0; j<10; j++){
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	
	point old;
	old.x = 0;
	old.y = 0;
	
	int old_x, old_y;
	
	float min;
	//printf("MINIMUM: %.2f\n\n", min1); 
	int cur_x, cur_y;
	float lf, f, rf, l, r, lb, b, rb;
	cur_point = start_point;
	cur_x = (int) cur_point.x;
	cur_y = (int) cur_point.y;
	old_x = (int) old.x;
	old_y = (int) old.y;

	while(map_elem[cur_x][cur_y].h != 0){
		
		map[cur_x][cur_y] = '.';
		
		printf("Point: (%d, %d)\t", cur_x, cur_y);
		printf("Old: (%d, %d)\n", old_x, old_y);
 
		//cur_x = (int) cur_point.x;
		//cur_y = (int) cur_point.y;
		
		lf = map_elem[cur_x-1][cur_y-1].f;
		f = map_elem[cur_x-1][cur_y].f;
		rf = map_elem[cur_x-1][cur_y+1].f;
		l = map_elem[cur_x][cur_y-1].f;
		r = map_elem[cur_x][cur_y+1].f;
		lb = map_elem[cur_x+1][cur_y-1].f;
		b = map_elem[cur_x+1][cur_y].f;
		rb = map_elem[cur_x+1][cur_y+1].f;
		
		min = minimum(CHEAT, f, CHEAT, l, r, CHEAT, CHEAT, CHEAT);
		
		old.x = cur_point.x;
		old.y = cur_point.y;

		old_x = (int) old.x;
		old_y = (int) old.y;

		if (min == lf){
			//if (cur_point.th == MAX_TH){
				cur_point.x = cur_point.x-1;
				cur_point.y = cur_point.y-1;
				//map[cur_x][cur_y] = 'q';
			//}
		}
		else if (min == f){
			//if (cur_point.th == MIN_TH){
				cur_point.x = cur_point.x-1;
				cur_point.y = cur_point.y;
				//map[cur_x][cur_y] = 'w';
			//}	
		}
		else if (min == rf){
			//if (cur_point.th == MIN_TH){
				cur_point.x = cur_point.x-1;
				cur_point.y = cur_point.y+1;
				//map[cur_x][cur_y] = 'e';
			//}
		}
		else if (min == l){
			cur_point.x = cur_point.x;
			cur_point.y = cur_point.y-1;
			//map[cur_x][cur_y] = 'a';
		}
		else if (min == r){
			cur_point.x = cur_point.x;
			cur_point.y = cur_point.y+1;
			//map[cur_x][cur_y] = 'd';
		}
		/*else if (min == lb){
			cur_point.x = cur_point.x+1;
			cur_point.y = cur_point.y-1;
			map[cur_x][cur_y] = 'z';
		}
		else if (min == b){
			cur_point.x = cur_point.x+1;
			cur_point.y = cur_point.y;
			map[cur_x][cur_y] = 'x';
		}
		else if (min == rb){
			cur_point.x = cur_point.x+1;
			cur_point.y = cur_point.y+1;
			map[cur_x][cur_y] = 'c';
		}*/
		
		map_elem[old_x][old_y].f = CHEAT;
		
		cur_x = (int) cur_point.x;
		cur_y = (int) cur_point.y;
	}
	
	printf("\n");
	
	for (i=0; i<10; i++){
		for (j=0; j<10; j++){
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	return 0;
}

/********************************************************************************/

point set_point(float x_val, float y_val, float th_val)
{
	point p;
	p.x = x_val;
	p.y = y_val;
	p.th = th_val;
	return p;
}

/********************************************************************************/

float distance(float x1, float y1, float x2, float y2)
{
	float dis, dis_1, dis_2;
	dis_1 = pow((x1-x2),2);
	dis_2 = pow((y1-y2),2);
	dis = dis_1 + dis_2;
	printf("\n");
	printf("Dis_1: %.2f Dis_2: %.2f Dis: %.2f\n", dis_1, dis_2, dis);
	dis = sqrt(dis);
	return dis;
}


/********************************************************************************/

float minimum(float lf, float f, float rf, float l, float r, 
					float lb, float b, float rb)
{
	float min;
	min = lf;
	if (f < min){
		min = f;
	}
	if (rf < min){
		min = rf;
	}
	if (l < min){
		min = l;
	}
	if (r < min){
		min = r;
	}
	if (lb < min){
		min = lb;
	}
	if (b < min){
		min = b;
	}
	if (rb < min){
		min = rb;
	}
	return min;
}  

