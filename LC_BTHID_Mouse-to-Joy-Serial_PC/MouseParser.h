#ifndef __mouserptparser_h__
#define __mouserptparser_h__

class MouseRptParser : public MouseReportParser {
  public:
    // the joyfactor is used to handle jostick sensitivity. Increase joy_factor to increase joystick sensitivity
    MouseRptParser() : xPos(0), yPos(0), joy_factor(28), pos_limit(512) {};
  private:
    int xPos;       // current X position value
    int yPos;       // current Y position value
    int joy_factor; // factor to scale the joystick value between -512 and +512
    int pos_limit;  // position limit (set to 512 in constructor)
    virtual void OnMouseMove(MOUSEINFO *mi);  
    virtual void OnMouseNotMove(MOUSEINFO *mi);  
  protected:
    virtual void OnLeftButtonUp(MOUSEINFO *mi);
    virtual void OnLeftButtonDown(MOUSEINFO *mi);
    virtual void OnRightButtonUp(MOUSEINFO *mi);
    virtual void OnRightButtonDown(MOUSEINFO *mi);
    virtual void OnMiddleButtonUp(MOUSEINFO *mi);
    virtual void OnMiddleButtonDown(MOUSEINFO *mi);
};

void MouseRptParser::OnMouseMove(MOUSEINFO *mi) {
  xPos = (mi->dX) * joy_factor;
  yPos = (mi->dY) * joy_factor;
  if (xPos < -pos_limit){
    xPos = -pos_limit;
  }
  else if (xPos > pos_limit){
    xPos = pos_limit;
  }
  if (yPos < -pos_limit){
    yPos = -pos_limit;
  }
  else if (yPos > pos_limit){
    yPos = pos_limit;
  }
  Serial.print("xPos : ");
  Serial.print(xPos);
  Serial.print("\t;\t");
  Serial.print("yPos : ");
  Serial.print(yPos);
  Serial.println();

  Joystick.X(map(xPos, -pos_limit, pos_limit, 0, 1023));
  Joystick.Y(map(yPos, -pos_limit, pos_limit, 0, 1023));

};

void MouseRptParser::OnMouseNotMove(MOUSEINFO *mi) {
  if((xPos != 0) || (yPos != 0))
  {
    xPos = 0;
    yPos = 0;
    Joystick.X(map(xPos, -pos_limit, pos_limit, 0, 1023));
    Joystick.Y(map(yPos, -pos_limit, pos_limit, 0, 1023));
  }
}

void MouseRptParser::OnLeftButtonUp(MOUSEINFO *mi) {
  Joystick.button(5,0); //arg=numero de bouton, on ou off (0 ou 1)
};

void MouseRptParser::OnLeftButtonDown(MOUSEINFO *mi) {
   Joystick.button(5,1);
};

void MouseRptParser::OnRightButtonUp(MOUSEINFO *mi) {
   Joystick.button(4,0);
};

void MouseRptParser::OnRightButtonDown(MOUSEINFO *mi) {
   Joystick.button(4,1); 
};

void MouseRptParser::OnMiddleButtonUp(MOUSEINFO *mi) {
   Joystick.button(3,0);
};

void MouseRptParser::OnMiddleButtonDown(MOUSEINFO *mi) {
   Joystick.button(3,1);
};

#endif
