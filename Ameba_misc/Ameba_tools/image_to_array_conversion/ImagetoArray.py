from PIL import Image
import numpy as np

# Load the image
image_path = 'filename.png'  # Replace with your image path
img = Image.open(image_path)

# Convert image to RGBA to ensure inclusion of the alpha channel
img = img.convert('RGBA')

# Get image data as a numpy array
image_data = np.array(img)

# Flatten the 3D array to 2D where each row is a pixel [A, R, G, B]
pixels = image_data.reshape(-1, 4)

#uncomment and comment accordingly to the color format you would like to convert if needed
# RGBA1111 format (4-bit)
# rgba1111_array = []
# for r, g, b, a in pixels:
#     rgba1111 = ((r >> 7) << 3) | ((g >> 7) << 2) | ((b >> 7) << 1) | (a >> 7)
#     rgba1111_array.append(f"0x{rgba1111:01X}")
    
# RGBA2222 format (8-bit)
# rgba2222_array = []
# for r, g, b, a in pixels:
#     rgba2222 = ((r >> 6) << 6) | ((g >> 6) << 4) | ((b >> 6) << 2) | (a >> 6)
#     rgba2222_array.append(f"0x{rgba2222:02X}")

# RGBA4444 format (16-bit)
# rgba4444_array = []
# for r, g, b, a in pixels:
#     rgba4444 = ((r >> 4) << 12) | ((g >> 4) << 8) | ((b >> 4) << 4) | (a >> 4)
#     rgba4444_array.append(f"0x{rgba4444:04X}")
    
# RGBA5551 format (16-bit)
# rgba5551_array = []
# for r, g, b, a in pixels:
#     rgba5551 = ((r >> 3) << 11) | ((g >> 3) << 6) | ((b >> 3) << 1) | (1 if a > 127 else 0)
#     rgba5551_array.append(f"0x{rgba5551:04X}")

# RGBA8888 format: 0xRRGGBBAA
rgba8888_array = []
for r, g, b, a in pixels:
    rgba_value = (r << 24) | (g << 16) | (b << 8) | a
    rgba8888_array.append(f"0x{rgba_value:08X}")

with open(image_path, 'rb') as img_file:
    img_data = img_file.read()
    img_data_length = len(img_data)

print(f"The binary length of the image is: {img_data_length} bytes.")

output_file_path = 'filename.txt'  # Replace with your desired output file path

with open(output_file_path, 'w') as file:
    file.write('unsigned char pict0_bin[] __attribute__((aligned(32))) = {\n')
    for i, (r, g, b, a) in enumerate(pixels):
        if i % 8 == 0:
            file.write('\n    ')
        file.write(f"0x{r:02X}, 0x{g:02X}, 0x{b:02X}, 0x{a:02X}, ")

    file.write('\n};\n')

print(f"C-style array has been exported to {output_file_path}.")
