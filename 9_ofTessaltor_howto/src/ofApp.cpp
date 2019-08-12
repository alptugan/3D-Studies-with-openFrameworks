#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    totalW = 400;
    totalH = 400;
    _mesh.setMode( OF_PRIMITIVE_POINTS );
    generateMesh(totalW,totalH,30,ofColor(255));
    
}

void ofApp::generateMesh(int ww, int hh, int res, ofColor _color) {
    int w,h;
    w = 100;
    h = 100;
    
    
    
    
    _meshW    = floor(ww / w);
    _meshH    = floor(hh / h);
    
    _mesh.clear();
    _meshPoints.clear();
    _meshPointsMoved.clear();
    
    _meshPoints.resize(_meshH * _meshW);
    _meshPointsMoved.resize(_meshPoints.size());
    
    for (int y = 0; y < _meshH; y++){
        for (int x = 0; x < _meshW; x++){
            ofPolyline thisRect;
            ofMesh thisMesh;
            thisMesh.setMode( OF_PRIMITIVE_LINE_LOOP );
            
            int _id = x + (y * _meshW);
            
            _meshPoints[_id].x = x * w;           // vertex x coordinate
            _meshPoints[_id].y = y * h;           // vertex y coordinate
            _meshPoints[_id].z = 0;                      // vertex z coordinate
            
            thisRect.addVertex( _meshPoints[_id].x , _meshPoints[_id].y );
            thisRect.addVertex( _meshPoints[_id].x + w , _meshPoints[_id].y );
            thisRect.addVertex( _meshPoints[_id].x + w , h + _meshPoints[_id].y );
            thisRect.addVertex( _meshPoints[_id].x , h + _meshPoints[_id].y);
            thisRect.close();
            
          
            theseHexesOutline.push_back(thisRect);
            tess.tessellateToMesh(thisRect, OF_POLY_WINDING_NONZERO, thisMesh);
            
            thisMesh.mergeDuplicateVertices();
            
            for (int ii=0; ii<thisMesh.getNumVertices();ii++){
                thisMesh.addColor(ofColor(0)); // fill color
            }
            
        
            
            theseHexesFilled.push_back(thisMesh);
        }
    }
    
    
    
    
    /*
     
    _mesh.addIndex(x+y*_meshW);         // 0  meshH = 9, meshW = 12
    _mesh.addIndex((x+1)+y*_meshW);     // 1
    _mesh.addIndex((x+1)+(y+1)*_meshW); // 13
    _mesh.addIndex(x+(y+1)*_meshW);     // 12
    _mesh.addIndex(x+y*_meshW);         // 0
    
    */
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(100), ofColor(0));
    
    
    ofSetLineWidth(1);
    
    cam.begin();
    
    
    ofEnableDepthTest();
    glEnable(GL_CULL_FACE); // Cull back facing polygons
   // glCullFace(GL_FRONT); // might be GL_FRONT instead
    
    ofPushMatrix();
    ofTranslate(-totalW*0.5, -totalH*0.5);
    
    //(ofColor(0));
    //theMesh.drawWireframe();
    for (int i = 0; i < theseHexesFilled.size(); i++) {
        theseHexesFilled[i].draw();
        theseHexesOutline[i].draw();
    }
   
    
    ofPopMatrix();
    
    ofDisableDepthTest();
    
    
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
