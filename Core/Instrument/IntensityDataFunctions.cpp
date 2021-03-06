// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IntensityDataFunctions.cpp
//! @brief     Implement class IntensityDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BornAgainNamespace.h"
#include "ConvolutionDetectorResolution.h"
#include "IHistogram.h"
#include "IntensityDataFunctions.h"
#include "Numeric.h"

//! Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]).
double IntensityDataFunctions::getRelativeDifference(
        const OutputData<double>& dat, const OutputData<double>& ref)
{
    if(!dat.hasSameDimensions(ref))
        throw Exceptions::RuntimeErrorException(
            "IntensityDataFunctions::getRelativeDifference() -> "
            "Error. Different dimensions of data and reference.");

    double diff = 0.0;
    for(size_t i=0; i<dat.getAllocatedSize(); ++i)
        diff += Numeric::get_relative_difference(dat[i], ref[i]);
    diff /= dat.getAllocatedSize();

    if (std::isnan(diff))
        throw Exceptions::RuntimeErrorException("diff=NaN!");
    return diff;
}

double IntensityDataFunctions::getRelativeDifference(
    const IHistogram& dat, const IHistogram& ref)
{
    return getRelativeDifference(
        *std::unique_ptr<OutputData<double>>(dat.getData().meanValues()),
        *std::unique_ptr<OutputData<double>>(ref.getData().meanValues()) );
}

OutputData<double>* IntensityDataFunctions::createRelativeDifferenceData(
    const OutputData<double>& data, const OutputData<double>& reference)
{
    if(!data.hasSameDimensions(reference))
        throw Exceptions::RuntimeErrorException(
            "IntensityDataFunctions::createRelativeDifferenceData() -> "
            "Error. Different dimensions of data and reference.");
    OutputData<double>* result = reference.clone();
    for(size_t i=0; i<result->getAllocatedSize(); ++i)
        (*result)[i] = Numeric::get_relative_difference(data[i], reference[i]);
    return result;
}

std::unique_ptr<OutputData<double>>
IntensityDataFunctions::createRearrangedDataSet(const OutputData<double>& data, int n)
{
    if (data.getRank() != 2)
        throw Exceptions::LogicErrorException("IntensityDataFunctions::rotateDataByN90Deg()"
            " -> Error! Works only on two-dimensional data");
    n = (4 + n % 4) % 4;
    if (n == 0)
        return std::unique_ptr<OutputData<double>>(data.clone());
    std::unique_ptr<OutputData<double>> output(new OutputData<double>());

    // swapping axes if necessary
    const IAxis& x_axis = data.getAxis(0);
    const IAxis& y_axis = data.getAxis(1);
    output->addAxis( n == 2 ? x_axis : y_axis);
    output->addAxis( n == 2 ? y_axis : x_axis);

    // creating index mapping
    std::function<void(std::vector<int>&)> index_mapping;
    if (n == 2) {
        const int end_bin_x = static_cast<int>(x_axis.size()) - 1;
        const int end_bin_y = static_cast<int>(y_axis.size()) - 1;
        index_mapping = [end_bin_x, end_bin_y](std::vector<int>& inds) {
            inds[0] = end_bin_x - inds[0];
            inds[1] = end_bin_y - inds[1];
        };
    } else {
        const size_t rev_axis_i = n % 3;
        const size_t end_bin = data.getAxis(rev_axis_i).size() - 1;
        index_mapping = [rev_axis_i, end_bin](std::vector<int>& inds) {
            const int tmp_index = inds[rev_axis_i];
            inds[rev_axis_i] = inds[rev_axis_i ^ 1];
            inds[rev_axis_i ^ 1] = static_cast<int>(end_bin) - tmp_index;
        };
    }

    for (size_t index = 0, size = data.getAllocatedSize(); index < size; ++index) {
        std::vector<int> axis_inds = data.getAxesBinIndices(index);
        index_mapping(axis_inds);
        size_t output_index = output->toGlobalIndex(
            {static_cast<unsigned>(axis_inds[0]), static_cast<unsigned>(axis_inds[1])});
        (*output)[output_index] = data[index];
    }
    return output;
}

OutputData<double>* IntensityDataFunctions::createClippedDataSet(
        const OutputData<double>& origin, double x1, double y1, double x2, double y2)
{
    if (origin.getRank() != 2)
        throw Exceptions::LogicErrorException(
            "IntensityDataFunctions::createClippedData()"
            " -> Error! Works only on two-dimensional data");

    OutputData<double>* result = new OutputData<double>;
    for(size_t i_axis=0; i_axis<origin.getRank(); i_axis++) {
        const IAxis& axis = origin.getAxis(i_axis);
        IAxis* new_axis;
        if(i_axis == 0)
            new_axis = axis.createClippedAxis(x1, x2);
        else
            new_axis = axis.createClippedAxis(y1, y2);
        result->addAxis(*new_axis);
        delete new_axis;
    }
    result->setAllTo(0.0);

    OutputData<double>::const_iterator it_origin = origin.begin();
    OutputData<double>::iterator it_result = result->begin();
    while (it_origin != origin.end()) {
        double x = origin.getAxisValue(it_origin.getIndex(), 0);
        double y = origin.getAxisValue(it_origin.getIndex(), 1);
        if(result->getAxis(0).contains(x) && result->getAxis(1).contains(y)) {
            *it_result = *it_origin;
            ++it_result;
        }
        ++it_origin;
    }

    return result;
}

OutputData<double>* IntensityDataFunctions::applyDetectorResolution(
    const OutputData<double>& origin, const IResolutionFunction2D& resolution_function)
{
    if (origin.getRank() != 2)
        throw Exceptions::LogicErrorException(
            "IntensityDataFunctions::applyDetectorResolution()"
            " -> Error! Works only on two-dimensional data");
    OutputData<double>* result = origin.clone();
    const std::unique_ptr<ConvolutionDetectorResolution> P_resolution(
        new ConvolutionDetectorResolution(resolution_function));
    P_resolution->applyDetectorResolution(result);
    return result;
}

// For axis FixedBinAxis("axis", 8, -5.0, 3.0) the coordinate x=-4.5 (center of bin #0) will
// be converted into 0.5 (which is a bin center expressed in bin fraction coordinates).
// The coordinate -5.0 (outside of axis definition) will be converted to -0.5
// (center of non-existing bin #-1).
// Used for Mask convertion.

double IntensityDataFunctions::coordinateToBinf(double coordinate, const IAxis& axis)
{
    size_t index = axis.findClosestIndex(coordinate);
    Bin1D bin = axis.getBin(index);
    double f = (coordinate - bin.m_lower)/bin.getBinSize();
    return static_cast<double>(index) + f;
}

double IntensityDataFunctions::coordinateFromBinf(double value, const IAxis& axis)
{
    int index = static_cast<int>(value);

    double result(0);
    if(index < 0) {
        Bin1D bin = axis.getBin(0);
        result = bin.m_lower + value*bin.getBinSize();
    } else if(index >= static_cast<int>(axis.size())) {
        Bin1D bin = axis.getBin(axis.size()-1);
        result = bin.m_upper + (value-axis.size())*bin.getBinSize();
    } else {
        Bin1D bin = axis.getBin(static_cast<size_t>(index));
        result = bin.m_lower + (value - static_cast<double>(index))*bin.getBinSize();
    }

    return result;
}

void IntensityDataFunctions::coordinateToBinf(double& x, double& y, const OutputData<double>& data)
{
    x = coordinateToBinf(x, data.getAxis(BornAgain::X_AXIS_INDEX));
    y = coordinateToBinf(y, data.getAxis(BornAgain::Y_AXIS_INDEX));
}

void IntensityDataFunctions::coordinateFromBinf(
    double& x, double& y, const OutputData<double>& data)
{
    x = coordinateFromBinf(x, data.getAxis(BornAgain::X_AXIS_INDEX));
    y = coordinateFromBinf(y, data.getAxis(BornAgain::Y_AXIS_INDEX));
}
