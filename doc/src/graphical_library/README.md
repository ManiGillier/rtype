
Graphical Library
-------

# Restrictions

The Graphical Library imposes restrictions.

1. All methods must be called in a single Thread.
2. The `init` method must be called before any other method.
3. The `deinit` method must be called before the object is deconstructed.

# Usage

## Rectangle

In order to draw a rectangle, you need to create a `Rectangle` object, and then call the `draw` method with that rectangle.

You can specify three parameters.  
1. The on-screen position with `position`, as a `WorldPosition` object.
2. The on-screen size with `size`, as a `Vector2ui` object.
3. The color with `color`.

## Text

In order to draw text on screen, you need to create a `Text` object, and then call the `draw` method with that text.

To help center the text, you can use the `getTextWidth` method to get the width of the text in on-screen pixels, using either a `Text` object, or just plain text with a fontSize.

You cannot change the text font.

You can choose the text, it's on-screen position, font size and color.

## Images

Images are called Textures.

Textures are referenced by name as a `std::string`.

The best way to use Textures is to register them using the `registerTexture` method, by specifying a path to the texture file, and a name to reference it ; then to load all textures with `loadAllTextures` at a specified time.  
This way, you will have a lag at the loading time, but not in random state change. You could load all textures in a dedicated "Loading" screen for example.

If you prefer, you can load a single texture instantly using the `loadTexture` method.

You can get a loaded texture through the `getTexture` method.

You can render a `Texture` object via the `draw` method.

To position the texture to draw, modify a copy of the `Texture` object.  

You have write access to :  
1. The `scale` attribute, to scale up or down the texture. 1.0 is the default scale.
2. The `pos` attribute, to set the on-screen position.
3. The `rotation` attribyte, to set the rotation in degrees.

You have read access to :  
1. The `path` attribute, specifying the texture file path.
2. The `name` attribute, specifying the texture reference name.
3. The `size` attribute, specifying the on-screen size for a scale of 1.

## Sound

Like textures, sound can be registered for loading, or loaded directly following similar conventions.

You only have read access on the `Sound` object, allowing the reading of the file path and reference name.

A sound is played using the `play` method.

## Events

Events are used to know if a key is pressed, down or just up.

You can register a list of events with the `registerEvent` method.  
Events are referenced by name in the form of a `std::string`.

If you want to deactivate an event, bind it to the `gl::Key::UNDEFINED` key.

You can re-bind events using the `bindKey` method.

If the key bound to an event was pressed in the current frame but not in the precedent frame, the `isEventStart` method should yield `true`.

If the key bound to an event is currently pressed, the `isEventActive` method should yield `true`.

In other cases, or if the event is deactivated, the `isEvent{Start,Active}` methods should yield false.

## Render loop

The render loop should be implemented at a higher order.

If the window was closed, the `should_close` method returns `true`.  
You should not call any methods other than `end_frame` or `deinit` in this case.

Any render methods should be called between the call of `start_new_frame` and `end_frame`.

A typical implementation would be like the following : 

``` c++
gl.init();
/*
Register events
Register textures
Register sounds
*/
gl.loadEverything();
while (!gl.should_close()) {
    gl.start_new_frame(gl::BLACK);
    /*
    Drawing code here
    */
    gl.end_frame();
}
gl.deinit();
```

## Miscellaneous

When using textures and sound, we recommand using the `loadEverything` method, loading both registered textures and sounds.

If you need to get the window size, use the `get_window_size` method.

If you need to get the delta time between the last frame, use the `getDeltaTime` method.

## Implementation

An implementation was done using the `Raylib` library, and can be found in the `graphical_library/raylib/` directory.

You can instanciate it in a cpp file using the following : 

``` c++
#include <graphical_library/raylib/Raylib.hpp>

std::make_unique<Raylib>();
```

## Elements

The library features several graphical utilities such as `Button`, `TextBox`, `InputBox`, `KeybindSelect`, and `CheckBox` which can be created later on by only using a few parameters like the pos, the size, the color and the action the element needs to apply.

## GUI Creation

Using the elements creating new GUIs menu is easier, it can be done by creating a new folder in `client/state_machine/states/` using the GUI's name as folder name.
Once donc you need to add a .ccp and a .hpp using the GUI's name. then a gui folder containing every elements wanted as .hpp files as well as a file named `[GUI's name]Scene.hpp` holding every initializations like `this->add<Element>()`.
Then you need to create the scene in your initial hpp and cpp and your GUI is good to go.
For exemple creating a menu which would have a singular button I would create a folder called menu/ containing :
### gui/MenuScene.hpp :
```cpp
#include <graphical_library/raylib/GuiScene.hpp>

class MenuScene : public GuiScene
{
public:
    MenuScene(gl::GraphicalLibrary &gl)
    : GuiScene(gl) {}

    auto init() -> void
    {
        this->add<MenuButton>();
    }
};
```

### gui/MenuButton.hpp :
```cpp
class MenuButton : public Button
{
public:
    MenuButton()
    : Button()
    {
        this->x = 650;
        this->y = 700;
        this->width = 300;
        this->height = 55;
        this->idleColor = {120, 200, 120, 255};
        this->hoverColor = {180, 255, 180, 255};
        this->pressedColor = {80, 160, 80, 255};
        this->text = "Click me !";
    }
    auto onClick() -> void
    {
        std::cout << "You clicked me !" << std::endl;
    }
};

```

### Menu.hpp :
```cpp
#include "client/state_machine/State.hpp"

class Menu : public State {
public:
    Menu(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void
};
```

### Menu.cpp :
```cpp
#include "Menu.hpp"
#include <iostream>
#include <memory>
#include "client/manager/ClientManager.hpp"
#include "client/state_machine/State.hpp"
#include "gui/MenuScene.hpp"

Menu::Menu(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Menu::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene =
        std::make_unique<MenuScene>(this->getGraphicalLibrary(), *this);
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();
}
```

SOON tm
