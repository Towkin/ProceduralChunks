<?xml version="1.0"?><doc>
<members>
<member name="T:sf.View" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="40">
\brief 2D camera that defines what region is shown on screen

</member>
<member name="M:sf.View.#ctor" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="48">
\brief Default constructor

This constructor creates a default view of (0, 0, 1000, 1000)

</member>
<member name="M:sf.View.#ctor(sf.Rect&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="56">
\brief Construct the view from a rectangle

\param rectangle Rectangle defining the zone to display

</member>
<member name="M:sf.View.#ctor(sf.Vector2&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,sf.Vector2&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="64">
\brief Construct the view from its center and size

\param center Center of the zone to display
\param size   Size of zone to display

</member>
<member name="M:sf.View.setCenter(System.Single,System.Single)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="73">
\brief Set the center of the view

\param x X coordinate of the new center
\param y Y coordinate of the new center

\see setSize, getCenter

</member>
<member name="M:sf.View.setCenter(sf.Vector2&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="84">
\brief Set the center of the view

\param center New center

\see setSize, getCenter

</member>
<member name="M:sf.View.setSize(System.Single,System.Single)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="94">
\brief Set the size of the view

\param width  New width of the view
\param height New height of the view

\see setCenter, getCenter

</member>
<member name="M:sf.View.setSize(sf.Vector2&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="105">
\brief Set the size of the view

\param size New size

\see setCenter, getCenter

</member>
<member name="M:sf.View.setRotation(System.Single)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="115">
\brief Set the orientation of the view

The default rotation of a view is 0 degree.

\param angle New angle, in degrees

\see getRotation

</member>
<member name="M:sf.View.setViewport(sf.Rect&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="127">
\brief Set the target viewport

The viewport is the rectangle into which the contents of the
view are displayed, expressed as a factor (between 0 and 1)
of the size of the RenderTarget to which the view is applied.
For example, a view which takes the left side of the target would
be defined with View.setViewport(sf::FloatRect(0, 0, 0.5, 1)).
By default, a view has a viewport which covers the entire target.

\param viewport New viewport rectangle

\see getViewport

</member>
<member name="M:sf.View.reset(sf.Rect&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="144">
\brief Reset the view to the given rectangle

Note that this function resets the rotation angle to 0.

\param rectangle Rectangle defining the zone to display

\see setCenter, setSize, setRotation

</member>
<member name="M:sf.View.getCenter" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="156">
\brief Get the center of the view

\return Center of the view

\see getSize, setCenter

</member>
<member name="M:sf.View.getSize" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="166">
\brief Get the size of the view

\return Size of the view

\see getCenter, setSize

</member>
<member name="M:sf.View.getRotation" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="176">
\brief Get the current orientation of the view

\return Rotation angle of the view, in degrees

\see setRotation

</member>
<member name="M:sf.View.getViewport" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="186">
\brief Get the target viewport rectangle of the view

\return Viewport rectangle, expressed as a factor of the target size

\see setViewport

</member>
<member name="M:sf.View.move(System.Single,System.Single)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="196">
\brief Move the view relatively to its current position

\param offsetX X coordinate of the move offset
\param offsetY Y coordinate of the move offset

\see setCenter, rotate, zoom

</member>
<member name="M:sf.View.move(sf.Vector2&lt;System.Single&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="207">
\brief Move the view relatively to its current position

\param offset Move offset

\see setCenter, rotate, zoom

</member>
<member name="M:sf.View.rotate(System.Single)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="217">
\brief Rotate the view relatively to its current orientation

\param angle Angle to rotate, in degrees

\see setRotation, move, zoom

</member>
<!-- Discarding badly formed XML document comment for member 'M:sf.View.zoom(System.Single)'. -->
<member name="M:sf.View.getTransform" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="244">
\brief Get the projection transform of the view

This function is meant for internal use only.

\return Projection transform defining the view

\see getInverseTransform

</member>
<member name="M:sf.View.getInverseTransform" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\graphics\view.hpp" line="256">
\brief Get the inverse projection transform of the view

This function is meant for internal use only.

\return Inverse of the projection transform defining the view

\see getTransform

</member>
<member name="T:sf.Window" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="54">
\brief Window that serves as a target for OpenGL rendering

</member>
<member name="M:sf.Window.#ctor" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="62">
\brief Default constructor

This constructor doesn't actually create the window,
use the other constructors or call create() to do so.

</member>
<member name="M:sf.Window.#ctor(sf.VideoMode,sf.String!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt32,sf.ContextSettings!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="71">
\brief Construct a new window

This constructor creates the window with the size and pixel
depth defined in \a mode. An optional style can be passed to
customize the look and behavior of the window (borders,
title bar, resizable, closable, ...). If \a style contains
Style::Fullscreen, then \a mode must be a valid video mode.

The fourth parameter is an optional structure specifying
advanced OpenGL context settings such as antialiasing,
depth-buffer bits, etc.

\param mode     Video mode to use (defines the width, height and depth of the rendering area of the window)
\param title    Title of the window
\param style    %Window style, a bitwise OR combination of sf::Style enumerators
\param settings Additional settings for the underlying OpenGL context

</member>
<member name="M:sf.Window.#ctor(HWND__*,sf.ContextSettings!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="92">
\brief Construct the window from an existing control

Use this constructor if you want to create an OpenGL
rendering area into an already existing control.

The second parameter is an optional structure specifying
advanced OpenGL context settings such as antialiasing,
depth-buffer bits, etc.

\param handle   Platform-specific handle of the control (\a HWND on
                Windows, \a %Window on Linux/FreeBSD, \a NSWindow on OS X)
\param settings Additional settings for the underlying OpenGL context

</member>
<member name="M:sf.Window.Dispose" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="109">
\brief Destructor

Closes the window and frees all the resources attached to it.

</member>
<member name="M:sf.Window.create(sf.VideoMode,sf.String!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt32,sf.ContextSettings!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="117">
\brief Create (or recreate) the window

If the window was already created, it closes it first.
If \a style contains Style::Fullscreen, then \a mode
must be a valid video mode.

The fourth parameter is an optional structure specifying
advanced OpenGL context settings such as antialiasing,
depth-buffer bits, etc.

\param mode     Video mode to use (defines the width, height and depth of the rendering area of the window)
\param title    Title of the window
\param style    %Window style, a bitwise OR combination of sf::Style enumerators
\param settings Additional settings for the underlying OpenGL context

</member>
<member name="M:sf.Window.create(HWND__*,sf.ContextSettings!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="136">
\brief Create (or recreate) the window from an existing control

Use this function if you want to create an OpenGL
rendering area into an already existing control.
If the window was already created, it closes it first.

The second parameter is an optional structure specifying
advanced OpenGL context settings such as antialiasing,
depth-buffer bits, etc.

\param handle   Platform-specific handle of the control (\a HWND on
                Windows, \a %Window on Linux/FreeBSD, \a NSWindow on OS X)
\param settings Additional settings for the underlying OpenGL context

</member>
<member name="M:sf.Window.close" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="154">
\brief Close the window and destroy all the attached resources

After calling this function, the sf::Window instance remains
valid and you can call create() to recreate the window.
All other functions such as pollEvent() or display() will
still work (i.e. you don't have to test isOpen() every time),
and will have no effect on closed windows.

</member>
<member name="M:sf.Window.isOpen" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="166">
\brief Tell whether or not the window is open

This function returns whether or not the window exists.
Note that a hidden window (setVisible(false)) is open
(therefore this function would return true).

\return True if the window is open, false if it has been closed

</member>
<member name="M:sf.Window.getSettings" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="178">
\brief Get the settings of the OpenGL context of the window

Note that these settings may be different from what was
passed to the constructor or the create() function,
if one or more settings were not supported. In this case,
SFML chose the closest match.

\return Structure containing the OpenGL context settings

</member>
<member name="M:sf.Window.pollEvent(sf.Event*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="191">
\brief Pop the event on top of the event queue, if any, and return it

This function is not blocking: if there's no pending event then
it will return false and leave \a event unmodified.
Note that more than one event may be present in the event queue,
thus you should always call this function in a loop
to make sure that you process every pending event.
\code
sf::Event event;
while (window.pollEvent(event))
{
   // process event...
}
\endcode

\param event Event to be returned

\return True if an event was returned, or false if the event queue was empty

\see waitEvent

</member>
<member name="M:sf.Window.waitEvent(sf.Event*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="216">
\brief Wait for an event and return it

This function is blocking: if there's no pending event then
it will wait until an event is received.
After this function returns (and no error occurred),
the \a event object is always valid and filled properly.
This function is typically used when you have a thread that
is dedicated to events handling: you want to make this thread
sleep as long as no new event is received.
\code
sf::Event event;
if (window.waitEvent(event))
{
   // process event...
}
\endcode

\param event Event to be returned

\return False if any error occurred

\see pollEvent

</member>
<member name="M:sf.Window.getPosition" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="243">
\brief Get the position of the window

\return Position of the window, in pixels

\see setPosition

</member>
<member name="M:sf.Window.setPosition(sf.Vector2&lt;System.Int32&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="253">
\brief Change the position of the window on screen

This function only works for top-level windows
(i.e. it will be ignored for windows created from
the handle of a child window/control).

\param position New position, in pixels

\see getPosition

</member>
<member name="M:sf.Window.getSize" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="267">
\brief Get the size of the rendering region of the window

The size doesn't include the titlebar and borders
of the window.

\return Size in pixels

\see setSize

</member>
<member name="M:sf.Window.setSize(sf.Vector2&lt;System.UInt32&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="280">
\brief Change the size of the rendering region of the window

\param size New size, in pixels

\see getSize

</member>
<member name="M:sf.Window.setTitle(sf.String!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="290">
\brief Change the title of the window

\param title New title

\see setIcon

</member>
<member name="M:sf.Window.setIcon(System.UInt32,System.UInt32,System.Byte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="300">
\brief Change the window's icon

\a pixels must be an array of \a width x \a height pixels
in 32-bits RGBA format.

The OS default icon is used by default.

\param width  Icon's width, in pixels
\param height Icon's height, in pixels
\param pixels Pointer to the array of pixels in memory. The
              pixels are copied, so you need not keep the
              source alive after calling this function.

\see setTitle

</member>
<member name="M:sf.Window.setVisible(System.Boolean)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="319">
\brief Show or hide the window

The window is shown by default.

\param visible True to show the window, false to hide it

</member>
<member name="M:sf.Window.setVerticalSyncEnabled(System.Boolean)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="329">
\brief Enable or disable vertical synchronization

Activating vertical synchronization will limit the number
of frames displayed to the refresh rate of the monitor.
This can avoid some visual artifacts, and limit the framerate
to a good value (but not constant across different computers).

Vertical synchronization is disabled by default.

\param enabled True to enable v-sync, false to deactivate it

</member>
<member name="M:sf.Window.setMouseCursorVisible(System.Boolean)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="344">
\brief Show or hide the mouse cursor

The mouse cursor is visible by default.

\param visible True to show the mouse cursor, false to hide it

</member>
<member name="M:sf.Window.setKeyRepeatEnabled(System.Boolean)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="354">
\brief Enable or disable automatic key-repeat

If key repeat is enabled, you will receive repeated
KeyPressed events while keeping a key pressed. If it is disabled,
you will only get a single event when the key is pressed.

Key repeat is enabled by default.

\param enabled True to enable, false to disable

</member>
<member name="M:sf.Window.setFramerateLimit(System.UInt32)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="368">
\brief Limit the framerate to a maximum fixed frequency

If a limit is set, the window will use a small delay after
each call to display() to ensure that the current frame
lasted long enough to match the framerate limit.
SFML will try to match the given limit as much as it can,
but since it internally uses sf::sleep, whose precision
depends on the underlying OS, the results may be a little
unprecise as well (for example, you can get 65 FPS when
requesting 60).

\param limit Framerate limit, in frames per seconds (use 0 to disable limit)

</member>
<member name="M:sf.Window.setJoystickThreshold(System.Single)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="385">
\brief Change the joystick threshold

The joystick threshold is the value below which
no JoystickMoved event will be generated.

The threshold value is 0.1 by default.

\param threshold New threshold, in the range [0, 100]

</member>
<member name="M:sf.Window.setActive(System.Boolean)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="398">
\brief Activate or deactivate the window as the current target
       for OpenGL rendering

A window is active only on the current thread, if you want to
make it active on another thread you have to deactivate it
on the previous thread first if it was active.
Only one window can be active on a thread at a time, thus
the window previously active (if any) automatically gets deactivated.
This is not to be confused with requestFocus().

\param active True to activate, false to deactivate

\return True if operation was successful, false otherwise

</member>
<member name="M:sf.Window.requestFocus" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="416">
\brief Request the current window to be made the active
       foreground window

At any given time, only one window may have the input focus
to receive input events such as keystrokes or mouse events.
If a window requests focus, it only hints to the operating
system, that it would like to be focused. The operating system
is free to deny the request.
This is not to be confused with setActive().

\see hasFocus

</member>
<member name="M:sf.Window.hasFocus" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="432">
\brief Check whether the window has the input focus

At any given time, only one window may have the input focus
to receive input events such as keystrokes or most mouse
events.

\return True if window has focus, false otherwise
\see requestFocus

</member>
<member name="M:sf.Window.display" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="445">
\brief Display on screen what has been rendered to the window so far

This function is typically called after all OpenGL rendering
has been done for the current frame, in order to show
it on screen.

</member>
<member name="M:sf.Window.getSystemHandle" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="455">
\brief Get the OS-specific handle of the window

The type of the returned handle is sf::WindowHandle,
which is a typedef to the handle type defined by the OS.
You shouldn't need to use this function, unless you have
very specific stuff to implement that SFML doesn't support,
or implement a temporary workaround until a bug is fixed.
The type is \a HWND on Windows, \a %Window on Linux/FreeBSD
and \a NSWindow on OS X.

\return System handle of the window

</member>
<member name="M:sf.Window.onCreate" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="473">
\brief Function called after the window has been created

This function is called so that derived classes can
perform their own specific initialization as soon as
the window is created.

</member>
<member name="M:sf.Window.onResize" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="483">
\brief Function called after the window has been resized

This function is called so that derived classes can
perform custom actions when the size of the window changes.

</member>
<member name="M:sf.Window.filterEvent(sf.Event!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="494">
\brief Processes an event before it is sent to the user

This function is called every time an event is received
from the internal window (through pollEvent or waitEvent).
It filters out unwanted events, and performs whatever internal
stuff the window needs before the event is returned to the
user.

\param event Event to filter

</member>
<member name="M:sf.Window.initialize" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="508">
\brief Perform some common internal initializations

</member>
<member name="T:Camera" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\window.hpp" line="530">
\class sf::Window
\ingroup window

sf::Window is the main class of the Window module. It defines
an OS window that is able to receive an OpenGL rendering.

A sf::Window can create its own new window, or be embedded into
an already existing control using the create(handle) function.
This can be useful for embedding an OpenGL rendering area into
a view which is part of a bigger GUI with existing windows,
controls, etc. It can also serve as embedding an OpenGL rendering
area into a window created by another (probably richer) GUI library
like Qt or wxWidgets.

The sf::Window class provides a simple interface for manipulating
the window: move, resize, show/hide, control mouse cursor, etc.
It also provides event handling through its pollEvent() and waitEvent()
functions.

Note that OpenGL experts can pass their own parameters (antialiasing
level, bits for the depth and stencil buffers, etc.) to the
OpenGL context attached to the window, with the sf::ContextSettings
structure which is passed as an optional argument when creating the
window.

Usage example:
\code
// Declare and create a new window
sf::Window window(sf::VideoMode(800, 600), "SFML window");

// Limit the framerate to 60 frames per second (this step is optional)
window.setFramerateLimit(60);

// The main loop - ends as soon as the window is closed
while (window.isOpen())
{
   // Event processing
   sf::Event event;
   while (window.pollEvent(event))
   {
       // Request for closing the window
       if (event.type == sf::Event::Closed)
           window.close();
   }

   // Activate the window for OpenGL rendering
   window.setActive();

   // OpenGL drawing commands go here...

   // End the current frame and display its contents on screen
   window.display();
}
\endcode

</member>
<member name="T:sf.Mouse" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="40">
\brief Give access to the real-time state of the mouse

</member>
<member name="T:sf.Mouse.Button" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="48">
\brief Mouse buttons

</member>
<member name="T:sf.Mouse.Wheel" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="63">
\brief Mouse wheels

</member>
<member name="M:sf.Mouse.isButtonPressed(sf.Mouse.Button)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="73">
\brief Check if a mouse button is pressed

\param button Button to check

\return True if the button is pressed, false otherwise

</member>
<member name="M:sf.Mouse.getPosition" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="83">
\brief Get the current position of the mouse in desktop coordinates

This function returns the global position of the mouse
cursor on the desktop.

\return Current position of the mouse

</member>
<member name="M:sf.Mouse.getPosition(sf.Window!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="94">
\brief Get the current position of the mouse in window coordinates

This function returns the current position of the mouse
cursor, relative to the given window.

\param relativeTo Reference window

\return Current position of the mouse

</member>
<member name="M:sf.Mouse.setPosition(sf.Vector2&lt;System.Int32&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="107">
\brief Set the current position of the mouse in desktop coordinates

This function sets the global position of the mouse
cursor on the desktop.

\param position New position of the mouse

</member>
<member name="M:sf.Mouse.setPosition(sf.Vector2&lt;System.Int32&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,sf.Window!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\mouse.hpp" line="118">
\brief Set the current position of the mouse in window coordinates

This function sets the current position of the mouse
cursor, relative to the given window.

\param position New position of the mouse
\param relativeTo Reference window

</member>
<member name="T:sf.Keyboard" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\keyboard.hpp" line="37">
\brief Give access to the real-time state of the keyboard

</member>
<member name="T:sf.Keyboard.Key" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\keyboard.hpp" line="45">
\brief Key codes

</member>
<member name="M:sf.Keyboard.isKeyPressed(sf.Keyboard.Key)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\keyboard.hpp" line="157">
\brief Check if a key is pressed

\param key Key to check

\return True if the key is pressed, false otherwise

</member>
<member name="M:sf.Keyboard.setVirtualKeyboardVisible(System.Boolean)" decl="true" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\keyboard.hpp" line="167">
\brief Show or hide the virtual keyboard

Warning: the virtual keyboard is not supported on all
systems. It will typically be implemented on mobile OSes
(Android, iOS) but not on desktop OSes (Windows, Linux, ...).

If the virtual keyboard is not available, this function does
nothing.

\param visible True to show, false to hide

</member>
<member name="M:Camera.#ctor(sf.Window!System.Runtime.CompilerServices.IsConst*,System.Single)" decl="false" source="d:\mina saker\annat\visual studio projekt\proceduralchunksgit\proceduralchunks\include\sfml\window\keyboard.hpp" line="189">
\class sf::Keyboard
\ingroup window

sf::Keyboard provides an interface to the state of the
keyboard. It only contains static functions (a single
keyboard is assumed), so it's not meant to be instantiated.

This class allows users to query the keyboard state at any
time and directly, without having to deal with a window and
its events. Compared to the KeyPressed and KeyReleased events,
sf::Keyboard can retrieve the state of a key at any time
(you don't need to store and update a boolean on your side
in order to know if a key is pressed or released), and you
always get the real state of the keyboard, even if keys are
pressed or released when your window is out of focus and no
event is triggered.

Usage example:
\code
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    // move left...
}
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    // move right...
}
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
{
    // quit...
}
\endcode

\see sf::Joystick, sf::Mouse, sf::Touch

</member>
</members>
</doc>