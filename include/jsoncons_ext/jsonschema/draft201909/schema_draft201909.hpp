// Copyright 2013-2023 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSONSCHEMA_SCHEMA_DRAFT201909_HPP
#define JSONCONS_JSONSCHEMA_SCHEMA_DRAFT201909_HPP

#include <jsoncons/json.hpp>

namespace jsoncons {
namespace jsonschema {
namespace draft7 {
    
    template <class Json>
    struct schema_draft201909
    {
        static Json get_schema() 
        {
            static Json schema = Json::parse(R"(
    {
    } 
            )"); 

            return schema;
        }
    };

} // namespace draft201909
} // namespace jsonschema
} // namespace jsoncons

#endif // JSONCONS_JSONSCHEMA_SCHEMA_DRAFT201909_HPP
