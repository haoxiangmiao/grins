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


#ifndef GRINS_PARSED_BOUNDARY_QOI_H
#define GRINS_PARSED_BOUNDARY_QOI_H

// GRINS
#include "grins/qoi_base.h"
#include "grins/variable_name_defaults.h"

// libMesh
#include "libmesh/fem_function_base.h"
#include "libmesh/auto_ptr.h"

namespace GRINS
{
  //! Parsed Boundary QoI
  /*!
    This class implements a QoI that is an arbitrary integral of a
    parsed function on the boundary of the domain.
  */
  class ParsedBoundaryQoI : public QoIBase
  {
  public:

    using QoIBase::QoIBase;

    virtual ~ParsedBoundaryQoI() = default;

    //! Required to provide clone (deep-copy) for adding QoI object to libMesh objects.
    virtual QoIBase* clone() const override;

    virtual bool assemble_on_interior() const override;

    virtual bool assemble_on_sides() const override;

    //! Initialize local variables
    virtual void init( const GetPot& input,
                       const MultiphysicsSystem& system,
                       unsigned int qoi_num ) override;

    virtual void init_context( AssemblyContext& context ) override;

    //! Compute the qoi value.
    virtual void side_qoi( AssemblyContext& context,
                           const unsigned int qoi_index ) override;

    //! Compute the qoi derivative with respect to the solution.
    virtual void side_qoi_derivative( AssemblyContext& context,
                                      const unsigned int qoi_index ) override;

  protected:

    std::unique_ptr<libMesh::FEMFunctionBase<libMesh::Number> >
    qoi_functional;


    //! List of boundary ids on which we want to compute this QoI
    std::set<libMesh::boundary_id_type> _bc_ids;

    //! Manual copy constructor due to the UniquePtr
    ParsedBoundaryQoI(const ParsedBoundaryQoI& original);

  };

  inline
  bool ParsedBoundaryQoI::assemble_on_interior() const
  {
    return false;
  }

  inline
  bool ParsedBoundaryQoI::assemble_on_sides() const
  {
    return true;
  }
}
#endif //GRINS_PARSED_BOUNDARY_QOI_H
