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


#ifndef GRINS_INTEGRATED_FUNCTION_H
#define GRINS_INTEGRATED_FUNCTION_H

// libMesh
#include "libmesh/quadrature.h"
#include "libmesh/exact_solution.h"

// GRINS
#include "grins/qoi_base.h"
#include "grins/variable_name_defaults.h"
#include "grins/rayfire_mesh.h"
#include "grins/fem_function_and_derivative_base.h"

namespace GRINS
{

  //! IntegratedFunction
  /*!
    The purpose of this class is to integrate a function along a 1D line through a 2D mesh.
    This class utilizes the RayfireMesh class to calculate the line and provide 1D elements for evaluating
    the function.

    The template parameter must be FunctionBase or FEMFunctionBase.

    Currently, calculating element qoi derivatives is not supported.
  */
  template<typename Function>
  class IntegratedFunction : public QoIBase
  {
  public:
    //! Constructor
    /*!
      @param p_level The desired Gauss Quadrature level
      @param f A FunctionBase or FEMFunctionBase object for evaluting the QoI
      @param rayfire A RayfireMesh object (will be initialized in init())
      @param qoi_name Passed to the QoIBase
    */
    IntegratedFunction(unsigned int p_level, const std::shared_ptr<Function> & f, const std::shared_ptr<RayfireMesh> & rayfire, const std::string & qoi_name);

    //! Required to provide clone (deep-copy) for adding QoI object to libMesh objects.
    virtual QoIBase* clone() const override;

    virtual bool assemble_on_interior() const override;

    virtual bool assemble_on_sides() const override;

    //! Compute the qoi value.
    virtual void element_qoi( AssemblyContext & context,
                              const unsigned int qoi_index ) override;

    //! Compute the qoi derivative with respect to the solution.
    virtual void element_qoi_derivative( AssemblyContext & context,
                                         const unsigned int qoi_index ) override;

    //! Initializes the rayfire with the mesh from system
    virtual void init( const GetPot & input,
                       const MultiphysicsSystem & system,
                       unsigned int qoi_num ) override;

    //! Reinitialize the rayfire
    virtual void reinit(MultiphysicsSystem & system) override;

    const RayfireMesh & get_rayfire()
    {
      return *(_rayfire.get());
    }

    Function & get_function()
    {
      return *(_f.get());
    }

    const Function & get_function() const
    {
      return *(_f.get());
    }

  private:
    //! Quadrature order
    unsigned int _p_level;

    //! Pointer to the template class used for function evaluation
    std::shared_ptr<Function> _f;

    //! Pointer to RayfireMesh object
    std::shared_ptr<RayfireMesh> _rayfire;

    //! Compute the value of a QoI at a QP
    libMesh::Real qoi_value(Function & f, AssemblyContext & context, const libMesh::Point & xyz);

    //! Compute derivatiuves at QP
    void qoi_derivative(Function & f, AssemblyContext & context, const libMesh::Point & qp_xyz,
                        const libMesh::Real JxW, const unsigned int qoi_index);

  protected:
    //! Cache a non-const pointer to the MultiphysicsSystem object
    MultiphysicsSystem * _multiphysics_system;

  };

  template<typename Function>
  inline
  bool IntegratedFunction<Function>::assemble_on_interior() const
  {
    return true;
  }

  template<typename Function>
  inline
  bool IntegratedFunction<Function>::assemble_on_sides() const
  {
    return false;
  }
}
#endif //GRINS_INTEGRATED_FUNCTION_H
