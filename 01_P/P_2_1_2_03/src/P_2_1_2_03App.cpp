#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * changing size of circles in a rad grid depending the mouseposition
 *
 * MOUSE
 * position x/y        : module size and offset z
 */

class P_2_1_2_03App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
private:
    Vec2i mMousePos;
    float mTileCount = 20;
    Color mModuleColor = Color::black();
    float mModuleAlpha = 180.0f / 255.0f;
    float mMaxDistance =  500;
};

void P_2_1_2_03App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
}

void P_2_1_2_03App::update()
{
}

void P_2_1_2_03App::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    gl::color(ColorA(mModuleColor, mModuleAlpha));
    gl::lineWidth(3);
    
    float gridStepX = getWindowWidth() / mTileCount;
    float gridStepY = getWindowHeight() / mTileCount;
    for (int gridY = 0; gridY < mTileCount; gridY++)
    {
        for (int gridX = 0; gridX < mTileCount; gridX++)
        {
            float posX = gridX * gridStepX;
            float posY = gridY * gridStepY;
            float diameter = mMousePos.distance(Vec2i(posX, posY));
            diameter = diameter  / mMaxDistance * 40;
            gl::pushMatrices();
            gl::translate(posX, posY, diameter * 5);
            gl::drawStrokedRect(Rectf(0, 0, diameter, diameter));
            gl::popMatrices();
        }
    }
}

void P_2_1_2_03App::mouseDown( MouseEvent event )
{
}

void P_2_1_2_03App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

CINDER_APP_NATIVE( P_2_1_2_03App, RendererGl )
