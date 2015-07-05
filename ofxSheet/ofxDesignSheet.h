///////////////////////////////////////////////////////////
//  ofxDesignSheet.h
//  Implementation of the Class ofxDesignSheet
//  Created on:      26-jun-2015 11:32:44
//  Original author: Christopher
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
/* to do list

- snap to grid



*/
///////////////////////////////////////////////////////////

#if !defined(EA_9CAB384A_EFD1_43ec_AA8F_2C4DD2728E4F__INCLUDED_)
#define EA_9CAB384A_EFD1_43ec_AA8F_2C4DD2728E4F__INCLUDED_

#include "ofxSheetComponent.h"
#include "ofxSheetDefines.h"

class ofxSheetItem;
class ofxItemRelation;

class ofxDesignSheet : public ofxSheetComponent {

public:

	ofxDesignSheet();
	virtual ~ofxDesignSheet();

	void				draw() override;
	void				scale(float newFactor) override;
	void				setScaleFactor(float newFactor);
	float				getScaleFactor() { return this->scaleFactor;};
	


	void				toogleGrid() { grid == true ? grid = false : grid = true;};
	void				toogleRuler() { ruler == true ? ruler = false : ruler = true;};

	void				toogleRemovalDecision() { 
		actionOnRemove == ofxRemovalDecision::OFX_DECISION_REMOVE ? actionOnRemove = ofxRemovalDecision::OFX_DECISION_SETTONULL :  actionOnRemove = ofxRemovalDecision::OFX_DECISION_REMOVE;};

	void				translate(float x, float y) override;
	void				translate(ofPoint newPostion) override;

	ofxSheetComponent*	isInside( ofPoint point) override;

	// Sheet Items
	ofxSheetItem *		createItem();
	bool				removeItem(ofxSheetItem* toRemove); // remove item might kill the relations ( kill or setToNULL)
	ofPoint				getClosestToGrid(ofPoint pointToSnap, int &nearX, int &nearY);

	// Relations
	ofxItemRelation*	createRelation(ofxSheetItem *start, ofxSheetItem *end, ofxRelationDirection newDirection = ofxRelationDirection::OFX_SHEET_DIRECTION_NON);
	bool				removeRelation(ofxItemRelation* toRemove); // remove relation doesn´t kill the item

	bool				remove(ofxSheetComponent *value);
	
protected:
	bool			ruler;
	bool			grid;

	ofxRemovalDecision actionOnRemove;
	bool				removeRelationsContaining(ofxSheetItem *itemToRemove);
	bool				setItemToNullRelationsContaining(ofxSheetItem *itemToRemove);


	float			scaleFactor;

	int				minimumDivision;

	vector<ofxSheetItem *> m_itemList;	
	vector<ofxItemRelation*> m_relationList;

	float getClosestToGridY( float y, int &nearGrid);
	float getClosestToGridX( float x, int &nearGrid);

	void			drawEnvironment();
	void			drawGrid(int x, int y);
	void			drawRuler(int x, int y);

};
#endif // !defined(EA_9CAB384A_EFD1_43ec_AA8F_2C4DD2728E4F__INCLUDED_)
