//
//  PhysicsWorld.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/25/13.
//
//

#pragma once

#include "Common.h"

namespace game {

typedef std::shared_ptr<class PhysicsWorld> PhysicsWorldRef;
	
struct PhysicsWorld {
public:
	PhysicsWorld();
	~PhysicsWorld();
	
	btDynamicsWorld* getWorld() { return mWorld; }
	
private:
	btBroadphaseInterface * mBroadPhase;
	btCollisionConfiguration * mCollisionConfiguration;
	btCollisionDispatcher * mCollisionDispatcher;
	btConstraintSolver * mSolver;
	btDynamicsWorld	* mWorld;
};
	
}
