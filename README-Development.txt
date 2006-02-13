---------------------------  Quad-Buffered Stereo  ---------------------------
                                OsiriX Plugin
                            README for Developers
                        Created: 2006-01-31 by Jonathon Mah
                   Last Updated: 2006-02-13 by Jonathon Mah



Class List:
  QuadBufferedStereo
    The plugin class that OsiriX talks to when the menu item is selected.
  QBSController
    The main controller that handles the settings user interface, user
    defaults, and initializing the screen to stereo. A singleton class
    accessed with +[QBSController sharedController].
  NSOpenGLPixelFormat+QuadBufferedStereo
    Allows inserting the stereo pixel format attribute to newly-initialized
    OpenGL pixel formats.
  VTKView+QuadBufferedStereo
    Sets up VTK for stereo rendering on registered subclasses. Handles the
    registration of these classes.
  MPRView+QuadBufferedStereo
    Overrides the stereo switching behavior.
  SRView+QuadBufferedStereo, and
  VRView+QuadBufferedStereo
    Overrides the stereo switching behavior and provides methods for reading
    pixel data from either the left or right buffers. This is necessary when
    capturing a fly-through movie and the view is in quad-buffered stereo
    mode.
  FlyThruController+QuadBufferedStereo
    Adds stereo movie export for fly-throughs.


Code Overview:
  The Quad-Buffered Stereo plugin makes extensive use of "method sizzling", a
  technique which changes the runtime class structure to remap method
  implementations.  It sounds scary, but it's perfectly safe. :) CocoaDev has
  a good introduction to method swizzling, located at
  <http://www.cocoadev.com/index.pl?MethodSwizzling>. The purpose of this is
  to allow certain methods to be overridden by categories whilst keeping
  access to the original methods. For example, the primary method in
  NSOpenGLPixelFormat+QuadBufferedStereo category is:
  
  - (id)QBS_initWithAttributes:(NSOpenGLPixelFormatAttribute *)attrs;
    // Will be swizzled for -initWithAttributes:
  
  At runtime (in the +load method), the -initWithAttributes: method from the
  NSOpenGLPixelFormat will be renamed to -QBS_initWithAttributes:, and our
  method will be renamed to -initWithAttributes:. Thus when some code calls
  [[NSOpenGLPixelFormat alloc] initWithAttributres:attrs], our code will
  instead be called. Inside our -QBS_initWithAttributes method are lines such
  as:
  
  result = [self QBS_initWithAttributes:attrs];
  
  This is _not_ a recursive call to itself; rather, it is a call to the
  original -initWithAttributres: method (which will have been renamed by the
  time this code is executed).
  
  To create a quad-buffered OpenGL view, the view must be initialized with a
  stereo pixel format. However, VTK never supplies this, and since the VTK
  initialization code is written in C++, it cannot be modified at runtime to
  do so. To create a stereo pixel format, I added a category on
  NSOpenGLPixelFormat which adds stereo to _every_ pixel format created
  between a pair of method calls. This is unlikely to cause any problems, but
  should be kept in mind should OsiriX ever create multiple OpenGL views
  simultaneously in multiple threads.
  
  During QuickTime movie capture of fly-throughs, pixel data is read from the
  window. If quad-buffered stereo is enabled, the pixel data will always be
  read from the left eye buffer, so stereo movies cannot be created. To read
  from the correct buffer, glReadBuffer() must be called. This is the job of
  -[SRView QBS_nsimage:], which is called in place of the original
  -[SRView nsimage:] method (and similarly for VRView).


Fragility:
  The Quad-Buffered Stereo plugin uses certain code that may break in the
  future. The overridden stereo switching methods are based on code taken from
  the respective views in OsiriX. If the switching code in OsiriX changes,
  these overridden methods (which don't ever call the original method) may
  require updating.
  
  The same is the case with the -initWithFrame: method in VTKView, and
  -QBS_flyThruQuickTimeExportStereo in FlyThruController.
  
  It would be best to integrate the functionality of this plugin directly into
  OsiriX, so that future OsiriX changes will not break it.


3D Volume Rendering:
  (I am not experienced with VTK; the following is to the best of my knowledge
  as I was researching VTK's rendering methods.)
  
  VTK performs stereo rendering in the OpenGL renderer, using the OpenGL
  geometry to calculate the appropriate images for left and right eyes. VTK
  performs ray cast volume renderings in software and then places it into the
  OpenGL scene as a texture on a simple quad (plane). Without modification,
  this quad is placed close to the camera, adding extra stereo separation to
  the volume. For the volume to be correctly displayed, the quad must be
  placed at the focal point of the left and right cameras, so that the quad
  has zero parallax.
  
  This can be achieved by ignoring a parameter passed to a method in the VTK
  class 'vtkOpenGLRayCastImageDisplayHelper'. I don't know the consequences of
  doing this, but it seems to have the desired effect. A simple patch to do
  this is included in the file 'vtkOpenGLRayCastImageDisplayHelper.cxx.patch'.
  Having to alter VTK is undesirable, as it means that both VTK and OsiriX
  must be recompiled.
  
  This workaround could change if/when OsiriX adds support for alternate
  volume renderers, such as shear warping.
  
  This still contains a bug, though: the stereo is inverted (the left eye
  image is displayed in the right eye, and vice-versa). I couldn't see what
  caused this, and have left it unfixed at the moment. If you find a fix,
  please contact me (Jonathon Mah; details below).


Links:
  Jonathon Mah
    <me@JonathonMah.com>
    <http://www.JonathonMah.com/>
  Paul Bourke
    <http://www.swin.edu.au/astronomy/pbourke/>
  SAPAC
    <http://www.sapac.edu.au/>
  OsiriX
    <http://homepage.mac.com/rossetantoine/osirix/>
  VTK
    <http://www.vtk.org/>


License:
  The Quad-Buffered Stereo plugin is Copyright 2005-2006 Jonathon Mah, SAPAC,
  and is licensed under the MIT License as follows:
  
  Copyright (c) 2005-2006 Jonathon Mah, SAPAC
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to
  deal in the Software without restriction, including without limitation the
  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
  sell copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
