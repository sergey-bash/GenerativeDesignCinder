#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * moving corners of rectangles in a grid
 *
 * MOUSE
 * position x          : corner position offset x
 * position y          : corner position offset y
 * left click          : random position
 */

class P_2_1_2_04App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseUp( MouseEvent event );
	void update();
	void draw();
    
private:
    Vec2i mMousePos;
    Rand mRand;
    unsigned long mRandomSeed;
    float mTileCount = 20.0f;
    float mRectSize = 30.0f;
};

void P_2_1_2_04App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
}

void P_2_1_2_04App::update()
{
}

void P_2_1_2_04App::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    
    gl::color(ColorA(ColorModel::CM_HSV, 192.0f / 360.0f, 1.0f, 0.64f, 0.6f));
    mRand.seed(mRandomSeed);
    
    for (int gridY = 0; gridY  < mTileCount; gridY++)
    {
        for (int gridX = 0; gridX < mTileCount; gridX++)
        {
            Vec2f pos = Vec2f(getWindowWidth() / mTileCount * gridX, getWindowHeight() / mTileCount * gridY);
            
            float baseShiftX = mMousePos.x / 20.0f;
            float baseShiftY = mMousePos.y / 20.0f;
            Vec2f shift1 = Vec2f(baseShiftX * mRand.nextFloat(-1, 1), baseShiftY * mRand.nextFloat(-1, 1));
            Vec2f shift2 = Vec2f(baseShiftX * mRand.nextFloat(-1, 1), baseShiftY * mRand.nextFloat(-1, 1));
            Vec2f shift3 = Vec2f(baseShiftX * mRand.nextFloat(-1, 1), baseShiftY * mRand.nextFloat(-1, 1));
            Vec2f shift4 = Vec2f(baseShiftX * mRand.nextFloat(-1, 1), baseShiftY * mRand.nextFloat(-1, 1));
            
            gl::begin(GL_TRIANGLE_STRIP);
            
            gl::vertex(pos + Vec2f(0, mRectSize) + shift2);
            gl::vertex(pos + Vec2f(mRectSize, mRectSize) + shift3);
            gl::vertex(pos + shift1);
            gl::vertex(pos + Vec2f(mRectSize, 0) + shift4);
            gl::end();
        }
    }
}

void P_2_1_2_04App::mouseDown( MouseEvent event )
{
}

void P_2_1_2_04App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_2_04App::mouseUp( MouseEvent event )
{
    mRandomSeed = mRand.nextUint();
}

CINDER_APP_NATIVE( P_2_1_2_04App, RendererGl )
