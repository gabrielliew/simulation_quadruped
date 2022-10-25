#ifndef INCLUDE_SIMULATIONEVENTHANDLER_HPP
#define INCLUDE_SIMULATIONEVENTHANDLER_HPP

#include <dart/dart.hpp>
#include <dart/gui/osg/osg.hpp>
#include <dart/utils/utils.hpp>

#include "SimulationWorldNode.hpp"

class SimulationEventHandler : public osgGA::GUIEventHandler
{
public:
  SimulationEventHandler(SimulationWorldNode* node);

  bool handle(
      const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&) override;

protected:
  ::osg::ref_ptr<SimulationWorldNode> mNode;
};

#endif /* INCLUDE_SIMULATIONEVENTHANDLER_HPP */
