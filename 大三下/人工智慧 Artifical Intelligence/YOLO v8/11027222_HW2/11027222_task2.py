import cv2
import numpy as np
from ultralytics import YOLO

def segment_and_replace(foreground_image_path, background_image_path, model_path, output_image_path, conf=0.5, angle=0):
    # Load YOLO model
    model = YOLO(model_path)
    
    # Load images
    foreground = cv2.imread(foreground_image_path, cv2.IMREAD_UNCHANGED)
    background = cv2.imread(background_image_path)
    
    # Ensure the foreground image has 3 channels (RGB)
    if foreground.shape[2] == 4:
        foreground = cv2.cvtColor(foreground, cv2.COLOR_BGRA2BGR)
    
    # Segment the foreground image
    results = model(foreground)
    mask = results[0].masks.data[0].cpu().numpy()  # Get the first mask
    
    # Ensure mask is in the correct format
    mask = mask.astype(np.uint8)
    mask = cv2.resize(mask, (foreground.shape[1], foreground.shape[0]))  # Resize mask to match foreground
    
    # Create an alpha channel based on the mask
    alpha_channel = (mask * 255).astype(np.uint8)
    
    # Add the alpha channel to the foreground image
    b, g, r = cv2.split(foreground)
    foreground_rgba = cv2.merge((b, g, r, alpha_channel))
    
    # Resize the foreground to fit the background
    scale_factor = min(background.shape[1] / foreground_rgba.shape[1], background.shape[0] / foreground_rgba.shape[0])
    new_width = int(foreground_rgba.shape[1] * scale_factor * 1.3)
    new_height = int(foreground_rgba.shape[0] * scale_factor * 0.95)
    foreground_rgba = cv2.resize(foreground_rgba, (new_width, new_height))
    
    # Rotate the foreground image if needed
    if angle != 0:
        center = (foreground_rgba.shape[1] // 2, foreground_rgba.shape[0] // 2)
        M = cv2.getRotationMatrix2D(center, angle, 1)
        foreground_rgba = cv2.warpAffine(foreground_rgba, M, (foreground_rgba.shape[1], foreground_rgba.shape[0]), borderMode=cv2.BORDER_CONSTANT, borderValue=(0, 0, 0, 0))
    
    # Ensure the background image is in the correct format
    if background.shape[2] == 3:
        b, g, r = cv2.split(background)
        alpha = np.ones(b.shape, dtype=b.dtype) * 255  # Create a fully opaque alpha channel
        background = cv2.merge((b, g, r, alpha))
    
    # Calculate the position to place the foreground
    x_offset = (background.shape[1] - foreground_rgba.shape[1]) // 2 + 30  # Shift right
    y_offset = (background.shape[0] - foreground_rgba.shape[0]) // 2 + 15  # Shift down
    
    # Composite the foreground onto the background
    alpha_channel = foreground_rgba[:, :, 3] / 255.0
    for c in range(0, 3):
        background[y_offset:y_offset+foreground_rgba.shape[0], x_offset:x_offset+foreground_rgba.shape[1], c] = \
            background[y_offset:y_offset+foreground_rgba.shape[0], x_offset:x_offset+foreground_rgba.shape[1], c] * (1 - alpha_channel) + \
            foreground_rgba[:, :, c] * alpha_channel
    
    # Save the output image
    cv2.imwrite(output_image_path, background)

# Paths to the images and model
foreground_image_path = 'me.png'
background_image_path = 'pilot.png'
model_path = 'yolov8m-seg.pt'
output_image_path = 'output.png'

# Perform segmentation and background replacement
segment_and_replace(foreground_image_path, background_image_path, model_path, output_image_path, angle=0)
