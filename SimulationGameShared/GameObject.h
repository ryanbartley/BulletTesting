//
//  Object.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/25/13.
//
//

#pragma once

#include <string>

#include "GameNode.h"
#include "OpenGLMotionState.h"

namespace game {

template <class PhysicsObject, class VisualObject>
class GameObject : public GameNode {
public:
	
	struct GameObjectFormat : public GameNode::GameNodeFormat {
		GameObjectFormat()
		: mCollisionShape(nullptr), mInitPos( ci::Vec3f() ),
			mInitRot( ci::Quatf() ), mMass( 1.0f ), mColor( ci::ColorA() )
		{}
		
		//Physics Format Options
		GameObjectFormat* collisionShape( btCollisionShape *collShape ) { mCollisionShape = collShape; return this; }
		GameObjectFormat* initPosition( const ci::Vec3f &initPos ) { mInitPos = initPos; return this; }
		GameObjectFormat* initRotation( const ci::Quatf &initRot ) { mInitRot = initRot; return this; }
		GameObjectFormat* mass( float mass ) { mMass = mass; return this; }
		GameObjectFormat* color( const ci::ColorA &color ) { mColor = color; }
		
		btCollisionShape* getCollisionShape() { return mCollisionShape; }
		const ci::Vec3f&  getInitPosition() { return mInitPos; }
		const ci::Quatf&  getInitRotation() { return mInitRot; }
		const ci::ColorA& getColor() { return mColor; }
		float			  getMass() { return mMass; }
		
	private:
		btCollisionShape   *mCollisionShape;
		ci::Vec3f			mInitPos;
		ci::Quatf			mInitRot;
		float				mMass;
		ci::ColorA			mColor;
	};
	
	GameObject( GameObjectFormat &format )
	: GameNode( format ), mPhysics( format.getCollisionShape(), format.getMass(), format.getInitPosition(), format.getInitRotation() ), mVisuals( format.getColor() ), mDebug( false )
	{
		
	}
	
	virtual ~GameObject() {}
	
	//
	virtual void update() = 0;
	virtual void render() = 0;
	
	
	// Implicit conversion functions
	btRigidBody* operator()() { return mPhysics.getBody(); }
	
	// Settings 
	void enableDebug( bool debug = true ) { mDebug = debug; }
	
protected:
	PhysicsObject		mPhysics;
	VisualObject		mVisuals;
	bool				mDebug;
};
	
}
