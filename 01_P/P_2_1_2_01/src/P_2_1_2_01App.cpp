#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Vbo.h"

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

// (sergey) Had to use TriMesh and manually compose cirlce out of triangles because
//          gl::lineWidth() has an upper limit
class P_2_1_2_01App : public AppNative {
public:
    void setup();
    void mouseUp( MouseEvent event );
    void mouseMove( MouseEvent event );
    void update();
    void draw();
private:
    void drawCircleOnMesh(float innerRadius, float outerRadius);
    void appendVertex(float x, float y);
    
    Vec2i mMousePos;
    float mTileCount = 20;
    Colorf mCircleColor = Colorf::black();
    float mCircleAlpha = 180.0f / 255.0f;
    int mRandomSeed = 0;
    Rand mRand;
    TriMesh2d mCircleMesh;
};

void P_2_1_2_01App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
    
    gl::VboMesh::Layout layout;
    layout.setStaticIndices();
    layout.setDynamicPositions();
    layout.setDynamicColorsRGB();
}

void P_2_1_2_01App::update()
{
}

void P_2_1_2_01App::drawCircleOnMesh(float innerRadius, float outerRadius)
{
    const int resolution = 100;
    mCircleMesh.clear();
    
    float angleStep = 2.0f * M_PI / resolution;
    
    appendVertex(innerRadius, 0);
    appendVertex(outerRadius, 0);
    
    for (int i = 1; i <= resolution; i++)
    {
        float angle = i * angleStep;
        appendVertex(innerRadius * cos(angle), innerRadius * sin(angle));
        appendVertex(outerRadius * cos(angle), outerRadius * sin(angle));
        mCircleMesh.appendTriangle(i*2 - 2, i*2 - 1, i*2 + 1);
        mCircleMesh.appendTriangle(i*2 + 1, i*2 - 2, i*2);
    }
}

void P_2_1_2_01App::appendVertex(float x, float y)
{
    mCircleMesh.appendVertex(Vec2f(x, y));
    mCircleMesh.appendColorRgba(ColorAf(mCircleColor, mCircleAlpha));
}


void P_2_1_2_01App::draw()
{
    // clear out the window with black
    gl::clear( Color::white() );
    
    gl::pushMatrices();
    gl::translate(getWindowWidth() / mTileCount / 2.0f, getWindowHeight() / mTileCount / 2.0f);
    
    mRand.seed(mRandomSeed);
    
    gl::color(ColorAf(mCircleColor, mCircleAlpha));
    float lineWidth = mMousePos.y / 60.0f;
    float radius = mMousePos.y / 30.0f;
    
    drawCircleOnMesh(radius - lineWidth / 2.0f, radius + lineWidth / 2.0f);
    
    for (int gridY = 0; gridY < mTileCount; gridY++) {
        for (int gridX = 0; gridX < mTileCount; gridX++) {
            float posX = getWindowWidth() / mTileCount * gridX;
            float posY = getWindowHeight() / mTileCount * gridY;
            
            float shiftX = mRand.nextFloat(-mMousePos.x, mMousePos.x) / 20.0f;
            float shiftY = mRand.nextFloat(-mMousePos.x, mMousePos.x) / 20.0f;
            
            gl::pushMatrices();
            gl::translate(Vec2f(posX + shiftX, posY + shiftY));
            gl::draw(mCircleMesh);
            gl::popMatrices();
            
        }
    }
    
    gl::popMatrices();
}

void P_2_1_2_01App::mouseUp( MouseEvent event )
{
    mRandomSeed = mRand.nextUint();
}

void P_2_1_2_01App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

CINDER_APP_NATIVE( P_2_1_2_01App, RendererGl )