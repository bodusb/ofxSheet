///////////////////////////////////////////////////////////
//  ofxSheetItem.cpp
//  Implementation of the Class ofxSheetItem
//  Created on:      26-jun-2015 11:32:46
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxSheetItem.h"
#include "ofxDesignSheet.h"

#include "ofxItemRelation.h"

ofxSheetItem::ofxSheetItem(ofxSheetComponent * componentLink) : ofxSheetComponent(ofxComponentType::OFX_SHEET_GENERICITEM){
	this->form.standardize();
	this->component = componentLink;
	this->setColor(ofColor::lightBlue);
	this->style = ofxItemVisibilityStyle::OFX_SHEET_ITEM_TRANSPARENT_WITH_CONTOUR;
}

ofxSheetItem::~ofxSheetItem() {

	this->neighbors.clear();
}

void ofxSheetItem::draw(){
	//ofLogVerbose("[ITEM][DRAW]") << "Draw item";
	ofPushMatrix();
	ofPushStyle();

	switch( style ){

	case ofxItemVisibilityStyle::OFX_SHEET_ITEM_VISIBLE : 
		ofSetColor(this->color);
		drawContext();
		break;
	case ofxItemVisibilityStyle::OFX_SHEET_ITEM_CONTOUR : 
		this->drawContour();
		break;
	case ofxItemVisibilityStyle::OFX_SHEET_ITEM_HIDEN : break;
	case ofxItemVisibilityStyle::OFX_SHEET_TRANSPARENT : 
		ofSetColor(this->color,128);
		drawContext();
		break;
	case ofxItemVisibilityStyle::OFX_SHEET_ITEM_VISIBLE_WITH_CONTOUR : 
		ofSetColor(this->color);
		drawContext();
		this->drawContour();
		break;
	case ofxItemVisibilityStyle::OFX_SHEET_ITEM_TRANSPARENT_WITH_CONTOUR: 
		ofSetColor(this->color,128);
		drawContext();
		this->drawContour();
		break;
	default: break;

	};

	ofPopStyle();
	ofPopMatrix();
}


void ofxSheetItem::scale(float newFactor) {
	form.scale(newFactor); // scale the size of the item

	ofPoint aux;
	aux = this->component->getRectangle().getTopLeft();

	// correct the relation reference->object
	this->form.x -= aux.x;
	this->form.y -= aux.y;

	// apply the increase/decrease scale, to a screen->object reference
	form.x *= newFactor;
	form.y *= newFactor;

	// correct the relation reference->object
	this->form.x += aux.x;
	this->form.y += aux.y;
}


void ofxSheetItem::releaseSnap(int x, int y){
	
	ofLogVerbose("[ofxSheetItem][SNAP]") << "Before snap: " + ofToString (x) + " - " + ofToString(y);
	
	ofxDesignSheet *ds = (ofxDesignSheet*)component;
	ofPoint p = ds->getClosestToGrid( ofPoint(x,y), this->closestGridX , this->closestGridY);
	this->setX( p.x);
	this->setY( p.y);

	ofLogVerbose("[ofxSheetItem][SNAP]") << "After snap: " + ofToString (this->form.getX()) + " - " + ofToString(this->form.getY());
	ofLogVerbose("[ofxSheetItem][SNAP]") << "After snap: Closest Grid " + ofToString (this->closestGridX) + " - " + ofToString(this->closestGridY);

}



void ofxSheetItem::addRelationToNeighbors(ofxItemRelation *newRelation ){

	this->neighbors.push_back(newRelation);
}
bool ofxSheetItem::removeRelationFromNeighbors(ofxItemRelation* toRemove){
	ofLogVerbose("[ofxSheetItem][removeRelationFromNeighbors]") << " on item: " << this->getID();
	int counter = 0;

	for( auto & item : this->neighbors ) {
		if( item->getID() == toRemove->getID()) {	
			if ( this->neighbors.empty() || counter == this->neighbors.size()){
				ofLogVerbose("[ofxSheetItem][removeRelationFromNeighbors]") << "Neighbor Size (empty or more than last): " << this->neighbors.size();
				return false;
			} else {
				ofLogVerbose("[ofxSheetItem][removeRelationFromNeighbors]") << "Removing Neighbor relation: " << toRemove->getID();

				// delate relation from neighbor
				this->neighbors.erase( this->neighbors.begin() + counter);

				ofLogVerbose("[ofxSheetItem][removeRelationFromNeighbors]") << "Neighbor Size: " << this->neighbors.size();
				return true;
			}
		counter++;
		}
		
	}


	ofLogVerbose("[ofxSheetItem][removeRelationFromNeighbors]") << "Neighbor Size (didn't find):" << this->neighbors.size();
	return false;
}