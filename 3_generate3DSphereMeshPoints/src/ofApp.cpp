#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    radius = 200;
    total = 20;
    rot = 0;
    animateZPos = 1;
    
    world.setMode(OF_PRIMITIVE_TRIANGLES);
    
    animation = true;
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
    animate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    
    cam.begin();
    
    ofPushMatrix();
    ofRotateX(rot);
    ofRotateY(rot);
    ofSetColor(255, 255, 255);
    world.drawWireframe();
    
    //world.drawVertices();
    
    for (int i=0; i < world.getVertices().size(); i++) {
        
        float x = world.getVertex(i).x;
        float y = world.getVertex(i).y;
        float z = world.getVertex(i).z;
        
        ofSetColor(255, 0, 0);
        /*
        
        float length = sqrt(x*x+y*y+z*z);
        
        x = x / length;
        y = y / length;
        z = z / length;
        //+ sin(ofGetElapsedTimef()) * 20;*/
        float sanim = 1.1;
        
        //ofDrawCircle(x*sanim, y*sanim, z*sanim,3);
        
        ofDrawSphere(x*sanim, y*sanim, z*sanim, 1);
    }
    
    ofPopMatrix();
    
    
    
    cam.end();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 30);
    
}

void ofApp::animate() {
    world.clear();
    for (int i= 0; i < total; i++) {
        float lat = ofMap(i,0,total-1,0.0,PI);
        
        for (int j= 0; j<total; j++) {
            float lon = ofMap(j,0,total-1,0.0,TWO_PI);
            
            if(animation)
                animateZPos = ofMap(ofNoise(i*ofGetElapsedTimef()*0.05, j*ofGetElapsedTimef()*0.05),0,1,-10,10);
            
            
            float x = (animateZPos+radius) * sin(lat) * cos(lon);
            float y = (animateZPos+radius) * sin(lat) * sin(lon);
            float z = (animateZPos+radius) * cos(lat);
            
            world.addVertex(ofVec3f(x,y,z));
            
            
            

            //ofSetColor(255, 0, 0);
            
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
    
    if(animation) {
        rot = rot + 0.3;
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
