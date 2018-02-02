#define SWN     PC2
#define SWE     PC3
#define SWS     PC4
#define SWW     PC5
#define SWC     PE7
#define ROTA	PE4
#define ROTB	PE5

#define COMPASS_SWITCHES (_BV(SWW)|_BV(SWS)|_BV(SWE)|_BV(SWN))

void init_switches();
int right_rotate();
int center_pressed();
int left_pressed();
int right_pressed();
int up_pressed();
int down_pressed();
int down_held();