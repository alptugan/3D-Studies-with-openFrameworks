//
//  meshTexturedPlane.h
//  7_generate3DPlaneFboTexture
//
//  Created by alp tugan on 26.07.2019.
//

#ifndef meshTexturedPlane_h
#define meshTexturedPlane_h

#include "ofxGui.h"
#include "ofMain.h"

class meshTexturedPlane {
private:
    
    ofMesh mesh;
    ofFbo fbo;
    int rows, cols;
    ofLight directional;
    
    
    ofParameter<ofColor> mColor;
    ofParameter<int> mThickness;
    ofParameter<float> nVal1,nVal2,nVal3, mAmount;
    ofParameter<int> res;
    ofParameter<bool> bDrawFbo,bAnimated, bDrawDebug, bDrawTexturedMesh, bFillMesh;
    
    
    ofPlanePrimitive plane;
public:
    ofParameterGroup parameters;
    
    meshTexturedPlane() {
        res  = 40;
    }
    
    
    ~meshTexturedPlane() {
        
    }
    
    void setup() {
        
        /*camera.setPosition(ofVec3f(0, -4.f, -10.f));
         camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
         camera.setDistance( 10 );
         camera.setNearClip( 0.1 );
         camera.setFarClip( 300 );*/
        
        
        bDrawFbo = false;
        bAnimated = true;
        
        
        // Generate parameters
        parameters.setName("C7 Mesh Web");
        parameters.add(bDrawDebug.set("Draw Debug",bDrawDebug));
        parameters.add(bDrawFbo.set("Draw FBO",bDrawFbo));
        parameters.add(bAnimated.set("Animate Mesh",bAnimated));
        parameters.add(res.set("Resolution", res, 2, 200));
        parameters.add(mThickness.set("Line Thickness", 2 , 1, 20));
        parameters.add(bFillMesh.set("Fill Mesh", true));
        parameters.add(mColor.set("Mesh Fill Color", ofColor(0,0,0,255), ofColor(0,0,0,0), ofColor(255,255,255,255)));
        
        // Noise Parameters
        //parmNoise.setName("Textured Mesh Params");
        parameters.add(bDrawTexturedMesh.set("Draw Mesh",true));
        parameters.add(nVal1.set("Noise 1D",0.0025,0.,0.01));
        parameters.add(nVal2.set("Noise 2D",0.0025,0.,0.01));
        parameters.add(nVal3.set("Noise 3D",0.075,0.,0.5));
        parameters.add(mAmount.set("Movement Amount",100,0,500));
        
        
        // Setup light
        directional.setDirectional();
        
        // Generate fbo texture
        generateFboTexture();
        
        // AddEvent listener to parameter changes
        ofAddListener(parameters.parameterChangedE(), this, &meshTexturedPlane::onParamsChanged);
    }
    
    void onParamsChanged(ofAbstractParameter & params) {
        generateFboTexture();
    }
    
    void generateFboTexture() {
        
        
        ofDisableArbTex();
        fbo.clear();
        
        float fboDiv = 1.f;
        fbo.allocate(1000/fboDiv, 1000/fboDiv, GL_RGBA,4);
        
        
        cols = fbo.getWidth() / res;
        rows = fbo.getHeight() / res;
        
        plane.set(fbo.getWidth(), fbo.getHeight(), rows+1, cols+1);
        
        fbo.begin();
        ofClear(0, 0, 0, 0);
        
        if(bFillMesh) {
            ofSetColor(mColor);
            ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
        }
        
        
        
        int numIterations = cols;
        
        for (int i = 0; i < numIterations; i++) {
            int tx = i*res + res;
            int ty = i*res + res;
            ofSetColor(255, 255, 255, 255);
            ofSetLineWidth(mThickness);
            ofDrawLine(tx, 0, tx, fbo.getHeight());
            ofDrawLine(0, ty, fbo.getWidth(), ty);
        }
        
        fbo.end();
        
        fbo.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
    
        mesh = plane.getMesh();
        ofQuaternion rquat;
        rquat.makeRotate( 90, 1, 0, 0);
        ofSeedRandom();
        float rseed = ofRandom(0, 10000);

        vector< glm::vec3 >& verts = plane.getMesh().getVertices();
        for( int i = 0; i < verts.size(); i++ ) {
            verts[i] = rquat * verts[i];
        }
        
        vector< glm::vec3 >& tcoords = plane.getMesh().getVertices();
        for( int i = 0; i < tcoords.size(); i++ ) {
            //tcoords[i].x *= 1.f;
            //tcoords[i].y *= 1.f;
        }
        
    }
    
    void update() {
        
        if(bAnimated) {
            //vector< ofVec3f >& verts = mesh.getVertices();
            vector< glm::vec3 >& verts = plane.getMesh().getVertices();
            for( int i = 0; i < verts.size(); i++ ) {
                verts[i].y = ofSignedNoise( verts[i].x*nVal1, verts[i].y*nVal2 + verts[i].z*nVal2, ofGetElapsedTimef() * nVal3 ) * mAmount;
            }
        }
    }
    
    void draw() {
        //glEnable(GL_DEPTH_TEST);
        if(bDrawFbo) {
            //ofTranslate(-fbo.getWidth()*0.5,-fbo.getHeight()*0.5);
            fbo.draw(200,200);
        }
        
        
        ofPushMatrix();
        
        if(bDrawTexturedMesh) {
            ofSetColor( 255, 255, 255, 255 );
            //ofTranslate(ofGetWidth() * 0.5 - cols*res*0.5, 0, 50);
            fbo.getTexture().bind();
            
            plane.draw();
            
            fbo.getTexture().unbind();
        }
        
        ofPopMatrix();
        
        if(bDrawDebug) {
            ofSetColor( 255, 0, 0, 200 );
            plane.drawWireframe();
        }
        
        
    }
    
    
};
#endif /* meshTexturedPlane_h */
