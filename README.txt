---------------------------  Quad-Buffered Stereo  ---------------------------
                                OsiriX Plugin
                                    README
                        Created: 2006-01-31 by Jonathon Mah
                   Last Updated: 2006-02-01 by Jonathon Mah



Introduction:
  The Quad-Buffered Stereo plugin for OsiriX allows you to view 3D
  reconstructions in stereo. The plugin sends the left and right images to the
  graphics card. Depending on your graphics card's capabilities, you can use
  viewing methods such as active shutter glasses or passive TwinView monitor
  output.
  
  The plugin also adds stereo exporting of QuickTime fly-through movies.  This
  creates separate movie files for the left and right eyes.


Requirements:
- OsiriX 2.3
- A graphics card capable of stereo output, for stereo viewing
- Stereo movie exporting has no extra requirements


Features:
- Stereo viewing of all 3D renderings
  - MPR
  - Maximum Intensity Projection
  - Volume Rendering
  - Surface Rendering
  - Endoscopy
- Stereo exports of fly-throughs
- PPC and Intel compatibility (Universal Binary)


Installation:
  Copy 'Quad-Buffered Stereo.plugin' into the directory:
  /Library/Application Support/OsiriX/Plugins/
  Alternatively, you can copy it to your home Library folder.


Usage:
  Open OsiriX and load any image series. To open the stereo settings, choose
  the menu item "Plugins > Others > Quad-Buffered Stereo". 3D reconstructions
  will use this stereo option. To access stereo settings whilst a 3D view is
  open, shift-click the Stereo toolbar button.


Tips:
- Set the background of 3D MPR views to dark gray instead of black, so you can
  tell the background from the black edges of slices.


Bugs:
- The left and right images are inverted in volume rendering modes (MIP,
  Volume Rendering, and Endoscopy)
- The "Quad-Buffered Stereo" menu item is not available from within a 3D view


Credits:
  Quad-Buffered Stereo was created by Jonathon Mah during an internship at the
  South Australian Partnership for Advanced Computing (SAPAC), over the
  (Australian) summer of 2005-2006. Thanks to Craig Hill for the initial idea
  and ongoing support; Paul Bourke for the introduction to stereoscopy and
  great sample code; and Dr Antoine Rosset and the OsiriX development team for
  an amazing open-source product.


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


Version History:
1.0   (2006-02-xx)
  - Initial public release

0.1   (2005-12-08)
  - Development begun by Jonathon Mah


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