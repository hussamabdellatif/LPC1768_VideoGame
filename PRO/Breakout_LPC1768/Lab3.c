#include "LPC17xx.H"
#include "GLCD.h"
#include "GLCD_UTILS.h"
#include "stdlib.h"
#include "stdio.h"
#include <math.h>



void square(int x, int y){
GLCD_PutPixel(x,y);
}

void circle(float x, float y){
GLCD_PutPixel(x,y);
}


void delay(int count) {
	int i;
	for (i = 0; i < count; i++); //Just count for delay
}
void erase_paddle(int cx, int cy, int width){
	int i;
	int j;
	for(i=(cx-(width/2));i<=(cx+(width/2));i++){
		for(j=cy;j<=230;j++){
				GLCD_SetTextColor(Black);
				square(i,j);

		}
	}

}
void draw_circle(int cx, int cy, int radius){
	GLCD_SetTextColor(Yellow);
	GLCD_draw_circle( cx, cy, radius);
}
void erase_circle(int cx, int cy, int radius){
	GLCD_SetTextColor(Black);
	GLCD_draw_circle( cx, cy, radius);
}

void draw_paddle(int cx, int cy, int width, int height){
	int i;
	int j;
	for(i=(cx-(width/2));i<=(cx+(width/2));i++){
		for(j=cy;j<=230;j++){
				GLCD_SetTextColor(Yellow);
				square(i,j);
		}
	}
}

void erase_block(int cx, int cy, int width, int height){
	short i;
	short j;

	GLCD_SetTextColor(Black);
	for(i=cx;i<= cx+width;i++){
				for(j=cy;j<=(cy+height);j++){
					if(i == cx || i == cx+width || j==cy || j==cy+height){
					GLCD_SetTextColor(Black);
					square(i,j);
					}else{
					GLCD_SetTextColor(Black);
					square(i,j);
					}
				}
			}

}

void draw(int cx, int cy, int width, unsigned char color, int height, int iter){


	short i;
	short j;
	int colors[] = {Green, Green, Orange, Orange, Yellow, Yellow};
	GLCD_SetTextColor(color);
	for(i=cx;i<= cx+width;i++){
				for(j=cy;j<=(cy+height);j++){
					if(i == cx || i == cx+width || j==cy || j==cy+height){
					GLCD_SetTextColor(color);
					square(i,j);
					}else{
					GLCD_SetTextColor(colors[iter]);
					square(i,j);
					}
				}
			}
}





int main() {
		int num_block2s = 96;
		int paddle_x =320/2;
		int paddle_cy = 220;
		int score = 0;
		int paddle_height = 10;
		int z;
		int r=0;
	int i;
		int loc;
		int d;
		int rec_x;
		int rec_y;
		short ball_x = 320/2;
		short ball_y = 240/2;
		short ball_r = 4 ;
		int ball_vx = 3;
		int ball_vy =2 ;
		int counter;
		char x;
		int counter2;
		int game_notdone = 0;
		int game_inital = 1;
		int num_lives = 3;
		char* lives;
		int wait_up = 1;
		char num;

		int pin = 0x800;
int paddle_width = 60;
		short bxr[96];
		short byr[96];
		GLCD_Init();               //Initializes the LCD display
    GLCD_Clear(Black);         //Clear display and set background color to black
    GLCD_SetTextColor(Blue);   //Pixels will be drawn in blue
		LPC_GPIO2->FIODIR = 0x000000FF;

		//display_lives(3);


		for( z=0; z<=5;z++){
  //Pixels will be drawn in a certain color;
			for( d=0;d<16;d++){
				loc = (16*z)+d;
				if(loc<=95){
				bxr[loc] = (d*20);
				byr[loc] = ((z+1)*10);
				draw(bxr[loc] ,byr[loc], 20, Blue,10,z);
				}
			}
		}
			draw_paddle(paddle_x, paddle_cy, 60, paddle_height);


		//ball;
		draw_circle(ball_x, ball_y, ball_r);


		r=0;
    while((game_inital || game_notdone) == 1) {

			while(wait_up){
				if(((LPC_GPIO1->FIOPIN & 1<<27) ==0) ){
						wait_up = 0;
				}
			}
			if((LPC_GPIO1->FIOPIN & 1<<28) ==0)
			while(1){
				if((LPC_GPIO1->FIOPIN & 1<<28) ==1){
					break;
				}
			}

			//int i;//An infinite loop is needed or else the program will just exit

			if(((LPC_GPIO1->FIOPIN & 1<<29) ==0) && (paddle_x + paddle_width/2 <= 305 ) ){

				erase_paddle(paddle_x, paddle_cy, paddle_width);
				paddle_x = paddle_x +5 ;
				draw_paddle(paddle_x, paddle_cy,paddle_width, paddle_height);

			}
			if(((LPC_GPIO1->FIOPIN & 1<<26) ==0) && (paddle_x- paddle_width/2 >= 0 )){
					erase_paddle(paddle_x, paddle_cy, paddle_width);
					paddle_x = paddle_x - 5;
					draw_paddle(paddle_x, paddle_cy, paddle_width, paddle_height);


			}
			erase_circle(ball_x,ball_y, ball_r);
			if(ball_x + ball_r > 310){
					ball_vx = -1 * ball_vx;
			}
			if(ball_x + ball_r < 3){
				ball_vx = -1 * ball_vx;
			}
			if (ball_y + ball_r==0){
				ball_vy = -1 * ball_vy;
			}

			if(ball_y == paddle_cy  && (ball_x >= paddle_x - paddle_width/2  &&  ball_x  <= paddle_x+ paddle_width/2 )){

					ball_vy = -1 * ball_vy;



			}







			for(counter= 0;counter<95;counter++){

				if((ball_x + r >= bxr[counter] && ball_x + r <= bxr[counter] + 20) && (ball_y + r >= byr[counter] && ball_y + r <= byr[counter] +10)){
				if(counter % 5){
				score = score +1;
				}

				erase_block(bxr[counter], byr[counter], 20,10);
					ball_vy  = -1 * ball_vy;
					erase_block(bxr[counter], byr[counter], 20,10);
					bxr[counter] = 0;
					byr[counter] = 0;
					num_block2s--;



					break;
				}

			}
			for(counter2 =0 ; counter2<96;counter2++){

				if(bxr[counter2] != 0 || byr[counter2] != 0){
					game_notdone =1;
					break;
				}
			}
			//change to another value when you want to end the game faster
			if(num_block2s == 96){
					GLCD_Init();               //Initializes the LCD display
					GLCD_Clear(Black);         //Clear display and set background color to black
					GLCD_SetTextColor(Blue);   //Pixels will be drawn in blue
					GLCD_DisplayString(5,5,"You Win");
					break;
			}
				ball_x = ball_x + ball_vx;
			ball_y = ball_y + ball_vy;
			draw_circle(ball_x, ball_y, ball_r);
			delay(700000);
			game_inital = 0;






			if(ball_y  > (paddle_cy)){
				if(num_lives == 1){
					GLCD_Clear(Black);
				GLCD_DisplayString(5,5,"You Lose");
					break;
				}
				num_lives--;
				wait_up = 1;
				erase_circle(ball_x,ball_y, ball_r);
				ball_x = 320/2;
				ball_y = 240/2;

			}

			if(paddle_x >= 150){
			GLCD_SetBackColor(Black);
			GLCD_DisplayString(9,0,"lives");
			 x = num_lives +'0';
				GLCD_DisplayChar(9,5,x);
				GLCD_DisplayString(7,0,"Score:");
				GLCD_DisplayChar(7,7,(score + '0' ));
			}
			/*
			}else{
				GLCD_ClearLn(9);
				erase_paddle(paddle_x, paddle_cy, 60);
				draw_paddle(paddle_x, paddle_cy,60, paddle_height);
			}
			*/
		}



}
