/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp()
: Osc("127.0.0.1", 12346, 12345)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
}

/******************************
******************************/
void ofApp::exit()
{
	printf("Good-bye\n");
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("OSC receive");
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	

}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	while(Osc.OscReceive.hasWaitingMessages()){
		ofxOscMessage m_receive;
		Osc.OscReceive.getNextMessage(m_receive); // 引数がpointerから参照に変わった.
		
		if(m_receive.getAddress() == "/MousePos"){
			OSC_mouseX = m_receive.getArgAsFloat(0);
			OSC_mouseY = m_receive.getArgAsFloat(1);
		}else{
			msg_Unrecognized = m_receive.getAddress();
			msg_Unrecognized += ":";
			for(size_t i = 0; i < m_receive.getNumArgs(); i++){
			
				msg_Unrecognized += " ";
				msg_Unrecognized += m_receive.getArgTypeName(i);
				msg_Unrecognized += ":";

				if(m_receive.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_Unrecognized += ofToString(m_receive.getArgAsInt32(i));
				}else if(m_receive.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_Unrecognized += ofToString(m_receive.getArgAsFloat(i));
				}else if(m_receive.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_Unrecognized += m_receive.getArgAsString(i);
				}else{
					msg_Unrecognized += "unhandled argument type";
				}
				
				msg_Unrecognized += ", ";
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(30);
	
	/********************
	********************/
	ofSetColor(255);
	
	{
		char buf[BUF_SIZE];
		sprintf(buf, "(%7.2f, %7.2f)", OSC_mouseX, OSC_mouseY);
		ofDrawBitmapString(buf, 20, 20);
	}
	
	{
		char buf[BUF_SIZE];
		sprintf(buf, "%s", msg_Unrecognized.c_str());
		ofDrawBitmapString(buf, 20, 50);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
