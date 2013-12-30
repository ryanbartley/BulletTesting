//
//  OpenGLMotionState.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/25/13.
//
//

#pragma once

#include "cinder/Matrix44.h"

#include <BulletDynamics/btBulletCollisionCommon.h>

namespace game {

class OpenGLMotionState : public btDefaultMotionState {
public:
	OpenGLMotionState( const btTransform &transform ) : btDefaultMotionState(transform) {}
	
	void getGLWorldTransform( ci::Matrix44f *transform )
	{
		btTransform trans;
		getWorldTransform(trans);
		trans.getOpenGLMatrix( (*transform) );
	}
};

}