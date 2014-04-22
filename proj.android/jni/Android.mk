LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libbird

LOCAL_SRC_FILES := bird/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/Sound.cpp \
                   ../../Classes/BirdJni.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
