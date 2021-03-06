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
../src/actors/HeatMap/HeatMap.cpp \
../src/actors/HeatMap/DiffusingHeatMap.cpp \
../src/actors/NeutronRegion/NeutronRegion.cpp \
../src/actors/NeutronRegion/ControlRod/ControlRod.cpp \
../src/actors/NeutronRegion/FuelRod/FuelRod.cpp \
../src/actors/NeutronRegion/Moderator/Moderator.cpp \
../src/actors/NeutronRegion/ReactorCore/ReactorCore.cpp \
../src/actors/NeutronField/Neutron.cpp \
../src/actors/NeutronField/BspTree/BspTreeNode.cpp \
../src/actors/NeutronField/BspTree/BspTree.cpp \
../src/actors/NeutronField/BatchResult.cpp \
../src/actors/NeutronField/NeutronField.cpp \
../src/actors/Sensors/Thermocouple/Thermocouple.cpp

#LOCAL_SHARED_LIBRARIES := 

LOCAL_C_INCLUDES := \
godot-cpp/godot_headers \
godot-cpp/include/ \
godot-cpp/include/core \
godot-cpp/include/gen

LOCAL_STATIC_LIBRARIES := godot-prebuilt

include $(BUILD_SHARED_LIBRARY)