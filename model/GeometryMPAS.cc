/*
 * (C) Copyright 2017 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "oops/util/Logger.h"
#include "model/GeometryMPAS.h"
#include "Fortran.h"
#include "eckit/config/Configuration.h"

// -----------------------------------------------------------------------------
namespace mpas {
// -----------------------------------------------------------------------------
GeometryMPAS::GeometryMPAS(const eckit::Configuration & config,
                           const eckit::mpi::Comm & comm) : comm_(comm) {
  oops::Log::trace() << "========= GeometryMPAS::GeometryMPAS step 1 =========="
                     << std::endl;
  mpas_geo_setup_f90(keyGeom_, config);
  oops::Log::trace() << "========= GeometryMPAS::GeometryMPAS step 2 =========="
                     << std::endl;
}
// -----------------------------------------------------------------------------
GeometryMPAS::GeometryMPAS(const GeometryMPAS & other) : comm_(other.comm_) {
  const int key_geo = other.keyGeom_;
  oops::Log::trace() << "========= GeometryMPAS mpas_geo_clone_f90   =========="
                     << std::endl;
  mpas_geo_clone_f90(key_geo, keyGeom_);
}
// -----------------------------------------------------------------------------
GeometryMPAS::~GeometryMPAS() {
  mpas_geo_delete_f90(keyGeom_);
}
// -----------------------------------------------------------------------------
void GeometryMPAS::print(std::ostream & os) const {
  int nCellsGlobal;
  int nCells;
  int nCellsSolve;
  int nEdgesGlobal;
  int nEdges;
  int nEdgesSolve;
  int nVertLevels;
  int nVertLevelsP1;
  mpas_geo_info_f90(keyGeom_, nCellsGlobal, nCells, nCellsSolve, \
                              nEdgesGlobal, nEdges, nEdgesSolve, \
                              nVertLevels, nVertLevelsP1);

  os << ", nCellsGlobal = " << nCellsGlobal \
     << ", nCells = " << nCells \
     << ", nCellsSolve = " << nCellsSolve \
     << ", nEdgesGlobal = " << nEdgesGlobal \
     << ", nEdges = " << nEdges \
     << ", nEdgesSolve = " << nEdgesSolve \
     << ", nVertLevels = " <<nVertLevels \
     << ", nVertLevelsP1 = " <<nVertLevelsP1
     << ", communicator = " << this->getComm().name();
}
// -----------------------------------------------------------------------------
}  // namespace mpas
