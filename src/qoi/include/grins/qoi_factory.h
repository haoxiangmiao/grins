//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// GRINS - General Reacting Incompressible Navier-Stokes
//
// Copyright (C) 2014-2019 Paul T. Bauman, Roy H. Stogner
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

#ifndef QOI_FACTORY_H
#define QOI_FACTORY_H

//libMesh
#include "libmesh/getpot.h"

//GRINS
#include "grins/composite_qoi.h"
#include "grins/rayfire_mesh.h"
#include "grins/fem_function_and_derivative_base.h"

// shared_ptr
#include <memory>

namespace GRINS
{
  class QoIFactory
  {
  public:

    QoIFactory() = default;

    virtual ~QoIFactory() = default;

    virtual std::shared_ptr<CompositeQoI> build(const GetPot& input);

  protected:

    virtual void add_qoi( const GetPot& input,
                          const std::string& qoi_name,
                          std::shared_ptr<CompositeQoI>& qois );

    virtual void check_qoi_physics_consistency( const GetPot& input,
                                                const std::string& qoi_name );

    virtual void echo_qoi_list( std::shared_ptr<CompositeQoI>& qois );

    void consistency_helper( const std::set<std::string>& requested_physics,
                             const std::set<std::string>& required_physics,
                             const std::string& qoi_name );

    void consistency_error_msg( const std::string& qoi_name, const std::set<std::string>& required_physics );

  private:
    //! Helper function to read a required value from the input file, or error if value is missing
    template<typename T>
    void get_var_value( const GetPot & input, T & value, std::string input_var, T default_value);

    //! Helper function to reduce code duplication in SpectroscopicTransmission and SpectroscopicAbsorption creation
    bool create_spectroscopic_qoi(const GetPot & input, const std::string & qoi_name, const std::string & qoi_string, QoIBase ** qoi, std::shared_ptr<CompositeQoI> & qois);

    //! Helper function to encapsulate the creation of an AbsorptionCoeff object
    std::shared_ptr<FEMFunctionAndDerivativeBase<libMesh::Real>> create_absorption_coeff(const GetPot & input, const std::string & qoi_string);
  };
}
#endif // QOI_FACTORY_H
