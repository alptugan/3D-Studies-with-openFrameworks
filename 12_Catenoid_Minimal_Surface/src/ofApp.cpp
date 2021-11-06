#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetWindowPosition(0,0);
    ofSetWindowShape(1920, 1080);
    catenoidSurface.setup();
    
    int digit = 42;
    cout << digit << " : " << &digit << " : " << *(&digit) << endl;
    printf("The address of digit = %d.", digit);

}

//--------------------------------------------------------------
void ofApp::update(){
    catenoidSurface.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    catenoidSurface.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'd') {
        catenoidSurface.isDebug = !catenoidSurface.isDebug;
    }
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
