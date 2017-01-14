#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    radius = 200;
    total = 20;
    
    world.setMode(OF_PRIMITIVE_TRIANGLES);
    
    
    for (int i= 0; i < total; i++) {
        float lat = ofMap(i,0,total-1,0.0,PI);
        
        for (int j= 0; j<total; j++) {
            float lon = ofMap(j,0,total-1,0.0,TWO_PI);
            
            float x = radius * sin(lat) * cos(lon);
            float y = radius * sin(lat) * sin(lon);
            float z = radius * cos(lat);
            
            world.addVertex(ofVec3f(x,y,z));
        }
        
    }
    
    for (int j = 0; j < total - 1; j++) {
        for (int i = 0 ; i < total - 1 ; i++) {
            
            world.addIndex(i+j*total);         // 0
            world.addIndex((i+1)+j*total);     // 1
            world.addIndex(i+(j+1)*total);     // 6
            
            world.addIndex((i+1)+j*total);     // 1
            world.addIndex((i+1)+(j+1)*total); // 7
            world.addIndex(i+(j+1)*total);     // 6
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    
    cam.begin();
    
    world.drawWireframe();
    //world.drawVertices();
    
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
