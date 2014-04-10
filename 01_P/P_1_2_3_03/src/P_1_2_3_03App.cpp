#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class P_1_2_3_03App : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseUp( MouseEvent event );
    void keyUp( KeyEvent event );
	void update();
	void draw();
    
private:
    Rand mRand;
    const int sColorsCount = 20;
    const float sAlpha = 0.27f;
    vector<ColorAf> mColors;
    Vec2i mMousePos;
    unsigned long mSeed;
    
    void generateColors();
};

void P_1_2_3_03App::setup()
{
    setWindowSize(800, 800);
    mSeed = 0;
    gl::enableAlphaBlending();
}

void P_1_2_3_03App::generateColors()
{
    mColors.clear();
    for (int i = 0; i < sColorsCount; i++)
    {
        if (i % 2 == 0)
        {
            mColors.push_back(ColorAf(ColorModel::CM_HSV,
                                     mRand.nextFloat(),
                                     1.0,
                                     mRand.nextFloat(), sAlpha));
        }
        else
        {
            mColors.push_back(ColorAf(ColorModel::CM_HSV,
                                     195.0f / 360.0f,
                                     mRand.nextFloat(),
                                     1.0, sAlpha));
        }
        
    }
    
}

void P_1_2_3_03App::update()
{
    mRand.seed(mSeed);
    generateColors();
}

void P_1_2_3_03App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    int counter = 0;
    int rowCount = mRand.nextInt(5, 30);
    float rowHeight = float(getWindowHeight()) / float(rowCount);
    
    for (int i = rowCount; i >= 0; i--)
    {
        int partCount = i + 1;
        vector<float> parts;
        
        for (int ii = 0; ii < partCount; ii++)
        {
            if (mRand.nextFloat() < 0.075)
            {
                int fragments = mRand.nextInt(2, 20);
                partCount += fragments;
                for (int iii = 0; iii < fragments; iii++)
                {
                    parts.push_back(mRand.nextFloat(2.0));
                }
            }
            else
            {
                parts.push_back(mRand.nextFloat(2, 20));
            }
        }
        
        float sumPartsTotal = 0.0f;
        for (int ii = 0; ii < partCount; ii++) sumPartsTotal += parts[ii];
        
        float sumPartsNow = 0.0f;
        for (int ii = 0; ii < parts.size(); ii++) {
            int index = counter % sColorsCount;
            
            
            
            float rectLeft = lmap(sumPartsNow, 0.0f, sumPartsTotal, 0.0f, float(getWindowWidth()));
            float rectWidth = lmap(parts[ii], 0.0f, sumPartsTotal, 0.0f, float(getWindowWidth()));
            float rectTop = rowHeight * i;
            float rectBottom = rowHeight * (i + 1.5f);
            
            gl::begin(GL_TRIANGLE_STRIP);
            gl::color(0.0f, 0.0f, 0.0f);
            gl::vertex(rectLeft, rectTop);
            gl::vertex(rectLeft + rectWidth, rectTop);
            gl::color(mColors[index]);
            gl::vertex(rectLeft, rectBottom);
            gl::vertex(rectLeft + rectWidth, rectBottom);
            gl::end();
            
            
            sumPartsNow += parts[ii];
            counter++;
        }
    }
    
}

void P_1_2_3_03App::mouseDown( MouseEvent event )
{

}

void P_1_2_3_03App::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void P_1_2_3_03App::mouseUp( MouseEvent event )
{
    mSeed = mRand.nextUint(100000);
}

void P_1_2_3_03App::keyUp(KeyEvent event)
{
    
}

CINDER_APP_NATIVE( P_1_2_3_03App, RendererGl )
