///////////////////////////////////////////////////////////
//  ofxSheetComponent.cpp
//  Implementation of the Class ofxSheetComponent
//  Created on:      26-jun-2015 11:32:57
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxSheetComponent.h"


ofxSheetComponent::ofxSheetComponent(){
}



ofxSheetComponent::~ofxSheetComponent(){

}




void ofxSheetComponent::drawContour(){

	ofPushStyle();
	ofPushMatrix();

	ofSetColor(ofColor::black);
	ofNoFill();
	ofLine(form.x,form.y,form.x + form.width, form.y);
	ofLine(form.x,form.y,form.x, form.y + form.height);

	ofLine(form.x + form.width, form.y + form.height, form.x, form.y + form.height);
	ofLine(form.x + form.width, form.y + form.height, form.x + form.width, form.y);

	ofPopMatrix();
	ofPopStyle();
}