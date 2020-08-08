//
//  c32_Catenoid.h
//  example_AV_Template
//
//  Created by alp tugan on 10.07.2020.
//

#ifndef c32_Catenoid_h
#define c32_Catenoid_h

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDropdown.h"


class c32_Catenoid  {
private:
    ofVboMesh vbo;
    
    ofParameter<float> audioMaxFac = {"Audio Threshold",0.0,0.0,2.0};
    ofParameter<float> total = {"Number Of Points", 30, 10, 1000};
    ofParameter<float> scl  = {"Distance Between Points", 50, 1, 200};
    ofParameter<float> c = {"c Constant", 0.01, -100, 100};
    ofParameter<float> vRange = {"v Range", 0.1, -100, 100};
    ofParameter<bool> enableLights = {"Enable Lights", true};
    ofParameter<glm::vec3> lightPos = {"Light Position", glm::vec3(0,0,1000), glm::vec3(-3000),glm::vec3(3000)};
    ofParameter<float> depth = {"Depth", 0.0, 0, 30};
    ofParameterGroup sceneGui;
    ofParameterGroup AnimGui;
    ofParameter<bool> animEnable = {"Enable Animation", false};
    ofParameter<float> animSpeed = {"Speed", 0.05, -2, 2};
    ofParameter<float> animAmt = {"Animation Amount", 20, 0, 100};
    ofParameter<float> rotZ = {"Enable Vertical Rotation", 1, 0 , 10};
    ofParameter<int> lineThickness = {"Line Thickness", 2, 1, 8};
    
    ofParameterGroup guiCamGroup;
    ofParameter<bool> camAutoPilot = {"Enable Cam Auto Movement", false};
    ofParameter<float> camMoveSpeed = {"Cam Movement Speed", 0.0045, 0, 1};
    ofParameter<glm::vec3> camMoveRange = {"Cam Movement Range", glm::vec3(300), glm::vec3(-2000), glm::vec3(2000)};
    
    ofParameter<float> dumpSize = {"Size", 5000, 0 , 10000};
    ofxPanel gui;
    
    // Dropdown Menu
    ofParameter<int> modes;
    unique_ptr<ofxIntDropdown> intDropdown;
    
    vector<glm::vec3> origPoints;
    float flowAmt;
    ofEasyCam cam;
    ofLight light;
    
    // Cam path Locations
    vector<glm::vec3> log_list;
    
public:
    
    c32_Catenoid() {
        gui.setup("Cateneoid Surface Parameters");
        
        sceneGui.setName("3D Scene Parameters");
        gui.add(total);
        gui.add(scl);
        gui.add(vRange);
        gui.add(c);
        gui.add(depth);
        
        sceneGui.add(enableLights);
        sceneGui.add(lightPos);
        modes.setName("CHANGE DRAWING MODE");
        intDropdown =  make_unique<ofxIntDropdown>(modes);
        intDropdown->enableCollapseOnSelection();
        
        // Dropdown contents
        intDropdown->add(0, "WIREFRAME");
        intDropdown->add(1, "POINTS");
        intDropdown->add(2, "FILL");
        gui.add(intDropdown.get());
        
        gui.add(sceneGui);
        
        AnimGui.setName("ANIMATION PARAMETERS");
        AnimGui.add(animEnable);
        AnimGui.add(animSpeed);
        AnimGui.add(animAmt);
        AnimGui.add(rotZ);
        AnimGui.add(dumpSize);
        gui.add(AnimGui);
        
        guiCamGroup.setName("3D CAM MOVEMENT");
        guiCamGroup.add(camAutoPilot);
        guiCamGroup.add(camMoveSpeed);
        guiCamGroup.add(camMoveRange);
        gui.add(guiCamGroup);
        
        /*isOrtho(false),
        fov(60),
        nearClip(0),
        farClip(0),
        lensOffset(0.0f, 0.0f),
        forceAspectRatio(false),
        aspectRatio(4./3.),
        vFlip(false)*/
        cam.setNearClip(0);
        cam.setFarClip(7000);

        
        light.setup();
        
        
        gui.loadFromFile("settings.xml");
        
        setup();
    }
    
    ~c32_Catenoid() {}
    
    void setup() {
        
    }
    
    void update() {
        light.setPosition(lightPos);
        
        /* CAM AUTO PILOT */
        //if(camAutoPilot)
        //{
            auto noise_seed     = glm::vec3(0.304, 0.096, 0.6);
            auto noise_location = glm::vec3(
                                            ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * camMoveSpeed), 0, 1, -camMoveRange->x, camMoveRange->x),
                                            ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * camMoveSpeed), 0, 1, -camMoveRange->y, camMoveRange->y),
                                            ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * camMoveSpeed), 0, 1, -camMoveRange->z, camMoveRange->z)
                                            );
            this->log_list.push_back(noise_location);
            
            while (this->log_list.size() > 30) {
                this->log_list.erase(this->log_list.begin());
                
            }
        //}
    }
    
    void draw() {
        ofPushMatrix();
        ofPushStyle();
        ofSetLineWidth(lineThickness);
       
        
        if(enableLights)
        {
            ofEnableLighting();
            light.enable();
        }
        
        /* CAM AUTO PILOT */
        // Auto cam pilot path
        if(camAutoPilot)
        {
            auto direction = this->log_list[this->log_list.size() * 0.25] - this->log_list[this->log_list.size() - 1];
            this->cam.lookAt(this->log_list[this->log_list.size() - 1]);
            this->cam.setPosition(this->log_list[this->log_list.size() - 1] + direction);
        }
    
        cam.begin();
        
        ofEnableDepthTest();
       
        ofSetColor(255,0,0);
        ofDrawSphere(this->log_list.back(), 2);
        
        //ofNoFill();
        ofPushMatrix();
        ofRotateDeg(90, 1, 0, 0);
        //ofDrawBox(0, 0, 0, 800);
        generateCatenoid();
        
        ofRotateZDeg(rotZ*ofGetFrameNum());
        if(modes.get() == 0)
            vbo.draw(ofPolyRenderMode::OF_MESH_WIREFRAME);
        else if(modes.get() == 1)
            vbo.draw(ofPolyRenderMode::OF_MESH_POINTS);
        else if(modes.get() == 2)
            vbo.draw(ofPolyRenderMode::OF_MESH_FILL);
        
        ofPopMatrix();
        
        
        
        cam.end();
        
        
        
        ofDisableDepthTest();
        
        if(enableLights)
        {
            ofDisableLighting();
            light.disable();
        }
        

        
        ofPopStyle();
        ofPopMatrix();
        
        gui.draw();
    }
    
    
    void generateCatenoid() {
        // -inf <= v <= inf
        //  -PI <= u <= PI
        //  c is a non-zero real constant.
        glPointSize(lineThickness);
        vbo.clear();
        
        total = floor(total);
        
        origPoints.clear();
        for (int i = 0; i < total; i++) {
            float v = ofMap(i, 0, total - 1, -vRange, vRange);
            
            for(int j = 0; j < total; j++) {

                float u = ofMap(j, 0, total - 1, 0, TWO_PI);

                glm::vec3 p;
                
                p.x = c * cosh( v / c) * cos( u ) * scl;
                p.y = c * cosh( v / c) * sin( u ) * scl;
                p.z = v * scl * depth;
                
                origPoints.push_back(p);
                vbo.addVertex(p);
                
                vbo.addColor(ofColor(255));
            }
        }
        
        
        for (int j = 0; j < total - 1; j++) {
            for (int i = 0 ; i < total - 1; i++) {
                
                vbo.addIndex(i+j*total);         // 0
                vbo.addIndex((i+1)+j*total);     // 1
                vbo.addIndex(i+(j+1)*total);     // 6
                
                vbo.addIndex((i+1)+j*total);     // 1
                vbo.addIndex((i+1)+(j+1)*total); // 7
                vbo.addIndex(i+(j+1)*total);     // 6
                
            }
        }
        
        if(animEnable)
        {
            flowAmt -= animSpeed;
            float yoff = flowAmt;
            
            vector<glm::vec3> & vert = vbo.getVertices();
            int idd = 0;
            for (int i = 0; i < total; i++) {
                float xoff = 0;
                for(int j = 0; j < total; j++) {
                    
                    float nn = ofNoise(xoff,yoff) * animAmt;
                    
                    if(j != 0 && j != total - 1)
                        vert[idd].z = origPoints[idd].z + nn;
                    
                    /*if(j == 0) {
                        vert[0].z = origPoints[0].z + nn;
                        vert[(total - 1) * (i + 1)].z = vert[0].z;
                    }*/
                    
                    xoff += 0.14;
                    idd++;
                }
                yoff += 0.1;
            }
        }
        
    }
    
    void windowResized(int w, int h) {
        setup();
    }
};

#endif /* c32_Catenoid_h */
