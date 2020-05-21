#pragma once

#include "ofMain.h"
#include "ofxGui.h"                     // Dependecy : ofxGui GUI
#include "quadPlaneWireFrame.h"         // Dependecy : Draw terrain class with wireframe without diagonals in quads
#include "ofxFFTLive.h"                 // Dependecy : ofxFFT - MIC INPUT sound analysis via FFT
#include "particleNoise.h"              // Dependecy : Particle Class wandering around using Perlin Noise
#include "ofxDOF.h"                     // Dependecy : ofxDOF - Depth of Field effect
#include "ofxPostProcessing.h"          // Dependecy : Draw terrain class with wireframe without diagonals in quads
#include "ofxFilikaUtils.h"             // Dependecy : Utility class for general purposes

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
    
    ofxPanel gui;                                       // Main GUI
    quadPlaneWireFrame terrain;                         // Declare "quadPlaneWireFrame.h" Class
    
    /* SOUND ANALYSIS */
    ofxFFTLive fftLive;                                 // Declara FFT constant
    vector<float> audioPeakBuf;                         // Realtime FFT data with specifed number of buffers
    ofParameterGroup audioGui;                          // ofxFFT parameters
    ofxSlider<float> audioThreshold;                    // Peak threshold value (keep it 1)
    ofxSlider<float> audioPeakDecay;
    ofxSlider<float> audioMaxDecay;
    ofxToggle audioMirror;                              // Mirror FFT Data
    ofParameter<glm::vec2> audioHighThres;              // Avarage peak High Freq threshold values
    ofParameter<glm::vec2> audioMidThres;               // Avarage peak Middle Freq threshold values
    ofParameter<glm::vec2> audioLowThres;               // Avarage peak Low Freq threshold values
    ofParameter<bool> isShowBars;                       // Show FFT Graph
    ofParameter<bool> isSoundInteractionEnabled;        // Enable Disable sound interaction
    ofParameter<bool> gEnableDepth;                     // Enable Disable depth sorting
    ofParameter<string> averagePeak;                    // Shows average peak for the sound spectrum
    
    /* WANDERING PARTICLE PARAMETERS */
    ofxPanel guiParticle;
    ofParameter<bool> gParticleEnableLines;
    ofParameter<bool> gParticleEnableLines2;
    ofParameter<ofColor> gParticleColor;                // Specifies particle color
    ofParameter<ofColor> gParticlePrivateLineColor;     // Particle connection between same class objects
    ofParameter<ofColor> gParticleWavesLineColor;       // Particle connections to peak FFT datas
		
    
    ofParameter<glm::vec3> gLightPos;                   // Global 3D light position
    ofEasyCam cam;                                      // interactive camera
    ofLight light;                                      // Global 3D Light Object
    
    /* Wandering by Perlin noise Particle */
    vector<particleNoise> particles;                    // Declaration of the wandering particles
    void checkConnections(glm::vec3 veci);              // Makes line connections between particles and peak points of the sound terrain
    void connectAgents();                               // Makes line connections between wandering particles if they are close enough together
    
    /* Camera Moving Autopilot Path */
    ofParameterGroup gCamMovPathParms;                  // Autopilot mode is free style moving of the "cam" object
    ofParameter<float> gAnimationSpeed;                 // the speed of camera movements
    ofParameter<glm::vec3> gCameraTrackingOff;          // How far the viewer from the camera
    ofParameter<glm::vec3> gCameraMoveLimits;           // Maximum distance that can "cam" object travels
    ofParameter<bool> gEnableAutoPilotCam;              // Enable/Disable autopilot mode
    float nCounter;                                     // Works as timing for the autopilot path
    glm::vec3 camLastPos,camLastPosAuto;                // position vectors to hold camera's last position
    
    /* DOF */
    ofxDOF dof;                                         // depth of field shader
    ofxPanel guiDOF;                                    // GUI for DOF
    ofParameter<float> gFocalDist;                      // How far the focus plane is
    ofParameter<float> gFocalRange;                     // How much range that it would be
    ofParameter<int> gBlurAmt;                          // How much blur out of focus area
    
    bool isDebug;                                       // Debug mode on / off
    bool isDofDepth;                                    // Enable/Disable DOF depth view
    bool isSave;                                        // Save screen image as png
    
    /* OFXFILIKA UTILITY CLASS */
    ofxFilikaUtils utils;                               // Handy general purpose utility function
    
    /* POST PROCESSING */
    ofxPanel guiEffect;                                 // Post processing effects
    vector<ofParameter<bool>> gFxBtns;                  // Enable disable butons for the specified effect
    ofParameter<bool> gFxEnableSoundInteraction;        // Enable disable sound interactive fx mode
    ofxPostProcessing post;                             // Post Processing object
    void initPostProcessing();                          // Setup post processing object
    
    
    ofMesh mesh;                                        // 3D Mesh object that holds connection between wandering particles
    ofMesh meshWaves;                                   // Holds lines between FFT peak data points and particles
};
