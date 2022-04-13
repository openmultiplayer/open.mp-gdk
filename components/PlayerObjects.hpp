#pragma once
#include "../main.hpp"
#include "./common.hpp"

namespace ompgdk
{
	inline int CreatePlayerObject(int playerid, int modelid, float x, float y, float z, float rotx, float roty, float rotz, float drawDistance)
	{
		IPlayerObjectData* data = GetPlayerData<IPlayerObjectData>(playerid);
		if (data)
		{
			IPlayerObject* object = data->create(modelid, { x, y, z }, { rotx, roty, rotz }, drawDistance);
			if (object)
			{
				return object->getID();
			}
		}
		return INVALID_OBJECT_ID;
	}

	inline bool DestroyPlayerObject(int playerid, int objectid)
	{
		IPlayerObjectData* data = GetPlayerData<IPlayerObjectData>(playerid);
		if (data->get(objectid))
		{
			data->release(objectid);
			return true;
		}
		return false;
	}

	inline bool AttachPlayerObjectToVehicle(int playerid, int objectid, int vehicleid, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		IVehicle* vehicle = GetEntity<IVehicle>(vehicleid);
		if (vehicle)
		{
			object->attachToVehicle(*vehicle, { offsetX, offsetY, offsetZ }, { rotX, rotY, rotZ });
		}
		else
		{
			object->resetAttachment();
		}
		return true;
	}

	inline bool AttachPlayerObjectToPlayer(int playerid, int objectid, int playeridAttachedTo, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		if (GDKManager::Get()->GetCore())
		{
			GDKManager::Get()->GetCore()->logLn(LogLevel::Warning, "This native was removed from sa-mp, we do not support it either (yet)");
		}
		return false;
	}

	inline bool AttachPlayerObjectToObject(int playerid, int objectid, int attachedToId, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		GET_PLAYER_OBJECT_CHECKED(attachedTo, playerid, attachedToId, false);

		object->attachToObject(*attachedTo, { offsetX, offsetY, offsetZ }, { rotX, rotY, rotZ });
		return true;
	}

	inline bool SetPlayerObjectPos(int playerid, int objectid, float x, float y, float z)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		object->setPosition({ x, y, z });
		return true;
	}

	inline bool GetPlayerObjectPos(int playerid, int objectid, float* x, float* y, float* z)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		Vector3 position = object->getPosition();
		*x = position.x;
		*y = position.y;
		*z = position.z;
		return true;
	}

	inline bool SetPlayerObjectRot(int playerid, int objectid, float rotX, float rotY, float rotZ)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		object->setRotation(Vector3(rotX, rotY, rotZ));
		return true;
	}

	inline bool GetPlayerObjectRot(int playerid, int objectid, float* x, float* y, float* z)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		Vector3 rotation = object->getRotation().ToEuler();
		*x = rotation.x;
		*y = rotation.y;
		*z = rotation.z;
		return true;
	}

	inline int GetPlayerObjectModel(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, INVALID_OBJECT_MODEL_ID);
		return object->getModel();
	}

	inline bool SetPlayerObjectNoCameraCol(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		object->setCameraCollision(false);
		return true;
	}

	inline bool IsValidPlayerObject(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		return true;
	}

	inline bool MovePlayerObject(int playerid, int objectid, float x, float y, float z, float speed, float rotX, float rotY, float rotZ)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		ObjectMoveData data;
		data.targetPos = { x, y, z };
		data.targetRot = { rotX, rotY, rotZ };
		data.speed = speed;

		object->move(data);
		return true;
	}

	inline bool StopPlayerObject(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		object->stop();
		return true;
	}

	inline bool IsPlayerObjectMoving(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		return object->isMoving();
	}

	inline bool EditPlayerObject(int playerid, int objectid)
	{
		IPlayer* player = GetPlayer(playerid);
		if (player == nullptr)
		{
			return false;
		}

		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		IPlayerObjectData* playerData = queryExtension<IPlayerObjectData>(*player);
		if (playerData)
		{
			playerData->beginEditing(*object);
			return true;
		}
		return false;
	}

	inline bool SetPlayerObjectMaterial(int playerid, int objectid, int materialIndex, int modelId, const char* txdName, const char* textureName, uint32_t materialcolor)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		object->setMaterial(materialIndex, modelId, txdName, textureName, Colour::FromARGB(materialcolor));
		return true;
	}

	inline bool SetPlayerObjectMaterialText(int playerid, int objectid, const char* text, int materialindex, int materialsize, const char* fontface, int fontsize, bool bold, uint32_t fontcolor, uint32_t backcolor, int textalignment)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		object->setMaterialText(materialindex, text, ObjectMaterialSize(materialsize), fontface, fontsize, bold, Colour::FromARGB(fontcolor), Colour::FromARGB(backcolor), ObjectMaterialTextAlign(textalignment));
		return true;
	}

	inline float GetPlayerObjectDrawDistance(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, 0.0f);
		return object->getDrawDistance();
	}

	inline float GetPlayerObjectMoveSpeed(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, 0.0f);
		return object->getMovingData().speed;
	}

	inline bool GetPlayerObjectMovingTargetPos(int playerid, int objectid, float* x, float* y, float* z)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		const ObjectMoveData& data = object->getMovingData();
		Vector3 pos = data.targetPos;
		*x = pos.x;
		*y = pos.y;
		*z = pos.z;
		return true;
	}

	inline bool GetPlayerObjectTarget(int playerid, int objectid, float* x, float* y, float* z)
	{
		return ompgdk::GetPlayerObjectMovingTargetPos(playerid, objectid, x, y, z);
	}

	inline bool GetPlayerObjectMovingTargetRot(int playerid, int objectid, float* x, float* y, float* z)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		const ObjectMoveData& data = object->getMovingData();
		Vector3 rot = data.targetRot;
		*x = rot.x;
		*y = rot.y;
		*z = rot.z;
		return true;
	}

	inline bool GetPlayerObjectAttachedData(int playerid, int objectid, int* attached_vehicleid, int* attached_objectid, int* attached_playerid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		const ObjectAttachmentData data = object->getAttachmentData();
		*attached_vehicleid = INVALID_VEHICLE_ID;
		*attached_objectid = INVALID_OBJECT_ID;
		*attached_playerid = INVALID_PLAYER_ID;

		if (data.type == ObjectAttachmentData::Type::Object)
		{
			*attached_objectid = data.ID;
		}
		else if (data.type == ObjectAttachmentData::Type::Player)
		{
			*attached_playerid = data.ID;
		}
		else if (data.type == ObjectAttachmentData::Type::Vehicle)
		{
			*attached_vehicleid = data.ID;
		}

		return true;
	}

	inline bool GetPlayerObjectAttachedOffset(int playerid, int objectid, float* x, float* y, float* z, float* rx, float* ry, float* rz)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		const ObjectAttachmentData data = object->getAttachmentData();
		Vector3 offset = data.offset;
		Vector3 rot = data.rotation;

		*x = offset.x;
		*y = offset.y;
		*z = offset.z;

		*rx = rot.x;
		*ry = rot.y;
		*rz = rot.z;
		return true;
	}

	inline int GetPlayerObjectSyncRotation(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		return object->getAttachmentData().syncRotation;
	}

	inline bool IsPlayerObjectMaterialSlotUsed(int playerid, int objectid, int materialindex)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		const ObjectMaterialData* data = nullptr;
		bool result = object->getMaterialData(materialindex, data);
		if (result)
		{
			return data->used;
		}
		return result;
	}

	inline bool GetPlayerObjectMaterial(int playerid, int objectid, int materialindex, int* modelid, char* txdname, int size)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		const ObjectMaterialData* data = nullptr;
		bool result = object->getMaterialData(materialindex, data);
		if (result)
		{
			memcpy(txdname, data->textOrTXD.data(), size);
			txdname[size - 1] = '\0';
			*modelid = object->getModel();
		}
		return result;
	}

	inline bool GetPlayerObjectMaterialText(int playerid, int objectid, int materialindex, char* text, int size)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		const ObjectMaterialData* data = nullptr;
		bool result = object->getMaterialData(materialindex, data);
		if (result)
		{
			memcpy(text, data->textOrTXD.data(), size);
			text[size - 1] = '\0';
		}
		return result;
		return result;
	}

	inline bool IsPlayerObjectNoCameraCol(int playerid, int objectid)
	{
		GET_PLAYER_OBJECT_CHECKED(object, playerid, objectid, false);
		return !object->getCameraCollision();
	}

	inline int GetPlayerSurfingPlayerObjectID(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, INVALID_OBJECT_ID);
		const PlayerSurfingData& data = player->getSurfingData();
		if (data.type == PlayerSurfingData::Type::PlayerObject)
		{
			return data.ID;
		}
		else 
		{
			return INVALID_OBJECT_ID;
		}
	}

	inline int GetPlayerCameraTargetPlayerObj(int playerid)
	{
		GET_PLAYER_CHECKED(player, playerid, INVALID_OBJECT_ID);
		IObject* object = player->getCameraTargetObject();
		if (object)
		{
			return object->getID();
		}
		else 
		{
			return INVALID_OBJECT_ID;
		}
	}
}
