#ifndef SPHERICALDETECTORTEST_H
#define SPHERICALDETECTORTEST_H

#include "SphericalDetector.h"
#include "Exceptions.h"
#include "OutputData.h"
#include "FixedBinAxis.h"
#include "ConvolutionDetectorResolution.h"
#include "ResolutionFunction2DGaussian.h"
#include "Polygon.h"
#include "BornAgainNamespace.h"
#include "Rectangle.h"
#include <memory>

class SphericalDetectorTest : public ::testing::Test
{
 protected:
    SphericalDetectorTest();
    virtual ~SphericalDetectorTest();

    SphericalDetector *originalDetector;
    SphericalDetector copyOfOriginalDetector;
};

SphericalDetectorTest::SphericalDetectorTest()
{
    originalDetector = new SphericalDetector();
    FixedBinAxis axis0("axis0", 10, 0.0, 10.0);
    FixedBinAxis axis1("axis1", 20, 0.0, 20.0);
    originalDetector->addAxis(axis0);
    originalDetector->addAxis(axis1);
    originalDetector->setDetectorResolution(new ConvolutionDetectorResolution(
            new ResolutionFunction2DGaussian(1,1)));
}

SphericalDetectorTest::~SphericalDetectorTest()
{
    delete originalDetector;
}

//! Default detector construction

TEST_F(SphericalDetectorTest, initialState)
{
    SphericalDetector detector;

    // checking size
    EXPECT_EQ((size_t)0, detector.getDimension());
    EXPECT_EQ(IDetector2D::RADIANS, detector.getDefaultAxesUnits());

    // detector units
    std::vector<IDetector2D::EAxesUnits> validUnits =
        {IDetector2D::NBINS, IDetector2D::RADIANS, IDetector2D::DEGREES, IDetector2D::QYQZ};
    EXPECT_EQ(validUnits, detector.getValidAxesUnits());

    // masks
    EXPECT_FALSE(detector.hasMasks());
    EXPECT_EQ(0, detector.getNumberOfMaskedChannels());

    // resolution function
    EXPECT_EQ(nullptr, detector.getDetectorResolutionFunction());

    // region of interest
    EXPECT_EQ(nullptr, detector.regionOfInterest());

    // behavior
    ASSERT_THROW(detector.getAxis(0), Exceptions::OutOfBoundsException);
    OutputData<double>* p_intensity_map(nullptr);
    ASSERT_THROW(detector.applyDetectorResolution(p_intensity_map),
                 Exceptions::NullPointerException);
}

//! Construction of the detector with axes.

TEST_F(SphericalDetectorTest, constructionWithAxes)
{
    SphericalDetector detector;
    FixedBinAxis axis0("axis0", 10, 0.0, 10.0);
    FixedBinAxis axis1("axis1", 20, 0.0, 20.0);
    detector.addAxis(axis0);
    detector.addAxis(axis1);

    // checking dimension and axes
    EXPECT_EQ((size_t)2, detector.getDimension());
    EXPECT_EQ(axis0.getMin(), detector.getAxis(0).getMin() );
    EXPECT_EQ(axis0.getMax(), detector.getAxis(0).getMax() );
    EXPECT_EQ(axis0.getName(), detector.getAxis(0).getName() );
    EXPECT_EQ(axis1.getName(), detector.getAxis(1).getName() );
    EXPECT_EQ(axis1.getMin(), detector.getAxis(1).getMin() );
    EXPECT_EQ(axis1.getMax(), detector.getAxis(1).getMax() );

    // clearing detector
    detector.clear();
    EXPECT_EQ((size_t)0, detector.getDimension());
}

//! Construction of the detector via classical constructor.

TEST_F(SphericalDetectorTest, constructionWithParameters)
{
    SphericalDetector detector(10, -1.0, 1.0, 20, 0.0, 2.0);
    EXPECT_EQ(10, detector.getAxis(0).getSize() );
    EXPECT_EQ(-1.0, detector.getAxis(0).getMin() );
    EXPECT_EQ(1.0, detector.getAxis(0).getMax() );
    EXPECT_EQ(BornAgain::PHI_AXIS_NAME, detector.getAxis(0).getName());
    EXPECT_EQ(20, detector.getAxis(1).getSize() );
    EXPECT_EQ(0.0, detector.getAxis(1).getMin() );
    EXPECT_EQ(2.0, detector.getAxis(1).getMax() );
    EXPECT_EQ(BornAgain::ALPHA_AXIS_NAME, detector.getAxis(1).getName());
}

//! Init external data with detector axes

TEST_F(SphericalDetectorTest, initOutputData)
{
    SphericalDetector detector(10, -1.0, 1.0, 20, 0.0, 2.0);
    OutputData<double> data;
    detector.initOutputData(data);

    EXPECT_EQ(data.getAllocatedSize(), 200);

    EXPECT_EQ(10, data.getAxis(0)->getSize() );
    EXPECT_EQ(-1.0, data.getAxis(0)->getMin() );
    EXPECT_EQ(1.0, data.getAxis(0)->getMax() );
    EXPECT_EQ(BornAgain::PHI_AXIS_NAME, data.getAxis(0)->getName());
    EXPECT_EQ(20, data.getAxis(1)->getSize() );
    EXPECT_EQ(0.0, data.getAxis(1)->getMin() );
    EXPECT_EQ(2.0, data.getAxis(1)->getMax() );
    EXPECT_EQ(BornAgain::ALPHA_AXIS_NAME, data.getAxis(1)->getName());
}

//! Testing region of interest.

TEST_F(SphericalDetectorTest, regionOfInterest)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("axis0", 8, -3.0, 5.0));
    detector.addAxis(FixedBinAxis("axis1", 4, 0.0, 4.0));

    // creating region of interest
    double xlow(-2.0), ylow(1.0), xup(4.0), yup(3.0);
    detector.setRegionOfInterest(xlow, ylow, xup, yup);
    EXPECT_FALSE(nullptr == detector.regionOfInterest());
    EXPECT_EQ(detector.regionOfInterest()->getXlow(), xlow);
    EXPECT_EQ(detector.regionOfInterest()->getYlow(), ylow);
    EXPECT_EQ(detector.regionOfInterest()->getXup(), xup);
    EXPECT_EQ(detector.regionOfInterest()->getYup(), yup);

    // replacing region of interest with a new one
    double xlow2(-2.1), ylow2(1.1), xup2(4.1), yup2(3.1);
    detector.setRegionOfInterest(xlow2, ylow2, xup2, yup2);
    EXPECT_EQ(detector.regionOfInterest()->getXlow(), xlow2);
    EXPECT_EQ(detector.regionOfInterest()->getYlow(), ylow2);
    EXPECT_EQ(detector.regionOfInterest()->getXup(), xup2);
    EXPECT_EQ(detector.regionOfInterest()->getYup(), yup2);

    // removing region of interest
    detector.resetRegionOfInterest();
    EXPECT_TRUE(nullptr == detector.regionOfInterest());
}

//! Init external data with detector axes when region of interest is present.

TEST_F(SphericalDetectorTest, regionOfInterestAndData)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("axis0", 8, -3.0, 5.0));
    detector.addAxis(FixedBinAxis("axis1", 4, 0.0, 4.0));

    // creating region of interest which is larger than detector plane
    detector.setRegionOfInterest(-4.0, -1.0, 6.0, 7.0);

    // initializing data via the detector and making sure that data axes are exactly as in detector
    OutputData<double> data;
    detector.initOutputData(data);
    EXPECT_EQ(data.getAllocatedSize(), 32);
    EXPECT_EQ(data.getAxis(0)->getSize(), 8);
    EXPECT_EQ(data.getAxis(0)->getMin(), -3.0);
    EXPECT_EQ(data.getAxis(0)->getMax(), 5.0);
    EXPECT_EQ(data.getAxis(1)->getSize(), 4);
    EXPECT_EQ(data.getAxis(1)->getMin(), 0.0);
    EXPECT_EQ(data.getAxis(1)->getMax(), 4.0);

    // Creating region of interest inside the detector and checking that data is initialized with
    // axes corresponding to croped area.
    // Please note, that crop is done via IAxis::createClippedAxis which
    detector.setRegionOfInterest(-1.8, 0.5, 3.0, 2.5);
    detector.initOutputData(data);
    EXPECT_EQ(data.getAxis(0)->getSize(), 6);
    EXPECT_EQ(data.getAxis(0)->getMin(), -2.0); // result of crop at x = -1.8
    EXPECT_EQ(data.getAxis(0)->getMax(), 4.0); // result of crop at x = 3.0
    EXPECT_EQ(data.getAxis(1)->getSize(), 3);
    EXPECT_EQ(data.getAxis(1)->getMin(), 0.0);
    EXPECT_EQ(data.getAxis(1)->getMax(), 3.0);
}


TEST_F(SphericalDetectorTest, DetectorCopying)
{
    copyOfOriginalDetector = *originalDetector;
    delete originalDetector;
    originalDetector = 0;
    ASSERT_TRUE( copyOfOriginalDetector.getDimension() == 2 );
    EXPECT_EQ( (double)0, copyOfOriginalDetector.getAxis(0).getMin() );
    EXPECT_EQ( (double)10, copyOfOriginalDetector.getAxis(0).getMax() );
    EXPECT_EQ( (size_t)10, copyOfOriginalDetector.getAxis(0).getSize() );
    EXPECT_EQ( (double)0, copyOfOriginalDetector.getAxis(1).getMin() );
    EXPECT_EQ( (double)20, copyOfOriginalDetector.getAxis(1).getMax() );
    EXPECT_EQ( (size_t)20, copyOfOriginalDetector.getAxis(1).getSize() );
    EXPECT_TRUE(std::string("ConvolutionDetectorResolution")
        == copyOfOriginalDetector.getDetectorResolutionFunction()->getName());
}

TEST_F(SphericalDetectorTest, MaskOfDetector)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("x-axis", 12, -4.0, 8.0));
    detector.addAxis(FixedBinAxis("y-axis", 6, -2.0, 4.0));

    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};

    Geometry::Polygon polygon(x, y);
    detector.addMask(polygon, true);

    const OutputData<bool> *mask = detector.getDetectorMask()->getMaskData();
    for(size_t index=0; index<mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(detector.isMasked(index));
        } else {
            EXPECT_FALSE(detector.isMasked(index));
        }
    }

    SphericalDetector detector2 = detector;
    mask = detector2.getDetectorMask()->getMaskData();
    for(size_t index=0; index<mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(detector2.isMasked(index));
        } else {
            EXPECT_FALSE(detector2.isMasked(index));
        }
    }

    mask = detector.getDetectorMask()->getMaskData();
    for(size_t index=0; index<mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(detector.isMasked(index));
        } else {
            EXPECT_FALSE(detector.isMasked(index));
        }
    }
}

#endif // SPHERICALDETECTORTEST_H
