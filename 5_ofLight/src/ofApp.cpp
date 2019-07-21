#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30);
    
    //light.setDirectional();
    
    ofFloatColor ambient_color(1., 1.0, 1.0, 1.);
    ofFloatColor diffuse_color(1., 1., 1.);
    ofFloatColor specular_color(0, 1., 0);
    
    //light.setAmbientColor(ambient_color);
    //light.setDiffuseColor(diffuse_color);
    //light.setSpecularColor(specular_color);
    
    //light.setSpotlight();
    //light.setSpotlightCutOff(200);
    //light.setSpotConcentration(0.1);
    
    light.setPointLight();
    light.setAttenuation(1.2,0.01,0.0);
    
    isStopAnim = false;
    
    xx = 0;
    yy = 0;
    zz = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    cam.begin();
    
    if(!isStopAnim)
    {
        yy = cos(ofGetElapsedTimef() * 0.4) * 250;
        zz = sin(ofGetElapsedTimef() * 0.4) * 250;
    }
    
    
    light.setPosition(xx, yy, zz);
    ofPushStyle();
    light.draw();
    
    ofRotateDeg(ofGetElapsedTimef()*10, 1, 1, 0);
    
    light.enable();
    ofEnableLighting();
    ofSetColor(255, 255, 255);
    ofDrawBox(0,0,0,220);
    ofDisableLighting();
    light.disable();
    
    ofPopStyle();
    
    cam.end();
    
    ofDisableDepthTest();
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
    isStopAnim = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    isStopAnim = false;
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
