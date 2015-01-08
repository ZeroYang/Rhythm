#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;
CCScene* HelloWorld::scene() {
	CCScene *scene = CCScene::create();

	HelloWorld *layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}
void HelloWorld::toGameLayer(CCObject* pSender) {
	SimpleAudioEngine::sharedEngine()->playEffect("music/mode_select_02.wav");
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = Game4Key::scene();
	// run
	pDirector->replaceScene(pScene);
}

bool HelloWorld::init() {
	//////////////////////////////

	if (!CCLayer::init()) {
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
			"anim/key_press.png", "anim/key_press.plist",
			"anim/key_press.ExportJson");

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("background.plist", "background.png");
	cache->addSpriteFramesWithFile("button/button.plist", "button/button.png");
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", this,
			menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(
			ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
					origin.y + pCloseItem->getContentSize().height/2));

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCLabelTTF* pLabel = CCLabelTTF::create("节奏大师", "Arial", TITLE_FONT_SIZE);

	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height - pLabel->getContentSize().height+20));

	this->addChild(pLabel, 1);
	CCSprite* pSprite = CCSprite::createWithSpriteFrameName("bg2.png");

	pSprite->setPosition(
			ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	this->addChild(pSprite, 0);
	m_emitter = CCParticleFireworks::create();
	m_emitter->retain();
	pSprite->addChild(m_emitter, 10);

	pSprite->setTexture(
			CCTextureCache::sharedTextureCache()->addImage("images/fire.png"));

	m_emitter->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	CCSprite* key4SpriteButton = CCSprite::createWithSpriteFrameName(
			"key_button_4.png");

	CCSprite* key5SpriteButton = CCSprite::createWithSpriteFrameName(
			"key_button_5.png");
	CCSprite* key6SpriteButton = CCSprite::createWithSpriteFrameName(
			"key_button_6.png");
	CCMenuItemSprite* game4KeyMenu = CCMenuItemSprite::create(key4SpriteButton,
		key4SpriteButton, key4SpriteButton, this,
		menu_selector(HelloWorld::toGameLayer));
	
	CCMenuItemSprite* game5KeyMenu = CCMenuItemSprite::create(key5SpriteButton,
			key5SpriteButton, key5SpriteButton, this,
			menu_selector(HelloWorld::toGameLayer));
	CCMenuItemSprite* game6KeyMenu = CCMenuItemSprite::create(key6SpriteButton,
			key6SpriteButton, key6SpriteButton, this,
			menu_selector(HelloWorld::toGameLayer));
	CCMenu* menu = CCMenu::create(game4KeyMenu, game5KeyMenu, game6KeyMenu,
			NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 1);
	menu->setPosition(ccp(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height/2));

//	CCSprite* long_ud = CCSprite::createWithSpriteFrameName(
//				"long_ud.png");
//	long_ud->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//	addChild(long_ud,10);
//	long_ud->setScaleY(500);



	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
			"music/title_bgm.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect(
			"music/mode_select_02.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect(
			"music/music_select_01.wav");
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
		CCLOG("background music is playing");
	} else {
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
				"music/title_bgm.mp3", true);
		CCLOG("background music is not playing");
	}
	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
