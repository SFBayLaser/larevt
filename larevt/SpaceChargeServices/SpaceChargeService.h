////////////////////////////////////////////////////////////////////////
// \file SpaceChargeService.h
//
// \brief pure virtual service interface for space charge distortions
//
// \author mrmooney@bnl.gov
//
////////////////////////////////////////////////////////////////////////
#ifndef SPACECHARGESERVICE_H
#define SPACECHARGESERVICE_H

#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "larevt/SpaceCharge/SpaceCharge.h"

namespace spacecharge {
  class SpaceChargeService {
  public:
    using provider_type = spacecharge::SpaceCharge;

    virtual ~SpaceChargeService() = default;
    virtual const spacecharge::SpaceCharge* provider() const = 0;
  };
}

DECLARE_ART_SERVICE_INTERFACE(spacecharge::SpaceChargeService, SHARED)

#endif // SPACECHARGESERVICE_H
