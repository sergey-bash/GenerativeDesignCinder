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
 *
 * KEYS
 * 1-3                 : stroke color
 * del, backspace      : erase
 */
class P_2_0_03App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void keyUp( KeyEvent event);
	void update();
	void draw();
private:
    Vec2i mMousePos;
    bool mIsMousePressed;
    bool mClear;
    ColorAf mStrokeColor;
};

void P_2_0_03App::setup()
{
    setWindowSize(720, 720);
    mIsMousePressed = false;
    mClear = true;
    mStrokeColor = ColorAf(0, 0, 0, 10.0f / 255.0f); // Alpha in Processing ranges from 0 to 255
    gl::enableAlphaBlending();
}

void P_2_0_03App::update()
{
}

void P_2_0_03App::draw()
{
	if (mClear) {
        gl::clear( Color( 1, 1, 1 ) );
        mClear = false;
    }
    
    if (!mIsMousePressed) return;
    
    gl::pushMatrices();
    gl::translate(getWindowWidth() / 2, getWindowHeight() / 2);
    
    int circleResolution = lmap(float(mMousePos.y), 0.0f, float(getWindowHeight()), 2.0f, 10.0f);
    float radius = mMousePos.x - getWindowWidth() / 2 + 0.5;
    float angle = 2.0f * M_PI / circleResolution;
    
    gl::lineWidth(2.0f);
    gl::color(mStrokeColor);
    
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

void P_2_0_03App::mouseDown( MouseEvent event )
{
    mIsMousePressed = true;
    mMousePos = event.getPos();
}

void P_2_0_03App::mouseUp( MouseEvent event )
{
    mIsMousePressed = false;
}

void P_2_0_03App::mouseDrag( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_0_03App::keyUp( KeyEvent event )
{
    switch (event.getChar()) {
        case '1':
        mStrokeColor = ColorAf(0, 0, 0, 10.0f / 255.0f);
        break;
        case '2':
        mStrokeColor = ColorAf(ColorModel::CM_HSV, 192.0f / 360.0f, 1.0, 0.64, 10.0f / 255.0f);
        break;
        case '3':
        mStrokeColor = ColorAf(ColorModel::CM_HSV, 52.0f / 360.0f, 1.0, 0.71, 10.0f / 255.0f);
        break;
        default:
        break;
    }
    
    if (event.getCode() == KeyEvent::KEY_DELETE || event.getCode() == KeyEvent::KEY_BACKSPACE) mClear = true;
}

CINDER_APP_NATIVE( P_2_0_03App, RendererGl )
