#ifndef INCLUDE_DART_WINDOW_HPP
#define INCLUDE_DART_WINDOW_HPP

#include <dart/dart.hpp>
#include <dart/gui/gui.hpp>
#include <dart/utils/urdf/DartLoader.hpp>
#include <dart/utils/utils.hpp>

using namespace dart::common;
using namespace dart::dynamics;
using namespace dart::simulation;
using namespace dart::gui;
using namespace dart::gui::glut;
using namespace dart::utils;
using namespace dart::math;

const int default_countdown = 100; // Number of timesteps for applying force

class MyWindow : public SimWindow {
public:
  /// Constructor
  MyWindow(const WorldPtr &world) : mForceCountDown(0), mPositiveSign(true) {
    setWorld(world);

    mController =
        std::make_unique<DartInterface>(mWorld->getSkeleton("quadruped"));
  }

  /// Handle keyboard input
  void keyboard(unsigned char key, int x, int y) override {
    switch (key) {
    case ',':
      mForceCountDown = default_countdown;
      mPositiveSign = false;
      break;
    case '.':
      mForceCountDown = default_countdown;
      mPositiveSign = true;
      break;
    case 'a':
      //   mController->changeWheelSpeed(default_speed_increment);
      break;
    case 's':
      //   mController->changeWheelSpeed(-default_speed_increment);
      break;
    default:
      SimWindow::keyboard(key, x, y);
    }
  }

  void timeStepping() override {
    mController->clearForces();
    auto positions = mWorld->getSkeleton("quadruped")->getPositions();
    // std::cout<<positions<<std::endl;

    SimWindow::timeStepping();
  }

protected:
  std::unique_ptr<DartInterface> mController;

  /// Number of iterations before clearing a force entry
  int mForceCountDown;

  /// Whether a force should be applied in the positive or negative direction
  bool mPositiveSign;
};

#endif /* INCLUDE_DART_WINDOW_HPP */
