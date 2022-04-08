#pragma once
#include "../main.hpp"
#include "./common.hpp"

namespace ompgdk
{
    inline bool GetObjectPos(int objectid, float* x, float* y, float* z)
    {
        GET_ENTITY_CHECKED(object, IObject, objectid, false);
        Vector3 position = object->getPosition();
        *x = position.x;
        *y = position.y;
        *z = position.z;
        return true;
    }

    inline bool GetObjectRot(int objectid, float* rx, float* ry, float* rz)
    {
        GET_ENTITY_CHECKED(object, IObject, objectid, false);
        Vector3 rotation = object->getRotation().ToEuler();
        *rx = rotation.x;
        *ry = rotation.y;
        *rz = rotation.z;
        return true;
    }
}
