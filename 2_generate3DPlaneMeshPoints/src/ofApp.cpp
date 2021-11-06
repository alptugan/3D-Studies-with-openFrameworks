#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    scl = 100; // Set Scale of grids
    
    terrainW = 800;
    terrainH = 800;
    
    terrainZPos = 40;
    cols = terrainW / scl; // set rows per scl
    rows = terrainH / scl; // set columns per scl
    
    
    cout << "columns numbers: " << cols << endl;
    cout << "rows numbers: " << cols << endl;
    
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    //mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    
    for (int j = 0; j < rows; j++) {
        xoff = 0;
        for (int i = 0 ; i < cols; i++) {
            
            float x = i*scl;
            float y = j*scl;
            //float z = ofRandom(-10,10);
            float z = 0;
            mesh.addVertex(ofVec3f(x,y,z));
            mesh.addColor(ofFloatColor(1,1,1));
           
            //mesh.addColor(ofFloatColor(ofMap(z,-50,50,0,1),ofMap(z,-50,50,0,1),ofMap(z,-50,50,0,1),1));
            
            xoff += 0.1;
        }
        yoff += 0.1;
    }
    
    ofSetWindowPosition(-ofGetWidth(), 0);
    // Generate order of indices to set triangles per rows and column
    for (int j = 0; j < rows - 1 ; j++) {
        for (int i = 0 ; i < cols - 1; i++) {
            mesh.addIndex(i+j*cols);         // 0
            mesh.addIndex((i+1)+j*cols);     // 1
            mesh.addIndex((i+1)+(j+1)*cols); // 5
            //mesh.addIndex(i+(j+1)*cols);     // 6
            //mesh.addIndex(i+j*cols);         // 0
            
            
            /*mesh.addIndex(i+j*cols);         // 0
            mesh.addIndex((i+1)+j*cols);     // 1
            mesh.addIndex(i+(j+1)*cols);     // 6
            
            mesh.addIndex((i+1)+j*cols);     // 1
            mesh.addIndex((i+1)+(j+1)*cols); // 7
            mesh.addIndex(i+(j+1)*cols);     // 6*/
            
        }
    }
    
    for (int i = 0 ; i < cols; i++) {
        mesh.addIndex((rows*cols) - (i) - 1);
    }
    
    for (int j = 0; j < rows - 1 ; j++) {
        mesh.addIndex(j*rows);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    //light.setPosition(ofVec3f(0,sin(ofGetElapsedTimef())*100,0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5 - terrainW*0.5 + scl*0.5, ofGetHeight()*0.5 - terrainH*0.5 + scl*0.5);
    //ofRotateX(60);
    
    //ofTranslate(0, -terrainH*0.5);
    
    for (int j = 0; j < rows; j++) {
        xoff = 0;
        for (int i = 0 ; i < cols; i++) {
            float z = ofMap(ofNoise(xoff, yoff,i+j ),0,1,-1*terrainZPos,terrainZPos);
            mesh.setVertex(i+j*cols, ofVec3f(mesh.getVertex(i+j*cols).x,mesh.getVertex(i+j*cols).y,z));
            xoff += 0.005;
        }
        yoff += 0.005;
    }
    
  
    ofEnableLighting();
    light.enable();
    
    mesh.draw();
    
    light.disable();
    ofDisableLighting();
    
    ofSetColor(255);
    mesh.drawWireframe();
    
    if(showIndices) {
        for (int j = 0; j < rows; j++) {
            for (int i = 0 ; i < cols; i++) {
                ofDrawBitmapStringHighlight(ofToString(i+j*cols), ofPoint(mesh.getVertex(i+j*cols).x - 10,mesh.getVertex(i+j*cols).y + 5));
            }
        }

    }
    ofPopMatrix();
    
    if(showIndices) {
        for (int j = 0; j < rows ; j++) {
            for (int i = 0 ; i < cols; i++) {
                
                ofDrawBitmapStringHighlight(ofToString(i+j*cols), 40, 40 + (120 * j));
                ofDrawBitmapStringHighlight(ofToString((i+1)+j*cols), 40, 60 + (120 * j));
                ofDrawBitmapStringHighlight(ofToString((i+1)+(j+1)*cols), 40, 80 + (120 * j));
                ofDrawBitmapStringHighlight(ofToString(i+(j+1)*cols), 40, 100 + (120 * j));
                ofDrawBitmapStringHighlight(ofToString(i+j*cols), 40, 120 + (120 * j));
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'i') {
        showIndices = !showIndices;
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
