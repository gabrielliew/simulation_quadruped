#ifndef INCLUDE_DART_INTERFACE_HPP
#define INCLUDE_DART_INTERFACE_HPP

#include <dart/dart.hpp>
#include <dart/utils/utils.hpp>

using namespace dart::common;
using namespace dart::dynamics;
using namespace dart::simulation;
using namespace dart::gui;
using namespace dart::gui::glut;
using namespace dart::utils;
using namespace dart::math;

class DartInterface {
public:
  /// Constructor
  DartInterface(const SkeletonPtr &quadruped) : mQuadruped(quadruped) {
    mForces = Eigen::VectorXd::Zero(mQuadruped->getNumDofs());
  }

  void clearForces() { mForces.setZero(); }

protected:
  SkeletonPtr mQuadruped;

  Eigen::VectorXd mForces;
};

#endif /* INCLUDE_DART_INTERFACE_HPP */
