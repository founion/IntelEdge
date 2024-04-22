from serial.tools import list_ports

import pydobot

class dobot_sp():
  x = 190
  y1 = 5
  y2 = -200
  z = 90
  r = 0
  velocity = 500
  acceleration = 500
  
  def __init__(self) -> None:
    available_ports = list_ports.comports()
    print(f'available ports: {[x.device for x in available_ports]}')
    port = available_ports[0].device

    self.device = pydobot.Dobot(port=port, verbose=True)

    (self.x, self.y, self.z, self.r, _, _, _, _) = self.device.pose()
    
  def dobot_init_sp(self):
    self.device.suck(True)
    self.device.speed(self.velocity, self.acceleration)
    self.device.move_to(200, 200, 100, self.r, wait=True) 

  def pick_st(self):
    self.device.grip(False) # False = Gripper open / True = Gripper close
    self.device.move_to(self.x + 50, self.y1 + 200, self.z, self.r, wait=True)  # we wait until this movement is done before continuing
    self.device.wait(200)
    self.device.move_to(self.x + 50, self.y1 + 200, self.z - 100, self.r, wait=True)
    self.device.grip(True)
    self.device.wait(500)
    self.device.move_to(self.x + 50, self.y1 + 200, self.z, self.r, wait=True)
    self.device.wait(200)
    self.device.move_to(self.x, self.y1, self.z, self.r, wait=True)
    self.device.wait(200)
    self.device.move_to(self.x, self.y1, self.z - 50, self.r, wait=True)
    self.device.wait(200)
    self.device.grip(False)
    self.device.wait(500)
    self.device.move_to(self.x, self.y1, self.z, self.r, wait=True)
    self.device.suck(False)

  def pick_pp(self):
    self.device.grip(False) # False = Gripper open / True = Gripper close
    self.device.move_to(self.x + 50, self.y2 + 405, self.z, self.r, wait=True)  # we wait until this movement is done before continuing
    self.device.wait(200)
    self.device.move_to(self.x + 50, self.y2 + 405, self.z - 100, self.r, wait=True)
    self.device.grip(True)
    self.device.wait(500)
    self.device.move_to(self.x + 50, self.y2 + 405, self.z, self.r, wait=True)
    self.device.wait(200)
    self.device.move_to(self.x, self.y2, self.z, self.r, wait=True)
    self.device.wait(200)
    self.device.move_to(self.x, self.y2, self.z - 50, self.r, wait=True)
    self.device.wait(200)
    self.device.grip(False)
    self.device.wait(500)
    self.device.move_to(self.x, self.y2, self.z, self.r, wait=True)
    self.device.suck(False)

  def end_sp(self):
    self.device.suck(False)
    self.device.close()
