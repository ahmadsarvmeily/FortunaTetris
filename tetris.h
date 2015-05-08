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

#define MAX_LEVEL 31

typedef enum {Up,Down,Left,Right} direction;

void redraw_tetromino();
void show_grid();
void clear_area();
void clear_field();
void redraw();
int check_line(int line);
void clear_lines();
int check_collision(tetromino block);
void store_block(tetromino block);
void reset_bag();
int random_block_number();
int spawn_block();
int rotate_tetromino();
void move_tetromino(direction movement);
void reset();
