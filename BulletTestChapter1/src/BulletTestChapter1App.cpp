#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "PhysicsWorld.h"
#include "GameObject.h"
#include "DefaultPhysicsObject.h"
#include "DefaultVisualObject.h"
#include "MyFirstGameObject.h"

typedef game::MyFirstGameObject<game::DefaultPhysicsObject, game::DefaultVisualObject> DefaultGameObject;
typedef std::shared_ptr<DefaultGameObject> DefaultGameObjectRef;

using namespace ci;
using namespace ci::app;
using namespace std;

class BulletTestChapter1App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	game::PhysicsWorldRef	mPhysics;
	DefaultGameObjectRef	mObject;
};

void BulletTestChapter1App::setup()
{
	DefaultGameObject::MyFirstGameObjectFormat mFormat;
	
	mPhysics = game::PhysicsWorldRef( new game::PhysicsWorld() );
//	mObject = DefaultGameObjectRef( new DefaultGameObject( ) );
	
}

void BulletTestChapter1App::mouseDown( MouseEvent event )
{
}

void BulletTestChapter1App::update()
{
}

void BulletTestChapter1App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( BulletTestChapter1App, RendererGl )
