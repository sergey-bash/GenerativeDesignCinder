#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * changing size and position of circles in a grid
 *
 * MOUSE
 * position x          : circle position
 * position y          : circle size
 * left click          : random position
 */

// (sergey) gl::lineWidth() has an upper limit, yet there seems to be no other simple way
// to draw a stroked circle
class P_2_1_2_01App : public AppNative {
public:
    void setup();
    void mouseUp( MouseEvent event );
    void mouseMove( MouseEvent event );
    void update();
    void draw();
private:
    Vec2i mMousePos;
    float mTileCount = 20;
    Colorf mCircleColor = Colorf::black();
    float mCircleAlpha = 180.0f / 255.0f;
    int mRandomSeed = 0;
    Rand mRand;
};

void P_2_1_2_01App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
}

void P_2_1_2_01App::update()
{
}

void P_2_1_2_01App::draw()
{
    // clear out the window with black
    gl::clear( Color::white() );
    
    gl::pushMatrices();
    gl::translate(getWindowWidth() / mTileCount / 2.0f, getWindowHeight() / mTileCount / 2.0f);
    
    mRand.seed(mRandomSeed);
    
    gl::color(ColorAf(mCircleColor, mCircleAlpha));
    gl::lineWidth(mMousePos.y / 60.0f);
    
    for (int gridY = 0; gridY < mTileCount; gridY++) {
        for (int gridX = 0; gridX < mTileCount; gridX++) {
            float posX = getWindowWidth() / mTileCount * gridX;
            float posY = getWindowHeight() / mTileCount * gridY;
            
            float shiftX = mRand.nextFloat(-mMousePos.x, mMousePos.x) / 20.0f;
            float shiftY = mRand.nextFloat(-mMousePos.x, mMousePos.x) / 20.0f;
            
            gl::drawStrokedCircle(Vec2f(posX + shiftX, posY + shiftY), mMousePos.y / 15.0f);
            
        }
    }
    
    gl::popMatrices();
}

void P_2_1_2_01App::mouseUp( MouseEvent event )
{
}

void P_2_1_2_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

CINDER_APP_NATIVE( P_2_1_2_01App, RendererGl )