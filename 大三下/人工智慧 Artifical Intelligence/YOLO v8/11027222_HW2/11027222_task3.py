import cv2
import numpy as np
from ultralytics import YOLO

# Load the YOLOv8 pose model
model = YOLO("yolov8m-pose.pt")

# Load the image
image_path = "raisehand.png"  # Adjust this if the image is in a different directory
image = cv2.imread(image_path)

# Check if the image is loaded correctly
if image is None:
    raise FileNotFoundError(f"Failed to load image at {image_path}")

# Perform pose detection on the image
results = model.predict(source=image)
keypoints = results[0].keypoints.data.cpu().numpy()
boxes = results[0].boxes.data.cpu().numpy()

# Define skeleton connections for drawing
skeleton = {
    "head": [(0, 1), (1, 2), (2, 3), (3, 4), (4, 0), (0, 5), (0, 6)],
    "body": [(5, 6), (11, 12), (5, 11), (6, 12)],
    "hands": [(5, 7), (7, 9), (6, 8), (8, 10), (11, 13), (13, 15), (12, 14), (14, 16)]
}

# Function to draw lines and circles for skeleton
def draw_skeleton(image, keypoints, skeleton, color, threshold=0.5):
    for partA, partB in skeleton:
        if keypoints[partA][2] > threshold and keypoints[partB][2] > threshold:
            cv2.line(image, (int(keypoints[partA][0]), int(keypoints[partA][1])),
                     (int(keypoints[partB][0]), int(keypoints[partB][1])), color, 2)
            cv2.circle(image, (int(keypoints[partA][0]), int(keypoints[partA][1])), 3, color, -1)
            cv2.circle(image, (int(keypoints[partB][0]), int(keypoints[partB][1])), 3, color, -1)

# Function to draw bounding boxes
def draw_boxes(image, boxes, threshold=0.5):
    for box in boxes:
        x1, y1, x2, y2, confidence = box[:5]
        if confidence > threshold:
            cv2.rectangle(image, (int(x1), int(y1)), (int(x2), int(y2)), (0, 0, 255), 2)
            label = f"person {confidence:.2f}"
            cv2.putText(image, label, (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

# Function to check and label raised hands
def label_raised_hands(image, keypoints):
    left_wrist, right_wrist = keypoints[9], keypoints[10]
    left_elbow, right_elbow = keypoints[7], keypoints[8]
    left_shoulder, right_shoulder = keypoints[5], keypoints[6]

    if left_wrist[1] < left_elbow[1] and left_wrist[1] < left_shoulder[1]:
        cv2.putText(image, "UP", (int(left_wrist[0]), int(left_wrist[1])), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    
    if right_wrist[1] < right_elbow[1] and right_wrist[1] < right_shoulder[1]:
        cv2.putText(image, "UP", (int(right_wrist[0]), int(right_wrist[1])), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

# Draw skeletons, boxes, and label raised hands
for person in keypoints:
    draw_skeleton(image, person, skeleton["head"], (0, 255, 0))
    draw_skeleton(image, person, skeleton["body"], (255, 192, 203))
    draw_skeleton(image, person, skeleton["hands"], (255, 0, 0))
    label_raised_hands(image, person)

draw_boxes(image, boxes)

# Display the resulting image in a window
cv2.imshow("Pose Detection", image)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Save the resulting image
cv2.imwrite("out_raisehand.png", image)


