//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// GRINS - General Reacting Incompressible Navier-Stokes
//
// Copyright (C) 2014-2015 Paul T. Bauman, Roy H. Stogner
// Copyright (C) 2010-2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-

#ifndef GRINS_DEFAULT_VARIABLE_BUILDER_H
#define GRINS_DEFAULT_VARIABLE_BUILDER_H

// GRINS
#include "grins/variable_builder.h"
#include "grins/builder_helper.h"

// libMesh
#include "libmesh/getpot.h"

namespace GRINS
{
  class DefaultVariableBuilder : public VariableBuilder,
                                 public BuilderHelper
  {
  public:
    DefaultVariableBuilder(){}
    ~DefaultVariableBuilder(){}

    virtual void build_variables_impl( const GetPot& input,
                                       MultiphysicsSystem& system );

  protected:

    //! Parse [Variable/<var_section>/names]
    void parse_var_names( const GetPot& input,
                          const std::string& var_type,
                          const std::string& var_section,
                          std::vector<std::string>& var_names ) const;

    //! Helper function to extract [Varaiable/<var_section>/fe_family] from input
    std::string parse_fe_family( const GetPot& input, const std::string& var_section ) const
    { return this->parse_var_option(input,var_section,std::string("fe_family"),std::string("DIE!")); }

    //! Helper function to extract [Varaiable/<var_section>/order] from input
    std::string parse_fe_order( const GetPot& input, const std::string& var_section ) const
    { return this->parse_var_option(input,var_section,std::string("order"),std::string("DIE!")); }

    //! Parses the [Variable/<var_section>/var_type] option
    /*! The var_type is how we distinguish between the Variables so that
        the user can name the section whatever they want. If var_type
        is not present, then we assume that the var_type is actually the
        the section name, var_section. */
    std::string parse_var_type( const GetPot& input,
                                const std::string& var_section ) const
    { std::string input_sec = VariablesParsing::variables_section()+"/"+var_section+"/type";
      return input(input_sec,var_section); }

    //! Helper function to reduce code duplication
    std::string parse_var_option( const GetPot& input,
                                  const std::string& var_section,
                                  const std::string& option,
                                  const std::string& default_val ) const;


  };
} // end namespace GRINS

#endif // GRINS_DEFAULT_VARIABLE_BUILDER_H
