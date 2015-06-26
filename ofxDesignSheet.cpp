///////////////////////////////////////////////////////////
//  ofxDesignSheet.cpp
//  Implementation of the Class ofxDesignSheet
//  Created on:      26-jun-2015 11:32:44
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxDesignSheet.h"


ofxDesignSheet::ofxDesignSheet(){

	this->form.set(0,0,210,219);

	grid = true;
}



ofxDesignSheet::~ofxDesignSheet(){

}





void ofxDesignSheet::draw(){

	// Draw sheet backgorund
	ofSetColor(ofColor::white);
	ofFill();
	ofDrawPlane(this->getCenter(),form.width,form.height);



	// Draw Sheet Contour
	this->drawContour();
	
	// Draw Grid
	if(grid) this->drawGrid(10,10);


}


ofColor ofxDesignSheet::GetSheetColor(){

	return sheetColor;
}


void ofxDesignSheet::SetSheetColor(ofColor newVal){

	sheetColor = newVal;
}


void ofxDesignSheet::drawGrid(int x, int y){
	ofPushStyle();
	ofPushMatrix();

	ofSetColor(ofColor::gray);
	ofNoFill();
    
	for(int i = 0; i < form.height; i+=y) {
        ofLine(form.x,form.y + i, form.x + form.width,form.y + i);
    }
    
	for(int j = 0; j < form.width; j+=x)
    {
        ofLine(form.x + j,form.y,form.x + j,form.y + form.height);
    }


	ofPopMatrix();
	ofPopStyle();
}