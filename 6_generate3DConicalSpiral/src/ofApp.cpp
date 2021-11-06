#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Enable logging
    ofLogToConsole();
    
    isDebug = true;
    
    // Parameters
    ofxGuiSetFont( "../../../../../../assets/DIN.otf", 8 );
    ofxGuiSetDefaultWidth( 300 );
    ofxGuiSetFillColor(ofColor(255,204,0,200));
    
    xmlSettingsPath = "settings.xml";
    gui.setDefaultEventsPriority(ofEventOrder::OF_EVENT_ORDER_BEFORE_APP);
    gui.setup( "Conical Spiral Parameters", xmlSettingsPath );
    group.add(csRes.set("Number of Points", 50, 10, 1000));
    group.add(csPos.set("Cone Position", glm::vec3(0,0,0), glm::vec3(-1000,-1000,-1000), glm::vec3(1000,1000,1000)));
    group.add(csRad.set("Spiral Radius", 60, 3, 1000));
    group.add(csFreq.set("Spiral Frequency", 0.3, 0, 1));
    group.add(csHeight.set("Spiral Height", 100, 1, 1000));
    group.add(csPathLineThickness.set("Spiral Thickness", 1, 0.1, 10));
    group.add(csPathColor.set("Spiral Color", ofColor(255,255,255,255), ofColor(0, 0, 0, 0), ofColor(255,255,255,255)));
    group.add(csRotateY.set("Animate Y Axis", true));
    group.add(csAnimateFreq.set("Animate Frequency", true));
    group.add(csShowPath.set("Show Spiral Path",false));
    group.add(csShowBoundingBox.set("Show Bounding Box", true));
    group.add(csShowPivotPoint.set("Show Shape Axes", true));
    group.add(csShowObjects.set("Show Objects On Path", true));
    group.add(csGenerate.set("Save Settings"));
    
    gui.add(group);
    gui.setPosition(ofGetWidth() - 310,10);
    
    gui.loadFromFile(xmlSettingsPath);
    
    // set window background color
    ofSetBackgroundColor(0);
    
    csPosListener = csPos.newListener([&](glm::vec3&){return this->setCamPosition();});
    ofAddListener(group.parameterChangedE(), this, &ofApp::guiUpdated);
    
    
    
    generateConicalSpiral();
    setCamPosition();
}

void ofApp::guiUpdated(ofAbstractParameter & _p) {
    generateConicalSpiral();
}

void ofApp::setCamPosition() {
    cam.setPosition(csPos->x, csPos->y, csPos->z);
}

void ofApp::guiChanged() {
    gui.saveToFile(xmlSettingsPath);
}

void ofApp::generateConicalSpiral() {
    
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    pos.clear();
    pos.resize(csRes);
    mesh.clear();
    
    // Resolution of the line
    for (int i = 0; i < pos.size(); i++) {
        
        // map the values to height
        float t = ofMap(i, 0, pos.size(), 0, csHeight);
        
        if(i == 0)
            actualW = ((csHeight - t) / csHeight) * csRad * 2;

        // where the magic magic happens
        // implementation ref: http://www.mathematische-basteleien.de/spiral.htm
        /*pos[i].x = csPos->x + ((csHeight - t) / csHeight) * csRad * cos(csFreq * t);
        pos[i].y = csPos->y + ((csHeight - t) / csHeight) * csRad * sin(csFreq * t);
        pos[i].z = csPos->z + t;*/
        
        pos[i].x = ((csHeight - t) / csHeight) * csRad * cos(csFreq * t);
        pos[i].y = ((csHeight - t) / csHeight) * csRad * sin(csFreq * t);
        pos[i].z = t;
        
        // Stroke Size
        //ofSetLineWidth(csPathLineThickness);
        
        // Color
        mesh.addColor(ofColor(csPathColor->r, csPathColor->g, csPathColor->b, csPathColor->a));
        
        // set mesh vertices in 3D space
        mesh.addVertex(pos[i]);
    }
}



//--------------------------------------------------------------
void ofApp::update(){
    if(csAnimateFreq) {
        csFreq = ofMap(sin(ofGetElapsedTimef()*0.5), -1, 1, 0.01, 1);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    ofDrawAxis(100);
    drawConicalSpiral();
    cam.end();
    
    if(isDebug) {
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(),2), gui.getPosition().x, gui.getPosition().y + gui.getHeight() + 20);
        gui.draw();
    }
}

void ofApp::drawConicalSpiral() {
    
    ofPushStyle();
    ofPushMatrix();
    {
        // rotate it to see from side look
        ofRotateXDeg(-90);
        // animate
        if(csRotateY)
            ofRotateZDeg(ofGetElapsedTimef()*20);
        // move the whole shape to position
        //ofTranslate(csPos);

        // Draw surrounding box
        if(csShowBoundingBox) {
            ofSetColor(ofColor(255,10,10,255));
            ofNoFill();
            ofSetLineWidth(1);
            ofDrawBox(actualW, actualW, csHeight);
        }
        
        ofPushMatrix();
        // Move the shape to the bottom & draw mesh
        ofTranslate(0, 0, -csHeight*0.5);
        if(csShowPivotPoint) {
            ofSetColor(ofColor(255,10,10,100));
            ofDrawArrow(glm::vec3(0,0,0),glm::vec3(0,actualW*0.5,0),0.55);   // y axis
            ofDrawArrow(glm::vec3(0,0,0),glm::vec3(actualW*0.5,0,0),0.55);   // x axis
            ofDrawArrow(glm::vec3(0,0,0),glm::vec3(0,0,csHeight),0.55);      // z axis
        }
        
        
        if(csShowPath) {
            ofSetLineWidth(csPathLineThickness);
            mesh.drawWireframe();
        }
        
        // Draw objects
        if(csShowObjects) {
            for (int i = 0; i < pos.size(); i++) {
                ofSetLineWidth(1);
                ofSetColor(ofColor(255,255,255));
                ofDrawBox(pos[i], ofMap(i, 0, pos.size()-1,5,1));
            }
        }
        ofPopMatrix();
        
        
    }
    ofPopMatrix();
    ofPopStyle();
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
    gui.setPosition(ofGetWidth() - 310,10);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
