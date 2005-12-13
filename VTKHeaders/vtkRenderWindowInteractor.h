/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkRenderWindowInteractor.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkRenderWindowInteractor - platform-independent render window interaction including picking and frame rate control.

// .SECTION Description
// vtkRenderWindowInteractor provides a platform-independent interaction
// mechanism for mouse/key/time events. It serves as a base class for
// platform-dependent implementations that handle routing of mouse/key/timer
// messages to vtkInteractorStyle and its subclasses. 
// vtkRenderWindowInteractor also provides controls for picking,
// rendering frame rate, and headlights.
//
// vtkRenderWindowInteractor has changed from previous implementations and
// now serves only as a shell to hold user preferences and route messages
// to vtkInteractorStyle. Callbacks are available for many Events.
// Platform specific subclasses should provide methods for
// CreateTimer/DestroyTimer, TerminateApp, and an event loop if required
// via Initialize/Start/Enable/Disable.

#ifndef __vtkRenderWindowInteractor_h
#define __vtkRenderWindowInteractor_h

#include "vtkObject.h"

// Timer flags for win32/X compatibility
#define VTKI_TIMER_FIRST  0
#define VTKI_TIMER_UPDATE 1

class vtkAbstractPicker;
class vtkAbstractPropPicker;
class vtkInteractorObserver;
class vtkInteractorObserver;
class vtkRenderWindow;
class vtkRenderer;

class VTK_RENDERING_EXPORT vtkRenderWindowInteractor : public vtkObject
{
public:
  static vtkRenderWindowInteractor *New();
  vtkTypeRevisionMacro(vtkRenderWindowInteractor,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Prepare for handling events. This must be called before the
  // interactor will work.
  virtual void Initialize();
  void ReInitialize() {  this->Initialized = 0; this->Enabled = 0;
                        this->Initialize(); } 

  // Description:
  // This Method detects loops of RenderWindow-Interactor,
  // so objects are freed properly.
  virtual void UnRegister(vtkObjectBase *o);

  // Description:
  // Start the event loop. This is provided so that you do not have to
  // implement your own event loop. You still can use your own
  // event loop if you want. Initialize should be called before Start.
  virtual void Start() {};

  // Description:
  // Enable/Disable interactions.  By default interactors are enabled when
  // initialized.  Initialize() must be called prior to enabling/disabling
  // interaction. These methods are used when a window/widget is being
  // shared by multiple renderers and interactors.  This allows a "modal"
  // display where one interactor is active when its data is to be displayed
  // and all other interactors associated with the widget are disabled
  // when their data is not displayed.
  virtual void Enable() { this->Enabled = 1; this->Modified();};
  virtual void Disable() { this->Enabled = 0; this->Modified();};
  vtkGetMacro(Enabled, int);

  // Description:
  // Set/Get the rendering window being controlled by this object.
  void SetRenderWindow(vtkRenderWindow *aren);
  vtkGetObjectMacro(RenderWindow,vtkRenderWindow);

  // Description:
  // Event loop notification member for Window size change
  virtual void UpdateSize(int x,int y);

  // Description:
  // Timer methods must be overridden by platform dependent subclasses.
  // flag is passed to indicate if this is first timer set or an update
  // as Win32 uses repeating timers, whereas X uses One shot more timer
  // if flag==VTKXI_TIMER_FIRST Win32 and X should createtimer
  // otherwise Win32 should exit and X should perform AddTimeOut()
  virtual int CreateTimer(int )  { return 1; };
  virtual int DestroyTimer()    { return 1; };

  // Description:
  // This function is called on 'q','e' keypress if exitmethod is not
  // specified and should be overridden by platform dependent subclasses
  // to provide a termination procedure if one is required.
  virtual void TerminateApp(void) {};

  // Description:
  // External switching between joystick/trackball/new? modes.
  virtual void SetInteractorStyle(vtkInteractorObserver *);
  vtkGetObjectMacro(InteractorStyle,vtkInteractorObserver);

  // Description:
  // Turn on/off the automatic repositioning of lights as the camera moves.
  vtkSetMacro(LightFollowCamera,int);
  vtkGetMacro(LightFollowCamera,int);
  vtkBooleanMacro(LightFollowCamera,int);

  // Description:
  // Set/Get the desired update rate. This is used by vtkLODActor's to tell
  // them how quickly they need to render.  This update is in effect only
  // when the camera is being rotated, or zoomed.  When the interactor is
  // still, the StillUpdateRate is used instead.
  vtkSetClampMacro(DesiredUpdateRate,double,0.0001,VTK_LARGE_FLOAT);
  vtkGetMacro(DesiredUpdateRate,double);

  // Description:
  // Set/Get the desired update rate when movement has stopped.
  // See the SetDesiredUpdateRate method.
  vtkSetClampMacro(StillUpdateRate,double,0.0001,VTK_LARGE_FLOAT);
  vtkGetMacro(StillUpdateRate,double);

  // Description:
  // See whether interactor has been initialized yet.
  vtkGetMacro(Initialized,int);

  // Description:
  // Set/Get the object used to perform pick operations. In order to
  // pick instances of vtkProp, the picker must be a subclass of 
  // vtkAbstractPropPicker, meaning that it can identify a particular 
  // instance of vtkProp.
  virtual void SetPicker(vtkAbstractPicker*);
  vtkGetObjectMacro(Picker,vtkAbstractPicker);

  // Description:
  // Create default picker. Used to create one when none is specified.
  // Default is an instance of vtkPropPicker.
  virtual vtkAbstractPropPicker *CreateDefaultPicker();

  // Description:
  // These methods correspond to the the Exit, User and Pick
  // callbacks. They allow for the Style to invoke them.
  virtual void ExitCallback();
  virtual void UserCallback();
  virtual void StartPickCallback();
  virtual void EndPickCallback();
  
  // Description:
  // Get the current position of the mouse.
  virtual void GetMousePosition(int *x, int *y) { *x = 0 ; *y = 0; }

  // Description:
  // Hide or show the mouse cursor, it is nice to be able to hide the
  // default cursor if you want VTK to display a 3D cursor instead.
  void HideCursor();
  void ShowCursor();

  // Description:
  // Render the scene. Just pass the render call on to the 
  // associated vtkRenderWindow.
  virtual void Render();

  // Description:
  // Given a position x, move the current camera's focal point to x.
  // The movement is animated over the number of frames specified in
  // NumberOfFlyFrames. The LOD desired frame rate is used.
  void FlyTo(vtkRenderer *ren, double x, double y, double z);
  void FlyTo(vtkRenderer *ren, double *x)
    {this->FlyTo(ren, x[0], x[1], x[2]);}
  void FlyToImage(vtkRenderer *ren, double x, double y);
  void FlyToImage(vtkRenderer *ren, double *x)
    {this->FlyToImage(ren, x[0], x[1]);}

  // Description:
  // Set the number of frames to fly to when FlyTo is invoked.
  vtkSetClampMacro(NumberOfFlyFrames,int,1,VTK_LARGE_INTEGER);
  vtkGetMacro(NumberOfFlyFrames,int);

  // Description:
  // Set the total Dolly value to use when flying to (FlyTo()) a
  // specified point. Negative values fly away from the point.
  vtkSetMacro(Dolly,double);
  vtkGetMacro(Dolly,double);

  // Description:
  // Set/Get information about the current event. 
  // The current x,y position is in the EventPosition, and the previous
  // event position is in LastEventPosition, updated automatically each
  // time EventPosition is set using its Set() method. 
  // The other information is about key board input.
  vtkGetVector2Macro(EventPosition,int);
  vtkGetVector2Macro(LastEventPosition,int);
  vtkSetVector2Macro(LastEventPosition,int);
  virtual void SetEventPosition(int x, int y)
  {
    vtkDebugMacro(<< this->GetClassName() << " (" << this 
                  << "): setting EventPosition to (" << x << "," << y << ")");
    if (this->EventPosition[0] != x || this->EventPosition[1] != y)
      {
      this->LastEventPosition[0] = this->EventPosition[0];
      this->LastEventPosition[1] = this->EventPosition[1];
      this->EventPosition[0] = x;
      this->EventPosition[1] = y;
      this->Modified();
      }
  };
  virtual void SetEventPosition(int pos[2])
  {
    this->SetEventPosition(pos[0], pos[1]);
  } 
  virtual void SetEventPositionFlipY(int x, int y)
  {
    this->SetEventPosition(x, this->Size[1] - y - 1);
  }
  virtual void SetEventPositionFlipY(int pos[2])
  {
    this->SetEventPositionFlipY(pos[0], pos[1]);
  } 
  vtkSetMacro(ControlKey, int);
  vtkGetMacro(ControlKey, int);
  vtkSetMacro(ShiftKey, int);
  vtkGetMacro(ShiftKey, int);
  vtkSetMacro(KeyCode, char);
  vtkGetMacro(KeyCode, char);
  vtkSetMacro(RepeatCount, int);
  vtkGetMacro(RepeatCount, int);
  vtkSetStringMacro(KeySym);
  vtkGetStringMacro(KeySym);

  // Description:
  // Set all the event information in one call.
  void SetEventInformation(int x, 
                           int y, 
                           int ctrl=0, 
                           int shift=0, 
                           char keycode=0, 
                           int repeatcount=0,
                           const char* keysym=0)
    {
      this->LastEventPosition[0] = this->EventPosition[0];
      this->LastEventPosition[1] = this->EventPosition[1];
      this->EventPosition[0] = x;
      this->EventPosition[1] = y;
      this->ControlKey = ctrl;
      this->ShiftKey = shift;
      this->KeyCode = keycode;
      this->RepeatCount = repeatcount;
      if(keysym)
        {
        this->SetKeySym(keysym);
        }
      this->Modified();
    }

  // Description:
  // Calls SetEventInformation, but flips the Y based on the current Size[1] 
  // value (i.e. y = this->Size[1] - y - 1).
  void SetEventInformationFlipY(int x, 
                                int y, 
                                int ctrl=0, 
                                int shift=0, 
                                char keycode=0, 
                                int repeatcount=0,
                                const char* keysym=0)
    {
      this->SetEventInformation(x, 
                                this->Size[1] - y - 1, 
                                ctrl, 
                                shift, 
                                keycode, 
                                repeatcount, 
                                keysym);
    }

  // Description:
  // Set all the keyboard-related event information in one call.
  void SetKeyEventInformation(int ctrl=0, 
                              int shift=0, 
                              char keycode=0, 
                              int repeatcount=0,
                              const char* keysym=0)
    {
      this->ControlKey = ctrl;
      this->ShiftKey = shift;
      this->KeyCode = keycode;
      this->RepeatCount = repeatcount;
      if(keysym)
        {
        this->SetKeySym(keysym);
        }
      this->Modified();
    }

  // Description:
  // This methods sets the Size ivar of the interactor without
  // actually changing the size of the window. Normally
  // application programmers would use UpdateSize if anything.
  // This is useful for letting someone else change the size of
  // the rendering window and just letting the interactor
  // know about the change.
  // The current event width/height (if any) is in EventSize 
  // (Expose event, for example).
  vtkSetVector2Macro(Size,int);
  vtkGetVector2Macro(Size,int);
  vtkSetVector2Macro(EventSize,int);
  vtkGetVector2Macro(EventSize,int);

  // Description:
  // When an event occurs, we must determine which Renderer the event
  // occurred within, since one RenderWindow may contain multiple
  // renderers.
  virtual vtkRenderer *FindPokedRenderer(int,int);

protected:
  vtkRenderWindowInteractor();
  ~vtkRenderWindowInteractor();

  vtkRenderWindow    *RenderWindow;
  vtkInteractorObserver *InteractorStyle;

  // Used as a helper object to pick instances of vtkProp
  vtkAbstractPicker          *Picker;

  int   Initialized;
  int   Enabled;
  int   Style;
  int   LightFollowCamera;
  int   ActorMode;
  double DesiredUpdateRate;
  double StillUpdateRate;  

  // Event information
  int   ControlKey;
  int   ShiftKey;
  char  KeyCode;
  int   RepeatCount;
  char* KeySym; 
  int   EventPosition[2];
  int   LastEventPosition[2];
  int   EventSize[2];
  int   Size[2];
  
  // control the fly to
  int NumberOfFlyFrames;
  double Dolly;
  
private:
  vtkRenderWindowInteractor(const vtkRenderWindowInteractor&);  // Not implemented.
  void operator=(const vtkRenderWindowInteractor&);  // Not implemented.
};

#endif
