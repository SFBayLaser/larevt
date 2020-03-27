////////////////////////////////////////////////////////////////////////
// \file SpaceChargeServiceStandard.h
//
// \brief header of service for storing/accessing space charge distortions
//
// \author mrmooney@bnl.gov
//
////////////////////////////////////////////////////////////////////////
#ifndef SPACECHARGESERVICESTANDARD_H
#define SPACECHARGESERVICESTANDARD_H

#include "art/Framework/Principal/Run.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "larevt/SpaceCharge/SpaceChargeStandard.h"
#include "larevt/SpaceChargeServices/SpaceChargeService.h"

namespace spacecharge {
  class SpaceChargeServiceStandard : public SpaceChargeService {
  public:
    // this enables art to print the configuration help:
    // using Parameters =
    // art::ServiceTable<spacecharge::SpaceChargeStandard::ConfigurationParameters_t>;

    SpaceChargeServiceStandard(fhicl::ParameterSet const& pset, art::ActivityRegistry& reg);

  private:
    void reconfigure(fhicl::ParameterSet const& pset);
    void preBeginRun(const art::Run& run);

    const provider_type*
    provider() const override
    {
      return &fProp;
    }

    spacecharge::SpaceChargeStandard fProp;

  }; // class SpaceChargeServiceStandard
} // namespace spacecharge

DECLARE_ART_SERVICE_INTERFACE_IMPL(spacecharge::SpaceChargeServiceStandard,
                                   spacecharge::SpaceChargeService,
                                   SHARED)

#endif // SPACECHARGESERVICESTANDARD_H
