#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Shader.h"

#include "cinder/Camera.h"
#include "PhysicsWorld.h"

#include <BulletDynamics/btBulletDynamicsCommon.h>

using namespace ci;
using namespace ci::app;
using namespace std;

Matrix44f fromBulletTransform( const btTransform &matrix )
{
	btTransform trans;
	Matrix44f m;
	matrix.getOpenGLMatrix( m.m );
	return m;
}

class BulletTestFirstProgramApp : public AppNative {
  public:
	BulletTestFirstProgramApp();
	void setup();
	void mouseDown( MouseEvent event );
	void keyDown( KeyEvent event );
	void update();
	void draw();
	void shutdown();
	btRigidBody* addBox( float rad, float x, float y, float z, float mass );
	void renderBox( btRigidBody* box );
	
	CameraPersp					mCam;
	Vec3f						mCameraTarget, mCameraEye;
	
	game::PhysicsWorldRef		mPhysicsWorld;
	
	std::vector<btRigidBody*>   mBodies;
};

BulletTestFirstProgramApp::BulletTestFirstProgramApp()
: AppNative(), mCam(), mCameraTarget( 0, 0, 0 ), mCameraEye( 0, 0, 20 ),
	mPhysicsWorld( new game::PhysicsWorld() )
{
	mPhysicsWorld->getWorld()->setGravity( btVector3( 0, -10, 0 ) );
	
	btTransform t;
	t.setIdentity();
	t.setOrigin( btVector3( 0, 0, 0 ) );
	btStaticPlaneShape* plane = new btStaticPlaneShape( btVector3(0,1,0), 0 );
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info( 0.0f, motion, plane );
	btRigidBody* body = new btRigidBody(info);
	mPhysicsWorld->getWorld()->addRigidBody( body );
	mBodies.push_back( body );
	
	addBox( 1.0f, 0, 20, 0, 1.0f );
	addBox( 1.0f, 0.7f, 40, 0.7f, 1.0f );
}

void BulletTestFirstProgramApp::shutdown()
{
	for( auto bodyIt = mBodies.begin(); bodyIt != mBodies.end(); ++bodyIt )
	{
		mPhysicsWorld->getWorld()->removeCollisionObject( *bodyIt );
		auto motionState = (*bodyIt)->getMotionState();
		auto collisionShape = (*bodyIt)->getCollisionShape();
		delete *bodyIt;
		delete collisionShape;
		delete motionState;
	}
}

void BulletTestFirstProgramApp::setup()
{
	mCam.setPerspective( 70.0f, getWindowAspectRatio(), 0.01f, 1000.0f);
	
	gl::bindStockShader( gl::ShaderDef().color() );
	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void BulletTestFirstProgramApp::keyDown( KeyEvent event )
{
	if( event.getChar() == KeyEvent::KEY_w ) {
		mCameraEye.y++;
	}
	else if( event.getChar() == KeyEvent::KEY_a ) {
		mCameraEye.x--;
	}
	else if( event.getChar() == KeyEvent::KEY_s ) {
		mCameraEye.y--;
	}
	else if( event.getChar() == KeyEvent::KEY_d ) {
		mCameraEye.x++;
	}
	else if( event.getChar() == KeyEvent::KEY_SPACE ) {
		btRigidBody* box = addBox( 1.0f, mCameraEye.x, mCameraEye.y, mCameraEye.z, 1.0f );
		Vec3f look = (mCameraEye - mCameraTarget).normalized() * -20.0f;
		cout << look << endl;
		box->setLinearVelocity( btVector3(look.x, look.y, look.z) );
	}
}

void BulletTestFirstProgramApp::mouseDown( MouseEvent event )
{
}

void BulletTestFirstProgramApp::update()
{
	mPhysicsWorld->getWorld()->stepSimulation( 1.0f / 60.0f );
	mCam.lookAt( mCameraEye, mCameraTarget );
}

void BulletTestFirstProgramApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	gl::pushMatrices();
	gl::setMatrices( mCam );
	
	for( int i = 0; i < mBodies.size(); i++ ) {
		if( i < 1 ) {
			btTransform t;
			t = mBodies[0]->getWorldTransform();
			
			ATTRIBUTE_ALIGNED16(btScalar m[16]);
			t.getOpenGLMatrix(m);
			Matrix44f squareMatrix(m);
//			Matrix44f squareMatrix = fromBulletTransform(t);
			gl::pushModelView();
			gl::multModelView( Matrix44f::createRotation( Vec3f( 1, 0, 0 ), toRadians( -90.0f )) );
			gl::drawSolidRect( Rectf( -1000.0f, -1000.0f, 1000.0f, 1000.0f ) );
			gl::popModelView();
		}
		else {
			renderBox( mBodies[i] );
		}
	}
	gl::popMatrices();
}

btRigidBody* BulletTestFirstProgramApp::addBox( float rad, float x, float y, float z, float mass )
{
	btTransform t;
	t.setIdentity();
	t.setOrigin( btVector3( x, y, z ) );
	btBoxShape* box = new btBoxShape( btVector3( rad / 2.0f, rad / 2.0f, rad / 2.0f ) );
	btMotionState* motion = new btDefaultMotionState(t);
	btVector3 inertia(0,0,0);
	
	if( mass != 0.0 )
		box->calculateLocalInertia( mass, inertia );
	
	btRigidBody::btRigidBodyConstructionInfo info( mass, motion, box );
	btRigidBody* body = new btRigidBody(info);
	mPhysicsWorld->getWorld()->addRigidBody( body );
	mBodies.push_back( body );
	return body;
}

void BulletTestFirstProgramApp::renderBox( btRigidBody *box )
{
	btTransform t;
	
	box->getMotionState()->getWorldTransform(t);
	ATTRIBUTE_ALIGNED16(btScalar m[16]);
	t.getOpenGLMatrix(m);
	Matrix44f squareMatrix(m);
	
//	Matrix44f squareMatrix = fromBulletTransform(t);
	
	gl::pushModelView();
	gl::multModelView( squareMatrix );
	gl::drawCube( Vec3f( 0.0f, 0.0f, 0.0f ), Vec3f( 1.0f, 1.0f, 1.0f ) );
	gl::popModelView();
}

CINDER_APP_NATIVE( BulletTestFirstProgramApp, RendererGl )
