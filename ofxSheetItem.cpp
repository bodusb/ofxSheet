///////////////////////////////////////////////////////////
//  ofxSheetItem.cpp
//  Implementation of the Class ofxSheetItem
//  Created on:      26-jun-2015 11:32:46
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxSheetItem.h"

ofxSheetItem::~ofxSheetItem(){

	this->form.standardize();

}


ofxSheetItem::ofxSheetItem(ofxSheetComponent * componentLink){
	
	this->form.standardize();

	this->component = componentLink;

}


void ofxSheetItem::draw(){
	//ofLogVerbose("[ITEM][DRAW]") << "Draw item";

	ofPushMatrix();
	ofPushStyle();

		ofSetColor(this->color);
		ofDrawPlane(form.getCenter(),form.width,form.width);
			
	ofPopStyle();
	ofPopMatrix();
}


void ofxSheetItem::moveBack(){

}


void ofxSheetItem::moveBackwards(){

}


void ofxSheetItem::moveFront(){

}


void ofxSheetItem::moveFrontwards(){

}


