#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/svg/Svg.h"
#include "cinder/svg/SvgGl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
 * shapes in a grid, that are always facing the mouse
 *
 * MOUSE
 * position x/y        : position to face
 *
 * KEYS
 * 1-7                 : choose shapes
 * arrow up/down       : scale of shapes
 * arrow left/right    : additional rotation of shapes
 * c                   : toggle. color mode
 * d                   : toggle. size depending on distance
 * g                   : toggle. grid resolution
 */

// (sergey) I've failed to get SVG opacity to work

class P_2_1_1_04App : public AppNative {
public:
	void setup();
	void mouseUp( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
private:
    
    svg::DocRef mCurrentShape;
    
    int mTileCount = 10;
    float mTileWidth, mTileHeight;
    float mShapeSize = 50;
    float mNewShapeSize = mShapeSize;
    float mShapeAngle = 0;
    float mMaxDist;
    
    Colorf mShapeColor = Colorf(0, 130.0f / 255.0f, 164.0f / 255.0f);
    int mFillMode = 0;
    int mSizeMode = 0;

    Vec2i mMousePos;
    static float calculateAngleDeg(float cellWidth, float cellHeight);
};

void P_2_1_1_04App::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
    
    mTileWidth = float(getWindowWidth()) / mTileCount;
    mTileHeight = float(getWindowHeight()) / mTileCount;
    mMaxDist = sqrt(getWindowWidth() * getWindowWidth() + getWindowHeight() * getWindowHeight());
    
    mCurrentShape = svg::Doc::create(loadAsset("module_1.svg"));
}

void P_2_1_1_04App::update()
{
}

void P_2_1_1_04App::draw()
{
	gl::clear( ColorA::white() );
    
    for (int gridY = 0; gridY < mTileCount; gridY++)
    {
        for (int gridX = 0; gridX < mTileCount; gridX++)
        {
            float posX = mTileWidth * gridX + mTileWidth / 2.0f;
            float posY = mTileHeight * gridY + mTileHeight / 2.0f;
            
            float angle = atan2(float(mMousePos.y - posY), float(mMousePos.x - posX))
                            + mShapeAngle / 360.0f * 2.0f * M_PI;
            
            float distance = Vec2f(mMousePos.x, mMousePos.y).distance(Vec2f(posX, posY));
            if (mSizeMode == 0) mNewShapeSize = mShapeSize;
            if (mSizeMode == 1) mNewShapeSize = mShapeSize * 1.5f - lmap(distance, 0.0f, 500.0f, 5.0f, mShapeSize);
            if (mSizeMode == 2) mNewShapeSize = lmap(distance, 0.0f, 500.0f, 5.0f, mShapeSize);
            
            svg::Style style = mCurrentShape->getStyle();
            if (mFillMode == 0)
            {
                style.unspecifyFill();
                style.setOpacity(0.1f);
                style.setFillOpacity(0.1f);
            }
            if (mFillMode == 1) {
                style.setFill(svg::Paint(mShapeColor));
                style.unspecifyOpacity();
            }
            if (mFillMode == 2)
            {
                float alpha = lmap(distance, 0.0f, float(mMaxDist), 1.0f, 0.0f);
                style.setFill(svg::Paint(Colorf(1.0f, 0.0f, alpha)));
                style.setOpacity(alpha);
                style.setFillOpacity(alpha);
            }
            if (mFillMode == 3)
            {
                float alpha = lmap(distance, 0.0f, float(mMaxDist), 0.0f, 1.0f);
                style.setFill(svg::Paint(mShapeColor));
                style.setOpacity(alpha);
                style.setFillOpacity(alpha);
            }
            mCurrentShape->setStyle(style);
            
            float scale = mNewShapeSize / float(mCurrentShape->getWidth());
            MatrixAffine2f scaleMatrix;
            scaleMatrix.scale(scale);
            mCurrentShape->setTransform(scaleMatrix);
            
            gl::pushMatrices();
            gl::translate(posX, posY);
            gl::rotate(angle * 360.0f / (2.0f * M_PI));
            gl::translate(-mTileWidth / 2.0f, -mTileHeight / 2.0f);
            gl::draw(*mCurrentShape);
            gl::popMatrices();
        }
    }
    
}

float P_2_1_1_04App::calculateAngleDeg(float cellWidth, float cellHeight)
{
    float cosAlpha = cellWidth / sqrt(4*cellHeight*cellHeight + cellWidth * cellWidth);
    return acos(cosAlpha) / (2.0f * M_PI) * 360.0f;
}

void P_2_1_1_04App::mouseUp( MouseEvent event )
{
    
}

void P_2_1_1_04App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_2_1_1_04App::keyUp( KeyEvent event )
{
    char ch = event.getChar();
    if (ch == 'c' || ch == 'C') mFillMode = (mFillMode + 1) % 4;
    if (ch == 'd' || ch == 'D') mSizeMode = (mSizeMode + 1) % 3;
    
    if (ch == 'g' || ch == 'G')
    {
        mTileCount += 5;
        if (mTileCount > 20) mTileCount = 10;
        mTileWidth = getWindowWidth() / float(mTileCount);
        mTileHeight = getWindowHeight() / float(mTileCount);
    }
    
    if (ch == '1') mCurrentShape = svg::Doc::create(loadAsset("module_1.svg"));
    if (ch == '2') mCurrentShape = svg::Doc::create(loadAsset("module_2.svg"));
    if (ch == '3') mCurrentShape = svg::Doc::create(loadAsset("module_3.svg"));
    if (ch == '4') mCurrentShape = svg::Doc::create(loadAsset("module_4.svg"));
    if (ch == '5') mCurrentShape = svg::Doc::create(loadAsset("module_5.svg"));
    if (ch == '6') mCurrentShape = svg::Doc::create(loadAsset("module_6.svg"));
    if (ch == '7') mCurrentShape = svg::Doc::create(loadAsset("module_7.svg"));
    
    if (event.getCode() == KeyEvent::KEY_UP) mShapeSize += 5;
    if (event.getCode() == KeyEvent::KEY_DOWN) mShapeSize = max(mShapeSize - 5.0f, 5.0f);
    if (event.getCode() == KeyEvent::KEY_LEFT) mShapeAngle -= 5;
    if (event.getCode() == KeyEvent::KEY_RIGHT) mShapeAngle += 5;
}

CINDER_APP_NATIVE( P_2_1_1_04App, RendererGl )
