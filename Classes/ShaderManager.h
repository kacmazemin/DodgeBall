//
// Created by emin on 31.01.2021.
//

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "cocos2d.h"

class ShaderManager
{
public:
    static ShaderManager* getInstance();

    cocos2d::GLProgram* getOrCreateGLProgram(const std::string& path);

    void removeShaderFromNode(cocos2d::Node* node);
};


#endif //SHADERMANAGER_H
