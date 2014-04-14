#include "MainScene.h"
#include "Resource.h"

USING_NS_CC;

static float dis = 0.0f;

Scene* MainWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	srand ((unsigned)time(NULL));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	log("%f",visibleSize.width);
	log("%f",visibleSize.height);

	b_gamestate = GAME_STATUS_START;

	// game bg
	auto bg = Sprite::create(RES_BIRD_BG);
	bg->setPosition(origin.x+visibleSize.width / 2, origin.y+visibleSize.height / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg);

	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;

	// logo
	auto logo = Sprite::create(RES_BIRD_LOGO);
	logo->setScale(scaleX,scaleY);
	logo->setPosition(origin.x+visibleSize.width / 2, origin.y+visibleSize.height / 2 + logo->getContentSize().height * 2 * scaleY);
	logo->setTag(TAG_LOGO);
	this->addChild(logo, 1);

	// bird
	auto bird = Sprite::create(RES_BIRD_BIRD);
	bird->setScale(scaleX,scaleY);
	bird->setPosition(origin.x+visibleSize.width / 2, origin.y+visibleSize.height*0.6);
	bird->setTag(TAG_BIRD);
	this->addChild(bird, 1);
	Animation* an = Animation::create();
	an->addSpriteFrameWithFile(RES_BIRD_BIRD);
	an->addSpriteFrameWithFile(RES_BIRD_BIRD1);
	an->addSpriteFrameWithFile(RES_BIRD_BIRD2);
	an->setDelayPerUnit(BIRD_ANIM_S);
	an->setLoops(-1);
	Animate* anim = Animate::create(an);
	bird->runAction(anim);

	//floor
	auto floor = Sprite::create(RES_BIRD_FLOOR);
	floor->setScale(visibleSize.width / floor->getContentSize().width, visibleSize.height/480);
	floor->setAnchorPoint(Point::ZERO);
	floor->setPosition(origin.x,origin.y);
	floor->setTag(TAG_FLOOR_1);
	//auto action_floor = Sequence::create(MoveTo::create(FLOOR_SPEED, Point(-1*visibleSize.width,origin.y)),										
	//									CallFunc::create(
	//									[&](){
	//											Point origin = Director::getInstance()->getVisibleOrigin();
	//											this->getChildByTag(TAG_FLOOR_1)->setPosition(origin.x,origin.y);
	//								         }),NULL);
	//floor->runAction(RepeatForever::create(action_floor));
	this->addChild(floor,2);
    
	auto floor2 = Sprite::create(RES_BIRD_FLOOR);
	floor2->setScale(visibleSize.width / floor2->getContentSize().width, visibleSize.height/480);
	floor2->setAnchorPoint(Point::ZERO);
	floor2->setPosition(origin.x+visibleSize.width,origin.y);
	floor2->setTag(TAG_FLOOR_2);
	//auto action_floor2 = Sequence::create(MoveTo::create(FLOOR_SPEED, Point(origin.x,origin.y)),										
	//	CallFunc::create(
	//	[&](){
	//		Point origin = Director::getInstance()->getVisibleOrigin();
	//		this->getChildByTag(TAG_FLOOR_2)->setPosition(origin.x+Director::getInstance()->getVisibleSize().width,origin.y);
	//}),NULL);
	//floor2->runAction(RepeatForever::create(action_floor2));
	this->addChild(floor2,2);

	// start btn
	auto startBtn = MenuItemImage::create(RES_BIRD_SBTN, RES_BIRD_SBTNP, CC_CALLBACK_1(MainWorld::gameStart, this));
	startBtn->setScale(scaleX,scaleY);
	startBtn->setPosition(origin.x+visibleSize.width / 4, origin.y+startBtn->getScaleY()*startBtn->getContentSize().height/2+floor->getContentSize().height*floor->getScaleY());
	auto menu = Menu::create(startBtn, NULL);
	menu->setPosition(Point::ZERO);
	menu->setTag(TAG_START_BTN);
	this->addChild(menu, 2);

	//rank btn
	auto rankBtn = MenuItemImage::create(RES_BIRD_RANK, RES_BIRD_RANKP, CC_CALLBACK_1(MainWorld::gameRank, this));
	rankBtn->setScale(scaleX,scaleY);
	rankBtn->setPosition(origin.x+(3*visibleSize.width) / 4, origin.y+rankBtn->getScaleY()*startBtn->getContentSize().height/2+floor->getContentSize().height*floor->getScaleY());
	auto menu2 = Menu::create(rankBtn, NULL);
	menu2->setPosition(Point::ZERO);
	menu2->setTag(TAG_RANK_BTN);
	this->addChild(menu2, 2);

	//rate Btn
	auto rateBtn = MenuItemImage::create(RES_BIRD_RATE, RES_BIRD_RATE, CC_CALLBACK_1(MainWorld::gameRate, this));
	rateBtn->setScale(scaleX,scaleY);
	rateBtn->setPosition(origin.x+visibleSize.width / 2, origin.y+visibleSize.height*0.5);
	auto menu3 = Menu::create(rateBtn, NULL);
	menu3->setPosition(Point::ZERO);
	menu3->setTag(TAG_RATE_BTN);
	this->addChild(menu3, 2);

	//pipeline
	for(int i=0;i<3;i++)
	{
		pipelines_down[i] = Sprite::create(RES_BIRD_OBD);
		pipelines_down[i]->setScale(scaleX,scaleY);
		pipelines_down[i]->setVisible(false);
		pipelines_down[i]->setAnchorPoint(Point::ZERO);
		this->addChild(pipelines_down[i], 1);

		pipelines_up[i] = Sprite::create(RES_BIRD_OBU);
		pipelines_up[i]->setScale(scaleX,scaleY);
		pipelines_up[i]->setVisible(false);
		pipelines_up[i]->setAnchorPoint(Point::ZERO);
		this->addChild(pipelines_up[i], 1);
	}

	// update 
	scheduleUpdate();

	// touch
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(MainWorld::onTouchesEnded, this);
	listener->onTouchesBegan = CC_CALLBACK_2(MainWorld::onTouchesBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void MainWorld::gameStart(Ref* pSender)
{
	auto action = Sequence::create(DelayTime::create(2.0f),										
		CallFunc::create(
		[&](){
			this->b_gamestate = GAME_STATUS_PLAYING;
			pipelines_up[0]->setVisible(true);
			pipelines_down[0]->setVisible(true);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Point origin = Director::getInstance()->getVisibleOrigin();
			auto floor_1 = this->getChildByTag(TAG_FLOOR_1);
			auto floor_h = floor_1->getContentSize().height*(floor_1->getScaleY());
			auto min_y = floor_h + (MIN_UP_DOWN/4);
			auto max_y = visibleSize.height - (MIN_UP_DOWN*5/4);
			auto y = CCRANDOM_0_1()*(max_y - min_y) + min_y;
			dis = y;
			auto h = pipelines_down[0]->getContentSize().height*pipelines_down[0]->getScaleY();
			pipelines_down[0]->setPosition(origin.x + visibleSize.width, origin.y+y-h);
			pipelines_up[0]->setPosition(origin.x + visibleSize.width, origin.y+y+MIN_UP_DOWN);

			auto y2 = CCRANDOM_0_1()*(max_y - min_y) + min_y;
			while(abs((int)y2 - (int)dis)<=100)
			{
				y2 = CCRANDOM_0_1()*(max_y - min_y) + min_y;
			}
			dis = y2;
			pipelines_down[1]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT, origin.y+y2-h);
			pipelines_up[1]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT, origin.y+y2+MIN_UP_DOWN);

			auto y3 = CCRANDOM_0_1()*(max_y - min_y) + min_y;
			while(abs((int)y3 - (int)dis)<=100)
			{
				y3 = CCRANDOM_0_1()*(max_y - min_y) + min_y;
			}
			dis = y3;
			pipelines_down[2]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT*2, origin.y+y3-h);
			pipelines_up[2]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT*2, origin.y+y3+MIN_UP_DOWN);
	}),NULL);

	this->runAction(action);
}

void MainWorld::gameRate(Ref* pSender)
{

}

void MainWorld::gameRank(Ref* pSender)
{

}

void MainWorld::update(float time)
{
	switch(b_gamestate)
	{
	case GAME_STATUS_START:
		updateFloor();
		break;
	case GAME_STATUS_PLAYING:
		updateFloor();
		updatePipelines();
		break;
	}
}

void MainWorld::updatePipelines()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	for(int i=0;i<3;i++)
	{
		auto x = pipelines_up[i]->getPositionX();
		auto w = pipelines_up[i]->getContentSize().width*pipelines_up[i]->getScaleX();
		if(x+w<=0)
		{
			auto floor_1 = this->getChildByTag(TAG_FLOOR_1);
			auto floor_h = floor_1->getContentSize().height*(floor_1->getScaleY());
			auto min_y = floor_h + (MIN_UP_DOWN/4);
			auto max_y = visibleSize.height - (MIN_UP_DOWN*5/4);
			auto y = CCRANDOM_0_1()*(max_y - min_y) + min_y;
			while(abs((int)y - (int)dis)<=100)
			{
				y = CCRANDOM_0_1()*(max_y - min_y) + min_y;
			}
			dis = y;
			auto h = pipelines_down[i]->getContentSize().height*pipelines_down[i]->getScaleY();
			auto f_x = i==0 ? pipelines_up[2]->getPositionX() : pipelines_up[i-1]->getPositionX();
			pipelines_down[i]->setPosition(f_x+MIN_LEFT_RIGHT, origin.y+y-h);
			pipelines_up[i]->setPosition(f_x+MIN_LEFT_RIGHT, origin.y+y+MIN_UP_DOWN);
			pipelines_down[i]->setVisible(false);
			pipelines_up[i]->setVisible(false);
			continue;
		}
		pipelines_up[i]->setPositionX(x - FLOOR_SPEED);
		pipelines_down[i]->setPositionX(x - FLOOR_SPEED);
		if(x - FLOOR_SPEED <= visibleSize.width && !pipelines_up[i]->isVisible())
		{
			pipelines_up[i]->setVisible(true);
			pipelines_down[i]->setVisible(true);
		}
	}
}

void MainWorld::updateFloor()
{
	//update floor 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto floor_1 = this->getChildByTag(TAG_FLOOR_1);
	auto floor_2 = this->getChildByTag(TAG_FLOOR_2);

	auto floor_1_x = floor_1->getPositionX();
	if(floor_1_x<=-1*visibleSize.width)
		floor_1->setPositionX(origin.x);
	else
		floor_1->setPositionX(floor_1_x-FLOOR_SPEED);

	auto floor_2_x = floor_2->getPositionX();
	if(floor_2_x<=origin.x)
		floor_2->setPositionX(origin.x+visibleSize.width);
	else
		floor_2->setPositionX(floor_2_x-FLOOR_SPEED);
}

void MainWorld::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
//	log("%s","touch began");
}

void MainWorld::onTouchesEnded(const vector<Touch*>& touches, Event* event)
{
//	log("%s","touch end");
}
