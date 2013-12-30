//
//  GameNode.h
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/27/13.
//
//

#pragma once

#include "Common.h"

namespace game {
	
class GameNode {
public:
	
	struct GameNodeFormat {
		GameNodeFormat() : mParent(nullptr), mDataPtr() {}
		
		GameNodeFormat* parent( GameNode* parent )
		{ if( parent != nullptr ) mParent = parent; return this; }
		GameNodeFormat* personalDataType( const Type type )
		{ mDataPtr->setType( type ); return this; }
		
		GameNode* getParent() { return mParent; }
		PersonalData* getDataPtr() { return mDataPtr; }
		
	private:
		GameNode* mParent;
		PersonalData* mDataPtr;
	};
	
	explicit GameNode( GameNodeFormat &format )
	: mParent( format.getParent() ), mData( format.getDataPtr() )
	{
		
	}
	virtual ~GameNode();
	
	virtual void update();
	
	GameNode* getParentNode() const;
	void setParentNode( GameNode* newParent );
	
	void addChildNode( GameNode* childNode );
	void removeChildNode( GameNode* childNode );
	
	const PersonalData* getPersonalData() const;
	const size_t countChildNodes( const bool RecrusiveCount = false ) const;
	virtual const bool isRootNode() const = 0;
	
	GameNode* getChildNodeById( const int nodeId );
	
private:
	GameNode*		mParent;
	PersonalData*	mData;
	std::list<GameNode*> mChildren;
};
	
}
