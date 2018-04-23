//
//  CustomButton.cpp
//  Template
//
//  Created by Bilal Mirza on 10/09/2017.
//
//

#include "CustomButton.h"

namespace  {
    const float OFFSET_Y = 16.0f;
    const float TOUCH_ANIMATION_SPEED = 0.04f;
    const float BASE_COLOR_MULTIPLIER = 0.7f;
}

namespace UICustom {
    
    CustomButton* CustomButton::createButton(const std::string &fileName, const Color3B CustomButtonColor, const std::function<void (Ref *)> &YesFunc)
    {
        return CustomButton::create(fileName, CustomButtonColor, nullptr, YesFunc);
    }

    CustomButton* CustomButton::create(const std::string &fileName, const Color3B CustomButtonColor,cocos2d::Sprite *icon, const std::function<void (Ref *)> &YesFunc)
    {
        CustomButton *node = new (std::nothrow)CustomButton();
        if(node)
        {
            node->initCustomButton(fileName);
            node->_mainSprite->setColor(CustomButtonColor);
            node->_mainFunc = YesFunc;
            
            if(icon)
            {
                node->initIcon(icon);
            }
            node->init();
            node->autorelease();
            return node;
        }
        
        CC_SAFE_DELETE(node);
        return nullptr;
    }


    bool CustomButton::init()
    {

        
        _base = Sprite::createWithTexture(_mainSprite->getTexture());
        this->addChild(_base,-1);
        
        float  newR = _mainSprite->getColor().r * (BASE_COLOR_MULTIPLIER);
        float  newG = _mainSprite->getColor().g * (BASE_COLOR_MULTIPLIER);
        float  newB = _mainSprite->getColor().b * (BASE_COLOR_MULTIPLIER);
        _base->setColor(Color3B(newR,newG,newB));
        
        
        _shadow = Sprite::createWithTexture(_mainSprite->getTexture());
        _shadow->setOpacity(50);
        _shadow->setColor(Color3B::BLACK);
        _shadow->setPositionY(-OFFSET_Y);
        this->addChild(_shadow,-2);
        
        
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->onTouchBegan = [=](Touch* touch, Event* event){
            if(this->getBoundingBoxOfImage().containsPoint(touch->getLocation()) && _isEnabled)
            {
                this->onTouchDown();
            }
            return true;
        };
        listener->onTouchMoved = [=](Touch* touch, Event* event){
            if(this->getBoundingBoxOfImage().containsPoint(touch->getLocation()) && _didTouchDown == false && _isEnabled)
            {
                this->onTouchDown();
            }
            
            if(this->getBoundingBoxOfImage().containsPoint(touch->getLocation()) == false && _didTouchDown == true && _isEnabled)
            {
                this->onTouchUp();
            }
            

            return true;
        };
        listener->onTouchEnded = [=](Touch* touch, Event* event){
            if(this->getBoundingBoxOfImage().containsPoint(touch->getLocation()) && _isEnabled )
            {
                this->onTouchUp();
                _mainFunc(this);
            }
            if(_didTouchDown)
            {
                this->onTouchUp();
            }
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        this->scheduleUpdate();

        return true;
    }

    void CustomButton::initCustomButton(const std::string &fileName)
    {
        _mainSprite = Sprite::create(fileName);
        this->addChild(_mainSprite,3);
        _mainSprite->setPositionY(OFFSET_Y);
    }

    void CustomButton::initIcon(cocos2d::Sprite *icon)
    {
        _icon = icon;
        _mainSprite->addChild(_icon);
        _icon->setPosition(_mainSprite->getContentSize()/2);
    }

    void CustomButton::onTouchDown()
    {
        _mainSprite->stopAllActions();
        _mainSprite->runAction(MoveTo::create(TOUCH_ANIMATION_SPEED, Point(0,OFFSET_Y/3)));
        _didTouchDown = true;
    }
    void CustomButton::onTouchUp()
    {
        
        _mainSprite->stopAllActions();
        _mainSprite->runAction(JumpTo::create(TOUCH_ANIMATION_SPEED * 2.5f , Point(0,OFFSET_Y), OFFSET_Y, 1));
        _didTouchDown = false;
    }

    const Rect CustomButton::getBoundingBoxOfImage() const
    {
        
        Rect a = Rect(this->getPosition().x + _mainSprite->getPosition().x - _mainSprite->getContentSize().width/2, this->getPosition().y + _mainSprite->getPosition().y - _mainSprite->getContentSize().height/2, _mainSprite->getBoundingBox().size.width, _mainSprite->getBoundingBox().size.height);
        return a;
    }

    void CustomButton::update(float dt)
    {
        _shadow->setPositionY(-_mainSprite->getPosition().y);
    }
    
    void CustomButton::setEnable(const bool enable)
    {
        _isEnabled = enable;
        if(_isEnabled)
        {
            _mainSprite->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
            _base->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
            
            if(_icon)
            {
                _icon->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
            }
        }
        else{
            _mainSprite->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_GRAYSCALE));
            _base->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_GRAYSCALE));
            if(_icon)
            {
                _base->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_GRAYSCALE));
            }
        }
    }


}
