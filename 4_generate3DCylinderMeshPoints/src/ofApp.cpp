#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableDepthTest();
    resolution = 30; // Set resolution
    
    heigth = 300;
    radius = 150;
    
    animate = true;
    
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    
    generateCylinder();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    cam.begin();
    ofPushMatrix();
    
    //ofEnableLighting();
    //light.enable();
    ofRotateX(90);
    if(animate) {

        ofRotateZ(ofGetElapsedTimef()*10);
        
        for (int i = 0; i < resolution + 1; i++) {
            float x = mesh.getVertex(i).x;
            float y = mesh.getVertex(i).y;
            float iFac;
            
            float z;
            
            iFac = ofMap(i,0,resolution,resolution*0.5,resolution);
            z = sin(ofGetElapsedTimef()*iFac*0.5)*2;
            
            if(i == 1) {
                //z = sin(ofGetElapsedTimef()*5)*iFac;
                //iFac = ofMap(resolution*0.5,0,mesh.getNumVertices()-1,-4,4);
                //z = sin(ofGetElapsedTimef()*5)*iFac;
                
                iFac = ofMap(resolution,0,resolution,resolution*0.5,resolution);
                z = sin(ofGetElapsedTimef()*iFac*0.5)*2;

                //ofDrawSphere(x, y, mesh.getVertex(i).z +z,10);
                
            }

            if(i == resolution*2 + 1 || i == resolution +2) {
                //iFac = ofMap(resolution,0,mesh.getNumVertices()-1,-4,4);
                //z = sin(ofGetElapsedTimef()*5)*iFac;
                //ofDrawSphere(x, y, mesh.getVertex(i).z +z,10);
                
            }
            
            
            mesh.setVertex(i, ofVec3f(x,y,mesh.getVertex(i).z + z));
        }
    }
    //
    mesh.disableColors();
    ofSetColor(255,0);
    //mesh.draw();
    //mesh.drawVertices();
    mesh.enableColors();
    //light.disable();
    //ofDisableLighting();
    
    ofSetColor(255,255);
    mesh.drawWireframe();
    
    
    ofPopMatrix();
    //ofNoFill();
    //ofDrawCylinder(0, 0, 100, 200);
    
    
    cam.end();
   
}

void ofApp::generateCylinder() {
    mesh.clear();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    // Top Cap Vertex Center Point
    mesh.addVertex(ofVec3f(0,0,-heigth*0.5));
    
    // Top Cap Vertices around center
    for (int i = 0 ; i < resolution; i++) {
        
        float theta = ofMap(i,0,resolution-1,0.0,TWO_PI);
        
        float x = radius * cos(theta);
        float y = radius * sin(theta);

        float z = -heigth*0.5;
        
        mesh.addVertex(ofVec3f(x,y,z));
        
    }
    
    

    // Bottom Cap Vertices around center
    mesh.addVertex(ofVec3f(0,0,heigth*0.5));
    
    // Bottom Cap Vertex Center Point
    for (int i = 0 ; i < resolution; i++) {
        
        float theta = ofMap(i,0,resolution-1,0.0,TWO_PI);
        
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        
        float z = heigth*0.5;
        
        mesh.addVertex(ofVec3f(x,y,z));
        
        
    }
    
    
    for (int i = 0 ; i < resolution ; i++) {
        
        // Top Cap Indices
        mesh.addIndex(0);
        mesh.addIndex(i);
        mesh.addIndex(i+1);
        
        // Bottom Cap Indices
        mesh.addIndex(resolution + 1);
        mesh.addIndex(resolution + i + 1);
        mesh.addIndex(resolution + i + 2);

    }
    
    
    
    for (int i = 0 ; i < resolution-1; i++) {
        
        mesh.addIndex(i + 1);
        mesh.addIndex(resolution + i + 2);
        mesh.addIndex(resolution + i + 3);
        mesh.addIndex(i + 1);
        mesh.addIndex(i + 2);
        mesh.addIndex(resolution + i + 3);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'f') {
        ofToggleFullscreen();
    }
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
