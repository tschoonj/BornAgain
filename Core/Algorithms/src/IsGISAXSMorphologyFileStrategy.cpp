#include "IsGISAXSMorphologyFileStrategy.h"

IsGISAXSMorphologyFileStrategy::IsGISAXSMorphologyFileStrategy()
{
}

void IsGISAXSMorphologyFileStrategy::init(
        const std::vector<IFormFactor*>& form_factors,
        const std::vector<double>& fractions,
        const std::vector<IInterferenceFunction*>& interference_functions)
{
    IInterferenceFunctionStrategy::init(form_factors, fractions, interference_functions);
    if (!checkVectorSizes()) {
        throw ClassInitializationException(
                "Wrong number of formfactors or interference functions for IsGISAXS morphology file strategy.");
    }
}

double IsGISAXSMorphologyFileStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    //TODO: implement correct behaviour
    double intensity = 0.0;
    complex_t amplitude = complex_t(0.0, 0.0);
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        complex_t ff = m_form_factors[i]->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
        double fraction = m_fractions[i];
        amplitude += fraction*ff;
        intensity += fraction*(std::norm(ff));
    }
    double amplitude_norm = std::norm(amplitude);
    double itf_function = m_interference_functions[0]->evaluate(k_i-k_f_bin.getMidPoint());
    return intensity + amplitude_norm*(itf_function-1.0);
}

bool IsGISAXSMorphologyFileStrategy::checkVectorSizes()
{
    size_t n_ffs = m_form_factors.size();
    size_t n_frs = m_fractions.size();
    size_t n_ifs = m_interference_functions.size();
    return (n_ffs==n_frs && n_ifs==1);
}
