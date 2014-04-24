#include "MainScene.h"
#include "Resource.h"
#include "Sound.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "BirdJni.h"
#endif // Android


#ifdef BIRD_DEBUG
#include "FileR.h"
#endif

USING_NS_CC;

static float dis = 0.0f;

static void setEnableRecursiveCascading(Node* node, bool enable)
{
	node->setCascadeColorEnabled(enable);
	node->setCascadeOpacityEnabled(enable);

	auto& children = node->getChildren();
	for(const auto &child : children) {
		setEnableRecursiveCascading(child, enable);
	}
}

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
    
#ifdef BIRD_DEBUG
	FileR::ReadConfig();
#endif // BIRD_DEBUG

	Sound::getInstance()->setDispatcher(this);

	srand ((unsigned)time(NULL));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	log("%f",visibleSize.width);
	log("%f",visibleSize.height);

	b_gamestate = GAME_STATUS_START;
	b_velocity  =  BIRD_VELOCITY;
	b_sound = 0.0f;

	// game bg
	auto bg = Sprite::create(RES_BIRD_BG);
	bg->setPosition(origin.x+visibleSize.width / 2, origin.y+visibleSize.height / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg);

	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;

	//floor
	auto floor = Sprite::create(RES_BIRD_FLOOR);
	floor->setScale(visibleSize.width / floor->getContentSize().width, visibleSize.height/480);
	floor->setAnchorPoint(Point::ZERO);
	floor->setPosition(origin.x,origin.y);
	floor->setTag(TAG_FLOOR_1);
	this->addChild(floor,3);
    
	auto floor2 = Sprite::create(RES_BIRD_FLOOR);
	floor2->setScale(visibleSize.width / floor2->getContentSize().width, visibleSize.height/480);
	floor2->setAnchorPoint(Point::ZERO);
	floor2->setPosition(origin.x+visibleSize.width,origin.y);
	floor2->setTag(TAG_FLOOR_2);
	this->addChild(floor2,3);

	// voice btn
	auto startBtn = MenuItemImage::create(RES_BIRD_VOICE, RES_BIRD_VOICEP, CC_CALLBACK_1(MainWorld::gameNoice, this));
	startBtn->setScale(scaleX,scaleY);
	startBtn->setPosition(origin.x+visibleSize.width / 4, origin.y+startBtn->getScaleY()*startBtn->getContentSize().height/2+floor->getContentSize().height*floor->getScaleY());
	auto menu = Menu::create(startBtn, NULL);
	menu->setPosition(Point::ZERO);
	menu->setTag(TAG_VOICE_BTN);
	this->addChild(menu, 4);

	//touch btn
	auto touchBtn = MenuItemImage::create(RES_BIRD_TOUCH, RES_BIRD_TOUCHP, CC_CALLBACK_1(MainWorld::gameTouch, this));
	touchBtn->setScale(scaleX,scaleY);
	touchBtn->setPosition(origin.x+(3*visibleSize.width) / 4, origin.y+touchBtn->getScaleY()*startBtn->getContentSize().height/2+floor->getContentSize().height*floor->getScaleY());
	auto menu2 = Menu::create(touchBtn, NULL);
	menu2->setPosition(Point::ZERO);
	menu2->setTag(TAG_TOUCH_BTN);
	this->addChild(menu2, 4);

	//rank btn
	auto rankBtn = MenuItemImage::create(RES_BIRD_RANK, RES_BIRD_RANKP, CC_CALLBACK_1(MainWorld::gameRank, this));
	rankBtn->setScale(scaleX,scaleY);
	rankBtn->setPosition(origin.x+visibleSize.width / 2, origin.y+startBtn->getScaleY()*startBtn->getContentSize().height*3/2+floor->getContentSize().height*floor->getScaleY());
	auto menu4 = Menu::create(rankBtn, NULL);
	menu4->setPosition(Point::ZERO);
	menu4->setTag(TAG_RANK_BTN);
	this->addChild(menu4, 4);

	//rate Btn
	auto rateBtn = MenuItemImage::create(RES_BIRD_RATE, RES_BIRD_RATE, CC_CALLBACK_1(MainWorld::gameRate, this));
	rateBtn->setScale(scaleX,scaleY);
	rateBtn->setPosition(origin.x+visibleSize.width / 2, origin.y + rankBtn->getPositionY() + rateBtn->getContentSize().height*scaleY*1.5);
	auto menu3 = Menu::create(rateBtn, NULL);
	menu3->setPosition(Point::ZERO);
	menu3->setTag(TAG_RATE_BTN);
	this->addChild(menu3, 4);

	// bird
	auto bird = Sprite::create(RES_BIRD_BIRD_1_1);
	bird->setScale(scaleX,scaleY);
	b_y = origin.y+rateBtn->getPositionY()+rateBtn->getContentSize().height*scaleY+ rateBtn->getContentSize().height*scaleY/2;
	bird->setPosition(origin.x+visibleSize.width / 2, b_y);
	bird->setTag(TAG_BIRD);
	this->addChild(bird, 2);
	

	// logo
	auto logo = Sprite::create(RES_BIRD_LOGO);
	logo->setScale(scaleX,scaleY);
	logo->setPosition(origin.x+visibleSize.width / 2, origin.y+bird->getPositionY()+bird->getContentSize().height*scaleY+ bird->getContentSize().height*scaleY*2);
	logo->setTag(TAG_LOGO);
	this->addChild(logo, 1);

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

	// score
	//auto score = Label::createWithBMFont("fonts/futura-48.fnt", "0");
	TTFConfig config("fonts/voltergoldfish.ttf",40);
	auto score = Label::createWithTTF(config,"0",TextHAlignment::LEFT);
	score->setPosition(origin.x+visibleSize.width / 2, origin.y+visibleSize.height*8 /9);
	score->setScaleX(scaleX);
	score->setScaleY(scaleY);
	score->setColor(Color3B::ORANGE);
	score->setAnchorPoint(Point::ANCHOR_MIDDLE);
	score->enableShadow(Color4B::BLACK,Size(2,-2),0);
	this->addChild(score, 3);
	score->setVisible(false);
	score->setTag(TAG_SCORE);

	//tap
	auto tapsprite = Sprite::create(RES_BIRD_TAP);
	tapsprite->setScale(scaleX,scaleY);
	tapsprite->setPosition(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2);
	tapsprite->setVisible(false);
	tapsprite->setTag(TAG_TAP);
	this->addChild(tapsprite, 3);

	auto layer = LayerColor::create(Color4B(0,0,0,0));
	layer->setTag(TAG_COLOR);
	layer->setVisible(false);
	this->addChild(layer, 5);

	//sound mode
	auto soundsprite = Sprite::create(RES_SOUND_MODE);
	soundsprite->setScale(scaleX,scaleY);
	soundsprite->setPosition(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2);
	soundsprite->setVisible(false);
	soundsprite->setTag(TAG_SOUND);
	this->addChild(soundsprite, 3);

	//score result
	auto score_result = Sprite::create(RES_BIRD_RESULT);
	score_result->setScale(scaleX,scaleY);
	score_result->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	score_result->setPosition(origin.x+visibleSize.width/2, rateBtn->getPositionY()+rateBtn->getContentSize().height);
	score_result->setTag(TAG_RESULT);

	auto score_1 = Label::createWithTTF(config,"0",TextHAlignment::LEFT);
	score_1->enableShadow(Color4B::BLACK,Size(2,-2),0);
	score_1->setPosition(score_result->getContentSize().width/2, score_result->getContentSize().height*6/8+5);
	score_1->setTag(TAG_SCORE1);
	score_result->addChild(score_1);

	auto score_best = Label::createWithTTF(config,"0",TextHAlignment::LEFT);
	score_best->enableShadow(Color4B::BLACK,Size(2,-2),0);
	score_best->setPosition(score_result->getContentSize().width/2, score_best->getContentSize().height+10);
	score_best->setTag(TAG_BEST);
	score_result->addChild(score_best);

	Value s(UserDefault::getInstance()->getIntegerForKey("score"));
	score_best->setString(s.getDescription());

	auto _new = Sprite::create(RES_BIRD_NEW);
	_new->setAnchorPoint(Point::ZERO);
	_new->setTag(TAG_NEW);
	_new->setPosition(_new->getContentSize().width/2,_new->getContentSize().height*2);
	_new->setVisible(false);
	score_result->addChild(_new);
	this->addChild(score_result, 4);
	score_result->setVisible(false);

	//gameover
	auto gameover = Sprite::create(RES_GAME_OVER);
	gameover->setScale(scaleX,scaleY);
	gameover->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	gameover->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height-10);
	gameover->setTag(TAG_OVER);
	gameover->setVisible(false);
	this->addChild(gameover,4);

	//sound banner
	auto sound_banner = Sprite::create(RES_SOUND_BANNER_O);
	sound_banner->setScale(scaleX,scaleY);
	sound_banner->setAnchorPoint(Point::ZERO);
	sound_banner->setPosition(origin.x+50, origin.y+floor->getContentSize().height*floor->getScaleY()+50);
	sound_banner->setTag(TAG_SOUND_BANNER);

//	auto s_b_o = Sprite::create(RES_SOUND_BANNER);
//	s_b_o->setTag(TAG_SOUND_BANNER_O);
//	s_b_o->setAnchorPoint(Point::ZERO);
    auto s_b_o = ProgressTimer::create(Sprite::create(RES_SOUND_BANNER));
    s_b_o->setType(ProgressTimer::Type::BAR);
    s_b_o->setMidpoint(Point(0,0));
    s_b_o->setBarChangeRate(Point(0, 1));
    s_b_o->setAnchorPoint(Point::ZERO);
	s_b_o->setTag(TAG_SOUND_BANNER_O);
    s_b_o->setPercentage(50);

	sound_banner->addChild(s_b_o,-1);

	sound_banner->setVisible(false);
	this->addChild(sound_banner,4);

	// update 
	scheduleUpdate();

	// touch
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(MainWorld::onTouchesEnded, this);
	listener->onTouchesBegan = CC_CALLBACK_2(MainWorld::onTouchesBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	initBird();
    return true;
}

void MainWorld::initBird()
{
	b_score = 0;
	auto scoreSprite = (Label*)this->getChildByTag(TAG_SCORE);
	Value s(b_score);
	scoreSprite->setString(s.getDescription());

	auto bird  = this->getChildByTag(TAG_BIRD);
	bird->setRotation(0);
	int i = rand()%4 + 1;
	Animation* an = Animation::create();
	if(1 == i)
	{
		an->addSpriteFrameWithFile(BIRD_RAND(1, 1));
		an->addSpriteFrameWithFile(BIRD_RAND(1, 2));
		an->addSpriteFrameWithFile(BIRD_RAND(1, 3));
	}
	else if(2 == i)
	{
		an->addSpriteFrameWithFile(BIRD_RAND(2, 1));
		an->addSpriteFrameWithFile(BIRD_RAND(2, 2));
		an->addSpriteFrameWithFile(BIRD_RAND(2, 3));
	}
	else if(3 == i)
	{
		an->addSpriteFrameWithFile(BIRD_RAND(3, 1));
		an->addSpriteFrameWithFile(BIRD_RAND(3, 2));
		an->addSpriteFrameWithFile(BIRD_RAND(3, 3));
	}
	else
	{
		an->addSpriteFrameWithFile(BIRD_RAND(4, 1));
		an->addSpriteFrameWithFile(BIRD_RAND(4, 2));
		an->addSpriteFrameWithFile(BIRD_RAND(4, 3));
	}
	an->setDelayPerUnit(BIRD_ANIM_S);
	an->setLoops(-1);
	Animate* anim = Animate::create(an);
	bird->runAction(anim);

	b_judge[0]=false;
	b_judge[1]=false;
	b_judge[2]=false;
	b_score = 0;

	if(b_gamestate == GAME_STATUS_READY || b_gamestate == GAME_STATUS_START)
	{
		auto a = MoveBy::create(0.5, Point(0,20));
		auto b = a->reverse();
		auto action = RepeatForever::create(Sequence::create(a,b,NULL));
		action->setTag(TAG_FLY);
		bird->runAction(action);
	}
}

void MainWorld::initGame()
{
	auto action1 = FadeTo::create(0.5f,255);
	auto action2 = FadeTo::create(0.5f, 0);
	if (this->b_gamestate == GAME_STATUS_GAME_END)
	{
		for (int i=0;i<3;++i)
		{
			pipelines_down[i]->setVisible(false);
			pipelines_up[i]->setVisible(false);
		}
		this->setPipes();
	}

	auto action = Sequence::create(action1, 
		CallFunc::create([&](){
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Point origin = Director::getInstance()->getVisibleOrigin();
			if(this->b_gamestate == GAME_STATUS_GAME_END)
			{
				this->initBird();
				this->getChildByTag(TAG_BIRD)->setPositionY(b_y);
			}
			this->getChildByTag(TAG_BIRD)->setPositionX(origin.x+visibleSize.width/4);
			this->getChildByTag(TAG_BIRD)->stopActionByTag(TAG_FLY);
			setStartMenuVisiable(false);
			if (b_moode == MODE_TOUCH)
			{
				this->getChildByTag(TAG_TAP)->setVisible(true);
			}
			else
			{
				this->getChildByTag(TAG_SOUND_BANNER)->setVisible(true);
				this->getChildByTag(TAG_SOUND)->setVisible(true);
			}
			this->getChildByTag(TAG_SCORE)->setVisible(true);
			this->b_gamestate = GAME_STATUS_PRE;
	}),action2,CallFunc::create([&](){
		auto layer = this->getChildByTag(TAG_COLOR);
		layer->setVisible(false);
	}) ,NULL);

	auto layer = this->getChildByTag(TAG_COLOR);
	layer->setOpacity(0);
	layer->setVisible(true);
	layer->runAction(action);
}

void MainWorld::gameNoice(Ref* pSender)
{
	b_moode = MODE_SOUND;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	startRecord();
#endif
	initGame();
}

void MainWorld::gameTouch(Ref* pSender)
{
	b_moode = MODE_TOUCH;
	initGame();
}

void MainWorld::gameready()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	this->getChildByTag(TAG_BIRD)->setPositionX(origin.x+visibleSize.width/4);	
	this->b_gamestate = GAME_STATUS_READY;
	auto action = Sequence::create(DelayTime::create(2.0f),										
		CallFunc::create(
		[&](){
			if(this->b_gamestate == GAME_STATUS_GAME_OVER)
				return;
			this->b_gamestate = GAME_STATUS_PLAYING;
			pipelines_up[0]->setVisible(true);
			pipelines_down[0]->setVisible(true);
			this->setPipes();
	}),NULL);

	this->runAction(action);
}

void MainWorld::setPipes()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto y = randh();
	auto h = pipelines_down[0]->getContentSize().height*pipelines_down[0]->getScaleY();
	pipelines_down[0]->setPosition(origin.x + visibleSize.width, origin.y+y-h);
	pipelines_up[0]->setPosition(origin.x + visibleSize.width, origin.y+y+MIN_UP_DOWN);

	y = randh();
	pipelines_down[1]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT, origin.y+y-h);
	pipelines_up[1]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT, origin.y+y+MIN_UP_DOWN);

	y = randh();

	pipelines_down[2]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT*2, origin.y+y-h);
	pipelines_up[2]->setPosition(origin.x + visibleSize.width + MIN_LEFT_RIGHT*2, origin.y+y+MIN_UP_DOWN);
}

void MainWorld::setStartMenuVisiable(bool isVisiable)
{
	this->getChildByTag(TAG_VOICE_BTN)->setVisible(isVisiable);
	this->getChildByTag(TAG_TOUCH_BTN)->setVisible(isVisiable);
	this->getChildByTag(TAG_RANK_BTN)->setVisible(isVisiable);
	this->getChildByTag(TAG_RATE_BTN)->setVisible(isVisiable);
	this->getChildByTag(TAG_LOGO)->setVisible(isVisiable);
	this->getChildByTag(TAG_OVER)->setVisible(isVisiable);
	this->getChildByTag(TAG_RESULT)->setVisible(isVisiable);
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
	case GAME_STATUS_PRE:
		updateFloor();
		updateBird();
		break;
	case GAME_STATUS_READY:
		updateFloor();
		updateBird();
		checkCollision();
		break;
	case GAME_STATUS_PLAYING:
		updateFloor();
		updatePipelines();
		updateBird();
		checkCollision();
		break;
	case GAME_STATUS_GAME_OVER:
		updateBird();
		break;
	case GAME_STATUS_GAME_END:
		break;
	}
}

void MainWorld::gameOver()
{
	if (b_moode == MODE_TOUCH)
	{
		this->getChildByTag(TAG_TAP)->setVisible(false);
	}
	else
	{
		this->getChildByTag(TAG_SOUND_BANNER)->setVisible(false);
		this->getChildByTag(TAG_SOUND)->setVisible(false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		stopRecord();
		b_sound = 0;
#endif
	}
	
	this->getChildByTag(TAG_SCORE)->setVisible(false);
	this->getChildByTag(TAG_VOICE_BTN)->setVisible(true);
	this->getChildByTag(TAG_RATE_BTN)->setVisible(true);
	this->getChildByTag(TAG_RANK_BTN)->setVisible(true);
	auto result = this->getChildByTag(TAG_RESULT);
	result->setVisible(true);
	this->getChildByTag(TAG_TOUCH_BTN)->setVisible(true);
	this->getChildByTag(TAG_OVER)->setVisible(true);
	result->getChildByTag(TAG_NEW)->setVisible(false);
	auto sc = (Label*)result->getChildByTag(TAG_SCORE1);
	Value s(b_score);
	sc->setString(s.getDescription());

	int score = UserDefault::getInstance()->getIntegerForKey("score");
	if(b_score>score)
	{
		UserDefault::getInstance()->setIntegerForKey("score",b_score);
		result->getChildByTag(TAG_NEW)->setVisible(true);
		auto scb = (Label*)result->getChildByTag(TAG_BEST);
		scb->setString(s.getDescription());
	}
}

void MainWorld::checkCollision()
{
	Sprite* bird = (Sprite*)this->getChildByTag(TAG_BIRD);
	Rect rect_o = bird->getBoundingBox();
	Rect rect = Rect(rect_o.getMinX()+4, rect_o.getMinY(), bird->getContentSize().width*bird->getScaleX()-8,bird->getContentSize().height*bird->getScaleY()-6);

	bool ao_f = rect.intersectsRect(this->getChildByTag(TAG_FLOOR_1)->getBoundingBox());
	bool ao_f2 = rect.intersectsRect(this->getChildByTag(TAG_FLOOR_2)->getBoundingBox());
	if(ao_f || ao_f2)
	{
		b_gamestate = GAME_STATUS_GAME_OVER;
		return;
	}
	for(int i=0;i<3;i++)
	{
		bool ao_u = rect.intersectsRect(pipelines_up[i]->getBoundingBox());
		bool ao_d = rect.intersectsRect(pipelines_down[i]->getBoundingBox());
		if(ao_u || ao_d)
		{
			b_gamestate = GAME_STATUS_GAME_OVER;
			break;
		}
	}
}

void MainWorld::updatePipelines()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto bird = this->getChildByTag(TAG_BIRD);
	for(int i=0;i<3;i++)
	{
		auto x = pipelines_up[i]->getPositionX();
		auto w = pipelines_up[i]->getContentSize().width*pipelines_up[i]->getScaleX();
		if(x+w<=0)
		{
			auto y = randh();
			auto h = pipelines_down[i]->getContentSize().height*pipelines_down[i]->getScaleY();
			auto f_x = i==0 ? pipelines_up[2]->getPositionX() : pipelines_up[i-1]->getPositionX();
			pipelines_down[i]->setPosition(f_x+MIN_LEFT_RIGHT, origin.y+y-h);
			pipelines_up[i]->setPosition(f_x+MIN_LEFT_RIGHT, origin.y+y+MIN_UP_DOWN);
			pipelines_down[i]->setVisible(false);
			pipelines_up[i]->setVisible(false);
			b_judge[i] = false;
			continue;
		}
		auto w2 = (w/2)+(bird->getContentSize().width*bird->getScaleX())/2;
		if(x <= (bird->getPositionX() - w2) && !b_judge[i])
		{
			b_judge[i] = true;
			++b_score;
			//log("score: %d", b_score);
			auto scoreSprite = (Label*)this->getChildByTag(TAG_SCORE);
			Value s(b_score);
			scoreSprite->setString(s.getDescription());
			//if(1 == b_score)
			//	scoreSprite->setPositionY(scoreSprite->getPositionY()+30);
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

float MainWorld::randh()
{
	auto floor_1 = this->getChildByTag(TAG_FLOOR_1);
	auto floor_h = floor_1->getContentSize().height*(floor_1->getScaleY());
	auto min_y = floor_h + (MIN_UP_DOWN/2);
	auto max_y = Director::getInstance()->getVisibleSize().height - (MIN_UP_DOWN*6/4);
	auto y = CCRANDOM_0_1()*(max_y - min_y) + min_y;
	int count = 0;
	while(abs((int)y - (int)dis)<=MIN_DIS && abs((int)y - (int)dis)>=MAX_DIS && count<=10)
	{
		y = CCRANDOM_0_1()*(max_y - min_y) + min_y;
		++count;
	}
	dis = y;
	return y;
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

void MainWorld::updateBird()
{
	auto bird  = this->getChildByTag(TAG_BIRD);
	if(this->b_gamestate == GAME_STATUS_GAME_OVER)
	{
		if(bird->getRotation()<45.0f)
		{
			b_velocity  =  BIRD_VELOCITY;
			bird->setRotation(45);
			bird->stopAllActions();
		}
		float h = (bird->getContentSize().height*bird->getScaleY())/2;
		float y = bird->getPositionY()-h;
		auto floor = this->getChildByTag(TAG_FLOOR_1);
		float y_f = floor->getContentSize().height*floor->getScaleY();
		if(y>y_f)
		{
			b_velocity -= BIRD_GRAVITY;
			bird->setPositionY(bird->getPositionY() + b_velocity);
		}
		else
		{
			bird->setPositionY(y_f);
			this->b_gamestate = GAME_STATUS_GAME_END;
			b_velocity  =  BIRD_VELOCITY;
			gameOver();
		}
	}
	else if(b_gamestate == GAME_STATUS_PRE)
	{

	}
	else
	{
		auto range = bird->getRotation();
		if(range<30)
			bird->setRotation(++range);
		b_velocity -= BIRD_GRAVITY;
		bird->setPositionY(bird->getPositionY() + b_velocity);
	}

	if (b_moode == MODE_SOUND)
	{
		updateSoundBanner();
	}
	
}

void MainWorld::updateSoundBanner()
{
	if (b_sound>0)
	{
		auto b = (Sprite*)this->getChildByTag(TAG_SOUND_BANNER);
		auto banner = (ProgressTimer*)b->getChildByTag(TAG_SOUND_BANNER_O);
		float height = b_sound-25.0f;
		height = height>80 ? 80 : height;
        banner->setPercentage(height*100/80);
<<<<<<< HEAD
//		Rect textureRect = banner->getTextureRect();
//		textureRect = Rect(textureRect.origin.x,textureRect.origin.y,textureRect.size.width,height);
//		banner->setTextureRect(textureRect,banner->isTextureRectRotated(),textureRect.size);
=======
>>>>>>> FETCH_HEAD
	}
}

void MainWorld::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
//	log("%s","touch began");
	if(b_gamestate == GAME_STATUS_READY || b_gamestate == GAME_STATUS_PLAYING)
	{
		if(b_moode != MODE_TOUCH) return;
		this->getChildByTag(TAG_BIRD)->setRotation(-30);
		b_velocity = BIRD_UP_VELOCITY;
	}
	else if(b_gamestate == GAME_STATUS_PRE)
	{
		if(b_moode != MODE_TOUCH) return;
		this->getChildByTag(TAG_TAP)->setVisible(false);
		this->gameready();
	}
}

void MainWorld::onTouchesEnded(const vector<Touch*>& touches, Event* event)
{
//	log("%s","touch end");
}


void MainWorld::SoundeHandler(float db)
{
//	log("sound: %f",db);
	if(b_sound<=0)
	{
		b_sound = db;
		return;
	}

	if(abs(db - b_sound)>MIN_DB && db > b_sound)
	{
		if(b_gamestate == GAME_STATUS_READY || b_gamestate == GAME_STATUS_PLAYING)
		{
			if(b_moode == MODE_TOUCH) return;
			this->getChildByTag(TAG_BIRD)->setRotation(-30);
			b_velocity = BIRD_UP_VELOCITY;
		}
		else if(b_gamestate == GAME_STATUS_PRE)
		{
			if(b_moode == MODE_TOUCH) return;
			this->getChildByTag(TAG_SOUND)->setVisible(false);
			this->gameready();
		}
	}
	b_sound = db;
}