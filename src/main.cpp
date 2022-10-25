#include <dart/dart.hpp>
#include <dart/gui/osg/osg.hpp>
#include <dart/utils/urdf/DartLoader.hpp>
#include <dart/utils/utils.hpp>

#include "SimulationEventHandler.hpp"
#include "SimulationWidget.hpp"
#include "SimulationWorldNode.hpp"

int main(int argc, char *argv[]) {

  dart::utils::DartLoader loader;
  auto ground =
      loader.parseSkeleton("/home/liew/my_projects/simulation_quadruped/"
                           "resources/ground.urdf");
  ground->setName("ground");
  auto quadruped =
      loader.parseSkeleton("/home/liew/my_projects/simulation_quadruped/"
                           "resources/mini_cheetah/mini_cheetah.urdf");
  quadruped->setName("quadruped");
  
  dart::simulation::WorldPtr world =
      std::make_shared<dart::simulation::World>();
  world->setGravity(Eigen::Vector3d(0.0, -9.81, 0.0));

  if (dart::collision::CollisionDetector::getFactory()->canCreate("bullet")) {
    world->getConstraintSolver()->setCollisionDetector(
        dart::collision::CollisionDetector::getFactory()->create("bullet"));
  }

  world->addSkeleton(ground);
  world->addSkeleton(quadruped);

  osg::ref_ptr<SimulationWorldNode> node =
      new SimulationWorldNode(world, quadruped);

  osg::ref_ptr<dart::gui::osg::ImGuiViewer> viewer =
      new dart::gui::osg::ImGuiViewer();
  viewer->addWorldNode(node);

  viewer->getImGuiHandler()->addWidget(
      std::make_shared<SimulationWidget>(viewer, node));

  viewer->addEventHandler(new SimulationEventHandler(node));

  viewer->setUpViewInWindow(0, 0, 1280, 960);

  viewer->realize();
  osgViewer::Viewer::Windows windows;
  viewer->getWindows(windows);
  windows.front()->setWindowName("Quadruped Simulation");

  viewer->getCameraManipulator()->setHomePosition(
      ::osg::Vec3d(-1,2,2), ::osg::Vec3d(1.00, 0.00, 0.00),
      ::osg::Vec3d(0.00, 0.1, 0.00));

  viewer->setCameraManipulator(viewer->getCameraManipulator());

  viewer->run();
}