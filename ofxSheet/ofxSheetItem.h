///////////////////////////////////////////////////////////
//  ofxSheetItem.h
//  Implementation of the Class ofxSheetItem
//  Created on:      26-jun-2015 11:32:45
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_8793D2FD_9A4C_401c_8A1A_994DBB96EDD0__INCLUDED_)
#define EA_8793D2FD_9A4C_401c_8A1A_994DBB96EDD0__INCLUDED_

#include "ofxSheetComponent.h"
#include "ofxSheetDefines.h"

class ofxItemRelation;


class ofxSheetItem : public ofxSheetComponent
{

public:
	ofxSheetItem(ofxSheetComponent *componentLink) ;
	virtual ~ofxSheetItem();

	void draw() override;

	virtual void drawContext() { // example ---- PLEASE OVERRIDE THIS or USE AS DEBUG!!!
		ofDrawPlane(form.getCenter(),form.width,form.width);
		ofSetColor(ofColor::black);
		ofDrawBitmapStringHighlight( ofToString(this->id) + ":" + ofToString(this->form.getTopLeft()), form.getTopLeft());
	};

	void scale(float newFactor) override;

	void releaseSnap(int x, int y);

	ofxSheetComponent * getComponent(){return component;}
	ofxItemVisibilityStyle getVisibilityStyle(){	return style;}
	void setComponent(ofxSheetComponent *newVal){component = newVal;}
	void setVisibilityStyle(ofxItemVisibilityStyle newVal){style = newVal;}

	void setClosestGrid(int x, int y) { closestGridX = x; closestGridY = y;};
	ofPoint getClosestGrid() { return ofPoint(closestGridX,closestGridY);};

	void				addRelationToNeighbors(ofxItemRelation *newRelation );
	bool				removeRelationFromNeighbors(ofxItemRelation* comp);

	int					getNeighborsSize() { return this->neighbors.size();};

private:
	int closestGridX;
	int closestGridY;
	ofxItemVisibilityStyle style;
	ofxSheetComponent *component;
	int drawLevel;

	vector<ofxItemRelation*> neighbors;

};
#endif // !defined(EA_8793D2FD_9A4C_401c_8A1A_994DBB96EDD0__INCLUDED_)
