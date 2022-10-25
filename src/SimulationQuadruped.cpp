#include "SimulationQuadruped.hpp"
#include <iostream>

SimulationQuadruped::SimulationQuadruped() {
  /*
   *leg is in fl,fr,hl,hr
   *the library axes are x=forward, y=left, z=up
   *dartsim axes are x=forward, y=up, z=right
   * need to convert correctly in world node
   */

  convexMPC = ConvexMPC(10, 0.025, -9.8, 4);
  std::vector<Eigen::Vector3d> hipLocations(4);
  hipLocations[0] = Eigen::Vector3d(0.19, 0.049, 0);
  hipLocations[1] = Eigen::Vector3d(0.19, -0.049, 0);
  hipLocations[2] = Eigen::Vector3d(-0.19, 0.049, 0);
  hipLocations[3] = Eigen::Vector3d(-0.19, -0.049, 0);
  std::vector<int> offset = {0, 5, 5, 0};
  footPlanner = FootPlanner(4, hipLocations, 0.125, 0.125, 0.002);
  gait = Gait(4, 10, 0.025, 0.0125, offset);
  std::vector<int> side = {1, -1, 1, -1};
  for (int i = 0; i < 4; i++) {
    legController[i] =
        LegController(side[i], 0.062, 0.209, 0.195, hipLocations[i]);
  }

  std::cout << "declare quadruped" << std::endl;
}


Eigen::VectorXd SimulationQuadruped::update(int mode, double timePassed,
                                            Eigen::VectorXd positions,
                                            Eigen::VectorXd velocities,
                                            Eigen::Vector3d desiredVelocity) {
  Eigen::VectorXd forces(18);
  forces.setZero();
  jointAngle = positions.block(6, 0, 12, 1);
  jointVelocity = velocities.block(6, 0, 12, 1);
  for (int i = 0; i < 4; i++) {
    legController[i].updateQ(jointAngle.block<3, 1>(i * 3, 0));
    legController[i].updateQD(jointVelocity.block<3, 1>(i * 3, 0));
  }
  MPCdata currentState;
  currentState.position =
      Eigen::Vector3d(positions[3], -positions[5], positions[4]);
  currentState.linear_velocity =
      Eigen::Vector3d(velocities[3], -velocities[5], velocities[4]);
  currentState.rotation =
      Eigen::Vector3d(positions[0], -positions[2], positions[1]);
  currentState.rotation_velocity =
      Eigen::Vector3d(velocities[0], -velocities[2], velocities[1]);
  if (mode == 1) {
    legJointCommand jointCMD;
    jointCMD.feedForwardTorque = Eigen::Vector3d::Zero();
    jointCMD.qDesired = Eigen::Vector3d(0, 0.6, -1.5);
    jointCMD.qdDesired = Eigen::Vector3d::Zero();
    jointCMD.kP << 80, 0, 0, 0, 80, 0, 0, 0, 80;
    jointCMD.kd << 1, 0, 0, 0, 1, 0, 0, 0, 1;
    for (int i = 0; i < 4; i++) {
        forces.block(i * 3 + 6, 0, 3, 1) =
        legController[i].getTorque(jointCMD);
      }
  }

  return forces;
}