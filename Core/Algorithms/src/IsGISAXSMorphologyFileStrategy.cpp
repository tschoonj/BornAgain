#include "IsGISAXSMorphologyFileStrategy.h"

#include <algorithm>

IsGISAXSMorphologyFileStrategy::IsGISAXSMorphologyFileStrategy()
: m_win_x(0.0)
, m_win_y(0.0)
{
}

void IsGISAXSMorphologyFileStrategy::init(
        const SafePointerVector<FormFactorInfo> &form_factor_infos,
        const SafePointerVector<IInterferenceFunction> &ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException(
                "Wrong number of formfactors or interference functions for IsGISAXS morphology file strategy.");
    }
}

void IsGISAXSMorphologyFileStrategy::initPositions(
        const std::vector<double> &x_positions, const std::vector<double> &y_positions)
{
    m_x_positions = x_positions;
    m_y_positions = y_positions;
    // init window sizes for Hann function
    double x_min = *std::min_element(m_x_positions.begin(), m_x_positions.end());
    double x_max = *std::max_element(m_x_positions.begin(), m_x_positions.end());
    double y_min = *std::min_element(m_y_positions.begin(), m_y_positions.end());
    double y_max = *std::max_element(m_y_positions.begin(), m_y_positions.end());
    m_win_x = x_max - x_min;
    m_win_y = y_max - y_min;
    if (m_win_x <= 0.0 || m_win_y <= 0.0) {
        throw Exceptions::ClassInitializationException("Window sizes should be strictly positive");
    }
}

double IsGISAXSMorphologyFileStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    complex_t mean_ff = complex_t(0.0, 0.0);

    // calculate form factors
    std::vector<complex_t> ff_values;
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        ff_values.push_back(m_ff_infos[i]->mp_ff->evaluate(k_i, k_f_bin, alpha_i, alpha_f));
        mean_ff += m_ff_infos[i]->m_abundance*ff_values[i];
    }

    // coherent part
    complex_t coherent_amplitude = complex_t(0.0, 0.0);
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        complex_t phase = q.x()*m_x_positions[i] + q.y()*m_y_positions[i];
        double fraction = m_ff_infos[i]->m_abundance;
        double hann_value = hannFunction(m_x_positions[i], m_y_positions[i]);
        coherent_amplitude += fraction*ff_values[i]*std::exp( complex_t(0.0, 1.0)*phase )*hann_value;
    }
    double coherent_intensity = std::norm(coherent_amplitude);

    // diffuse part
    double diffuse_intensity = 0.0;
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        diffuse_intensity += m_ff_infos[i]->m_abundance*std::norm(ff_values[i]);
        for (size_t j=i+1; j<m_ff_infos.size(); ++j) {
            double x_diff = m_x_positions[i]-m_x_positions[j];
            double y_diff = m_y_positions[i]-m_y_positions[j];
            complex_t phase = q.x()*x_diff + q.y()*y_diff;
            diffuse_intensity += m_ff_infos[i]->m_abundance * m_ff_infos[j]->m_abundance *
                    2.0*(ff_values[i]*std::conj(ff_values[j]) *
                    std::exp( complex_t(0.0, 1.0)*phase )).real();
        }
    }
//    // diffuse part from IsGISAXS --> seems to be wrong (contains only one probability in cross-products and lacks the factor 2)
//    double diffuse_intensity = 0.0;
//    for (size_t i=0; i<m_form_factors.size(); ++i) {
//        for (size_t j=i; j<m_form_factors.size(); ++j) {
//            double x_diff = m_x_positions[i]-m_x_positions[j];
//            double y_diff = m_y_positions[i]-m_y_positions[j];
//            complex_t phase = q.x()*x_diff + q.y()*y_diff;
//            diffuse_intensity += m_fractions[i]*((ff_values[i]-mean_ff)*std::conj(ff_values[j]-mean_ff)*std::exp( complex_t(0.0, 1.0)*phase )).real();
//        }
//    }
    return coherent_intensity + diffuse_intensity;
}

bool IsGISAXSMorphologyFileStrategy::checkVectorSizes()
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs>0 && n_ifs==0);
}

double IsGISAXSMorphologyFileStrategy::hannFunction(double x, double y) const
{
    double result = (M_PI*M_PI/4.0)*std::cos(M_PI*x/m_win_x)*std::cos(M_PI*y/m_win_y);
    return result;
}
