#include "toolbox/toolbox.hpp"

#include "toolbox/envpanel.hpp"
#include "toolbox/terrpanel.hpp"
#include "toolbox/roadpanel.hpp"
#include "editor.hpp"


ToolBox* ToolBox::m_toolbox = 0;

// ----------------------------------------------------------------------------
void ToolBox::init()
{
    IGUIEnvironment* gui_env = Editor::getEditor()->getGUIEnv();

    m_wndw = gui_env->addWindow(
            rect<s32>(),
            false, L"Stuffs", 0, TBOX_ID);
    initWndw(m_wndw);
    dimension2du ss = Editor::getEditor()->getScreenSize();
    m_wndw->setRelativePosition(position2di(ss.Width - 250, 50));

    m_terr_wndw = gui_env->addWindow(rect<s32>(), false, L"Terrain", m_wndw, TWND_ID);
    m_terr_panel = TerrPanel::getTerrPanel(m_terr_wndw);
    initWndw(m_terr_wndw);

    m_env_wndw = gui_env->addWindow(rect<s32>(), false, L"Env", m_wndw, EWND_ID);
    m_env_panel = EnvPanel::getEnvPanel(m_env_wndw);
    initWndw(m_env_wndw);    
    m_env_wndw->setVisible(false);

    m_road_wndw = gui_env->addWindow(rect<s32>(), false, L"Road", m_wndw, RWND_ID);
    m_road_panel = RoadPanel::getRoadPanel(m_road_wndw);
    initWndw(m_road_wndw);
    m_road_wndw->setVisible(false);

    gui_env->addButton(rect<s32>(0, 0, 50, 50), m_wndw,   TWND_ID);
    gui_env->addButton(rect<s32>(50, 0, 100, 50), m_wndw, EWND_ID);
    gui_env->addButton(rect<s32>(100, 0, 150, 50), m_wndw, RWND_ID);

} // init

void ToolBox::initWndw(IGUIWindow* wndw)
{
    dimension2du ss = Editor::getEditor()->getScreenSize();
    wndw->setMinSize(dimension2du(250, ss.Height - 50));
    wndw->setDraggable(false);
    wndw->getCloseButton()->setVisible(false);
    wndw->setDrawTitlebar(false);
}

// ----------------------------------------------------------------------------
ToolBox* ToolBox::getToolBox()
{
    if (m_toolbox != 0) return m_toolbox;

    m_toolbox = new ToolBox();
    m_toolbox->init();
    return m_toolbox;
} // getToolBox

// ----------------------------------------------------------------------------
void ToolBox::reallocate()
{
    dimension2du ss = Editor::getEditor()->getScreenSize();

    m_wndw->setMinSize(dimension2du(250, ss.Height-50));
    m_wndw->setRelativePosition(position2di(ss.Width-250,50));

    m_env_panel->reallocate(ss);

} // reallocate

// ----------------------------------------------------------------------------
void ToolBox::setWndw(int ID)
{
    m_terr_wndw->setVisible(false);
    m_env_wndw->setVisible(false);
    m_road_wndw->setVisible(false);
    switch(ID)
    {
    case TWND_ID:
        m_terr_wndw->setVisible(true);
        break;
    case EWND_ID:
        m_env_wndw->setVisible(true);
        break;
    case RWND_ID:
        m_road_wndw->setVisible(true);
        break;
    default:
        break;
    }
}
