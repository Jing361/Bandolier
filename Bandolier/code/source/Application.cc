#include <GLFW/glfw3.h>

#include "platform/Windows/windows_window.hh"
#include "logger.hh"

#include "Application.hh"

namespace Bandolier{

Application::Application()
  : mWindow(std::make_unique<WindowsWindow>(WindowProperties("test", 1280, 720)))
{
  if(Application::AppInstance)
  {
    logging::core()->error("Initializing a new application when one already exists!");
    throw std::runtime_error("Initializing a new application when one already exists!");
  }
  Application::AppInstance = this;

  mWindow->CloseChannel().lock()->subscribe(
    [this](const Events::WindowClose&)
    {
      mRunning = false;
      Bandolier::logging::client()->trace("Window close event occurred!");
    }
  );

  mWindow->AllChannel().lock()->subscribe(
    [this](const Events::BaseEvent& e)
    {
      logging::client()->trace("{0}", e.Name());
      for(auto& layer : mLayerStack)
      {
        if(layer->OnEvent(e))
          break;
      }
    }
  );
}

Application::~Application()
{
}

void
Application::PushLayer(LayerStack::value_type layer)
{
  mLayerStack.PushLayer(std::move(layer));
}

void
Application::PushOverlay(Bandolier::LayerStack::value_type overlay)
{
  mLayerStack.PushOverlay(std::move(overlay));
}

}