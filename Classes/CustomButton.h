//
//  CustomButton.h
//  Template
//
//  Created by Bilal Mirza on 10/09/2017.
//
//

#ifndef CustomButton_h
#define CustomButton_h

#include <stdio.h>

USING_NS_CC;

/*
-includes CustomButton of different kind
-draws the CustomButtons

*/
namespace UICustom{

    namespace CUSTOM_BUTTON_IMAGES {
        const std::string SQUARE = "res/Square.png";
        const std::string CIRCLE = "res/Circle.png";
        const std::string TRIANGLE = "res/Triangle.png";
    }


    namespace COLOR{
        const cocos2d::Color3B RED = Color3B(236, 95, 103);
        const cocos2d::Color3B ORANGE = Color3B(249, 145, 87);
        const cocos2d::Color3B YELLOW = Color3B(250, 200, 99);
        const cocos2d::Color3B GREEN = Color3B(153, 199, 148);
        const cocos2d::Color3B SEAGREEN = Color3B(95, 179, 179);
        const cocos2d::Color3B BLUE = Color3B(102, 153, 204);
        const cocos2d::Color3B PURPLE = Color3B(197, 148, 197);
        const cocos2d::Color3B BROWN = Color3B(171, 121, 103);
        const cocos2d::Color3B PINK = Color3B(236, 95, 157);
        const cocos2d::Color3B AQUA = Color3B(95, 211, 236);
        const cocos2d::Color3B PARROTGREEN = Color3B(142, 236, 95);
        const cocos2d::Color3B LIME = Color3B(236, 224, 95);
        const cocos2d::Color3B BLUE_PURPLE = Color3B(118, 95, 236);
        const cocos2d::Color3B CREAM = Color3B(247, 200, 212);
        const cocos2d::Color3B GRAY = Color3B(101, 115, 126);
    }

    class CustomButton : public cocos2d::Node
    {
        
    public:
        
        static CustomButton* createButton(const std::string &fileName, const Color3B CustomButtonColor, const std::function<void (Ref *)> &YesFunc);
        static CustomButton* create(const std::string &fileName, const Color3B CustomButtonColor,cocos2d::Sprite *icon, const std::function<void (Ref *)> &YesFunc);

        const Color3B getCustomButtonColor() const {return _mainSprite->getColor();}
     
        virtual void setEnable(const bool enable);
        
        
    private:
        virtual bool init();
        void initCustomButton(const std::string &fileName);
        void initIcon(cocos2d::Sprite *icon);
        void initColor();
        void update(float dt);
        const cocos2d::Rect getBoundingBoxOfImage() const;

        bool getIsTouchDown() const { return _didTouchDown;}
        void onTouchDown();
        void onTouchUp();
        
        
        std::function<void (Ref *)> _mainFunc;
        
        cocos2d::Sprite *_mainSprite = nullptr;
        cocos2d::Sprite *_base = nullptr;
        cocos2d::Sprite *_shadow = nullptr;
        cocos2d::Sprite *_icon = nullptr;
        
        bool _didTouchDown = false;
        bool _isEnabled = true;
        

    };
}

#endif /* CustomButton_h */
