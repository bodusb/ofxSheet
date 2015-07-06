///////////////////////////////////////////////////////////
//  ofxItemRelation.cpp
//  Implementation of the Class ofxItemRelation
//  Created on:      04-jul-2015 22:04:18
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxItemRelation.h"

#include "ofxSheetItem.h"
#include "ofxDesignSheet.h"

ofxItemRelation::ofxItemRelation(ofxSheetComponent *componentLink) : ofxSheetComponent(ofxComponentType::OFX_SHEET_RELATION) {

	this->component = componentLink;
	this->node1 = NULL;
	this->node2 = NULL;

	this->setColor(ofColor::black);

	this->direction = ofxRelationDirection::OFX_SHEET_DIRECTION_NON;
	this->lineStyle = ofxRelationStyle::OFX_SHEET_RELATION_BELZIER;

	form.set(0,0,20,20);

}


ofxItemRelation::~ofxItemRelation(){

}

void ofxItemRelation::draw() {
	ofPushStyle();


	ofSetColor( this->getColor());


	ofSetLineWidth(2);

	line.clear();
	if(node1){
		node1LastPosition = node1->getRectangle().getCenter();
	}
	if(node2){
		node2LastPosition = node2->getRectangle().getCenter();
	}

	line.clear();
	line.addVertex(node1LastPosition);


	if( this->lineStyle == ofxRelationStyle::OFX_SHEET_RELATION_DIRECT){

		line.addVertex(node2LastPosition);
	} else if( this->lineStyle == ofxRelationStyle::OFX_SHEET_RELATION_BELZIER){
		// adjust belzier
		meanNodes.set( (node2LastPosition.x + node1LastPosition.x)/2 , (node2LastPosition.y + node1LastPosition.y)/2 ); 
		line.bezierTo( ofPoint(meanNodes.x,node1LastPosition.y), ofPoint(meanNodes.x,node2LastPosition.y),node2LastPosition);
	}


	

	this->line.draw();

	ofFill();

	form.x = line.getPointAtPercent(0.5).x - form.width/2;
	form.y = line.getPointAtPercent(0.5).y - form.height/2;

	this->drawContour();

	ofPopStyle();
}


void ofxItemRelation::scale(float newFactor){
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


