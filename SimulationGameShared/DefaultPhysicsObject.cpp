//
//  DefaultPhysicsObject.cpp
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/27/13.
//
//

#include "DefaultPhysicsObject.h"

namespace game {

DefaultPhysicsObject::DefaultPhysicsObject( btCollisionShape* collShape, float mass, const ci::Vec3f &initialPosition, const ci::Quatf &initialRotation )
{
	mCollisionShape = collShape;
	
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( toBullet(initialPosition) );
	transform.setRotation( toBullet(initialRotation) );
	
	mMotionState = new OpenGLMotionState(transform);
	
	btVector3 localInertia(0,0,0);
	
	if( mass != 0.0f )
		collShape->calculateLocalInertia( mass, localInertia );
	
	btRigidBody::btRigidBodyConstructionInfo cInfo( mass, mMotionState, collShape, localInertia );
	
	mRigidBody = new btRigidBody(cInfo);
}
	
	DefaultPhysicsObject::~DefaultPhysicsObject()
{
	delete mRigidBody;
	delete mMotionState;
	delete mCollisionShape;
}
	
}