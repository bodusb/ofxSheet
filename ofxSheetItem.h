///////////////////////////////////////////////////////////
//  ofxSheetItem.h
//  Implementation of the Class ofxSheetItem
//  Created on:      26-jun-2015 11:32:45
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_8793D2FD_9A4C_401c_8A1A_994DBB96EDD0__INCLUDED_)
#define EA_8793D2FD_9A4C_401c_8A1A_994DBB96EDD0__INCLUDED_

#include "ofxSheetComponent.h"
#include "ofxItemVisibilityStyle.h"

class ofxSheetItem : public ofxSheetComponent
{

public:
	ofxSheetItem(ofxSheetComponent *componentLink) ;
	virtual ~ofxSheetItem();

	void draw() override;
	void moveBack();
	void moveBackwards();
	void moveFront();
	void moveFrontwards();

	ofColor GetColor(){return color;}
	ofxSheetComponent * GetComponent(){return component;}
	ofxItemVisibilityStyle* GetVisibilityStyle(){	return m_ofxItemVisibilityStyle;}
	void SetColor(ofColor newVal){color = newVal;}
	void SetComponent(ofxSheetComponent *newVal){component = newVal;}
	void SetVisibilityStyle(ofxItemVisibilityStyle* newVal){m_ofxItemVisibilityStyle = newVal;}



private:
	ofxItemVisibilityStyle *m_ofxItemVisibilityStyle;
	ofxSheetComponent *component;
	int drawLevel;
	ofColor color;

};
#endif // !defined(EA_8793D2FD_9A4C_401c_8A1A_994DBB96EDD0__INCLUDED_)
