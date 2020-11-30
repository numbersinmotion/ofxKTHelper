#include "ofxKTScroller.h"

void ofxKTScroller::setup() {
    
    ofRectangle originalBoundingBox = font->getStringBoundingBox(text, 0, 0);
    
    center.x = -originalBoundingBox.getX() - originalBoundingBox.getWidth() / 2;
    center.y = -originalBoundingBox.getY() - originalBoundingBox.getHeight() / 2;
    
    scale.x = textDimensions.x / originalBoundingBox.getWidth();
    scale.y = textDimensions.y / originalBoundingBox.getHeight();
    if (bKeepAspectRatio) {
        ofRectangle boundingBoxScaled = originalBoundingBox;
        boundingBoxScaled.scaleTo(ofRectangle(0, 0, textDimensions.x, textDimensions.y), OF_ASPECT_RATIO_KEEP);
        scale.x = boundingBoxScaled.getWidth() / originalBoundingBox.getWidth();
        scale.y = boundingBoxScaled.getHeight() / originalBoundingBox.getHeight();
    }
    
    current = glm::vec2(0, 0);
    
    fbo.allocate(xCount * textDimensions.x, yCount * textDimensions.y, GL_RGBA, 4);
    fbo.begin();
        ofClear(0);
        ofPushMatrix();
            ofTranslate(current);
            ofScale(scale.x, scale.y);
            font->drawStringAsShapes(text, center.x, center.y);
        ofPopMatrix();
    fbo.end();
    
}

void ofxKTScroller::update() {
    
    current.x = fmod(current.x + scrollVelocity.x + fbo.getWidth() + textDimensions.x, fbo.getWidth() +  textDimensions.x);
    current.y = fmod(current.y + scrollVelocity.y + fbo.getHeight() + textDimensions.y, fbo.getHeight() +  textDimensions.y);
    
    fbo.begin();
        ofClear(0);
        ofSetColor(255);
        for (float i = 0; i < fbo.getWidth() + textDimensions.x; i += textDimensions.x) {
            for (float j = 0; j < fbo.getHeight() + textDimensions.y; j += textDimensions.y) {
                float xActual = fmod(current.x + i, fbo.getWidth() + textDimensions.x) - textDimensions.x;
                float yActual = fmod(current.y + j, fbo.getHeight() + textDimensions.y) - textDimensions.y;
                ofPushMatrix();
                    ofTranslate(textDimensions.x / 2, textDimensions.y / 2);
                    ofTranslate(xActual, yActual);
                    ofScale(scale.x, scale.y);
                    font->drawStringAsShapes(text, center.x, center.y);
                ofPopMatrix();
            }
        }
    fbo.end();
    
}
