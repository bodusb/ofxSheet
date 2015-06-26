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
	ofxSheetItem(ofxSheetComponent * componentLink);
	virtual ~ofxSheetItem();

	virtual void draw();
	void moveBack();
	void moveBackwards();
	void moveFront();
	void moveFrontwards();

private:
	ofxItemVisibilityStyle *m_ofxItemVisibilityStyle;
	ofxSheetComponent* component;
	int drawLevel;

};
#endif // !defined(EA_8793D2FD_9A4C_401c_8A1A_994DBB96EDD0__INCLUDED_)
