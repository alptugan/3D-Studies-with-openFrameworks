//
//  particleNoise.h
//  10_generatePlane_WireFrame_SoundReactive
//
//  Created by alp tugan on 12.05.2020.
//

#ifndef particleNoise_h
#define particleNoise_h

#include "ofMain.h"

class particleNoise {
private:
    glm::vec3 noiseSeed;
    vector<glm::vec3> pos;
    vector<glm::vec3> vel;
    vector<glm::vec3> loc;
    vector<glm::vec3> top;
    int w,h,d;
    int lowerNoiseLimit;
    ofMesh mesh;
    int randTailLen, randRad;
public:
    ofColor color;
    
    void setSize(int w, int h, int lowerNoiseLimit = 0) {
        this->w = w*0.5;
        this->h = h*0.5;
        this->d = h*0.5;
        this->lowerNoiseLimit = lowerNoiseLimit;
    }
    
    glm::vec3 getPosition() {
        if(top.size() > 0)
            return top[0];
        else
            return;
    }
    
    void setup() {
        mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINE_STRIP);
        noiseSeed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
        randTailLen = 12 + ofRandom(40);
        randRad = 10 + ofRandom(20);
    }
    
    void draw(int x = 0, int y = 0, int z = 0) {
        //top.clear();
        
        auto location = glm::vec3(
                                  ofMap(ofNoise(noiseSeed.x, ofGetFrameNum() * 0.003), 0, 1, 0, w*2),
                                  ofMap(ofNoise(noiseSeed.y, ofGetFrameNum() * 0.003), 0, 1, 0, h*2),
                                  ofMap(ofNoise(noiseSeed.z, ofGetFrameNum() * 0.003), 0, 1, lowerNoiseLimit, d*2)
                                  );
        this->top.push_back(location);
        
        
        while(mesh.getVertices().size() > randTailLen) {
            //mesh.clear();
            mesh.removeVertex(0);
            
            top.erase(top.begin());
        }
        
        /* DRAW SHAPES */
        ofPushStyle();
        ofSetColor(color);
        ofNoFill();
        ofSetSphereResolution(3);
        ofSetLineWidth(6 + randRad / 30);
        
        ofPushMatrix();
        ofTranslate(top[0]);
        ofRotateDeg(ofGetFrameNum()*4, 1, 0, 1);
        ofDrawSphere(glm::vec3(0), randRad);
        ofPopMatrix();
        
        for (auto& tp : top) {
            
            mesh.addColor(ofColor(color));
            mesh.addVertex(location);
        }
        
        for(int i = 0; i < mesh.getVertices().size(); i++) {
            mesh.setColor(i, ofColor(color,ofMap(i, 0, mesh.getVertices().size(), 0, 255)));
        }
        
       
        mesh.draw();
        ofPopStyle();
    }
};
#endif /* particleNoise_h */
