#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * drawing a filled circle with lines.
 *
 * MOUSE
 * position x          : length
 * position y          : thickness and number of lines
 */
class P_2_0_01App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
private:
    Vec2i mMousePos;
};

void P_2_0_01App::setup()
{
    setWindowSize(550, 550);
}

void P_2_0_01App::update()
{
}

void P_2_0_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    
    gl::pushMatrices();
    gl::translate(getWindowWidth() / 2, getWindowHeight() / 2);
    
    int circleResolution = lmap(float(mMousePos.y), 0.0f, float(getWindowHeight()), 2.0f, 80.0f);
    float radius = mMousePos.x - getWindowWidth() / 2 + 0.5;
    float angle = 2.0f * M_PI / circleResolution;
    float lineWidth = mMousePos.y / 20.0f;
    
    gl::lineWidth(lineWidth);
    gl::color(Colorf(0, 0, 0));
    
    for (int i = 0; i <= circleResolution; i++)
    {
        float x = cos(angle * i) * radius;
        float y = sin(angle * i) * radius;
        gl::drawLine(Vec2f::zero(), Vec2f(x, y));
    }
    
    gl::popMatrices();
    
}

void P_2_0_01App::mouseDown( MouseEvent event )
{
}

void P_2_0_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

CINDER_APP_NATIVE( P_2_0_01App, RendererGl )
