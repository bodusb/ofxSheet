#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	sheet.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch( key ) {

	case OF_KEY_UP: 
		this->sheet.translate(0, - 10);
		break;
	case OF_KEY_DOWN: 		
		this->sheet.translate(0, + 10);
		break;
	case '=': case '+':
		this->sheet.scale(2);
		break;
	case '-': case '_': 		
		this->sheet.scale(0.5);
		break;
	case 'n': case 'N': {
		ofxSheetItem * sI = sheet.createItem(); 
		sI->releaseSnap(ofGetMouseX(),ofGetMouseY());
		sI->setColor(ofColor::red);
		break; }
	case 'r': case 'R': {
		ofxSheetComponent * sI = sheet.isInside(ofPoint(ofGetMouseX(),ofGetMouseY()));
		if (sI){

			sheet.remove(sI);
		}
		break;}

	}


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	switch (button){
	case 0:
		// treat left
		break;
	case 1:
		// treat middle
		if ( this->selectedByMouse){
			this->selectedByMouse->setX(x);
			this->selectedByMouse->setY(y);
			ofLogVerbose("[ofApp][DraggingItem]") << "Draggin: " + ofToString (this->selectedByMouse->getX()) + " - " + ofToString(this->selectedByMouse->getY());


		} else {
		}
		break;
	case 2:
		// treat right
		break;
	default: break;
	}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


	mouseStart.x = x;
	mouseStart.y = y;
	unsigned long long  clickTime = ofGetElapsedTimeMillis();

	// test single or double click

	if ( clickTime - mouseStartTime  > 500){
		// single click
		switch (button){
		case 0:
			// treat left
			// verify if inside of something
			this->selectedByMouse = sheet.isInside(mouseStart);

			break;
		case 1:
			// treat middle
			this->selectedByMouse = sheet.isInside(mouseStart);

			break;
		case 2:
			// treat right
			this->selectedByMouse = sheet.isInside(mouseStart);
			break;
		default: break;
		}

	} else {
		// double click

		switch (button){
		case 0:
			// treat left

			// double click in nothing
			if(selectedByMouse == NULL){
				this->sheet.translate(- sheet.getX() + 20, - sheet.getY() + 20);
				this->sheet.setScaleFactor(1); //does not correct items
			}

			break;
		case 1:
			// treat middle
			break;
		case 2:
			// treat right

			// double click in nothing
			if(selectedByMouse == NULL){
				this->sheet.scale( 1/this->sheet.getScaleFactor()); //correct items
			}

			break;
		default: break;
		}

	}

	mouseStartTime = clickTime;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mouseEnd.x = x;
	mouseEnd.y = y;


	switch (button){
	case 0:{
		// treat left
		
		// click and release on the same item => change properties
		// click and release on other item => create a relation
		// click and release on nothing => /???

		ofxSheetComponent * releasedOn = sheet.isInside(ofPoint(ofGetMouseX(),ofGetMouseY()));


		if ( this->selectedByMouse != NULL && selectedByMouse->getType() == ofxComponentType::OFX_SHEET_GENERICITEM 
			&& releasedOn != NULL && releasedOn->getType() == ofxComponentType::OFX_SHEET_GENERICITEM ){ // exist click and release

			if( this->selectedByMouse->getID() == releasedOn->getID() ) { // same item

				this->selectedByMouse->getColor() == ofColor::blue ? selectedByMouse->setColor(ofColor::red) : selectedByMouse->setColor(ofColor::blue);
			
			} else { // different itens

				this->sheet.createRelation((ofxSheetItem*)selectedByMouse,(ofxSheetItem*)releasedOn);
			
			}
	
		} else {

		}

		break;}
	case 1:
		// treat middle
		if ( this->selectedByMouse ){
			
			if( selectedByMouse->getType() == ofxComponentType::OFX_SHEET_GENERICITEM ){
				((ofxSheetItem*)this->selectedByMouse)->releaseSnap(x,y);
			}
			
		} else {
			sheet.translate(mouseEnd - mouseStart); 
		}
		break;
	case 2:
		// treat right
		if(this->selectedByMouse){
		} else {
			if (mouseEnd.x > mouseStart.x){
				// increase scale
				sheet.scale( 1 + mouseEnd.distance(mouseStart)/ofGetWidth());
			} else if (mouseEnd.x < mouseStart.x){
				sheet.scale( 1 - mouseEnd.distance(mouseStart)/ofGetWidth());
			}
			
		}
		break;
	default: break;
	}



}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
