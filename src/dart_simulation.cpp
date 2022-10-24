#include <dart/dart.hpp>
#include <dart/gui/gui.hpp>
#include <dart/utils/urdf/DartLoader.hpp>
#include <dart/utils/utils.hpp>

#include "dart_interface.hpp"
#include "dart_window.hpp"

using namespace dart::common;
using namespace dart::dynamics;
using namespace dart::simulation;
using namespace dart::gui;
using namespace dart::gui::glut;
using namespace dart::utils;
using namespace dart::math;

int main(int argc, char *argv[]) {
  dart::utils::DartLoader loader;
  SkeletonPtr floor =
      loader.parseSkeleton("/home/liew/my_projects/simulation_quadruped/"
                           "resources/ground.urdf");
  floor->setName("ground");
  SkeletonPtr quadruped =
      loader.parseSkeleton("/home/liew/my_projects/simulation_quadruped/"
                           "resources/mini_cheetah/mini_cheetah.urdf");
  quadruped->setName("quadruped");
  Eigen::VectorXd balancedPose(18);
  balancedPose << -1.570796, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  quadruped->setPositions(balancedPose);

  WorldPtr world = std::make_shared<World>();
  world->setGravity(Eigen::Vector3d(0.0, -9.81, 0.0));

  if (dart::collision::CollisionDetector::getFactory()->canCreate("bullet")) {
    world->getConstraintSolver()->setCollisionDetector(
        dart::collision::CollisionDetector::getFactory()->create("bullet"));
  }

  world->addSkeleton(floor);
  world->addSkeleton(quadruped);

  MyWindow window(world);

  // Print instructions
  std::cout << "'.': forward push" << std::endl;
  std::cout << "',': backward push" << std::endl;
  std::cout << "'s': increase skateboard forward speed" << std::endl;
  std::cout << "'a': increase skateboard backward speed" << std::endl;
  std::cout << "space bar: simulation on/off" << std::endl;
  std::cout << "'p': replay simulation" << std::endl;
  std::cout << "'v': Turn contact force visualization on/off" << std::endl;
  std::cout << "'[' and ']': replay one frame backward and forward"
            << std::endl;

  // Initialize glut, initialize the window, and begin the glut event loop
  glutInit(&argc, argv);
  window.initWindow(640, 480, "Multi-Pendulum Tutorial");
  glutMainLoop();
}