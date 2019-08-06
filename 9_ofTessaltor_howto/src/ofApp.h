#pragma once

#include "ofMain.h"

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
		
    int totalW,totalH;
    ofPolyline thePoly;

    ofTessellator tess;

    
    vector<ofPolyline> theseHexesOutline;
    vector<ofMesh> theseHexesFilled;
    
    
    int                     _meshW, _meshH;    // Mesh rows & columns number
    vector<glm::vec3>       _meshPoints;       // original mesh vertices
    vector<glm::vec3>       _meshPointsMoved;  // modified mesh vertices
    
    float                   _time;             // the value to iterate noise function
    ofParameter<ofColor>    _meshStrokeColor;  // Mesh Stroke Color
    ofParameter<ofColor>    _meshFillColor;    // Mesh Fill Color
    ofParameter<int>        _meshThickness;    // Mesh point size
    ofVboMesh               _mesh;             // the object to draw

    ofParameter<int>        _meshRes;          // 3d resolution of the object
    ofParameter<int>        _w, _h;            // width & height
    
    ofParameter<bool>       _enableDepth;      // Enable / Disable depth test
    ofParameter<bool>       _enableAliasing;   // Enable / Disable anti-aliasing for smooth lines (by default it is enabled in oF)
    ofParameter<bool>       _enableFill;       // Enable / Disable mesh surface fill color
    ofParameter<bool>       _enableStroke;     // Enable / Disable mesh wireframe drawing
    ofParameter<bool>       _enableTexture;    // Wrap texture onto generated plane primitive
    ofParameter<bool>       _animate;          // Animation or not
    ofParameter<glm::vec3>  _meshPosDisp;      // x,y,z displacement factor in pixels
    ofParameter<float>      _animFreq;         // the speed of movement
    ofParameter<float>      _animNoiseF1;      // Animation noise multiplier
    ofParameter<float>      _animNoiseF2;      // Animation noise multiplier
    ofParameter<glm::vec2>  _animRes;          // Resolution of the grid animation (This parameter affects animation resolution)
    ofParameter<bool>       isDebug;           // Enable or Disable Debug view
    
    ofParameterGroup        meshGUI;           // Mesh Parameters
    ofParameterGroup        meshAnimGUI;       // Mesh Animation Parameters
    
    ofImage                 texture;           // Underneath solid texture Filling option with texture
    float                   preAnimFreq;       // keep track of the animation state
    ofMesh mesh;
    
    void generateMesh(int ww, int hh, int _res, ofColor _color);
    
    ofEasyCam cam;
};
