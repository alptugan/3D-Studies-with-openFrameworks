//
//  wireframeTerrainNoDiagonal.h
//  contentManager
//
//  Created by alp tugan on 17.02.2019.
//

#ifndef wireframeTerrainNoDiagonal_h
#define wireframeTerrainNoDiagonal_h

#include "ofxGui.h"
#include "ofMain.h"


class wireframeTerrainNoDiagonal {
    
private:
    
    ofParameter<float> res,  noiseOffX, noiseOffY, speed, speedOfFlow;
    ofParameter<bool> bDrawFbo,bAnimated, bAnimatedFlow, bDrawDebug, bDrawTexturedMesh, bEnableParticles;
    
    ofEasyCam cam;
    
    // SHELL
    vector<vector<glm::vec3>> verticesList;
    vector<glm::vec3> planeVertices;
    vector<float> freqPeakArr;
    
    //TERRAIN
    ofMesh terrainMesh, terrainFillMesh;
    
    ofParameter<int> terrainW, terrainH, terrainStep, sDepthThres, lineThickness;
    ofParameter<string> info;
    ofParameter<bool> isDebug, isAnimate, isFlowing;
    
    ofParameter<ofColor> color;
    
    float xoff, yoff, flowVal;
    int rowId,colId, flowAnimStartRow;
    bool isFirstTime;
    
public:
    ofParameterGroup parameters;
    //--------------------------------------------------------------
    // METHOD: SETTERS & GETTERS
    //--------------------------------------------------------------
    void setIndiceMode(bool _val) {
       
    }
    
    int getNumCols() {
        
        return floor(terrainW / terrainStep) + 1;
    }
    
    int getNumRows() {
        
        return floor(terrainH / terrainStep) + 1;
    }
    
    vector<glm::vec3> & getVertices() {
        
        return terrainMesh.getVertices();
    }
    
    // to set selected vertex zDepth
    void setVertexPos(int _id, float _val) {
        vector<glm::vec3> & verts = terrainMesh.getVertices();
        
        float z = ofMap(_val, 0, 1, -sDepthThres, sDepthThres);
        verts[_id].z = z;
        terrainFillMesh.setVertex(_id, verts[_id]);
    }
    
    
    void setFFTArray(float audioData[], int size, int rowIndex = -1) {
        freqPeakArr.clear();
        
        if(rowId == -1)
        {
            freqPeakArr.resize(terrainMesh.getVertices().size());
        
            for(int i = 0; i < size; i++) {
                freqPeakArr[i] = audioData[(size - 1) - i];
                //freqPeakArr[i] = audioData[rand() % size];
            }
            
            //random_shuffle(freqPeakArr.begin(), freqPeakArr.end());
        } else {
            
            if(!isFirstTime) {
                isFirstTime = true;
                flowAnimStartRow = rowIndex;
            }
            
            
            int numTotalRows = getNumRows();
            this->rowId = (flowAnimStartRow * numTotalRows) - getNumCols();
            freqPeakArr.resize(size);
            
            
            for(int i = 0; i < size; i++) {
                freqPeakArr[i] = audioData[i];
            }
         
            flowAnimStartRow = flowAnimStartRow - speedOfFlow;
            if(flowAnimStartRow < 1) {
                isFirstTime = false;
            }
        }
    }
    
    //--------------------------------------------------------------
    // METHOD: SCENE CONSTRUCTOR
    //--------------------------------------------------------------
    wireframeTerrainNoDiagonal() {
        
        
    }
    
    void setup(int _terrainStep = 100, int _terrainW = 800, int _terrainH = 800, bool _isDebug = false) {
        // Set Default Terrain Values
        terrainStep = _terrainStep;
        terrainW = _terrainW;
        terrainH = _terrainH;
        isDebug = _isDebug;
        
        // Dark green (0, 59, 0)
        // Islamic green (0, 143, 17)
        // Malachite (0, 255, 65)
        
        
        // Init GUI
        parameters.setName("Terrain Setup");
        
        parameters.add(terrainStep.set("Terrain Grid Size", terrainStep, 10, 300));
        parameters.add(terrainW.set("Terrain Height", terrainW, 100, 2000));
        parameters.add(terrainH.set("Terrain Width", terrainH, 100, 2000));
        parameters.add(color.set("WireFrame Color", ofColor(0, 255, 65), ofColor(0), ofColor(255)));
        parameters.add(lineThickness.set("Wireframe Thickness",1, 1, 8));
        parameters.add(isAnimate.set("Enable Animation Z", false));
        parameters.add(isFlowing.set("Enable Flowing Animation", true));
        parameters.add(speedOfFlow.set("Speed of Flow",1,0,10));
        parameters.add(sDepthThres.set("Z Movement Threshold", 100, -500, 500));
        parameters.add(speed.set("Flow Speed", 0.001, -1, 1));
        parameters.add(noiseOffX.set("Noise X", 0.12, 0, 1));
        parameters.add(noiseOffY.set("Noise Y", 0.21, 0, 1));
        parameters.add(isDebug.set("Enable/Disable Debug",isDebug ));
        parameters.add(info.set("Vertex Count = 0"));
        
        // Add gui listeners
        terrainStep.addListener(this, &wireframeTerrainNoDiagonal::terrainRefresh);
        terrainW.addListener(this, &wireframeTerrainNoDiagonal::terrainRefresh);
        terrainH.addListener(this, &wireframeTerrainNoDiagonal::terrainRefresh);
        
        //generateShell();
        
        xoff = 0;
        yoff = 0;
        
        generateTerrainVertices();
        
        isFirstTime = false;
        
        bEnableParticles = true;

    }
    
    //--------------------------------------------------------------
    // METHOD: TERRAIN RE-GENARATE WHENEVER a property is changed update mesh
    //--------------------------------------------------------------
    void terrainRefresh(int & _val) {
        generateTerrainVertices();
    }
    
    //--------------------------------------------------------------
    // METHOD: GENERATE TERRAIN VERTICES
    //--------------------------------------------------------------
    void generateTerrainVertices() {
         //ofSetLineWidth(4);
        
        
        //terrainMesh.setMode(OF_PRIMITIVE_POINTS);
        
        // Find the number of columns and rows
        int colNum = terrainW / terrainStep;
        int rowNum = terrainH / terrainStep;
        
        // Clear Current Mesh
        terrainMesh.clear();
        // Set mesh mode to GL LINES
        terrainMesh.setMode(OF_PRIMITIVE_LINES);
        
        
        // Generate vertex points for Wireframe
        for (int i = 0; i <= terrainW; i = i + terrainStep) {
            for (int j = 0; j <= terrainH; j = j + terrainStep) {
                // first y - columns - j
                // then x  - rows - i
                float z = 0; //ofMap(ofNoise(i*0.02, j*0.02),0,1, -sDepthThres, sDepthThres);
                terrainMesh.addVertex(glm::vec3(j,i,z));
            }
        }
        
        // Info shows vertices number
        info = "Vertex Count= " + ofToString(terrainMesh.getVertices().size());
        
        // Difference between rows and columns to supply algorithm
        int diffFac = rowNum - colNum;
        
        // Loop through vertices to set indices on the fly
        for (int i = 1; i < terrainMesh.getVertices().size() + 1; i++) {
            // GENERATES HORIZONTAL INDICES
            if(i < terrainMesh.getVertices().size() - rowNum) {
                // When rowNum > colNum calculate diffFac else it should be negative
                if(rowNum > colNum) {
                    diffFac = rowNum - colNum + 1;
                }else{
                    diffFac = (colNum - rowNum - 1)*-1;
                }
                
                // When rowNum = colNum
                if( rowNum == colNum) {
                    diffFac = 1;
                }
                
                // Add indices according to algorithm
                terrainMesh.addIndex(i - 1);
                terrainMesh.addIndex((i - 1) + colNum + diffFac);
            }
            
            // GENERATES VERTICAL INDICES
            if(i % (rowNum + 1) != 0) {
                terrainMesh.addIndex(i-1);
                terrainMesh.addIndex(i);
            } else {}
        }
        
        
        // Generate vertex fill points for Solid color Mesh
        terrainFillMesh.clear();
        terrainFillMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        float scl = terrainStep;
        float rows = colNum + 1;
        float cols = rowNum + 1;
        for (int j = 0; j < rows; j++) {
            for (int i = 0 ; i < cols; i++) {
                
                float x = i*scl;
                float y = j*scl;
                //float z = ofRandom(-10,10);
                float z =  0;
                terrainFillMesh.addVertex(ofVec3f(x,y,z));
                terrainFillMesh.addColor(ofColor(0,59,0));
                //mesh.addColor(ofFloatColor(ofMap(z,-50,50,0,1),ofMap(z,-50,50,0,1),ofMap(z,-50,50,0,1),1));
             
            }
        }
        
        
        // Generate order of indices to set triangles per rows and column
        for (int j = 0; j < rows - 1 ; j++) {
            for (int i = 0 ; i < cols - 1; i++) {
                
                terrainFillMesh.addIndex(i+j*cols);         // 0
                terrainFillMesh.addIndex((i+1)+j*cols);     // 1
                terrainFillMesh.addIndex(i+(j+1)*cols);     // 6
                
                terrainFillMesh.addIndex((i+1)+j*cols);     // 1
                terrainFillMesh.addIndex((i+1)+(j+1)*cols); // 7
                terrainFillMesh.addIndex(i+(j+1)*cols);     // 6
            }
        }
        
        planeVertices = terrainMesh.getVertices();
        
        
    }
    
    //--------------------------------------------------------------
    // METHOD: UPDATE
    //--------------------------------------------------------------
    void update() {
        
        
    }
    
    //--------------------------------------------------------------
    // METHOD: DRAW
    //--------------------------------------------------------------
    void draw() {
        
        ofSetLineWidth(lineThickness);
        
        // Animate through terrain vertices
        if(terrainMesh.getVertices().size() > 0)
        {
            vector<glm::vec3> & verts = terrainMesh.getVertices();
            int idd = 0;
            if(isAnimate) {
                
                //yoff = 0;
                flowVal += speed;
                
                
                yoff = flowVal;
                for (int i = 0; i <= terrainW; i = i + terrainStep) {
                    xoff = 0;
                    for (int j = 0; j <= terrainH; j = j + terrainStep) {
                        float z = ofMap(ofNoise(xoff, yoff),0,1, -sDepthThres, sDepthThres);
                        //terrainMesh.setVertex(idd, glm::vec3(terrainMesh.getVertex(idd).x,terrainMesh.getVertex(idd).y,z));
                        verts[idd].z = z + ((freqPeakArr.size() > 0) ? freqPeakArr[idd] * 100 : 0);
                        terrainFillMesh.setVertex(idd, verts[idd]);
                        
                        xoff += noiseOffX;
                        idd++;
                    }
                    yoff += noiseOffY;
                }
            } else if(isFlowing) {
              
                
                for (int i = 0; i <= terrainW; i = i + terrainStep) {
                    float z = 0; //ofMap(ofNoise(xoff, yoff),0,1, -sDepthThres, sDepthThres);
                    //terrainMesh.setVertex(idd, glm::vec3(terrainMesh.getVertex(idd).x,terrainMesh.getVertex(idd).y,z));
                    verts[this->rowId + idd].z = z + ((freqPeakArr.size() > 0) ? freqPeakArr[idd] * 100 : 0);
                    terrainFillMesh.setVertex(this->rowId + idd, verts[this->rowId + idd]);
                    
                    idd++;
                }
                

            }
        }
        
        ofEnableDepthTest();
        this->cam.begin();
        
        ofPushMatrix();
            ofScale(1,-1,1);
            ofTranslate(-terrainW*0.5, -terrainH*0.5);
        
            ofPushMatrix();
                ofTranslate(0,0, -0.1);
                terrainFillMesh.draw();
            ofPopMatrix();
            // Draw terrain
            drawTerrain();
        
        ofPopMatrix();
        this->cam.end();
        
        // Draw Shell
        //drawShell();
        
        ofDisableDepthTest();
    }
    
    //--------------------------------------------------------------
    // METHOD: DRAW TERRAIN
    //--------------------------------------------------------------
    void drawTerrain() {
        ofSetColor(color);
        
        

        terrainMesh.draw();
        
        
        if(isDebug) {
            for (int i = 0; i < terrainMesh.getVertices().size(); i++) {
                ofDrawBitmapStringHighlight(ofToString(i),terrainMesh.getVertex(i).x, terrainMesh.getVertex(i).y);
                ofSetColor(200, 0, 0);
                ofDrawCircle(terrainMesh.getVertex(i).x, terrainMesh.getVertex(i).y, 3);
            }
        }
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //--------------------------------------------------------------
    // METHOD: DRAW SHELL MESH
    //--------------------------------------------------------------
    void drawShell() {
        this->cam.begin();
        ofNoFill();
        int sound_index = 0;
        for (auto vertices : this->verticesList) {
            
            ofBeginShape();
            for (auto vertex : vertices) {
                
                float noise_value = ofMap(ofNoise(vertex.x * 0.005, vertex.y * 0.005, vertex.z * 0.005, ofGetFrameNum() * 0.05), 0, 1, 0.8, 1.0);
                ofVertex(vertex.x, vertex.y, vertex.z * noise_value);
            }
            ofEndShape(true);
        }
        
        this->cam.end();
    }
    
    //--------------------------------------------------------------
    // METHOD: GENERATE SHELL POINTS
    //--------------------------------------------------------------
    void generateShell() {
        
        //ofSetLineWidth(1);
        
        // Parameter reference by https://twitter.com/ru_sack/status/798308368007892992
        
        float a = 1.25;
        float b = 1.25;
        float c = 1.0;
        float h = 3.5;
        float k = 0;
        float w = 0.12;
        int R = 1;
        int scale = 100;
        
        float u_step = 0.15;
        int v_step = 15;
        for (float u = -35; u <= -1; u += u_step) {
            
            for (int v = 0; v <= 360; v += v_step) {
                
                vector<glm::vec3> vertices;
                vertices.push_back(this->make_shell_point(a, b, c, h, k, u + u_step * 0.5, (v + v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
                vertices.push_back(this->make_shell_point(a, b, c, h, k, u + u_step * 0.5, (v - v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
                vertices.push_back(this->make_shell_point(a, b, c, h, k, u - u_step * 0.5, (v - v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
                vertices.push_back(this->make_shell_point(a, b, c, h, k, u - u_step * 0.5, (v + v_step * 0.5) * DEG_TO_RAD, w, R) * scale);
                this->verticesList.push_back(vertices);
            }
        }
    }
    //--------------------------------------------------------------
    // METHOD RETURN: CALCULATES SHELL POINTS
    //--------------------------------------------------------------
    glm::vec3 make_shell_point(float a, float b, float c, float h, float k, float u, float v, float w, int R) {
        
        float x = (h + a * cos(v)) * exp(w * u) * cos(c * u);
        float y = R * (h + a * cos(v)) * exp(w * u) * sin(c * u);
        float z = (k + b * sin(v)) * exp(w * u);
        
        return glm::vec3(x, y, z);
    }
};

#endif /* c8_Particle_Circular_Motion_h */
