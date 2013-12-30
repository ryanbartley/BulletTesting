//
//  DefaultVisualObject.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/27/13.
//
//

#pragma once

#include "cinder/gl/Vao.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/GlslProg.h"

#include "Common.h"

namespace game {
	
class DefaultVisualObject {
public:
	DefaultVisualObject( );
	~DefaultVisualObject() {}
	
	void setupBuffers();
	void setupShaders();
	
private:
	ci::gl::VaoRef mVao;
	ci::gl::VboRef mElementVbo, mPositionVbo;
};
	
}