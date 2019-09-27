#include "layer_stack.hh"

namespace Bandolier {

LayerStack::LayerStack()
  : mSplitIndex(0)
{}

void
LayerStack::PushLayer(value_type layer)
{
  mLayers.emplace(mLayers.begin() + mSplitIndex, layer);
  ++mSplitIndex;
  layer->OnAttach();
}

void
LayerStack::PopLayer()
{
  (*(mLayers.begin() + mSplitIndex))->OnDetach();
  mLayers.erase(mLayers.begin() + mSplitIndex);
  --mSplitIndex;
}

void
LayerStack::EraseLayer(value_type layer)
{
  auto it = std::find(mLayers.begin(), mLayers.begin() + mSplitIndex, layer);
  if(it != mLayers.begin() + mSplitIndex)
  {
    mLayers.erase(it);
  }
  layer->OnDetach();
}

void
LayerStack::PushOverlay(value_type overlay)
{
  mLayers.emplace_back(overlay);
  overlay->OnDetach();
}

void
LayerStack::PopOverlay()
{
  auto overlay = mLayers.back();
  mLayers.pop_back();
  overlay->OnDetach();
}

void
LayerStack::EraseOverlay(value_type overlay)
{
  auto it = std::find(mLayers.begin() + mSplitIndex, mLayers.end(), overlay);
  if(it != mLayers.end())
  {
    mLayers.erase(it);
  }
  overlay->OnDetach();
}

}