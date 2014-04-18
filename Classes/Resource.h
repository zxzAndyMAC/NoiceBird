#ifndef __BIRD_RES__
#define __BIRD_RES__

#define BIRD_DEBUG 1

#define BIRD_RAND(i, n) RES_BIRD_BIRD_##i##_##n

//res
#define RES_BIRD_BG       "bird/bird_bg.png"
#define RES_BIRD_LOGO     "bird/bird_logo.png"
#define RES_BIRD_BIRD_1_1 "bird/bird_1_1.png"
#define RES_BIRD_BIRD_1_2 "bird/bird_1_2.png"
#define RES_BIRD_BIRD_1_3 "bird/bird_1_3.png"
#define RES_BIRD_BIRD_2_1 "bird/bird_2_1.png"
#define RES_BIRD_BIRD_2_2 "bird/bird_2_2.png"
#define RES_BIRD_BIRD_2_3 "bird/bird_2_3.png"
#define RES_BIRD_BIRD_3_1 "bird/bird_3_1.png"
#define RES_BIRD_BIRD_3_2 "bird/bird_3_2.png"
#define RES_BIRD_BIRD_3_3 "bird/bird_3_3.png"
#define RES_BIRD_BIRD_4_1 "bird/bird_4_1.png"
#define RES_BIRD_BIRD_4_2 "bird/bird_4_2.png"
#define RES_BIRD_BIRD_4_3 "bird/bird_4_3.png"
#define RES_BIRD_VOICE    "bird/bird_noice.png"
#define RES_BIRD_VOICEP   "bird/bird_noice_pressed.png"
#define RES_BIRD_TOUCH    "bird/bird_touch.png"
#define RES_BIRD_TOUCHP	  "bird/bird_touch_pressed.png"
#define RES_BIRD_FLOOR    "bird/bird_floor.png"
#define RES_BIRD_RANK     "bird/bird_rank.png"
#define RES_BIRD_RANKP    "bird/bird_rank_press.png"
#define RES_BIRD_RATE     "bird/bird_rate.png"
#define	RES_BIRD_OBD      "bird/obstacle_down.png"
#define	RES_BIRD_OBU      "bird/obstacle_up.png"
#define RES_BIRD_TAP      "bird/bird_tap.png"

//TAG
#define TAG_LOGO		1000
#define TAG_BIRD		1001
#define TAG_VOICE_BTN   1002
#define TAG_FLOOR_1     1003
#define TAG_FLOOR_2     1004
#define TAG_RANK_BTN	1005
#define TAG_RATE_BTN    1006
#define TAG_TOUCH_BTN   1007
#define TAG_SCORE       1008
#define TAG_FLY         1009
#define TAG_TAP         1010
#define TAG_COLOR       1011

//states
#define GAME_STATUS_START      10
#define GAME_STATUS_READY      20
#define GAME_STATUS_PLAYING    30
#define GAME_STATUS_GAME_OVER  40
#define GAME_STATUS_RESTART    50
#define GAME_STATUS_GAME_END   60
#define GAME_STATUS_PRE        70

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
#define MAX_DIS          200.0
#endif
#endif