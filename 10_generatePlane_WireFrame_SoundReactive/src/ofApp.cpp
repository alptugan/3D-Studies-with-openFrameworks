#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    // Set background color
    ofSetBackgroundColor(0);
    
    // Set window size, debug mode and dof view mode
    ofSetWindowPosition(0,0);
    ofSetWindowShape(1920, 1080);
    isDebug = true;
    isDofDepth = false;
    
    // Setup Post Processing Effects
    initPostProcessing();
    
    // Enable log to console option to view debug messages using ofLog function
    ofLogToConsole();
    
    // GLOBAL GUI COLORS
    ofColor gFill(40);
    ofColor gBorder(120);
    
    ofColor gFill2(120);
    ofColor gBorder2(40);
    
    // GLOBAL GUI UI PARAMETERS
    ofxGuiSetFont( "../../../../../../assets/fonts/DIN.otf", 8 );
    ofxGuiSetDefaultWidth( 300 );
    ofxGuiSetFillColor(gFill);
    
    string xmlSettingsPath = "settings.xml";
    gui.setup( "### APP PARAMETERS ###", xmlSettingsPath );
    gui.setPosition(ofGetWidth() - 310,10);
    gui.setHeaderBackgroundColor(gFill);
    gui.setBorderColor(gBorder2);
    
    // SETUP TERRAIN WITH SPECIFIED WIDTH / HEIGHT
    terrain.setup(800, 600);
    
    /* CAM MOVEMENT PARAMETERS */
    cam.setPosition(0, 0, 1850);
    //cam.removeAllInteractions();
    //cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY,OF_MOUSE_BUTTON_LEFT);
    //cam.addInteraction(ofEasyCam::TRANSFORM_ROTATE, OF_MOUSE_BUTTON_LEFT);
    //cam.addInteraction(ofEasyCam::TRANSFORM_SCALE, OF_MOUSE_BUTTON_MIDDLE);
    
    /* GUI AUTOPILOT CAMERA */
    gCamMovPathParms.setName("### CAM AUTOPILOT MOVEMENT ###");
    gCamMovPathParms.add(gEnableAutoPilotCam.set("Enable Cam Auto-pilot", false));
    gCamMovPathParms.add(gAnimationSpeed.set("Animation Speed",0.2,0.0,1));
    gCamMovPathParms.add(gCameraMoveLimits.set("Cam Move Limits", glm::vec3(200,200,600), glm::vec3(-8000), glm::vec3(8000)));
    gCamMovPathParms.add(gCameraTrackingOff.set("Cam Offset", glm::vec3(0, 0, 260), glm::vec3(-4000), glm::vec3(8000)));
    
    
    // ADD :  3D Depth sorting enable /disable
    gui.add(gEnableDepth.set("Enable Depth Sorting", true));
    
    // ADD :  Terrain options
    gui.add(terrain.getGUI());
    //gui.getGroup("### CAM AUTOPILOT MOVEMENT ###").minimize();
    
    // ADD : FFT PARAMETERS
    audioGui.setName("### AUDIO FFT PARAMETERS ###");
    audioGui.add(isSoundInteractionEnabled.set("Enable Sound Interaction", true));
    audioGui.add(audioThreshold.setup("audioThreshold", 1.0, 0.0, 1.0)->getParameter());
    audioGui.add(audioPeakDecay.setup("audioPeakDecay", 0.915, 0.0, 1.0)->getParameter());
    audioGui.add(audioMaxDecay.setup("audioMaxDecay", 0.995, 0.0, 1.0)->getParameter());
    audioGui.add(audioMirror.setup("audioMirror", true)->getParameter());
    audioGui.add(averagePeak.set("Average PEAK",""));
    audioGui.add(audioHighThres.set("High Range", glm::vec2(0, 0.5), glm::vec2(0), glm::vec2(5)));
    audioGui.add(audioMidThres.set("Mid Range", glm::vec2(0, 0.5), glm::vec2(0), glm::vec2(5)));
    audioGui.add(audioLowThres.set("Low Range", glm::vec2(0, 0.5), glm::vec2(0), glm::vec2(5)));
    
    // ADD : FFT GUI
    gui.add(audioGui);
    gui.getGroup("### AUDIO FFT PARAMETERS ###").minimize();
    
    // Load last session settings
    gui.loadFromFile(xmlSettingsPath);
    
    
    // Init dof
    dof.setup(ofGetWidth(), ofGetHeight());
    
    /* GUI DOF */
    string xmlSettingsPathDOF = "settingsDOF.xml";
    ofxGuiSetFillColor(gFill2);
    guiDOF.setup( "### DOF PARAMETERS ###", xmlSettingsPathDOF );
    guiDOF.add(gLightPos.set("Light Position", glm::vec3(1000,1000,2000), glm::vec3(-4000),glm::vec3(4000)));
    guiDOF.add(gFocalRange.set("Focal Range", 50, 0, 5000));
    guiDOF.add(gFocalDist.set("Focal Distance", 150, -5000, 5000));
    guiDOF.add(gBlurAmt.set("Blur Amount", 1, 0, 20));
    guiDOF.add(gCamMovPathParms);
    guiDOF.setPosition(ofGetWidth() - 614,10);
    guiDOF.setHeaderBackgroundColor(gFill2);
    guiDOF.setBorderColor(gBorder2);
    guiDOF.loadFromFile(xmlSettingsPathDOF);
    
    
    /* GUI PARTICLE */
    string xmlSettingsPathParticles = "settingsParticles.xml";
    ofxGuiSetFillColor(gFill);
    ofxGuiSetDefaultWidth(200);
    guiParticle.setup( "### PARTICLE PARAMETERS ###", xmlSettingsPathParticles );
    guiParticle.add(gParticleEnableLines.set("Enable Particle Lines", false));
    guiParticle.add(gParticleEnableLines2.set("Enable Particle Wave Lines ", false));
    guiParticle.add(gParticleColor.set("Particle Colors", ofColor(255,0,0), ofColor(0), ofColor(255)));
    guiParticle.add(gParticlePrivateLineColor.set("Particle Private Connection Colors", ofColor(255,0,0), ofColor(0), ofColor(255)));
    guiParticle.add(gParticleWavesLineColor.set("Particle Waves Connection Colors", ofColor(255,0,0), ofColor(0), ofColor(255)));
    guiParticle.setPosition(ofGetWidth() - 818,10);
    guiParticle.setHeaderBackgroundColor(gFill);
    guiParticle.setBorderColor(gBorder2);
    guiParticle.loadFromFile(xmlSettingsPathParticles);
    
    /* GUI EFFECTS */
    string xmlSettingsPathFx = "settingsEffects.xml";
    ofxGuiSetFillColor(gFill2);
    ofxGuiSetDefaultWidth(154);
    
    guiEffect.setup( "### FX ###", xmlSettingsPathFx );
    gFxBtns.resize(post.size());
    
    ofLog() << "--------------------------------------";
    ofLog() << "EFFECT NAMES :";
    ofLog() << "--------------------------------------";
    for (int i = 0; i < post.size(); i++) {
        guiEffect.add(gFxBtns[i].set(ofToString(i) + " - " + post[i]->getName(), false));
        ofLog() << ofToString(i) + " - " + post[i]->getName();
    }
    guiEffect.setPosition(ofGetWidth() - 976,10);
    guiEffect.setHeaderBackgroundColor(gFill2);
    guiEffect.setBorderColor(gBorder2);
    guiEffect.loadFromFile(xmlSettingsPathFx);
    
    

    
    /* FFT SECTION */
    fftLive.setMirrorData(false);
    fftLive.setup();

   
    /* WANDERING PARTICLES */
    for (int i = 0; i < 20; i++) {
        particleNoise temp;
        particles.push_back(temp);
        
        particles[i].setup();
    }
    
    // Mesh mode for connection lines.
    // In primitive lines mode you can create color gradients
    mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
    meshWaves.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // LIGHT
    light.setPosition(gLightPos);
    
    // FFT
    fftLive.setThreshold(audioThreshold);
    fftLive.setPeakDecay(audioPeakDecay);
    fftLive.setMaxDecay(audioMaxDecay);
    fftLive.setMirrorData(audioMirror);
    fftLive.update();
    
    // DOF PARAMETERS UPDATE
    dof.setFocalDistance(gFocalDist);
    dof.setFocalRange(gFocalRange);
    dof.setBlurAmount(gBlurAmt);

    
    /* MESH GUI */
    glm::vec3 target;
    glm::vec3 camera_location;
    
    if(gEnableAutoPilotCam)
    {
        //ofSeedRandom(39);
        float t = nCounter * gAnimationSpeed;
        float xC = ofSignedNoise(0.002, 0, t) * gCameraMoveLimits->x;
        float yC = ofSignedNoise(0, 0.001, t) * gCameraMoveLimits->y;
        float zC = ofSignedNoise(t, 0, 0.0013) * gCameraMoveLimits->z;
        
        target = glm::vec3(xC, yC, zC);
        //particles[i]
        
        camera_location = target + gCameraTrackingOff.get();
        
        // Creates a nice tween between current point and the upcoming point
        camLastPosAuto = 0.05 * camera_location + (1 - 0.05) * camLastPosAuto;
        
        // Set camera position
        this->cam.setPosition(camLastPosAuto);
        
        // the following method keeps camera look at always in the middle of the screen
        this->cam.lookAt(glm::vec3(0));
        
        // Keeps camera moving on the generated path. Functions as time
        nCounter += 0.01;
        
        // Holds the last position on autopilot mode
        camLastPos = cam.getPosition();
    }else{
        // Tween to original starting pos
        camLastPos = 0.05 * glm::vec3(77,-1793,2154) + (1 - 0.05) * camLastPos;
        cam.setPosition(camLastPos);
        cam.lookAt(glm::vec3(0,1200 + sin(ofGetElapsedTimef())*600,300+ sin(ofGetElapsedTimef()*0.5)*1200));
        camLastPosAuto = cam.getPosition();
    }
    
    
    // Sound interaction conditions for post processing effects
    // The logic is a little bit dirty
    // This part depends on your creativity :)
    if(fftLive.getAveragePeak() > 0.4) {
        gFxBtns[0] = true;
    }else{
        gFxBtns[0] = false;
    }
    
    if(fftLive.getAveragePeak() > 0.7) {
        gFxBtns[11] = true;
        gFxBtns[12] = true;
        //
    }else{
        gFxBtns[11] = false;
        gFxBtns[12] = false;
        //gFxBtns[8] = false;
    }
    
    if(fftLive.getAveragePeak() > 0.73) {
        isDofDepth = true;
        gFxBtns[15] = true;
        gFxBtns[6] = true;
    }else{
        isDofDepth = false;
        gFxBtns[15] = false;
        gFxBtns[6] = false;
    }
    
    if(gEnableAutoPilotCam)
    {
        if(camera_location.z < -2500 || camera_location.z > 2500 ) {
            //terrain._enableSolidFillColor = false;
            gFxBtns[0] = true;
            //gFxBtns[11] = true;
            //gFxBtns[12] = true;
        }else{
            //terrain._enableSolidFillColor = true;
            //gFxBtns[11] = false;
            //gFxBtns[12] = false;
        }
        
       
    }
    
    // Enable/Disable the selected effects
    for (int i = 0; i < post.size(); i++) {
        post[i]->setEnabled(gFxBtns[i]);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAlphaBlending();                                       // Enable Alpha Blending
    

    // SOUND INPUT ANALYSIS
    if(isSoundInteractionEnabled)
    {
        int numBins = terrain.getColNum();
        if(numBins > audioPeakBuf.size()) {
            audioPeakBuf.clear();
            audioPeakBuf.resize(numBins);
        }
        audioPeakBuf = fftLive.getFftPeakData();
        
        //audioData = new float[numBins];
        //fftLive.getFftPeakData(audioData, numBins);
        //terrain.setFFTArray(audioData, numBins);
       
        terrain.setAvgPeak(fftLive.getAveragePeak());
        terrain.setFFTArray(audioPeakBuf, numBins);
    }
    

    if(gEnableDepth) ofEnableDepthTest();                           // Enable mesh depth sorting
  
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    ofEnableLighting();                                             // Enable global lighting
    dof.begin();                                                    // DOF begin
    cam.begin(dof.getDimensions());                                 // Start 3D camera

    light.enable();                                                 // ENABLE LIGHT OBJECT
    
    ofPushMatrix();                                                 // PUSH MATRIX
    ofTranslate(-terrain.getWidth()*0.5,-terrain.getHeight()*0.5);  // Translation to center terrain object
    terrain.draw();                                                 // Draw terrain
    
    // DRAW WANDERING PARTICLES
    for (int i = 0; i < particles.size(); i++) {
        particles[i].setSize(terrain.getWidth(), terrain.getHeight(), terrain.getMeshDispZ());
        particles[i].color = gParticleColor;
        particles[i].draw();
        
        if(gParticleEnableLines2)
        checkConnections(particles[i].getPosition());               // Connect particles to terrain vertices
    }
    if(gParticleEnableLines)
    connectAgents();                                                // Connect oarticles to each other
    
    
    // Draw Environment outer box
    ofPushStyle();
    ofSetColor(255,0,0);
    ofNoFill();
    ofDrawBox(terrain.getWidth()*0.5, terrain.getHeight()*0.5,terrain.getHeight()*0.5,terrain.getWidth(), terrain.getHeight(),terrain.getHeight());
    
    ofSetSphereResolution(30);
    
    ofSetLineWidth(9);
    ofSetColor(255,0,0);
    ofTranslate(terrain.getWidth()*0.5,terrain.getHeight()*0.5);
    ofRotateXDeg(sin(ofGetElapsedTimef()*0.09)*360);
    ofRotateYDeg(sin(ofGetElapsedTimef()*0.1)*180);
    ofDrawIcoSphere(0,0,0 ,4500);
    
    ofPopStyle();
    
    ofPopMatrix();                                                    // POP MATRIX
    
    light.disable();                                                  // DISABLE LIGHT
    
    cam.end();                                                        // Stop 3D camera
    dof.end();                                                        // DOF begin
    
    ofDisableLighting();                                              // Disable Global light
    
    if(gEnableDepth) ofDisableDepthTest();                            // Disable mesh depth sorting
    
    
    
    
    //--------------------------------------------------------------
    // SAVE BEGIN
    //--------------------------------------------------------------
    if(isSave) {
        utils.saveImageBegin(ofGetWidth(), ofGetHeight());
    }
    
    
    post.begin();                                                      // begin scene to post process
    //--------------------------------------------------------------
    // DRAW SCENE TO CANVAS
    //--------------------------------------------------------------
    if(isDofDepth){
        dof.drawFocusAssist(0, 0);
    }
    else{
        dof.getFbo().draw(0, 0);
    }
    
    post.end();                                                         // end scene to post process
    
    //--------------------------------------------------------------
    // SAVE END
    //--------------------------------------------------------------
    if(isSave) {
        utils.saveImageEnd();
        isSave = false;
    }
    
    ofDisableAlphaBlending();                                           // Disable Alpha Blending
    
    // GUI & DEBUG RELATED
    if(isDebug)
    {
        gui.draw();
        guiDOF.draw();
        guiParticle.draw();
        guiEffect.draw();
        light.draw();                                                   // DRAW LIGHT
        utils.drawFPS(ofxFilikaAlignment::TOP_LEFT);                    // DRAW FPS
    }
    
    
    // SOUND INPUT ANALYSIS
    if(isSoundInteractionEnabled)
    {
        //delete[] audioData;
    }
}

void ofApp::checkConnections(glm::vec3 veci) {
    ofPushStyle();
    meshWaves.clear();
    
    for(int i = 0; i < terrain.dump.size(); i++) {
        float dist = glm::distance(veci, terrain.dump[i]);
        
        ofSetLineWidth(3);
        
        if(dist > 10 && dist < 1000) {
            
            float alpha = ofMap(dist, 10, 1000, 255, 0);
            
            meshWaves.addVertex(veci);
            meshWaves.addColor(ofColor(gParticlePrivateLineColor->r,gParticlePrivateLineColor->g,gParticlePrivateLineColor->b,alpha * audioPeakBuf[int(i%(terrain.getColNum()))]));
            
            meshWaves.addVertex(terrain.dump[i]);
            meshWaves.addColor(ofColor(gParticleWavesLineColor->r,gParticleWavesLineColor->g,gParticleWavesLineColor->b, alpha * audioPeakBuf[int(i%(terrain.getColNum()))]));
        }
    }
    meshWaves.draw();
    ofPopStyle();
}


void ofApp::connectAgents() {
    ofPushStyle();
    mesh.clear();
    for (int i = 0; i < particles.size(); i++) {
        for (int j = i; j < particles.size(); j++) {
            
            if(i != j)
            {
                ofSetLineWidth(2 * audioPeakBuf[int(i%(terrain.getColNum()))]);
                float dist = glm::distance(particles[i].getPosition(), particles[j].getPosition());
            
                if(dist > 10 && dist < 1700) {
                    float alpha = ofMap(dist, 10, 1700, 255, 0);
                    
                    mesh.addVertex(particles[i].getPosition());
                    mesh.addColor(ofColor(gParticlePrivateLineColor->r,gParticlePrivateLineColor->g,gParticlePrivateLineColor->b,alpha * fftLive.getAveragePeak()));
                    
                    mesh.addVertex(particles[j].getPosition());
                    mesh.addColor(ofColor(gParticlePrivateLineColor->r,gParticlePrivateLineColor->g,gParticlePrivateLineColor->b));
                }
            }
        }
    }
    
    mesh.draw();
    ofPopStyle();
}

void ofApp::initPostProcessing() {
    /* POST PROCESSING */
    // Setup post-processing chain
    post.getPasses().clear();
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<BloomPass>()->setEnabled(false);
    post.createPass<BleachBypassPass>()->setEnabled(false);
    post.createPass<ContrastPass>()->setEnabled(false);
    post.createPass<ConvolutionPass>()->setEnabled(false);
    //post.createPass<DofPass>()->setEnabled(false);
    //post.createPass<DofAltPass>()->setEnabled(false);
    //post.createPass<EdgePass>()->setEnabled(false);
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<FakeSSSPass>()->setEnabled(false);
    //post.createPass<GodRaysPass>()->setEnabled(false);
    post.createPass<HorizontalTiltShifPass>()->setEnabled(false);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    post.createPass<LimbDarkeningPass>()->setEnabled(false);
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<RimHighlightingPass>()->setEnabled(false);
    post.createPass<SSAOPass>()->setEnabled(false);
    post.createPass<ToonPass>()->setEnabled(false);
    post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    post.createPass<ZoomBlurPass>()->setEnabled(false);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        ofToggleFullscreen();
    }else if(key == 'g') {
        isDebug = !isDebug;
    }else if(key == 's') {
        utils.isSaved = false;
        isSave = !isSave;
        
    }else if(key == 'd') {
        isDofDepth = true;
        gFxBtns[15] = true;
        gFxBtns[6] = true;
        
    }else if(key == '.') {
        terrain._enableSolidFillColor ^= true;
    }else if(key == '<') {
        gEnableAutoPilotCam = !gEnableAutoPilotCam;
    }else if(key == 'z') {
        gParticleEnableLines = !gParticleEnableLines;
    }else if(key == 'x') {
        gParticleEnableLines2 = !gParticleEnableLines2;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'd') {
        isDofDepth = false;
        gFxBtns[15] = false;
        gFxBtns[6] = false;
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
    gui.setPosition(ofGetWidth() - 310,10);
    guiDOF.setPosition(ofGetWidth() - 614,10);
    guiParticle.setPosition(ofGetWidth() - 818,10);
    guiEffect.setPosition(ofGetWidth() - 976,10);
    // todo : there is something related to dof reinitiation
    //dof.setup(w, h);
    initPostProcessing();

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
