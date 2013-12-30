//
//  Common.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/25/13.
//
//

#pragma once

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <BulletDynamics/btBulletCollisionCommon.h>

namespace game {

// Game Info
enum Type{
	NONE,
	PLAYER,
	WALL,
	FLOOR
};

// Small Class to hold specific data
// for all types with differentiating ID's
struct PersonalData {
public:
	PersonalData()
	: mId( PersonalData::idCreator() ), mType( Type::NONE ) {}
	PersonalData( Type type )
	: mId( PersonalData::idCreator() ), mType(type) {}
	
	~PersonalData() {}
	const int			getId() const { return mId; }
	const Type&			getType() const { return mType; }
	void				setType( Type type ) { mType = type; }
	
	// creating unique ID's for personalData
	static int idCreator()
	{
		static int totalId = 0;
		return totalId++;
	}
	
private:
	const int			mId;
	Type				mType;
};
	
// Beginning Conversion from type to type
btQuaternion toBullet( const ci::Quatf & cinderQuat )
{
	btQuaternion bulletQuat( cinderQuat.v.x, cinderQuat.v.y, cinderQuat.v.z, cinderQuat.w );
	return bulletQuat;
}

btVector3 toBullet( const ci::Vec3f cinderVec )
{
	btVector3 bulletVec( cinderVec.x, cinderVec.y, cinderVec.z );
	return bulletVec;
}
	
}