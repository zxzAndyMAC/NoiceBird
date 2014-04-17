#ifndef __BIRD_RES__
#define __BIRD_RES__

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

//param
#define FLOOR_SPEED     7
#define BIRD_ANIM_S     0.15f
#define MIN_LEFT_RIGHT  350
#define MIN_UP_DOWN     200

//states
#define GAME_STATUS_START      10
#define GAME_STATUS_PLAYING    20
#define GAME_STATUS_GAME_OVER  30
#define GAME_STATUS_RESTART    40

#endif