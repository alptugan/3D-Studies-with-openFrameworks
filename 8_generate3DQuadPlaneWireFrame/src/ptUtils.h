//
//  ptUtils.h
//  1_Triangular_Mesh
//
//  Created by alp tugan on 14.07.2019.
//

#ifndef ptUtils_h
#define ptUtils_h

#include "ofMain.h"

typedef enum ptAlignment {TL, TR, BR, BL} ptAlignment;

class ptUtils {
    
    
public:
    
    void drawFPS(ptAlignment _position) {
        int x = 0;
        int y = 0;
        
        switch(_position) {
            case TL:
                x = 0;
                y = 20;
                break;
            case TR:
                x = ofGetWidth() - 40;
                y = 20;
                break;
            case BR:
                x = ofGetWidth() - 40;
                y = ofGetHeight() - 20;
                break;
            case BL:
                x = 0;
                y = ofGetHeight() - 20;;
                break;
        }
        
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(),1), x, y);
        
    }
};


#endif /* ptUtils_h */
