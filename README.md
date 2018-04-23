# CustomButton
A cocos2d-x class that allows you to create cool animated buttons.


Usage:


'''
UICustom::CustomButton *cb = UICustom::CustomButton::create(UICustom::CUSTOM_BUTTON_IMAGES::SQUARE, UICustom::COLOR::GREEN, nullptr, [=](Ref *sender){
    
    log("Button pressed");
});
this->addChild(cb);
'''
