#include "FTDistributions1D.h"
#include "FTDistributions2D.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include <memory>

class FTDistributionsTest : public ::testing::Test
{
protected:
    FTDistributionsTest() {}
};

// test 1D

TEST_F(FTDistributionsTest, FTDistribution1DCauchyConstructor)
{
    std::unique_ptr<IFTDistribution1D> P_1d_cauchy { new FTDistribution1DCauchy(1.0) };
    EXPECT_EQ(1.0, P_1d_cauchy->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DCauchyType, P_1d_cauchy->getName());
    EXPECT_NEAR(0.961538, P_1d_cauchy->evaluate(0.2),0.000001);

    P_1d_cauchy->setOmega(3.0);
    EXPECT_EQ(3.0, P_1d_cauchy->omega());

    P_1d_cauchy->setParameterValue(BornAgain::Omega, -7.0);
    EXPECT_EQ(-7.0, P_1d_cauchy->omega());
}

TEST_F(FTDistributionsTest, FTDistribution1DCauchyClone)
{
    std::unique_ptr<IFTDistribution1D> P_1d_cauchy { new FTDistribution1DCauchy(5.0) };
    std::unique_ptr<IFTDistribution1D> P_clone { P_1d_cauchy->clone() };

    EXPECT_EQ(5.0, P_clone->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DCauchyType, P_clone->getName());
    EXPECT_NEAR(0.5, P_clone->evaluate(0.2),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution1DGaussConstructor)
{
    std::unique_ptr<IFTDistribution1D> P_1d_gauss { new FTDistribution1DGauss(1.0) };
    EXPECT_EQ(1.0, P_1d_gauss->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DGaussType, P_1d_gauss->getName());
    EXPECT_NEAR(0.9801987, P_1d_gauss->evaluate(0.2),0.000001);

    P_1d_gauss->setOmega(3.0);
    EXPECT_EQ(3.0, P_1d_gauss->omega());
}

TEST_F(FTDistributionsTest, FTDistribution1DGaussClone)
{
    std::unique_ptr<IFTDistribution1D> P_1d_gauss { new FTDistribution1DGauss(5.0) };
    std::unique_ptr<IFTDistribution1D> P_clone { P_1d_gauss->clone() };

    EXPECT_EQ(5.0, P_clone->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DGaussType, P_clone->getName());
    EXPECT_NEAR(0.6065307, P_clone->evaluate(0.2),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution1DGateConstructor)
{
    std::unique_ptr<IFTDistribution1D> P_1d_gate { new FTDistribution1DGate(1.0) };
    EXPECT_EQ(1.0, P_1d_gate->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DGateType, P_1d_gate->getName());
    EXPECT_NEAR(0.993347, P_1d_gate->evaluate(0.2),0.000001);

    P_1d_gate->setOmega(3.0);
    EXPECT_EQ(3.0, P_1d_gate->omega());
}

TEST_F(FTDistributionsTest, FTDistribution1DGateClone)
{
    std::unique_ptr<IFTDistribution1D> P_1d_gate { new FTDistribution1DGate(5.0) };
    std::unique_ptr<IFTDistribution1D> P_clone { P_1d_gate->clone() };

    EXPECT_EQ(5.0, P_clone->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DGateType, P_clone->getName());
    EXPECT_NEAR(0.841471, P_clone->evaluate(0.2),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution1DTriangleConstructor)
{
    std::unique_ptr<IFTDistribution1D> P_1d_triangle { new FTDistribution1DTriangle(1.0) };
    EXPECT_EQ(1.0, P_1d_triangle->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DTriangleType, P_1d_triangle->getName());
    EXPECT_NEAR(0.996671, P_1d_triangle->evaluate(0.2),0.000001);

    P_1d_triangle->setOmega(3.0);
    EXPECT_EQ(3.0, P_1d_triangle->omega());
}

TEST_F(FTDistributionsTest, FTDistribution1DTriangleClone)
{
    std::unique_ptr<IFTDistribution1D> P_1d_triangle { new FTDistribution1DTriangle(5.0) };
    std::unique_ptr<IFTDistribution1D> P_clone { P_1d_triangle->clone() };

    EXPECT_EQ(5.0, P_clone->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DTriangleType, P_clone->getName());
    EXPECT_NEAR(0.919395, P_clone->evaluate(0.2),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution1DCosineConstructor)
{
    std::unique_ptr<IFTDistribution1D> P_1d_cosine { new FTDistribution1DCosine(1.0) };
    EXPECT_EQ(1.0, P_1d_cosine->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DCosineType, P_1d_cosine->getName());
    EXPECT_NEAR(0.997389, P_1d_cosine->evaluate(0.2),0.000001);

    P_1d_cosine->setOmega(3.0);
    EXPECT_EQ(3.0, P_1d_cosine->omega());
}

TEST_F(FTDistributionsTest, FTDistribution1DCosineClone)
{
    std::unique_ptr<IFTDistribution1D> P_1d_cosine { new FTDistribution1DCosine(5.0) };
    std::unique_ptr<IFTDistribution1D> P_clone { P_1d_cosine->clone() };

    EXPECT_EQ(5.0, P_clone->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DCosineType, P_clone->getName());
    EXPECT_NEAR(0.936342, P_clone->evaluate(0.2),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution1DVoigtConstructor)
{
    std::unique_ptr<IFTDistribution1D> P_1d_voigt { new FTDistribution1DVoigt(1.0,1.7) };
    EXPECT_EQ(1.0, P_1d_voigt->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DVoigtType, P_1d_voigt->getName());
    EXPECT_NEAR(0.993261, P_1d_voigt->evaluate(0.2),0.000001);

    P_1d_voigt->setOmega(3.0);
    EXPECT_EQ(3.0, P_1d_voigt->omega());
}

TEST_F(FTDistributionsTest, FTDistribution1DVoigtClone)
{
    std::unique_ptr<IFTDistribution1D> P_1d_voigt { new FTDistribution1DVoigt(5.0,-5.6) };
    std::unique_ptr<IFTDistribution1D> P_clone { P_1d_voigt->clone() };

    EXPECT_EQ(5.0, P_clone->omega());
    EXPECT_EQ(BornAgain::FTDistribution1DVoigtType, P_clone->getName());
    EXPECT_NEAR(-0.096572, P_clone->evaluate(0.2),0.000001);
}

// test 2D

TEST_F(FTDistributionsTest, FTDistribution2DCauchyConstructor)
{
    std::unique_ptr<IFTDistribution2D> P_2d_cauchy { new FTDistribution2DCauchy(1.0,2.0) };
    EXPECT_EQ(1.0, P_2d_cauchy->omegaX());
    EXPECT_EQ(2.0, P_2d_cauchy->omegaY());
    EXPECT_EQ(2.0, P_2d_cauchy->parameter(BornAgain::OmegaY)->value());
    EXPECT_EQ(0, P_2d_cauchy->parameter(BornAgain::Gamma)->value());
    EXPECT_EQ(M_PI/2.0, P_2d_cauchy->delta());
    EXPECT_EQ(0.0, P_2d_cauchy->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DCauchyType, P_2d_cauchy->getName());
    EXPECT_NEAR(0.343206, P_2d_cauchy->evaluate(0.2, 0.5),0.000001);

    P_2d_cauchy->setGamma(3.0);
    EXPECT_EQ(3.0, P_2d_cauchy->gamma());
    EXPECT_EQ(3.0, P_2d_cauchy->parameter(BornAgain::Gamma)->value());

    P_2d_cauchy->setParameterValue(BornAgain::OmegaX, 7.0);
    P_2d_cauchy->setParameterValue(BornAgain::OmegaY, 5.3);
    EXPECT_EQ(7.0, P_2d_cauchy->omegaX());
    EXPECT_EQ(5.3, P_2d_cauchy->omegaY());
}

TEST_F(FTDistributionsTest, FTDistribution2DCauchyClone)
{
    std::unique_ptr<IFTDistribution2D> P_2d_cauchy { new FTDistribution2DCauchy(5.0,2.3) };
    std::unique_ptr<IFTDistribution2D> P_clone { P_2d_cauchy->clone() };

    EXPECT_EQ(5.0, P_clone->omegaX());
    EXPECT_EQ(2.3, P_clone->omegaY());
    EXPECT_EQ(M_PI/2.0, P_clone->delta());
    EXPECT_EQ(0.0, P_clone->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DCauchyType, P_clone->getName());
    EXPECT_NEAR(0.165121078, P_clone->evaluate(0.2, 0.5),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution2DGaussConstructor)
{
    std::unique_ptr<IFTDistribution2D> P_2d_gauss { new FTDistribution2DGauss(1.0,2.0) };
    EXPECT_EQ(1.0, P_2d_gauss->omegaX());
    EXPECT_EQ(2.0, P_2d_gauss->omegaY());
    EXPECT_EQ(M_PI/2.0, P_2d_gauss->delta());
    EXPECT_EQ(0.0, P_2d_gauss->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGaussType, P_2d_gauss->getName());
    EXPECT_NEAR(0.5945205, P_2d_gauss->evaluate(0.2, 0.5),0.000001);

    P_2d_gauss->setGamma(3.0);
    EXPECT_EQ(3.0, P_2d_gauss->gamma());
}

TEST_F(FTDistributionsTest, FTDistribution2DGaussClone)
{
    std::unique_ptr<IFTDistribution2D> P_2d_gauss { new FTDistribution2DGauss(5.0,2.3) };
    std::unique_ptr<IFTDistribution2D> P_clone { P_2d_gauss->clone() };

    EXPECT_EQ(5.0, P_clone->omegaX());
    EXPECT_EQ(2.3, P_clone->omegaY());
    EXPECT_EQ(M_PI/2.0, P_clone->delta());
    EXPECT_EQ(0.0, P_clone->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGaussType, P_clone->getName());
    EXPECT_NEAR(0.3130945, P_clone->evaluate(0.2, 0.5),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution2DGateConstructor)
{
    std::unique_ptr<IFTDistribution2D> P_2d_gate { new FTDistribution2DGate(1.0,2.0) };
    EXPECT_EQ(1.0, P_2d_gate->omegaX());
    EXPECT_EQ(2.0, P_2d_gate->omegaY());
    EXPECT_EQ(M_PI/2.0, P_2d_gate->delta());
    EXPECT_EQ(0.0, P_2d_gate->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGateType, P_2d_gate->getName());
    EXPECT_NEAR(0.875513, P_2d_gate->evaluate(0.2, 0.5),0.000001);

    P_2d_gate->setGamma(3.0);
    EXPECT_EQ(3.0, P_2d_gate->gamma());
}

TEST_F(FTDistributionsTest, FTDistribution2DGateClone)
{
    std::unique_ptr<IFTDistribution2D> P_2d_gate { new FTDistribution2DGate(5.0,2.3) };
    std::unique_ptr<IFTDistribution2D> P_clone { P_2d_gate->clone() };

    EXPECT_EQ(5.0, P_clone->omegaX());
    EXPECT_EQ(2.3, P_clone->omegaY());
    EXPECT_EQ(M_PI/2.0, P_clone->delta());
    EXPECT_EQ(0.0, P_clone->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DGateType, P_clone->getName());
    EXPECT_NEAR(0.736461, P_clone->evaluate(0.2, 0.5),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution2DConeConstructor)
{
    std::unique_ptr<IFTDistribution2D> P_2d_cone { new FTDistribution2DCone(1.0,2.0) };
    EXPECT_EQ(1.0, P_2d_cone->omegaX());
    EXPECT_EQ(2.0, P_2d_cone->omegaY());
    EXPECT_EQ(M_PI/2.0, P_2d_cone->delta());
    EXPECT_EQ(0.0, P_2d_cone->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DConeType, P_2d_cone->getName());
    EXPECT_NEAR(0.924374, P_2d_cone->evaluate(0.2, 0.5),0.000001);

    P_2d_cone->setGamma(3.0);
    EXPECT_EQ(3.0, P_2d_cone->gamma());
}

TEST_F(FTDistributionsTest, FTDistribution2DConeClone)
{
    std::unique_ptr<IFTDistribution2D> P_2d_cone { new FTDistribution2DCone(5.0,2.3) };
    std::unique_ptr<IFTDistribution2D> P_clone { P_2d_cone->clone() };

    EXPECT_EQ(5.0, P_clone->omegaX());
    EXPECT_EQ(2.3, P_clone->omegaY());
    EXPECT_EQ(M_PI/2.0, P_clone->delta());
    EXPECT_EQ(0.0, P_clone->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DConeType, P_clone->getName());
    EXPECT_NEAR(0.837410, P_clone->evaluate(0.2, 0.5),0.000001);
}

TEST_F(FTDistributionsTest, FTDistribution2DVoigtConstructor)
{
    std::unique_ptr<IFTDistribution2D> P_2d_voigt { new FTDistribution2DVoigt(1.0,2.0,3.5) };
    EXPECT_EQ(1.0, P_2d_voigt->omegaX());
    EXPECT_EQ(2.0, P_2d_voigt->omegaY());
    EXPECT_EQ(M_PI/2.0, P_2d_voigt->delta());
    EXPECT_EQ(0.0, P_2d_voigt->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DVoigtType, P_2d_voigt->getName());
    EXPECT_NEAR(1.2228072, P_2d_voigt->evaluate(0.2, 0.5),0.000001);

    P_2d_voigt->setGamma(3.0);
    EXPECT_EQ(3.0, P_2d_voigt->gamma());
}

TEST_F(FTDistributionsTest, FTDistribution2DVoigtClone)
{
    std::unique_ptr<IFTDistribution2D> P_2d_voigt { new FTDistribution2DVoigt(5.0,2.3, -5.6) };
    std::unique_ptr<IFTDistribution2D> P_clone { P_2d_voigt->clone() };

    EXPECT_EQ(5.0, P_clone->omegaX());
    EXPECT_EQ(2.3, P_clone->omegaY());
    EXPECT_EQ(M_PI/2.0, P_clone->delta());
    EXPECT_EQ(0.0, P_clone->gamma());
    EXPECT_EQ(BornAgain::FTDistribution2DVoigtType, P_clone->getName());
    EXPECT_NEAR(-0.6635305, P_clone->evaluate(0.2, 0.5),0.000001);
}
