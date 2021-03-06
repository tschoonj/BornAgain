// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformFromDomain.cpp
//! @brief     Implements namespace TransformFromDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TransformFromDomain.h"
#include "AxesItems.h"
#include "Beam.h"
#include "BeamAngleItems.h"
#include "BeamItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "ConvolutionDetectorResolution.h"
#include "DetectorItems.h"
#include "SphericalDetectorItem.h"
#include "RectangularDetectorItem.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "FTDecayFunctionItems.h"
#include "FTDistributionItems.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "InfinitePlane.h"
#include "INodeUtils.h"
#include "InterferenceFunctionItems.h"
#include "InterferenceFunctions.h"
#include "Lattice2DItems.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerItem.h"
#include "LayerRoughness.h"
#include "LayerRoughnessItems.h"
#include "Line.h"
#include "MaskItems.h"
#include "ModelPath.h"
#include "Numeric.h"
#include "ParameterPattern.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "RegionOfInterest.h"
#include "RectangularDetector.h"
#include "ResolutionFunctionItems.h"
#include "SphericalDetector.h"
#include "Units.h"
#include "VectorItem.h"
#include "ParameterTreeUtils.h"
#include "InstrumentItem.h"
#include "ResolutionFunction2DGaussian.h"
#include "ParameterUtils.h"
#include "Particle.h"
#include "ParticleDistribution.h"
#include <limits>

using namespace INodeUtils;

void SetPDF1D(SessionItem* item, const IFTDistribution1D* pdf, QString group_name);
void setPDF2D(SessionItem* item, const IFTDistribution2D* pdf, QString group_name);
void SetDecayFunction1D(SessionItem* item, const IFTDecayFunction1D* pdf, QString group_name);
void SetDecayFunction2D(SessionItem* item, const IFTDecayFunction2D* pdf, QString group_name);

void set2DLatticeParameters(SessionItem* item, const Lattice2D& lattice);

void setDistribution(SessionItem* item, ParameterDistribution par_distr,
                     QString group_name, double factor = 1.0);

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunctionRadialParaCrystal* sample)
{
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE,
                                sample->peakDistance());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH,
                                sample->dampingLength());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE,
                                sample->domainSize());
    item->setItemValue(InterferenceFunctionRadialParaCrystalItem::P_KAPPA,
                                sample->kappa());

    auto ipdf = OnlyChildOfType<IFTDistribution1D>(*sample);
    QString group_name = InterferenceFunctionRadialParaCrystalItem::P_PDF;
    SetPDF1D(item, ipdf, group_name);
}

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunction2DParaCrystal* sample)
{
    set2DLatticeParameters(item, sample->lattice());

    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH,
                                sample->dampingLength());
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1,
                                sample->domainSizes()[0]);
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2,
                                sample->domainSizes()[1]);
    item->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION,
                                sample->integrationOverXi());

    auto pdfs = ChildNodesOfType<IFTDistribution2D>(*sample);
    QStringList group_names;
    group_names << InterferenceFunction2DParaCrystalItem::P_PDF1
                << InterferenceFunction2DParaCrystalItem::P_PDF2;
    for (unsigned i = 0; i < pdfs.size(); ++i)
        setPDF2D(item, pdfs[i], group_names[i]);
}

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunction1DLattice* sample)
{
    Lattice1DParameters lattice_params = sample->getLatticeParameters();
    item->setItemValue(InterferenceFunction1DLatticeItem::P_LENGTH,
                                lattice_params.m_length);
    item->setItemValue(InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE,
                                Units::rad2deg(lattice_params.m_xi));

    auto pdf = OnlyChildOfType<IFTDecayFunction1D>(*sample);
    QString group_name = InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION;
    SetDecayFunction1D(item, pdf, group_name);
}

void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const InterferenceFunction2DLattice* sample)
{
    set2DLatticeParameters(item, sample->lattice());

    item->setItemValue(InterferenceFunction2DLatticeItem::P_XI_INTEGRATION,
                                sample->integrationOverXi());

    auto p_pdf = OnlyChildOfType<IFTDecayFunction2D>(*sample);
    QString group_name = InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION;
    SetDecayFunction2D(item, p_pdf, group_name);
}

void TransformFromDomain::setItemFromSample(SessionItem* layerItem, const Layer* layer,
                                            const LayerInterface* top_interface)
{
    layerItem->setItemValue(LayerItem::P_THICKNESS, layer->thickness());
    layerItem->setGroupProperty(LayerItem::P_ROUGHNESS, Constants::LayerZeroRoughnessType);
    layerItem->setItemValue(LayerItem::P_NSLICES, (int)layer->numberOfSlices());

    if (top_interface) {
        const LayerRoughness* roughness = top_interface->getRoughness();
        if (TransformFromDomain::isValidRoughness(roughness)) {
            SessionItem* roughnessItem = layerItem->setGroupProperty(
                LayerItem::P_ROUGHNESS, Constants::LayerBasicRoughnessType);
            TransformFromDomain::setItemFromSample(roughnessItem, roughness);
        }
    }
}

void TransformFromDomain::setItemFromSample(SessionItem* item, const LayerRoughness* sample)
{
    item->setItemValue(LayerBasicRoughnessItem::P_SIGMA, sample->getSigma());
    item->setItemValue(LayerBasicRoughnessItem::P_HURST, sample->getHurstParameter());
    item->setItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH,
                                sample->getLatteralCorrLength());
}

//! Initialization of ParticleDistributionItem
void TransformFromDomain::setItemFromSample(SessionItem* item,
                                            const ParticleDistribution* sample)
{
    ParticleDistributionItem *distItem = dynamic_cast<ParticleDistributionItem*>(item);
    Q_ASSERT(distItem);

    distItem->setItemValue(ParticleItem::P_ABUNDANCE, sample->abundance());

    ParameterDistribution par_distr = sample->parameterDistribution();
    QString main_distr_par_name = QString::fromStdString(par_distr.getMainParameterName());

    distItem->setDomainCacheName(main_distr_par_name);

    double unit_factor(1.0);
    if (ParameterUtils::mainParUnits(*sample) == BornAgain::UnitsRad)
        unit_factor = 1. / Units::degree;

    QString group_name = ParticleDistributionItem::P_DISTRIBUTION;
    setDistribution(distItem, par_distr, group_name, unit_factor);
}

//! Returns true if given roughness is non-zero roughness
bool TransformFromDomain::isValidRoughness(const LayerRoughness* roughness)
{
    if (!roughness)
        return false;
    if (roughness->getSigma() == 0 && roughness->getHurstParameter() == 0.0
        && roughness->getLatteralCorrLength() == 0.0)
        return false;
    return true;
}

void TransformFromDomain::setItemFromSample(BeamItem* beamItem, const GISASSimulation& simulation)
{
    Q_ASSERT(beamItem);
    Beam beam = simulation.getInstrument().getBeam();

    beamItem->setIntensity(beam.getIntensity());
    beamItem->setWavelength(beam.getWavelength());
    beamItem->setInclinationAngle(Units::rad2deg(beam.getAlpha()));
    beamItem->setAzimuthalAngle(Units::rad2deg(beam.getPhi()));

    // distribution parameters
    const DistributionHandler::Distributions_t distributions
        = simulation.getDistributionHandler().getDistributions();
    for (size_t i = 0; i < distributions.size(); ++i) {
        ParameterPattern pattern_wavelength;
        pattern_wavelength.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
        ParameterPattern pattern_alpha;
        pattern_alpha.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
        ParameterPattern pattern_phi;
        pattern_phi.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Azimuth);
        std::string mainParameterName = distributions[i].getMainParameterName();
        if (mainParameterName == pattern_wavelength.toStdString()) {
            BeamDistributionItem* beamWavelength = dynamic_cast<BeamDistributionItem*>(
                beamItem->getItem(BeamItem::P_WAVELENGTH));
            setItemFromSample(beamWavelength, distributions[i]);
        } else if (mainParameterName == pattern_alpha.toStdString()) {
            BeamDistributionItem* inclinationAngle = dynamic_cast<BeamDistributionItem*>(
                beamItem->getItem(BeamItem::P_INCLINATION_ANGLE));
            setItemFromSample(inclinationAngle, distributions[i]);
        } else if (mainParameterName == pattern_phi.toStdString()) {
            BeamDistributionItem* azimuthalAngle = dynamic_cast<BeamDistributionItem*>(
                beamItem->getItem(BeamItem::P_AZIMUTHAL_ANGLE));
            setItemFromSample(azimuthalAngle, distributions[i]);
        }
    }
}

void TransformFromDomain::setInstrumentDetectorFromSample(InstrumentItem* instrumentItem,
                                            const GISASSimulation& simulation)
{
    const IDetector2D* iDetector = simulation.getInstrument().getDetector();

    if(auto detector = dynamic_cast<const SphericalDetector*>(iDetector)) {
        instrumentItem->setDetectorGroup(Constants::SphericalDetectorType);
        auto item = dynamic_cast<SphericalDetectorItem*> (instrumentItem->detectorItem());
        setItemFromSample(item, *detector);
    }

    else if(auto detector = dynamic_cast<const RectangularDetector*>(iDetector)) {
        instrumentItem->setDetectorGroup(Constants::RectangularDetectorType);
        auto item = dynamic_cast<RectangularDetectorItem*> (instrumentItem->detectorItem());
        setItemFromSample(item, *detector);

        Q_ASSERT(item);
        setItemFromSample(item,* detector);
    }

    else {
        throw GUIHelpers::Error(
            "TransformFromDomain::setInstrumentDetectorFromSample(DetectorItem*) -> Unknown detector type.");
    }
}


void TransformFromDomain::setItemFromSample(SphericalDetectorItem* detectorItem,
                                            const SphericalDetector& detector)
{
    // Axes
    const IAxis& phi_axis = detector.getAxis(0);
    const IAxis& alpha_axis = detector.getAxis(1);

    BasicAxisItem* phiAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(SphericalDetectorItem::P_PHI_AXIS));
    Q_ASSERT(phiAxisItem);
    phiAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)phi_axis.size());
    phiAxisItem->setItemValue(BasicAxisItem::P_MIN, Units::rad2deg(phi_axis.getMin()));
    phiAxisItem->setItemValue(BasicAxisItem::P_MAX, Units::rad2deg(phi_axis.getMax()));

    BasicAxisItem* alphaAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(SphericalDetectorItem::P_ALPHA_AXIS));
    Q_ASSERT(alphaAxisItem);
    alphaAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)alpha_axis.size());
    alphaAxisItem->setItemValue(BasicAxisItem::P_MIN, Units::rad2deg(alpha_axis.getMin()));
    alphaAxisItem->setItemValue(BasicAxisItem::P_MAX, Units::rad2deg(alpha_axis.getMax()));

    // detector resolution
    if (const IDetectorResolution* p_resfunc = detector.detectorResolution()) {
        if (const ConvolutionDetectorResolution* p_convfunc
            = dynamic_cast<const ConvolutionDetectorResolution*>(p_resfunc)) {
            if (const ResolutionFunction2DGaussian* resfunc
                = dynamic_cast<const ResolutionFunction2DGaussian*>(
                    p_convfunc->getResolutionFunction2D())) {
                SessionItem* item
                    = detectorItem->setGroupProperty(SphericalDetectorItem::P_RESOLUTION_FUNCTION,
                                                     Constants::ResolutionFunction2DGaussianType);
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_X,
                                            Units::rad2deg(resfunc->getSigmaX()));
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_Y,
                                            Units::rad2deg(resfunc->getSigmaY()));
            } else {
                throw GUIHelpers::Error("TransformFromDomain::setItemFromSample("
                                        "SphericalDetectorItem* detectorItem, const GISASSimulation "
                                        "&simulation) -> Error, unknown detector resolution "
                                        "function");
            }
        } else {
            throw GUIHelpers::Error(
                "TransformFromDomain::setItemFromSample(SphericalDetectorItem "
                "*detectorItem, const GISASSimulation& simulation) -> Error, not a "
                "ConvolutionDetectorResolution function");
        }
    }
}


void TransformFromDomain::setItemFromSample(RectangularDetectorItem* detectorItem,
                                            const RectangularDetector& detector)
{
    // Axes
    BasicAxisItem* xAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(RectangularDetectorItem::P_X_AXIS));
    Q_ASSERT(xAxisItem);
    xAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)detector.getNbinsX());
    xAxisItem->setItemValue(BasicAxisItem::P_MAX, detector.getWidth());

    BasicAxisItem* yAxisItem = dynamic_cast<BasicAxisItem*>(
        detectorItem->getItem(RectangularDetectorItem::P_Y_AXIS));
    Q_ASSERT(yAxisItem);
    yAxisItem->setItemValue(BasicAxisItem::P_NBINS, (int)detector.getNbinsY());
    yAxisItem->setItemValue(BasicAxisItem::P_MAX, detector.getHeight());

    if(detector.getDetectorArrangment() == RectangularDetector::GENERIC) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_GENERIC);

        kvector_t normal = detector.getNormalVector();
        detectorItem->getItem(RectangularDetectorItem::P_NORMAL)->setItemValue(
            VectorItem::P_X, normal.x());
        detectorItem->getItem(RectangularDetectorItem::P_NORMAL)->setItemValue(
            VectorItem::P_Y, normal.y());
        detectorItem->getItem(RectangularDetectorItem::P_NORMAL)->setItemValue(
            VectorItem::P_Z, normal.z());

        kvector_t direction = detector.getDirectionVector();
        detectorItem->getItem(RectangularDetectorItem::P_DIRECTION)->setItemValue(
            VectorItem::P_X, direction.x());
        detectorItem->getItem(RectangularDetectorItem::P_DIRECTION)->setItemValue(
            VectorItem::P_Y, direction.y());
        detectorItem->getItem(RectangularDetectorItem::P_DIRECTION)->setItemValue(
            VectorItem::P_Z, direction.z());

        detectorItem->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());
    }

    else if (detector.getDetectorArrangment() == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_SAMPLE);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_DIRECT_BEAM);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_REFLECTED_BEAM);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_U0, detector.getU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_V0, detector.getV0());

    } else if (detector.getDetectorArrangment()
               == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        detectorItem->setDetectorAlignment(Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS);
        detectorItem->setItemValue(RectangularDetectorItem::P_DISTANCE,
                                            detector.getDistance());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_U0,
                                            detector.getDirectBeamU0());
        detectorItem->setItemValue(RectangularDetectorItem::P_DBEAM_V0,
                                            detector.getDirectBeamV0());

    } else {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(RectangularDetectorItem* detectorItem "
            "Error. Unknown detector arrangement");
    }

    // detector resolution
    if (const IDetectorResolution* p_resfunc = detector.detectorResolution()) {
        if (const ConvolutionDetectorResolution* p_convfunc
            = dynamic_cast<const ConvolutionDetectorResolution*>(p_resfunc)) {
            if (const ResolutionFunction2DGaussian* resfunc
                = dynamic_cast<const ResolutionFunction2DGaussian*>(
                    p_convfunc->getResolutionFunction2D())) {
                SessionItem* item
                    = detectorItem->setGroupProperty(RectangularDetectorItem::P_RESOLUTION_FUNCTION,
                                                     Constants::ResolutionFunction2DGaussianType);
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_X,
                                            resfunc->getSigmaX());
                item->setItemValue(ResolutionFunction2DGaussianItem::P_SIGMA_Y,
                                            resfunc->getSigmaY());
            } else {
                throw GUIHelpers::Error("TransformFromDomain::setItemFromSample("
                                        "RectangularDetectorItem* detectorItem, const GISASSimulation "
                                        "&simulation) -> Error, unknown detector resolution "
                                        "function");
            }
        } else {
            throw GUIHelpers::Error(
                "TransformFromDomain::setItemFromSample(RectangularDetectorItem "
                "*detectorItem, const GISASSimulation& simulation) -> Error, not a "
                "ConvolutionDetectorResolution function");
        }
    }
}

void TransformFromDomain::setDetectorMasks(DetectorItem* detectorItem, const GISASSimulation& simulation)
{
    const IDetector2D* detector = simulation.getInstrument().getDetector();
    if( (detector->getDetectorMask() && detector->getDetectorMask()->numberOfMasks()) ||
        detector->regionOfInterest()) {
        detectorItem->createMaskContainer();

        double scale(1.0);
        if(detectorItem->modelType() == Constants::SphericalDetectorType)
            scale = 1./Units::degree;

        setDetectorMasks(detectorItem->maskContainerItem(), *detector, scale);
    }
}

void TransformFromDomain::setDetectorMasks(MaskContainerItem* containerItem,
                                           const IDetector2D& detector, double scale)
{
    auto detectorMask = detector.getDetectorMask();
    for(size_t i_mask=0; i_mask<detectorMask->numberOfMasks(); ++i_mask) {
        bool mask_value(false);
        const IShape2D* shape = detectorMask->getMaskShape(i_mask, mask_value);

        if(const Ellipse* ellipse = dynamic_cast<const Ellipse*>(shape)) {
            EllipseItem* ellipseItem = new EllipseItem();
            ellipseItem->setItemValue(EllipseItem::P_XCENTER, scale*ellipse->getCenterX());
            ellipseItem->setItemValue(EllipseItem::P_YCENTER, scale*ellipse->getCenterY());
            ellipseItem->setItemValue(EllipseItem::P_XRADIUS, scale*ellipse->getRadiusX());
            ellipseItem->setItemValue(EllipseItem::P_YRADIUS, scale*ellipse->getRadiusY());
            ellipseItem->setItemValue(EllipseItem::P_ANGLE, scale*ellipse->getTheta());
            ellipseItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            containerItem->insertItem(0, ellipseItem);
        }

        else if(const Rectangle* rectangle = dynamic_cast<const Rectangle*>(shape)) {
            RectangleItem* rectangleItem = new RectangleItem();
            rectangleItem->setItemValue(RectangleItem::P_XLOW, scale*rectangle->getXlow());
            rectangleItem->setItemValue(RectangleItem::P_YLOW, scale*rectangle->getYlow());
            rectangleItem->setItemValue(RectangleItem::P_XUP, scale*rectangle->getXup());
            rectangleItem->setItemValue(RectangleItem::P_YUP, scale*rectangle->getYup());
            rectangleItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            containerItem->insertItem(0, rectangleItem);

        }

        else if(const Polygon* polygon = dynamic_cast<const Polygon*>(shape)) {
            PolygonItem* polygonItem = new PolygonItem();
            std::vector<double> xpos, ypos;
            polygon->getPoints(xpos, ypos);
            for(size_t i_point=0; i_point<xpos.size(); ++i_point) {
                PolygonPointItem* pointItem = new PolygonPointItem();
                pointItem->setItemValue(PolygonPointItem::P_POSX, scale*xpos[i_point]);
                pointItem->setItemValue(PolygonPointItem::P_POSY, scale*ypos[i_point]);
                polygonItem->insertItem(-1, pointItem);
            }

            polygonItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            polygonItem->setItemValue(PolygonItem::P_ISCLOSED, true);

            containerItem->insertItem(0, polygonItem);
        }

        else if(const VerticalLine* vline = dynamic_cast<const VerticalLine*>(shape)) {
            VerticalLineItem* lineItem = new VerticalLineItem();
            lineItem->setItemValue(VerticalLineItem::P_POSX, scale*vline->getXpos());
            lineItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            containerItem->insertItem(0, lineItem);
        }

        else if(const HorizontalLine* hline = dynamic_cast<const HorizontalLine*>(shape)) {
            HorizontalLineItem* lineItem = new HorizontalLineItem();
            lineItem->setItemValue(HorizontalLineItem::P_POSY, scale*hline->getYpos());
            lineItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            containerItem->insertItem(0, lineItem);
        }

        else if(const InfinitePlane* plane = dynamic_cast<const InfinitePlane*>(shape)) {
            Q_UNUSED(plane);
            MaskAllItem* planeItem = new MaskAllItem();
            planeItem->setItemValue(MaskItem::P_MASK_VALUE, mask_value);
            containerItem->insertItem(-1, planeItem);
        }

        else {
            throw GUIHelpers::Error("TransformFromDomain::setDetectorMasks() -> Error. "
                                    "Unknown shape");
        }
    }

    if(detector.regionOfInterest()) {
        RegionOfInterestItem *roiItem = new RegionOfInterestItem();
        roiItem->setItemValue(RectangleItem::P_XLOW, scale*detector.regionOfInterest()->getXlow());
        roiItem->setItemValue(RectangleItem::P_YLOW, scale*detector.regionOfInterest()->getYlow());
        roiItem->setItemValue(RectangleItem::P_XUP, scale*detector.regionOfInterest()->getXup());
        roiItem->setItemValue(RectangleItem::P_YUP, scale*detector.regionOfInterest()->getYup());
        containerItem->insertItem(-1, roiItem);
    }
}


void TransformFromDomain::setItemFromSample(BeamDistributionItem* beamDistributionItem,
                                            const ParameterDistribution& parameterDistribution)
{
    Q_ASSERT(beamDistributionItem);

    if (parameterDistribution.getMinValue() < parameterDistribution.getMaxValue()) {
        throw GUIHelpers::Error(
            "TransformFromDomain::setItemFromSample(BeamDistributionItem* beamDistributionItem,"
            "const ParameterDistribution& parameterDistribution) -> Error. ParameterDistribution "
            "with defined min,max are not yet implemented in GUI");
    }

    double unit_factor(1.0);
    if (beamDistributionItem->modelType() == Constants::BeamAzimuthalAngleType
        || beamDistributionItem->modelType() == Constants::BeamInclinationAngleType) {
        unit_factor = 1. / Units::degree;
    }
    QString group_name = BeamDistributionItem::P_DISTRIBUTION;
    setDistribution(beamDistributionItem, parameterDistribution, group_name, unit_factor);
}

void SetPDF1D(SessionItem* item, const IFTDistribution1D* ipdf, QString group_name)
{
    if (const FTDistribution1DCauchy* pdf = dynamic_cast<const FTDistribution1DCauchy*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DCauchyType);
        pdfItem->setItemValue(FTDistribution1DCauchyItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DGauss* pdf
               = dynamic_cast<const FTDistribution1DGauss*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DGaussType);
        pdfItem->setItemValue(FTDistribution1DGaussItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DGate* pdf = dynamic_cast<const FTDistribution1DGate*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DGateType);
        pdfItem->setItemValue(FTDistribution1DGateItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DTriangle* pdf
               = dynamic_cast<const FTDistribution1DTriangle*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DTriangleType);
        pdfItem->setItemValue(FTDistribution1DTriangleItem::P_OMEGA,
                                       pdf->omega());
    } else if (const FTDistribution1DCosine* pdf
               = dynamic_cast<const FTDistribution1DCosine*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DCosineType);
        pdfItem->setItemValue(FTDistribution1DCosineItem::P_OMEGA, pdf->omega());
    } else if (const FTDistribution1DVoigt* pdf
               = dynamic_cast<const FTDistribution1DVoigt*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution1DVoigtType);
        pdfItem->setItemValue(FTDistribution1DVoigtItem::P_OMEGA, pdf->omega());
        pdfItem->setItemValue(FTDistribution1DVoigtItem::P_ETA, pdf->eta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setPDF1D: -> Error");
    }
}

void setPDF2D(SessionItem* item, const IFTDistribution2D* pdf, QString group_name)
{
    if (const FTDistribution2DCauchy* pdf_cauchy
        = dynamic_cast<const FTDistribution2DCauchy*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DCauchyType);
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_OMEGA_X,
                                       pdf_cauchy->omegaX());
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_OMEGA_Y,
                                       pdf_cauchy->omegaY());
        pdfItem->setItemValue(FTDistribution2DCauchyItem::P_GAMMA,
                                       Units::rad2deg(pdf_cauchy->gamma()));
    } else if (const FTDistribution2DGauss* pdf_gauss
               = dynamic_cast<const FTDistribution2DGauss*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DGaussType);
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_OMEGA_X,
                                       pdf_gauss->omegaX());
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_OMEGA_Y,
                                       pdf_gauss->omegaY());
        pdfItem->setItemValue(FTDistribution2DGaussItem::P_GAMMA,
                                       Units::rad2deg(pdf_gauss->gamma()));
    } else if (const FTDistribution2DGate* pdf_gate
               = dynamic_cast<const FTDistribution2DGate*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DGateType);
        pdfItem->setItemValue(FTDistribution2DGateItem::P_OMEGA_X,
                                       pdf_gate->omegaX());
        pdfItem->setItemValue(FTDistribution2DGateItem::P_OMEGA_Y,
                                       pdf_gate->omegaY());
        pdfItem->setItemValue(FTDistribution2DGateItem::P_GAMMA,
                                       Units::rad2deg(pdf_gate->gamma()));
    } else if (const FTDistribution2DCone* pdf_cone
               = dynamic_cast<const FTDistribution2DCone*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DConeType);
        pdfItem->setItemValue(FTDistribution2DConeItem::P_OMEGA_X,
                                       pdf_cone->omegaX());
        pdfItem->setItemValue(FTDistribution2DConeItem::P_OMEGA_Y,
                                       pdf_cone->omegaY());
        pdfItem->setItemValue(FTDistribution2DConeItem::P_GAMMA,
                                       Units::rad2deg(pdf_cone->gamma()));
    } else if (const FTDistribution2DVoigt* pdf_voigt
               = dynamic_cast<const FTDistribution2DVoigt*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDistribution2DVoigtType);
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_OMEGA_X,
                                       pdf_voigt->omegaX());
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_OMEGA_Y,
                                       pdf_voigt->omegaY());
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_GAMMA,
                                       Units::rad2deg(pdf_voigt->gamma()));
        pdfItem->setItemValue(FTDistribution2DVoigtItem::P_ETA, pdf_voigt->eta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setPDF2D: -> Error");
    }
}

void SetDecayFunction1D(SessionItem* item, const IFTDecayFunction1D* ipdf, QString group_name)
{
    if (const FTDecayFunction1DCauchy* pdf = dynamic_cast<const FTDecayFunction1DCauchy*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DCauchyType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->decayLength());
    } else if (const FTDecayFunction1DGauss* pdf
               = dynamic_cast<const FTDecayFunction1DGauss*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DGaussType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->decayLength());
    } else if (const FTDecayFunction1DTriangle* pdf
               = dynamic_cast<const FTDecayFunction1DTriangle*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DTriangleType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH,
                                       pdf->decayLength());
    } else if (const FTDecayFunction1DVoigt* pdf
               = dynamic_cast<const FTDecayFunction1DVoigt*>(ipdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction1DVoigtType);
        pdfItem->setItemValue(FTDecayFunction1DItem::P_DECAY_LENGTH, pdf->decayLength());
        pdfItem->setItemValue(FTDecayFunction1DVoigtItem::P_ETA, pdf->eEta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::SetDecayFunction1D: -> Error");
    }
}

void SetDecayFunction2D(SessionItem* item, const IFTDecayFunction2D* pdf, QString group_name)
{
    if (const FTDecayFunction2DCauchy* pdf_cauchy
        = dynamic_cast<const FTDecayFunction2DCauchy*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction2DCauchyType);
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X,
                                       pdf_cauchy->decayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y,
                                       pdf_cauchy->decayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA,
                                       Units::rad2deg(pdf_cauchy->gamma()));
    } else if (const FTDecayFunction2DGauss* pdf_gauss
               = dynamic_cast<const FTDecayFunction2DGauss*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction2DGaussType);
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X,
                                       pdf_gauss->decayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y,
                                       pdf_gauss->decayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA,
                                       Units::rad2deg(pdf_gauss->gamma()));
    } else if (const FTDecayFunction2DVoigt* pdf_voigt
               = dynamic_cast<const FTDecayFunction2DVoigt*>(pdf)) {
        SessionItem* pdfItem
            = item->setGroupProperty(group_name, Constants::FTDecayFunction2DVoigtType);
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_X,
                                       pdf_voigt->decayLengthX());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_DECAY_LENGTH_Y,
                                       pdf_voigt->decayLengthY());
        pdfItem->setItemValue(FTDecayFunction2DItem::P_GAMMA,
                                       Units::rad2deg(pdf_voigt->gamma()));
        pdfItem->setItemValue(FTDecayFunction2DVoigtItem::P_ETA, pdf_voigt->eta());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::SetDecayFunction2D: -> Error");
    }
}

void set2DLatticeParameters(SessionItem* item, const Lattice2D& lattice)
{
    SessionItem* latticeItem(0);
    if (lattice.getName() == BornAgain::SquareLatticeType) {
        latticeItem = item->setGroupProperty(
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, Constants::SquareLatticeType);
        latticeItem->setItemValue(SquareLatticeItem::P_LATTICE_LENGTH, lattice.length1());

    } else if (lattice.getName() == BornAgain::HexagonalLatticeType) {
        latticeItem = item->setGroupProperty(
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, Constants::HexagonalLatticeType);
        latticeItem->setItemValue(HexagonalLatticeItem::P_LATTICE_LENGTH, lattice.length1());

    } else {
        latticeItem = item->setGroupProperty(
            InterferenceFunction2DLatticeItem::P_LATTICE_TYPE, Constants::BasicLatticeType);
        latticeItem->setItemValue(BasicLatticeItem::P_LATTICE_LENGTH1, lattice.length1());
        latticeItem->setItemValue(BasicLatticeItem::P_LATTICE_LENGTH2, lattice.length2());
        latticeItem->setItemValue(BasicLatticeItem::P_LATTICE_ANGLE,
                                  Units::rad2deg(lattice.latticeAngle()));
    }
    latticeItem->setItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE,
                       Units::rad2deg(lattice.rotationAngle()));
}

void setDistribution(SessionItem* partDistrItem, ParameterDistribution par_distr,
                     QString group_name, double factor)
{
    const IDistribution1D* p_distribution = par_distr.getDistribution();

    SessionItem* item = 0;
    if (const DistributionGate* distr = dynamic_cast<const DistributionGate*>(p_distribution)) {
        item = partDistrItem->setGroupProperty(group_name, Constants::DistributionGateType);
        item->setItemValue(DistributionGateItem::P_MIN, factor*distr->getMin());
        item->setItemValue(DistributionGateItem::P_MAX, factor*distr->getMax());
    } else if (const DistributionLorentz* distr
               = dynamic_cast<const DistributionLorentz*>(p_distribution)) {
        item = partDistrItem->setGroupProperty(group_name, Constants::DistributionLorentzType);
        item->setItemValue(DistributionLorentzItem::P_MEAN, factor*distr->getMean());
        item->setItemValue(DistributionLorentzItem::P_HWHM, factor*distr->getHWHM());
    } else if (const DistributionGaussian* distr
               = dynamic_cast<const DistributionGaussian*>(p_distribution)) {
        item = partDistrItem->setGroupProperty(group_name, Constants::DistributionGaussianType);
        item->setItemValue(DistributionGaussianItem::P_MEAN, factor*distr->getMean());
        item->setItemValue(DistributionGaussianItem::P_STD_DEV, factor*distr->getStdDev());
    } else if (const DistributionLogNormal* distr
               = dynamic_cast<const DistributionLogNormal*>(p_distribution)) {
        item = partDistrItem->setGroupProperty(group_name, Constants::DistributionLogNormalType);
        item->setItemValue(DistributionLogNormalItem::P_MEDIAN, factor*distr->getMedian());
        item->setItemValue(DistributionLogNormalItem::P_SCALE_PAR,
                                       distr->getScalePar());
    } else if (const DistributionCosine* distr
               = dynamic_cast<const DistributionCosine*>(p_distribution)) {
        item = partDistrItem->setGroupProperty(group_name, Constants::DistributionCosineType);
        item->setItemValue(DistributionCosineItem::P_MEAN, factor*distr->getMean());
        item->setItemValue(DistributionCosineItem::P_SIGMA, factor*distr->getSigma());
    } else if (const DistributionTrapezoid* distr
               = dynamic_cast<const DistributionTrapezoid*>(p_distribution)) {
        item = partDistrItem->setGroupProperty(group_name, Constants::DistributionTrapezoidType);
        item->setItemValue(DistributionTrapezoidItem::P_CENTER, factor*distr->getMean());
        item->setItemValue(DistributionTrapezoidItem::P_LEFTWIDTH, factor*distr->getLeftWidth());
        item->setItemValue(DistributionTrapezoidItem::P_MIDDLEWIDTH,
                           factor*distr->getMiddleWidth());
        item->setItemValue(DistributionTrapezoidItem::P_RIGHTWIDTH, factor*distr->getRightWidth());
    } else {
        throw GUIHelpers::Error("TransformFromDomain::setDistribution: -> unknown distribution");
    }

    DistributionItem *distItem = dynamic_cast<DistributionItem*>(item);
    Q_ASSERT(distItem);

    distItem->setItemValue(DistributionItem::P_NUMBER_OF_SAMPLES, (int)par_distr.getNbrSamples());

    if(distItem->isTag(DistributionItem::P_SIGMA_FACTOR))
        distItem->setItemValue(DistributionItem::P_SIGMA_FACTOR, par_distr.getSigmaFactor());

    // TODO It's wrong if domain distribution made for angles.
    if(distItem->isTag(DistributionItem::P_LIMITS))
        distItem->init_limits_group(par_distr.getLimits(), factor);

}
