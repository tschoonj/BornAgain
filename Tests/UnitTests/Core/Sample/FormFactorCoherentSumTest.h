#include "FormFactorCoherentSum.h"
#include "FormFactorDot.h"
#include "Exceptions.h"

class FormFactorCoherentSumTest : public ::testing::Test
{
protected:
    FormFactorCoherentSumTest() {}
    virtual ~FormFactorCoherentSumTest() {}
};

TEST_F(FormFactorCoherentSumTest, RelAbundance)
{
    const double epsilon=1e-12;
    auto p_ff = new FormFactorDot();
    FormFactorCoherentSum ffw(1.0);
    FormFactorCoherentPart part(p_ff);
    ffw.addCoherentPart(part);
    EXPECT_EQ(1.0, ffw.relativeAbundance());
    ffw.scaleRelativeAbundance(2.0);
    EXPECT_NEAR(0.5, ffw.relativeAbundance(), epsilon);
    EXPECT_THROW(ffw.scaleRelativeAbundance(0.0), Exceptions::LogicErrorException);
}

TEST_F(FormFactorCoherentSumTest, FormFactor)
{
    auto p_ff = new FormFactorDot();
    FormFactorCoherentSum ffw(1.0);
    FormFactorCoherentPart part(p_ff);
    ffw.addCoherentPart(part);
    EXPECT_EQ(0.0, ffw.radialExtension());
    ffw.scaleRelativeAbundance(2.0);
    EXPECT_EQ(0.0, ffw.radialExtension());
}
