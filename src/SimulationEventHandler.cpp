#include "SimulationEventHandler.hpp"

//==============================================================================
SimulationEventHandler::SimulationEventHandler(
    SimulationWorldNode* node)
  : mNode(node)
{
  // Do nothing
}

//==============================================================================
bool SimulationEventHandler::handle(
    const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&)
{
  if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
  {
    if (ea.getKey() == 'r' || ea.getKey() == 'R')
    {
      mNode->reset();
      return true;
    }
    else if (ea.getKey() == 'a' || ea.getKey() == 'A')
    {
      return true;
    }
    else if (ea.getKey() == 's' || ea.getKey() == 'S')
    {
      return true;
    }
    else if (ea.getKey() == 'd' || ea.getKey() == 'D')
    {
      return true;
    }
    else if (ea.getKey() == 'f' || ea.getKey() == 'F')
    {
      return true;
    }
  }

  return false;
}