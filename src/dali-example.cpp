/*
 * Copyright (c) 2024 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// EXTERNAL INCLUDES
#include <dali-toolkit/dali-toolkit.h>
#include <dali/devel-api/adaptor-framework/window-devel.h>

using namespace Dali;
using namespace Dali::Toolkit;

namespace {
const char *const
    STYLE_PATH(DEMO_STYLE_DIR
               "dali-example.json"); ///< The style used for this example
const char *const
    BACKGROUND_STYLE_NAME("Background"); ///< The name of the Background style
const char *const
    IMAGE_STYLE_NAME("StyledImage"); ///< The name of the styled image style
const char *const IMAGE_PATH(DEMO_IMAGE_DIR
                             "silhouette.jpg"); ///< Image to show
} // unnamed namespace

/// Basic DALi Example to use for debugging small programs on target
class Example : public ConnectionTracker {
public:
  ///< Constructor
  Example(Application &application) : mApplication(application) {
    mApplication.InitSignal().Connect(this, &Example::Create);
  }

  ~Example() = default;

private:
  ///< Called to initialise the application UI
  void Create(Application &application) {
    // Get a handle to the main window & respond to key events
    Window window = application.GetWindow();
    window.KeyEventSignal().Connect(this, &Example::OnKeyEvent);

    // Create the background using the style sheet
    Control control = Control::New();
    control.SetStyleName(BACKGROUND_STYLE_NAME);
    window.Add(control);

    // Create an ImageView and add it to the window
    ImageView image = ImageView::New(IMAGE_PATH);
    image.SetProperty(Actor::Property::ANCHOR_POINT, AnchorPoint::CENTER);
    image.SetProperty(Actor::Property::PARENT_ORIGIN,
                      Vector3(0.5f, 0.25f, 0.5f));
    window.Add(image);

    // Create an ImageView with properties set from the style sheet
    ImageView styledImage = ImageView::New();
    styledImage.SetStyleName(IMAGE_STYLE_NAME);
    window.Add(styledImage);
  }

  ///< Called when a key is pressed, we'll use this to quit
  void OnKeyEvent(const KeyEvent &event) {
    if (event.GetState() == KeyEvent::DOWN) {
      if (IsKey(event, Dali::DALI_KEY_ESCAPE) ||
          IsKey(event, Dali::DALI_KEY_BACK)) {
        mApplication.Quit();
      }
    }
  }

private:
  Application &mApplication;
};

int DALI_EXPORT_API main(int argc, char **argv) {
  Application application = Application::New(&argc, &argv, STYLE_PATH);
  Example test(application);
  application.MainLoop();
  return 0;
}
