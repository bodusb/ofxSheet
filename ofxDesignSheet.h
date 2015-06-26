///////////////////////////////////////////////////////////
//  ofxDesignSheet.h
//  Implementation of the Class ofxDesignSheet
//  Created on:      26-jun-2015 11:32:44
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_9CAB384A_EFD1_43ec_AA8F_2C4DD2728E4F__INCLUDED_)
#define EA_9CAB384A_EFD1_43ec_AA8F_2C4DD2728E4F__INCLUDED_

#include "ofxSheetComponent.h"
#include "ofxSheetStyle.h"

class ofxDesignSheet : public ofxSheetComponent {

public:	
	ofxDesignSheet();
	virtual ~ofxDesignSheet();

	void draw();
	ofColor GetSheetColor();
	void SetSheetColor(ofColor newVal);

	void toogleGrid() { grid == true ? grid = false : grid = true;};

	void scaleToAllPage() { float f = form.height; form.setHeight(ofGetHeight() - 10); form.setHeight( form.height*form.width/f); form.x = ofGetWidth()/2 - form.width/2; form.y = ofGetHeight()/2 - form.height/2;};
	void scaleToPageWidth() { float f = form.width; form.setWidth(ofGetWidth() - 10); form.setHeight( (form.width*form.height)/f); centralize();};
	void centralize() { form.setPosition(ofGetWidth()/2 - form.width/2,form.y);};

private:
	bool			grid;
	ofColor			sheetColor;
	ofxSheetStyle	m_ofxSheetStyle;

	void			drawGrid(int x, int y);


};
#endif // !defined(EA_9CAB384A_EFD1_43ec_AA8F_2C4DD2728E4F__INCLUDED_)
