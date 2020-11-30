#pragma once

#include "ofMain.h"

enum FlipDirection { UP, DOWN, LEFT, RIGHT };

class ofxKTFlipper {
    
public:
    
    void setup();
    void update();
    void drawStringOutlineInBox(string text, ofRectangle boundingBox, Boolean bKeepAspectRatio);
    
    ofTrueTypeFont* font;
    
    string currentText, nextText;
    
    glm::vec2 textDimensions;
    glm::vec2 textPosition;
    float flipSpeed;
    bool isFlipping;
    FlipDirection flipDirection;
    float flipPercent;
    bool bKeepAspectRatio;
    
    glm::vec2 scale;
    glm::vec2 current;
    glm::vec2 center;
    
    ofFbo fbo;
    
};
