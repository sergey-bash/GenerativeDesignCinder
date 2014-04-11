#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * drawing with a changing shape by draging the mouse.
 *
 * MOUSE
 * position x          : length
 * position y          : thickness and number of lines
 * drag                : draw
 */
class P_2_0_02App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );
    void mouseDrag( MouseEvent event );
	void update();
	void draw();
private:
    Vec2i mMousePos;
    bool mIsMousePressed;
};

void P_2_0_02App::setup()
{
    setWindowSize(720, 720);
    mIsMousePressed = false;
    gl::enableAlphaBlending();
}

void P_2_0_02App::update()
{
}

void P_2_0_02App::draw()
{
	// clear out the window with black
	if (getElapsedFrames() == 1) gl::clear( Color( 1, 1, 1 ) );
    
    if (!mIsMousePressed) return;
    
    gl::pushMatrices();
    gl::translate(getWindowWidth() / 2, getWindowHeight() / 2);
    
    int circleResolution = lmap(float(mMousePos.y), 0.0f, float(getWindowHeight()), 2.0f, 10.0f);
    float radius = mMousePos.x - getWindowWidth() / 2 + 0.5;
    float angle = 2.0f * M_PI / circleResolution;
    
    gl::lineWidth(2.0f);
    gl::color(ColorAf(0, 0, 0, 0.1f));
    
    gl::begin(GL_LINE_STRIP);
    for (int i = 0; i <= circleResolution; i++)
    {
        float x = cos(angle * i) * radius;
        float y = sin(angle * i) * radius;
        gl::vertex(Vec2f(x, y));
    }
    gl::end();
    
    gl::popMatrices();
    
}

void P_2_0_02App::mouseDown( MouseEvent event )
{
    mIsMousePressed = true;
}

void P_2_0_02App::mouseUp( MouseEvent event )
{
    mIsMousePressed = false;
}

void P_2_0_02App::mouseDrag( MouseEvent event )
{
    mMousePos = event.getPos();
}

CINDER_APP_NATIVE( P_2_0_02App, RendererGl )
