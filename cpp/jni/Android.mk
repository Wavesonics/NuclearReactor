# Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := godot-prebuilt
LOCAL_SRC_FILES := ../godot-cpp/bin/libgodot-cpp.android.release.arm64v8.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := nuclear-physics
LOCAL_CPPFLAGS := -std=c++17
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_CFLAGS := -w
LOCAL_LDLIBS := -llog

LOCAL_SRC_FILES := \
../src/init.cpp \
../src/util/Utils.cpp \
../src/actors/ControlRod.cpp \
../src/actors/FuelRod.cpp \
../src/actors/HeatMap.cpp \
../src/actors/Moderator.cpp \
../src/actors/Neutron.cpp \
../src/actors/NeutronField.cpp \
../src/actors/NeutronRegion.cpp \
../src/actors/ReactorCore.cpp

#LOCAL_SHARED_LIBRARIES := 

LOCAL_C_INCLUDES := \
godot-cpp/godot_headers \
godot-cpp/include/ \
godot-cpp/include/core \
godot-cpp/include/gen

LOCAL_STATIC_LIBRARIES := godot-prebuilt

NDK_LIBS_OUT=../bin/$(TARGET_ARCH_ABI)

include $(BUILD_SHARED_LIBRARY)