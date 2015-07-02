///////////////////////////////////////////////////////////
//  ofxDesignSheet.cpp
//  Implementation of the Class ofxDesignSheet
//  Created on:      26-jun-2015 11:32:44
//  Original author: Christopher
///////////////////////////////////////////////////////////

#include "ofxDesignSheet.h"


ofxDesignSheet::ofxDesignSheet() : ofxSheetComponent(ComponentType::sheetItem){

	this->form.set(0,0,210,219);
	this->form.standardize();

	grid = true;
}


ofxDesignSheet::~ofxDesignSheet(){

	this->m_itemList.clear();

}


void ofxDesignSheet::draw(){

	ofPushStyle();
	ofPushMatrix();

	ofSetLineWidth(5);
	ofSetColor(ofColor::green);
	ofLine(this->form.getTopLeft(),ofPoint(this->form.getTopLeft().x + 50,this->form.getTopLeft().y));

	ofSetColor(ofColor::red);
	ofLine(this->form.getTopLeft(),ofPoint(this->form.getTopLeft().x,this->form.getTopLeft().y + 50));

	ofSetColor(ofColor::blue);
	ofFill();
	ofCircle(this->form.getTopLeft(),5);

	
	ofPopMatrix();
	ofPopStyle();

	// Draw Grid 
	//if(grid) this->drawGrid(10,10);


	// Draw componentes
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
	ofLogVerbose() << "current: " + ofToString( n->getID() );

	//if( !m_itemList.empty())
	//ofLogVerbose() << "last: " + ofToString( (*this->m_itemList.end())->getID() );

	this->m_itemList.push_back(n);
}


bool ofxDesignSheet::removeItem(ofxSheetComponent* comp){

	int counter = 0;

	for( auto & item : m_itemList ) {
		if( item->getID() == comp->getID()) {	
			break;
		}
		counter++;
	}


	if ( this->m_itemList.empty() || counter == this->m_itemList.size()){
	return false;
	} else {
		this->m_itemList.erase( this->m_itemList.begin() + counter);

	}
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

	return NULL;
}

