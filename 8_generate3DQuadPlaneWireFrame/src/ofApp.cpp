#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
   
    quadPlane.setup();
    quadPlane.setTexture("../../../../../../assets/test2.jpg");
    
    gui.setDefaultWidth(300);
    gui.setup("Project Parameters");
    gui.add(quadPlane.getGUI());
    
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
        cam.begin();
            ofScale(1,1);
            ofTranslate(-quadPlane.getWidth()*0.5,-quadPlane.getHeight()*0.5);
            quadPlane.draw();
        cam.end();
    ofPopMatrix();
    
    gui.draw();
    
    
    // Draw fps
    utils.drawFPS(ptAlignment::TR);
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
