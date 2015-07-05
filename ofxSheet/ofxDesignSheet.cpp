///////////////////////////////////////////////////////////
//  ofxDesignSheet.cpp
//  Implementation of the Class ofxDesignSheet
//  Created on:      26-jun-2015 11:32:44
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxDesignSheet.h"

#include "ofxItemRelation.h"
#include "ofxSheetItem.h"

ofxDesignSheet::ofxDesignSheet() : ofxSheetComponent(ofxComponentType::OFX_SHEET_DESIGNSHEET){

	this->form.set(20,20,0,0);
	this->form.standardize();

	this->ruler = true;
	this->grid = true;
	actionOnRemove = ofxRemovalDecision::OFX_DECISION_REMOVE;

	this->scaleFactor = 1;
	this->minimumDivision = 10;

	this->setColor(ofColor::lightBlue);

}

ofxDesignSheet::~ofxDesignSheet(){

	this->m_itemList.clear();

}

void ofxDesignSheet::draw(){

	ofPushStyle();
	ofPushMatrix();

	ofSetLineWidth(5);
	ofSetColor(ofColor::green);
	ofLine(this->form.getTopLeft(),ofPoint(this->form.getTopLeft().x + 50*this->scaleFactor,this->form.getTopLeft().y));

	ofSetColor(ofColor::red);
	ofLine(this->form.getTopLeft(),ofPoint(this->form.getTopLeft().x,this->form.getTopLeft().y + 50*this->scaleFactor));

	ofSetColor(ofColor::blue);
	ofFill();
	ofCircle(this->form.getTopLeft(),5);


	ofPopMatrix();
	ofPopStyle();

	// Draw Grid 
	this->drawEnvironment();


	// Draw Relation
	for( auto & item : m_relationList ) 
		item->draw();

	// Draw componentes
	for( auto & item : m_itemList ) 
		item->draw();

}

void ofxDesignSheet::drawEnvironment(){
	ofPushStyle();
	ofPushMatrix();

	int x = minimumDivision*scaleFactor, y = minimumDivision*scaleFactor;

	//Draw Grid
	if(grid) this->drawGrid(x,y);

	// draw Rules
	if(ruler) this->drawRuler(x,y);

	ofPopMatrix();
	ofPopStyle();
}

void ofxDesignSheet::drawGrid(int x, int y){
	ofPushStyle();

	ofSetColor(ofColor::white);
	ofSetLineWidth(1);


	float w = ofGetWidth();
	float h = ofGetHeight();

	// draw after the reference
	for(int i = this->form.getTopLeft().y; i < h; i+=y) 
		ofLine(0,i,w,i);    
	for(int j = this->form.getTopLeft().x; j < w; j+=x)
		ofLine(j,0,j,h);

	// draw before the reference
	for(int i = this->form.getTopLeft().y; i > minimumDivision*2; i-=y) 
		ofLine(0,i,w,i);    
	for(int j = this->form.getTopLeft().x; j > minimumDivision*2; j-=x)
		ofLine(j,0,j,h);

	ofPopStyle();

}

void ofxDesignSheet::drawRuler(int x, int y){
	ofPushStyle();


	float w = ofGetWidth();
	float h = ofGetHeight();

	// draw ruler base
	ofSetColor(ofColor::white);
	ofDrawPlane(w/2,10,w, 20);
	ofDrawPlane(10,h/2,20,h);

	// draw ruler contour
	ofSetColor(ofColor::black);
	ofSetLineWidth(2);
	ofLine(20,20,w,20);
	ofLine(20,20,20,h);

	// draw scale

	int counter = 0;

	// draw after the reference X
	for(int i = this->form.getTopLeft().x; i < w; i+=x*4) {
		ofLine(i,0,i,20);    
		ofDrawBitmapString(ofToString(counter),i + 1,10);
		counter ++;
	}

	counter = 0;
	// draw before the reference X
	for(int i = this->form.getTopLeft().x; i > 20; i-=x*4) {
		ofLine(i,0,i,20);    
		ofDrawBitmapString(ofToString(counter),i + 1,10);
		counter --;
	}


	counter = 0;
	// draw after the reference Y
	for(int i = this->form.getTopLeft().y; i < h; i+=y*4) {
		ofLine(0,i,20,i);    
		ofDrawBitmapString(ofToString(counter),0,i + 11);
		counter ++;
	}

	counter = 0;
	// draw before the reference Y
	for(int i = this->form.getTopLeft().y; i > 20; i-=y*4) {
		ofLine(0,i,20,i);    
		ofDrawBitmapString(ofToString(counter),0,i + 11);
		counter --;
	}

	ofPopStyle();

}

void ofxDesignSheet::setScaleFactor(float newFactor) { 

	this->scaleFactor = newFactor;

	// pass Scale
	for( auto & item : m_itemList ) 
		item->scale(newFactor);

};

void ofxDesignSheet::scale(float newFactor){

	this->scaleFactor = scaleFactor*newFactor;

	// pass Scale
	for( auto & item : m_itemList ) {
		ofLogVerbose("[ofxDesignSheet]") << "Before scale: " + ofToString (item->getX()) + " - " + ofToString(item->getY());
		item->scale(newFactor);
		ofLogVerbose("[ofxDesignSheet]") << "after scale: " + ofToString (item->getX()) + " - " + ofToString(item->getY());

		//if(snap){
		//item->setX( item->getClosestGrid().x*minimumDivision*scaleFactor);
		//item->setY( item->getClosestGrid().y*minimumDivision*scaleFactor);
		//ofLogVerbose("[ofxDesignSheet]") << "after scale (snap): " + ofToString (item->getX()) + " - " + ofToString(item->getY());

		//}

	}

	for( auto & item : m_relationList ) {
		item->scale(newFactor);
	}

}

float ofxDesignSheet::getClosestToGridX( float x, int &nearGrid){


	// solve x

	float realValue = abs(this->form.getTopLeft().x - x);

	int numberOfGrids = (realValue)/(minimumDivision*scaleFactor);
	ofLogVerbose("[ofxDesignSheet]") << "Closest x grid: " + ofToString(numberOfGrids);

	float reminder = ((realValue) - abs(numberOfGrids*minimumDivision*scaleFactor)) / (realValue);
	ofLogVerbose("[ofxDesignSheet]") << "remainder: " + ofToString(reminder);


	if ( reminder > 0.5 ) {
		//snap left
		nearGrid = numberOfGrids + 1;
	} else {
		//snap right
		nearGrid = numberOfGrids;
	}

	int signal = 1;
	x < this->form.getTopLeft().x ? signal = -1 : signal = 1;

	return this->form.getTopLeft().x + (signal)*(nearGrid)*minimumDivision*scaleFactor;
}

float ofxDesignSheet::getClosestToGridY( float y, int &nearGrid){


	// solve y

	float realValue = abs(this->form.getTopLeft().y - y);

	int numberOfGrids = (realValue)/(minimumDivision*scaleFactor);
	ofLogVerbose("[ofxDesignSheet]") << "Closest y grid: " + ofToString(numberOfGrids);

	float reminder = (abs(realValue) - abs(numberOfGrids*minimumDivision*scaleFactor)) / (realValue);
	ofLogVerbose("[ofxDesignSheet]") << "remainder: " + ofToString(reminder);


	if ( reminder > 0.5 ) {
		//snap left
		nearGrid = numberOfGrids + 1;
	} else {
		//snap right
		nearGrid = numberOfGrids;
	}

	int signal = 1;
	y < this->form.getTopLeft().y ? signal = -1 : signal = 1;

	return this->form.getTopLeft().y + (signal)*(nearGrid)*minimumDivision*scaleFactor;
}

ofPoint ofxDesignSheet::getClosestToGrid(ofPoint pointToSnap, int &nearX, int &nearY){
	ofLogVerbose("[ofxDesignSheet]") << "getClosestToGrid";
	ofLogVerbose("[ofxDesignSheet]") << ofToString (pointToSnap);


	ofPoint snapped;
	// solve x

	snapped.x = this->getClosestToGridX(pointToSnap.x,nearX);

	// solve y

	snapped.y = this->getClosestToGridY(pointToSnap.y,nearY);

	return snapped;
}


bool ofxDesignSheet::remove(ofxSheetComponent *value){

	if( value->getType() == ofxComponentType::OFX_SHEET_GENERICITEM ){

		return this->removeItem((ofxSheetItem*)value);

	} else if( value->getType() == ofxComponentType::OFX_SHEET_RELATION ){

		return this->removeRelation((ofxItemRelation*)value);
	}

	return false;
}


//--------------------------------------------------------------
// Sheet Items
//--------------------------------------------------------------
ofxSheetItem * ofxDesignSheet::createItem(){
		ofLogVerbose("[ofxDesignSheet][createItem]") << " -----------------------------------------------------------------------------------";

	ofxSheetItem *n = new ofxSheetItem(this);

	n->setRectangle(ofRectangle(ofGetMouseX(),ofGetMouseY(),100*scaleFactor,100*scaleFactor));

	ofLogVerbose("[ofxDesignSheet][createItem]") << "Current ID: " + ofToString( n->getID() ) + " - pos:(" + ofToString(n->getRectangle().position) +")";

	this->m_itemList.push_back(n);

	return n;
}

bool ofxDesignSheet::removeItem(ofxSheetItem* toRemove){
	ofLogVerbose("[ofxDesignSheet][removeItem]") << " -----------------------------------------------------------------------------------";
	int counter = 0;

	for( auto & item : m_itemList ) {
		if( item->getID() == toRemove->getID()) {	
			if ( this->m_itemList.empty() || counter == this->m_itemList.size()){
				ofLogVerbose("[ofxDesignSheet][removeItem]") << "ItemList Size (empty or more than last): " << this->m_itemList.size();
				return false;
			} else {
				ofLogVerbose("[ofxDesignSheet][removeItem]") << "Removing item: " << item->getID();

				// delete relations that contains this node or set to null????
				switch( this->actionOnRemove){
				case ofxRemovalDecision::OFX_DECISION_REMOVE : this->removeRelationsContaining(item); break;
				case ofxRemovalDecision::OFX_DECISION_SETTONULL : this->setItemToNullRelationsContaining(item); break;
				default: break;
				};
				ofLogVerbose("[ofxDesignSheet][removeItem]") << "Finished to resolve relations of this item";

				// delete node
				this->m_itemList.erase( this->m_itemList.begin() + counter);

				ofLogVerbose("[ofxDesignSheet][removeItem]") << "ItemList Size: " << this->m_itemList.size();
				return true;
			}
		}
		counter++;
	}


	ofLogVerbose("[ofxDesignSheet][removeItem]") << "ItemList Size (didn't find):" << this->m_itemList.size();
	return false;
}

void ofxDesignSheet::translate(float x, float y){

	this->form.x += x;
	this->form.y += y;

	for( auto & item : m_itemList ) {
		item->setX( item->getX() + x );
		item->setY( item->getY() + y );
	}
}

void ofxDesignSheet::translate(ofPoint newPosition){
	//ofLogVerbose("[DESIGNSHEET]") << "translate";
	this->form.x += newPosition.x;
	this->form.y += newPosition.y;

	for( auto & item : m_itemList ) {
		//ofLogVerbose("[DESIGNSHEET]") << "translate item";
		item->setX( item->getX() + newPosition.x );
		item->setY( item->getY() + newPosition.y );
	}
}

ofxSheetComponent* ofxDesignSheet::isInside( ofPoint point){

	for( auto & item : m_itemList ) 
		if( item->isInside(point)) 
			return item;

	for( auto & item : m_relationList ) // verify to get closer area
		if( item->isInside(point)) 
			return item;

	return NULL;
}

//--------------------------------------------------------------
// Sheet Relations (edges)
//--------------------------------------------------------------

ofxItemRelation* ofxDesignSheet::createRelation(ofxSheetItem *start, ofxSheetItem *end, ofxRelationDirection newDirection){
	ofLogVerbose("[ofxDesignSheet][createRelation]") << " -----------------------------------------------------------------------------------";

	ofxItemRelation *r = new ofxItemRelation(this);

	// create relation (Edges)
	r->setNode1(start);
	r->setNode2(end);
	r->setRelationDirection(newDirection);
	this->m_relationList.push_back(r);

	// update neighbors relations (edges)
	start->addRelationToNeighbors(r);
	end->addRelationToNeighbors(r);

	ofLogVerbose("[ofxDesignSheet][createRelation]") << "Relation ID: " + ofToString( r->getID() ) + " - relationBetween:(" + ofToString(start->getID()) + "," + ofToString(end->getID()) + ")";
	ofLogVerbose("[ofxDesignSheet][createRelation]") << "Start neighbor size: " + ofToString( start->getNeighborsSize());
	ofLogVerbose("[ofxDesignSheet][createRelation]") << "End neighbor size: " + ofToString( end->getNeighborsSize());

	ofLogVerbose("[ofxDesignSheet][createRelation]") << "RelationList Size: " + ofToString( this->m_relationList.size());
	return r;
}

bool ofxDesignSheet::removeRelation(ofxItemRelation* toRemove){ 
	ofLogVerbose("[ofxDesignSheet][removeRelation]") << " -----------------------------------------------------------------------------------";
	ofLogVerbose("[ofxDesignSheet][removeRelation]") << "Request to delete:" << toRemove->getID();

	int counter = 0;

	for( auto & item : m_relationList ) {
		if( item->getID() == toRemove->getID()) {	
			if ( this->m_relationList.empty() || counter == this->m_relationList.size()){
				ofLogVerbose("[ofxDesignSheet][removeRelation]") << "relationList Size (empty or more than last): " << this->m_relationList.size();
				return false;
			} else {
				ofLogVerbose("[ofxDesignSheet][removeRelation]") << "Removing relation: " << item->getID();

				// delete relation in nodes;
				item->getNode1()->removeRelationFromNeighbors(item);
				item->getNode2()->removeRelationFromNeighbors(item);

				// delate relation
				this->m_relationList.erase( this->m_relationList.begin() + counter);

				ofLogVerbose("[ofxDesignSheet][removeRelation]") << "relationList Size: " << this->m_relationList.size();
				return true;
			}
		}
		counter++;
	}

	ofLogVerbose("[ofxDesignSheet][removeRelation]") << "relationList Size (didn't find):" << this->m_relationList.size();
	return false;
}


bool ofxDesignSheet::removeRelationsContaining(ofxSheetItem *itemToRemove){
	ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << " -----------------------------------------------------------------------------------";
	ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Item being removed: " << itemToRemove->getID();
	int counter = 0;
	bool toReturn = false;

	vector<int> idsToRemove;

	// find relations that contain the item to be removed and clen their nodes neighbores
	for( auto & item : m_relationList ) {
		ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Searching on relation: " << item->getID();
			if ( this->m_relationList.empty() || counter == this->m_relationList.size()){
				ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "relationList Size (empty or more than last): " << this->m_relationList.size();
				ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "counter: " << counter;

				return false;
			} else {
				// delete relation in NEIGHBOR nodes;
				if( item->getNode1()->getID() == itemToRemove->getID()) 	{
					ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Go to node2: " << item->getNode2()->getID() << " and remove the neighbor " << item->getID();
					item->getNode2()->removeRelationFromNeighbors(item);
					ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "-> add relation to remove: " << item->getID();
					idsToRemove.push_back(item->getID());
				} else if( item->getNode2()->getID() == itemToRemove->getID())     {
					ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Go to node2: " << item->getNode1()->getID() << " and remove the neighbor " << item->getID();
					item->getNode1()->removeRelationFromNeighbors(item);
					ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "-> add relation to remove: " << item->getID();
					idsToRemove.push_back(item->getID());
				}

				ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Node1 neighbor size: " + ofToString( item->getNode1()->getNeighborsSize());
				ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Node2 neighbor size: " + ofToString( item->getNode2()->getNeighborsSize());



				ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "relationList Size: " << this->m_relationList.size();
				toReturn = true;
			}
		
		counter++;
	}

	
	// remove nodes that were tagged to removal
	int counterToRemove = 0;
	while ( idsToRemove.size() != 0 ){
	    MainLoop:

		ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << " Amount of relations to remove: " + ofToString( idsToRemove.size() );
		counterToRemove = 0;
		for( auto idToRemove : idsToRemove){
			counter = 0;
			for( auto & item : m_relationList ) {
				ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Searching for: " << idToRemove << " outer iteration : " << counterToRemove << " - intern iteration : " << counter;
				if( idToRemove == item->getID()){
					// delate relation
					ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "Removing relation: " << item->getID();
					this->m_relationList.erase( this->m_relationList.begin() + counter);
					idsToRemove.erase(idsToRemove.begin() + counterToRemove);
					goto MainLoop;
				}
				counter++;
			}
			counterToRemove ++;
		}
	}

	if(!toReturn) ofLogVerbose("[ofxDesignSheet][removeRelationsContaining]") << "relationList Size (didn't find):" << this->m_relationList.size();
	return toReturn;
}

bool ofxDesignSheet::setItemToNullRelationsContaining(ofxSheetItem *itemToRemove){

	int counter = 0;
	bool toReturn = false;

	for( auto & item : m_relationList ) {
		if( item->getID() == itemToRemove->getID()) {	
			if ( this->m_relationList.empty() || counter == this->m_relationList.size()){
				ofLogVerbose("[ofxDesignSheet][setItemToNullRelationsContaining]") << "relationList Size (empty or more than last): " << this->m_relationList.size();
				return false;
			} else {
				ofLogVerbose("[ofxDesignSheet][setItemToNullRelationsContaining]") << "Removing relation: " << item->getID();

				// delete relation in nodes;
				if( item->getNode1()->getID() == itemToRemove->getID()) 	{
					item->setNode1(NULL);
				} else if( item->getNode2()->getID() == itemToRemove->getID())     {
					item->setNode2(NULL);
				}

				ofLogVerbose("[ofxDesignSheet][setItemToNullRelationsContaining]") << "Node1 neighbor size: " + ofToString( item->getNode1()->getNeighborsSize());
				ofLogVerbose("[ofxDesignSheet][setItemToNullRelationsContaining]") << "Node2 neighbor size: " + ofToString( item->getNode2()->getNeighborsSize());

				// delate relation
				this->m_relationList.erase( this->m_relationList.begin() + counter);

				ofLogVerbose("[ofxDesignSheet][setItemToNullRelationsContaining]") << "relationList Size: " << this->m_relationList.size();
				toReturn = true;
			}
		}
		counter++;
	}

	ofLogVerbose("[ofxDesignSheet][setItemToNullRelationsContaining]") << "relationList Size (didn't find):" << this->m_relationList.size();
	return toReturn;
}