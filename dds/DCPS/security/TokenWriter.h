/*
*
*
* Distributed under the DDS License.
* See: http://www.DDS.org/license.html
*/



#ifndef DDS_DCPS_TOKEN_WRITER_IMPL_H
#define DDS_DCPS_TOKEN_WRITER_IMPL_H

#include "dds/DCPS/security/DdsSecurity_Export.h"

#include "dds/DdsSecurityCoreC.h"
#include "dds/Versioned_Namespace.h"
#include "dds/DCPS/iterator_adaptor.h"

#include "TokenReader.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class DDS_TEST;

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL

namespace OpenDDS {
namespace Security {

/**
* @class TokenWriter
*
* @brief Implements some simple wrapper functions to provide a non-const API
* around the Token data structure as specified in the DDS security specification
*
* See the DDS security specification, OMG formal/17-09-20, for a description of
* the interface this class is implementing.
*
*/

class DdsSecurity_Export TokenWriter
{
public:
  TokenWriter(DDS::Security::Token& token_ref);
  TokenWriter(DDS::Security::Token& token_ref, const std::string& class_id);

  virtual ~TokenWriter();

  const TokenReader& get_reader();

  void set_class_id(const std::string& class_name);

  void add_property(const char* prop_name, const char* prop_value, bool propagate = true);
  void add_property(const char* prop_name, const DDS::OctetSeq& prop_value, bool propagate = true);
  void add_bin_property(const char* prop_name, const DDS::OctetSeq& prop_value, bool propagate = true);
  void add_bin_property(const char* prop_name, const std::string& prop_value, bool propagate = true);

private:
  DCPS::sequence_back_insert_iterator<DDS::BinaryPropertySeq> binary_property_inserter_;
  DCPS::sequence_back_insert_iterator<DDS::PropertySeq> property_inserter_;
  DDS::Security::Token& token_ref_;
  OpenDDS::Security::TokenReader reader_;
};

inline const TokenReader& TokenWriter::get_reader()
{
  return reader_;
}

inline void TokenWriter::set_class_id(const std::string& class_id)
{
  token_ref_.class_id = class_id.c_str();
}


} // namespace Security
} // namespace OpenDDS

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL

#endif
