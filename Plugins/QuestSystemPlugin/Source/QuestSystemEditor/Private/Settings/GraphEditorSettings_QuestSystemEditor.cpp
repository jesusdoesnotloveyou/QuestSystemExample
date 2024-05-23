// Quest System by JDNLY. All Rights Reserved

#include "QuestSystemGraphAssetEditor/GraphEditorSettings_QuestSystemEditor.h"

UGraphEditorSettings_QuestSystemEditor::UGraphEditorSettings_QuestSystemEditor()
{
    AutoLayoutStrategy = EAutoLayoutStrategy::Tree;
    bFirstPassOnly = false;
    bRandomInit = false;
    OptimalDistance = 100.f;
    MaxIteration = 50;
    InitTemperature = 10.f;
    CoolDownRate = 10.f;
}

UGraphEditorSettings_QuestSystemEditor::~UGraphEditorSettings_QuestSystemEditor()
{
    
}

