# CustomButton
A cocos2d-x class that allows you to create cool animated buttons.

![Alt Text](https://media.giphy.com/media/47G2v61yDytCGp7FkB/giphy.gif)

Usage:


```
UICustom::CustomButton *cb = UICustom::CustomButton::create(UICustom::CUSTOM_BUTTON_IMAGES::SQUARE, UICustom::COLOR::GREEN, nullptr, [=](Ref *sender){
    
    log("Button pressed");
});
this->addChild(cb);
```

