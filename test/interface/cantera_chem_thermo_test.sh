#!/bin/bash

PROG="${GRINS_TEST_DIR}/cantera_chem_thermo_test"

INPUT="${GRINS_TEST_INPUT_DIR}/cantera_chem_thermo.in"

${LIBMESH_RUN:-} $PROG $INPUT $PETSC_OPTIONS 