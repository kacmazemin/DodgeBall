//
// Created by emin on 26.01.2021.
//

#include "Board.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2EdgeShape.h"
#include "Physics/PhysicsManager.h"
#include "Pocket.h"
#include "../Utils/ScreenUtils.h"
#include "Ball.h"

Board::Board(b2World &world) : world(&world)
{
    cocos2d::Node::init();
    autorelease();

    createTableSprite();
    createPhysicEdges();
    createPockets();
}

void Board::createTableSprite()
{
    tableSprite = cocos2d::Sprite::create("textures/table.png");

    ScreenUtils::fitH(tableSprite, ScreenUtils::getVisibleRect().size.height * .8f);

    addChild(tableSprite);
}

void Board::createPhysicEdges()
{
    const cocos2d::Rect tableBB = tableSprite->getBoundingBox();
    const float offsetX = tableBB.size.width * .0675f;
    const float offsetY = tableBB.size.height * .12f;
    const float spaceL = tableBB.size.height * .068f;
    const float spaceR = tableBB.size.height * .048f;
    const float cornerSpace = tableBB.size.height * .062f;

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0,0); // bottom-left corner

    groundBody = world->CreateBody(&groundBodyDef);
    // Define the ground box shape.
    b2EdgeShape groundBox;

    //counterclockwise
    // bottom left
    groundBox.Set(b2Vec2((tableBB.getMinX() + offsetX + cornerSpace) / PTM_RATIO, (tableBB.getMinY() + offsetY) / PTM_RATIO),
                  b2Vec2((tableBB.getMidX() - spaceL) / PTM_RATIO, (tableBB.getMinY() + offsetY ) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // bottom right
    groundBox.Set(b2Vec2((tableBB.getMidX() + spaceR) / PTM_RATIO, (tableBB.getMinY() + offsetY) / PTM_RATIO),
                  b2Vec2((tableBB.getMaxX() - offsetX - cornerSpace) / PTM_RATIO, (tableBB.getMinY() + offsetY) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // top left
    groundBox.Set(b2Vec2((tableBB.getMinX() + offsetX + cornerSpace) / PTM_RATIO, (tableBB.getMaxY() - offsetY) / PTM_RATIO),
                  b2Vec2((tableBB.getMidX() - spaceL) / PTM_RATIO, (tableBB.getMaxY()- offsetY) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // top right
    groundBox.Set(b2Vec2((tableBB.getMidX() + spaceR) / PTM_RATIO, (tableBB.getMaxY() - offsetY) / PTM_RATIO),
                  b2Vec2((tableBB.getMaxX() - offsetX - cornerSpace) / PTM_RATIO, (tableBB.getMaxY()- offsetY) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2((tableBB.getMinX() + offsetX) / PTM_RATIO, (tableBB.getMaxY() - offsetY - cornerSpace) / PTM_RATIO),
                  b2Vec2((tableBB.getMinX() + offsetX) / PTM_RATIO, (tableBB.getMinY() + offsetY + cornerSpace) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2((tableBB.getMaxX() - offsetX) / PTM_RATIO, (tableBB.getMinY() + offsetY + cornerSpace) / PTM_RATIO),
                  b2Vec2((tableBB.getMaxX() - offsetX ) / PTM_RATIO, (tableBB.getMaxY() - offsetY - cornerSpace) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

}

void Board::changePhysicsPosition(const cocos2d::Vec2& position)
{
    groundBody->SetTransform(b2Vec2( position.x / PTM_RATIO, position.y / PTM_RATIO), groundBody->GetAngle());
}

void Board::createPockets()
{
    const cocos2d::Rect tableBB = tableSprite->getBoundingBox();

    const float offset = tableBB.size.height * .09f;
    const float startX = tableBB.getMinX() + offset;
    const float topPocketsY = tableBB.getMaxY() - offset;

    const float distanceX = (tableBB.size.width - (offset * 2)) * .5f;
    const float distanceY = tableBB.size.height -  (offset * 2);

    for (int i = 0; i < 2 ; i++)
    {
        for (int j = 0; j < 3 ; j++)
        {
            auto* pocket = new Pocket(*world,
                    cocos2d::Vec2{startX + (j * distanceX), topPocketsY - (distanceY * i)});
            pockets.emplace_back(pocket);
            addChild(pocket);
        }
    }

    pockets[1]->addOffset(cocos2d::Vec2{-offset * .15f, offset * .3f});
    pockets[4]->addOffset(cocos2d::Vec2{-offset * .15f, -offset * .3f});
}
