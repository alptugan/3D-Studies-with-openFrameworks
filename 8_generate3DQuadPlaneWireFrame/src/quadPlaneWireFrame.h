//
//  quadPlaneWireFrame.h
//
//  Created by alp tugan on 15.07.2019.
//

#ifndef quadPlaneWireFrame_h
#define quadPlaneWireFrame_h

#include "ofMain.h"


class quadPlaneWireFrame {
private:
    int                     _meshW, _meshH;    // Mesh rows & columns number
    vector<glm::vec3>       _meshPoints;       // original mesh vertices
    vector<glm::vec3>       _meshPointsMoved;  // modified mesh vertices
    
    float                   _time;             // the value to iterate noise function
    ofParameter<ofColor>    _meshStrokeColor;  // Mesh Stroke Color
    ofParameter<ofColor>    _meshFillColor;    // Mesh Fill Color
    ofParameter<int>        _meshThickness;    // Mesh point size
    ofVboMesh               _mesh;             // the object to draw
    ofPlanePrimitive        plane;
    ofParameter<int>        _meshRes;          // 3d resolution of the object
    ofParameter<int>        _w, _h;            // width & height
    
    ofParameter<bool>       _enableFill;
    ofParameter<bool>       _enableTexture;    // Wrap texture onto generated plane primitive
    ofParameter<bool>       _animate;          // Animation or not
    ofParameter<glm::vec3>  _meshPosDisp;      // x,y,z displacement factor in pixels
    ofParameter<float>      _animFreq;         // the speed of movement
    ofParameter<float>      _animNoiseF1;      // Animation noise multiplier
    ofParameter<float>      _animNoiseF2;      // Animation noise multiplier
    ofParameter<glm::vec2>  _animRes;
    ofParameter<bool>       isDebug;           // Enable or Disable Debug view
    
    ofParameterGroup        meshGUI;           // Mesh Parameters
    ofParameterGroup        meshAnimGUI;       // Mesh Animation Parameters
    
    ofImage                 texture;           // Underneath solid texture Filling option with texture
    float                   preAnimFreq;       // keep track of the animation state
    ofMesh mesh;
public:
    /* SETTERS */
    void setMeshMode(ofPrimitiveMode _mode = OF_PRIMITIVE_LINES) {
        _mesh.setMode(_mode);
    }
    void setAnimation(bool _val) {
        _animate = _val;
    }
    void setMeshThickness(int _thickness) {
        _meshThickness = _thickness;
    }
    void setMeshResolution(int _res) {
        _meshRes = _res;
    }
    
    void setTexture(string _texSrc) {
        texture.load(_texSrc);                      // Load Texture
    }
    
    /* GETTERS */
    bool isAnimating() {
        return _animate;
    }
    
    ofParameterGroup getGUI() {
        return meshGUI;
    }
    
    int getWidth() {
        return _w;
    }
    
    int getHeight() {
        return _h;
    }
    
    void generateMesh(int ww, int hh, int _res, ofColor _color) {
        _meshW    = floor(_w / _meshRes);
        _meshH    = floor(_h / _meshRes);
        
        _mesh.clear();
        _meshPoints.clear();
        _meshPointsMoved.clear();
        
        _meshPoints.resize(_meshH * _meshW);
        _meshPointsMoved.resize(_meshPoints.size());
        
        for (int y = 0; y < _meshH; y++){
            for (int x = 0; x < _meshW; x++){
                
                int _id = x + (y * _meshW);
                
                _meshPoints[_id].x = x * _meshRes;           // vertex x coordinate
                _meshPoints[_id].y = y * _meshRes;           // vertex y coordinate
                _meshPoints[_id].z = 0;                      // vertex z coordinate
            
                _mesh.addVertex(_meshPoints[_id]);           // make a new vertex
                _mesh.addColor(ofColor(_meshStrokeColor->r, _meshStrokeColor->g,_meshStrokeColor->b,_meshStrokeColor->a));   // add a color at that vertex
            }
        }
        
        // the following code generates quad shape index from vertices that generated above
        for (int y = 0; y < _meshH-1; y++){
            for (int x=0; x < _meshW-1; x++){
                _mesh.addIndex(x+y*_meshW);         // 0  meshH = 9, meshW = 12
                _mesh.addIndex((x+1)+y*_meshW);     // 1
                _mesh.addIndex((x+1)+y*_meshW);     // 1
                _mesh.addIndex((x+1)+(y+1)*_meshW); // 13
                _mesh.addIndex((x+1)+(y+1)*_meshW); // 13
                _mesh.addIndex(x+(y+1)*_meshW);     // 12
                _mesh.addIndex(x+(y+1)*_meshW);     // 12
                _mesh.addIndex(x+y*_meshW);         // 0
            }
        }
        
    
        // Comment the following line to disable texture image wrapping to whole mesh
        if(_enableTexture)
            plane.resizeToTexture(texture.getTexture());
    }
    
    void setup(int _width=-1, int _height=-1, int _resolution = 60, ofColor _color = ofColor(255), int _thickness = 1) {
        
        _animate            = false;
        _animFreq           = 3;
        _animNoiseF1        = 0.05;
        _animNoiseF2        = 0.05;
        _meshRes            = _resolution;
        _meshStrokeColor    = _color;
        _meshThickness      = _thickness;
        
        if(_width == -1 || _height == -1) {
            _w        = ofGetWidth();
            _h        = ofGetHeight();
        }else{
            _w        = _width;
            _h        = _height;
        }
        
        
        
        plane.set(_w, _h);                                      // Background for quad mesh
        _meshPosDisp = glm::vec3(0,0,60);                       // Vertex z coordinate animation
        setMeshMode();                                          // Set mesh mode to OF_PRIMITIVE_LINES
        generateMesh(_w, _h, _meshRes, _meshStrokeColor);       // Generate quad wireframe
        generateGUI();                                          // Built gui for interactive parameter update
    }
    
    void draw() {
        ofDisableArbTex();
        
        ofEnableDepthTest();                                    // Enable depth sorting
        ofPushStyle();
        
        animateMesh(_animate);                                  // if animation enabled change the z coordinate of the vetices
        
        ofSetLineWidth(_meshThickness);                         // Set Mesh line thickness
        
        if(_enableFill)                                         // Fill underneath of the generated quadmesh
        {
            ofPushStyle();
            if(_enableTexture)
                texture.bind();
            else
                ofSetColor(_meshFillColor);
            
            // When depth enabled quad mesh and underlying mesh graphics creates a jitter effect.
            // Placing primitive mesh plane  a little bit lower fix the issue nearly.
            // Anyways, it's an ugly hack. Should be fixed
            plane.setPosition(0,0,-0.1);
            
            // Draw underlying plane primitive fill with color
            plane.draw();
            
            // Draws boundiries of the mesh
            //ofFloatColor color(1.0,0.0,0.0,1.0);
            //glTexParameterfv(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BORDER_COLOR, &color.r);
            //ofSetColor(color);
            //plane.drawWireframe();
            
            if(_enableTexture)
                texture.unbind();
            
            ofPopStyle();
        }
       
        _mesh.draw(); // Draw mesh
        
        ofPopStyle();
        
        ofDisableDepthTest();           // Disable depth sorting
        
        // Show vertex point indices of the mesh
        if(isDebug) {
            for (int y = 0; y < _meshH; y++){
                for (int x=0; x < _meshW; x++){
                    int _id = x + (y * _meshW);
                    ofDrawBitmapStringHighlight(ofToString(_id), x*_meshRes, y*_meshRes);
                }
            }
        }
    }
private:
    void generateGUI() {
        
        preAnimFreq = _animFreq;
        
        meshGUI.setName("Quad Mesh Parameters");
        meshAnimGUI.setName("Animation Parameters");
        
        meshGUI.add(_enableFill.set("Fill Mesh", false));
        meshGUI.add(_meshFillColor.set("Mesh Fill Color", ofColor(0,0,0,255), ofColor(0,0,0,0), ofColor(255,255,255,255)));
        meshGUI.add(_enableTexture.set("Enable Texture Image", false));
        meshGUI.add(_w.set("Mesh Width", _w, _meshRes, 5000));
        meshGUI.add(_h.set("Mesh Height", _h, _meshRes, 5000));
        meshGUI.add(_meshRes.set("Mesh Resolution", _meshRes, 5, 300));
        meshGUI.add(_meshThickness.set("Mesh Stroke Size", _meshThickness, 1, 10));
        meshGUI.add(_meshStrokeColor.set("Mesh Stroke Color", _meshStrokeColor, ofColor(0,0,0,0), ofColor(255,255,255,255)));
        
        meshAnimGUI.add(_animate.set("Enable Animation", _animate));
        meshAnimGUI.add(_meshPosDisp.set("Animation Amount", _meshPosDisp, glm::vec3(0,0,0), glm::vec3(1000,1000,1000)));
        meshAnimGUI.add(_animFreq.set("Animation Speed", _animFreq, 0, 40));
        meshAnimGUI.add(_animNoiseF1.set("Noise Multiplier X", _animNoiseF1, 0, 1));
        meshAnimGUI.add(_animNoiseF2.set("Noise Multiplier Y", _animNoiseF2, 0, 1));
        meshAnimGUI.add(_animRes.set("Animation Resolution", glm::vec2(0.1, 0.1), glm::vec2(0.01, 0.01), glm::vec2(5, 5)));
        
        meshGUI.add(meshAnimGUI);
        meshGUI.add(isDebug.set("Enable Debug", isDebug));
        
        
        ofAddListener(meshGUI.parameterChangedE(), this, &quadPlaneWireFrame::onMeshGUIChange);
    }
    
    void onMeshGUIChange(ofAbstractParameter & params) {
        generateMesh(_w, _h, _meshRes, _meshStrokeColor);

        if( params.getName() == _animate.getName() ){
            if(!_animate) {
                preAnimFreq = _animFreq;
                animateMesh(true);
                //_animFreq = 0;
            }else{
                //_animFreq = preAnimFreq;
            }
        }
    }
    
    void animateMesh(bool _enableAnimation) {
        if(_enableAnimation) {
            if(_enableFill)
                plane.set(_w, _h, _meshW, _meshH);
            
            _time = ofGetElapsedTimef();
            
            _meshPointsMoved.clear();
            
            _meshPointsMoved.resize(_meshPoints.size());
            
            for (int y = 0; y < _meshH; y++){
                for (int x = 0; x < _meshW; x++){
                    
                    int _id = x + (y * _meshW);                                     // current vertex index
                    
                    float zVal;// = ofSignedNoise(_time*_animFreq) * _meshPosDisp->z;  // Calculate z point animation
                    zVal = ofNoise((x * _animRes->x) * _animNoiseF1, (y * _animRes->y) * _animNoiseF2, _time * _animFreq) * _meshPosDisp->z;
                    
                    _meshPointsMoved[_id].x = 0;                                    // vertex x coordinate
                    _meshPointsMoved[_id].y = 0;                                    // vertex y coordinate
                    _meshPointsMoved[_id].z = zVal;                                 // vertex z coordinate
                    
                    if(_enableFill)
                        plane.getMesh().setVertex(_id, glm::vec3(_meshPoints[_id].x + _meshPointsMoved[_id].x, _meshPoints[_id].y + _meshPointsMoved[_id].y, _meshPoints[_id].z + _meshPointsMoved[_id].z));
                    
                    _mesh.setVertex(_id, glm::vec3(_meshPoints[_id].x + _meshPointsMoved[_id].x, _meshPoints[_id].y + _meshPointsMoved[_id].y, _meshPoints[_id].z + _meshPointsMoved[_id].z));
                    //mesh.setVertex(_id, glm::vec3(_mesh.getVertices()[_id].x + _meshPointsMoved[_id].x, _mesh.getVertices()[_id].y + _meshPointsMoved[_id].y, _mesh.getVertices()[_id].z + _meshPointsMoved[_id].z));
                }
            }
            
        }
        
    }
};

#endif /* quadPlane_h */
