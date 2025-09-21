import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import io

img = Image.open("1200.jpeg").convert("L")
img_matrix = np.array(img)

plt.imshow(img_matrix, cmap='gray')
plt.title("Original Image")
plt.axis('off')
plt.show()

print(f"Original image shape: {img_matrix.shape}")

U, S, VT = np.linalg.svd(img_matrix, full_matrices=False)

def reconstruct_image(k:int):
    S_k = np.diag(S[:k])
    U_k = U[:, :k]
    VT_k = VT[:k, :]
    return np.dot(U_k, np.dot(S_k, VT_k))

ks = [10, 50, 100, 200]
reconstructions = [reconstruct_image(k) for k in ks]

plt.figure(figsize=(12, 6))
for i, (k, rec) in enumerate(zip(ks, reconstructions)):
    plt.subplot(1, len(ks), i+1)
    plt.imshow(rec, cmap='gray')
    plt.title(f"k = {k}")
    plt.axis('off')
plt.suptitle("Compressed Images Using Top-k Singular Values")
plt.show()

def get_compressed_size(k:int):
    compressed_img = Image.fromarray(np.clip(reconstruct_image(k), 0, 255).astype('uint8'))
    buffer = io.BytesIO()
    compressed_img.save(buffer, format='JPEG', quality=95)
    return len(buffer.getvalue())

original_buffer = io.BytesIO()
img.save(original_buffer, format='JPEG', quality=95)
original_size = len(original_buffer.getvalue())

print("\nSIZE COMPARISON:")
print(f"Original image size: {original_size / 1024:.2f} KB")
for k in ks:
    size = get_compressed_size(k)
    print(f"Compressed with k={k}: {size / 1024:.2f} KB, saved: {(1 - size / original_size) * 100:.1f}%")

print("Higher k means better quality but less compression.")
print("Lower k gives stronger compression but loses more details.")
