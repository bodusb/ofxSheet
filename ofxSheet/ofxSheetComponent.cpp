///////////////////////////////////////////////////////////
//  ofxSheetComponent.cpp
//  Implementation of the Class ofxSheetComponent
//  Created on:      26-jun-2015 11:32:57
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxSheetComponent.h"


ofxSheetComponent::ofxSheetComponent(){
}


ofxSheetComponent::ofxSheetComponent(ofxComponentType newType) {

	this->type = newType;

	static int _id = 0; 
	id = _id++;

}



ofxSheetComponent::~ofxSheetComponent(){

}




void ofxSheetComponent::drawContour(){

	ofPushStyle();
	ofPushMatrix();

	ofSetColor(ofColor::black);
	ofSetLineWidth(1);
	ofNoFill();
	ofLine(	this->form.getTopLeft().x, this->form.getTopLeft().y, 
			this->form.getTopLeft().x + form.width, this->form.getTopLeft().y);
	ofLine(	this->form.getTopLeft().x, this->form.getTopLeft().y, 
			this->form.getTopLeft().x, this->form.getTopLeft().y + form.height);

	ofLine(	this->form.getTopLeft().x + form.width, this->form.getTopLeft().y + form.height, 
			this->form.getTopLeft().x, this->form.getTopLeft().y + form.height);
	ofLine(	this->form.getTopLeft().x + form.width, this->form.getTopLeft().y + form.height, 
			this->form.getTopLeft().x + form.width, this->form.getTopLeft().y);

	ofPopMatrix();
	ofPopStyle();
}