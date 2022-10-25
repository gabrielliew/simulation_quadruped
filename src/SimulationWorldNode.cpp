#include "SimulationWorldNode.hpp"

#include <osgShadow/ShadowMap>

SimulationWorldNode::SimulationWorldNode(
    const dart::simulation::WorldPtr &world,
    const dart::dynamics::SkeletonPtr &quadruped)
    : dart::gui::osg::RealTimeWorldNode(world), mQuadruped(quadruped),
      mExternalForce(Eigen::Vector3d::Zero()), mForceDuration(0.0),controlMode_(1) {
  assert(world);
  assert(quadruped);
  // this->setTargetRealTimeFactor(0.25);
  Eigen::VectorXd balancedPose(18);
  balancedPose << -1.570796, 0.0, 0.0, 0.0, 0.4, 0.0, 0.0, 0.6, -1.5, 0.0, 0.6,
      -1.5, 0.0, 0.6, -1.5, 0.0, 0.6, -1.5;
  mQuadruped->setPositions(balancedPose);
  mInitialState =
      mQuadruped->getConfiguration(dart::dynamics::Skeleton::CONFIG_POSITIONS |
                                   dart::dynamics::Skeleton::CONFIG_VELOCITIES);
}

void SimulationWorldNode::customPreStep() {
  auto forces = simQuadruped.update(controlMode_, this->mWorld->getTime(),
                                    mQuadruped->getPositions(),
                                    mQuadruped->getVelocities(),Eigen::Vector3d::Zero());
  // std::cout << (forces).transpose() << std::endl;

  mQuadruped->setForces(forces);
}

void SimulationWorldNode::reset() {
  this->mWorld->reset();
  mExternalForce.setZero();
  mQuadruped->setConfiguration(mInitialState);
}
