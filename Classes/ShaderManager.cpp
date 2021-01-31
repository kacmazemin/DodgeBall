//
// Created by emin on 31.01.2021.
//

#include "ShaderManager.h"

static ShaderManager* sharedInstance = nullptr;

ShaderManager* ShaderManager::getInstance() {

    if (! sharedInstance)
    {
        sharedInstance = new ShaderManager();
    }

    return sharedInstance;
}

cocos2d::GLProgram *ShaderManager::getOrCreateGLProgram(const std::string& path)
{
    auto shader = cocos2d::GLProgram::createWithFilenames("shaders/" + path + ".vert", "shaders/" + path + ".frag");

    shader->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
    shader->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_COLOR, cocos2d::GLProgram::VERTEX_ATTRIB_COLOR);
    shader->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORDS);

    shader->link();

    return shader;
}

void ShaderManager::removeShaderFromNode(cocos2d::Node* node)
{
    if(node)
    {
        node->setGLProgramState(
                cocos2d::GLProgramState::getOrCreateWithGLProgramName(
                cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    }
}

