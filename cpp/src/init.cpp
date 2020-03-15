#include <Godot.hpp>
#include "actors/NeutronField/NeutronField.h"
#include "actors/NeutronRegion/ControlRod/ControlRod.h"
#include "actors/NeutronRegion/FuelRod/FuelRod.h"
#include "actors/NeutronRegion/Moderator/Moderator.h"
#include "actors/NeutronRegion/ReactorCore/ReactorCore.h"
#include "actors/HeatMap/HeatMap.h"
#include "actors/HeatMap/DiffusingHeatMap.h"
#include "actors/Sensors/Thermocouple/Thermocouple.h"


extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    
    godot::register_class<nuclearPhysics::NeutronField>();
    godot::register_class<nuclearPhysics::ReactorCore>();
    godot::register_class<nuclearPhysics::ControlRod>();
    godot::register_class<nuclearPhysics::FuelRod>();
    godot::register_class<nuclearPhysics::Moderator>();
    godot::register_class<nuclearPhysics::HeatMap>();
    godot::register_class<nuclearPhysics::DiffusingHeatMap>();
	godot::register_class<nuclearPhysics::Thermocouple>();
}