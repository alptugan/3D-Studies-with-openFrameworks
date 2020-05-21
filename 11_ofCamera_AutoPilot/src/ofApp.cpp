#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    cam.setDistance(80);
    
    //cam.removeAllInteractions();
    //cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY,OF_MOUSE_BUTTON_LEFT);
    //cam.addInteraction(ofEasyCam::TRANSFORM_ROTATE, OF_MOUSE_BUTTON_LEFT);
    //cam.addInteraction(ofEasyCam::TRANSFORM_SCALE, OF_MOUSE_BUTTON_MIDDLE);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofNode node;
    
    cam.setPosition(cos(ofGetFrameNum() * 0.02) * 90, sin(ofGetFrameNum() * 0.02) * 40, cam.getPosition().z);
    node.transformGL();
    
    
    
    node.restoreTransformGL();
    
    
    cam.lookAt(glm::vec3(0,0,0));
    
    
    cam.begin();
    
    ofNoFill();
    ofSetColor(255);
    ofDrawBox(25);
    
    //ofNode node;
    //node.lookAt(cam.getPosition(), {0,1,0});
    //node.setPosition(cos(ofGetFrameNum() * 0.02) * 10, sin(ofGetFrameNum() * 0.02) * 10, 0);
    //node.transformGL();
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofDrawCircle(0, 0, 0, 2);
    ofDrawLine(0,0,0,0,0,2);
    //node.restoreTransformGL();
    
    cam.end();
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
