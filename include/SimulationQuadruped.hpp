#ifndef INCLUDE_SIMULATIONQUADRUPED_HPP
#define INCLUDE_SIMULATIONQUADRUPED_HPP

#include <array>
#include <quadruped_control_library/convexMPC.hpp>
#include <quadruped_control_library/fixedFootPlanner.hpp>
#include <quadruped_control_library/fixedFootTrajectory.hpp>
#include <quadruped_control_library/fixedGait.hpp>
#include <quadruped_control_library/legController.hpp>

using namespace QuadrupedLeg;
using namespace FixedGait;
using namespace FixedFootPlanner;
using namespace FixedFootTrajectory;

class SimulationQuadruped {
public:
  SimulationQuadruped();
  Eigen::VectorXd update(int mode,double timePassed, Eigen::VectorXd positions,
                         Eigen::VectorXd velocities,
                         Eigen::Vector3d desiredVelocity);

private:
  ConvexMPC convexMPC;
  FootPlanner footPlanner;
  Gait gait;
  std::array<LegController, 4> legController;
  std::array<FootTrajectory, 4> footTrajectory;
  Eigen::Vector3d bodyPosition;
  Eigen::Vector3d bodyVelocity;
  Eigen::Vector3d bodyAngle;
  Eigen::Vector3d bodyAngularVelocity;
  Eigen::VectorXd jointAngle;
  Eigen::VectorXd jointVelocity;
};

#endif /* INCLUDE_SIMULATIONQUADRUPED_HPP */
