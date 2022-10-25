#include "SimulationWorldNode.hpp"

#include <osgShadow/ShadowMap>

SimulationWorldNode::SimulationWorldNode(
    const dart::simulation::WorldPtr &world,
    const dart::dynamics::SkeletonPtr &quadruped)
    : dart::gui::osg::RealTimeWorldNode(world), mQuadruped(quadruped),
      mExternalForce(Eigen::Vector3d::Zero()), mForceDuration(0.0) {
  assert(world);
  assert(quadruped);
  Eigen::VectorXd balancedPose(18);
  balancedPose << -1.570796, 0.0, 0.0, 0.0, 0.4, 0.0, 0.0, 0.6, -1.5, 0.0, 0.6,
      -1.5, 0.0, 0.6, -1.5, 0.0, 0.6, -1.5;
  mQuadruped->setPositions(balancedPose);
  mInitialState =
      mQuadruped->getConfiguration(dart::dynamics::Skeleton::CONFIG_POSITIONS |
                                   dart::dynamics::Skeleton::CONFIG_VELOCITIES);
}

void SimulationWorldNode::customPreStep() {
  mExternalForce.setZero();
  // mQuadruped->setForces();
  // Eigen::VectorXd
}

void SimulationWorldNode::reset() {
  mExternalForce.setZero();
  mQuadruped->setConfiguration(mInitialState);
}
