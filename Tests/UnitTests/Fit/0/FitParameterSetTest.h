#include "IFitParameter.h"
#include "FitParameterSet.h"
#include "gtest/gtest.h"

class FitParameterSetTest : public ::testing::Test
{
 protected:
    FitParameterSetTest(){}
    virtual ~FitParameterSetTest(){}
};

TEST_F(FitParameterSetTest, addFitParameter)
{
    FitParameterSet parameters;

    IFitParameter *par = new IFitParameter("pattern1", 1.0);
    parameters.addFitParameter(par);
    EXPECT_EQ(parameters.size(), 1u);
    EXPECT_EQ(par->name(), "pattern1");

    // attempt to add same fit parameter twice
    EXPECT_THROW(parameters.addFitParameter(par), std::runtime_error);

    IFitParameter *par2 = new IFitParameter("pattern2", 1.0);
    parameters.addFitParameter(par2);
    EXPECT_EQ(parameters.size(), 2u);
    EXPECT_EQ(par2->name(), "pattern2");

    parameters.clear();
    EXPECT_EQ(parameters.size(), 0u);
}

TEST_F(FitParameterSetTest, getFitParameter)
{
    FitParameterSet parameters;

    IFitParameter *par1 = new IFitParameter("pattern1", 1.0);
    parameters.addFitParameter(par1);
    IFitParameter *par2 = new IFitParameter("pattern2", 1.0);
    parameters.addFitParameter(par2);

    EXPECT_EQ(parameters.fitParameter("pattern1"), par1);
    EXPECT_EQ(parameters.fitParameter("pattern2"), par2);
    EXPECT_EQ(parameters["pattern1"], par1);
    EXPECT_EQ(parameters["pattern2"], par2);
    EXPECT_EQ(parameters[0], par1);
    EXPECT_EQ(parameters[1], par2);

    EXPECT_THROW(parameters.fitParameter("par3"), std::runtime_error);
    EXPECT_THROW(parameters["par3"], std::runtime_error);
    EXPECT_THROW(parameters[2], std::runtime_error);
}

TEST_F(FitParameterSetTest, parameterValues)
{
    FitParameterSet parameters;
    parameters.addFitParameter(new IFitParameter("pattern1", 1.0));
    parameters.addFitParameter(new IFitParameter("pattern2", 2.0));
    parameters.addFitParameter(new IFitParameter("pattern3", 3.0));
    std::vector<double> values{1.0, 2.0, 3.0};
    EXPECT_EQ(parameters.values(), values);

    std::vector<double> new_values{4.0, 5.0, 6.0};
    parameters.setValues(new_values);
    EXPECT_EQ(parameters.values(), new_values);

    // are values different?
    EXPECT_FALSE(parameters.valuesDifferFrom(new_values));
    new_values = {4.0, 5.1, 6.0};
    EXPECT_TRUE(parameters.valuesDifferFrom(new_values));

    // attempt to set vector of wrong size
    new_values = {4.0, 5.0, 6.0, 7.0};
    EXPECT_THROW(parameters.setValues(new_values), std::runtime_error);
}

TEST_F(FitParameterSetTest, parameterErrors)
{
    FitParameterSet parameters;
    IFitParameter *par1 = new IFitParameter("pattern1", 1.0, AttLimits::limitless(), 0.01);
    IFitParameter *par2 = new IFitParameter("pattern2", 1.0, AttLimits::limitless(), 0.01);

    parameters.addFitParameter(par1);
    parameters.addFitParameter(par2);
    par1->setError(1.0);
    par2->setError(2.0);

    std::vector<double> errors{1.0, 2.0};
    EXPECT_EQ(parameters.errors(), errors);

    parameters.setErrors(std::vector<double>() = {4.0, 5.0});
    EXPECT_EQ(par1->error(), 4.0);
    EXPECT_EQ(par2->error(), 5.0);
}

TEST_F(FitParameterSetTest, fixRelease)
{
    FitParameterSet parameters;
    IFitParameter *par1 = new IFitParameter("pattern1", 1.0, AttLimits::limitless(), 0.01);
    IFitParameter *par2 = new IFitParameter("pattern2", 1.0, AttLimits::limitless(), 0.01);
    IFitParameter *par3 = new IFitParameter("pattern3", 1.0, AttLimits::limitless(), 0.01);

    parameters.addFitParameter(par1);
    parameters.addFitParameter(par2);
    parameters.addFitParameter(par3);

    EXPECT_EQ(parameters.freeFitParameterCount(), 3u);

    par1->limits().setFixed(true);
    EXPECT_EQ(parameters.freeFitParameterCount(), 2u);
    par2->limits().setFixed(true);
    EXPECT_EQ(parameters.freeFitParameterCount(), 1u);

    parameters.fixAll();
    EXPECT_EQ(parameters.freeFitParameterCount(), 0u);

    parameters.releaseAll();
    EXPECT_EQ(parameters.freeFitParameterCount(), 3u);

    std::vector<std::string> names_to_fix={"pattern1", "pattern3"};
    parameters.setFixed(names_to_fix, true);
    EXPECT_EQ(parameters.freeFitParameterCount(), 1u);
    EXPECT_TRUE(par1->limits().isFixed());
    EXPECT_FALSE(par2->limits().isFixed());
    EXPECT_TRUE(par3->limits().isFixed());
}
