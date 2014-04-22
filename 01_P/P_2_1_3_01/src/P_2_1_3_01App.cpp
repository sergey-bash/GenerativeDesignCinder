#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * changing circle amount, size and position in a grid
 *
 * MOUSE
 * position x          : circle amount and size
 * position y          : circle position
 * left click          : random position
 */
class P_2_1_3_01App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
    
private:
    Vec2i mMousePos;
    
    float mTileCountX = 10;
    float mTileCountY = 10;
    float mTileWidth, mTileHeight;
    
    int mCount = 0;
    int mColorStep = 15;
    int mCircleCount;
    float mEndSize, mEndOffset;
    
    unsigned long mRandomSeed;
    Rand mRand;
    
};

void P_2_1_3_01App::setup()
{
    setWindowSize(800, 800);
    mTileWidth = getWindowWidth() / mTileCountX;
    mTileHeight = getWindowHeight() / mTileCountY;
    gl::enableAlphaBlending();
}

void P_2_1_3_01App::update()
{
}

void P_2_1_3_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    
    gl::color(0, 0, 0, 0.5f);
    
    mRand.seed(mRandomSeed);
    
    gl::pushMatrices();
    gl::translate(mTileWidth / 2.0f, mTileHeight / 2.0f);
    
    mCircleCount = mMousePos.x / 30.0f + 1.0f;
    
    mEndSize = lmap(float(mMousePos.x), 0.0f, float(getWindowWidth()), mTileWidth / 2.0f, 0.0f);
    mEndOffset = lmap(float(mMousePos.y), 0.0f, float(getWindowHeight()), 0.0f, (mTileWidth - mEndSize)/2.0f);
    
    for (int gridY = 0; gridY <= mTileCountY; gridY++) {
        for (int gridX = 0; gridX <= mTileCountX; gridX++) {
            gl::pushMatrices();
            gl::translate(mTileWidth * gridX, mTileHeight * gridY);
            gl::scale(Vec2f(1.0f, mTileHeight / mTileWidth));
            
            int toggle = mRand.nextInt(4);
            if (toggle == 0) gl::rotate(-90.0f);
            if (toggle == 1) gl::rotate(0.0f);
            if (toggle == 2) gl::rotate(90.0f);
            if (toggle == 3) gl::rotate(180.0f);
            
            for (int i = 0; i < mCircleCount; i++) {
                float diameter = lmap(float(i), 0.0f, mCircleCount - 1.0f, mTileWidth, mEndSize);
                float offset = lmap(float(i), 0.0f, mCircleCount - 1.0f, 0.0f, mEndOffset);
                gl::drawStrokedCircle(Vec2f(offset, 0.0f), diameter / 2.0f);
            }
            
            gl::popMatrices();
        }
    }
    
    gl::popMatrices();
}

void P_2_1_3_01App::mouseDown( MouseEvent event )
{
}

void P_2_1_3_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

CINDER_APP_NATIVE( P_2_1_3_01App, RendererGl )
