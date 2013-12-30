//
//  GameNode.cpp
//  BulletTestChapter1
//
//  Created by Ryan Bartley on 12/27/13.
//
//

#include "GameNode.h"

namespace game {
	
GameNode::~GameNode()
{
	mParent = nullptr;
	mChildren.clear();
	delete mData;
}
	
void GameNode::update()
{
	if( !mChildren.empty() ) {
		for( auto childIt = mChildren.begin(); childIt != mChildren.end(); ++childIt ) {
			if( *childIt != nullptr ) {
				(*childIt)->update();
			}
		}
	}
}
	
GameNode* GameNode::getParentNode() const
{
	return mParent;
}
	
void GameNode::setParentNode( GameNode *newParent )
{
	if( mParent != nullptr ) {
		mParent->removeChildNode( this );
	}
	mParent = newParent;
}
	
void GameNode::addChildNode( GameNode *childNode )
{
	if( childNode != nullptr ) {
		childNode->setParentNode( this );
		mChildren.push_back( childNode );
	}
}
	
const PersonalData* GameNode::getPersonalData() const
{
	return &mData;
}
	
const size_t GameNode::countChildNodes( const bool recrusiveCount ) const
{
	if(!recrusiveCount) {
		return mChildren.size();
	}
	else {
		size_t RetVal = mChildren.size();
		for( auto childIt = mChildren.begin(); childIt != mChildren.end(); ++childIt ) {
			RetVal += (*childIt)->countChildNodes(true);
		}
		return RetVal;
	}
}
	
GameNode* GameNode::getChildNodeById( const int nodeId )
{
	GameNode* retVal = nullptr;
	if( !mChildren.empty() ) {
		for( auto childIt = mChildren.begin(); childIt != mChildren.end(); ++childIt ) {
			if( nodeId == (*childIt)->getPersonalData()->getId() ) {
				retVal = (*childIt);
			}
		}
	}
	return retVal;
}
	
}