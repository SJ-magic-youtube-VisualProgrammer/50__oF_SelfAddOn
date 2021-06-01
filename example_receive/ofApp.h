/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxOsc_BiDirection.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	enum{
		BUF_SIZE = 512,
	};
	
	enum{
		WIDTH	= 400,
		HEIGHT	= 400,	
	};
	
	OSC_TARGET Osc;
	
	float OSC_mouseX;
	float OSC_mouseY;
	
	string msg_Unrecognized = "";

	
public:
	ofApp();
	~ofApp();
	void exit();
	
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
