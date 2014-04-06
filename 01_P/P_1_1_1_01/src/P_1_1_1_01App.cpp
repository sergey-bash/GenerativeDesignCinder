#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_1_1_01App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
    
private:
    Vec2i mMousePos;
};

void P_1_1_1_01App::setup()
{
    setWindowSize(800, 400);
}

void P_1_1_1_01App::mouseDown( MouseEvent event )
{
}

void P_1_1_1_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
    if (mMousePos.x < 0) mMousePos.x = 0;
    if (mMousePos.y < 0) mMousePos.y = 0;
}

void P_1_1_1_01App::update()
{
}

void P_1_1_1_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    float stepX = mMousePos.x + 2;
    float stepY = mMousePos.y + 2;
    
    for (int gridY = 0; gridY < getWindowHeight(); gridY += stepY)
    {
        for (int gridX = 0; gridX < getWindowWidth(); gridX += stepX)
        {
            gl::color(Colorf(ColorModel::CM_HSV, float(gridX) / getWindowWidth(), 1.0 - float(gridY) / getWindowHeight(), 1.0));
            gl::drawSolidRect(Rectf(gridX, gridY, gridX + stepX, gridY + stepY));
        }
    }
}

CINDER_APP_NATIVE( P_1_1_1_01App, RendererGl )
