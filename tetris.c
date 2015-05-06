#include "tetromino.h"
#include "switches.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h> 

#define LED_ON      PORTB |=  _BV(PINB7)
#define LED_OFF     PORTB &= ~_BV(PINB7) 
#define LED_TOGGLE  PINB  |=  _BV(PINB7)

#define DEBUG 0

#define START_X 3
#define START_Y 0

volatile uint16_t grid [GRID_WIDTH][GRID_HEIGHT];

volatile int at_bottom = 0;

volatile int loop = 1;
volatile int movable = 1;
volatile int lines = 0;
volatile int level = 0;
volatile int score = 0;

#define MAX_LEVEL 31

int base_score[4] = {40,100,300,1200};

volatile tetromino current_tetromino, last_tetromino;

tetromino block_list[7] = {{O,START_X,START_Y,0},{I,START_X,START_Y,0},{T,START_X,START_Y,0},{J,START_X,START_Y,0},{L,START_X,START_Y,0},{S,START_X,START_Y,0},{Z,START_X,START_Y,0}};
volatile int bag[7];
volatile int blocks_taken = 7;

typedef enum {Up,Down,Left,Right} direction;


void redraw_tetromino(){
	cli();
	clear_tetromino(last_tetromino);
	display_tetromino(current_tetromino);
	sei();
}

void show_grid(){
	int ypos = 60;
	
	int i, j = 0;
	for ( i = 0; i < GRID_HEIGHT; i++ ){
		display_string_xy("",SIDEBAR_START+10,ypos);
		for ( j = 0; j < GRID_WIDTH; j++ ){

			if(grid[j][i]) {display_string("X");}
			else {display_string("O");}
		}
		ypos += 10;
	}
}

void clear_area(){
	rectangle clear = {0,GRID_WIDTH*BLOCK_SIZE,0,GRID_HEIGHT*BLOCK_SIZE};
	fill_rectangle(clear,BLACK);
}

void clear_field(){
	int i, j = 0;
	for ( i = 0; i < GRID_WIDTH; i++ ){
		for ( j = 0; j < GRID_HEIGHT; j++ ){
			grid[i][j] = 0;
		}
	}
}

void redraw(){
	clear_area();
	char points[15];
	sprintf(points, "Lines: %d", lines);
	display_string_xy(points,SIDEBAR_START+10,20);
	sprintf(points, "Level: %d", level);
	display_string_xy(points,SIDEBAR_START+10,30);
	sprintf(points, "Score: %d", score);
	display_string_xy(points,SIDEBAR_START+10,40);
	int i, j = 0;
	for ( i = 0; i < GRID_WIDTH; i++ ){
		for ( j = 0; j < GRID_HEIGHT; j++ ){
			if (grid[i][j]) display_block(i*BLOCK_SIZE,j*BLOCK_SIZE,grid[i][j]);
		}
	}
}

int check_line(int line){
	int j = 0;
	for ( j = 0; j < GRID_WIDTH; j++ ){
		if (!(grid[j][line])) { return 0; }
	}
	return 1;
}

void clear_lines(){
	
	int i, j, x, changed = 0, count = 0;
	for ( x = 0; x < GRID_HEIGHT; x++ ){
		if(check_line(x)){
			count++;
			changed = 1;
			for ( i = 0; i < GRID_WIDTH; i++ ){
				for (j = x-1; j >= 0; j-- ){
					grid[i][j+1] = grid[i][j];
				}
			}
		}
	}
	lines += count;
	level = div(lines,10).quot;
	score += base_score[count-1] * (level+1);
	if (count && (level > 0) && (level < MAX_LEVEL)) OCR3A -= 500;
	if (changed) redraw();
	
}

int check_collision(tetromino block){
	int i, j = 0;
	for ( i = 0; i < GRID_WIDTH; i++ ){
		for ( j = 0; j < GRID_HEIGHT; j++ ){
			if ((i >= block.x)&&(i < block.x+4)){
				if ((j >= block.y)&&(j < block.y+4)){ 
					if (grid[i][j] && block_grid[i-block.x][j-block.y]) return 0;
				} 
			}
		}
	}
	return 1;
}

void store_block(tetromino block){
	int i, j = 0;
	for ( i = 0; i < GRID_WIDTH; i++ ){
		for ( j = 0; j < GRID_HEIGHT; j++ ){
			if ((i >= block.x)&&(i < block.x+4)){
				if ((j >= block.y)&&(j < block.y+4)){ 
					if(block_grid[i-block.x][j-block.y]) grid[i][j] = block.type;
				}
			} 
		}
	}
	clear_lines();
}

void reset_bag(){
	int i;
	blocks_taken = 0;
	for (i = 0; i < 7; i++ ){
		bag[i] = 1;
	}
}

int random_block_number(){
	int r = rand() % 7;
	return r;
}

int spawn_block(){
	at_bottom = 0;
	tetromino new_tetromino;	
	if (blocks_taken == 7) { reset_bag(); };
	int rand_num;
	do {
		rand_num = random_block_number();
	} while (!bag[rand_num]);
	


	bag[rand_num] = 0;
	blocks_taken++;
	new_tetromino = block_list[rand_num];

	adjust_virtual_grid(new_tetromino.type,new_tetromino.angle);
	update_block_grid();
	if(check_collision(new_tetromino)) {last_tetromino = current_tetromino = new_tetromino; return 1;}
	else { loop = 0; cli(); return 0;}
}

int rotate_tetromino(){
	tetromino new_tetromino = current_tetromino;
	last_tetromino = current_tetromino;
	if (new_tetromino.angle == 3) 
		new_tetromino.angle = 0;
	else new_tetromino.angle += 1;
	adjust_virtual_grid(new_tetromino.type,new_tetromino.angle);
	
	if ((new_tetromino.y + bottommost_virtual_block()) > GRID_HEIGHT) return 0;
	if ((new_tetromino.x + leftmost_virtual_block()) < 0) return 0; 
	if ((new_tetromino.x + rightmost_virtual_block()) > GRID_WIDTH-1) return 0;

	if (!check_collision(new_tetromino)) return 0;
	
	current_tetromino = new_tetromino; 
	redraw_tetromino();
	return 1;
}

void move_tetromino(direction movement){
	tetromino new_tetromino;
	new_tetromino = current_tetromino;
	last_tetromino = current_tetromino;
	switch (movement){
		case Up:
			new_tetromino.y -= 1;
			break;
		case Down:
			if ((current_tetromino.y + bottommost_block(block_grid)) < GRID_HEIGHT-1){ 
				new_tetromino.y += 1;
			} else {
				at_bottom = 1;
			}
			break;
		case Left:
			if ((current_tetromino.x + leftmost_block(block_grid)) > 0){ 
				new_tetromino.x -= 1;
			} else {
				
			}
			break;
		case Right:
			if ((current_tetromino.x + rightmost_block(block_grid)) < GRID_WIDTH-1){ 
				new_tetromino.x += 1;
			} else {
				
			}
			break;
	}
	if (check_collision(new_tetromino)){
		current_tetromino = new_tetromino;
	} else {
		if (movement == Down) at_bottom = 1;
	}
	redraw_tetromino();
}

void draw_shape_alternate(rectangle shape, int counter){
	if (counter % 2) {
		fill_rectangle(shape,RED);
	} else {
		fill_rectangle(shape,YELLOW_4);
		shape.left += BORDER_SIZE;
		shape.right -= BORDER_SIZE;
		shape.top += BORDER_SIZE;
		shape.bottom -= BORDER_SIZE;
		fill_rectangle(shape,YELLOW_1);
	}
}

void reset(){
	at_bottom = 0;
	loop = 1;
	movable = 1;
	lines = 0;
	level = 0;
	score = 0;
	blocks_taken = 7;
	reset_bag();
	clear_field();
	clear_area();
}

ISR(TIMER1_COMPA_vect)
{
	if (center_pressed()){
		rotate_tetromino();
	}
	if(left_pressed()){
		move_tetromino(Left);
	}
	if(right_pressed()){
		move_tetromino(Right);
	}
	if(up_pressed()){
		//move_tetromino(Up);
	}
	if(down_pressed()){
		//move_tetromino(Down);
	}
	if(down_held()){
		move_tetromino(Down);
	}
}

ISR(TIMER3_COMPA_vect)
{
	if (DEBUG){
		show_grid();
		show_block_grid();
	}
	if (!at_bottom){
		move_tetromino(Down);
		redraw_tetromino();
	} else {
		tetromino new_tetromino = current_tetromino;
		new_tetromino.y += 1;
		if (((new_tetromino.y + bottommost_block(block_grid)) == GRID_HEIGHT) || !check_collision(new_tetromino)){
			store_block(current_tetromino);
			spawn_block();
		} else {
			move_tetromino(Down);
		}

	}
}

int main()
{
	
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;
	init_lcd();
	init_switches();
	set_frame_rate_hz(61);
	set_orientation(North);
	
	DDRB |= _BV(PB7);
	PORTB &= ~_BV(PB7);

	/* enable button press inturrupt */
	TCCR1A = 0;
	TCCR1B = _BV(WGM12);
	TCCR1B |= _BV(CS10);
	TIMSK1 |= _BV(OCIE1A);

	OCR3A = 0;

	/*timer for random seed */
	TCCR2B |= (1 << CS10);

	/* timer for block falling speed*/
	TCCR3A = 0;
	TCCR3B = _BV(WGM32);
	TCCR3B |= _BV(CS32);
	TIMSK3 |= _BV(OCIE3A);
	
	OCR3A = 20000;
	
	//display_string_xy("Press Center to Start",60,30);
	display_string_xy("\n",0,0);
	display_string("   _____ ____ _____ _____ _____ ____\n");
	display_string("  |_   _|  __|_   _|  _  |_   _| ___|\n");
	display_string("    | | | |__  | | | |_| | | | \\ \\\n");
	display_string("    | | |  __| | | | ,  _| | |  \\ \\\n");
	display_string("    | | | |__  | | | |\\ \\ _| |_ _\\ \\\n");
	display_string("    |_| |____| |_| |_| \\_\\_____|____|\n");
	display_string("\n          Press Center to Start");
	
	do{
		while(!center_pressed()){}
		reset();
		rectangle background = {0,display.width,0,display.height};
		display.background = GREY_0;
		display.foreground = BLACK;
		fill_rectangle(background,display.background);

		redraw();

		srand(TCNT2);
		spawn_block();
		OCR1A = 65535;
		LED_ON;
		sei();
		while(loop);
		cli();
		LED_OFF;
		display_string_xy("Game Over",SIDEBAR_START+10,10); 
		display.background = BLACK;
		display.foreground = WHITE;
		display_string_xy("Press Center to Restart",0,10);
	} while (1);

	return -1;
}