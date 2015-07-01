///////////////////////////////////////////////////////////
//  ofxDesignSheet.cpp
//  Implementation of the Class ofxDesignSheet
//  Created on:      26-jun-2015 11:32:44
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxDesignSheet.h"


ofxDesignSheet::ofxDesignSheet(){

	this->form.set(0,0,210,219);
	this->form.standardize();

	grid = true;
}



ofxDesignSheet::~ofxDesignSheet(){

}





void ofxDesignSheet::draw(){

	ofPushMatrix();
	ofPushStyle();

	// Draw sheet backgorund
	ofSetColor(ofColor::white);
	ofFill();
	ofDrawPlane(this->form.getTopLeft().x,this->form.getTopLeft().y,this->getWidth(),this->getHeight());

	ofPopStyle();
	ofPopMatrix();
	

	// Draw Sheet Contour
	this->drawContour();
	
	// Draw Grid 
	//if(grid) this->drawGrid(10,10);


	// Draw componentes

	auto itSI = this->m_itemList.begin(); // create iterator
	for( auto & item : m_itemList ) {
		item->draw();
	}

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


//--------------------------------------------------------------
// Sheet Items
//--------------------------------------------------------------
void ofxDesignSheet::createItem(){
	ofxSheetItem *n = new ofxSheetItem(this);
	n->setRectangle(ofRectangle(ofGetMouseX(),ofGetMouseY(),100,100));
	n->SetColor(ofColor::red);
	this->m_itemList.push_back(n);

}

void ofxDesignSheet::translate(float x, float y){

	this->form.x += x;
	this->form.y += y;

	auto itSI = this->m_itemList.begin(); // create iterator
	for( auto & item : m_itemList ) {
		item->setX( item->getX() + x );
		item->setY( item->getY() + y );
	}
}

void ofxDesignSheet::translate(ofPoint newPosition){
	ofLogVerbose("[DESIGNSHEET]") << "translate";
	this->form.x += newPosition.x;
	this->form.y += newPosition.y;

	auto itSI = this->m_itemList.begin(); // create iterator
	for( auto & item : m_itemList ) {
		ofLogVerbose("[DESIGNSHEET]") << "translate item";
		item->setX( item->getX() + newPosition.x );
		item->setY( item->getY() + newPosition.y );
	}
}


ofxSheetComponent* ofxDesignSheet::isInside( ofPoint point){

	auto itSI = this->m_itemList.begin(); // create iterator
	for( auto & item : m_itemList ) {
		if ( item->isInside(point)){
			return item;
		}
	}
	return NULL;
}