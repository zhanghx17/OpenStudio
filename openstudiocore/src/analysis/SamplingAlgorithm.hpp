/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#ifndef ANALYSIS_SAMPLINGALGORITHM_HPP
#define ANALYSIS_SAMPLINGALGORITHM_HPP

#include "AnalysisAPI.hpp"
#include "DakotaAlgorithm.hpp"

namespace openstudio {
namespace analysis {

class SamplingAlgorithmOptions;

namespace detail {

  class SamplingAlgorithm_Impl;

} // detail

/** SamplingAlgorithm is a DakotaAlgorithm that implements dakotaInFileDescription so as to specify
 *  a particular Sampling method and related options. The purpose of SamplingAlgorithm is not so 
 *  much to provide sampling algorithms (the sampling algorithms available are also available in 
 *  DDACE), but to enable proper sampling from a number of \link UncertaintyDescription 
 *  UncertaintyDescriptions\endlink. */
class ANALYSIS_API SamplingAlgorithm : public DakotaAlgorithm {
 public:
  /** @name Constructors and Destructors */
  //@{

  /** Construct from options. */
  explicit SamplingAlgorithm(const SamplingAlgorithmOptions& options);

  /** Constructor provided for deserialization; not for general use. */
  SamplingAlgorithm(const UUID& uuid,
                    const UUID& versionUUID,
                    const std::string& displayName,
                    const std::string& description,
                    bool complete,
                    bool failed,
                    int iter,
                    const SamplingAlgorithmOptions& options,
                    const boost::optional<FileReference>& restartFileReference,
                    const boost::optional<FileReference>& outFileReference,
                    const boost::optional<openstudio::runmanager::Job>& job);

  virtual ~SamplingAlgorithm() {}

  //@}

  /** @name Getters and Queries */
  //@{

  SamplingAlgorithmOptions samplingAlgorithmOptions() const;

  //@}
 protected:
  /// @cond
  typedef detail::SamplingAlgorithm_Impl ImplType;

  explicit SamplingAlgorithm(std::shared_ptr<detail::SamplingAlgorithm_Impl> impl);

  friend class detail::SamplingAlgorithm_Impl;
  friend class AnalysisObject;
  friend class detail::AnalysisObject_Impl;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.analysis.SamplingAlgorithm");
};

/** \relates SamplingAlgorithm*/
typedef boost::optional<SamplingAlgorithm> OptionalSamplingAlgorithm;

/** \relates SamplingAlgorithm*/
typedef std::vector<SamplingAlgorithm> SamplingAlgorithmVector;

} // analysis
} // openstudio

#endif // ANALYSIS_SAMPLINGALGORITHM_HPP

