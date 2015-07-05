
///////////////////////////////////////////////////////////
//  ofxSheetItem.h
//  Implementation of the Class ofxSheetItem
//  Created on:      26-jun-2015 11:32:45
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(OFXSHEETDEFINES_H)
#define OFXSHEETDEFINES_H

enum ofxItemVisibilityStyle{
	OFX_SHEET_ITEM_VISIBLE,
	OFX_SHEET_ITEM_HIDEN,
	OFX_SHEET_ITEM_CONTOUR,
	OFX_SHEET_TRANSPARENT,
	OFX_SHEET_ITEM_VISIBLE_WITH_CONTOUR,
	OFX_SHEET_ITEM_TRANSPARENT_WITH_CONTOUR
};

enum ofxComponentType{
	OFX_SHEET_DESIGNSHEET, 
	OFX_SHEET_GENERICITEM,
	OFX_SHEET_RELATION,
};

enum ofxRelationStyle{
	OFX_SHEET_RELATION_DIRECT,
	OFX_SHEET_RELATION_BELZIER
};

enum ofxRelationDirection{
	OFX_SHEET_DIRECTION_NON,
	OFX_SHEET_DIRECTION_1T2,
	OFX_SHEET_DIRECTION_2T1,
};


enum ofxRemovalDecision{
	OFX_DECISION_REMOVE,
	OFX_DECISION_SETTONULL,
};

#endif