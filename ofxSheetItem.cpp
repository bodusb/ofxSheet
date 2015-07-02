///////////////////////////////////////////////////////////
//  ofxSheetItem.cpp
//  Implementation of the Class ofxSheetItem
//  Created on:      26-jun-2015 11:32:46
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxSheetItem.h"




ofxSheetItem::ofxSheetItem(ofxSheetComponent * componentLink) : ofxSheetComponent(ComponentType::sheetItem){
	
	this->form.standardize();

	this->component = componentLink;

}

ofxSheetItem::~ofxSheetItem() {

}

void ofxSheetItem::draw(){
	//ofLogVerbose("[ITEM][DRAW]") << "Draw item";

	ofPushMatrix();
	ofPushStyle();

		ofSetColor(this->color,128);
		ofDrawPlane(form.getCenter(),form.width,form.width);
			
	ofPopStyle();
	ofPopMatrix();

	this->drawContour();

	ofSetColor(ofColor::black);
	ofDrawBitmapStringHighlight( ofToString(this->id), form.getTopLeft());
}


void ofxSheetItem::moveBack(){

}


void ofxSheetItem::moveBackwards(){

}


void ofxSheetItem::moveFront(){

}


void ofxSheetItem::moveFrontwards(){

}


