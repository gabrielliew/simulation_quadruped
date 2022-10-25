#ifndef INCLUDE_SIMULATIONWORLDNODE_HPP
#define INCLUDE_SIMULATIONWORLDNODE_HPP

#include "SimulationQuadruped.hpp"
#include <dart/dart.hpp>
#include <dart/gui/osg/osg.hpp>
#include <dart/utils/utils.hpp>

class SimulationWorldNode : public dart::gui::osg::RealTimeWorldNode {
public:
  SimulationWorldNode(const dart::simulation::WorldPtr &world,
                      const dart::dynamics::SkeletonPtr &quadruped);

  void customPreStep() override;
  void switchControlMode(int controlMode) { controlMode_ = controlMode; };
  void reset();

protected:
  dart::dynamics::SkeletonPtr mQuadruped;
  dart::dynamics::Skeleton::Configuration mInitialState;
  Eigen::Vector3d mExternalForce;
  int mForceDuration;
  int controlMode_;
  SimulationQuadruped simQuadruped;
};

#endif /* INCLUDE_SIMULATIONWORLDNODE_HPP */
