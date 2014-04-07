#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_1_2_01App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event);
	void update();
	void draw();
private:
    Vec2f mMousePos;
    int mSegmentCount;
    float mRadius;
    TriMesh2d mTriMesh;
};

void P_1_1_2_01App::setup()
{
    setWindowSize(800, 800);
    mSegmentCount = 360;
    mRadius = 300;
}

void P_1_1_2_01App::update()
{
    mTriMesh.clear();
    Vec2f center = Vec2f(getWindowWidth() / 2, getWindowHeight() / 2);
    
    float segmentAngle = 2.0f * M_PI / mSegmentCount;
    for (int i = 0; i < mSegmentCount; i++)
    {
        Colorf color(ColorModel::CM_HSV, float(i) / mSegmentCount,
                     mMousePos.x / getWindowWidth(),
                     mMousePos.y / getWindowHeight());
        float currentAngle = segmentAngle * i;
        Vec2f first = Vec2f(mRadius * cos(currentAngle - segmentAngle / 2.0f),
                            mRadius * sin(currentAngle - segmentAngle / 2.0f)) + center;
        Vec2f second = Vec2f(mRadius * cos(currentAngle + segmentAngle / 2.0f),
                             mRadius * sin(currentAngle + segmentAngle / 2.0f)) + center;
        mTriMesh.appendVertex(center);
        mTriMesh.appendVertex(first);
        mTriMesh.appendVertex(second);
        mTriMesh.appendColorRgb(color);
        mTriMesh.appendColorRgb(color);
        mTriMesh.appendColorRgb(color);
        mTriMesh.appendTriangle(i*3, i*3 + 1, i*3 + 2);
    }
}

void P_1_1_2_01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    gl::draw(mTriMesh);
}

void P_1_1_2_01App::mouseDown( MouseEvent event )
{
}

void P_1_1_2_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_1_1_2_01App::keyUp( KeyEvent event )
{
    switch (event.getChar()) {
        case '1':
        mSegmentCount = 360;
        break;
        
        case '2':
        mSegmentCount = 45;
        break;
        
        case '3':
        mSegmentCount = 24;
        break;
        
        case '4':
        mSegmentCount = 12;
        break;
        
        case '5':
        mSegmentCount = 6;
        break;
        
        default:
        break;
    }
}

CINDER_APP_NATIVE( P_1_1_2_01App, RendererGl )
