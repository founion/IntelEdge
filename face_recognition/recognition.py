import cv2

# Load frontal face recognizer
frontal_recognizer = cv2.face.LBPHFaceRecognizer_create()
frontal_recognizer.read('/home/yk/openvino_notebooks/train/frontal_trainer.yml')

# Load profile face recognizer
profile_recognizer = cv2.face.LBPHFaceRecognizer_create()
profile_recognizer.read('/home/yk/openvino_notebooks/train/profile_trainer.yml')

# Load frontal face cascade classifier
frontal_cascadePath = cv2.data.haarcascades + 'haarcascade_frontalface_default.xml'
frontal_faceCascade = cv2.CascadeClassifier(frontal_cascadePath)

# Load profile face cascade classifier
profile_cascadePath = cv2.data.haarcascades + 'haarcascade_profileface.xml'
profile_faceCascade = cv2.CascadeClassifier(profile_cascadePath)

font = cv2.FONT_HERSHEY_SIMPLEX

id = 0

# Mapping of IDs to names for frontal faces
frontal_id_to_names = ['jeonghwan', 'hojoon', 'yukyeong', 'ayeong', 'test1', 'unknown']

# Mapping of IDs to names for profile faces
profile_id_to_names = ['jeonghwan', 'hojoon', 'yukyeong', 'ayeong', 'test1', 'unknown']

cam = cv2.VideoCapture(0)
cam.set(3, 640)
cam.set(4, 480)

minW = 0.1 * cam.get(3)
minH = 0.1 * cam.get(4)

while True:
    ret, img = cam.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Detect frontal faces
    frontal_faces = frontal_faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,
        minSize=(int(minW), int(minH)),
    )

    # Detect profile faces
    profile_faces = profile_faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,
        minSize=(int(minW), int(minH)),
    )

    # Draw rectangles and recognize frontal faces
    for (x, y, w, h) in frontal_faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
        id_front, confidence = frontal_recognizer.predict(gray[y:y + h, x:x + w])
        
        if confidence < 70:  # 인식률 30% 이상인 경우
            id = frontal_id_to_names[id_front]
            confidence_text = " {0}%".format(round(100 - confidence))
        else:
            id = frontal_id_to_names[5]
            confidence_text = " "

        cv2.putText(img, str(id), (x + 5, y - 5), font, 1, (255, 255, 255), 2)
        cv2.putText(img, str(confidence_text), (x + 5, y + h - 2), font, 1, (255, 255, 0), 1)

    # Draw rectangles and recognize profile faces
    for (x, y, w, h) in profile_faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
        id_profile, confidence = profile_recognizer.predict(gray[y:y + h, x:x + w])

        if confidence < 70:  # 인식률 30% 이상인 경우
            id = profile_id_to_names[id_profile]
            confidence_text = " {0}%".format(round(100 - confidence))
        else:
            id = frontal_id_to_names[5]
            confidence_text = " "

        cv2.putText(img, str(id), (x + 5, y - 5), font, 1, (255, 255, 255), 2)
        cv2.putText(img, str(confidence_text), (x + 5, y + h - 2), font, 1, (255, 255, 0), 1)

    cv2.imshow('camera', img)
    k = cv2.waitKey(10) & 0xff
    if k == 27:
        break

print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()
