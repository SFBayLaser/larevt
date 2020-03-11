#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Principal/Event.h"
#include "art/Persistency/Provenance/ScheduleContext.h"
#include "fhiclcpp/ParameterSet.h"
#include "larevt/CalibrationDBI/Interface/PmtGainService.h"
#include "larevt/CalibrationDBI/Providers/SIOVPmtGainProvider.h"
#include "larcore/CoreUtils/EnsureOnlyOneSchedule.h"

namespace lariov{

  /**
     \class SIOVPmtGainService
     art service implementation of PmtGainService.  Implements
     a pmt gain retrieval service for database scheme in which
     all elements in a database folder share a common interval of validity
  */
  class SIOVPmtGainService : public PmtGainService,
                             private lar::EnsureOnlyOneSchedule<SIOVPmtGainService> {

    public:

      SIOVPmtGainService(fhicl::ParameterSet const& pset, art::ActivityRegistry& reg);
      ~SIOVPmtGainService(){}

      void PreProcessEvent(const art::Event& evt, art::ScheduleContext) {
        fProvider.UpdateTimeStamp(evt.time().value());
      }

    private:

      PmtGainProvider const& DoGetProvider() const override {
        return fProvider;
      }

      PmtGainProvider const* DoGetProviderPtr() const override {
        return &fProvider;
      }

      SIOVPmtGainProvider fProvider;
  };
}//end namespace lariov

DECLARE_ART_SERVICE_INTERFACE_IMPL(lariov::SIOVPmtGainService, lariov::PmtGainService, SHARED)


namespace lariov{

  SIOVPmtGainService::SIOVPmtGainService(fhicl::ParameterSet const& pset, art::ActivityRegistry& reg)
  : fProvider(pset.get<fhicl::ParameterSet>("PmtGainProvider"))
  {
    //register callback to update local database cache before each event is processed
    reg.sPreProcessEvent.watch(this, &SIOVPmtGainService::PreProcessEvent);
  }

}//end namespace lariov

DEFINE_ART_SERVICE_INTERFACE_IMPL(lariov::SIOVPmtGainService, lariov::PmtGainService)
