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
  
  int mGuiControlMode;

  int mControlMode;
};


#endif /* INCLUDE_SIMULATIONWIDGET_HPP */
