from keras.models import load_model  # TensorFlow is required for Keras to work
import cv2  # Install opencv-python
import numpy as np
from enum import Enum
import time

from Separate_move import dobot_sp

prev_time = 0
FPS = 5
total_capture = 0

class Product(Enum):
  Nothing = "None"
  Plastic = "Plastic"
  Styrofoam = "Styrofoam"
  Paper = "Paper" 

prev_product = Product.Nothing 
current_product = Product.Nothing

product_dict = {
  Product.Plastic.name : 0,
  Product.Styrofoam.name : 0,
  Product.Paper.name : 0,
}

bot = dobot_sp()

# Disable scientific notation for clarity
np.set_printoptions(suppress=True)

# Load the model
model = load_model("sp_keras_model.h5", compile=False)

# Load the labels
class_names = open("sp_labels.txt", "r").readlines()

# CAMERA can be 0 or 1 based on default camera of your computer
camera = cv2.VideoCapture(0)

bot.dobot_init_sp()

while True:
    # Grab the webcamera's image.
    ret, image = camera.read()
    current_time = time.time() - prev_time
    
    if (ret == True) and (current_time > 1. / FPS):
      prev_time = time.time()
      
      image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)
      cv2.imshow("Webcam Image", image)
      image = np.asarray(image, dtype=np.float32).reshape(1, 224, 224, 3)
      image = (image / 127.5) - 1
      
      # Predicts the model
      prediction = model.predict(image, verbose=None)
      index = np.argmax(prediction)
    
      class_name = class_names[index]
      confidence_score = prediction[0][index]

      # Print prediction and confidence score
      confidence = np.round(confidence_score * 100)
      current_class = class_name[2:].split("\n")[0]
      
      if confidence >= 97:
        if current_class == Product.Plastic.value:
          current_product = Product.Plastic
        elif current_class == Product.Styrofoam.value:
          current_product = Product.Styrofoam
        elif current_class == Product.Paper.value:
          current_product = Product.Paper
        elif current_class == Product.Nothing.value:
          current_product = Product.Nothing
      
      if(prev_product == Product.Nothing) and (current_product != Product.Nothing):
        if current_product == Product.Plastic:
          bot.pick_pl()
        elif current_product == Product.Styrofoam:
          bot.pick_st()
        elif current_product == Product.Paper:
          bot.pick_pp()
      
      prev_product = current_product
      
      if cv2.waitKey(1) == 27:
        break

bot.end_sp()
camera.release()
cv2.destroyAllWindows()