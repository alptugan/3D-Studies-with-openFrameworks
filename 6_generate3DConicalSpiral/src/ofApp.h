#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxPanel gui;
    ofParameterGroup group;
    ofParameter<glm::vec3> csPos;
    ofParameter<int> csRad;
    ofParameter<float> csFreq;
    ofParameter<int> csHeight;
    ofParameter<int> csRes;
    ofParameter<bool> csRotateY;
    ofParameter<bool> csAnimateFreq;
    ofParameter<bool> csShowPath;
    ofParameter<bool> csShowBoundingBox;
    ofParameter<bool> csShowPivotPoint;
    ofParameter<bool> csShowObjects;
    
    ofParameter<void> csGenerate;
    
    ofParameter<ofColor> csPathColor;
    ofParameter<int> csPathLineThickness;
    
    ofEventListener csPosListener;
    void setCamPosition();
    
    void guiChanged();
    void guiUpdated(ofAbstractParameter & _p);
    
    void generateConicalSpiral();
    void drawConicalSpiral();
    
    vector<glm::vec3> pos;
    bool isDebug;
    
    ofEasyCam cam;
    ofMesh mesh;
    
    string xmlSettingsPath;
    
    int actualW;
    
};
