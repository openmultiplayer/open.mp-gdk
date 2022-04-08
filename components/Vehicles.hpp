#pragma once
#include "../main.hpp"

namespace ompgdk
{
	inline bool GetVehiclePos(int vehicleid, float* x, float* y, float* z)
	{
		GET_ENTITY_CHECKED(vehicle, IVehicle, vehicleid, false);
		Vector3 pos = vehicle->getPosition();
		*x = pos.x;
		*y = pos.y;
		*z = pos.z;
		return true;
	}

	inline bool GetVehicleVelocity(int vehicleid, float* x, float* y, float* z)
	{
		GET_ENTITY_CHECKED(vehicle, IVehicle, vehicleid, false);
		Vector3 velocity = vehicle->getVelocity();
		*x = velocity.x;
		*y = velocity.y;
		*z = velocity.z;
		return true;
	}

	inline bool GetVehicleZAngle(int vehicleid, float* angle)
	{
		GET_ENTITY_CHECKED(vehicle, IVehicle, vehicleid, false);
		*angle = vehicle->getZAngle();
		return true;
	}

	inline bool GetVehicleRotationQuat(int vehicleid, float* w, float* x, float* y, float* z)
	{
		GET_ENTITY_CHECKED(vehicle, IVehicle, vehicleid, false);
		GTAQuat quat = vehicle->getRotation();
		*w = quat.q.w;
		*x = quat.q.x;
		*y = quat.q.y;
		*z = quat.q.z;
		return true;
	}

	inline int GetVehicleVirtualWorld(int vehicleid)
	{
		GET_ENTITY_CHECKED(vehicle, IVehicle, vehicleid, 0);
		return vehicle->getVirtualWorld();
	}

}