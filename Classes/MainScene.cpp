#include "MainScene.h"
#include "Resource.h"

USING_NS_CC;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	log("%f",visibleSize.width);
	log("%f",visibleSize.height);

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
	auto action_floor = Sequence::create(MoveTo::create(FLOOR_SPEED, Point(-1*visibleSize.width,origin.y)),										
										CallFunc::create(
										[&](){
												Point origin = Director::getInstance()->getVisibleOrigin();
												this->getChildByTag(TAG_FLOOR_1)->setPosition(origin.x,origin.y);
									         }),NULL);
	floor->runAction(RepeatForever::create(action_floor));
	this->addChild(floor,2);
    
	auto floor2 = Sprite::create(RES_BIRD_FLOOR);
	floor2->setScale(visibleSize.width / floor2->getContentSize().width, visibleSize.height/480);
	floor2->setAnchorPoint(Point::ZERO);
	floor2->setPosition(origin.x+visibleSize.width,origin.y);
	floor2->setTag(TAG_FLOOR_2);
	auto action_floor2 = Sequence::create(MoveTo::create(FLOOR_SPEED, Point(origin.x,origin.y)),										
		CallFunc::create(
		[&](){
			Point origin = Director::getInstance()->getVisibleOrigin();
			this->getChildByTag(TAG_FLOOR_2)->setPosition(origin.x+Director::getInstance()->getVisibleSize().width,origin.y);
	}),NULL);
	floor2->runAction(RepeatForever::create(action_floor2));
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
}

void MainWorld::gameRate(Ref* pSender)
{

}

void MainWorld::gameRank(Ref* pSender)
{

}

void MainWorld::update(float time)
{

}

void MainWorld::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
//	log("%s","touch began");
}

void MainWorld::onTouchesEnded(const vector<Touch*>& touches, Event* event)
{
//	log("%s","touch end");
}
