//
//  DefaultPhysicsObject.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/27/13.
//
//

#pragma once

#include "Common.h"
#include "OpenGLMotionState.h"

namespace game {

class DefaultPhysicsObject {
private:
	DefaultPhysicsObject() {}

public:
	explicit DefaultPhysicsObject( btCollisionShape* collShape, float mass, const ci::Vec3f &initialPosition, const ci::Quatf &initialRotation );
	~DefaultPhysicsObject();
	
	void getTransform( ci::Matrix44f *transform) {
		if(mMotionState) mMotionState->getGLWorldTransform(transform);
	}
	
	// Bullet stuff
	btCollisionShape*	getBulletShape() { return mCollisionShape; }
	btRigidBody*		getRigidBody() { return mRigidBody; }
	btMotionState*		getMotionState() { return mMotionState; }
	
private:
	btRigidBody		  *	mRigidBody;
	btCollisionShape  * mCollisionShape;
	OpenGLMotionState * mMotionState;
};
	
}