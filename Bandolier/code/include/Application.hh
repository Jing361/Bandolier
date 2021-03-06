#ifndef TEST_APPLICATION_HH
#define TEST_APPLICATION_HH

#include <memory>

#include <event_handler.hh>

#include <layer_stack.hh>
#include <ApplicationEvent.hh>
#include <Window.hh>

namespace Bandolier {

class Application;
// To be defined by the client
Application& CreateApplication();

class Application
{
protected:
  friend Application& Bandolier::CreateApplication();
  inline static Application* Instance = nullptr;

  std::unique_ptr<Bandolier::Window> mWindow;
  bool mRunning = false;
  LayerStack mLayerStack;

public:
  Application();
  virtual ~Application();

  virtual void
  run() = 0;

  Bandolier::Window&
  Window()
  {
    return *mWindow;
  }

  const Bandolier::Window&
  Window() const
  {
    return *mWindow;
  }

  //Using a static app instance allows the application to be accessed using only this base class,
  // and without knowledge of the client's implimentation.
  static Application&
  Get()
  {
    return *Instance;
  }

  virtual void
  PushLayer(LayerStack::value_type layer);
  virtual void
  PushOverlay(LayerStack::value_type overlay);
};

}

#endif //TEST_APPLICATION_HH
