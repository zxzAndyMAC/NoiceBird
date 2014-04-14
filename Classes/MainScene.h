#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MainWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void gameStart(Ref* pSender);
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
	int  b_gamestate;
	

	void updateFloor();
	void updatePipelines();
};

#endif // __HELLOWORLD_SCENE_H__
