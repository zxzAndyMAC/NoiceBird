#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "SoundDispatcher.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MainWorld : public cocos2d::Layer , SoundDispatcher
{
public:
	~MainWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void gameNoice(Ref* pSender);
	void gameTouch(Ref* pSender);
	void gameRank(Ref* pSender);
	void gameRate(Ref* pSender);

	void update(float time);

	void onTouchesEnded(const vector<Touch*>& touches, Event* event);
	void onTouchesBegan(const vector<Touch*>& touches, Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(MainWorld);

	Sprite *pipelines_down[3];
	Sprite *pipelines_up[3];

private:
	void  SoundeHandler(float db) override;

	int   b_gamestate;
	float b_velocity;
	bool  b_judge[3];
	int   b_score;
	float b_y;
	int   b_moode;
	float b_sound;

	void  initBird();
	void  updateSoundBanner();
	void  updateFloor();
	void  updatePipelines();
	void  updateBird();
	void  gameready();
	void  checkCollision();
	void  gameOver();
	void  setStartMenuVisiable(bool isVisiable);
	float randh();
	void  setPipes();
	void  initGame();
	void  preloadEffects();
};

#endif // __HELLOWORLD_SCENE_H__
