import cv2
import numpy as np

# Function to split and resize the image for multiple projectors, maintaining aspect ratio
def split_image_for_projectors(image, projectors=3, screen_width=1920, screen_height=1080):
    # Get the dimensions of the image
    image_height, image_width, _ = image.shape

    # Calculate the width of each part of the image for the projectors
    split_width = image_width // projectors

    splits = []

    for i in range(projectors):
        # Calculate the x-axis bounds for each split
        start_x = i * split_width
        end_x = start_x + split_width if i != projectors - 1 else image_width  # Handle the last split to cover the rest
        
        # Crop the image for the current projector
        split_image = image[:, start_x:end_x]
        
        # Create a black canvas (background) of 1920x1080 to paste the image onto
        canvas = np.zeros((screen_height, screen_width, 3), dtype=np.uint8)

        # Get the aspect ratios of the image and the projector screen
        image_aspect_ratio = split_image.shape[1] / split_image.shape[0]
        screen_aspect_ratio = screen_width / screen_height

        # Determine whether to fit the image based on width or height
        if image_aspect_ratio > screen_aspect_ratio:
            # Image is wider than the screen, fit to width
            new_width = screen_width
            new_height = int(new_width / image_aspect_ratio)
        else:
            # Image is taller than the screen, fit to height
            new_height = screen_height
            new_width = int(new_height * image_aspect_ratio)

        # Resize the split image to the new dimensions
        split_image_resized = cv2.resize(split_image, (new_width, new_height), interpolation=cv2.INTER_AREA)

        # Calculate the padding to center the image on the black canvas
        x_offset = (screen_width - new_width) // 2
        y_offset = (screen_height - new_height) // 2

        # Place the resized image onto the black canvas, centered
        canvas[y_offset:y_offset + new_height, x_offset:x_offset + new_width] = split_image_resized

        splits.append(canvas)

    return splits

# Load the image
image_path = 'apple.png'
image = cv2.imread(image_path)

# Check if the image was loaded correctly
if image is None:
    print("Error loading image")
    exit()

# Split the image for the projectors
projector_splits = split_image_for_projectors(image, projectors=3, screen_width=1920, screen_height=1080)

# Display each split image in separate windows using cv2.imshow()
for i, split_image in enumerate(projector_splits):
    window_name = f'Projector {i+1}'
    cv2.imshow(window_name, split_image)

# Wait for a key press and close all windows
cv2.waitKey(0)
cv2.destroyAllWindows()
