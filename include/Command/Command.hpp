#ifndef COMMAND_HPP
#define COMMAND_HPP
 #include<QtGui/QUndoCommand>
 //We have lists of commands that can be performed using by the mouse and keyboards enabled by user..
class Command:public QUndoCommand{
  private:
  float x;
  public:
  virtual void undo(){
    return;
  }

};




#endif