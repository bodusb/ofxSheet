///////////////////////////////////////////////////////////
//  ofxSheetComponent.h
//  Implementation of the Class ofxSheetComponent
//  Created on:      26-jun-2015 11:32:57
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_1DA943C3_3234_48fb_A839_A565C76A9516__INCLUDED_)
#define EA_1DA943C3_3234_48fb_A839_A565C76A9516__INCLUDED_

#include "ofMain.h"


class ofxSheetComponent
{

public:
	ofxSheetComponent();
	virtual ~ofxSheetComponent();

	virtual void draw() = 0;



	// Get/Set Proprieties
	float getHeight(){ return form.height;}
	ofRectangle getRectangle(){ 	return  this->form;}
	float getWidth(){ return form.width;}
	float getX(){ return form.x;}
	float getY(){ return form.y;}
	ofPoint getCenter(){ return form.getCenter();}

	void setHeight(float newHeight){ form.setHeight(newHeight);}
	void setRectangle(ofRectangle newRectangle){ form = newRectangle;}
	void setWidth(float newWidth){ form.setWidth(newWidth);}
	void setX(float newX){ form.x = newX;}
	void setY(float newY){ form.y = newY;}

	// Macro changes
	void scale(float newFactor){ form.scale(newFactor);}
	void translate(int x, int y){ form.translate(x,y);}
	void translate(ofPoint newPostion){ form.translate(newPostion);}

	bool isInside( ofPoint point) { return form.inside(point);}



protected:
	ofRectangle form;
	void drawContour();

};
#endif // !defined(EA_1DA943C3_3234_48fb_A839_A565C76A9516__INCLUDED_)
