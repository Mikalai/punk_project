near = 0.1
far = 100
left = -1
right = 1
top = -1
bottom = 1

M = [2 * near / (right - left),  0,   (right + left) / (right - left),     0;
     0,      2*near / (top - bottom) ,    (top + bottom) / (top - bottom) ,0;
     0,  0,   - (far + near) / (far - near), - 2 * near * far / (far - near);
     0, 0, -1, 0]
     
     
