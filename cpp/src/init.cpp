#include <Godot.hpp>
#include "actors/NeutronField.h"
#include "actors/NeutronRegion.h"
#include "actors/ControlRod.h"
#include "actors/FuelRod.h"
#include "actors/Moderator.h"


extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<nuclearPhysics::NeutronField>();
    godot::register_class<nuclearPhysics::ControlRod>();
    godot::register_class<nuclearPhysics::FuelRod>();
    godot::register_class<nuclearPhysics::Moderator>();
    godot::register_class<nuclearPhysics::Area2d>();
}