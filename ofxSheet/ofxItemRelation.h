///////////////////////////////////////////////////////////
//  ofxItemRelation.h
//  Implementation of the Class ofxItemRelation
//  Created on:      04-jul-2015 22:04:17
//  Original author: Christopher
///////////////////////////////////////////////////////////

#if !defined(EA_598F5F19_2DED_471c_9EA6_96B025CCB928__INCLUDED_)
#define EA_598F5F19_2DED_471c_9EA6_96B025CCB928__INCLUDED_

#include "ofMain.h"

#include "ofxSheetComponent.h"
#include "ofxSheetDefines.h"

class ofxSheetItem;

class ofxItemRelation : public ofxSheetComponent {

public:
	ofxItemRelation(ofxSheetComponent *componentLink);
	virtual ~ofxItemRelation();

	void draw() override;
	void scale(float newFactor) override;

	void setNode1(ofxSheetItem* n1) { node1 = n1;};
	void setNode2(ofxSheetItem* n2) { node2 = n2;};

	ofxSheetItem* getNode1() { return node1;};
	ofxSheetItem* getNode2() { return node2;};

	void	setLineStyle( ofxRelationStyle newStyle) { lineStyle = newStyle;};
	void	setRelationDirection ( ofxRelationDirection newDirection) { direction = newDirection;};

private:

	ofxSheetComponent *component;


	ofxSheetItem* node1;
	ofPoint node1LastPosition;

	ofPoint meanNodes;

	ofxSheetItem* node2;
	ofPoint node2LastPosition;

	ofxRelationStyle	lineStyle;
	ofxRelationDirection	direction;

	ofPolyline line;

};
#endif // !defined(EA_598F5F19_2DED_471c_9EA6_96B025CCB928__INCLUDED_)
