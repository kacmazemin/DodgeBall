//
// Created by emin on 23.01.2021.
//

#ifndef _GAMELAYER_H
#define _GAMELAYER_H

#include "cocos2d.h"
#include "GLES-Render.h"
#include "Box2D/Box2D.h"


class GameLayer : public cocos2d::Scene{

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);

private:

    b2World* world = nullptr;
    b2Body* body = nullptr;
    b2Body* body2 = nullptr;
    b2Body* groundBody = nullptr;
    b2Vec2 gravity = b2Vec2(0, -9.8f);

    GLESDebugDraw* debugDraw = nullptr;


    void update(float dt);
    void RenderDebug();

    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);


};


#endif //_GAMELAYER_H
