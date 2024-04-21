from serial.tools import list_ports

import pydobot

class dobot():
  x = 0
  y = 0
  z = 0
  r = 0
  velocity = 1000
  acceleration = 1000
  
  def __init__(self) -> None:
    available_ports = list_ports.comports()
    print(f'available ports: {[x.device for x in available_ports]}')
    port = available_ports[0].device

    self.device = pydobot.Dobot(port=port, verbose=True)

    (self.x, self.y, self.z, self.r, _, _, _, _) = self.device.pose()
    
  def dobot_init(self):
    self.device.suck(True)
    self.device.speed(self.velocity, self.acceleration)
    self.device.move_to(324, 0, 50, self.r, wait=True) 

  def pick(self):
    self.device.wait(2500)
    self.device.move_to(self.x, 0, 30, self.r, wait=True)
    self.device.move_to(self.x, 0, self.z + 20, self.r, wait=True)
    self.device.move_to(305, -95, self.z, self.r, wait=False)
    self.device.suck(False)
    self.device.move_to(324, 0, 50, self.r, wait=True)
    self.device.suck(True)

  def end(self):
    self.device.suck(False)
    self.device.close()
