/**
 * @file   SimpleChannelFilterService_service.cc
 * @brief  Service for channel quality info
 * @author Gianluca Petrillo (petrillo@fnal.gov)
 * @date   November 24th, 2014
 * @see    SimpleChannelFilterService.h
 */

// Our header
#include "Filters/SimpleChannelFilterService.h"

// LArSoft libraries
#include "Geometry/Geometry.h"
#include "Geometry/GeometryCore.h"

// Framework libraries
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

// C/C++ standard libraries
#include <vector>
#include <algorithm> // std::copy()
#include <iterator> // std::inserter()



namespace filter {

  //----------------------------------------------------------------------------
  SimpleChannelFilterService::SimpleChannelFilterService
    (fhicl::ParameterSet const& pset, art::ActivityRegistry&)
  {
    SimpleChannelFilter* simple_filter = new SimpleChannelFilter(pset);
    
    raw::ChannelID_t MaxChannel
      = raw::ChannelID_t(art::ServiceHandle<geo::Geometry>()->Nchannels() - 1);
    
    simple_filter->Setup(MaxChannel);
    
    SetFilter(simple_filter);
    
    mf::LogInfo("SimpleChannelFilterService") << "Loaded from configuration:"
      << "\n  - " << GetFilter().BadChannels().size() << " bad channels"
      << "\n  - " << GetFilter().NoisyChannels().size() << " noisy channels"
      << "\n  - largest channel ID: " << simple_filter->MaxChannel()
        << ", largest present: " << simple_filter->MaxChannelPresent()
      ;
    
  } // SimpleChannelFilterService::SimpleChannelFilterService()
  
  
  //----------------------------------------------------------------------------
  DEFINE_ART_SERVICE_INTERFACE_IMPL(filter::SimpleChannelFilterService, filter::ChannelFilterServiceInterface)
  
} // namespace filter
