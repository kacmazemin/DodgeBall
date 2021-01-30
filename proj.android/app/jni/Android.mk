LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameLayer.cpp \
                   $(LOCAL_PATH)/../../../Classes/Utils/GLES-Renderer.cpp \
                   $(LOCAL_PATH)/../../../Classes/Utils/ScreenUtils.cpp \
                   $(LOCAL_PATH)/../../../Classes/MenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Physics/PhysicsManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/Physics/SpriteWithPhysics.cpp \
                   $(LOCAL_PATH)/../../../Classes/Physics/ContactListener.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameComponents/Ball.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameComponents/BilliardCue.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameComponents/GhostCue.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameComponents/Board.cpp \
                   $(LOCAL_PATH)/../../../Classes/UI/CuePanel.cpp \
                   $(LOCAL_PATH)/../../../Classes/UI/LoadingNode.cpp \
                   $(LOCAL_PATH)/../../../Classes/UI/BallChartNode.cpp \
                   $(LOCAL_PATH)/../../../Classes/UI/RemainingShootNode.cpp \
                   $(LOCAL_PATH)/../../../Classes/UI/AnnouncerNode.cpp \
                   $(LOCAL_PATH)/../../../Classes/UI/CustomButton.cpp \
                   $(LOCAL_PATH)/../../../Classes/AudioManager.cpp




LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cc_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
