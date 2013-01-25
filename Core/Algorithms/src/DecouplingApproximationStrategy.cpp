#include "DecouplingApproximationStrategy.h"
#include "Exceptions.h"

DecouplingApproximationStrategy::DecouplingApproximationStrategy()
{
}

void DecouplingApproximationStrategy::init(
        const SafePointerVector<FormFactorInfo> &form_factor_infos,
        const SafePointerVector<IInterferenceFunction> &ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException("Wrong number of formfactors or interference functions for Decoupling Approximation.");
    }
}

double DecouplingApproximationStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    double intensity = 0.0;
    complex_t amplitude = complex_t(0.0, 0.0);
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        complex_t ff = m_ff_infos[i]->mp_ff->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
        double fraction = m_ff_infos[i]->m_abundance;
        amplitude += fraction*ff;
        intensity += fraction*(std::norm(ff));
    }
    double amplitude_norm = std::norm(amplitude);
    double itf_function = m_ifs[0]->evaluate(k_i-k_f_bin.getMidPoint());
    return intensity + amplitude_norm*(itf_function-1.0);
}

bool DecouplingApproximationStrategy::checkVectorSizes() const
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs>0 && n_ifs==1);
}

