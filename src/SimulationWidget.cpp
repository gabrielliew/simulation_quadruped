#include "SimulationWidget.hpp"

#include "dart/external/imgui/imgui.h"

#include "SimulationWorldNode.hpp"

//==============================================================================
SimulationWidget::SimulationWidget(dart::gui::osg::ImGuiViewer *viewer,
                                   SimulationWorldNode *node)
    : mViewer(viewer), mNode(node), mGuiGravityAcc(9.81f),
      mGravityAcc(mGuiGravityAcc), mGuiHeadlights(true), mGuiControlMode(1),
      mControlMode(1) {
  // Do nothing
}

//==============================================================================
void SimulationWidget::render() {
  ImGui::SetNextWindowPos(ImVec2(10, 20));
  ImGui::SetNextWindowSize(ImVec2(360, 400));
  ImGui::SetNextWindowBgAlpha(0.5f);
  if (!ImGui::Begin("Atlas Control", nullptr,
                    ImGuiWindowFlags_MenuBar |
                        ImGuiWindowFlags_HorizontalScrollbar)) {
    ImGui::End();
    return;
  }

  // Menu
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("Menu")) {
      if (ImGui::MenuItem("Exit"))
        mViewer->setDone(true);
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("About DART"))
        mViewer->showAbout();
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

  ImGui::Spacing();

  if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
    int e = mViewer->isSimulating() ? 0 : 1;
    if (mViewer->isAllowingSimulation()) {
      if (ImGui::RadioButton("Play", &e, 0) && !mViewer->isSimulating())
        mViewer->simulate(true);
      ImGui::SameLine();
      if (ImGui::RadioButton("Pause", &e, 1) && mViewer->isSimulating())
        mViewer->simulate(false);
    }
  }

  if (ImGui::CollapsingHeader("World Options",
                              ImGuiTreeNodeFlags_DefaultOpen)) {

    mGuiHeadlights = mViewer->checkHeadlights();
    if (ImGui::Checkbox("Headlights On/Off", &mGuiHeadlights)) {
      mViewer->switchHeadlights(mGuiHeadlights);
    }
  }
  ImGui::Spacing();
  if (ImGui::CollapsingHeader("Options", ImGuiTreeNodeFlags_DefaultOpen)) {
    const auto reset = ImGui::Button("Reset");
    if (reset)
      mNode->reset();

    ImGui::Spacing();
  }
  ImGui::RadioButton("No Control", &mGuiControlMode, 0);
  ImGui::RadioButton("PD control", &mGuiControlMode, 1);
  ImGui::RadioButton("MPC control", &mGuiControlMode, 2);

  if (mGuiControlMode != mControlMode) {
    switch (mGuiControlMode) {
    case 0:
      mNode->switchControlMode(0);
      break;
    case 1:
      mNode->switchControlMode(1);
      break;
    case 2:
      mNode->switchControlMode(2);
      break;
    }

    mControlMode = mGuiControlMode;
  }
  ImGui::End();
}
