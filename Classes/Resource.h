#ifndef __BIRD_RES__
#define __BIRD_RES__

#define BIRD_DEBUG 1
//res
#define RES_BIRD_BG       "bird/bird_bg.png"
#define RES_BIRD_LOGO     "bird/bird_logo.png"
#define RES_BIRD_BIRD     "bird/bird_hero.png"
#define RES_BIRD_BIRD1    "bird/bird_hero2.png"
#define RES_BIRD_BIRD2    "bird/bird_hero3.png"
#define RES_BIRD_SBTN     "bird/bird_start_btn.png"
#define RES_BIRD_SBTNP    "bird/brid_start_btn_pressed.png"
#define RES_BIRD_FLOOR    "bird/bird_floor.jpg"
#define RES_BIRD_RANK     "bird/bird_rank.png"
#define RES_BIRD_RANKP    "bird/bird_rank_press.png"
#define RES_BIRD_RATE     "bird/bird_rate.png"
#define	RES_BIRD_OBD      "bird/obstacle_down.png"
#define	RES_BIRD_OBU      "bird/obstacle_up.png"

//TAG
#define TAG_LOGO		1000
#define TAG_BIRD		1001
#define TAG_START_BTN   1002
#define TAG_FLOOR_1     1003
#define TAG_FLOOR_2     1004
#define TAG_RANK_BTN	1005
#define TAG_RATE_BTN    1006

//states
#define GAME_STATUS_START      10
#define GAME_STATUS_READY      20
#define GAME_STATUS_PLAYING    30
#define GAME_STATUS_GAME_OVER  40
#define GAME_STATUS_RESTART    50
#define GAME_STATUS_GAME_END   60

#ifdef BIRD_DEBUG
//param
static float FLOOR_SPEED=5;
static float BIRD_ANIM_S=0.15f;
static float MIN_LEFT_RIGHT=350;
static float MIN_UP_DOWN=200;
static float MIN_DIS=50;
static float BIRD_GRAVITY=0.5f;
static float BIRD_VELOCITY=5;
static float BIRD_UP_VELOCITY=10;
static float MAX_DIS=200.0;
#else
//param
#define FLOOR_SPEED      5
#define BIRD_ANIM_S      0.15f
#define MIN_LEFT_RIGHT   360
#define MIN_UP_DOWN      200
#define MIN_DIS          50
#define BIRD_GRAVITY     0.5f
#define BIRD_VELOCITY    5
#define BIRD_UP_VELOCITY 10
#define MAX_DIS          250.0
#endif
#endif