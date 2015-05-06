#include "tetromino.h"
#include <stdio.h>

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

int leftmost_virtual_block(){
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		for ( j = 0; j < 4; j++ ){
			if (virtual_grid[i][j]) return i;
		}
	}
	return -1;
}

int rightmost_virtual_block(){
	int i, j = 4;
	for ( i = 3; i > -1; i-- ){
		for ( j = 3; j > -1; j-- ){
			if (virtual_grid[i][j]) return i;
		}
	}
	return -1;
}

int bottommost_virtual_block(){
	int i, j = 4;
	for ( i = 3; i > -1; i-- ){
		for ( j = 3; j > -1; j-- ){
			if (virtual_grid[j][i]) return i;
		}
	}
	return -1;
}

void show_block_grid(){
	int ypos = 70 + (GRID_HEIGHT*10);
	char str[15];
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		display_string_xy("",SIDEBAR_START+10,ypos);
		for ( j = 0; j < 4; j++ ){
			//sprintf(str,"%d",grid[j][i]);
			//display_string(str);
			if(block_grid[j][i]) {display_string("X");}
			else {display_string("O");}
		}
		ypos += 10;
	}
}

void display_block(uint16_t x, uint16_t y, uint16_t color){
	rectangle shape = {x+1,x+BLOCK_SIZE-1,y+1,y+BLOCK_SIZE-1};
	fill_rectangle(shape,color);
}

void adjust_virtual_grid(tetromino_type piece, uint16_t angle){
	int i, j = 0;
	for ( i = 0; i < 4; i++ ){
		for ( j = 0; j < 4; j++ ){
			virtual_grid[i][j] = 0;
		}
	}
	switch (piece){
		case I:
			switch (angle){
				case 0:
					for (i = 0; i < 4; i++ ) {
						virtual_grid[i][2] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 4; i++ ) {
						virtual_grid[1][i] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 4; i++ ) {
						virtual_grid[i][1] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 4; i++ ) {
						virtual_grid[2][i] = 1;
					}
					break;
			}
			break;

		case O:
			virtual_grid[0][0] = 1;
			virtual_grid[0][1] = 1;
			virtual_grid[1][0] = 1;
			virtual_grid[1][1] = 1;
			break;
		case T:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[i][1] = 1;
					}
					virtual_grid[1][2] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[1][i] = 1;
					}
					virtual_grid[0][1] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[i][1] = 1;
					}
					virtual_grid[1][0] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[1][i] = 1;
					}
					virtual_grid[2][1] = 1;
					break;
				}
			break;
		case J:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[i][1] = 1;
					}
					virtual_grid[2][2] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[1][i] = 1;
					}
					virtual_grid[0][2] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[i][1] = 1;
					}
					virtual_grid[0][0] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[1][i] = 1;
					}
					virtual_grid[2][0] = 1;
					break;
				}
			
			break;
		case L:
			switch (angle){
				case 0:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[i][1] = 1;
					}
					virtual_grid[2][0] = 1;
					break;
				case 1:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[1][i] = 1;
					}
					virtual_grid[2][2] = 1;
					break;
				case 2:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[i][1] = 1;
					}
					virtual_grid[0][2] = 1;
					break;
				case 3:
					for (i = 0; i < 3; i++ ) {
						virtual_grid[1][i] = 1;
					}
					virtual_grid[0][0] = 1;
					break;
				}
			
			break;
		case S:
			switch (angle){
				case 0:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i+1][0] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i][1] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[2][i+1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[1][i] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i+1][1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i][2] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[1][i+1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[0][i] = 1;
					}
					break;
				}
			
			break;

			
		case Z:
			switch (angle){
				case 0:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i+1][1] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i][0] = 1;
					}
					break;
				case 1:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[2][i] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[1][i+1] = 1;
					}
					break;
				case 2:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i+1][2] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[i][1] = 1;
					}
					break;
				case 3:
					for (i = 0; i < 2; i++ ) {
						virtual_grid[1][i] = 1;
					}
					for (i = 0; i < 2; i++ ) {
						virtual_grid[0][i+1] = 1;
					}
					break;
				}
			
			break;
	}

}

void update_block_grid(){
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			block_grid[i][j] = virtual_grid[i][j];
		}
	}
}

void draw_tetromino(tetromino_type piece, int16_t y, int16_t x, uint16_t angle, uint16_t color){
	adjust_virtual_grid(piece,angle);
	update_block_grid();
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			if (block_grid[i][j]) display_block(x+BLOCK_SIZE*i,y+BLOCK_SIZE*j,color);
		}
	}
}

void display_tetromino(tetromino piece){
	draw_tetromino(piece.type,piece.y*BLOCK_SIZE,piece.x*BLOCK_SIZE,piece.angle,piece.type);
}

void clear_tetromino(tetromino piece){
	draw_tetromino(piece.type,piece.y*BLOCK_SIZE,piece.x*BLOCK_SIZE,piece.angle,BLACK);
}