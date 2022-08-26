import numpy as np
from scipy.stats import norm


A = np.arange(-60,60,1)
pdf = norm.pdf(A, scale=20)
for i in range(A.shape[0]):
	print(f"    color += texture2D(source, textureCoordinates - {A[i]:.1f} * offsetFactor) * {pdf[i]:.5f};")