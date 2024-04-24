from serial.tools import list_ports

import pydobot

class dobot_sp():
  j1 = 0
  j2 = 0
  j3 = 0
  j4 = 90
  velocity = 1000
  acceleration = 1000
  
  def __init__(self) -> None:
    available_ports = list_ports.comports()
    #print(f'available ports: {[x.device for x in available_ports]}')
    port = available_ports[0].device

    self.device = pydobot.Dobot(port=port, verbose=True)
    self.device.move_to(self.j1, self.j2, self.j3, self.j4, wait=True)
    # (self.x, self.y, self.z, self.r, _, _, _, _) = self.device.pose()
  
  def pose(self):
    return self.device.pose()
  
  def ready_position(self):
    self.device.move_to(self.j1 + 90, self.j2 + 10, self.j3, self.j4, wait=True)
    
  def pick_set(self):
    self.device.move_to(self.j1 + 90, self.j2 + 10, self.j3 + 70, self.j4, wait=True)    
    
  def dobot_init_sp(self):
    self.device.grip(False)
    self.device.speed(self.velocity, self.acceleration)
    self.ready_position()

  def pick_pl1(self):
    self.device.grip(False) # False = Gripper open / True = Gripper close
    self.device.wait(200)
    self.pick_set()
    self.device.wait(200)
    self.device.grip(True)
    self.device.wait(500)
    self.ready_position()
    self.device.wait(200)
    self.device.move_to(self.j1, self.j2 + 50, self.j3, self.j4, wait=True)
    self.device.wait(200)
    self.device.grip(False)
    self.device.wait(500)
    self.ready_position()
    
  def pick_pl2(self):
    self.device.grip(False) # False = Gripper open / True = Gripper close
    self.device.wait(200)
    self.pick_set()
    self.device.wait(200)
    self.device.grip(True)
    self.device.wait(500)
    self.ready_position()
    self.device.wait(200)
    self.device.move_to(self.j1, self.j2 - 5, self.j3, self.j4, wait=True)
    self.device.wait(200)
    self.device.grip(False)
    self.device.wait(500)
    self.ready_position()

  def pick_st(self):
    self.device.grip(False) # False = Gripper open / True = Gripper close
    self.device.wait(200)
    self.pick_set()
    self.device.wait(200)
    self.device.grip(True)
    self.device.wait(500)
    self.ready_position()
    self.device.wait(200)
    self.device.move_to(self.j1 - 40, self.j2 + 40, self.j3, self.j4, wait=True)
    self.device.wait(200)
    self.device.grip(False)
    self.device.wait(500)
    self.ready_position()

  def pick_pp(self):
    self.device.grip(False) # False = Gripper open / True = Gripper close
    self.device.wait(200)
    self.pick_set()
    self.device.wait(200)
    self.device.grip(True)
    self.device.wait(500)
    self.ready_position()
    self.device.wait(200)
    self.device.move_to(self.j1 + 40, self.j2 + 40, self.j3, self.j4, wait=True)
    self.device.wait(200)
    self.device.grip(False)
    self.device.wait(500)
    self.ready_position()

  def end_sp(self):
    self.device.suck(False)
    self.device.close()
