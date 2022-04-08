#pragma once
#include "../main.hpp"

namespace ompgdk
{
	inline int CreateActor(int modelid, float x, float y, float z, float rotation)
	{
		IActorsComponent* component = GDKManager::Get()->GetActors();
		if (component)
		{
			IActor* actor = component->create(modelid, { x, y ,z }, rotation);
			if (actor)
			{
				return actor->getID();
			}
		}
		return INVALID_ACTOR_ID;
	}

	inline bool DestroyActor(int actorid)
	{
		IActor* actor = GetEntity<IActor>(actorid);
		if (actor)
		{
			GDKManager::Get()->GetActors()->release(actor->getID());
			return true;
		}
		return false;
	}

	inline bool IsActorStreamedIn(int actorid, int playerid)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		GET_PLAYER_CHECKED(player, actorid, false);
		return actor->isStreamedInForPlayer(*player);
	}

	inline bool SetActorVirtualWorld(int actorid, int virtualWorld)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		actor->setVirtualWorld(virtualWorld);
		return true;
	}

	inline int GetActorVirtualWorld(int actorid)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, 0);
		return actor->getVirtualWorld();
	}

	inline bool ApplyActorAnimation(int actorid, const char* animLib, const char* animName, float delta, int loop, int lockX, int lockY, int freeze, int time)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		const AnimationData animationData(delta, loop, lockX, lockY, freeze, time, animLib, animName);
		actor->applyAnimation(animationData);
		return true;
	}

	inline bool ClearActorAnimations(int actorid)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		actor->clearAnimations();
		return true;
	}

	inline bool SetActorPos(int actorid, float x, float y, float z)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		actor->setPosition({ x, y, z });
		return true;
	}

	inline bool GetActorPos(int actorid, float* x, float* y, float* z)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		Vector3 position = actor->getPosition();
		*x = position.x;
		*y = position.y;
		*z = position.z;
		return true;
	}

	inline bool SetActorFacingAngle(int actorid, float angle)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		actor->setRotation(Vector3(0.0f, 0.0f, angle));
		return true;
	}

	inline bool GetActorFacingAngle(int actorid, float* angle)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		*angle = actor->getRotation().ToEuler().z;
		return true;
	}

	inline bool SetActorHealth(int actorid, float health)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		actor->setHealth(health);
		return true;
	}

	inline bool GetActorHealth(int actorid, float* health)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		*health = actor->getHealth();
		return true;
	}

	inline bool SetActorInvulnerable(int actorid, bool invulnerable)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		actor->setInvulnerable(invulnerable);
		return true;
	}

	inline bool IsActorInvulnerable(int actorid)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		return actor->isInvulnerable();
	}

	inline bool IsValidActor(int actorid)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		return true;
	}

	inline bool SetActorSkin(int actorid, int skin)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		actor->setSkin(skin);
		return true;
	}

	inline int GetActorSkin(int actorid)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, 0);
		return actor->getSkin();
	}

	inline bool GetActorAnimation(int actorid, char* animlib, int animlibSize, char* animname, int animnameSize, float* delta, bool* loop, bool* lockx, bool* locky, bool* freeze, int* time)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		const AnimationData& anim = actor->getAnimation();

		animlib = const_cast<char*>(anim.lib.data());
		animname = const_cast<char*>(anim.name.data());
		*delta = anim.delta;
		*loop = anim.loop;
		*lockx = anim.lockX;
		*locky = anim.lockY;
		*freeze = anim.freeze;
		*time = anim.time;

		return true;
	}

	inline bool GetActorSpawnInfo(int actorid, int* skin, float* x, float* y, float* z, float* rotation)
	{
		GET_ENTITY_CHECKED(actor, IActor, actorid, false);
		const ActorSpawnData& spawnData = actor->getSpawnData();

		Vector3 position = spawnData.position;
		*x = position.x;
		*y = position.y;
		*z = position.z;

		*rotation = spawnData.facingAngle;
		*skin = spawnData.skin;
		return true;
	}

}