#include "tetromino.h"
#include <stdio.h>

void clear_grid(){
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		for ( j = 0; j < 4; j++ ){
			block_grid[i][j] = 0;
		}
	}
}

int leftmost_block(){
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		for ( j = 0; j < 4; j++ ){
			if (block_grid[i][j]) return i;
		}
	}
	return -1;
}

int rightmost_block(){
	int i, j = 4;
	for ( i = 3; i > -1; i-- ){
		for ( j = 3; j > -1; j-- ){
			if (block_grid[i][j]) return i;
		}
	}
	return -1;
}

int bottommost_block(){
	int i, j = 4;
	for ( i = 3; i > -1; i-- ){
		for ( j = 3; j > -1; j-- ){
			if (block_grid[j][i]) return i;
		}
	}
	return -1;
}

int leftmost_rot_block(){
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		for ( j = 0; j < 4; j++ ){
			if (rot_grid[i][j]) return i;
		}
	}
	return -1;
}

int rightmost_rot_block(){
	int i, j = 4;
	for ( i = 3; i > -1; i-- ){
		for ( j = 3; j > -1; j-- ){
			if (rot_grid[i][j]) return i;
		}
	}
	return -1;
}

int bottommost_rot_block(){
	int i, j = 4;
	for ( i = 3; i > -1; i-- ){
		for ( j = 3; j > -1; j-- ){
			if (rot_grid[j][i]) return i;
		}
	}
	return -1;
}

void show_block_grid(){
	char str[15];
	display_string_xy("",0,0);
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		for ( j = 0; j < 4; j++ ){
			sprintf(str,"%d",block_grid[i][j]);
			display_string(str);
		}
		display_string("\n");
	}
}

void display_sidebar(){
	rectangle shape = {SIDEBAR_START,LCDWIDTH,0,LCDHEIGHT};
	fill_rectangle(shape,GREY_0);
}

void display_block(uint16_t x, uint16_t y, uint16_t color){
	rectangle shape = {x+1,x+BLOCK_SIZE-1,y+1,y+BLOCK_SIZE-1};
	fill_rectangle(shape,color);
}

void rotated_grid(tetromino_type piece, uint16_t angle){
	//int rot_grid[4][4];
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		for ( j = 0; j < 4; j++ ){
			rot_grid[i][j] = 0;
		}
	}
	switch (piece){
		case I:
			switch (angle){
				case 0:
					for (i = 0; i < 4; i++ ) {
						rot_grid[i][2] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 4; i++ ) {
						rot_grid[1][i] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 4; i++ ) {
						rot_grid[i][1] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 4; i++ ) {
						rot_grid[2][i] = 1;
					}
					break;
			}
			break;

		case O:
			rot_grid[0][0] = 1;
			rot_grid[0][1] = 1;
			rot_grid[1][0] = 1;
			rot_grid[1][1] = 1;
			break;
		case T:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						rot_grid[i][1] = 1;
					}
					rot_grid[1][2] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						rot_grid[1][i] = 1;
					}
					rot_grid[0][1] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						rot_grid[i][1] = 1;
					}
					rot_grid[1][0] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						rot_grid[1][i] = 1;
					}
					rot_grid[2][1] = 1;
					break;
				}
			break;
		case J:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						rot_grid[i][1] = 1;
					}
					rot_grid[2][2] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						rot_grid[1][i] = 1;
					}
					rot_grid[0][2] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						rot_grid[i][1] = 1;
					}
					rot_grid[0][0] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						rot_grid[1][i] = 1;
					}
					rot_grid[2][0] = 1;
					break;
				}
			
			break;
		case L:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						rot_grid[i][1] = 1;
					}
					rot_grid[2][0] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						rot_grid[1][i] = 1;
					}
					rot_grid[2][2] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						rot_grid[i][1] = 1;
					}
					rot_grid[0][2] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						rot_grid[1][i] = 1;
					}
					rot_grid[0][0] = 1;
					break;
				}
			
			break;
		case S:
			switch (angle){
				case 0:
					for (i = 0; i < 2; i++ ) {
						rot_grid[i+1][0] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[i][1] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 2; i++ ) {
						rot_grid[2][i+1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[1][i] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 2; i++ ) {
						rot_grid[i+1][0] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[i][2] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 2; i++ ) {
						rot_grid[1][i+1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[0][i] = 1;
					}
					break;
				}
			
			break;

			
		case Z:
			switch (angle){
				case 0:
					for (i = 0; i < 2; i++ ) {
						rot_grid[i+1][1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[i][0] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 2; i++ ) {
						rot_grid[2][i] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[1][i+1] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 2; i++ ) {
						rot_grid[i+1][2] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[i][1] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 2; i++ ) {
						rot_grid[1][i] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						rot_grid[0][i+1] = 1;
					}
					break;
				}
			
			break;
	}

	//return rot_grid;
}

void draw_tetromino(tetromino_type piece, int16_t y, int16_t x, uint16_t angle, uint16_t color){
	int i = 0;
	x = x*BLOCK_SIZE;
	y = y*BLOCK_SIZE;
	
	clear_grid();

	//last_tetromino = current_tetromino;
	switch (piece){
		case I:
			switch (angle){
				case 0:
					for (i = 0; i < 4; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE*2,color);
						block_grid[i][2] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 4; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 4; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 4; i++ ) {
						display_block(x+BLOCK_SIZE*2,y+BLOCK_SIZE*i,color);
						block_grid[2][i] = 1;
					}
					break;
			}
			break;

		case O:
			display_block(x,y,color);
			display_block(x+BLOCK_SIZE,y,color);
			display_block(x,y+BLOCK_SIZE,color);
			display_block(x+BLOCK_SIZE,y+BLOCK_SIZE,color);
			block_grid[0][0] = 1;
			block_grid[0][1] = 1;
			block_grid[1][0] = 1;
			block_grid[1][1] = 1;
			break;
		case T:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*2,color);
					block_grid[1][2] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					display_block(x,y+BLOCK_SIZE,color);
					block_grid[0][1] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					display_block(x+BLOCK_SIZE,y,color);
					block_grid[1][0] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					display_block(x+BLOCK_SIZE*2,y+BLOCK_SIZE,color);
					block_grid[2][1] = 1;
					break;
				}
			break;
		case J:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					display_block(x+BLOCK_SIZE*2,y+BLOCK_SIZE*2,color);
					block_grid[2][2] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					display_block(x,y+BLOCK_SIZE*2,color);
					block_grid[0][2] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					display_block(x,y,color);
					block_grid[0][0] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					display_block(x+BLOCK_SIZE*2,y,color);
					block_grid[2][0] = 1;
					break;
				}
			
			break;
		case L:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					display_block(x+BLOCK_SIZE*2,y,color);
					block_grid[2][0] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					display_block(x+BLOCK_SIZE*2,y+BLOCK_SIZE*2,color);
					block_grid[2][2] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					display_block(x,y+BLOCK_SIZE*2,color);
					block_grid[0][2] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					display_block(x,y,color);
					block_grid[0][0] = 1;
					break;
				}
			
			break;
		case S:
			switch (angle){
				case 0:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*(i+1),y,color);
						block_grid[i+1][0] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*2,y+BLOCK_SIZE*(i+1),color);
						block_grid[2][i+1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*(i+1),y+BLOCK_SIZE,color);
						block_grid[i+1][0] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE*2,color);
						block_grid[i][2] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*(i+1),color);
						block_grid[1][i+1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x,y+BLOCK_SIZE*i,color);
						block_grid[0][i] = 1;
					}
					break;
				}
			
			break;

			
		case Z:
			switch (angle){
				case 0:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*(i+1),y+BLOCK_SIZE,color);
						block_grid[i+1][1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*i,y,color);
						block_grid[i][0] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*2,y+BLOCK_SIZE*i,color);
						block_grid[2][i] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*(i+1),color);
						block_grid[1][i+1] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*(i+1),y+BLOCK_SIZE*2,color);
						block_grid[i+1][2] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE,color);
						block_grid[i][1] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 2; i++ ) {
						display_block(x+BLOCK_SIZE,y+BLOCK_SIZE*i,color);
						block_grid[1][i] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						display_block(x,y+BLOCK_SIZE*(i+1),color);
						block_grid[0][i+1] = 1;
					}
					break;
				}
			
			break;
	}

}

void display_tetromino(tetromino piece){
	draw_tetromino(piece.type,piece.y,piece.x,piece.angle,piece.type);
}

void clear_tetromino(tetromino piece){
	draw_tetromino(piece.type,piece.y,piece.x,piece.angle,BLACK);
}