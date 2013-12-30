//
//  MyFirstGameObject.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/27/13.
//
//

#pragma once

#include "GameObject.h"

namespace game {

template<class PhysicsObject, class VisualObject>
class MyFirstGameObject : public GameObject<PhysicsObject, VisualObject>{
public:
	
	struct MyFirstGameObjectFormat : GameObject<PhysicsObject, VisualObject>::GameObjectFormat {
		MyFirstGameObjectFormat() {}
		
	private:
	};
	
	MyFirstGameObject( MyFirstGameObjectFormat & format )
	: GameObject<PhysicsObject, VisualObject>( format )
	{
	}
	
	using GameObject<PhysicsObject, VisualObject>::mPhysics;
	using GameObject<PhysicsObject, VisualObject>::mVisuals;
	
	void update();
	void render();
	
private:
	
};

template<class PhysicsObject, class VisualObject>
void MyFirstGameObject<PhysicsObject, VisualObject>::update()
{
	GameNode::update();
	
}

template<class PhysicsObject, class VisualObject>
void MyFirstGameObject<PhysicsObject, VisualObject>::render()
{
	
}

}
