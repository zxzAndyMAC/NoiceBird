#ifndef __BIRD_RES__
#define __BIRD_RES__

#ifdef WIN32
#define BIRD_DEBUG 1
#endif // WIN32

#define BIRD_RAND(i, n) RES_BIRD_BIRD_##i##_##n

//res
#define RES_BIRD_BG       "bird_bg.png"
#define RES_BIRD_LOGO     "bird_logo.png"
#define RES_BIRD_BIRD_1_1 "bird_1_1.png"
#define RES_BIRD_BIRD_1_2 "bird_1_2.png"
#define RES_BIRD_BIRD_1_3 "bird_1_3.png"
#define RES_BIRD_BIRD_2_1 "bird_2_1.png"
#define RES_BIRD_BIRD_2_2 "bird_2_2.png"
#define RES_BIRD_BIRD_2_3 "bird_2_3.png"
#define RES_BIRD_BIRD_3_1 "bird_3_1.png"
#define RES_BIRD_BIRD_3_2 "bird_3_2.png"
#define RES_BIRD_BIRD_3_3 "bird_3_3.png"
#define RES_BIRD_BIRD_4_1 "bird_4_1.png"
#define RES_BIRD_BIRD_4_2 "bird_4_2.png"
#define RES_BIRD_BIRD_4_3 "bird_4_3.png"
#define RES_BIRD_VOICE    "bird_noice.png"
#define RES_BIRD_VOICEP   "bird_noice_pressed.png"
#define RES_BIRD_TOUCH    "bird_touch.png"
#define RES_BIRD_TOUCHP	  "bird_touch_pressed.png"
#define RES_BIRD_FLOOR    "bird_floor.png"
#define RES_BIRD_RANK     "bird_rank.png"
#define RES_BIRD_RANKP    "bird_rank_press.png"
#define RES_BIRD_RATE     "bird_rate.png"
#define	RES_BIRD_OBD      "obstacle_down.png"
#define	RES_BIRD_OBU      "obstacle_up.png"
#define RES_BIRD_TAP      "bird_tap.png"
#define RES_BIRD_RESULT   "scorebest.png"
#define RES_BIRD_NEW      "new.png"
#define RES_GAME_OVER     "bird_game_over.png"
#define RES_SOUND_MODE    "sound_mode.png"
#define RES_SOUND_BANNER  "sound_banner.png"
#define RES_SOUND_BANNER_O  "sound_banner_o.png"
#define RES_LOGO_1	      "logo-origin_1.png"
#define RES_LOGO_2	      "logo-origin_2.png"

//sound
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define SOUND_FLY		  "sound_android/fly.ogg"
#define SOUND_DEAD		  "sound_android/dead.ogg"
#define SOUND_POINT       "sound_android/point.ogg"
#else
#define SOUND_FLY		  "sound_win_mac/fly.wav"
#define SOUND_DEAD		  "sound_win_mac/dead.wav"
#define SOUND_POINT       "sound_win_mac/point.wav"
#endif

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
#define TAG_RESULT      1022
#define TAG_NEW			1023
#define TAG_SCORE1      1024
#define TAG_BEST		1025
#define TAG_OVER		1026
#define TAG_SOUND		1027
#define TAG_SOUND_BANNER 1028
#define TAG_SOUND_BANNER_O 1029
#define TAG_LOGO_1       1030
#define TAG_LOGO_2       1031
#define TAG_BATCHNODE    1032

//states
#define GAME_STATUS_START      10
#define GAME_STATUS_READY      20
#define GAME_STATUS_PLAYING    30
#define GAME_STATUS_GAME_OVER  40
#define GAME_STATUS_RESTART    50
#define GAME_STATUS_GAME_END   60
#define GAME_STATUS_PRE        70

#define MODE_TOUCH  2000
#define MODE_SOUND  2001

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
static float MIN_DB = 10;
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
#define MIN_DB			 7
#endif
#endif