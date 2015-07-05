///////////////////////////////////////////////////////////
//  ofxSheetComponent.h
//  Implementation of the Class ofxSheetComponent
//  Created on:      26-jun-2015 11:32:57
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_1DA943C3_3234_48fb_A839_A565C76A9516__INCLUDED_)
#define EA_1DA943C3_3234_48fb_A839_A565C76A9516__INCLUDED_

#include "ofMain.h"
#include "ofxSheetDefines.h"

class ofxSheetComponent{

public:
	ofxSheetComponent();
	ofxSheetComponent(ofxComponentType newType);
	virtual ~ofxSheetComponent();

	virtual void draw() = 0;

	virtual void translate(float x, float y){ form.translate(x,y);}
	virtual void translate(ofPoint newPostion){ form.translate(newPostion);}
	virtual ofxSheetComponent* isInside( ofPoint point) { return form.inside(point) ? this : NULL ;}

	ofxComponentType getType() {return this->type;};

	// Get/Set Proprieties
	float getHeight(){ return form.height;}
	ofRectangle getRectangle(){ return  this->form;}
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
	virtual void scale(float newFactor){ form.scale(newFactor);}
	void setID(int newValue) { id = newValue;};
	int getID() {return id;};

	ofColor				getColor(){ return color;};
	void				setColor(ofColor newVal){ color = newVal; };

protected:
	int id;
	ofxComponentType type;
	ofRectangle form;
	ofPoint toReference;
	ofColor color;

	void drawContour();

};
#endif // !defined(EA_1DA943C3_3234_48fb_A839_A565C76A9516__INCLUDED_)
