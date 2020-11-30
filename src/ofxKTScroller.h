#pragma once

#include "ofMain.h"

class ofxKTScroller {
    
public:
    
    void setup();
    void update();
    
    ofTrueTypeFont* font;
    
    string text;
    
    glm::vec2 textDimensions;
    glm::vec2 scrollVelocity;
    
    int xCount;
    int yCount;
    
    Boolean bKeepAspectRatio;
    
    glm::vec2 scale;
    glm::vec2 current;
    glm::vec2 center;
    
    ofFbo fbo;
    
};
