#ifndef INCLUDE_SIMULATIONWIDGET_HPP
#define INCLUDE_SIMULATIONWIDGET_HPP

#include <dart/gui/osg/ImGuiViewer.hpp>
#include <dart/gui/osg/ImGuiWidget.hpp>

class SimulationWorldNode;

class SimulationWidget : public dart::gui::osg::ImGuiWidget
{
public:
  /// Constructor
  SimulationWidget(
      dart::gui::osg::ImGuiViewer* viewer, SimulationWorldNode* node);

  // Documentation inherited
  void render() override;

protected:
  void setGravity(float gravity);

  ::osg::ref_ptr<dart::gui::osg::ImGuiViewer> mViewer;

  ::osg::ref_ptr<SimulationWorldNode> mNode;

  float mGuiGravityAcc;

  float mGravityAcc;

  bool mGuiHeadlights;

  /// Control mode value for GUI
  int mGuiControlMode;

  /// Actual control mode
  ///   - 0: No control
  ///   - 1: Short-stride walking control
  ///   - 1: Normal-stride walking control
  int mControlMode;
};


#endif /* INCLUDE_SIMULATIONWIDGET_HPP */
