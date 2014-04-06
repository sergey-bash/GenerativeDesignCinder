#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_0_01App : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
    
private:
    Vec2i mMousePos;
};

void P_1_0_01App::setup()
{
    setWindowSize(720, 720);
}

void P_1_0_01App::mouseDown( MouseEvent event )
{
}

void P_1_0_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_1_0_01App::update()
{
}

void P_1_0_01App::draw()
{
	// clear out the window with black
	gl::clear( Color(ColorModel::CM_HSV, float(mMousePos.y) / getWindowHeight(), 1.0, 1.0 ) );
    
    gl::color( Color(ColorModel::CM_HSV, 1.0f - float(mMousePos.y) / getWindowHeight(), 1.0, 1.0 ) );
    
    float rectSide = mMousePos.x + 1;
    gl::drawSolidRect(Rectf(getWindowWidth() / 2 - rectSide / 2,
                            getWindowHeight() / 2 - rectSide / 2,
                            getWindowWidth() / 2 + rectSide / 2,
                            getWindowHeight() / 2 + rectSide / 2));
    
}

CINDER_APP_NATIVE( P_1_0_01App, RendererGl )
