//
//  PhysicsWorld.cpp
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/25/13.
//
//

#include "PhysicsWorld.h"

namespace game {
	
PhysicsWorld::PhysicsWorld()
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mCollisionDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mBroadPhase = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mWorld = new btDiscreteDynamicsWorld( mCollisionDispatcher, mBroadPhase, mSolver, mCollisionConfiguration );
}
	
PhysicsWorld::~PhysicsWorld()
{
	delete mWorld;
	delete mSolver;
	delete mBroadPhase;
	delete mCollisionDispatcher;
	delete mCollisionConfiguration;
}
	
}