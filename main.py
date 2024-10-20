from ultralytics import YOLO
import cv2
import cvzone
import numpy as np
import math
import pytesseract
import json

# Initialize Video Capture
cap = cv2.VideoCapture(0)
cap.set(3, 1280)
cap.set(4, 720)

# Load YOLO model
model = YOLO('../yolo11n.pt')

# Set path for Tesseract executable (Update the path as per your installation)
pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

classNames = [
    "person", "bicycle", "car", "motorbike", "aeroplane", "bus", "train", "truck", "boat",
    "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
    "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella",
    "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat",
    "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle", "wine glass", "cup",
    "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange", "broccoli",
    "carrot", "hot dog", "pizza", "donut", "cake", "chair", "sofa", "pottedplant", "bed",
    "diningtable", "toilet", "tvmonitor", "laptop", "mouse", "remote", "keyboard", "cell phone",
    "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors",
    "teddy bear", "hair drier", "toothbrush"
]

# List to store extracted data
extracted_data = []

while True:
    success, img = cap.read()
    results = model(img, stream=True)
    for r in results:
        boxes = r.boxes
        for box in boxes:
            # Bounding box
            x1, y1, x2, y2 = box.xyxy[0]
            x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
            w, h = x2 - x1, y2 - y1

            # Draw rectangle on the image
            cvzone.cornerRect(img, (x1, y1, w, h))

            # Extract object class and confidence
            conf = math.ceil((box.conf[0] * 100)) / 100
            cls = int(box.cls[0])
            label = f'{classNames[cls]} {conf}'

            # Display class name and confidence on the image
            cvzone.putTextRect(img, label, (max(0, x1), max(35, y1)))

            # OCR - Crop the region of interest (ROI)
            roi = img[y1:y2, x1:x2]

            # Convert ROI to grayscale (optional preprocessing for better OCR results)
            gray_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)

            # Use Tesseract to extract text from the ROI
            extracted_text = pytesseract.image_to_string(gray_roi)

            # Save detected object details and OCR result to a dictionary
            data = {
                "class": classNames[cls],
                "confidence": conf,
                "bounding_box": [x1, y1, x2, y2],
                "extracted_text": extracted_text.strip()
            }

            # Append data to the list
            extracted_data.append(data)

            # Optionally, print the OCR results in the console
            print(f'Extracted Text: {extracted_text}')

    # Display the webcam feed with the detected bounding boxes
    cv2.imshow('Webcam', img)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close windows
cap.release()
cv2.destroyAllWindows()

# Save extracted data to a JSON file
with open('extracted_data.json', 'w') as f:
    json.dump(extracted_data, f, indent=4)

print("Data saved to extracted_data.json")
